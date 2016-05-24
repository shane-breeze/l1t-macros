#include <string>
#include <vector>
#include <algorithm>

#include "TL1EventClass.h"
#include "TL1XvsY.h"

vector<double> bins(double max);
vector<double> phiBins();
double phiSwap(double xPhi, double yPhi);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void testTL1XvsY()
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

    // caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[0]->SetSample(sample,"");
    xvsy[0]->SetTrigger(triggerName,triggerTitle);
    xvsy[0]->SetRun(run);
    xvsy[0]->SetXBins(bins(200.0));
    xvsy[0]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    xvsy[0]->SetYBins(bins(200.0));
    xvsy[0]->SetY("l1met","L1 E_{T}^{miss} (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1Met");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetSample(sample,"");
    xvsy[1]->SetTrigger(triggerName,triggerTitle);
    xvsy[1]->SetRun(run);
    xvsy[1]->SetXBins(bins(200.0));
    xvsy[1]->SetX("mht","H_{T}^{miss} (GeV)");
    xvsy[1]->SetYBins(bins(200.0));
    xvsy[1]->SetY("l1htt","L1 H_{T}^{miss}");
    xvsy[1]->SetOutName(triggerName+"_recalcMht_vs_l1Mht");

    // caloEttBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetSample(sample,"");
    xvsy[2]->SetTrigger(triggerName,triggerTitle);
    xvsy[2]->SetRun(run);
    xvsy[2]->SetXBins(bins(600.0));
    xvsy[2]->SetX("caloEttBE","Total Calo E_{T} no HF (GeV)");
    xvsy[2]->SetYBins(bins(600.0));
    xvsy[2]->SetY("l1ett","L1 Total E_{T}");
    xvsy[2]->SetOutName(triggerName+"_caloEttBE_vs_l1Ett");

    // htt
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetSample(sample,"");
    xvsy[3]->SetTrigger(triggerName,triggerTitle);
    xvsy[3]->SetRun(run);
    xvsy[3]->SetXBins(bins(600.0));
    xvsy[3]->SetX("htt","Total H_{T} (GeV)");
    xvsy[3]->SetYBins(bins(600.0));
    xvsy[3]->SetY("l1htt","L1 Total H_{T}");
    xvsy[3]->SetOutName(triggerName+"_htt_vs_l1Htt");
    
    // caloMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetSample(sample,"");
    xvsy[4]->SetTrigger(triggerName,triggerTitle);
    xvsy[4]->SetRun(run);
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    xvsy[4]->SetOutName(triggerName+"_caloMetBEPhi_vs_l1MetPhi");

    // mht Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetSample(sample,"");
    xvsy[5]->SetTrigger(triggerName,triggerTitle);
    xvsy[5]->SetRun(run);
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("mhtPhi","H_{T}^{miss} Phi");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1httphi","L1 H_{T}^{miss} Phi");
    xvsy[5]->SetOutName(triggerName+"_recalcMhtPhi_vs_l1MhtPhi");


    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->InitPlots();

    while( event->Next() )
    {
        //----- Filters -----//
        // Muon loop
        bool passMuonFilter = event->MuonFilter();

        // Sums
        bool passSumsFilter = event->SumsFilter();
        //-------------------//

        event->GetL1Variables();
        xvsy[3]->Fill(event->fSums->Ht, event->fL1Htt);
        //xvsy[3]->Fill(recalcHtt, event->fL1Htt);
        
        if( !passMuonFilter ) continue;

        event->RecalculateVariables();
        double recalcMht = event->fRecalcMht;
        double recalcMhtPhi = event->fRecalcMhtPhi;
        double recalcHtt = event->fRecalcHtt;
        
        if( passSumsFilter )
            xvsy[0]->Fill(event->fSums->caloMetBE, event->fL1Met);
        //xvsy[1]->Fill(event->fSums->mHt, event->fL1Mht);
        xvsy[1]->Fill(recalcMht, event->fL1Mht);
        xvsy[2]->Fill(event->fSums->caloSumEtBE, event->fL1Ett);

        double xPhiMet = min( (float)abs(event->fSums->caloMetPhiBE), (float)abs(2*TMath::Pi()-event->fSums->caloMetPhiBE) );
        double yPhiMet = min( (float)abs(event->fL1MetPhi), (float)abs(2*TMath::Pi()-event->fL1MetPhi) );

        xvsy[4]->Fill(xPhiMet,yPhiMet);

        double tXPhiMht = recalcMhtPhi;
        double tYPhiMht = event->fL1MhtPhi;
        //if( tXPhi > TMath::Pi() ) tXPhi -= 2*TMath::Pi();
        double xPhiMht = min( (float)abs(tXPhiMht), (float)abs(2*TMath::Pi()-tXPhiMht) );
        double yPhiMht = min( (float)abs(tYPhiMht), (float)abs(2*TMath::Pi()-tYPhiMht) );

        if( recalcMht > 0.1 && event->fL1Mht > 0.1 ) xvsy[5]->Fill(xPhiMht,yPhiMht);
        // xvsy[5]->Fill(recalcMhtPhi, event->fL1MhtPhi);
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

double phiSwap(double xPhi, double yPhi)
{
    if( abs(yPhi-xPhi)<abs(yPhi+xPhi) ) return 1.0;
    else return -1.0;
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
