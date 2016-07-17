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

    std::string run = "2016B";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    bool doFit = false;
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"}; // Check the pu distribution to decide the relevant binning (for 2016 data these should be good)
    std::vector<int> puBins = {0,13,20,999};

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0";
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1Turnon*> turnons;
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/Turnons/";

    // caloMetBE and l1MetBE seeds
    turnons.emplace_back(new TL1Turnon());
    turnons[0]->SetSeeds({0.,40.,60.,80.,100.,120.});
    turnons[0]->SetXBins(metBins());
    turnons[0]->SetX("caloMetBE","Offline E_{T}^{miss} BE (GeV)");
    turnons[0]->SetSeed("l1EmuMetBESeed","L1 MET BE");
    turnons[0]->SetOutName(triggerName+"_caloMetBE_l1EmuMetBESeeds");
    turnons[0]->SetFit(doFit);

    // caloMetHF and l1MetBE seeds
    turnons.emplace_back(new TL1Turnon());
    turnons[1]->SetSeeds({0.,40.,60.,80.,100.,120.});
    turnons[1]->SetXBins(metBins());
    turnons[1]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    turnons[1]->SetSeed("l1EmuMetBESeed","L1 MET BE");
    turnons[1]->SetOutName(triggerName+"_caloMetHF_l1EmuMetBESeeds");
    turnons[1]->SetFit(doFit);

    // caloMetHF and l1MetHF seeds
    turnons.emplace_back(new TL1Turnon());
    turnons[2]->SetSeeds({0.,40.,60.,80.,100.,120.});
    turnons[2]->SetXBins(metBins());
    turnons[2]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    turnons[2]->SetSeed("l1EmuMetHFSeed","L1 MET HF");
    turnons[2]->SetOutName(triggerName+"_caloMetHF_l1EmuMetHFSeeds");
    turnons[2]->SetFit(doFit);

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

        double l1EmuMetBE = event->fL1EmuMet;
        double l1EmuMetHF = event->fL1EmuMetHF;
        double caloMetBE = sums->caloMetBE;
        double caloMetHF = sums->caloMet;

        if( !event->fMuonFilterPassFlag ) continue;

        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            turnons[0]->Fill(caloMetBE, l1EmuMetBE, pu);
            turnons[1]->Fill(caloMetHF, l1EmuMetBE, pu);
            turnons[2]->Fill(caloMetHF, l1EmuMetHF, pu);
        }
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
