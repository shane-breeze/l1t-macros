#include <string>
#include <vector>
#include <algorithm>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1XvsY.h"

std::vector<double> bins(double max, double width, double min);
std::vector<double> phiBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void makeXvsY()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    ///std::string run = "273301";
    std::string run = "273301-302-450";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu";
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1XvsY*> xvsy;

    // caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/xy/";
    xvsy[0]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetX("caloMetBE","Offline E_{T}^{miss} (GeV)");
    xvsy[0]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetY("l1Met","L1 E_{T}^{miss} (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1Met");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetX("recalcRecoMht","Offline H_{T}^{miss} (GeV)");
    xvsy[1]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[1]->SetOutName(triggerName+"_recalcRecoMht_vs_l1Mht");

    // caloEttBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(bins(600.0,10,0.0));
    xvsy[2]->SetX("recoEtt","Offline Total E_{T} (GeV)");
    xvsy[2]->SetYBins(bins(600.0,10,0.0));
    xvsy[2]->SetY("l1Ett","L1 Total E_{T}");
    xvsy[2]->SetOutName(triggerName+"_recoEtt_vs_l1Ett");

    // htt
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[3]->SetX("recohtt","Offline Total H_{T} (GeV)");
    xvsy[3]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[3]->SetY("l1Htt","L1 Total H_{T}");
    xvsy[3]->SetOutName(triggerName+"_htt_vs_l1Htt");
    
    // caloMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("caloMetBEPhi","Offline E_{T}^{miss} Phi");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1MetPhi","L1 E_{T}^{miss} Phi");
    xvsy[4]->SetOutName(triggerName+"_caloMetBEPhi_vs_l1MetPhi");

    // mht Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("recalcRecoMhtPhi","Offline H_{T}^{miss} Phi");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1MhtPhi","L1 H_{T}^{miss} Phi");
    xvsy[5]->SetOutName(triggerName+"_recalcRecoMhtPhi_vs_l1MhtPhi");

    // l1MhtFloat
    xvsy.emplace_back(new TL1XvsY());
    xvsy[6]->SetXBins(bins(200.0,2.5,0.0));
    xvsy[6]->SetX("recalcRecoMht","Offline H_{T}^{miss} (GeV)");
    xvsy[6]->SetYBins(bins(200.0,2.5,0.0));
    xvsy[6]->SetY("recalcl1mht","L1 H_{T}^{miss} (GeV)");
    xvsy[6]->SetOutName(triggerName+"_recalcRecoMht_vs_recalcL1Mht");
    
    // l1EttNjet vs recoEttNjet
    xvsy.emplace_back(new TL1XvsY());
    xvsy[7]->SetXBins(bins(10,1,0));
    xvsy[7]->SetX("nJetRecoEtt","Njet in Recalc Reco H_{T}^{miss}");
    xvsy[7]->SetYBins(bins(10,1,0));
    xvsy[7]->SetY("nJetL1Ett","Njet in Recalc L1 H_{T}^{miss}");
    xvsy[7]->SetOutName(triggerName+"_nJetRecoMht_vs_nJetL1Mht");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[8]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[8]->SetX("recoMht","Offline H_{T}^{miss} (GeV)");
    xvsy[8]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[8]->SetY("l1Mht","L1 H_{T}^{miss} (GeV)");
    xvsy[8]->SetOutName(triggerName+"_recoMht_vs_l1Mht");

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

        //----- HTT -----//
        double recoHtt = event->GetPEvent()->fSums->Ht;
        double l1Htt = event->fL1Htt;
        xvsy[3]->Fill(recoHtt, l1Htt, pu);
        
        //----- MHT -----//
        bool mhtPassFlag = event->fMhtPassFlag;

        double recoMht = event->GetPEvent()->fSums->mHt;
        double recalcRecoMht = event->fRecalcRecoMht;
        double l1Mht = event->fL1Mht;
        double recalcL1Mht = event->fRecalcL1Mht;

        if( mhtPassFlag && recalcRecoMht > 0.0 && l1Mht > 0.0 )
            xvsy[1]->Fill(recalcRecoMht, l1Mht, pu);

        if( mhtPassFlag && recalcRecoMht > 0.0 && recalcL1Mht > 0.0 )
        {
            double recalcRecoMhtPhi = event->fRecalcRecoMhtPhi;
            double l1MhtPhi = event->fL1MhtPhi;
            xvsy[5]->Fill(FoldPhi(recalcRecoMhtPhi), FoldPhi(l1MhtPhi), pu);
            xvsy[6]->Fill(recalcRecoMht, recalcL1Mht, pu);
            xvsy[7]->Fill(event->fNJetRecoMht, event->fNJetL1Mht, pu);
        }

        if( recoMht > 0.0 && l1Mht > 0.0 )
            xvsy[8]->Fill(recoMht, l1Mht, pu);

        //----- ETT -----//
        xvsy[2]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett, pu);

        if( !event->fMuonFilterPassFlag ) continue;
        //----- MET -----//
        if( event->fMetFilterPassFlag )
            xvsy[0]->Fill(event->GetPEvent()->fSums->caloMetBE, event->fL1Met, pu);

        //----- MET Phi -----//
        xvsy[4]->Fill(FoldPhi(event->GetPEvent()->fSums->caloMetPhiBE), FoldPhi(event->fL1MetPhi), pu);
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
