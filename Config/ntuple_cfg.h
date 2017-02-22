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
ntuple_cfg zeroBiasRun276653();
ntuple_cfg VBF_HInv();
ntuple_cfg benchmark_cfg();

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


ntuple_cfg benchmark_cfg()
{
  ntuple_cfg config;
  config.sampleName   = "Data";
  config.sampleTitle  = "2016 Data";
  config.triggerName  = "SingleMu";
  config.triggerTitle = "Single Muon";
  config.puFilename   = "";
  config.run          = "276243";
  config.outDirBase   = "/vagrant/benchmark/legacy";
  config.doFit        = false;
  config.puType       = {"0PU12","13PU19","20PU"};
  config.puBins       = {0,13,20,999};
  config.inFiles      = {"file:///vagrant/data/*.root"};
  config.baseOWdir    = config.outDirBase +
      "/20161101_"+config.sampleName+"_run-"+config.run+"_"+\
      config.triggerName+"_hadd/";
  config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
  config.sampleName+"_run-"+config.run+"_"+config.triggerName;
  return config;
}

#endif
