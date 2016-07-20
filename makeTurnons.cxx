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
    std::string sampleName = "Data";
    std::string sampleTitle = "2016 Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    // std::string sampleName = "HInv";
    // std::string sampleTitle = "VBF H #rightarrow Inv";
    // std::string triggerName = "";
    // std::string triggerTitle = "";
    std::string puFilename = "/afs/cern.ch/work/s/sbreeze/l1tClasses/PUWeights/20160719_Data-SingleMu-2016Bv1_VBFHinv/pu_mcReweightedToData.root";

    std::string run = "2016Bv1";
    // std::string run = "";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    bool doFit = false;
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"}; // Check the pu distribution to decide the relevant binning (for 2016 data these should be good)
    std::vector<int> puBins = {0,13,20,999};

    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu");
    inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160718_MC_VBFHinv125GeV_l1t-int-70p2");

    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+"_MET+HF/Turnons/";
    // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_MC_"+sampleName+"_MET+HF/Turnons/";
    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1Turnon*> turnons;

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
        (*it)->SetSample(sampleName,sampleTitle);
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(run);
        (*it)->SetOutDir(outDir);
        (*it)->SetPuType(puType);
        (*it)->SetPuBins(puBins);
        (*it)->SetPuFile(puFilename);
        (*it)->InitPlots();
    }

    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        if( triggerName == "SingleMu" )
            if( !event->fMuonFilterPassFlag ) 
                continue;
        
        int pu = event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        double l1EmuMetBE = event->fL1EmuMet;
        double l1EmuMetHF = event->fL1EmuMetHF;
        double caloMetBE = sums->caloMetBE;
        double caloMetHF = sums->caloMet;

        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            turnons[0]->Fill(caloMetBE, l1EmuMetBE);
            turnons[1]->Fill(caloMetHF, l1EmuMetBE);
            turnons[2]->Fill(caloMetHF, l1EmuMetHF);
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

    for(double binLowerEdge=  0.0; binLowerEdge< 40.0; binLowerEdge+= 4.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 70.0; binLowerEdge<100.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge<160.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=160.0; binLowerEdge<260.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);

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
