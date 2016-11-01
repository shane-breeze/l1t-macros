#!/bin/bash

SCRIPT=$1
NJOBS=$2
COMB="false"

NEnt="$(root -q -b -l "Scripts/getNEntries.cxx")"
iNEnt="$(echo $NEnt | grep -Po '(?<=NEntries = )[0-9]+')"

echo "================================================================================"
echo "=============================== Submitting jobs! ==============================="
echo "================================================================================"

echo "\"sh $SCRIPT CHUNK $NJOBS $iNEnt $COMB\""
for i in `seq 0 $(($NJOBS-1))`; do
    echo -n "Job $i: "
    bsub -q 8nm -eo /dev/null -oo /dev/null "sh $SCRIPT $i $NJOBS $iNEnt $COMB"
    #bsub -q 8nm "sh $SCRIPT $i $NJOBS $iNEnt $COMB"
done
