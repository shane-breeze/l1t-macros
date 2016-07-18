#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1Resolution.h"

std::vector<double> bins(std::string plotType);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void makeResolutions()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

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
   
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/Resolutions/";
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1Resolution*> resolution;
    
    // caloMetBE
    resolution.emplace_back(new TL1Resolution());
    resolution[0]->SetPlotType("Energy");
    resolution[0]->SetBins(bins("Energy"));
    resolution[0]->SetX("caloMetBE","Offline E_{T}^{miss}");
    resolution[0]->SetY("l1met","L1 E_{T}^{miss}");
    resolution[0]->SetOutName(triggerName+"_caloMetBE_over_l1Met");
    resolution[0]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // mht
    // resolution.emplace_back(new TL1Resolution());
    // resolution[1]->SetBins(bins());
    // resolution[1]->SetX("mht","Offline H_{T}^{miss}");
    // resolution[1]->SetY("l1mht","L1 H_{T}^{miss}");
    // resolution[1]->SetOutName(triggerName+"_recalcMht_over_l1Mht");
    //resolution[1]->SetAddMark("L1 ETM > 40 GeV");

    // caloEttBE
    // resolution.emplace_back(new TL1Resolution());
    // resolution[2]->SetBins(bins());
    // resolution[2]->SetX("caloEttBE","Offline Total E_{T}");
    // resolution[2]->SetY("l1ett","L1 Total E_{T}");
    // resolution[2]->SetOutName(triggerName+"_caloEttBE_over_l1Ett");
    //resolution[2]->SetAddMark("L1 ETM > 40 GeV");

    // htt
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetPlotType("Energy");
    resolution[1]->SetBins(bins("Energy"));
    resolution[1]->SetX("htt","Offline Total H_{T}");
    resolution[1]->SetY("l1htt","L1 Total H_{T}");
    resolution[1]->SetOutName(triggerName+"_htt_over_l1Htt");
    resolution[1]->SetAddMark("Offline HTT > 100 GeV");

    // caloMetBE Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetPlotType("Position");
    resolution[2]->SetBins(bins("Position"));
    resolution[2]->SetX("caloMetBEPhi","Offline E_{T}^{miss} Phi");
    resolution[2]->SetY("l1metphi","L1 E_{T}^{miss} Phi");
    resolution[2]->SetOutName(triggerName+"_caloMetBEPhi_over_l1MetPhi");
    //resolution[0]->SetAddMark("L1 ETM > 40 GeV");

    // mht Phi
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetPlotType("Position");
    resolution[3]->SetBins(bins("Position"));
    resolution[3]->SetX("mhtPhi","Offline H_{T}^{miss} Phi");
    resolution[3]->SetY("l1httphi","L1 Total H_{T} Phi");
    resolution[3]->SetOutName(triggerName+"_recalcMhtPhi_over_l1MhtPhi");
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
        auto sums = event->GetPEvent()->fSums;

        // HTT
        double recoHtt = sums->Ht;
        double l1Htt = event->fL1Htt;
        if( recoHtt > 100.0 && l1Htt > 0.02 )
            resolution[1]->Fill(recoHtt, l1Htt, pu);

        // MHT
        //double recalcRecoMht = event->fRecalcRecoMht;
        double l1Mht = event->fL1Mht;
        //if( recalcRecoMht > 0.2 && l1Mht > 0.2 )
        //    resolution[1]->Fill(recalcRecoMht, l1Mht, pu);

        // MHT Phi
        double recoMhtPhi = sums->mHtPhi;
        double l1MhtPhi = event->fL1MhtPhi;
        if( sums->mHt != 0.0 && l1Mht != 0.0 )
            resolution[3]->Fill(FoldPhi(recoMhtPhi), FoldPhi(l1MhtPhi), pu);

        // ETT
        //double recoEtt = sums->caloSumEtBE;
        //double l1Ett = event->fL1Ett;
        //if( recoEtt != 0.0 && l1Ett != 0.0 )
        //    resolution[2]->Fill(recoEtt, l1Ett, pu);

        if( !event->fMuonFilterPassFlag ) continue;

        // MET
        double recoMet = sums->caloMetBE;
        double l1Met = event->fL1Met;
        if( event->fMetFilterPassFlag )
        {
            if( recoMet > 40.0 && l1Met != 0.0 )
                resolution[0]->Fill(recoMet, l1Met, pu);
        }

        // MET Phi
        double recoMetPhi = sums->caloMetPhiBE;
        double l1MetPhi = event->fL1MetPhi;
        if( recoMet != 0.0 && l1Met != 0.0 )
            resolution[2]->Fill(FoldPhi(recoMetPhi), FoldPhi(l1MetPhi), pu);

    }

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
        (*it)->DrawPlots();
        
}

std::vector<double> bins(std::string plotType)
{
    std::vector<double> temp;
    if( plotType == "Energy" ) for(double binLowerEdge=-1.0; binLowerEdge<=1.5; binLowerEdge+= 0.05) temp.push_back(binLowerEdge);
    else if( plotType == "Position" ) for(double binLowerEdge=-0.3; binLowerEdge<=0.3; binLowerEdge+= 0.005) temp.push_back(binLowerEdge);
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
