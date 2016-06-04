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
    resolution[0]->SetOutName(triggerName+"_caloMetBE_over_l1Met_lowPU");
    resolution[0]->SetAddMark("0PU12");

    // mht
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetBins(bins());
    resolution[1]->SetX("mht","H_{T}^{miss}");
    resolution[1]->SetY("l1mht","L1 H_{T}^{miss}");
    resolution[1]->SetOutName(triggerName+"_recalcMht_over_l1Mht_lowPU");
    resolution[1]->SetAddMark("0PU12");

    // caloEttBE
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetBins(bins());
    resolution[2]->SetX("caloEttBE","Total Calo E_{T} no HF");
    resolution[2]->SetY("l1ett","L1 Total E_{T}");
    resolution[2]->SetOutName(triggerName+"_caloEttBE_over_l1Ett_lowPU");
    resolution[2]->SetAddMark("0PU12");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetBins(bins());
    resolution[3]->SetX("htt","Total H_{T}");
    resolution[3]->SetY("l1htt","L1 Total H_{T}");
    resolution[3]->SetOutName(triggerName+"_htt_over_l1Htt_lowPU");
    resolution[3]->SetAddMark("0PU12");

    // caloMetBE Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[4]->SetBins(bins());
    resolution[4]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    resolution[4]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[4]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi_lowPU");
    resolution[4]->SetAddMark("0PU12");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[5]->SetBins(bins());
    resolution[5]->SetX("mhtPhi","H_{T}^{miss} Phi");
    resolution[5]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[5]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi_lowPU");
    resolution[5]->SetAddMark("0PU12");


    // caloMetBE
    resolution.emplace_back(new TL1Resolution());
    resolution[6]->SetBins(bins());
    resolution[6]->SetX("caloMetBE","Calo E_{T}^{miss} no HF");
    resolution[6]->SetY("l1met","L1 E_{T}^{miss}");
    resolution[6]->SetOutName(triggerName+"_caloMetBE_over_l1Met_medPU");
    resolution[6]->SetAddMark("13PU19");

    // mht
    resolution.emplace_back(new TL1Resolution());
    resolution[7]->SetBins(bins());
    resolution[7]->SetX("mht","H_{T}^{miss}");
    resolution[7]->SetY("l1mht","L1 H_{T}^{miss}");
    resolution[7]->SetOutName(triggerName+"_recalcMht_over_l1Mht_medPU");
    resolution[7]->SetAddMark("13PU19");

    // caloEttBE
    resolution.emplace_back(new TL1Resolution());
    resolution[8]->SetBins(bins());
    resolution[8]->SetX("caloEttBE","Total Calo E_{T} no HF");
    resolution[8]->SetY("l1ett","L1 Total E_{T}");
    resolution[8]->SetOutName(triggerName+"_caloEttBE_over_l1Ett_medPU");
    resolution[8]->SetAddMark("13PU19");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[9]->SetBins(bins());
    resolution[9]->SetX("htt","Total H_{T}");
    resolution[9]->SetY("l1htt","L1 Total H_{T}");
    resolution[9]->SetOutName(triggerName+"_htt_over_l1Htt_medPU");
    resolution[9]->SetAddMark("13PU19");

    // caloMetBE Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[10]->SetBins(bins());
    resolution[10]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    resolution[10]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[10]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi_medPU");
    resolution[10]->SetAddMark("13PU19");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[11]->SetBins(bins());
    resolution[11]->SetX("mhtPhi","H_{T}^{miss} Phi");
    resolution[11]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[11]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi_medPU");
    resolution[11]->SetAddMark("13PU19");

    
    // caloMetBE
    resolution.emplace_back(new TL1Resolution());
    resolution[12]->SetBins(bins());
    resolution[12]->SetX("caloMetBE","Calo E_{T}^{miss} no HF");
    resolution[12]->SetY("l1met","L1 E_{T}^{miss}");
    resolution[12]->SetOutName(triggerName+"_caloMetBE_over_l1Met_highPU");
    resolution[12]->SetAddMark("20PU");

    // mht
    resolution.emplace_back(new TL1Resolution());
    resolution[13]->SetBins(bins());
    resolution[13]->SetX("mht","H_{T}^{miss}");
    resolution[13]->SetY("l1mht","L1 H_{T}^{miss}");
    resolution[13]->SetOutName(triggerName+"_recalcMht_over_l1Mht_highPU");
    resolution[13]->SetAddMark("20PU");

    // caloEttBE
    resolution.emplace_back(new TL1Resolution());
    resolution[14]->SetBins(bins());
    resolution[14]->SetX("caloEttBE","Total Calo E_{T} no HF");
    resolution[14]->SetY("l1ett","L1 Total E_{T}");
    resolution[14]->SetOutName(triggerName+"_caloEttBE_over_l1Ett_highPU");
    resolution[14]->SetAddMark("20PU");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[15]->SetBins(bins());
    resolution[15]->SetX("htt","Total H_{T}");
    resolution[15]->SetY("l1htt","L1 Total H_{T}");
    resolution[15]->SetOutName(triggerName+"_htt_over_l1Htt_highPU");
    resolution[15]->SetAddMark("20PU");

    // caloMetBE Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[16]->SetBins(bins());
    resolution[16]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    resolution[16]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[16]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi_highPU");
    resolution[16]->SetAddMark("20PU");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[17]->SetBins(bins());
    resolution[17]->SetX("mhtPhi","H_{T}^{miss} Phi");
    resolution[17]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[17]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi_highPU");
    resolution[17]->SetAddMark("20PU");


    // caloMetBE
    resolution.emplace_back(new TL1Resolution());
    resolution[18]->SetBins(bins());
    resolution[18]->SetX("caloMetBE","Calo E_{T}^{miss} no HF");
    resolution[18]->SetY("l1met","L1 E_{T}^{miss}");
    resolution[18]->SetOutName(triggerName+"_caloMetBE_over_l1Met");

    // mht
    resolution.emplace_back(new TL1Resolution());
    resolution[19]->SetBins(bins());
    resolution[19]->SetX("mht","H_{T}^{miss}");
    resolution[19]->SetY("l1mht","L1 H_{T}^{miss}");
    resolution[19]->SetOutName(triggerName+"_recalcMht_over_l1Mht");

    // caloEttBE
    resolution.emplace_back(new TL1Resolution());
    resolution[20]->SetBins(bins());
    resolution[20]->SetX("caloEttBE","Total Calo E_{T} no HF");
    resolution[20]->SetY("l1ett","L1 Total E_{T}");
    resolution[20]->SetOutName(triggerName+"_caloEttBE_over_l1Ett");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[21]->SetBins(bins());
    resolution[21]->SetX("htt","Total H_{T}");
    resolution[21]->SetY("l1htt","L1 Total H_{T}");
    resolution[21]->SetOutName(triggerName+"_htt_over_l1Htt");

    // caloMetBE Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[22]->SetBins(bins());
    resolution[22]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    resolution[22]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[22]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[23]->SetBins(bins());
    resolution[23]->SetX("mhtPhi","H_{T}^{miss} Phi");
    resolution[23]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[23]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi");


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
        int add = 0;
        if( pu >= 13 && pu <= 19 ) add = 6;
        else if( pu >= 20 ) add = 12;

        // HTT
        double recoHtt = event->GetPEvent()->fSums->Ht;
        double l1Htt = event->fL1Htt;
        if( recoHtt > 100.0 && l1Htt > 0.02 )
        {
            resolution[3+add]->Fill(recoHtt, l1Htt);
            resolution[21]->Fill(recoHtt, l1Htt);
        //resolution[3]->Fill(event->fRecalcRecoHtt, event->fL1Htt);
        }

        // MHT
        double recalcRecoMht = event->fRecalcRecoMht;
        double l1Mht = event->fL1Mht;
        //resolution[1]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);
        if( recalcRecoMht > 0.2 && l1Mht > 0.2 )
        {
            resolution[1+add]->Fill(recalcRecoMht, l1Mht);
            resolution[19]->Fill(recalcRecoMht, l1Mht);
        }


        if( !event->fMuonFilterPassFlag ) continue;
        // MET
        double recoMet = event->GetPEvent()->fSums->caloMetBE;
        double l1Met = event->fL1Met;
        if( event->fMetFilterPassFlag )
        {
            if( recoMet > 40.0 && l1Met != 0.0 )
            {
                resolution[add]->Fill(recoMet, l1Met);
                resolution[18]->Fill(recoMet, l1Met);
            }
        }

        // ETT
        double recoEtt = event->GetPEvent()->fSums->caloSumEtBE;
        double l1Ett = event->fL1Ett;
        if( recoEtt != 0.0 && l1Ett != 0.0 )
        {
            resolution[2+add]->Fill(recoEtt, l1Ett);
            resolution[20]->Fill(recoEtt, l1Ett);
        }

        // MET Phi
        double recoMetPhi = event->GetPEvent()->fSums->caloMetPhiBE;
        double l1MetPhi = event->fL1MetPhi;
        if( recoMet != 0.0 && l1Met != 0.0 )
        {
            resolution[4+add]->Fill(FoldPhi(recoMetPhi), FoldPhi(l1MetPhi));
            resolution[22]->Fill(FoldPhi(recoMetPhi), FoldPhi(l1MetPhi));
        }

        // MHT Phi
        double recoMhtPhi = event->GetPEvent()->fSums->mHtPhi;
        double l1MhtPhi = event->fL1MhtPhi;
        if( event->GetPEvent()->fSums->mHt != 0.0 && l1Mht != 0.0 )
        {
            resolution[5+add]->Fill(FoldPhi(recoMhtPhi), FoldPhi(l1MhtPhi));
            resolution[23]->Fill(FoldPhi(recoMhtPhi), FoldPhi(l1MhtPhi));
            //resolution[5]->Fill(event->fRecalcRecoMhtPhi, event->fL1MhtPhi);
        }
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
