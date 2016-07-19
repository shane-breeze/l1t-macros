#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1Resolution.h"

std::vector<double> bins(std::string plotType);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void makeJetResolutions()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Basic
    std::string sampleName = "Data";
    std::string sampleTitle = "2016 Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string puFilename = "/afs/cern.ch/work/s/sbreeze/l1tClasses/PUWeights/20160719_Data-SingleMu-2016Bv1_VBFHinv/pu_mcReweightedToData.root";

    std::string run = "276243";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160713_r276243_SingleMu_l1t-int-71p1/");
    
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+"/resJets/";
    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1Resolution*> resolution;

    // Jet Et - barrel
    // resolution.emplace_back(new TL1Resolution());
    // resolution[0]->SetBins(bins());
    // resolution[0]->SetX("jetEt","Offline Jet E_{T}");
    // resolution[0]->SetY("l1JetEt","L1 Jet E_{T})");
    // resolution[0]->SetOutName(triggerName+"_jetEt_over_l1JetEt_barrel");
    // resolution[0]->SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| < 1.479}");

    // Jet Et - end-cap
    // resolution.emplace_back(new TL1Resolution());
    // resolution[1]->SetBins(bins());
    // resolution[1]->SetX("jetEt","Offline Jet E_{T}");
    // resolution[1]->SetY("l1JetEt","L1 Jet E_{T}");
    // resolution[1]->SetOutName(triggerName+"_jetEt_over_l1JetEt_endcap");
    // resolution[1]->SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{1.479 < |#eta| < 3.0}");

    // Jet Et - barrel + end-cap
    resolution.emplace_back(new TL1Resolution());
    resolution[0]->SetPlotType("Energy");
    resolution[0]->SetBins(bins("Energy"));
    resolution[0]->SetX("jetEt","Offline Jet E_{T}");
    resolution[0]->SetY("l1JetEt","L1 Jet E_{T}");
    resolution[0]->SetOutName(triggerName+"_jetEt_over_l1JetEt_barrel-endcap");
    resolution[0]->SetAddMark("#splitline{E_{T}^{offline} > 30 GeV}{|#eta_{jet}^{offline}| < 3.0}");

    // Jet Et - HF
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetPlotType("Energy");
    resolution[1]->SetBins(bins("Energy"));
    resolution[1]->SetX("jetEt","Offline Jet E_{T}");
    resolution[1]->SetY("l1JetEt","L1 Jet E_{T}");
    resolution[1]->SetOutName(triggerName+"_jetEt_over_l1JetEt_hf");
    resolution[1]->SetAddMark("#splitline{E_{T}^{offline} > 30 GeV}{|#eta_{jet}^{offline}| > 3.0}");

    // Jet phi - barrel
    // resolution.emplace_back(new TL1Resolution());
    // resolution[4]->SetBins(bins());
    // resolution[4]->SetX("jetPhi","#phi_{jet}^{offline}");
    // resolution[4]->SetY("l1JetPhi","#phi_{jet}^{L1}");
    // resolution[4]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_barrel");
    // resolution[4]->SetAddMark("#splitline{E_{T}^{offline} > 30 GeV}{|#eta| < 1.479}");

    // // Jet Phi - endcap
    // resolution.emplace_back(new TL1Resolution());
    // resolution[5]->SetBins(bins());
    // resolution[5]->SetX("jetPhi","Offline Jet Phi");
    // resolution[5]->SetY("l1JetPhi","L1 Jet Phi");
    // resolution[5]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_endcap");
    // resolution[5]->SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{1.479 < |#eta| < 3.0}");

    // Jet Phi - barrel + endcap
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetPlotType("Position");
    resolution[2]->SetBins(bins("Position"));
    resolution[2]->SetX("jetPhi","#phi_{jet}^{offline}");
    resolution[2]->SetY("l1JetPhi","#phi_{jet}^{L1}");
    resolution[2]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_barrel-endcap");
    resolution[2]->SetAddMark("#splitline{E_{T}^{offline} > 30 GeV}{|#eta_{jet}^{offline}| < 3.0}");

    // Jet Phi - HF
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetPlotType("Position");
    resolution[3]->SetBins(bins("Position"));
    resolution[3]->SetX("jetPhi","#phi_{jet}^{offline}");
    resolution[3]->SetY("l1JetPhi","#phi_{jet}^{L1}");
    resolution[3]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_hf");
    resolution[3]->SetAddMark("#splitline{E_{T}^{offline} > 30 GeV}{|#eta_{jet}^{offline}| > 3.0}");

    // Jet Eta
    resolution.emplace_back(new TL1Resolution());
    resolution[4]->SetPlotType("Position");
    resolution[4]->SetBins(bins("Position"));
    resolution[4]->SetX("jetEta","|#eta_{jet}^{offline}|");
    resolution[4]->SetY("l1JetEta","|#eta_{jet}^{L1}|");
    resolution[4]->SetOutName(triggerName+"_jetEta_over_l1JetEta");
    resolution[4]->SetAddMark("E_{T}^{offline} > 30 GeV");

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
    {
        (*it)->SetSample(sampleName,sampleTitle);
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(run);
        (*it)->SetOutDir(outDir);
        (*it)->SetPuType(puType);
        (*it)->SetPuBins(puBins);
        (*it)->SetPuFileName(puFilename);
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
        double recoPhi = FoldPhi(recoJet->phi[event->fLeadingRecoJetIndex]);

        double l1Et = event->fL1JetEt[event->fMatchedL1JetIndex];
        double l1Eta = event->fL1JetEta[event->fMatchedL1JetIndex];
        double l1Phi = FoldPhi(event->fL1JetPhi[event->fMatchedL1JetIndex]);

        if( abs(recoEta) <= 1.479 )
        {
            //if(recoEt!=0.0 && l1Et!=0.0 && recoEt>=30.0) resolution[0]->Fill(recoEt, l1Et, pu);
            //if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0) resolution[4]->Fill(recoPhi, l1Phi, pu);

            if(recoEta!=0.0 && l1Eta!=0.0 && recoEt>=30.0) resolution[4]->Fill(abs(recoEta), abs(l1Eta), pu);
            if(recoEt>=30.0 && l1Et!=0.0 ) resolution[0]->Fill(recoEt, l1Et, pu);
            if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0) resolution[2]->Fill(recoPhi, l1Phi, pu);
        }
        else if( abs(recoEta) <= 3.0 )
        {
            //if(recoEt!=0.0 && l1Et!=0.0 && recoEt>=30.0) resolution[1]->Fill(recoEt, l1Et, pu);
            //if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0) resolution[5]->Fill(recoPhi, l1Phi, pu);

            if(recoEta!=0.0 && l1Eta!=0.0 && recoEt>=30.0) resolution[4]->Fill(abs(recoEta), abs(l1Eta), pu);
            if(recoEt>=30.0 && l1Et!=0.0 ) resolution[0]->Fill(recoEt, l1Et, pu);
            if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0) resolution[2]->Fill(recoPhi, l1Phi, pu);
        }
        else
        {
            if(recoEt>=30.0 && l1Et!=0.0) resolution[1]->Fill(recoEt, l1Et, pu);
            if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0) resolution[3]->Fill(recoPhi, l1Phi, pu);
            if(recoEta!=0.0 && l1Eta!=0.0 && recoEt>=30.0) resolution[4]->Fill(abs(recoEta), abs(l1Eta), pu);
        }
    }

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
        (*it)->DrawPlots();
}

std::vector<double> bins(std::string plotType)
{
    std::vector<double> temp;
    if( plotType == "Position" ) for(double binLowerEdge=-0.3; binLowerEdge<=0.3; binLowerEdge+= 0.005) temp.push_back(binLowerEdge);
    else if( plotType == "Energy" ) for(double binLowerEdge=-1.0; binLowerEdge<=1.5; binLowerEdge+= 0.05) temp.push_back(binLowerEdge);
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

double FoldPhi(double phi)
{
    return TMath::Min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
}
