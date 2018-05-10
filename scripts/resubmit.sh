#!/bin/zsh

for i in `ls crab_projects/|grep 04-18`; do
  echo $i
  crab status -d crab_projects/$i
  crab resubmit -d crab_projects/$i
done
