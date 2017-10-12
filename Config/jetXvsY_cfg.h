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
TL1XvsY recoL1EmuJetEtB(ntuple_cfg const * dataset);
TL1XvsY recoL1EmuJetEtE(ntuple_cfg const * dataset);
TL1XvsY recoL1EmuJetEtBE(ntuple_cfg const * dataset);
TL1XvsY recoL1EmuJetEtHF(ntuple_cfg const * dataset);

TL1XvsY recoL1JetPhiB(ntuple_cfg const * dataset);
TL1XvsY recoL1JetPhiE(ntuple_cfg const * dataset);
TL1XvsY recoL1JetPhiBE(ntuple_cfg const * dataset);
TL1XvsY recoL1JetPhiHF(ntuple_cfg const * dataset);
TL1XvsY recoL1JetEta(ntuple_cfg const * dataset);
TL1XvsY recoJetEtEta(ntuple_cfg const * dataset);
TL1XvsY l1JetEtEta(ntuple_cfg const * dataset);
std::vector<double> bins(const double & max);
std::vector<double> jetPhiBins();
std::vector<double> jetEtaBins();

// All Jet XvsYs
std::map< std::string, TL1XvsY* > jetXvsYs(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1XvsY* > xvsys;
    xvsys.emplace("recoL1JetEtB", new TL1XvsY(recoL1JetEtB(dataset)));
    xvsys.emplace("recoL1JetEtE", new TL1XvsY(recoL1JetEtE(dataset)));
    xvsys.emplace("recoL1JetEtBE", new TL1XvsY(recoL1JetEtBE(dataset)));
    xvsys.emplace("recoL1JetEtHF", new TL1XvsY(recoL1JetEtHF(dataset)));
    xvsys.emplace("recoL1EmuJetEtB", new TL1XvsY(recoL1EmuJetEtB(dataset)));
    xvsys.emplace("recoL1EmuJetEtE", new TL1XvsY(recoL1EmuJetEtE(dataset)));
    xvsys.emplace("recoL1EmuJetEtBE", new TL1XvsY(recoL1EmuJetEtBE(dataset)));
    xvsys.emplace("recoL1EmuJetEtHF", new TL1XvsY(recoL1EmuJetEtHF(dataset)));
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
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
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
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
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
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
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
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| > 3.0");
    return xvsy;
}

// Emu Jet Et - Barrel
TL1XvsY recoL1EmuJetEtB(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtB";
    std::string yparam = "l1EmuJetEtB";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_barrel";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "Emulated L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| < 1.479");
    return xvsy;
}

// Emu Jet Et - Endcap
TL1XvsY recoL1EmuJetEtE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtE";
    std::string yparam = "l1EmuJetEtE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_endcap";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "Emulated L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("1.479 < |#eta| < 3.0");
    return xvsy;
}

// Emu Jet Et - Central
TL1XvsY recoL1EmuJetEtBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtBE";
    std::string yparam = "l1EmuJetEtBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_central";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "Emulated L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("|#eta| < 3.0");
    return xvsy;
}

// Emu Jet Et - HF
TL1XvsY recoL1EmuJetEtHF(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEtHF";
    std::string yparam = "l1EmuJetEtHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam+"_HF";
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T} (GeV)");
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "Emulated L1 Jet E_{T} (GeV)");
    xvsy.SetYBins(bins(600.0));
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
    xvsy.SetXBins(jetPhiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(jetPhiBins());
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
    xvsy.SetXBins(jetPhiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(jetPhiBins());
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
    xvsy.SetXBins(jetPhiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(jetPhiBins());
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
    xvsy.SetXBins(jetPhiBins());
    xvsy.SetY(yparam, "L1 Jet #phi");
    xvsy.SetYBins(jetPhiBins());
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
    xvsy.SetXBins(jetEtaBins());
    xvsy.SetY(yparam, "L1 Jet #eta");
    xvsy.SetYBins(jetEtaBins());
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recoJetEtEta(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoJetEt";
    std::string yparam = "recoJetEta";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline Jet E_{T}");
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "Offline Jet #eta");
    xvsy.SetYBins(jetEtaBins());
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("Offline H_{T} > 1000\\L1 H_{T} < 100");
    return xvsy;
}

TL1XvsY l1JetEtEta(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "l1JetEt";
    std::string yparam = "l1JetEta";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsYJets/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "L1 Jet E_{T}");
    xvsy.SetXBins(bins(600.0));
    xvsy.SetY(yparam, "L1 Jet #eta");
    xvsy.SetYBins(jetEtaBins());
    xvsy.SetOutName(outName);
    xvsy.SetAddMark("Offline H_{T} > 1000\\L1 H_{T} < 100");
    return xvsy;
}

std::vector<double> bins(const double & max)
{
    std::vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=max; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
    return temp;
}

std::vector<double> jetPhiBins()
{
    std::vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=TMath::Pi(); binLowerEdge+= (TMath::Pi())/36.) temp.push_back(binLowerEdge);
    return temp;
}

std::vector<double> jetEtaBins()
{
    std::vector<double> temp;
    for(double binLowerEdge=-5.0; binLowerEdge<=5.0; binLowerEdge+= 0.1) temp.push_back(binLowerEdge);
    return temp;
}

#endif
