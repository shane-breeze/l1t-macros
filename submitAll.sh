#!/bin/bash
# run with:
# $ bsub -q 8nh "sh submitTurnons.sh"

L1T=/afs/cern.ch/work/s/sbreeze/L1Trigger/pre-201707/l1tClasses
CMSSW_BASE=/afs/cern.ch/work/s/sbreeze/CMSSW_8_0_9
cd $CMSSW_BASE/src
eval `scramv1 runtime -sh`
cd -

root -q -b -l "MakePlots/makeAll.cxx($1,$2,$3,$4)"
