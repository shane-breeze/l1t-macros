#include <string>
#include <vector>
#include <algorithm>

#include "Core/TL1EventClass.h"
#include "TL1XvsY.h"

struct JetMatch
{
    double l1JetEt, recoJetEt;
    double l1JetEta, recoJetEta;
    double l1JetPhi, recoJetPhi;
};

vector<double> bins(double max);
vector<double> phiBins();
double FoldPhi(double phi);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
bool GetMatch(TL1EventClass * event, unsigned iRecoJet, JetMatch & match);

void testTL1XvsYJets()
{
    std::shared_ptr<TStyle> myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle.get());

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string run = "273301";
    bool doFit = true;

    std::shared_ptr<TFile> rootFile(new TFile(Form("%s_%s_r%s.root",sample.c_str(),triggerName.c_str(),run.c_str()), "UPDATE"));

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1XvsY>> xvsy;

    // Jet Et - barrel
    xvsy.emplace_back(new TL1XvsY());
    xvsy[0]->SetSample(sample,"");
    xvsy[0]->SetTrigger(triggerName,triggerTitle);
    xvsy[0]->SetRun(run);
    xvsy[0]->SetXBins(bins(300.0));
    xvsy[0]->SetX("jetEt","Reco Jet E_{T} (GeV)");
    xvsy[0]->SetYBins(bins(300.0));
    xvsy[0]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    xvsy[0]->SetOutName(triggerName+"_jetEt_vs_l1JetEt_barrel");

    // Jet Et - end-cap
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetSample(sample,"");
    xvsy[1]->SetTrigger(triggerName,triggerTitle);
    xvsy[1]->SetRun(run);
    xvsy[1]->SetXBins(bins(300.0));
    xvsy[1]->SetX("jetEt","Reco Jet E_{T} (GeV)");
    xvsy[1]->SetYBins(bins(300.0));
    xvsy[1]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    xvsy[1]->SetOutName(triggerName+"_jetEt_vs_l1JetEt_endcap");

    // Jet Et - hf
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetSample(sample,"");
    xvsy[2]->SetTrigger(triggerName,triggerTitle);
    xvsy[2]->SetRun(run);
    xvsy[2]->SetXBins(bins(300.0));
    xvsy[2]->SetX("jetEt","Reco Jet E_{T} (GeV)");
    xvsy[2]->SetYBins(bins(300.0));
    xvsy[2]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    xvsy[2]->SetOutName(triggerName+"_jetEt_vs_l1JetEt_hf");

    // Jet phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetSample(sample,"");
    xvsy[3]->SetTrigger(triggerName,triggerTitle);
    xvsy[3]->SetRun(run);
    xvsy[3]->SetXBins(phiBins());
    xvsy[3]->SetX("jetPhi","Reco Jet Phi");
    xvsy[3]->SetYBins(phiBins());
    xvsy[3]->SetY("l1JetPhi","L1 Jet Phi");
    xvsy[3]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi_barrel");

    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetSample(sample,"");
    xvsy[4]->SetTrigger(triggerName,triggerTitle);
    xvsy[4]->SetRun(run);
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("jetPhi","Reco Jet Phi");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1JetPhi","L1 Jet Phi");
    xvsy[4]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi_endcap");

    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetSample(sample,"");
    xvsy[5]->SetTrigger(triggerName,triggerTitle);
    xvsy[5]->SetRun(run);
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("jetPhi","Reco Jet Phi");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1JetPhi","L1 Jet Phi");
    xvsy[5]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi_hf");


    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->InitPlots();

    while( event->Next() )
    {
        for(unsigned iRecoJet=0; iRecoJet<event->GetPEvent()->fJets->nJets; ++iRecoJet)
        {
            // Match reco jet with l1 jet
            JetMatch match;
            if( !GetMatch(event->GetPEvent(), iRecoJet, match) ) continue;

            if( abs(match.recoJetEta) >= 3.0 )
            {
                xvsy[2]->Fill(match.recoJetEt, match.l1JetEt);
                xvsy[5]->Fill(FoldPhi(match.recoJetPhi), FoldPhi(match.l1JetPhi));
            }

            // Jet filter (tight lepton veto and zero muon multiplicity)
            if( !event->fJetFilterPassFlag[iRecoJet] ) continue;

            if( abs(match.recoJetEta) < 1.3 )
            {
                xvsy[0]->Fill(match.recoJetEt, match.l1JetEt);
                xvsy[3]->Fill(FoldPhi(match.recoJetPhi), FoldPhi(match.l1JetPhi));
            }
            else if( abs(match.recoJetEta) < 3.0 )
            {
                xvsy[1]->Fill(match.recoJetEt, match.l1JetEt);
                xvsy[4]->Fill(FoldPhi(match.recoJetPhi), FoldPhi(match.l1JetPhi));
            }
        }
    }

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->DrawPlots();

    rootFile->Close();
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

bool GetMatch(TL1EventClass * event, unsigned iRecoJet, JetMatch & match)
{
    double recoJetEt = event->fJets->etCorr[iRecoJet];
    double recoJetEta = event->fJets->eta[iRecoJet];
    double recoJetPhi = event->fJets->phi[iRecoJet];
    double minDeltaR = 0.4;
    unsigned iMinL1Jet = 0;
    for(unsigned iL1Jet=0; iL1Jet<event->fL1JetEt.size(); ++iL1Jet)
    {
        double l1JetEt = event->fL1JetEt[iL1Jet];
        double l1JetEta = event->fL1JetEta[iL1Jet];
        double l1JetPhi = event->fL1JetPhi[iL1Jet];
        double deltaR = TMath::Sqrt((l1JetEta-recoJetEta)*(l1JetEta-recoJetEta) + (l1JetPhi-recoJetPhi)*(l1JetPhi-recoJetPhi));
        if( deltaR < minDeltaR )
        {
            minDeltaR = deltaR;
            iMinL1Jet = iL1Jet;
        }
    }
    if( minDeltaR < 0.4 )
    {
        match.l1JetEt = event->fL1JetEt[iMinL1Jet];
        match.l1JetEta = event->fL1JetEta[iMinL1Jet];
        match.l1JetPhi = event->fL1JetPhi[iMinL1Jet];
        match.recoJetEt = recoJetEt;
        match.recoJetEta = recoJetEta;
        match.recoJetPhi = recoJetPhi;
        return true;
    }
    return false;
}
