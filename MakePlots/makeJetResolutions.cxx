#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1Resolution.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/jetResolutions_cfg.h"

#include "../Debug/DebugHandler.h"

double FoldPhi(double phi);

// CHUNK = which chunk of root-files to run over
// NFILES = numbers of root-files
// NJOBS = number of jobs to submit
void makeJetResolutions(const int & CHUNK, const int & NJOBS, const int & NENT, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1Resolution* > resolutions = jetResolutions(dataset);

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/Turnons/" );
    if(!COMBINE) outDir = dataset->outDir + Form("_CHUNK%i/Turnons/",CHUNK);
    else inDir.clear();
    TL1EventClass * event(new TL1EventClass(inDir));

    // Begin
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
        if( !event->fIsLeadingRecoJet ) continue;
        if( !event->fIsMatchedL1Jet ) continue;

        // Get the relevant event parameters
        int pu = event->GetPEvent()->fVertex->nVtx;
        auto recoJet = event->GetPEvent()->fJets;

        double recoEt = recoJet->etCorr[event->fLeadingRecoJetIndex];
        double recoEta = recoJet->eta[event->fLeadingRecoJetIndex];
        double recoPhi = FoldPhi(recoJet->phi[event->fLeadingRecoJetIndex]);

        double l1Et = event->fL1JetEt[event->fMatchedL1JetIndex];
        double l1Eta = event->fL1JetEta[event->fMatchedL1JetIndex];
        double l1Phi = FoldPhi(event->fL1JetPhi[event->fMatchedL1JetIndex]);

        // Fill resolutions with event parameters. Includes the fill logic
        if( abs(recoEta) <= 1.479 )
        {
            if( resolutions.find("jetEtB") != resolutions.end() )
                if( recoEt!=0. && l1Et!=0. && recoEt>=30. )
                    resolutions["jetEtB"]->Fill(recoEt, l1Et, pu);
            if( resolutions.find("jetPhiB") != resolutions.end() )
                if( recoPhi!=0. && l1Phi!=0. && recoEt>=30. )
                    resolutions["jetPhiB"]->Fill(recoPhi, l1Phi, pu);
            if( resolutions.find("jetEtaB") != resolutions.end() )
                if( recoEta!=0. && l1Eta!=0. && recoEt>=30. )
                    resolutions["jetEtaB"]->Fill(abs(recoEta), abs(l1Eta), pu);

            if( resolutions.find("jetEtBE") != resolutions.end() )
                if( recoEt!=0. && l1Et!=0. && recoEt>=30. )
                    resolutions["jetEtBE"]->Fill(recoEt, l1Et, pu);
            if( resolutions.find("jetPhiBE") != resolutions.end() )
                if( recoPhi!=0. && l1Phi!=0. && recoEt>=30. )
                    resolutions["jetPhiBE"]->Fill(recoPhi, l1Phi, pu);
            if( resolutions.find("jetEtaBE") != resolutions.end() )
                if( recoEta!=0. && l1Eta!=0. && recoEt>=30. )
                    resolutions["jetEtaBE"]->Fill(abs(recoEta), abs(l1Eta), pu);
        }
        else if( abs(recoEta) <= 3.0 )
        {
            if( resolutions.find("jetEtE") != resolutions.end() )
                if( recoEt!=0. && l1Et!=0. && recoEt>=30. )
                    resolutions["jetEtE"]->Fill(recoEt, l1Et, pu);
            if( resolutions.find("jetPhiE") != resolutions.end() )
                if( recoPhi!=0. && l1Phi!=0. && recoEt>=30. )
                    resolutions["jetPhiE"]->Fill(recoPhi, l1Phi, pu);
            if( resolutions.find("jetEtaE") != resolutions.end() )
                if( recoEta!=0. && l1Eta!=0. && recoEt>=30. )
                    resolutions["jetEtaE"]->Fill(abs(recoEta), abs(l1Eta), pu);

            if( resolutions.find("jetEtBE") != resolutions.end() )
                if( recoEt!=0. && l1Et!=0. && recoEt>=30. )
                    resolutions["jetEtBE"]->Fill(recoEt, l1Et, pu);
            if( resolutions.find("jetPhiBE") != resolutions.end() )
                if( recoPhi!=0. && l1Phi!=0. && recoEt>=30. )
                    resolutions["jetPhiBE"]->Fill(recoPhi, l1Phi, pu);
            if( resolutions.find("jetEtaBE") != resolutions.end() )
                if( recoEta!=0. && l1Eta!=0. && recoEt>=30. )
                    resolutions["jetEtaBE"]->Fill(abs(recoEta), abs(l1Eta), pu);
        }
        else
        {
            if( resolutions.find("jetEtHF") != resolutions.end() )
                if( recoEt!=0. && l1Et!=0. && recoEt>=30. )
                    resolutions["jetEtHF"]->Fill(recoEt, l1Et, pu);
            if( resolutions.find("jetPhiHF") != resolutions.end() )
                if( recoPhi!=0. && l1Phi!=0. && recoEt>=30. )
                    resolutions["jetPhiHF"]->Fill(recoPhi, l1Phi, pu);
            if( resolutions.find("jetEtaHF") != resolutions.end() )
                if( recoEta!=0. && l1Eta!=0. && recoEt>=30. )
                    resolutions["jetEtaHF"]->Fill(abs(recoEta), abs(l1Eta), pu);
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
