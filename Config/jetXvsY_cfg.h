#ifndef JETXVSY_CFG_H
#define JETXVSY_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1XvsY.h"
#include "ntuple_cfg.h"

TL1XvsY recoL1JetEtB(ntuple_cfg const * dataset);
TL1XvsY recoL1JetEtE(ntuple_cfg const * dataset);
TL1XvsY recoL1JetEtBE(ntuple_cfg const * dataset);
TL1XvsY recoL1JetEtHF(ntuple_cfg const * dataset);
TL1XvsY recoL1JetPhiB(ntuple_cfg const * dataset);
TL1XvsY recoL1JetPhiE(ntuple_cfg const * dataset);
TL1XvsY recoL1JetPhiBE(ntuple_cfg const * dataset);
TL1XvsY recoL1JetPhiHF(ntuple_cfg const * dataset);
TL1XvsY recoL1JetEta(ntuple_cfg const * dataset);
std::vector<double> bins(const double & max);
std::vector<double> phiBins();
std::vector<double> etaBins();

// All Jet XvsYs
std::map< std::string, TL1XvsY* > jetXvsYs(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1XvsY* > xvsys;
    xvsys.emplace("recoL1JetEtB", new TL1XvsY(recoL1JetEtB(dataset)));
    xvsys.emplace("recoL1JetEtE", new TL1XvsY(recoL1JetEtE(dataset)));
    xvsys.emplace("recoL1JetEtBE", new TL1XvsY(recoL1JetEtBE(dataset)));
    xvsys.emplace("recoL1JetEtHF", new TL1XvsY(recoL1JetEtHF(dataset)));
    xvsys.emplace("recoL1JetPhiB", new TL1XvsY(recoL1JetPhiB(dataset)));
    xvsys.emplace("recoL1JetPhiE", new TL1XvsY(recoL1JetPhiE(dataset)));
    xvsys.emplace("recoL1JetPhiBE", new TL1XvsY(recoL1JetPhiBE(dataset)));
    xvsys.emplace("recoL1JetPhiHF", new TL1XvsY(recoL1JetPhiHF(dataset)));
    xvsys.emplace("recoL1JetEta", new TL1XvsY(recoL1JetEta(dataset)));
    return xvsys;
}

// Jet Et - Barrel
TL1XvsY recoL1JetEtB(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtB";
    std::string yparam = "l1JetEtB";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_barrel";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(300.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(300.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| < 1.479");
    return xvsy;
}

// Jet Et - Endcap
TL1XvsY recoL1JetEtE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtE";
    std::string yparam = "l1JetEtE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_endcap";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(300.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(300.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("1.479 < |#eta| < 3.0");
    return xvsy;
}

// Jet Et - Central
TL1XvsY recoL1JetEtBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtBE";
    std::string yparam = "l1JetEtBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_central";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(300.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(300.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| < 3.0");
    return xvsy;
}

// Jet Et - HF
TL1XvsY recoL1JetEtHF(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtHF";
    std::string yparam = "l1JetEtHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_HF";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(300.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(300.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| > 3.0");
    return xvsy;
}

// Jet Phi - Barrel
TL1XvsY recoL1JetPhiB(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetPhiB";
    std::string yparam = "l1JetPhiB";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_barrel";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet #phi");
    xvsy.SetXBins(phiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(phiBins());
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| < 1.479");
    return xvsy;
}

// Jet Phi - Endcap
TL1XvsY recoL1JetPhiE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetPhiE";
    std::string yparam = "l1JetPhiE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_endcap";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet #phi");
    xvsy.SetXBins(phiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(phiBins());
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("1.479 < |#eta| < 3.0");
    return xvsy;
}

// Jet Phi - Central
TL1XvsY recoL1JetPhiBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetPhiBE";
    std::string yparam = "l1JetPhiBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_central";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet #phi");
    xvsy.SetXBins(phiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(phiBins());
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| < 3.0");
    return xvsy;
}

// Jet Phi - HF
TL1XvsY recoL1JetPhiHF(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetPhiHF";
    std::string yparam = "l1JetPhiHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_HF";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet #phi");
    xvsy.SetXBins(phiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(phiBins());
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| > 3.0");
    return xvsy;
}

// Jet Eta
TL1XvsY recoL1JetEta(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEta";
    std::string yparam = "l1JetEta";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet #eta");
    xvsy.SetXBins(etaBins());
    xvsy.SetY(yparam, "L1 Jet #eta");
    xvsy.SetYBins(etaBins());
    xvsy.SetOutName(outName);
    return xvsy;
}

std::vector<double> bins(const double & max)
{
    std::vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=max; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
    return temp;
}

std::vector<double> phiBins()
{
    std::vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=TMath::Pi(); binLowerEdge+= (TMath::Pi())/36.) temp.push_back(binLowerEdge);
    return temp;
}

std::vector<double> etaBins()
{
    std::vector<double> temp;
    for(double binLowerEdge=-5.0; binLowerEdge<=5.0; binLowerEdge+= 0.1) temp.push_back(binLowerEdge);
    return temp;
}

#endif
