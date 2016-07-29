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

void makeXvsY(const int & SET, const bool & combine)
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

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

    // std::string run = "2016Bv1";
    std::string run = "276525";
    // std::string run = "";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    std::string outDir("");
    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160713_r276243_SingleMu_l1t-int-71p1/");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160718_MC_VBFHinv125GeV_l1t-int-70p2");
    if(!combine)
    {
        std::string files = "root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v71p1/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v71p1__276525_SingleMuon/160713_153738/0000/L1Ntuple_%i.root";
        for(int i=1+(SET*10); i<=10+(SET*10); ++i)
            inDir.push_back(Form(files.c_str(),i));
        // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_MC_"+sampleName+"_highMET/XvsY/";
        outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+Form("_highMET_SET%i/XvsY/",SET);
    }
    else
    {
        // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_MC_"+sampleName+"_highMET/XvsY/";
        outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+"_highMET_hadd/XvsY/";
    }

    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1XvsY*> xvsy;

    std::string baseOWdir = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput/20160728_Data_run-276525_SingleMu_highMET_hadd/XvsY/";

    // caloMetBE vs l1MetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[0]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMetBE_vs_l1MetBE.root","xy_caloMetBE_vs_l1MetBE");
    xvsy[0]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[0]->SetX("caloMetBE","Offline E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[0]->SetY("l1MetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1MetBE");

    // caloMetHF vs l1MetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMetHF_vs_l1MetBE.root","xy_caloMetHF_vs_l1MetBE");
    xvsy[1]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[1]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[1]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[1]->SetY("l1MetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[1]->SetOutName(triggerName+"_caloMetHF_vs_l1MetBE");

    // caloMetHF vs l1MetHF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMetHF_vs_l1MetHF.root","xy_caloMetHF_vs_l1MetHF");
    xvsy[2]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[2]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[2]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[2]->SetY("l1MetHF","L1 E_{T}^{miss} HF (GeV)");
    xvsy[2]->SetOutName(triggerName+"_caloMetHF_vs_l1MetHF");

    // l1MetBE vs recalcL1MetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetOverwriteNames(baseOWdir+"xy_SingleMu_l1MetBE_vs_recalcL1MetBE.root","xy_l1MetBE_vs_recalcL1MetBE");
    xvsy[3]->SetXBins(bins(800.0,10.0,0.0));
    xvsy[3]->SetX("l1MetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[3]->SetYBins(bins(800.0,10.0,0.0));
    xvsy[3]->SetY("recalcL1MetBE","Recalc L1 E_{T}^{miss} BE (GeV)");
    xvsy[3]->SetOutName(triggerName+"_l1MetBE_vs_recalcL1MetBE");

    // caloMetBE Phi vs l1MetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMetPhiBE_vs_l1MetPhiBE.root","xy_caloMetPhiBE_vs_l1MetPhiBE");
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("caloMetPhiBE","Offline E_{T}^{miss} Phi BE");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    xvsy[4]->SetOutName(triggerName+"_caloMetPhiBE_vs_l1MetPhiBE");

    // caloMetHF Phi vs l1MetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMetPhiHF_vs_l1MetPhiBE.root","xy_caloMetPhiHF_vs_l1MetPhiBE");
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    xvsy[5]->SetOutName(triggerName+"_caloMetPhiHF_vs_l1MetPhiBE");

    // caloMetHF Phi vs l1MetHF Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[6]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMetPhiHF_vs_l1MetPhiHF.root","xy_caloMetPhiHF_vs_l1MetPhiHF");
    xvsy[6]->SetXBins(phiBins());
    xvsy[6]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    xvsy[6]->SetYBins(phiBins());
    xvsy[6]->SetY("l1MetPhiHF","L1 E_{T}^{miss} Phi HF");
    xvsy[6]->SetOutName(triggerName+"_caloMetPhiHF_vs_l1MetPhiHF");

    // caloMetBE x vs l1MetBE x
    xvsy.emplace_back(new TL1XvsY());
    xvsy[7]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMexBE_vs_l1MexBE.root","xy_caloMexBE_vs_l1MexBE");
    xvsy[7]->SetXBins(bins(800.0,10.0,-800.0));
    xvsy[7]->SetX("caloMexBE","Offline E_{x}^{miss} BE");
    xvsy[7]->SetYBins(bins(800.0,10.0,-800.0));
    xvsy[7]->SetY("l1MexBE","L1 E_{x}^{miss} BE");
    xvsy[7]->SetOutName(triggerName+"_caloMexBE_vs_l1MexBE");

    // caloMetBE y vs l1MetBE y
    xvsy.emplace_back(new TL1XvsY());
    xvsy[8]->SetOverwriteNames(baseOWdir+"xy_SingleMu_caloMeyBE_vs_l1MeyBE.root","xy_caloMeyBE_vs_l1MeyBE");
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
        if( !combine ) (*it)->InitPlots();
        else (*it)->OverwritePlots();
    }

    unsigned NEntries(0);
    if(!combine) NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() && (!combine) )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        if( triggerName == "SingleMu" )
            if( !event->fMuonFilterPassFlag )
                continue;

        int pu = event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        double l1MetBE = event->fL1Met;
        double l1MetHF = event->fL1MetHF;
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double recalcL1MetBE = event->fRecalcL1Met;

        double l1MetPhiBE = event->fL1MetPhi;
        double l1MetPhiHF = event->fL1MetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;

        double l1MexBE = event->fL1Mex;
        double l1MeyBE = event->fL1Mey;
        double recoMexBE = l1MetBE * TMath::Cos(l1MetPhiBE);
        double recoMeyBE = l1MetBE * TMath::Sin(l1MetPhiBE);

        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            xvsy[0]->Fill(recoMetBE, l1MetBE, pu);
            xvsy[1]->Fill(recoMetHF, l1MetBE, pu);
            xvsy[2]->Fill(recoMetHF, l1MetHF, pu);

            xvsy[3]->Fill(l1MetBE, recalcL1MetBE, pu);

            xvsy[4]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1MetPhiBE), pu);
            xvsy[5]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiBE), pu);
            xvsy[6]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiHF), pu);

            xvsy[7]->Fill(recoMexBE, l1MexBE, pu);
            xvsy[8]->Fill(recoMeyBE, l1MeyBE, pu);
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
