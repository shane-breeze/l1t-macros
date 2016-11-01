#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Utilities/TL1DateTime.h"
#include "../Plotting/TL1RateEfficiency.h"

std::vector<double> metBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void makeRateEfficiency()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.08, myStyle);

    // Basic
    std::string sampleName = "VBFHInv";
    std::string sampleTitle = "VBF H #rightarrow Inv";
    //std::string triggerName = "SingleMu";
    //std::string triggerTitle = "Single Muon";
    std::string triggerName = "ZeroBias";
    std::string triggerTitle = "Zero Bias";
    std::string puFilename = "/afs/cern.ch/work/s/sbreeze/l1tClasses/PUWeights/20160719_Data-SingleMu-2016Bv1_VBFHinv/pu_mcReweightedToData.root";

    std::string run = "276653";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160717_r276653_ZeroBias_l1t-int-71p1");
    inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160718_MC_VBFHinv125GeV_l1t-int-70p2");

    // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+"/rates/";
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_MC_"+sampleName+"_"+triggerName+"_run-"+run+"_MET+HF/RateEfficiency/";
    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1RateEfficiency*> rateEff;

    // l1 MET BE
    rateEff.emplace_back(new TL1RateEfficiency());
    rateEff[0]->SetRatePlot("/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput/20160719_Data_run-276653_ZeroBias/rates/rates_ZeroBias_l1EmuMetBE.root","cumulative_rates_l1EmuMetBE");
    rateEff[0]->SetX("l1EmuMetBE","L1 E_{T}^{miss} BE (GeV)");
    rateEff[0]->SetXBins(metBins());
    rateEff[0]->SetOutName(triggerName+"_l1EmuMetBE");

    // l1 MET HF
    rateEff.emplace_back(new TL1RateEfficiency());
    rateEff[1]->SetRatePlot("/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput/20160719_Data_run-276653_ZeroBias/rates/rates_ZeroBias_l1EmuMetHF.root","cumulative_rates_l1EmuMetHF");
    rateEff[1]->SetX("l1EmuMetHF","L1 E_{T}^{miss} HF (GeV)");
    rateEff[1]->SetXBins(metBins());
    rateEff[1]->SetOutName(triggerName+"_l1EmuMetHF");

    for(auto it=rateEff.begin(); it!=rateEff.end(); ++it)
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

        int pu = event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        double l1EmuMetBE = event->fL1EmuMet;
        double l1EmuMetHF = event->fL1EmuMetHF;

        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        rateEff[0]->Fill(l1EmuMetBE, recoMetHF, pu);
        rateEff[1]->Fill(l1EmuMetHF, recoMetHF, pu);
    }

    for(auto it=rateEff.begin(); it!=rateEff.end(); ++it)
        (*it)->DrawPlots();
}

std::vector<double> metBins()
{
    std::vector<double> temp;
    for(double bin=0.0; bin<=200.0; bin+=5.0) temp.push_back(bin);
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
