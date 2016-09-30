#ifndef JETRATES_CFG_H
#define JETRATES_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Rates.h"
#include "ntuple_cfg.h"

TL1Rates singleJets(ntuple_cfg const * dataset);
TL1Rates doubleJets(ntuple_cfg const * dataset);
TL1Rates tripleJets(ntuple_cfg const * dataset);
TL1Rates quadJets(ntuple_cfg const * dataset);
std::vector<double> bins(const double & min, const double & max, const double & width);

// All Jet Rates
std::map< std::string, TL1Rates* > jetRates(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1Rates* > rates;
    rates.emplace("singleJets", new TL1Rates(singleJets(dataset)));
    rates.emplace("doubleJets", new TL1Rates(doubleJets(dataset)));
    rates.emplace("tripleJets", new TL1Rates(tripleJets(dataset)));
    rates.emplace("quadJets",   new TL1Rates(quadJets(dataset)));
    return rates;
}

// SingleJets
TL1Rates singleJets(ntuple_cfg const * dataset)
{
    TL1Rates rate;
    std::string xparam = "singlel1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Rates/rate_"+outName+".root", "rate_"+xparam);
    rate.SetAddMark("N_{jet} #geq 1");
    return rate;
}

// doubleJets
TL1Rates doubleJets(ntuple_cfg const * dataset)
{
    TL1Rates rate;
    std::string xparam = "doublel1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Rates/rate_"+outName+".root", "rate_"+xparam);
    rate.SetAddMark("N_{jet} #geq 2");
    return rate;
}

// tripleJets
TL1Rates tripleJets(ntuple_cfg const * dataset)
{
    TL1Rates rate;
    std::string xparam = "triplel1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Rates/rate_"+outName+".root", "rate_"+xparam);
    rate.SetAddMark("N_{jet} #geq 3");
    return rate;
}

// quadJets
TL1Rates quadJets(ntuple_cfg const * dataset)
{
    TL1Rates rate;
    std::string xparam = "quadl1JetEt";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Jet E_{T} (GeV)");
    rate.SetXBins(bins(0.0,300.0,1.0));
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Rates/rate_"+outName+".root", "rate_"+xparam);
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
