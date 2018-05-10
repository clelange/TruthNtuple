#!/usr/bin/env python
import ROOT
import sys
import os

directory = sys.argv[1]

print directory

for filename in os.listdir(directory):
    if filename.endswith(".root"):
        this_file = ROOT.TFile(os.path.join(directory, filename))
        if this_file.IsZombie():
            print filename, "is Zombie"
        if this_file.TestBit(ROOT.TFile.kRecovered):
            print filename, "is recovered"
