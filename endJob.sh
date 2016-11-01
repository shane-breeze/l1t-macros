#!/bin/bash

SCRIPT=$1
NJOBS=1
COMB="true"

iNEnt=1
i=0
sh $SCRIPT $i $NJOBS $iNEnt $COMB
