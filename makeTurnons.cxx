#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1Turnon.h"


vector<double> metBins();
vector<double> mhtBins();
vector<double> ettBins();
vector<double> httBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeTurnons()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";

    std::string run = "6.3fb^{-1}"; // an additional label for the plots
    std::string outDirBase = "/users/jt15104/l1t-macros/l1t-macros-Output/";
    bool doFit = false;
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"}; // Check the pu distribution to decide the relevant binning (for 2016 data these should be good)
    std::vector<int> puBins = {0,13,20,999};

    std::vector<std::string> inDir;
    // inDir.push_back("/hdfs/user/jt15104/copiesFromEOS/singleMuon2016_v70p1/run276242/");
    // inDir.push_back("/hdfs/user/jt15104/copiesFromEOS/singleMuon2016_v70p1/run276243/");
    inDir.push_back("/hdfs/user/jt15104/copiesFromEOS/singleMuon2016_v70p1/run276315/");    // inDir.push_back("");           
    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1Turnon*> turnons;

    // caloMetBE
    turnons.emplace_back(new TL1Turnon());
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/Turnons/";
    turnons[0]->SetSeeds({0.,40.,60.,80.,100.,120.});
    turnons[0]->SetXBins(metBins());
    turnons[0]->SetX("caloMetBE","Offline E_{T}^{miss} (GeV)");
    turnons[0]->SetSeed("l1MetSeed","L1 MET");
    turnons[0]->SetOutName(triggerName+"_caloMetBE_l1MetSeeds");
    turnons[0]->SetFit(doFit);

    // mht
    // turnons.emplace_back(new TL1Turnon());
    // turnons[1]->SetSeeds({0.,50.,70.,100.,130.,150.});
    // turnons[1]->SetXBins(mhtBins());
    // turnons[1]->SetX("mht","Offline H_{T}^{miss} (GeV)");
    // turnons[1]->SetSeed("l1Mht","L1 MHT");
    // turnons[1]->SetOutName(triggerName+"_recalcMht_l1MhtSeeds");
    // turnons[1]->SetFit(doFit);

    // caloEttBE
    // turnons.emplace_back(new TL1Turnon());
    // turnons[2]->SetSeeds({0.,40.,60.,100.,150.});
    // turnons[2]->SetXBins(ettBins());
    // turnons[2]->SetX("caloEttBE","Offline Total E_{T} (GeV)");
    // turnons[2]->SetSeed("l1ett","L1 ETT");
    // turnons[2]->SetOutName(triggerName+"_caloEttBE_l1EttSeeds");
    // turnons[2]->SetFit(doFit);

    // htt
    turnons.emplace_back(new TL1Turnon());
    turnons[3]->SetSeeds({0.,120.,160.,200.,240.,280.});
    turnons[3]->SetXBins(httBins());
    turnons[3]->SetX("recoHtt","Offline Total H_{T} (GeV)");
    turnons[3]->SetSeed("l1Htt","L1 HTT");
    turnons[3]->SetOutName(triggerName+"_recoHtt_l1HttSeeds");
    turnons[3]->SetFit(doFit);
    
    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
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

        //----- MHT -----//
        turnons[1]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht, pu);

        //----- HTT -----//
        turnons[3]->Fill(event->GetPEvent()->fSums->Ht, event->fL1Htt, pu);

        if( !event->fMuonFilterPassFlag ) continue;

        //----- MET -----//
        if( event->fMetFilterPassFlag )
            turnons[0]->Fill(sums->caloMetBE, event->fL1Met, pu);

        //----- ETT -----//
        turnons[2]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett, pu);
    }

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        (*it)->DrawPlots();
        (*it)->DrawTurnons();
    }

    cout << "Output saved in:\n" << outDir << endl;
}

vector<double> metBins()
{
    vector<double> temp;

    //for(double binLowerEdge=  0.0; binLowerEdge< 200.1; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);

    for(double binLowerEdge=  0.0; binLowerEdge< 40.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 70.0; binLowerEdge<100.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge<160.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=160.0; binLowerEdge<200.1; binLowerEdge+=40.0) temp.push_back(binLowerEdge);

    return temp;
}

vector<double> mhtBins()
{
    vector<double> temp;
    //for(double binLowerEdge=-30.0; binLowerEdge<  0.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 30.0; binLowerEdge< 50.0; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge= 25.0; binLowerEdge< 50.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 50.0; binLowerEdge< 80.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 80.0; binLowerEdge<140.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=140.0; binLowerEdge<200.0; binLowerEdge+=15.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge<300.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge<400.1; binLowerEdge+=50.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> ettBins()
{
    vector<double> temp;
    //for(double binLowerEdge=-30.0; binLowerEdge<  0.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=  0.0; binLowerEdge< 30.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 30.0; binLowerEdge< 50.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 50.0; binLowerEdge< 90.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 90.0; binLowerEdge<140.1; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge=100.0; binLowerEdge<700.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> httBins()
{
    vector<double> temp;
    for(double binLowerEdge=  0.0; binLowerEdge<100.0; binLowerEdge+=  5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge<200.0; binLowerEdge+= 10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge<400.0; binLowerEdge+= 20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=400.0; binLowerEdge<500.0; binLowerEdge+= 50.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=500.0; binLowerEdge<600.1; binLowerEdge+=100.0) temp.push_back(binLowerEdge);

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
