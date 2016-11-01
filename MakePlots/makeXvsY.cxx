#include <string>
#include <vector>
#include <algorithm>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1XvsY.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/sumXvsY_cfg.h"

#include "../Debug/DebugHandler.h"

double FoldPhi(double phi);

// CHUNK = which chunk of root-files to run over
// NJOBS = number of jobs to submit
void makeXvsY(const int & CHUNK, const int & NJOBS, const int & NENT, const int & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1XvsY* > xvsys = sumXvsYs(dataset);

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/XvsY/" );
    if( !COMBINE ) outDir = dataset->outDir + Form("_CHUNK%i/XvsY/",CHUNK);
    else inDir.clear();
    TL1EventClass * event(new TL1EventClass(inDir));

    // Begin
    for(auto it=xvsys.begin(); it!=xvsys.end(); ++it)
    {
        it->second->SetSample(dataset->sampleName,dataset->sampleTitle);
        it->second->SetTrigger(dataset->triggerName,dataset->triggerTitle);
        it->second->SetRun(dataset->run);
        it->second->SetOutDir(outDir);
        it->second->SetPuType(dataset->puType);
        it->second->SetPuBins(dataset->puBins);
        //if( dataset->sampleName != "Data" ) it->second->SetPuFile(dataset->puFilename);
        if( !COMBINE ) it->second->InitPlots();
        else it->second->OverwritePlots();
    }

    unsigned start(0), end(0);
    if( !COMBINE )
    {
        unsigned NEvents(NENT / NJOBS);
        start = CHUNK * NEvents;
        end   = (CHUNK+1) * NEvents;
        if( CHUNK == NJOBS-1 ) end = NENT;
    }

    // Loop
    for(int i=start; i<end && !COMBINE; ++i)
    {
        event->GetEntry(i);
        TL1Progress::PrintProgressBar(i-start, end-start);

        // Skip events that don't meet the selection criteria
        if( dataset->triggerName == "SingleMu" )
            if( !event->fMuonFilterPassFlag )
                continue;

        // Get the relevant event parameters
        int pu = 0;//event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        double l1MetBE = event->fL1Met;
        double l1MetHF = event->fL1MetHF;
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double recalcL1MetBE = event->fRecalcL1Met;

        double l1MetPhiBE = event->fL1MetPhi;
        double l1MetPhiHF = event->fL1MetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;

        double l1MexBE = event->fL1Mex;
        double l1MeyBE = event->fL1Mey;
        double recoMexBE = l1MetBE * TMath::Cos(l1MetPhiBE);
        double recoMeyBE = l1MetBE * TMath::Sin(l1MetPhiBE);

        double l1Htt = event->fL1Htt;
        double recoHtt = sums->Ht;

        //----- HTT -----//
        if( xvsys.find("recoHtt_l1Htt") != xvsys.end() )
            xvsys["recoHtt_l1Htt"]->Fill(recoHtt, l1Htt, pu);

        // Fill xvsy with event parameters
        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            if( xvsys.find("caloMetBE_l1MetBE") != xvsys.end() )
                xvsys["caloMetBE_l1MetBE"]->Fill(recoMetBE, l1MetBE, pu);
            if( xvsys.find("caloMetHF_l1MetBE") != xvsys.end() )
                xvsys["caloMetHF_l1MetBE"]->Fill(recoMetHF, l1MetBE, pu);
            if( xvsys.find("caloMetHF_l1MetHF") != xvsys.end() )
                xvsys["caloMetHF_l1MetHF"]->Fill(recoMetHF, l1MetHF, pu);

            if( xvsys.find("l1MetBE_recalcL1MetBE") != xvsys.end() )
                xvsys["l1MetBE_recalcL1MetBE"]->Fill(l1MetBE, recalcL1MetBE, pu);

            if( xvsys.find("caloMetPhiBE_l1MetPhiBE") != xvsys.end() )
                xvsys["caloMetPhiBE_l1MetPhiBE"]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1MetPhiBE), pu);
            if( xvsys.find("caloMetPhiHF_l1MetPhiBE") != xvsys.end() )
                xvsys["caloMetPhiHF_l1MetPhiBE"]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiBE), pu);
            if( xvsys.find("caloMetPhiHF_l1MetPhiHF") != xvsys.end() )
                xvsys["caloMetPhiHF_l1MetPhiHF"]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiHF), pu);

            if( xvsys.find("caloMetXBE_l1MetXBE") != xvsys.end() )
                xvsys["caloMetXBE_l1MetXBE"]->Fill(recoMexBE, l1MexBE, pu);
            if( xvsys.find("caloMetYBE_l1MetYBE") != xvsys.end() )
                xvsys["caloMetYBE_l1MetYBE"]->Fill(recoMeyBE, l1MeyBE, pu);
        }
    }

    // End
    for(auto it=xvsys.begin(); it!=xvsys.end(); ++it)
        it->second->DrawPlots();
    cout << "Output saved in:\n\t" << outDir << endl;
}

double FoldPhi(double phi)
{
    return TMath::Min( (float)TMath::Abs(phi), (float)TMath::Abs(2*TMath::Pi()-phi) );
}
