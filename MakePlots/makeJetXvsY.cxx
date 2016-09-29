#include <string>
#include <vector>
#include <algorithm>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Utilities/TL1DateTime.C"
#include "../Plotting/TL1XvsY.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/jetXvsY_cfg.h"

#include "../Debug/DebugHandler.h"

double FoldPhi(double phi);

// CHUNK = which chunk of root-files to run over
// NFILES = numbers of root-files
// NJOBS = number of jobs to submit
void makeJetXvsY(const int & CHUNK, const int & NFILES, const int & NJOBS, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1XvsY* > xvsys = jetXvsYs(dataset);

    // Split the files into CHUNKS:
    // 1 to n; n+1 to 2n; 2n+1 to 3n ... NJOBS*n to NFILES
    // n = nFilesPerJob
    // The final job is typically larger than the others (never smaller)
    std::vector<std::string> inDir;
    std::string outDir( dataset->outDir+"_hadd/XvsYJets/" );
    if( !COMBINE )
    {
        outDir = dataset->outDir;
        if( NJOBS > 1 ) outDir += Form("_CHUNK%i",CHUNK);
        outDir += "/XvsYJets/";

        int nFilesPerJob( NFILES / NJOBS );
        int finalFile( nFilesPerJob*(1+CHUNK) );
        if( CHUNK == NJOBS-1 ) finalFile = NFILES;

        for(int i=1+(CHUNK*nFilesPerJob); i<=finalFile; ++i)
            inDir.push_back(Form(dataset->inFiles.c_str(),i));
    }
    TL1EventClass * event(new TL1EventClass(inDir));

    // Begin
    for(auto it=xvsys.begin(); it!=xvsys.end(); ++it)
    {
        it->second->SetSample(dataset->sampleName, dataset->sampleTitle);
        it->second->SetTrigger(dataset->triggerName,dataset->triggerTitle);
        it->second->SetRun(dataset->run);
        it->second->SetOutDir(outDir);
        it->second->SetPuType(dataset->puType);
        it->second->SetPuBins(dataset->puBins);
        if( dataset->sampleName != "Data" ) it->second->SetPuFile(dataset->puFilename);
        if( !COMBINE ) it->second->InitPlots();
        else it->second->OverwritePlots();
    }

    // Loop
    unsigned NEntries(0); 
    if( !COMBINE ) NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() && !COMBINE )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        // Skip events that don't meet the selection criteria
        if( !event->fIsLeadingRecoJet ) continue;
        if( !event->fIsMatchedL1Jet ) continue;

        // Get the relevant event parameters
        int pu = event->GetPEvent()->fVertex->nVtx;
        auto jets = event->GetPEvent()->fJets;

        double recoEt = jets->etCorr[event->fLeadingRecoJetIndex];
        double recoEta = jets->eta[event->fLeadingRecoJetIndex];
        double recoPhi = jets->phi[event->fLeadingRecoJetIndex];

        double l1Et = event->fL1JetEt[event->fMatchedL1JetIndex];
        double l1Eta = event->fL1JetEta[event->fMatchedL1JetIndex];
        double l1Phi = event->fL1JetPhi[event->fMatchedL1JetIndex];

        // Fill xvsy with event parameters. Includes fill logic (e.g. different eta ranges)
        if( xvsys.find("recoL1JetEta") != xvsys.end() )
            xvsys["recoL1JetEta"]->Fill(recoEta, l1Eta, pu);
        if( abs(recoEta) <= 1.479 )
        {
            // Jet Et
            if( xvsys.find("recoL1JetEtB") != xvsys.end() )
                xvsys["recoL1JetEtB"]->Fill(recoEt, l1Et, pu);
            if( xvsys.find("recoL1JetEtBE") != xvsys.end() )
                xvsys["recoL1JetEtBE"]->Fill(recoEt, l1Et, pu);

            // Jet Phi
            if( xvsys.find("recoL1JetPhiB") != xvsys.end() )
                xvsys["recoL1JetPhiB"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
            if( xvsys.find("recoL1JetPhiBE") != xvsys.end() )
                xvsys["recoL1JetPhiBE"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        }
        else if( abs(recoEta) <= 3.0 )
        {
            // Jet Et
            if( xvsys.find("recoL1JetEtE") != xvsys.end() )
                xvsys["recoL1JetEtE"]->Fill(recoEt, l1Et, pu);
            if( xvsys.find("recoL1JetEtBE") != xvsys.end() )
                xvsys["recoL1JetEtBE"]->Fill(recoEt, l1Et, pu);

            // Jet Phi
            if( xvsys.find("recoL1JetPhiE") != xvsys.end() )
                xvsys["recoL1JetPhiE"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
            if( xvsys.find("recoL1JetPhiBE") != xvsys.end() )
                xvsys["recoL1JetPhiBE"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        }
        else
        {
            // Jet Et
            if( xvsys.find("recoL1JetEtHF") != xvsys.end() )
                xvsys["recoL1JetEtHF"]->Fill(recoEt, l1Et, pu);

            // Jet Phi
            if( xvsys.find("recoL1JetPhiHF") != xvsys.end() )
                xvsys["recoL1JetPhiHF"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        }
    }

    // End
    for(auto it=xvsys.begin(); it!=xvsys.end(); ++it)
        it->second->DrawPlots();
    cout << "Output saved in:\n\t" << outDir << endl;
}

double FoldPhi(double phi)
{
    return min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
}
