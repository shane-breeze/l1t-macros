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
    std::vector<std::string> inFiles;
    std::string baseOWdir;
    std::string outDir;
};

ntuple_cfg singleMuRun281693_281797_281976();
ntuple_cfg TTbarMC_13TeV_powheg_pythia8();

// The Ntuple cfg to use:
ntuple_cfg GetNtuple_cfg()
{
    return TTbarMC_13TeV_powheg_pythia8();
}

// Single Muon run 281693+281797+281976
ntuple_cfg singleMuRun281693_281797_281976()
{
    ntuple_cfg config;
    string basedir      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon";
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281693_281797_281976";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = {
        basedir+"/crab_Collision2016-wRECO-l1t-integration-v87p1__281693_SingleMuon/161006_170018/0000/L1Ntuple_*.root",
        basedir+"/crab_Collision2016-wRECO-l1t-integration-v87p1__281693_SingleMuon/161006_170018/0001/L1Ntuple_*.root",
        basedir+"/crab_Collision2016-wRECO-l1t-integration-v87p1__281797_SingleMuon/161006_165951/0000/L1Ntuple_*.root",
        basedir+"/crab_Collision2016-wRECO-l1t-integration-v87p1__281797_SingleMuon/161006_165951/0001/L1Ntuple_*.root",
        basedir+"/crab_Collision2016-wRECO-l1t-integration-v87p1__281976_SingleMuon/161006_165426/0000/L1Ntuple_*.root",
        basedir+"/crab_Collision2016-wRECO-l1t-integration-v87p1__281976_SingleMuon/161006_165426/0001/L1Ntuple_*.root"
    };
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161029_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// TTbar MC
ntuple_cfg TTbarMC_13TeV_powheg_pythia8()
{
    ntuple_cfg config;
    config.sampleName   = "TTbar";
    config.sampleTitle  = "TTbar";
    config.triggerName  = "";
    config.triggerTitle = "";
    config.puFilename   = "";
    config.run          = "";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {};
    config.puBins       = {};
    config.inFiles      = {
        "root://eoscms.cern.ch//eos/cms/store/group/dpg_trigger/comm_trigger/"
        "L1Trigger/L1Menu2016/Stage2/l1t-integration-v86p4-CMSSW-8019/"
        "TT_TuneCUETP8M1_13TeV-powheg-pythia8/"
        "crab_l1t-integration-v86p4-CMSSW-8019__TT_FlatPU20To70_13TeV/"
        "160927_211602/0000/L1Ntuple_*.root"
    };
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161031_"+config.sampleName+"_MC_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_MC";
    return config;
}

#endif
