#include <string>
#include <vector>
#include <algorithm>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1XvsY.h"

vector<double> bins(double max);
vector<double> phiBins();
vector<double> etaBins();
double FoldPhi(double phi);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeJetXvsY()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";

    std::string run = "6.3fb^{-1}"; // an additional label for the plots
    std::string outDirBase = "/users/jt15104/l1t-macros/l1t-macros-Output/";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    std::vector<std::string> inDir;
    // inDir.push_back("/hdfs/user/jt15104/copiesFromEOS/singleMuon2016_v70p1/run276242/");
    // inDir.push_back("/hdfs/user/jt15104/copiesFromEOS/singleMuon2016_v70p1/run276243/");
    inDir.push_back("/hdfs/user/jt15104/copiesFromEOS/singleMuon2016_v70p1/run276315/");
    // inDir.push_back("");             
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1XvsY*> xvsy;

    // Jet Et - barrel
    // xvsy.emplace_back(new TL1XvsY());
    // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/xyJets/";
    // xvsy[0]->SetXBins(bins(300.0));
    // xvsy[0]->SetX("jetEt","Offline Jet E_{T} (GeV)");
    // xvsy[0]->SetYBins(bins(300.0));
    // xvsy[0]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    // xvsy[0]->SetOutName(triggerName+"_jetEt_vs_l1JetEt_barrel");
    // xvsy[0]->SetAddMark("|#eta| < 1.479");

    // Jet Et - end-cap
    // xvsy.emplace_back(new TL1XvsY());
    // xvsy[1]->SetXBins(bins(300.0));
    // xvsy[1]->SetX("jetEt","Offline Jet E_{T} (GeV)");
    // xvsy[1]->SetYBins(bins(300.0));
    // xvsy[1]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    // xvsy[1]->SetOutName(triggerName+"_jetEt_vs_l1JetEt_endcap");
    // xvsy[1]->SetAddMark("1.479 < |#eta| < 3.0");
    
    // Jet Et - barrel end-cap
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(bins(300.0));
    xvsy[2]->SetX("jetEt","Offline Jet E_{T} (GeV)");
    xvsy[2]->SetYBins(bins(300.0));
    xvsy[2]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    xvsy[2]->SetOutName(triggerName+"_jetEt_vs_l1JetEt_barrel-endcap");
    xvsy[2]->SetAddMark("|#eta| < 3.0");

    // Jet Et - HF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(bins(300.0));
    xvsy[3]->SetX("jetEt","Offline Jet E_{T} (GeV)");
    xvsy[3]->SetYBins(bins(300.0));
    xvsy[3]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    xvsy[3]->SetOutName(triggerName+"_jetEt_vs_l1JetEt_hf");
    xvsy[3]->SetAddMark("|#eta| > 3.0");

    // Jet phi - barrel
    // xvsy.emplace_back(new TL1XvsY());
    // xvsy[4]->SetXBins(phiBins());
    // xvsy[4]->SetX("jetPhi","Offline Jet Phi");
    // xvsy[4]->SetYBins(phiBins());
    // xvsy[4]->SetY("l1JetPhi","L1 Jet Phi");
    // xvsy[4]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi_barrel");
    // xvsy[4]->SetAddMark("|#eta| < 1.479");

    // Jet Phi - endcap
    // xvsy.emplace_back(new TL1XvsY());
    // xvsy[5]->SetXBins(phiBins());
    // xvsy[5]->SetX("jetPhi","Offline Jet Phi");
    // xvsy[5]->SetYBins(phiBins());
    // xvsy[5]->SetY("l1JetPhi","L1 Jet Phi");
    // xvsy[5]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi_endcap");
    // xvsy[5]->SetAddMark("1.479 < |#eta| < 3.0");

    // Jet Phi - barrel endcap
    xvsy.emplace_back(new TL1XvsY());
    xvsy[6]->SetXBins(phiBins());
    xvsy[6]->SetX("jetPhi","Offline Jet Phi");
    xvsy[6]->SetYBins(phiBins());
    xvsy[6]->SetY("l1JetPhi","L1 Jet Phi");
    xvsy[6]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi_barrel-endcap");
    xvsy[6]->SetAddMark("|#eta| < 3.0");

    // Jet Phi - HF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[7]->SetXBins(phiBins());
    xvsy[7]->SetX("jetPhi","Offline Jet Phi");
    xvsy[7]->SetYBins(phiBins());
    xvsy[7]->SetY("l1JetPhi","L1 Jet Phi");
    xvsy[7]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi_hf");
    xvsy[7]->SetAddMark("|#eta| > 3.0");

    // Jet Eta
    xvsy.emplace_back(new TL1XvsY());
    xvsy[8]->SetXBins(etaBins());
    xvsy[8]->SetX("jetEta","Offline Jet Eta");
    xvsy[8]->SetYBins(etaBins());
    xvsy[8]->SetY("l1JetEta","L1 Jet Eta");
    xvsy[8]->SetOutName(triggerName+"_jetEta_vs_l1JetEta_hf");

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
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

        int pu = event->GetPEvent()->fVertex->nVtx;
        auto jets = event->GetPEvent()->fJets;

        for(unsigned iRecoJet=0; iRecoJet<jets->nJets; ++iRecoJet)
        {
            if( !event->fIsLeadingRecoJet ) continue;
            if( !event->fIsMatchedL1Jet ) continue;

            int pu = event->GetPEvent()->fVertex->nVtx;

            double recoEt = jets->etCorr[event->fLeadingRecoJetIndex];
            double recoEta = jets->eta[event->fLeadingRecoJetIndex];
            double recoPhi = jets->phi[event->fLeadingRecoJetIndex];

            double l1Et = event->fL1JetEt[event->fMatchedL1JetIndex];
            double l1Eta = event->fL1JetEta[event->fMatchedL1JetIndex];
            double l1Phi = event->fL1JetPhi[event->fMatchedL1JetIndex];
            if( abs(recoEta) <= 1.479 )
            {
                xvsy[0]->Fill(recoEt, l1Et, pu);
                xvsy[2]->Fill(recoEt, l1Et, pu);

                xvsy[4]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
                xvsy[6]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);

                xvsy[8]->Fill(recoEta, l1Eta, pu);
            }
            else if( abs(recoEta) <= 3.0 )
            {
                xvsy[1]->Fill(recoEt, l1Et, pu);
                xvsy[2]->Fill(recoEt, l1Et, pu);

                xvsy[5]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
                xvsy[6]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);

                xvsy[8]->Fill(recoEta, l1Eta, pu);
            }
            else
            {
                xvsy[3]->Fill(recoEt, l1Et, pu);
                xvsy[7]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi), pu);
                xvsy[8]->Fill(recoEta, l1Eta, pu);
            }
        }
    }

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->DrawPlots();
}

vector<double> bins(double max)
{
    vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=max; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> phiBins()
{
    vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=TMath::Pi(); binLowerEdge+= (TMath::Pi())/36.) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> etaBins()
{
    vector<double> temp;
    for(double binLowerEdge=-5.0; binLowerEdge<=5.0; binLowerEdge+= 0.1) temp.push_back(binLowerEdge);
    return temp;
}

double FoldPhi(double phi)
{
    return min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
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
