#include <string>
#include <vector>
#include <algorithm>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Utilities/TL1DateTime.C"
#include "../Plotting/TL1XvsY.h"

std::vector<double> bins(double max, double width, double min);
std::vector<double> phiBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void makeXvsY()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Basic
    // std::string sampleName = "Data";
    // std::string sampleTitle = "2016 Data";
    // std::string triggerName = "SingleMu";
    // std::string triggerTitle = "Single Muon";
    std::string sampleName = "HInv";
    std::string sampleTitle = "VBF H #rightarrow Inv";
    std::string triggerName = "";
    std::string triggerTitle = "";
    std::string puFilename = "/afs/cern.ch/work/s/sbreeze/l1tClasses/PUWeights/20160719_Data-SingleMu-2016Bv1_VBFHinv/pu_mcReweightedToData.root";

    // std::string run = "2016Bv1";
    std::string run = "";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160713_r276243_SingleMu_l1t-int-71p1/");
    inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160718_MC_VBFHinv125GeV_l1t-int-70p2");

    // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+"_MET+HF/xy/";
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_MC_"+sampleName+"_highMET/xy/";
    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1XvsY*> xvsy;

    // caloMetBE vs l1EmuMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[0]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[0]->SetX("caloMetBE","Offline E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[0]->SetY("l1EmuMetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1EmuMetBE");

    // caloMetHF vs l1EmuMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[1]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[1]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[1]->SetY("l1EmuMetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[1]->SetOutName(triggerName+"_caloMetHF_vs_l1EmuMetBE");

    // caloMetHF vs l1EmuMetHF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[2]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[2]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[2]->SetY("l1EmuMetHF","L1 E_{T}^{miss} HF (GeV)");
    xvsy[2]->SetOutName(triggerName+"_caloMetHF_vs_l1EmuMetHF");

    // l1MetBE vs recalcL1MetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[3]->SetX("l1MetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[3]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[3]->SetY("recalcL1MetBE","Recalc L1 E_{T}^{miss} BE (GeV)");
    xvsy[3]->SetOutName(triggerName+"_l1MetBE_vs_recalcL1MetBE");

    // caloMetBE Phi vs l1EmuMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("caloMetPhiBE","Offline E_{T}^{miss} Phi BE");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    xvsy[4]->SetOutName(triggerName+"_caloMetPhiBE_vs_l1MetPhiBE");

    // caloMetHF Phi vs l1EmuMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    xvsy[5]->SetOutName(triggerName+"_caloMetPhiHF_vs_l1MetPhiBE");

    // caloMetHF Phi vs l1EmuMetHF Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[6]->SetXBins(phiBins());
    xvsy[6]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    xvsy[6]->SetYBins(phiBins());
    xvsy[6]->SetY("l1MetPhiHF","L1 E_{T}^{miss} Phi HF");
    xvsy[6]->SetOutName(triggerName+"_caloMetPhiHF_vs_l1MetPhiHF");

    // caloMetBE x vs l1EmuMetBE x
    xvsy.emplace_back(new TL1XvsY());
    xvsy[7]->SetXBins(bins(800.0,10.0,-800.0));
    xvsy[7]->SetX("caloMexBE","Offline E_{x}^{miss} BE");
    xvsy[7]->SetYBins(bins(800.0,10.0,-800.0));
    xvsy[7]->SetY("l1MexBE","L1 E_{x}^{miss} BE");
    xvsy[7]->SetOutName(triggerName+"_caloMexBE_vs_l1MexBE");

    // caloMetBE y vs l1EmuMetBE y
    xvsy.emplace_back(new TL1XvsY());
    xvsy[8]->SetXBins(bins(800.0,10.0,-800.0));
    xvsy[8]->SetX("caloMeyBE","Offline E_{y}^{miss} BE");
    xvsy[8]->SetYBins(bins(800.0,10.0,-800.0));
    xvsy[8]->SetY("l1MeyBE","L1 E_{y}^{miss} BE");
    xvsy[8]->SetOutName(triggerName+"_caloMeyBE_vs_l1MeyBE");

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
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
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double recalcL1MetBE = event->fRecalcL1EmuMet;

        double l1EmuMetPhiBE = event->fL1EmuMetPhi;
        double l1EmuMetPhiHF = event->fL1EmuMetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;

        double l1EmuMexBE = event->fL1EmuMex;
        double l1EmuMeyBE = event->fL1EmuMey;
        double recoMexBE = l1EmuMetBE * TMath::Cos(l1EmuMetPhiBE);
        double recoMeyBE = l1EmuMetBE * TMath::Sin(l1EmuMetPhiBE);

        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            xvsy[0]->Fill(recoMetBE, l1EmuMetBE, pu);
            xvsy[1]->Fill(recoMetHF, l1EmuMetBE, pu);
            xvsy[2]->Fill(recoMetHF, l1EmuMetHF, pu);

            xvsy[3]->Fill(l1EmuMetBE, recalcL1MetBE, pu);

            xvsy[4]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1EmuMetPhiBE), pu);
            xvsy[5]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1EmuMetPhiBE), pu);
            xvsy[6]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1EmuMetPhiHF), pu);

            xvsy[7]->Fill(recoMexBE, l1EmuMexBE, pu);
            xvsy[8]->Fill(recoMeyBE, l1EmuMeyBE, pu);
        }
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
