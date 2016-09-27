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
};

ntuple_cfg singleMuRun276243();
ntuple_cfg VBF_HInv();

ntuple_cfg GetNtuple_cfg();

#endif
