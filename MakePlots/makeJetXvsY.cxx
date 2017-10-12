#include <string>
#include <vector>
#include <algorithm>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Plotting/TL1XvsY.h"

#include "../Config/ntuple_cfg.h"
#include "../Config/jetXvsY_cfg.h"

#include "../Debug/DebugHandler.h"

double FoldPhi(double phi);

// CHUNK = which chunk of root-files to run over
// NJOBS = number of jobs to submit
void makeJetXvsY(const int & CHUNK, const int & NJOBS, const int & NENT, const bool & COMBINE)
{
    // Check CHUNK < NJOBS
    DebugHandler::ErrorCheck(CHUNK >= NJOBS, "The CHUNK number exceeds the number of jobs", __FILE__, __LINE__);

    // Set ROOT style
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Get config objects
    ntuple_cfg * dataset = new ntuple_cfg(GetNtuple_cfg());
    std::map< std::string, TL1XvsY* > xvsys = jetXvsYs(dataset);

    std::vector<std::string> inDir = dataset->inFiles;
    std::string outDir( dataset->outDir+"_hadd/XvsYJets/" );
    if(!COMBINE) outDir = dataset->outDir + Form("_CHUNK%i/XvsYJets/",CHUNK);
    else inDir.clear();
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
    start = 220025;
    end = 220027;
    for(int i=start; i<end && !COMBINE; ++i)
    {
        event->GetEntry(i);
        TL1Progress::PrintProgressBar(i-start, end-start);

        // Skip events that don't meet the selection criteria
        //if( !event->fIsLeadingRecoJet ) continue;
        //if( !event->fIsMatchedL1Jet ) continue;

        // Get the relevant event parameters
        int pu = event->GetPEvent()->fVertex->nVtx;
        auto jets = event->GetPEvent()->fJets;
        auto muons = event->GetPEvent()->fMuons;

        //double recoEt = jets->etCorr[event->fLeadingRecoJetIndex];
        //double recoEta = jets->eta[event->fLeadingRecoJetIndex];
        //double recoPhi = jets->phi[event->fLeadingRecoJetIndex];

        //double l1Et = event->fL1JetEt[event->fMatchedL1JetIndex];
        //double l1Eta = event->fL1JetEta[event->fMatchedL1JetIndex];
        //double l1Phi = event->fL1JetPhi[event->fMatchedL1JetIndex];
        
        auto recoEts = jets->etCorr;
        auto recoEtas = jets->eta;
        auto recoPhis = jets->phi;
        auto recoMEFs = jets->mef;
        auto recoMMults = jets->muMult;
        auto l1Ets = event->fL1JetEt;
        auto l1Etas = event->fL1JetEta;
        auto l1Phis = event->fL1JetPhi;

        auto recoMuEt = muons->et;
        auto recoMuEta = muons->eta;
        auto recoMuPhi = muons->phi;

        double l1Ht = event->fL1Htt;
        double recoHt = event->GetPEvent()->fSums->Ht;

        if( recoHt > 1500. && l1Ht < 500 )
        {
            cout << "event " << i << endl;
            cout << "recoHt = " << recoHt << "\tl1Ht = " << l1Ht << endl;
            for(int j=0; j<recoEts.size(); ++j)
            {
                cout << "\treco jet " << j << ":";
                cout << "\trecoJetEt = "  << recoEts[j];
                cout << "\trecoJetEta = " << recoEtas[j];
                cout << "\trecoJetPhi = " << recoPhis[j];
                cout << "\trecoMEFs = "   << recoMEFs[j];
                cout << "\trecoMMult = "  << recoMMults[j] << endl;
            }
            for(int k=0; k<l1Ets.size(); ++k)
            {
                cout << "\tl1 jet " << k << ":";
                cout << "\tl1JetEt = "  << l1Ets[k];
                cout << "\tl1JetEta = " << l1Etas[k];
                cout << "\tl1JetPhi = " << l1Phis[k] << endl;
            }
            for(int l=0; l<recoMuEt.size(); ++l)
            {
                cout << "\treco Mu " << l << ":";
                cout << "\trecoMuEt = " << recoMuEt[l];
                cout << "\trecoMuEta = " << recoMuEta[l];
                cout << "\trecoMuPhi = " << recoMuPhi[l] << endl;
            }
        }

        // Fill xvsy with event parameters. Includes fill logic (e.g. different eta ranges)
        //if( xvsys.find("recoL1JetEta") != xvsys.end() )
        //    xvsys["recoL1JetEta"]->Fill(recoEta, l1Eta, pu);

        //if( xvsys.find("recoJetEtEta") != xvsys.end() &&
        //        recoHt > 1000. &&
        //        l1Ht < 100. )
        //    xvsys["recoJetEtEta"]->Fill(recoEt, recoEta, pu);
        //if( xvsys.find("l1JetEtEta") != xvsys.end() &&
        //        recoHt > 1000. &&
        //        l1Ht < 100. )
        //    xvsys["l1JetEtEta"]->Fill(l1Et, l1Eta, pu);

        //if( abs(recoEta) <= 1.479 )
        //{
        //    // Jet Et
        //    if( xvsys.find("recoL1JetEtB") != xvsys.end() )
        //        xvsys["recoL1JetEtB"]->Fill(recoEt, l1Et, pu);
        //    if( xvsys.find("recoL1JetEtBE") != xvsys.end() )
        //        xvsys["recoL1JetEtBE"]->Fill(recoEt, l1Et, pu);

        //    // Jet Phi
        //    if( xvsys.find("recoL1JetPhiB") != xvsys.end() )
        //        xvsys["recoL1JetPhiB"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        //    if( xvsys.find("recoL1JetPhiBE") != xvsys.end() )
        //        xvsys["recoL1JetPhiBE"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        //}
        //else if( abs(recoEta) <= 3.0 )
        //{
        //    // Jet Et
        //    if( xvsys.find("recoL1JetEtE") != xvsys.end() )
        //        xvsys["recoL1JetEtE"]->Fill(recoEt, l1Et, pu);
        //    if( xvsys.find("recoL1JetEtBE") != xvsys.end() )
        //        xvsys["recoL1JetEtBE"]->Fill(recoEt, l1Et, pu);

        //    // Jet Phi
        //    if( xvsys.find("recoL1JetPhiE") != xvsys.end() )
        //        xvsys["recoL1JetPhiE"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        //    if( xvsys.find("recoL1JetPhiBE") != xvsys.end() )
        //        xvsys["recoL1JetPhiBE"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        //}
        //else
        //{
        //    // Jet Et
        //    if( xvsys.find("recoL1JetEtHF") != xvsys.end() )
        //        xvsys["recoL1JetEtHF"]->Fill(recoEt, l1Et, pu);

        //    // Jet Phi
        //    if( xvsys.find("recoL1JetPhiHF") != xvsys.end() )
        //        xvsys["recoL1JetPhiHF"]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
        //}
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
