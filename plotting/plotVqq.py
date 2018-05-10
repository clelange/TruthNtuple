#!/usr/bin/env python
"""Control plots from truth ntuple at particle/gen level."""
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals
import os
import configparser
import ROOT


ROOT.gROOT.SetBatch(True)
OUTDIR = "plots"


def main():
    """only one function."""

    plot_sets = configparser.ConfigParser()
    plot_sets.read('plots.ini')

    groups = {}
    if not os.path.exists(OUTDIR):
        os.makedirs(OUTDIR)
    for filename in os.listdir(os.getcwd()):
        if filename.endswith(".root"):
            print(filename)
            short_name = "_".join(filename.split("_")[:2])
            if short_name not in groups.keys():
                groups[short_name] = []
            groups[short_name].append(filename)

    # loop over groups
    for group, samples in groups.items():
        print(group, ": ", len(samples))
        trees = {}
        in_files = {}
        hists = {}
        statbox = {}
        # loop over individual samples to get TTrees
        for sample in samples:
            print(sample)
            identifier = "MLM"
            if sample.find("94X") >= 0:
                identifier = "no_matching"
            sample_file = ROOT.TFile.Open(sample)
            in_files[identifier] = sample_file
            trees[identifier] = sample_file.Get("ntuplizer/tree")
            hists[identifier] = None
            statbox[identifier] = None

        # loop over plots
        for plot_name in plot_sets.sections():
            print(plot_sets[plot_name])
            drawn = False
            c1 = ROOT.TCanvas("c1", "c1", 800, 600)
            c1.Clear()
            legend = ROOT.TLegend(0.7, 0.75, 0.9, 0.9)
            # legend.SetBorderSize(0)
            for identifier in trees:
                trees[identifier].Draw("{variable}>>h{id}({binning})".format(
                    variable=plot_sets[plot_name]['variable'], id=identifier, binning=plot_sets[plot_name]['binning']), plot_sets[plot_name]['cuts'])
                hists[identifier] = ROOT.gDirectory.Get(
                    "h%s" % identifier).Clone("%s" % identifier)
                legend.AddEntry(hists[identifier], identifier.replace("_", " "), "l")
                hists[identifier].Scale(1. / hists[identifier].GetEntries())
                hists[identifier].Draw()
                ROOT.gPad.Update()
                statbox[identifier] = hists[identifier].GetListOfFunctions(
                ).FindObject("stats")
                statbox[identifier].SetX1NDC(.7)
                statbox[identifier].SetX2NDC(.95)
                if not drawn:
                    drawn = True
                    hists[identifier].SetLineStyle(1)
                    hists[identifier].SetLineColor(ROOT.kMagenta - 2)
                    statbox[identifier].SetY1NDC(.5)
                    statbox[identifier].SetY2NDC(.7)
                else:
                    hists[identifier].SetLineStyle(2)
                    hists[identifier].SetLineColor(ROOT.kGreen - 2)
                    statbox[identifier].SetY1NDC(.3)
                    statbox[identifier].SetY2NDC(.5)
                statbox[identifier].SetTextColor(
                    hists[identifier].GetLineColor())
            c1.Clear()
            c1.cd()
            drawn = False
            y_max = 0
            for identifier in hists:
                this_max = hists[identifier].GetMaximum()
                hists[identifier].SetLineWidth(2)
                if this_max > y_max:
                    y_max = this_max
                if not drawn:
                    hists[identifier].Draw("HIST")
                    hists[identifier].GetXaxis().SetTitle(
                        plot_sets[plot_name]['xtitle'])
                    hists[identifier].GetYaxis().SetTitle("Scaled to unity")
                    hists[identifier].SetTitle(group)
                    drawn = True
                else:
                    hists[identifier].Draw("SAMES HIST")
            for identifier in hists:
                hists[identifier].GetYaxis().SetRangeUser(0, y_max * 1.5)
            legend.Draw()
            c1.SaveAs("%s/%s_%s.png" %
                      (OUTDIR, group, plot_sets[plot_name].name))
            c1.SaveAs("%s/%s_%s.pdf" %
                      (OUTDIR, group, plot_sets[plot_name].name))
        # break


if __name__ == '__main__':
    main()
