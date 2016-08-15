#include <string>
#include <vector>

#include "../Plotting/tdrstyle.C"
#include "../Event/TL1EventClass.h"
#include "../Utilities/TL1Progress.C"
#include "../Utilities/TL1DateTime.C"
#include "../Plotting/TL1Resolution.h"

std::vector<double> bins(std::string plotType);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void makeResolutions(const int & SET, const bool & combine)
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

    // std::string run = "2016Bv1";
    // std::string run = "";
    std::string run = "276525";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    std::string outDir("");
    std::vector<std::string> inDir;
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160713_r276243_SingleMu_l1t-int-71p1/");
    // inDir.push_back("/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160718_MC_VBFHinv125GeV_l1t-int-70p2");
    if(!combine)
    {
        std::string files = "root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v71p1/SingleMuon/crab_Collision2016-wRECO-l1t-integration-v71p1__276525_SingleMuon/160713_153738/0000/L1Ntuple_%i.root";
        for(int i=1+(SET*10); i<=10+(SET*10); ++i)
            inDir.push_back(Form(files.c_str(),i));
        // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_MC_"+sampleName+"_highMET/Resolution/";
        outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+Form("_highMET_SET%i/Resolution/",SET);
    }
    else
    {
        // std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_MC_"+sampleName+"_highMET/Resolution/";
        outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sampleName+"_"+"run-"+run+"_"+triggerName+"_highMET_hadd/Resolution/";
    }
    
    TL1EventClass * event(new TL1EventClass(inDir));
    std::vector<TL1Resolution*> resolution;

    std::string baseOWdir = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput/20160729_Data_run-276525_SingleMu_highMET_hadd/Turnons/";

    // caloMetBE vs l1MetBE
    resolution.emplace_back(new TL1Resolution());
    if(combine) resolution[0]->SetOverwriteNames(baseOWdir+"res_SingleMu_diff_caloMetBE_l1MetBE.root","res_diff_caloMetBE_vs_l1MetBE");
    resolution[0]->SetPlotType("Energy");
    resolution[0]->SetBins(bins("Energy"));
    resolution[0]->SetX("caloMetBE","Offline E_{T}^{miss} BE");
    resolution[0]->SetY("l1MetBE","L1 E_{T}^{miss} BE");
    resolution[0]->SetOutName(triggerName+"_diff_caloMetBE_l1MetBE");
    resolution[0]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetHF vs l1MetBE
    resolution.emplace_back(new TL1Resolution());
    if(combine) resolution[1]->SetOverwriteNames(baseOWdir+"res_SingleMu_diff_caloMetHF_l1MetBE.root","res_diff_caloMetHF_vs_l1MetBE");
    resolution[1]->SetPlotType("Energy");
    resolution[1]->SetBins(bins("Energy"));
    resolution[1]->SetX("caloMetHF","Offline E_{T}^{miss} HF");
    resolution[1]->SetY("l1MetBE","L1 E_{T}^{miss} BE");
    resolution[1]->SetOutName(triggerName+"_diff_caloMetHF_l1MetBE");
    resolution[1]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetHF vs l1MetHF
    resolution.emplace_back(new TL1Resolution());
    if(combine) resolution[2]->SetOverwriteNames(baseOWdir+"res_SingleMu_diff_caloMetHF_l1MetHF.root","res_diff_caloMetHF_vs_l1MetHF");
    resolution[2]->SetPlotType("Energy");
    resolution[2]->SetBins(bins("Energy"));
    resolution[2]->SetX("caloMetHF","Offline E_{T}^{miss} HF");
    resolution[2]->SetY("l1MetHF","L1 E_{T}^{miss} HF");
    resolution[2]->SetOutName(triggerName+"_diff_caloMetHF_l1MetHF");
    resolution[2]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetPhiBE vs l1MetPhiBE
    resolution.emplace_back(new TL1Resolution());
    if(combine) resolution[3]->SetOverwriteNames(baseOWdir+"res_SingleMu_diff_caloMetPhiBE_l1MetPhiBE.root","res_diff_caloMetPhiBE_vs_l1MetPhiBE");
    resolution[3]->SetPlotType("Position");
    resolution[3]->SetBins(bins("Position"));
    resolution[3]->SetX("caloMetPhiBE","Offline E_{T}^{miss} Phi BE");
    resolution[3]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    resolution[3]->SetOutName(triggerName+"_diff_caloMetPhiBE_l1MetPhiBE");
    resolution[3]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetPhiHF vs l1MetPhiBE
    resolution.emplace_back(new TL1Resolution());
    if(combine) resolution[4]->SetOverwriteNames(baseOWdir+"res_SingleMu_diff_caloMetPhiHF_l1MetPhiBE.root","res_diff_caloMetPhiHF_vs_l1MetPhiBE");
    resolution[4]->SetPlotType("Position");
    resolution[4]->SetBins(bins("Position"));
    resolution[4]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    resolution[4]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    resolution[4]->SetOutName(triggerName+"_diff_caloMetPhiHF_l1MetPhiBE");
    resolution[4]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetPhiHF vs l1MetPhiHF
    resolution.emplace_back(new TL1Resolution());
    if(combine) resolution[5]->SetOverwriteNames(baseOWdir+"res_SingleMu_diff_caloMetPhiHF_l1MetPhiHF.root","res_diff_caloMetPhiHF_vs_l1MetPhiHF");
    resolution[5]->SetPlotType("Position");
    resolution[5]->SetBins(bins("Position"));
    resolution[5]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    resolution[5]->SetY("l1MetPhiHF","L1 E_{T}^{miss} Phi HF");
    resolution[5]->SetOutName(triggerName+"_diff_caloMetPhiHF_l1MetPhiHF");
    resolution[5]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
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

        // MET
        double l1MetBE = event->fL1Met;
        double l1MetHF = event->fL1MetHF;
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double l1MetPhiBE = event->fL1MetPhi;
        double l1MetPhiHF = event->fL1MetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;

        if( event->fMetFilterPassFlag )
        {
            if( recoMetBE > 40.0 && l1MetBE > 0.0 )
            {
                resolution[0]->Fill(recoMetBE, l1MetBE, pu);
                resolution[3]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1MetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1MetBE > 0.0 )
            {
                resolution[1]->Fill(recoMetHF, l1MetBE, pu);
                resolution[4]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1MetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1MetHF > 0.0 )
            {
                resolution[2]->Fill(recoMetHF, l1MetHF, pu);
                resolution[5]->Fill(recoMetPhiHF, l1MetPhiHF, pu);
            }
        }
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
