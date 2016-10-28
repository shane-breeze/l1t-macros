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

ntuple_cfg singleMuRun281613(); // 1-426
ntuple_cfg singleMuRun281616(); // 1-223
ntuple_cfg singleMuRun281638(); // 1-2
ntuple_cfg singleMuRun281639(); // 1-66
ntuple_cfg singleMuRun281641(); // 1-165
ntuple_cfg singleMuRun281663(); // 1-52
ntuple_cfg singleMuRun281674(); // 1-19
ntuple_cfg singleMuRun281680(); // 1-15
ntuple_cfg singleMuRun281686(); // 1-9
ntuple_cfg singleMuRun281689(); // 1-2
ntuple_cfg singleMuRun281691(); // 1-7
ntuple_cfg singleMuRun281693_1(); // 1-999
ntuple_cfg singleMuRun281693_2(); // 1000-1099
ntuple_cfg singleMuRun281707(); // 1-509
ntuple_cfg singleMuRun281726(); // 1-144
ntuple_cfg singleMuRun281727(); // 1-807
ntuple_cfg singleMuRun281797_1(); // 1-999
ntuple_cfg singleMuRun281797_2(); // 1000-1063
ntuple_cfg singleMuRun281975(); // 1-108
ntuple_cfg singleMuRun281976_1(); // 1-999
ntuple_cfg singleMuRun281976_2(); // 1000-1088
ntuple_cfg singleMuRun282033(); // 1-42
ntuple_cfg singleMuRun282034(); // 1-16
ntuple_cfg singleMuRun282035(); // 1-20
ntuple_cfg singleMuRun282037(); // 1-934
ntuple_cfg singleMuRun281693_281797_281976();

// The Ntuple cfg to use:
ntuple_cfg GetNtuple_cfg()
{
    return singleMuRun281693_281797_281976();
}

// Single Muon run 281613
ntuple_cfg singleMuRun281613()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281613";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281613_SingleMuon"
        "/161006_165805/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281616
ntuple_cfg singleMuRun281616()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281616";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281616_SingleMuon"
        "/161006_165230/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281638
ntuple_cfg singleMuRun281638()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281638";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281638_SingleMuon"
        "/161006_165456/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281639
ntuple_cfg singleMuRun281639()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281639";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281639_SingleMuon"
        "/161006_165739/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281641
ntuple_cfg singleMuRun281641()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281641";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281641_SingleMuon"
        "/161006_170131/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281663
ntuple_cfg singleMuRun281663()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281663";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281663_SingleMuon"
        "/161006_165831/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281674
ntuple_cfg singleMuRun281674()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281674";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281674_SingleMuon"
        "/161006_165712/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281680
ntuple_cfg singleMuRun281680()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281680";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281680_SingleMuon"
        "/161006_165646/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281686
ntuple_cfg singleMuRun281686()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281686";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281686_SingleMuon"
        "/161006_165618/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281689
ntuple_cfg singleMuRun281689()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281689";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281689_SingleMuon"
        "/161006_165323/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281691
ntuple_cfg singleMuRun281691()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281691";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281691_SingleMuon"
        "/161006_165900/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281693_1
ntuple_cfg singleMuRun281693_1()
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
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281693_SingleMuon"
        "/161006_170018/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281693_2
ntuple_cfg singleMuRun281693_2()
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
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281693_SingleMuon"
        "/161006_170018/0001/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281707
ntuple_cfg singleMuRun281707()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281707";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281707_SingleMuon"
        "/161006_165256/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281726
ntuple_cfg singleMuRun281726()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281726";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281726_SingleMuon"
        "/161006_170201/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281727
ntuple_cfg singleMuRun281727()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281727";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281727_SingleMuon"
        "/161006_165522/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281797_1
ntuple_cfg singleMuRun281797_1()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281797";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281797_SingleMuon"
        "/161006_165951/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281797_2
ntuple_cfg singleMuRun281797_2()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281797";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281797_SingleMuon"
        "/161006_165951/0001/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281975
ntuple_cfg singleMuRun281975()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281975";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281975_SingleMuon"
        "/161006_165549/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281976_1
ntuple_cfg singleMuRun281976_1()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281976";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281976_SingleMuon"
        "/161006_165426/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281976_2
ntuple_cfg singleMuRun281976_2()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "281976";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__281976_SingleMuon"
        "/161006_165426/0001/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 282033
ntuple_cfg singleMuRun282033()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "282033";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__282033_SingleMuon"
        "/161006_165356/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 282034
ntuple_cfg singleMuRun282034()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "282034";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__282034_SingleMuon"
        "/161006_170045/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 282035
ntuple_cfg singleMuRun282035()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "282035";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__282035_SingleMuon"
        "/161006_170230/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 282037
ntuple_cfg singleMuRun282037()
{
    ntuple_cfg config;
    config.sampleName   = "Data";
    config.sampleTitle  = "2016 Data";
    config.triggerName  = "SingleMu";
    config.triggerTitle = "Single Muon";
    config.puFilename   = "";
    config.run          = "282037";
    config.outDirBase   = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    config.doFit        = false;
    config.puType       = {"0PU12","13PU19","20PU"};
    config.puBins       = {0,13,20,999};
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__282037_SingleMuon"
        "/161006_165926/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

// Single Muon run 281693+281797+281976
ntuple_cfg singleMuRun281693_281797_281976()
{
    ntuple_cfg config;
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
    config.inFiles      = "root://eoscms.cern.ch//eos/cms/store/group"
        "/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2"
        "/Collision2016-wRECO-l1t-integration-v87p1/SingleMuon"
        "/crab_Collision2016-wRECO-l1t-integration-v87p1__282037_SingleMuon"
        "/161006_165926/0000/L1Ntuple_%i.root";
    config.baseOWdir    = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput"
        "/20161028_"+config.sampleName+"_run-"+config.run+"_"+\
        config.triggerName+"_hadd/";
    config.outDir       = config.outDirBase+"/"+TL1DateTime::GetDate()+"_"+\
        config.sampleName+"_run-"+config.run+"_"+config.triggerName;
    return config;
}

#endif
