#ifndef SUMXVSY_CFG_H
#define SUMXVSY_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1XvsY.h"
#include "ntuple_cfg.h"

TL1XvsY caloMetBE_l1MetBE(ntuple_cfg const * dataset);
TL1XvsY caloMetHF_l1MetBE(ntuple_cfg const * dataset);
TL1XvsY caloMetHF_l1MetHF(ntuple_cfg const * dataset);
TL1XvsY l1MetBE_recalcL1MetBE(ntuple_cfg const * dataset);
TL1XvsY caloMetPhiBE_l1MetPhiBE(ntuple_cfg const * dataset);
TL1XvsY caloMetPhiHF_l1MetPhiBE(ntuple_cfg const * dataset);
TL1XvsY caloMetPhiHF_l1MetPhiHF(ntuple_cfg const * dataset);
TL1XvsY caloMetXBE_l1MetXBE(ntuple_cfg const * dataset);
TL1XvsY caloMetYBE_l1MetYBE(ntuple_cfg const * dataset);
std::vector<double> bins(const double & min, const double & max, const double & width);
std::vector<double> phiBins();

// All Jet XvsYs
std::map< std::string, TL1XvsY* > sumXvsYs(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1XvsY* > xvsys;
    xvsys.emplace("caloMetBE_l1MetBE", new TL1XvsY(caloMetBE_l1MetBE(dataset)));
    xvsys.emplace("caloMetHF_l1MetBE", new TL1XvsY(caloMetHF_l1MetBE(dataset)));
    xvsys.emplace("caloMetHF_l1MetHF", new TL1XvsY(caloMetHF_l1MetHF(dataset)));
    xvsys.emplace("l1MetBE_recalcL1MetBE", new TL1XvsY(l1MetBE_recalcL1MetBE(dataset)));
    xvsys.emplace("caloMetPhiBE_l1MetPhiBE", new TL1XvsY(caloMetPhiBE_l1MetPhiBE(dataset)));
    xvsys.emplace("caloMetPhiHF_l1MetPhiBE", new TL1XvsY(caloMetPhiHF_l1MetPhiBE(dataset)));
    xvsys.emplace("caloMetPhiHF_l1MetPhiHF", new TL1XvsY(caloMetPhiHF_l1MetPhiHF(dataset)));
    xvsys.emplace("caloMetXBE_l1MetXBE", new TL1XvsY(caloMetXBE_l1MetXBE(dataset)));
    xvsys.emplace("caloMetYBE_l1MetYBE", new TL1XvsY(caloMetYBE_l1MetYBE(dataset)));
    return xvsys;
}

// calo Met BE vs. l1 Met BE
TL1XvsY caloMetBE_l1MetBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetBE";
    std::string yparam = "l1MetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} BE (GeV)");
    xvsy.SetXBins(bins(0.0, 800.0, 10.0));
    xvsy.SetY(yparam, "L1 E_{T}^{miss} BE (GeV)");
    xvsy.SetYBins(bins(0.0, 800.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo Met HF vs. l1 Met BE
TL1XvsY caloMetHF_l1MetBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetHF";
    std::string yparam = "l1MetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} HF (GeV)");
    xvsy.SetXBins(bins(0.0, 800.0, 10.0));
    xvsy.SetY(yparam, "L1 E_{T}^{miss} BE (GeV)");
    xvsy.SetYBins(bins(0.0, 800.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo Met HF vs. l1 Met HF
TL1XvsY caloMetHF_l1MetHF(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetHF";
    std::string yparam = "l1MetHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} HF (GeV)");
    xvsy.SetXBins(bins(0.0, 800.0, 10.0));
    xvsy.SetY(yparam, "L1 E_{T}^{miss} HF (GeV)");
    xvsy.SetYBins(bins(0.0, 800.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

// l1 Met BE vs. recalculated L1 Met BE
TL1XvsY l1MetBE_recalcL1MetBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "l1MetBE";
    std::string yparam = "recalcL1MetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "L1 E_{T}^{miss} BE (GeV)");
    xvsy.SetXBins(bins(0.0, 800.0, 10.0));
    xvsy.SetY(yparam, "Recalc L1 E_{T}^{miss} BE (GeV)");
    xvsy.SetYBins(bins(0.0, 800.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo Met Phi BE vs. l1 Met Phi BE
TL1XvsY caloMetPhiBE_l1MetPhiBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetPhiBE";
    std::string yparam = "l1MetPhiBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} #phi BE");
    xvsy.SetXBins(phiBins());
    xvsy.SetY(yparam, "L1 E_{T}^{miss} #phi BE");
    xvsy.SetYBins(phiBins());
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo Met Phi HF vs. l1 Met Phi BE
TL1XvsY caloMetPhiHF_l1MetPhiBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetPhiHF";
    std::string yparam = "l1MetPhiBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} #phi HF");
    xvsy.SetXBins(phiBins());
    xvsy.SetY(yparam, "L1 E_{T}^{miss} #phi BE");
    xvsy.SetYBins(phiBins());
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo Met Phi HF vs. l1 Met Phi HF
TL1XvsY caloMetPhiHF_l1MetPhiHF(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetPhiHF";
    std::string yparam = "l1MetPhiHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} #phi HF");
    xvsy.SetXBins(phiBins());
    xvsy.SetY(yparam, "L1 E_{T}^{miss} #phi HF");
    xvsy.SetYBins(phiBins());
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo MetX BE vs. l1 MetX BE
TL1XvsY caloMetXBE_l1MetXBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetXBE";
    std::string yparam = "l1MetXBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{x}^{miss} BE (GeV)");
    xvsy.SetXBins(bins(-400.0, 400.0, 10.0));
    xvsy.SetY(yparam, "L1 E_{x}^{miss} BE (GeV)");
    xvsy.SetYBins(bins(-400.0, 400.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo MetY BE vs. l1 MetY BE
TL1XvsY caloMetYBE_l1MetYBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetYBE";
    std::string yparam = "l1MetYBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{y}^{miss} BE (GeV)");
    xvsy.SetXBins(bins(-400.0, 400.0, 10.0));
    xvsy.SetY(yparam, "L1 E_{y}^{miss} BE (GeV)");
    xvsy.SetYBins(bins(-400.0, 400.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

std::vector<double> bins(const double & min, const double & max, const double & width)
{
    std::vector<double> temp;
    for(double binLowerEdge=min; binLowerEdge<=max; binLowerEdge+= width) temp.push_back(binLowerEdge);
    return temp;
}

std::vector<double> phiBins()
{
    std::vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=TMath::Pi(); binLowerEdge+= (TMath::Pi())/36.) temp.push_back(binLowerEdge);
    return temp;
}

#endif
