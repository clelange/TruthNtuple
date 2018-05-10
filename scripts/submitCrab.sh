#!/bin/zsh

EVENTSJOB=5000
NJOBS=50
TEMPLATE=crabConfig.py
DATE=`date +'%F'`

for CONFIG in `ls configs/*.py`; do
  CONFIG=`print $CONFIG(:t:r)`
  TAG="93X_mc2017_realistic_v3_qCut19"
  DATASET=${CONFIG}_GEN-SIM
  CONFIGNAME=crabConfig_${DATASET}.py
  cp $TEMPLATE $CONFIGNAME
  sed -i -e "s/CONFIG/$CONFIG/g" $CONFIGNAME
  sed -i -e "s/DATASET/$DATASET/g" $CONFIGNAME
  sed -i -e "s/DATE/$DATE/g" $CONFIGNAME
  sed -i -e "s/EVENTSJOB/$EVENTSJOB/g" $CONFIGNAME
  sed -i -e "s/NJOBS/$NJOBS/g" $CONFIGNAME
  sed -i -e "s/TAG/$TAG/g" $CONFIGNAME
  crab submit -c $CONFIGNAME
done
