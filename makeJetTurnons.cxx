#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1Turnon.h"

vector<double> bins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeJetTurnons()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";

    std::string run = "2016B_v1";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    bool doFit = false;
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1";
    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0";
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1Turnon*> turnons;

    // Jet Et - barrel
    turnons.emplace_back(new TL1Turnon());
    std::string outDir = outDirBase+"/"+turnons.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/TurnonsJets/";
    turnons[0]->SetSeeds({0., 36., 68., 128., 200.});
    turnons[0]->SetXBins(bins());
    turnons[0]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    turnons[0]->SetSeed("l1JetEt","L1 Jet E_{T}");
    turnons[0]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_barrel");
    turnons[0]->SetFit(doFit);
    turnons[0]->SetAddMark("|#eta| < 1.479");

    // Jet Et - end cap
    turnons.emplace_back(new TL1Turnon());
    turnons[1]->SetSeeds({0., 36., 68., 128., 200.});
    turnons[1]->SetXBins(bins());
    turnons[1]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    turnons[1]->SetSeed("l1JetEt","L1 Jet E_{T}");
    turnons[1]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_endcap");
    turnons[1]->SetFit(doFit);
    turnons[1]->SetAddMark("1.479 < |#eta| < 3.0");

    // Jet Et - barrel + endcap
    turnons.emplace_back(new TL1Turnon());
    turnons[2]->SetSeeds({0., 36., 68., 128., 200.});
    turnons[2]->SetXBins(bins());
    turnons[2]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    turnons[2]->SetSeed("l1JetEt","L1 Jet E_{T}");
    turnons[2]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_barrel-endcap");
    turnons[2]->SetFit(doFit);
    turnons[2]->SetAddMark("|#eta| < 3.0");

    // Jet Et - HF
    turnons.emplace_back(new TL1Turnon());
    turnons[3]->SetSeeds({0., 36., 68., 128., 176.});
    turnons[3]->SetXBins(bins());
    turnons[3]->SetX("recoJetEt","Offline Jet E_{T} (GeV)");
    turnons[3]->SetSeed("l1JetEt","L1 Jet E_{T}");
    turnons[3]->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_hf");
    turnons[3]->SetFit(doFit);
    turnons[3]->SetAddMark("|#eta| > 3.0");

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        (*it)->SetSample(sample,"");
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(run);
        (*it)->SetOutDir(outDir);
        (*it)->SetPuType(puType);
        (*it)->SetPuBins(puBins);
        (*it)->InitPlots();
    }

    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        if( !event->fIsLeadingRecoJet ) continue;
        if( !event->fIsMatchedL1Jet ) continue;

        int pu = event->GetPEvent()->fVertex->nVtx;

        auto recoJet = event->GetPEvent()->fJets;
        double recoEt = recoJet->etCorr[event->fLeadingRecoJetIndex];
        double recoEta = recoJet->eta[event->fLeadingRecoJetIndex];
        double recoPhi = recoJet->phi[event->fLeadingRecoJetIndex];

        double l1Et = event->fL1JetEt[event->fMatchedL1JetIndex];
        double l1Eta = event->fL1JetEta[event->fMatchedL1JetIndex];
        double l1Phi = event->fL1JetPhi[event->fMatchedL1JetIndex];

        if( abs(recoEta) <= 1.479 )
        {
            turnons[0]->Fill(recoEt, l1Et, pu);
            turnons[2]->Fill(recoEt, l1Et, pu);
        }
        else if( abs(recoEta) <= 3.0 )
        {
            turnons[1]->Fill(recoEt, l1Et, pu);
            turnons[2]->Fill(recoEt, l1Et, pu);
        }
        else
            turnons[3]->Fill(recoEt, l1Et, pu);
    }

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        (*it)->DrawPlots();
        (*it)->DrawTurnons();
    }
}

vector<double> bins()
{
    vector<double> temp;
    for(double binLowerEdge= 0.0; binLowerEdge< 120.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=120.0; binLowerEdge< 180.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=180.0; binLowerEdge< 300.0; binLowerEdge+=40.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge< 400.1; binLowerEdge+=100.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 2.5) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 70.0; binLowerEdge<200.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=200.0; binLowerEdge<300.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=300.0; binLowerEdge<400.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    return temp;
}

void SetMyStyle(int palette, double rmarg, TStyle * myStyle)
{
    myStyle->SetCanvasDefW(800);
    myStyle->SetCanvasDefH(600);
    myStyle->SetNumberContours(255);
    myStyle->SetPalette(palette);
    myStyle->SetPadRightMargin(rmarg);
    myStyle->cd();
}
