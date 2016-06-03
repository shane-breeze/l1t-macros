#include <string>
#include <memory>
#include <vector>

#include "Core/tdrstyle.C"
#include "Core/TL1EventClass.h"
#include "Core/TL1Progress.C"
#include "TL1Turnon.h"

vector<double> metBins(const std::string & pu);
vector<double> mhtBins();
vector<double> ettBins();
vector<double> httBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void testTL1Turnon()
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
    bool doFit = true;

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1Turnon>> turnons;

    int puMin=0;  //11, 19
    int puMax=10; //18, 1000

    // caloMetBE
    turnons.emplace_back(new TL1Turnon());
    std::string outDir = outDirBase+"/"+turnons.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/Turnons/";
    turnons[0]->SetSeeds({0.,40.,50.,60.,70.,80.,90.,100.,120.});
    turnons[0]->SetXBins(metBins("Low"));
    turnons[0]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    turnons[0]->SetSeed("l1MetSeed","L1 MET");
    turnons[0]->SetOutName(triggerName+"_caloMetBE_l1MetSeeds_lowPU");
    turnons[0]->SetFit(doFit);
    turnons[0]->SetAddMark("0PU10");

    // mht
    turnons.emplace_back(new TL1Turnon());
    turnons[1]->SetSeeds({0.,50.,70.,100.,120.,130.,140.,150.});
    turnons[1]->SetXBins(mhtBins());
    turnons[1]->SetX("mht","H_{T}^{miss} (GeV)");
    turnons[1]->SetSeed("l1Mht","L1 MHT");
    turnons[1]->SetOutName(triggerName+"_recalcMht_l1MhtSeeds_lowPU");
    turnons[1]->SetFit(doFit);
    turnons[1]->SetAddMark("0PU10");

    // caloEttBE
    turnons.emplace_back(new TL1Turnon());
    turnons[2]->SetSeeds({0.,40.,60.});
    turnons[2]->SetXBins(ettBins());
    turnons[2]->SetX("caloEttBE","Total Calo E_{T} no HF (GeV)");
    turnons[2]->SetSeed("l1ett","L1 ETT");
    turnons[2]->SetOutName(triggerName+"_caloEttBE_l1EttSeeds_lowPU");
    turnons[2]->SetFit(doFit);
    turnons[2]->SetAddMark("0PU10");

    // htt
    turnons.emplace_back(new TL1Turnon());
    turnons[3]->SetSeeds({0.,120.,160.,200.,240.,270.,280.,300.,320.});
    turnons[3]->SetXBins(httBins());
    turnons[3]->SetX("htt","Total H_{T} (GeV)");
    turnons[3]->SetSeed("l1htt","L1 HTT");
    turnons[3]->SetOutName(triggerName+"_htt_l1HttSeeds_lowPU");
    turnons[3]->SetFit(doFit);
    turnons[3]->SetAddMark("0PU10");

    // caloMetBE
    turnons.emplace_back(new TL1Turnon());
    turnons[4]->SetSeeds({0.,40.,50.,60.,70.,80.,90.,100.,120.});
    turnons[4]->SetXBins(metBins("Med"));
    turnons[4]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    turnons[4]->SetSeed("l1MetSeed","L1 MET");
    turnons[4]->SetOutName(triggerName+"_caloMetBE_l1MetSeeds_medPU");
    turnons[4]->SetFit(doFit);
    turnons[4]->SetAddMark("11PU18");

    // mht
    turnons.emplace_back(new TL1Turnon());
    turnons[5]->SetSeeds({0.,50.,70.,100.,120.,130.,140.,150.});
    turnons[5]->SetXBins(mhtBins());
    turnons[5]->SetX("mht","H_{T}^{miss} (GeV)");
    turnons[5]->SetSeed("l1Mht","L1 MHT");
    turnons[5]->SetOutName(triggerName+"_recalcMht_l1MhtSeeds_medPU");
    turnons[5]->SetFit(doFit);
    turnons[5]->SetAddMark("11PU18");

    // caloEttBE
    turnons.emplace_back(new TL1Turnon());
    turnons[6]->SetSeeds({0.,40.,60.});
    turnons[6]->SetXBins(ettBins());
    turnons[6]->SetX("caloEttBE","Total Calo E_{T} no HF (GeV)");
    turnons[6]->SetSeed("l1ett","L1 ETT");
    turnons[6]->SetOutName(triggerName+"_caloEttBE_l1EttSeeds_medPU");
    turnons[6]->SetFit(doFit);
    turnons[6]->SetAddMark("11PU18");

    // htt
    turnons.emplace_back(new TL1Turnon());
    turnons[7]->SetSeeds({0.,120.,160.,200.,240.,270.,280.,300.,320.});
    turnons[7]->SetXBins(httBins());
    turnons[7]->SetX("htt","Total H_{T} (GeV)");
    turnons[7]->SetSeed("l1htt","L1 HTT");
    turnons[7]->SetOutName(triggerName+"_htt_l1HttSeeds_medPU");
    turnons[7]->SetFit(doFit);
    turnons[7]->SetAddMark("11PU18");

    // caloMetBE
    turnons.emplace_back(new TL1Turnon());
    turnons[8]->SetSeeds({0.,40.,50.,60.,70.,80.,90.,100.,120.});
    turnons[8]->SetXBins(metBins("High"));
    turnons[8]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    turnons[8]->SetSeed("l1MetSeed","L1 MET");
    turnons[8]->SetOutName(triggerName+"_caloMetBE_l1MetSeeds_highPU");
    turnons[8]->SetFit(doFit);
    turnons[8]->SetAddMark("19PU");

    // mht
    turnons.emplace_back(new TL1Turnon());
    turnons[9]->SetSeeds({0.,50.,70.,100.,120.,130.,140.,150.});
    turnons[9]->SetXBins(mhtBins());
    turnons[9]->SetX("mht","H_{T}^{miss} (GeV)");
    turnons[9]->SetSeed("l1Mht","L1 MHT");
    turnons[9]->SetOutName(triggerName+"_recalcMht_l1MhtSeeds_highPU");
    turnons[9]->SetFit(doFit);
    turnons[9]->SetAddMark("19PU");

    // caloEttBE
    turnons.emplace_back(new TL1Turnon());
    turnons[10]->SetSeeds({0.,40.,60.});
    turnons[10]->SetXBins(ettBins());
    turnons[10]->SetX("caloEttBE","Total Calo E_{T} no HF (GeV)");
    turnons[10]->SetSeed("l1ett","L1 ETT");
    turnons[10]->SetOutName(triggerName+"_caloEttBE_l1EttSeeds_highPU");
    turnons[10]->SetFit(doFit);
    turnons[10]->SetAddMark("19PU");

    // htt
    turnons.emplace_back(new TL1Turnon());
    turnons[11]->SetSeeds({0.,120.,160.,200.,240.,270.,280.,300.,320.});
    turnons[11]->SetXBins(httBins());
    turnons[11]->SetX("htt","Total H_{T} (GeV)");
    turnons[11]->SetSeed("l1htt","L1 HTT");
    turnons[11]->SetOutName(triggerName+"_htt_l1HttSeeds_highPU");
    turnons[11]->SetFit(doFit);
    turnons[11]->SetAddMark("19PU");

    // caloMetBE
    turnons.emplace_back(new TL1Turnon());
    turnons[12]->SetSeeds({0.,40.,50.,60.,70.,80.,90.,100.,120.});
    turnons[12]->SetXBins(metBins("High"));
    turnons[12]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    turnons[12]->SetSeed("l1MetSeed","L1 MET");
    turnons[12]->SetOutName(triggerName+"_caloMetBE_l1MetSeeds_highPU");
    turnons[12]->SetFit(doFit);

    // mht
    turnons.emplace_back(new TL1Turnon());
    turnons[13]->SetSeeds({0.,50.,70.,100.,120.,130.,140.,150.});
    turnons[13]->SetXBins(mhtBins());
    turnons[13]->SetX("mht","H_{T}^{miss} (GeV)");
    turnons[13]->SetSeed("l1Mht","L1 MHT");
    turnons[13]->SetOutName(triggerName+"_recalcMht_l1MhtSeeds_highPU");
    turnons[13]->SetFit(doFit);

    // caloEttBE
    turnons.emplace_back(new TL1Turnon());
    turnons[14]->SetSeeds({0.,40.,60.});
    turnons[14]->SetXBins(ettBins());
    turnons[14]->SetX("caloEttBE","Total Calo E_{T} no HF (GeV)");
    turnons[14]->SetSeed("l1ett","L1 ETT");
    turnons[14]->SetOutName(triggerName+"_caloEttBE_l1EttSeeds_highPU");
    turnons[14]->SetFit(doFit);

    // htt
    turnons.emplace_back(new TL1Turnon());
    turnons[15]->SetSeeds({0.,120.,160.,200.,240.,270.,280.,300.,320.});
    turnons[15]->SetXBins(httBins());
    turnons[15]->SetX("htt","Total H_{T} (GeV)");
    turnons[15]->SetSeed("l1htt","L1 HTT");
    turnons[15]->SetOutName(triggerName+"_htt_l1HttSeeds_highPU");
    turnons[15]->SetFit(doFit);

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
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
        if( pu >= 11 && pu <= 18 ) add = 4;
        else if( pu >= 19 ) add = 8;
        //----- MHT -----//
        turnons[1+add]->Fill(event->fRecalcRecoMht, event->fRecalcL1Mht);
        turnons[13]->Fill(event->fRecalcRecoMht, event->fRecalcL1Mht);
        //turnons[1+add]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);
        
        //----- HTT -----//
        turnons[3+add]->Fill(event->GetPEvent()->fSums->Ht, event->fL1Htt);
        turnons[15]->Fill(event->GetPEvent()->fSums->Ht, event->fL1Htt);
        //turnons[3+add]->Fill(event->fRecalcRecoHtt, event->fL1Htt);

        if( !event->fMuonFilterPassFlag ) continue;
        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            turnons[add]->Fill(event->GetPEvent()->fSums->caloMetBE, event->fL1Met);
            turnons[12]->Fill(event->GetPEvent()->fSums->caloMetBE, event->fL1Met);
        }

        //----- ETT -----//
        turnons[2+add]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett);
        turnons[14]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett);
    }

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        (*it)->DrawPlots();
        (*it)->DrawTurnons();
    }
}

vector<double> metBins(const std::string & pu)
{
    vector<double> temp;
    if( pu == "Low" || pu == "High" )
    {
        for(double binLowerEdge=  0.0; binLowerEdge< 40.0; binLowerEdge+= 4.0) temp.push_back(binLowerEdge);
        for(double binLowerEdge= 40.0; binLowerEdge< 80.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
        for(double binLowerEdge= 80.0; binLowerEdge<200.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
        //for(double binLowerEdge=180.0; binLowerEdge<300.1; binLowerEdge+=40.0) temp.push_back(binLowerEdge);
    }
    else if( pu == "Med" )
    {
        for(double binLowerEdge=  0.0; binLowerEdge< 40.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
        for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
        for(double binLowerEdge= 70.0; binLowerEdge<200.1; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
        //for(double binLowerEdge=200.0; binLowerEdge<300.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    }
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
    for(double binLowerEdge=  0.0; binLowerEdge<100.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge<250.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=250.0; binLowerEdge<600.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=600.0; binLowerEdge<800.1; binLowerEdge+=50.0) temp.push_back(binLowerEdge);
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
