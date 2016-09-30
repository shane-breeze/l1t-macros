#!/bin/bash
# run with:
# $ bsub -q 8nh "sh submitTurnons.sh"

cd /afs/cern.ch/work/s/sbreeze/CMSSW_8_0_9/src/
eval `scramv1 runtime -sh`
cd /afs/cern.ch/work/s/sbreeze/l1tClasses/

root -q -b -l "MakePlots/makeRates.cxx($1,$2,$3,$4)"
