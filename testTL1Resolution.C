#include <string>
#include <vector>

#include "Core/tdrstyle.C"
#include "Core/TL1EventClass.h"
#include "Core/TL1Progress.C"
#include "TL1Resolution.h"

std::vector<double> bins();
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
    //std::string run = "273450";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1Resolution>> resolution;

    // caloMetBE
    resolution.emplace_back(new TL1Resolution());
    std::string outDir = outDirBase+"/"+resolution.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/Resolutions/";
    resolution[0]->SetBins(bins());
    resolution[0]->SetX("caloMetBE","Calo E_{T}^{miss} no HF");
    resolution[0]->SetY("l1met","L1 E_{T}^{miss}");
    resolution[0]->SetOutName(triggerName+"_caloMetBE_over_l1Met");

    // mht
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetBins(bins());
    resolution[1]->SetX("mht","H_{T}^{miss}");
    resolution[1]->SetY("l1mht","L1 H_{T}^{miss}");
    resolution[1]->SetOutName(triggerName+"_recalcMht_over_l1Mht");

    // caloEttBE
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetBins(bins());
    resolution[2]->SetX("caloEttBE","Total Calo E_{T} no HF");
    resolution[2]->SetY("l1ett","L1 Total E_{T}");
    resolution[2]->SetOutName(triggerName+"_caloEttBE_over_l1Ett");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetBins(bins());
    resolution[3]->SetX("htt","Total H_{T}");
    resolution[3]->SetY("l1htt","L1 Total H_{T}");
    resolution[3]->SetOutName(triggerName+"_htt_over_l1Htt");

    // caloMetBE Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[4]->SetBins(bins());
    resolution[4]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    resolution[4]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[4]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[5]->SetBins(bins());
    resolution[5]->SetX("mhtPhi","H_{T}^{miss} Phi");
    resolution[5]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[5]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi");

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
    {
        (*it)->SetSample(sample,"");
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(run);
        (*it)->SetOutDir(outDir);
        (*it)->InitPlots();
    }
    
    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        int pu = event->GetPEvent()->fVertex->nVtx;

        // HTT
        double recoHtt = event->GetPEvent()->fSums->Ht;
        double l1Htt = event->fL1Htt;
        if( recoHtt > 100.0 && l1Htt > 0.02 )
            resolution[3]->Fill(recoHtt, l1Htt, pu);

        // MHT
        double recalcRecoMht = event->fRecalcRecoMht;
        double l1Mht = event->fL1Mht;
        if( recalcRecoMht > 0.2 && l1Mht > 0.2 )
            resolution[1]->Fill(recalcRecoMht, l1Mht, pu);

        // MHT Phi
        double recoMhtPhi = event->GetPEvent()->fSums->mHtPhi;
        double l1MhtPhi = event->fL1MhtPhi;
        if( event->GetPEvent()->fSums->mHt != 0.0 && l1Mht != 0.0 )
            resolution[5]->Fill(FoldPhi(recoMhtPhi), FoldPhi(l1MhtPhi), pu);

        // ETT
        double recoEtt = event->GetPEvent()->fSums->caloSumEtBE;
        double l1Ett = event->fL1Ett;
        if( recoEtt != 0.0 && l1Ett != 0.0 )
            resolution[2]->Fill(recoEtt, l1Ett, pu);

        if( !event->fMuonFilterPassFlag ) continue;

        // MET
        double recoMet = event->GetPEvent()->fSums->caloMetBE;
        double l1Met = event->fL1Met;
        if( event->fMetFilterPassFlag )
        {
            if( recoMet > 40.0 && l1Met != 0.0 )
                resolution[0]->Fill(recoMet, l1Met, pu);
        }

        // MET Phi
        double recoMetPhi = event->GetPEvent()->fSums->caloMetPhiBE;
        double l1MetPhi = event->fL1MetPhi;
        if( recoMet != 0.0 && l1Met != 0.0 )
            resolution[4]->Fill(FoldPhi(recoMetPhi), FoldPhi(l1MetPhi), pu);

    }

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
        (*it)->DrawPlots();
}

std::vector<double> bins()
{
    std::vector<double> temp;
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
    return TMath::Min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
}
