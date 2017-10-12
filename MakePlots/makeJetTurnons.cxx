#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1Turnon.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/jetTurnons_cfg.h"

#include "../Debug/DebugHandler.h"

// CHUNK = which chunk of root-files to run over
// NJOBS = number of jobs to submit
void makeJetTurnons(const int & CHUNK, const int & NJOBS, const int & NENT, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1Turnon* > turnons = jetTurnons(dataset);

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/TurnonsJets/" );
    if(!COMBINE) outDir = dataset->outDir + Form("_CHUNK%i/TurnonsJets/",CHUNK);
    else inDir.clear();
    TL1EventClass * event(new TL1EventClass(inDir));

    // Begin
    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        it->second->SetSample(dataset->sampleName, dataset->sampleTitle);
        it->second->SetTrigger(dataset->triggerName, dataset->triggerTitle);
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
        double recoPhi = recoJet->phi[event->fLeadingRecoJetIndex];

        double l1Et = event->fL1EmuJetEt[event->fMatchedL1EmuJetIndex];
        double l1Eta = event->fL1EmuJetEta[event->fMatchedL1EmuJetIndex];
        double l1Phi = event->fL1EmuJetPhi[event->fMatchedL1EmuJetIndex];

        // Fill turnon with event parameters. Includes fill logic (e.g. different eta ranges)
        if( abs(recoEta) <= 1.479 )
        {
            if( turnons.find("jetEtBarrel") != turnons.end() )
                turnons["jetEtBarrel"]->Fill(recoEt, l1Et, pu);
            if( turnons.find("jetEtCentral") != turnons.end() )
                turnons["jetEtCentral"]->Fill(recoEt, l1Et, pu);
        }
        else if( abs(recoEta) <= 3.0 )
        {
            if( turnons.find("jetEtEndcap") != turnons.end() )
                turnons["jetEtEndcap"]->Fill(recoEt, l1Et, pu);
            if( turnons.find("jetEtCentral") != turnons.end() )
                turnons["jetEtCentral"]->Fill(recoEt, l1Et, pu);
        }
        else
        {
            if( turnons.find("jetEtHF") != turnons.end() )
                turnons["jetEtHF"]->Fill(recoEt, l1Et, pu);
        }
    }

    // End
    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        it->second->DrawPlots();
        it->second->DrawTurnons();
    }
    cout << "\tOutput saved in:\n" << outDir << endl;
}
