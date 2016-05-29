#include <string>
#include <vector>
#include <algorithm>

#include "Core/TL1EventClass.h"
#include "Core/TL1JetMatch.h"
#include "Core/TL1Progress.C"
#include "TL1XvsY.h"

vector<double> bins(double max);
vector<double> phiBins();
double FoldPhi(double phi);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

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

    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        TL1Progress::PrintProgressBar((float)(event->GetPEvent()->GetPosition()+1)/(float)(NEntries));
        for(unsigned iRecoJet=0; iRecoJet<event->GetPEvent()->fJets->nJets; ++iRecoJet)
        {
            std::shared_ptr<TL1JetMatch> jetMatch(new TL1JetMatch(0, iRecoJet));
            if( !event->GetMatchedJet(jetMatch.get()) ) continue;

            unsigned iL1Jet = jetMatch->GetIL1();
            double l1Et = event->fL1JetEt[iL1Jet];
            double l1Eta = event->fL1JetEta[iL1Jet];
            double l1Phi = event->fL1JetPhi[iL1Jet];
            
            double recoEt = event->GetPEvent()->fJets->etCorr[iRecoJet];
            double recoEta = event->GetPEvent()->fJets->eta[iRecoJet];
            double recoPhi = event->GetPEvent()->fJets->phi[iRecoJet];

            if( abs(recoEta) >= 3.0 )
            {
                xvsy[2]->Fill(recoEt, l1Et);
                xvsy[5]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi));
            }

            // Jet filter (tight lepton veto and zero muon multiplicity)
            if( !event->fJetFilterPassFlags[iRecoJet] ) continue;

            if( abs(recoEta) < 1.3 )
            {
                xvsy[0]->Fill(recoEt, l1Et);
                xvsy[3]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi));
            }
            else if( abs(recoEta) < 3.0 )
            {
                xvsy[1]->Fill(recoEt, l1Et);
                xvsy[4]->Fill(FoldPhi(recoPhi), FoldPhi(l1Phi));
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
