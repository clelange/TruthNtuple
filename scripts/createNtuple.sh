#!/usr/bin/env bash

INDIR=/eos/cms/store/user/clange/

# echo $INDIR

LIST=$(find $INDIR -name "*.root" -printf '%h\n' | sort -u | grep qCut19|grep Inf|grep -v failed)

# echo $LIST

for i in $(echo $LIST); do
  FILELIST=$(find $i \( -name "*.root" ! -name "*inLHE*.root" \))
  NAME=$(echo $i | cut -d'/' -f 7-8 | sed 's|/|_|')
  echo $NAME
  # echo $FILELIST | sed 's/ /,/g' | sed 's|/eos|file:/eos|g' > ${NAME}_files.txt
  FILECSV=$(echo $FILELIST | sed 's/ /,/g' | sed 's|/eos|file:/eos|g')
  # echo $FILECSV
  cmsRun Analysis/TruthNtuple/test/runNtuplizer.py inputFiles=${FILECSV} outputFile=ntuples/${NAME}.root maxEvents=-1
done
