#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1PUWeights.h"

void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
std::vector<double> bins(int min, int max);

void generatePUWeights()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.08, myStyle);

    // DATA
    std::string sampleName = "Data";
    std::string sampleTitle = "2016 Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    //std::string run = "276243";
    std::string run = "2016Bv1";
    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160713_r276243_SingleMu_l1t-int-71p1/");
    inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");

    // MC
    std::string mcName = "VBFHinv";
    std::string mcTitle = "VBF H #rightarrow Inv";
    std::vector<std::string> mcDir;
    mcDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160718_MC_VBFHinv125GeV_l1t-int-70p2");
    
    // OUTPUT 
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/l1tClasses/PUWeights";
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"-"
        +triggerName+"-"+run+"_"+mcName;

    TL1EventClass * event(new TL1EventClass(inDir));
    TL1EventClass * mcEvent(new TL1EventClass(mcDir));

    TL1PUWeights * puWeight(new TL1PUWeights());
    puWeight->SetBins(bins(1,100));
    
    // Start
    puWeight->SetData(sampleName,sampleTitle,triggerName,triggerTitle,run);
    puWeight->SetMC(mcName, mcTitle);
    puWeight->SetOutDir(outDir);
    puWeight->InitPlots();

    // Analyse - DATA
    unsigned NEntries = event->GetPEvent()->GetNEntries();
    std::cout << "Looping through DATA events" << std::endl;
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        int pu = event->GetPEvent()->fVertex->nVtx;
        puWeight->FillData(pu);
    }

    // Analyse - MC
    NEntries = mcEvent->GetPEvent()->GetNEntries();
    std::cout << "Looping through MC events" << std::endl;
    while( mcEvent->Next() )
    {
        unsigned position = mcEvent->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        int pu = mcEvent->GetPEvent()->fVertex->nVtx;
        puWeight->FillMC(pu);
    }

    // End
    puWeight->DrawPlots();
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

std::vector<double> bins(int min, int max)
{
    std::vector<double> temp;
    for(int i=min; i<=max; ++i) temp.push_back((double)i);
    return temp;
}
