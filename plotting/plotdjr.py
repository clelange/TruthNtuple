#!/usr/bin/env python
from ROOT import TFile, TTree, TH1D, TCanvas, TCut, TPad, TChain, TLegend, TString, TPad, gSystem, gStyle, AutoLibraryLoader
import os
import sys


c1 = TCanvas("c1", "c1", 800, 600)
hists = []

def setcanvas(c1, pad):

    c1.SetLeftMargin(0.0)
    c1.SetTopMargin(0.00)
    c1.SetRightMargin(0.00)
    c1.SetBottomMargin(0.0)

    pad[0] = TPad("pad0", "pad", 0, 0.67, 0.5, 1.0)
    pad[1] = TPad("pad1", "pad", 0.5, 0.67, 1.0, 1.0)
    pad[2] = TPad("pad2", "pad", 0, 0.33, 0.5, 0.67)
    pad[3] = TPad("pad3", "pad", 0.5, 0.33, 1.0, 0.67)
    pad[4] = TPad("pad4", "pad", 0., 0., 0.5, 0.33)
    for k in range(5):
        pad[k].Draw()


def setlegend(legend, hall, hmult0, hmult1, hmult2, hmult3, hmult4):

    legend.SetTextSize(0.050)
    legend.SetBorderSize(0)
    legend.SetTextFont(62)
    legend.SetLineColor(0)
    legend.SetLineStyle(1)
    legend.SetLineWidth(1)
    legend.SetFillColor(0)
    legend.SetFillStyle(1001)

    legend.AddEntry(hall, "all partons")
    legend.AddEntry(hmult0, "0 partons")
    legend.AddEntry(hmult1, "1 parton")
    legend.AddEntry(hmult2, "2 partons")
    legend.AddEntry(hmult3, "3 partons")
    legend.AddEntry(hmult4, "4 partons")


def makeplot(name, pad, tree, weight, drawstring, xlabel, nbins, xlow, xhigh, typeMC):

    pad.cd()
    multCuts = []
    multHists = []
    colours = [600, 629, 419, 810, 90]
    cuts = [
            "LHEEvent.npNLO()",
            "GenEvent.nMEPartons()",
            "GenEvent.nMEPartonsFiltered()"
           ]
    for m in range(5):
        multCuts.append(TCut("%s==%d" % (cuts[typeMC], m)))
    for m in range(5):
        multHists.append(TH1D("hmult%d_%s" % (m, name), "", nbins, xlow, xhigh))
        multHists[m].SetLineColor(colours[m])
        multHists[m].SetLineStyle(2)

    hall = TH1D("hall_%s" % name, "", nbins, xlow, xhigh)
    hall.SetLineColor(921)
    hall.SetLineWidth(2)

    tree.Draw("%s>>%s" % (drawstring, hall.GetName()), weight, "goff")

    for m in range(5):
        tree.Draw("%s>>%s" % (drawstring, multHists[m].GetName()), weight * multCuts[m], "goff")

    hall.GetXaxis().SetTitle(xlabel)

    legend = TLegend(0.67, 0.87 - 4 * 0.06, 0.87, 0.87)
    setlegend(legend, hall, multHists[0], multHists[1], multHists[2], multHists[3], multHists[4])

    hall.Draw("EHIST")
    for m in range(5):
        multHists[m].Draw("EHISTSAME")
    legend.Draw()

    return hall, multHists


def plotdjr(infile, outfile):

    TH1D.SetDefaultSumw2()

    tree = TChain("Events")
    # tree.Add(infile)
    for filename in fileList:
        tree.Add(filename)

    tree.SetAlias("GenEvent", "GenEventInfoProduct_generator__SIM.obj")
    tree.SetAlias("LHEEvent", "LHEEventProduct_externalLHEProducer__SIM.obj")

    weight = TCut("GenEvent.weight()")
    nbins = 50
    djrmin = -0.5
    djrmax = 3.
    # typeMC sets the kind of sample we are looking at:
    # 0 is for NLO with FXFX merging
    # 1 is for LO with MLM
    # 2 is for LO with MLM (plotting partons after excluding non-matched partons in wbb/vbf type processes)
    typeMC = 2

    pad = [None]*5
    setcanvas(c1, pad)
    gStyle.SetOptStat(0)

    histos = []
    histosAll = []
    xlabels = ["DJR 0.1", "DJR 1.2", "DJR 2.3", "DJR 3.4", "DJR 4.5"]

    for m in range(5):
        hall, h = makeplot("djr%d" % m, pad[m], tree, weight,
                         "log10(GenEvent.DJRValues_[%d])" %m, xlabels[m], nbins, djrmin, djrmax, typeMC)
        histos.append(h)
        histosAll.append(hall)

    c1.Print(outfile)
    c1.SaveAs(outfile.replace("root", "png"))
    c1.SaveAs(outfile.replace("root", "pdf"))


if __name__ == '__main__':
    rootDir = "/eos/cms/store/user/clange/"
    maxFiles = 1000
    samples = {}
    gSystem.Load("libFWCoreFWLite.so")
    AutoLibraryLoader.enable()
    for dirName, subdirList, fileList in os.walk(rootDir):
        if dirName.find('failed') >= 0:
            continue
        # print 'Found directory: %s' % dirName
        goodFiles = list(filter(lambda filename: filename.endswith(".root") and (filename.find("inLHE") < 0), fileList))
        if goodFiles:
            sample = "_".join(dirName.split("/")[rootDir.count("/"):rootDir.count("/")+2])
            samples[sample] = [os.path.join(dirName, filename) for filename in goodFiles[:maxFiles]]
    for sample, fileList in samples.iteritems():
        c1.Clear()
        c1.cd()
        print "Analysing", len(fileList), "files for", sample
        outFile = sample + ".root"
        plotdjr(fileList, outFile)

    # if len(sys.argv) < 2:
    #     print "please provide input directory"
    # directory = sys.argv[1]
    # fileList = []
    # maxFiles = 1000
    # for filename in os.listdir(directory):
    #     if filename.endswith(".root") and (filename.find("inLHE") < 0):
    #         fileList.append(os.path.join(directory, filename))
    #         if len(fileList) == maxFiles:
    #             break
    # sample = "_".join(directory.split("/")[6:8])
