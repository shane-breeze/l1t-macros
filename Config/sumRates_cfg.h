#ifndef SUMRATES_CFG_H
#define SUMRATES_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Rates.h"
#include "ntuple_cfg.h"

TL1Rates l1MetBE(ntuple_cfg const * dataset);
TL1Rates l1MetHF(ntuple_cfg const * dataset);
std::vector<double> metBins();

// All Jet Turnons
std::map< std::string, TL1Rates* > sumRates(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1Rates* > rates;
    rates.emplace("l1MetBE", new TL1Rates(l1MetBE(dataset)));
    rates.emplace("l1MetHF", new TL1Rates(l1MetHF(dataset)));
    return rates;
}

// l1 MET BE
TL1Rates l1MetBE(ntuple_cfg const * dataset)
{
    TL1Rates rate;
    std::string xparam = "l1MetBE";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 Central E_{T}^{miss} (GeV)");
    rate.SetXBins(metBins());
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Rates/rate_"+outName+".root", "rate_"+xparam);
    return rate;
}

// l1 MET HF
TL1Rates l1MetHF(ntuple_cfg const * dataset)
{
    TL1Rates rate;
    std::string xparam = "l1MetHF";
    std::string outName = dataset->triggerName+"_"+xparam;
    rate.SetX(xparam, "L1 HF E_{T}^{miss} (GeV)");
    rate.SetXBins(metBins());
    rate.SetOutName(dataset->triggerName+"_"+xparam);
    rate.SetOverwriteNames(dataset->baseOWdir+"/Rates/rate_"+outName+".root", "rate_"+xparam);
    return rate;
}

std::vector<double> metBins()
{
    std::vector<double> temp;
    for(double bin=0.0; bin<=200.0; bin+=5.0) temp.push_back(bin);
    return temp;
}

#endif
