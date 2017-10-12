#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1Resolution.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/sumResolutions_cfg.h"

#include "../Debug/DebugHandler.h"

double FoldPhi(double phi);

// CHUNK = which chunk of root-files to run over
// NJOBS = number of jobs to submit
void makeResolutions(const int & CHUNK, const int & NJOBS, const int & NENT, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1Resolution* > resolutions = sumResolutions(dataset);

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/Resolution/" );
    if(!COMBINE) outDir = dataset->outDir + Form("_CHUNK%i/Resolution/",CHUNK);
    else inDir.clear();
    TL1EventClass * event(new TL1EventClass(inDir));

    // Being
    for(auto it=resolutions.begin(); it!=resolutions.end(); ++it)
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
        int pu = event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        // MET
        double l1MetBE = event->fL1Met;
        double l1MetHF = event->fL1MetHF;
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double l1MetPhiBE = event->fL1MetPhi;
        double l1MetPhiHF = event->fL1MetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;

        // HTT
        double recoHtt = sums->Ht;
        double l1Htt = event->fL1Htt;

        if( recoHtt > 1500. && l1Htt > 0. )
            if( resolutions.find("recoHtt_l1Htt") != resolutions.end() )
                resolutions["recoHtt_l1Htt"]->Fill(recoHtt, l1Htt, pu);

        // Fill resolutions with event parameters. Includes the fill logic
        if( event->fMetFilterPassFlag )
        {
            if( recoMetBE > 40.0 && l1MetBE > 0.0 )
            {
                if( resolutions.find("caloMetBE_l1MetBE") != resolutions.end() )
                    resolutions["caloMetBE_l1MetBE"]->Fill(recoMetBE, l1MetBE, pu);
                if( resolutions.find("caloMetPhiBE_l1MetPhiBE") != resolutions.end() )
                    resolutions["caloMetPhiBE_l1MetPhiBE"]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1MetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1MetBE > 0.0 )
            {
                if( resolutions.find("caloMetHF_l1MetBE") != resolutions.end() )
                    resolutions["caloMetHF_l1MetBE"]->Fill(recoMetHF, l1MetBE, pu);
                if( resolutions.find("caloMetPhiHF_l1MetPhiBE") != resolutions.end() )
                    resolutions["caloMetPhiHF_l1MetPhiBE"]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1MetHF > 0.0 )
            {
                if( resolutions.find("caloMetHF_l1MetBE") != resolutions.end() )
                    resolutions["caloMetHF_l1MetHF"]->Fill(recoMetHF, l1MetHF, pu);
                if( resolutions.find("caloMetPhiHF_l1MetPhiBE") != resolutions.end() )
                    resolutions["caloMetPhiHF_l1MetPhiHF"]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiHF), pu);
            }
        }
    }

    // End
    for(auto it=resolutions.begin(); it!=resolutions.end(); ++it)
        it->second->DrawPlots();
    cout << "Output saved in:\n\t" << outDir << endl;
}

double FoldPhi(double phi)
{
    return TMath::Min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
}
