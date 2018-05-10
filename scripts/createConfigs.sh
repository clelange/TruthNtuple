#!/usr/bin/env bash
for i in `ls Configuration/GenProduction/python/*.py |grep -v __ |grep -v RunII`; do
  FRAG=`basename $i`
  cmsDriver.py Configuration/GenProduction/python/${FRAG} --fileout file:${FRAG%.py}.root --mc --eventcontent RAWSIM,LHE --datatier GEN-SIM,LHE --conditions 93X_mc2017_realistic_v3 --beamspot Realistic25ns13TeVEarly2017Collision --step LHE,GEN,SIM --nThreads 4 --geometry DB:Extended --era Run2_2017 --python_filename configs/${FRAG} --customise Configuration/DataProcessing/Utils.addMonitoring --no_exec
done
