#include <string>
#include <vector>
#include <algorithm>

#include "Core/TL1EventClass.h"
#include "Core/TL1Progress.C"
#include "TL1XvsY.h"

std::vector<double> bins(double max, double width, double min);
std::vector<double> phiBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void testTL1XvsY()
{
    std::shared_ptr<TStyle> myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle.get());

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string run = "273301";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1XvsY>> xvsy;

    // caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    std::string outDir = outDirBase+"/"+xvsy.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/xy/";
    xvsy[0]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    xvsy[0]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetY("l1Met","L1 E_{T}^{miss} (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1Met");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[1]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[1]->SetOutName(triggerName+"_recalcRecoMht_vs_l1Mht");

    // caloEttBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(bins(600.0,10,0.0));
    xvsy[2]->SetX("recoEtt","Reco Total E_{T} (GeV)");
    xvsy[2]->SetYBins(bins(600.0,10,0.0));
    xvsy[2]->SetY("l1Ett","L1 Total E_{T}");
    xvsy[2]->SetOutName(triggerName+"_recoEtt_vs_l1Ett");

    // htt
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[3]->SetX("recohtt","Reco Total H_{T} (GeV)");
    xvsy[3]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[3]->SetY("l1Htt","L1 Total H_{T}");
    xvsy[3]->SetOutName(triggerName+"_htt_vs_l1Htt");
    
    // caloMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1MetPhi","L1 E_{T}^{miss} Phi");
    xvsy[4]->SetOutName(triggerName+"_caloMetBEPhi_vs_l1MetPhi");

    // mht Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("recalcRecoMhtPhi","Reco H_{T}^{miss} Phi");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1MhtPhi","L1 H_{T}^{miss} Phi");
    xvsy[5]->SetOutName(triggerName+"_recalcRecoMhtPhi_vs_l1MhtPhi");

    // l1MhtFloat
    xvsy.emplace_back(new TL1XvsY());
    xvsy[6]->SetXBins(bins(200.0,2.5,0.0));
    xvsy[6]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[6]->SetYBins(bins(200.0,2.5,0.0));
    xvsy[6]->SetY("recalcl1mht","Recalc L1 H_{T}^{miss} (GeV)");
    xvsy[6]->SetOutName(triggerName+"_recalcRecoMht_vs_recalcL1Mht");
    //xvsy[6]->SetAddMark("n_{j}^{MHT}=4");
    
    // l1EttNjet vs recoEttNjet
    xvsy.emplace_back(new TL1XvsY());
    xvsy[7]->SetXBins(bins(10,1,0));
    xvsy[7]->SetX("nJetRecoEtt","Njet in Recalc Reco H_{T}^{miss}");
    xvsy[7]->SetYBins(bins(10,1,0));
    xvsy[7]->SetY("nJetL1Ett","Njet in Recalc L1 H_{T}^{miss}");
    xvsy[7]->SetOutName(triggerName+"_nJetRecoMht_vs_nJetL1Mht");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[8]->SetSample(sample,"");
    xvsy[8]->SetTrigger(triggerName,triggerTitle);
    xvsy[8]->SetRun(run);
    xvsy[8]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[8]->SetX("recoMht","Reco H_{T}^{miss} (GeV)");
    xvsy[8]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[8]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[8]->SetOutName(triggerName+"_recoMht_vs_l1Mht");


    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
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

        //----- HTT -----//
        xvsy[3]->Fill(event->GetPEvent()->fSums->Ht, event->fL1Htt);
        //xvsy[3]->Fill(event->fRecalcRecoHtt, event->fL1Htt);
        
        //----- MHT -----//
        if( event->fMhtPassFlag && event->fRecalcRecoMht != 0.0 && event->fL1Mht != 0.0 ) xvsy[1]->Fill(event->fRecalcRecoMht, event->fL1Mht);
        //xvsy[1]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);
        if( event->fMhtPassFlag && event->fRecalcRecoMht != 0.0 && event->fRecalcL1Mht != 0.0 )
        {
            xvsy[5]->Fill(FoldPhi(event->fRecalcRecoMhtPhi), FoldPhi(event->fL1MhtPhi));
            xvsy[6]->Fill(event->fRecalcRecoMht, event->fRecalcL1Mht);
            xvsy[7]->Fill(event->fNJetRecoMht, event->fNJetL1Mht);
        }
        if( event->GetPEvent()->fSums->mHt != 0.0 && event->fL1Mht != 0.0 ) xvsy[8]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);

        if( !event->fMuonFilterPassFlag ) continue;
        //----- MET -----//
        if( event->fMetFilterPassFlag )
            xvsy[0]->Fill(event->GetPEvent()->fSums->caloMetBE, event->fL1Met);

        //----- ETT -----//
        xvsy[2]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett);

        //----- MET Phi -----//
        xvsy[4]->Fill(FoldPhi(event->GetPEvent()->fSums->caloMetPhiBE), FoldPhi(event->fL1MetPhi));

    }

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->DrawPlots();
}

std::vector<double> bins(double max, double width, double min)
{
    std::vector<double> temp;
    for(double binLowerEdge=min; binLowerEdge<=max; binLowerEdge+= width) temp.push_back(binLowerEdge);
    return temp;
}

std::vector<double> phiBins()
{
    std::vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=TMath::Pi(); binLowerEdge+= (TMath::Pi())/36.) temp.push_back(binLowerEdge);
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
    return TMath::Min( (float)TMath::Abs(phi), (float)TMath::Abs(2*TMath::Pi()-phi) );
}
