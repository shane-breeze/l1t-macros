#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Plotting/TL1Resolution.h"

std::vector<double> bins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void testTL1Resolution()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Basic
    std::string sample = ;
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string run = "273301-302-450";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu";
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1Resolution*> resolution;

    // caloMetBE
    resolution.emplace_back(new TL1Resolution());
    std::string outDir = outDirBase+"/"+resolution.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/Resolutions/";
    resolution[0]->SetBins(bins());
    resolution[0]->SetX("caloMetBE","Offline E_{T}^{miss}");
    resolution[0]->SetY("l1met","L1 E_{T}^{miss}");
    resolution[0]->SetOutName(triggerName+"_caloMetBE_over_l1Met");
    resolution[0]->AddRelTitle("recoCaloMetBE","Offline E_{T}^{miss} (GeV)");
    resolution[0]->AddRelBins({20.,40.,60.,80.,100.,120.,140.});
    resolution[0]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // mht
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetBins(bins());
    resolution[1]->SetX("mht","Offline H_{T}^{miss}");
    resolution[1]->SetY("l1mht","L1 H_{T}^{miss}");
    resolution[1]->SetOutName(triggerName+"_recalcMht_over_l1Mht");
    resolution[1]->AddRelTitle("recoMht","Offline H_{T}^{miss} (GeV)");
    resolution[1]->AddRelBins({0.,10.,20.,30.,40.,50.,60.,70.,80.,100.});
    //resolution[1]->SetAddMark("L1 ETM > 40 GeV");

    // caloEttBE
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetBins(bins());
    resolution[2]->SetX("caloEttBE","Offline Total E_{T}");
    resolution[2]->SetY("l1ett","L1 Total E_{T}");
    resolution[2]->SetOutName(triggerName+"_caloEttBE_over_l1Ett");
    resolution[2]->AddRelTitle("recoEtt","Offline Total E_{T} (GeV)");
    resolution[2]->AddRelBins({0.,10.,20.,30.,40.,50.,60.,70.,80.,100.});
    //resolution[2]->SetAddMark("L1 ETM > 40 GeV");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetBins(bins());
    resolution[3]->SetX("htt","Offline Total H_{T}");
    resolution[3]->SetY("l1htt","L1 Total H_{T}");
    resolution[3]->SetOutName(triggerName+"_htt_over_l1Htt");
    resolution[3]->AddRelTitle("recoHtt","Offline Total H_{T} (GeV)");
    resolution[3]->AddRelBins({0.,10.,20.,30.,40.,50.,60.,70.,80.,100.});
    resolution[3]->SetAddMark("Offline HTT > 100 GeV");

    // caloMetBE Phi
    double p = TMath::Pi();
    resolution.emplace_back(new TL1Resolution());
    resolution[4]->SetBins(bins());
    resolution[4]->SetX("caloMetBEPhi","Offline E_{T}^{miss} Phi");
    resolution[4]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[4]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi");
    resolution[4]->AddRelTitle("recoCaloMetPhiBE","Offline E_{T}^{miss} Phi");
    resolution[4]->AddRelBins({-p,-0.75*p,-0.5*p,-0.25*p,0.,0.25*p,0.5*p,0.75*p,p});
    //resolution[0]->SetAddMark("L1 ETM > 40 GeV");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[5]->SetBins(bins());
    resolution[5]->SetX("mhtPhi","Offline H_{T}^{miss} Phi");
    resolution[5]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[5]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi");
    resolution[5]->AddRelTitle("recoMhtPhi","Offline H_{T}^{miss} Phi");
    resolution[5]->AddRelBins({-p,-0.75*p,-0.5*p,-0.25*p,0.,0.25*p,0.5*p,0.75*p,p});
    //resolution[0]->SetAddMark("L1 ETM > 40 GeV");

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
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

        // HTT
        double recoHtt = event->GetPEvent()->fSums->Ht;
        double l1Htt = event->fL1Htt;
        if( recoHtt > 100.0 && l1Htt > 0.02 )
            resolution[3]->Fill(recoHtt, l1Htt, pu);
        resolution[3]->RelFill(recoHtt, l1Htt, pu, {recoHtt});

        // MHT
        double recalcRecoMht = event->fRecalcRecoMht;
        double l1Mht = event->fL1Mht;
        if( recalcRecoMht > 0.2 && l1Mht > 0.2 )
            resolution[1]->Fill(recalcRecoMht, l1Mht, pu);
        resolution[1]->RelFill(recalcRecoMht, l1Mht, pu, {recalcRecoMht});

        // MHT Phi
        double recoMhtPhi = event->GetPEvent()->fSums->mHtPhi;
        double l1MhtPhi = event->fL1MhtPhi;
        if( event->GetPEvent()->fSums->mHt != 0.0 && l1Mht != 0.0 )
            resolution[5]->Fill(FoldPhi(recoMhtPhi), FoldPhi(l1MhtPhi), pu);
        resolution[5]->RelFill(FoldPhi(recoMhtPhi), FoldPhi(l1MhtPhi), pu, {FoldPhi(recoMhtPhi)});

        // ETT
        double recoEtt = event->GetPEvent()->fSums->caloSumEtBE;
        double l1Ett = event->fL1Ett;
        if( recoEtt != 0.0 && l1Ett != 0.0 )
            resolution[2]->Fill(recoEtt, l1Ett, pu);
        resolution[2]->RelFill(recoEtt, l1Ett, pu, {recoEtt});

        if( !event->fMuonFilterPassFlag ) continue;

        // MET
        double recoMet = event->GetPEvent()->fSums->caloMetBE;
        double l1Met = event->fL1Met;
        if( event->fMetFilterPassFlag )
        {
            if( recoMet > 40.0 && l1Met != 0.0 )
                resolution[0]->Fill(recoMet, l1Met, pu);
            resolution[0]->RelFill(recoMet, l1Met, pu, {recoMet});
        }

        // MET Phi
        double recoMetPhi = event->GetPEvent()->fSums->caloMetPhiBE;
        double l1MetPhi = event->fL1MetPhi;
        if( recoMet != 0.0 && l1Met != 0.0 )
            resolution[4]->Fill(FoldPhi(recoMetPhi), FoldPhi(l1MetPhi), pu);
        resolution[4]->RelFill(FoldPhi(recoMetPhi), FoldPhi(l1MetPhi), pu, {FoldPhi(recoMetPhi)});

    }

    resolution[0]->DrawPlots();
//    resolution[3]->DrawPlots();
//    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
//        (*it)->DrawPlots();
        
}

std::vector<double> bins()
{
    std::vector<double> temp;
    for(double binLowerEdge=-1.0; binLowerEdge<=1.5; binLowerEdge+= 0.05) temp.push_back(binLowerEdge);
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
