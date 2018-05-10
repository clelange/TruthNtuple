#!/usr/bin/env bash

INFILE=one.txt

for i in `cat ${INFILE}`; do
  FILELIST=$(dasgoclient -limit=50 -sep="," -query="file dataset=$i")
  NAME=$(echo $i | cut -d'/' -f 2-3 | sed 's|/|_|')
  # echo $NAME
  # echo $FILELIST | sed 's/ /,/g' | sed 's|/eos|file:/eos|g' > ${NAME}_files.txt
  FILECSV=$(echo $FILELIST | sed 's/ /,/g' | sed 's|/eos|file:/eos|g')
  # echo $FILECSV
  cmsRun Analysis/TruthNtuple/test/runNtuplizer.py inputFiles=${FILECSV} outputFile=ntuples/${NAME}.root maxEvents=100000
  # break
done
