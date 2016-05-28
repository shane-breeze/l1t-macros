#include <string>
#include <vector>

#include "Core/tdrstyle.C"
#include "Core/TL1EventClass.h"
#include "TL1Resolution.h"

vector<double> bins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void testTL1Resolution()
{
    std::shared_ptr<TStyle> myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle.get());

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string run = "273301";
    bool doFit = true;

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1Resolution>> resolution;

    // caloMetBE
    resolution.emplace_back(new TL1Resolution());
    resolution[0]->SetSample(sample,"");
    resolution[0]->SetTrigger(triggerName,triggerTitle);
    resolution[0]->SetRun(run);
    resolution[0]->SetBins(bins());
    resolution[0]->SetX("caloMetBE","Calo E_{T}^{miss} no HF");
    resolution[0]->SetY("l1met","L1 E_{T}^{miss}");
    resolution[0]->SetOutName(triggerName+"_caloMetBE_over_l1Met");

    // mht
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetSample(sample,"");
    resolution[1]->SetTrigger(triggerName,triggerTitle);
    resolution[1]->SetRun(run);
    resolution[1]->SetBins(bins());
    resolution[1]->SetX("mht","H_{T}^{miss}");
    resolution[1]->SetY("l1mht","L1 H_{T}^{miss}");
    resolution[1]->SetOutName(triggerName+"_recalcMht_over_l1Mht");

    // caloEttBE
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetSample(sample,"");
    resolution[2]->SetTrigger(triggerName,triggerTitle);
    resolution[2]->SetRun(run);
    resolution[2]->SetBins(bins());
    resolution[2]->SetX("caloEttBE","Total Calo E_{T} no HF");
    resolution[2]->SetY("l1ett","L1 Total E_{T}");
    resolution[2]->SetOutName(triggerName+"_caloEttBE_over_l1Ett");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetSample(sample,"");
    resolution[3]->SetTrigger(triggerName,triggerTitle);
    resolution[3]->SetRun(run);
    resolution[3]->SetBins(bins());
    resolution[3]->SetX("htt","Total H_{T}");
    resolution[3]->SetY("l1htt","L1 Total H_{T}");
    resolution[3]->SetOutName(triggerName+"_htt_over_l1Htt");

    // caloMetBE Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[4]->SetSample(sample,"");
    resolution[4]->SetTrigger(triggerName,triggerTitle);
    resolution[4]->SetRun(run);
    resolution[4]->SetBins(bins());
    resolution[4]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    resolution[4]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[4]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[5]->SetSample(sample,"");
    resolution[5]->SetTrigger(triggerName,triggerTitle);
    resolution[5]->SetRun(run);
    resolution[5]->SetBins(bins());
    resolution[5]->SetX("mhtPhi","H_{T}^{miss} Phi");
    resolution[5]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[5]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi");


    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
        (*it)->InitPlots();

    while( event->Next() )
    {
        // HTT
        if( event->GetPEvent()->fSums->Ht != 0.0 && event->fL1Htt != 0.0 ) resolution[3]->Fill(event->GetPEvent()->fSums->Ht, event->fL1Htt);
        //resolution[3]->Fill(event->fRecalcRecoHtt, event->fL1Htt);

        // MHT
        //resolution[1]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);
        if( event->fRecalcRecoMht != 0.0 && event->fL1Mht != 0.0 ) resolution[1]->Fill(event->fRecalcRecoMht, event->fL1Mht);


        if( !event->fMuonFilterPassFlag ) continue;
        // MET
        if( event->fMetFilterPassFlag )
            if( event->GetPEvent()->fSums->caloMetBE != 0.0 && event->fL1Met != 0.0 ) resolution[0]->Fill(event->GetPEvent()->fSums->caloMetBE, event->fL1Met);

        // ETT
        if( event->GetPEvent()->fSums->caloSumEtBE != 0.0 && event->fL1Ett != 0.0 ) resolution[2]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett);

        // MET Phi
        resolution[4]->Fill(FoldPhi(event->GetPEvent()->fSums->caloMetPhiBE), FoldPhi(event->fL1MetPhi));

        // MHT Phi
        resolution[5]->Fill(event->GetPEvent()->fSums->mHtPhi, event->fL1MhtPhi);
        //resolution[5]->Fill(event->fRecalcRecoMhtPhi, event->fL1MhtPhi);
    }

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
        (*it)->DrawPlots();
}

vector<double> bins()
{
    vector<double> temp;
    for(double binLowerEdge=-1.0; binLowerEdge<=3.0; binLowerEdge+= 0.02) temp.push_back(binLowerEdge);
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
    return min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
}
