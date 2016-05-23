#include <string>
#include <vector>

#include "TL1EventClass.h"
#include "TL1Turnon.h"

vector<double> metBins();
vector<double> mhtBins();
vector<double> ettBins();
vector<double> httBins();

void testTL1Turnon()
{
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

    std::vector<std::shared_ptr<TL1Turnon>> turnons;

    // caloMetBE
    turnons.emplace_back(new TL1Turnon());
    turnons[0]->SetSample(sample,"");
    turnons[0]->SetTrigger(triggerName,triggerTitle);
    turnons[0]->SetRun(run);
    turnons[0]->SetSeeds({0.,40.,50.,60.,70.,80.,90.,100.,120.});
    turnons[0]->SetXBins(metBins());
    turnons[0]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    turnons[0]->SetSeed("l1MetSeed","L1 MET");
    turnons[0]->SetOutName(triggerName+"_caloMetBE_l1MetSeeds_muonFilter");
    turnons[0]->SetFit(doFit);

    // mht
    turnons.emplace_back(new TL1Turnon());
    turnons[1]->SetSample(sample,"");
    turnons[1]->SetTrigger(triggerName,triggerTitle);
    turnons[1]->SetRun(run);
    turnons[1]->SetSeeds({0.,50.,70.,100.,120.,130.,140.,150.});
    turnons[1]->SetXBins(mhtBins());
    turnons[1]->SetX("mht","H_{T}^{miss} (GeV)");
    turnons[1]->SetSeed("l1Mht","L1 MHT");
    turnons[1]->SetOutName(triggerName+"_recalcMht_l1MhtSeeds");
    turnons[1]->SetFit(doFit);

    // caloEttBE
    turnons.emplace_back(new TL1Turnon());
    turnons[2]->SetSample(sample,"");
    turnons[2]->SetTrigger(triggerName,triggerTitle);
    turnons[2]->SetRun(run);
    turnons[2]->SetSeeds({0.,40.,60.});
    turnons[2]->SetXBins(ettBins());
    turnons[2]->SetX("caloEttBE","Total Calo E_{T} no HF (GeV)");
    turnons[2]->SetSeed("l1ett","L1 ETT");
    turnons[2]->SetOutName(triggerName+"_caloEttBE_l1EttSeeds");
    turnons[2]->SetFit(doFit);

    // htt
    turnons.emplace_back(new TL1Turnon());
    turnons[3]->SetSample(sample,"");
    turnons[3]->SetTrigger(triggerName,triggerTitle);
    turnons[3]->SetRun(run);
    turnons[3]->SetSeeds({0.,120.,160.,200.,240.,270.,280.,300.,320.});
    turnons[3]->SetXBins(httBins());
    turnons[3]->SetX("htt","Total H_{T} (GeV)");
    turnons[3]->SetSeed("l1htt","L1 HTT");
    turnons[3]->SetOutName(triggerName+"_htt_l1HttSeeds");
    turnons[3]->SetFit(doFit);

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
        (*it)->InitDists();

    while( event->Next() )
    {
        //----- Filters -----//
        // Muon loop
        bool passMuonFilter = event->MuonFilter();

        // Sums
        bool passSumsFilter = event->SumsFilter();
        //-------------------//

        if( !passMuonFilter ) continue;

        event->GetL1Variables();
        event->RecalculateVariables();
        double recalcMht = event->fRecalcMht;
        double recalcMhtPhi = event->fRecalcMhtPhi;
        double recalcHtt = event->fRecalcHtt;
        
        if( passSumsFilter )
            turnons[0]->Fill(event->fSums->caloMetBE, event->fL1Met);
        //turnons[1]->Fill(event->fSums->mHt, event->fL1Mht);
        turnons[1]->Fill(recalcMht, event->fL1Mht);
        turnons[2]->Fill(event->fSums->caloSumEtBE, event->fL1Ett);
        turnons[3]->Fill(event->fSums->Ht, event->fL1Htt);
        //turnons[3]->Fill(recalcHtt, event->fL1Htt);
    }

    for(auto it=turnons.begin(); it!=turnons.end(); ++it)
    {
        (*it)->DrawDists();
        (*it)->DrawTurnons();
    }

    rootFile->Close();
}

vector<double> metBins()
{
    vector<double> temp;
    for(double binLowerEdge=-20.0; binLowerEdge<  0.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=  0.0; binLowerEdge< 40.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 70.0; binLowerEdge<200.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge=100.0; binLowerEdge<200.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge<300.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge=250.0; binLowerEdge<300.1; binLowerEdge+=50.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> mhtBins()
{
    vector<double> temp;
    //for(double binLowerEdge=-30.0; binLowerEdge<  0.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=  0.0; binLowerEdge< 50.0; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
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
