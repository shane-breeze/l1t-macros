#!/bin/bash
# run with:
# $ bsub -q 8nh "sh submitTurnons.sh"

cd $CMSSW_BASE/src
eval `scramv1 runtime -sh`
cd -

root -q -b -l "MakePlots/makeJetTurnons.cxx($1,$2,$3,$4)"
