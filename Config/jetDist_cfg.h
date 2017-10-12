#ifndef JETDIST_CFG_H
#define JETDIST_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Dist.h"
#include "ntuple_cfg.h"

TL1Dist singleJets(ntuple_cfg const * dataset);
TL1Dist doubleJets(ntuple_cfg const * dataset);
TL1Dist tripleJets(ntuple_cfg const * dataset);
TL1Dist quadJets(ntuple_cfg const * dataset);
std::vector<double> bins(const double & min, const double & max, const double & width);

// All Jet Dist
std::map< std::string, TL1Dist* > jetDist(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1Dist* > dists;
    dists.emplace("singleJets", new TL1Dist(singleJets(dataset)));
    dists.emplace("doubleJets", new TL1Dist(doubleJets(dataset)));
    dists.emplace("tripleJets", new TL1Dist(tripleJets(dataset)));
    dists.emplace("quadJets",   new TL1Dist(quadJets(dataset)));
    return dists;
}

// SingleJets
TL1Dist singleJets(ntuple_cfg const * dataset)
{
    TL1Dist rate;
    std::string xparam = "singlel1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Dist/rate_"+outName+".root", "rate_"+xparam);
    rate.SetAddMark("N_{jet} #geq 1");
    return rate;
}

// doubleJets
TL1Dist doubleJets(ntuple_cfg const * dataset)
{
    TL1Dist rate;
    std::string xparam = "doublel1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Dist/rate_"+outName+".root", "rate_"+xparam);
    rate.SetAddMark("N_{jet} #geq 2");
    return rate;
}

// tripleJets
TL1Dist tripleJets(ntuple_cfg const * dataset)
{
    TL1Dist rate;
    std::string xparam = "triplel1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Dist/rate_"+outName+".root", "rate_"+xparam);
    rate.SetAddMark("N_{jet} #geq 3");
    return rate;
}

// quadJets
TL1Dist quadJets(ntuple_cfg const * dataset)
{
    TL1Dist rate;
    std::string xparam = "quadl1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Dist/rate_"+outName+".root", "rate_"+xparam);
    rate.SetAddMark("N_{jet} #geq 4");
    return rate;
}

std::vector<double> bins(const double & min, const double & max, const double & width)
{
    std::vector<double> temp;
    for(double bin=min; bin<=max; bin+=width) temp.push_back(bin);
    return temp;
}

#endif
