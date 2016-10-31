#!/bin/bash
# run with:
# $ bsub -q 8nh "sh submitTurnons.sh"

if [ -z ${L1T} ]; then
    echo "\$L1T is unset";
else
    cd $L1T;
fi

cd $CMSSW_BASE/src
eval `scramv1 runtime -sh`
cd -

root -q -b -l "MakePlots/makeXvsY.cxx($1,$2,$3)"
