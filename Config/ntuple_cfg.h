#ifndef NTUPLE_CFG_H
#define NTUPLE_CFG_H

#include <string>

#include "../Utilities/TL1DateTime.h"

struct ntuple_cfg {
    std::string sampleName, sampleTitle;
    std::string triggerName, triggerTitle;
    std::string puFilename;     
    std::string run;
    std::string outDirBase;
    bool doFit;
    std::vector<std::string> puType;
    std::vector<int> puBins;
    std::vector<std::string> inFiles;
    std::string baseOWdir;
    std::string outDir;
};

ntuple_cfg singleMuRun276243();
ntuple_cfg singleMuRun281693();
ntuple_cfg singleMuRun283877();
ntuple_cfg singleMuRun284043();
ntuple_cfg zeroBiasRun276653();
ntuple_cfg VBF_HInv();
ntuple_cfg singleMuRun2017B();
ntuple_cfg singleMuRun297604();
ntuple_cfg singleMuRun299329();
ntuple_cfg singleMuRun303948();

// The Ntuple cfg to use:
ntuple_cfg GetNtuple_cfg()
{
    return singleMuRun303948();
}

// Single Muon run 283877
ntuple_cfg singleMuRun283877()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "283877";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = {"root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v88p0/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v88p0__283877_SingleMuon"
        "/161028_163709/0000/L1Ntuple_*.root"};
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161101_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
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
    config.inFiles      = {"root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v71p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v71p1__278017_SingleMuon"
        "/160809_012632/0000/L1Ntuple_*.root"};
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161101_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281693
ntuple_cfg  singleMuRun281693()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281693";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = {"root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v86p4/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v86p4__281693_SingleMuon"
        "/161005_194247/0000/L1Ntuple_*.root"};
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161101_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 284043
ntuple_cfg  singleMuRun284043()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "284043";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = {"root://eoscms.cern.ch//eos/cms/store/group/"
        "dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/"
        "Collision2016-wRECO-l1t-integration-v88p0/SingleMuon/"
        "crab_Collision2016-wRECO-l1t-integration-v88p0__284043_SingleMuon/"
        "161102_014359/0000/L1Ntuple_*.root"};
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161111_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Zero Bias run 276653
ntuple_cfg zeroBiasRun276653()
{
    ntuple_cfg config;
    config.sampleName = "Data";
    config.sampleTitle = "2016 Data";
    config.triggerName = "ZeroBias";
    config.triggerTitle = "Zero Bias";
    config.puFilename = "";
    config.run = "276653";
    config.outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit = false;
    config.puType = {"0PU"};
    config.puBins = {0,999};
    config.inFiles = {"/afs/cern.ch/work/s/sbreeze/public/jets_and_sums"
        "/160717_r276653_ZeroBias_l1t-int-71p1/L1Ntuple_*.root"};
    config.baseOWdir = config.outDirBase+"/20161101_"+config.sampleName+\
        "_run-"+config.run+"_"+config.triggerName+"_hadd/";
    config.outDir = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
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
    config.inFiles      = {"/afs/cern.ch/work/s/sbreeze/public/jets_and_sums"
        "/160718_MC_VBFHinv125GeV_l1t-int-70p2/L1Ntuple_*.root"};
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161102_MC_HInv_highMET/";
    return config;
}

ntuple_cfg singleMuRun2017B()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "Run2017B";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = {"root://eoscms.cern.ch//eos/cms/store/group/"
        "dpg_trigger/comm_trigger/L1Trigger/safarzad/2017/"
        "Collision2017-wRECO-l1t-integration-v96p8_updatedHFSF/SingleMuon/"
        "crab_Collision2017-wRECO-l1t-integration-v96p8_updatedHFSF__SingleMuon/"
        "170703_072652/0000/L1Ntuple_*.root",
        "root://eoscms.cern.ch//eos/cms/store/group/"
        "dpg_trigger/comm_trigger/L1Trigger/safarzad/2017/"
        "Collision2017-wRECO-l1t-integration-v96p8_updatedHFSF/SingleMuon/"
        "crab_Collision2017-wRECO-l1t-integration-v96p8_updatedHFSF__SingleMuon/"
        "170703_072652/0001/L1Ntuple_*.root"
    };
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput"
        "/20170712_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

ntuple_cfg singleMuRun297604()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "297604";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU"};
    config.puBins       = {0,999};
    config.inFiles      = {"/afs/cern.ch/work/s/sbreeze/L1Trigger/Ntuples/"
        "201707_Jul/21_investigateRun297604/"
        "l1Ntuples2017_CMSSW925-patch2_l1t-int-v96p20/"
        "crab_l1Ntuples2017_CMSSW925-patch2_l1t-int-v96p20/results/"
        "L1Ntuple_*.root"
    };
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput"
        "/20170723_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

ntuple_cfg singleMuRun299329()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "299329";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU"};
    config.puBins       = {0,999};
    config.inFiles      = {"/afs/cern.ch/work/s/sbreeze/L1Trigger/Ntuples/"
        "201707_Jul/25_investigateRun299329/"
        "l1Ntuples2017_CMSSW925-patch2_l1t-int-v96p20/"
        "crab_l1Ntuples2017_CMSSW925-patch2_l1t-int-v96p20/results/"
        "L1Ntuple_*.root"
    };
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput"
        "/20170726_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

ntuple_cfg singleMuRun303948()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2017 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "303948";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU"};
    config.puBins       = {0,999};
    config.inFiles      = {"/eos/cms/store/group/dpg_trigger/comm_trigger/"
        "L1Trigger/bundocka/SingleMuon/303948sm/171005_073310/0000/L1Ntuple_*.root"
    };
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/L1TriggerStudiesOutput"
        "/20171012_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

#endif
