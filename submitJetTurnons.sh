#!/bin/bash
# run with:
# $ bsub -q 8nh "sh submitTurnons.sh"

cd /afs/cern.ch/work/s/sbreeze/CMSSW_8_0_9/src/
eval `scramv1 runtime -sh`
cmsenv
cd /afs/cern.ch/work/s/sbreeze/l1tClasses/

root -q -b -l "MakePlots/makeJetTurnons.cxx($1,$2,$3,false)"
