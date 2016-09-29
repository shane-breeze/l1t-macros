#ifndef NTUPLE_CFG_H
#define NTUPLE_CFG_H

#include <string>

struct ntuple_cfg {
    std::string sampleName, sampleTitle;
    std::string triggerName, triggerTitle;
    std::string puFilename;     
    std::string run;
    std::string outDirBase;
    bool doFit;
    std::vector<std::string> puType;
    std::vector<int> puBins;
    std::string inFiles;
    std::string baseOWdir;
    std::string outDir;
};

ntuple_cfg singleMuRun276243();
ntuple_cfg VBF_HInv();

// The Ntuple cfg to use:
ntuple_cfg GetNtuple_cfg()
{
    return singleMuRun276243();
}

// Single Muon run 276243
ntuple_cfg singleMuRun276243()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "276243";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v71p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v71p1__278017_SingleMuon"
        "/160809_012632/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20160929_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// VBF H -> Inv
ntuple_cfg VBF_HInv()
{
    ntuple_cfg config;
    config.sampleName = "HInv";
    config.sampleTitle = "VBF H #rightarrow Inv";
    config.triggerName = "";
    config.triggerTitle = "";
    config.puFilename = "/afs/cern.ch/work/s/sbreeze/l1tClasses/PUWeights"
        "/20160719_Data-SingleMu-2016Bv1_VBFHinv/pu_mcReweightedToData.root";
    config.run = "";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums"
        "/160718_MC_VBFHinv125GeV_l1t-int-70p2/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20160728_MC_HInv_highMET/";
    return config;
}

#endif
