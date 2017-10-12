#include <string>
#include <vector>
#include <algorithm>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1XvsY.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/sumXvsY_cfg.h"
#include "../Config/jetXvsY_cfg.h"
#include "../Config/sumTurnons_cfg.h"
#include "../Config/jetTurnons_cfg.h"

#include "../Debug/DebugHandler.h"

// CHUNK = which chunk of root-files to run over
// NJOBS = number of jobs to submit
void makeAll(const int & CHUNK, const int & NJOBS, const int & NENT, const int & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1XvsY* > xvsys = sumXvsYs(dataset);
    std::map< std::string, TL1XvsY* > jetXvsYs_ = jetXvsYs(dataset);
    xvsys.insert(jetXvsYs_.begin(), jetXvsYs_.end());

    std::map< std::string, TL1Turnon* > turnons = sumTurnons(dataset);
    std::map< std::string, TL1Turnon* > jetTurnons_ = jetTurnons(dataset);
    turnons.insert(jetTurnons_.begin(), jetTurnons_.end());

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/All/" );
    if( !COMBINE ) outDir = dataset->outDir + Form("_CHUNK%i/All/",CHUNK);
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
        if( dataset->triggerName == "SingleMu" )
            if( !event->fMuonFilterPassFlag )
                continue;

        // Get the relevant event parameters
        int pu = event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;
        auto jets = event->GetPEvent()->fJets;

        // MET
        double l1MetBE = event->fL1Met;
        double l1EmuMetBE = event->fL1EmuMet;
        double recoMetBE = sums->caloMetBE;
        double l1MetHF = event->fL1MetHF;
        double l1EmuMetHF = event->fL1EmuMetHF;
        double recoMetHF = sums->caloMet;

        // HTT
        double l1Htt = event->fL1Htt;
        double l1EmuHtt = event->fL1EmuHtt;
        double recalcRecoHtt = event->fRecalcRecoHtt;
        double recalcRecoHttNoMEF = event->fRecalcRecoHttNoMEF;
        double recoHtt = sums->Ht;

        // SUMS - XVSYS
        if( xvsys.find("recoHtt_l1Htt") != xvsys.end() )
            xvsys["recoHtt_l1Htt"]->Fill(recoHtt, l1Htt, pu);
        if( xvsys.find("recoHtt_l1EmuHtt") != xvsys.end() )
            xvsys["recoHtt_l1EmuHtt"]->Fill(recoHtt, l1EmuHtt, pu);

        if( event->fMhtPassFlag )
        {
            if( xvsys.find("recalcRecoHtt_l1Htt") != xvsys.end() )
                xvsys["recalcRecoHtt_l1Htt"]->Fill(recalcRecoHtt, l1Htt, pu);
            if( xvsys.find("recalcRecoHtt_l1EmuHtt") != xvsys.end() )
                xvsys["recalcRecoHtt_l1EmuHtt"]->Fill(recalcRecoHtt, l1EmuHtt, pu);
            if( xvsys.find("recalcRecoHttNoMEF_l1Htt") != xvsys.end() )
                xvsys["recalcRecoHttNoMEF_l1Htt"]->Fill(recalcRecoHttNoMEF, l1Htt, pu);
            if( xvsys.find("recalcRecoHttNoMEF_l1EmuHtt") != xvsys.end() )
                xvsys["recalcRecoHttNoMEF_l1EmuHtt"]->Fill(recalcRecoHttNoMEF, l1EmuHtt, pu);
        }

        if( event->fMetFilterPassFlag )
        {
            if( xvsys.find("caloMetBE_l1MetBE") != xvsys.end() )
                xvsys["caloMetBE_l1MetBE"]->Fill(recoMetBE, l1MetBE, pu);
            if( xvsys.find("caloMetHF_l1MetHF") != xvsys.end() )
                xvsys["caloMetHF_l1MetHF"]->Fill(recoMetHF, l1MetHF, pu);
            if( xvsys.find("caloMetBE_l1EmuMetBE") != xvsys.end() )
                xvsys["caloMetBE_l1EmuMetBE"]->Fill(recoMetBE, l1EmuMetBE, pu);
            if( xvsys.find("caloMetHF_l1EmuMetHF") != xvsys.end() )
                xvsys["caloMetHF_l1EmuMetHF"]->Fill(recoMetHF, l1EmuMetHF, pu);
        }


        // SUMS - TURNONS
        if( turnons.find("htt") != turnons.end() )
            turnons["htt"]->Fill(recoHtt, l1Htt, pu);
        if( turnons.find("emuHtt") != turnons.end() )
            turnons["emuHtt"]->Fill(recoHtt, l1EmuHtt, pu);
        
        if( event->fMhtPassFlag )
        {
            if( turnons.find("recalcHtt") != turnons.end() )
                turnons["recalcHtt"]->Fill(recalcRecoHtt, l1Htt, pu);
            if( turnons.find("emuRecalcHtt") != turnons.end() )
                turnons["emuRecalcHtt"]->Fill(recalcRecoHtt, l1EmuHtt, pu);
            if( turnons.find("recalcHttNoMEF") != turnons.end() )
                turnons["recalcHttNoMEF"]->Fill(recalcRecoHttNoMEF, l1Htt, pu);
            if( turnons.find("emuRecalcHttNoMEF") != turnons.end() )
                turnons["emuRecalcHttNoMEF"]->Fill(recalcRecoHttNoMEF, l1EmuHtt, pu);
        }

        if( event->fMetFilterPassFlag )
        {
            if( turnons.find("metBE") != turnons.end() )
                turnons["metBE"]->Fill(recoMetBE, l1MetBE, pu);
            if( turnons.find("metHF") != turnons.end() )
                turnons["metHF"]->Fill(recoMetHF, l1MetHF, pu);
            if( turnons.find("emuMetBE") != turnons.end() )
                turnons["emuMetBE"]->Fill(recoMetBE, l1EmuMetBE, pu);
            if( turnons.find("emuMetHF") != turnons.end() )
                turnons["emuMetHF"]->Fill(recoMetHF, l1EmuMetHF, pu);
        }
        
        if( event->fIsLeadingRecoJet && event->fIsMatchedL1Jet )
        {
            double recoJetEt = jets->etCorr[event->fLeadingRecoJetIndex];
            double recoJetEta = jets->eta[event->fLeadingRecoJetIndex];
            double l1JetEt = event->fL1JetEt[event->fMatchedL1JetIndex];
            double l1EmuJetEt = event->fL1EmuJetEt[event->fMatchedL1EmuJetIndex];

            // JETS - XVSYS
            if( abs(recoJetEta) <= 1.479 )
            {
                if( xvsys.find("recoL1JetEtB") != xvsys.end() )
                    xvsys["recoL1JetEtB"]->Fill(recoJetEt, l1JetEt, pu);
                if( xvsys.find("recoL1JetEtBE") != xvsys.end() )
                    xvsys["recoL1JetEtBE"]->Fill(recoJetEt, l1JetEt, pu);
                if( xvsys.find("recoL1EmuJetEtB") != xvsys.end() )
                    xvsys["recoL1EmuJetEtB"]->Fill(recoJetEt, l1EmuJetEt, pu);
                if( xvsys.find("recoL1EmuJetEtBE") != xvsys.end() )
                    xvsys["recoL1EmuJetEtBE"]->Fill(recoJetEt, l1EmuJetEt, pu);
            }
            else if( abs(recoJetEta) <= 3.0 )
            {
                if( xvsys.find("recoL1JetEtE") != xvsys.end() )
                    xvsys["recoL1JetEtE"]->Fill(recoJetEt, l1JetEt, pu);
                if( xvsys.find("recoL1JetEtBE") != xvsys.end() )
                    xvsys["recoL1JetEtBE"]->Fill(recoJetEt, l1JetEt, pu);
                if( xvsys.find("recoL1EmuJetEtE") != xvsys.end() )
                    xvsys["recoL1EmuJetEtE"]->Fill(recoJetEt, l1EmuJetEt, pu);
                if( xvsys.find("recoL1EmuJetEtBE") != xvsys.end() )
                    xvsys["recoL1EmuJetEtBE"]->Fill(recoJetEt, l1EmuJetEt, pu);
            }
            else
            {
                if( xvsys.find("recoL1JetEtHF") != xvsys.end() )
                    xvsys["recoL1JetEtHF"]->Fill(recoJetEt, l1JetEt, pu);
                if( xvsys.find("recoL1EmuJetEtHF") != xvsys.end() )
                    xvsys["recoL1EmuJetEtHF"]->Fill(recoJetEt, l1EmuJetEt, pu);
            }

            // JETS - TURNONS
            if( abs(recoJetEta) <= 1.479 )
            {
                if( turnons.find("jetEtB") != turnons.end() )
                    turnons["jetEtB"]->Fill(recoJetEt, l1JetEt, pu);
                if( turnons.find("jetEtBE") != turnons.end() )
                    turnons["jetEtBE"]->Fill(recoJetEt, l1JetEt, pu);
                if( turnons.find("emuJetEtB") != turnons.end() )
                    turnons["emuJetEtB"]->Fill(recoJetEt, l1EmuJetEt, pu);
                if( turnons.find("emuJetEtBE") != turnons.end() )
                    turnons["emuJetEtBE"]->Fill(recoJetEt, l1EmuJetEt, pu);
            }
            else if( abs(recoJetEta) <= 3.0 )
            {
                if( turnons.find("jetEtE") != turnons.end() )
                    turnons["jetEtE"]->Fill(recoJetEt, l1JetEt, pu);
                if( turnons.find("jetEtBE") != turnons.end() )
                    turnons["jetEtBE"]->Fill(recoJetEt, l1JetEt, pu);
                if( turnons.find("emuJetEtE") != turnons.end() )
                    turnons["emuJetEtE"]->Fill(recoJetEt, l1EmuJetEt, pu);
                if( turnons.find("emuJetEtBE") != turnons.end() )
                    turnons["emuJetEtBE"]->Fill(recoJetEt, l1EmuJetEt, pu);
            }
            else
            {
                if( turnons.find("jetEtHF") != turnons.end() )
                    turnons["jetEtHF"]->Fill(recoJetEt, l1JetEt, pu);
                if( turnons.find("emuJetEtHF") != turnons.end() )
                    turnons["emuJetEtHF"]->Fill(recoJetEt, l1EmuJetEt, pu);
            }
        }
    }

    // End
    for(auto it=xvsys.begin(); it!=xvsys.end(); ++it)
        it->second->DrawPlots();
    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        it->second->DrawPlots();
        it->second->DrawTurnons();
    }

    cout << "Output saved in:\n\t" << outDir << endl;
}
