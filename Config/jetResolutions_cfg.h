#ifndef JETRESOLUTION_CFG_H
#define JETRESOLUTION_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Resolution.h"
#include "ntuple_cfg.h"

TL1Resolution jetEtB(ntuple_cfg const * dataset);
TL1Resolution jetEtE(ntuple_cfg const * dataset);
TL1Resolution jetEtBE(ntuple_cfg const * dataset);
TL1Resolution jetEtHF(ntuple_cfg const * dataset);
TL1Resolution jetPhiB(ntuple_cfg const * dataset);
TL1Resolution jetPhiE(ntuple_cfg const * dataset);
TL1Resolution jetPhiBE(ntuple_cfg const * dataset);
TL1Resolution jetPhiHF(ntuple_cfg const * dataset);
TL1Resolution jetEtaB(ntuple_cfg const * dataset);
TL1Resolution jetEtaE(ntuple_cfg const * dataset);
TL1Resolution jetEtaBE(ntuple_cfg const * dataset);
TL1Resolution jetEtaHF(ntuple_cfg const * dataset);
std::vector<double> bins(std::string plotType);

// All Jet Resolutions
std::map< std::string, TL1Resolution* > jetResolutions(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1Resolution* > resolutions;
    resolutions.emplace("jetEtB",   new TL1Resolution(jetEtB(dataset)));
    resolutions.emplace("jetEtE",   new TL1Resolution(jetEtE(dataset)));
    resolutions.emplace("jetEtBE",  new TL1Resolution(jetEtBE(dataset)));
    resolutions.emplace("jetEtHF",  new TL1Resolution(jetEtHF(dataset)));
    resolutions.emplace("jetPhiB",  new TL1Resolution(jetPhiB(dataset)));
    resolutions.emplace("jetPhiE",  new TL1Resolution(jetPhiE(dataset)));
    resolutions.emplace("jetPhiBE", new TL1Resolution(jetPhiBE(dataset)));
    resolutions.emplace("jetPhiHF", new TL1Resolution(jetPhiHF(dataset)));
    resolutions.emplace("jetEtaB",  new TL1Resolution(jetEtaB(dataset)));
    resolutions.emplace("jetEtaE",  new TL1Resolution(jetEtaE(dataset)));
    resolutions.emplace("jetEtaBE", new TL1Resolution(jetEtaBE(dataset)));
    resolutions.emplace("jetEtaHF", new TL1Resolution(jetEtaHF(dataset)));
    return resolutions;
}

// Jet Et - Barrel
TL1Resolution jetEtB(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "recoJetEtB";
    std::string yparam   = "l1JetEtB";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Barrel Jet E_{T} (GeV)");
    resolution.SetY(yparam, "L1 Barrel Jet E_{T} (GeV)");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| < 1.479}");
    return resolution;
}

// Jet Et - Endcap
TL1Resolution jetEtE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "recoJetEtE";
    std::string yparam   = "l1JetEtE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Barrel Jet E_{T} (GeV)");
    resolution.SetY(yparam, "L1 Barrel Jet E_{T} (GeV)");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{1.479 < |#eta| < 3.0}");
    return resolution;
}

// Jet Et - Central
TL1Resolution jetEtBE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "recoJetEtBE";
    std::string yparam   = "l1JetEtBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Central Jet E_{T} (GeV)");
    resolution.SetY(yparam, "L1 Central Jet E_{T} (GeV)");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| < 3.0}");
    return resolution;
}

// Jet Et - HF
TL1Resolution jetEtHF(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "recoJetEtHF";
    std::string yparam   = "l1JetEtHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline HF Jet E_{T} (GeV)");
    resolution.SetY(yparam, "L1 HF Jet E_{T} (GeV)");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| > 3.0}");
    return resolution;
}

// Jet Phi - Barrel
TL1Resolution jetPhiB(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetPhiB";
    std::string yparam   = "l1JetPhiB";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Barrel Jet #phi");
    resolution.SetY(yparam, "L1 Barrel Jet #phi");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| < 1.479}");
    return resolution;
}

// Jet Phi - Endcap
TL1Resolution jetPhiE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetPhiE";
    std::string yparam   = "l1JetPhiE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Endcap Jet #phi");
    resolution.SetY(yparam, "L1 Endcap Jet #phi");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{1.479 < |#eta| < 3.0}");
    return resolution;
}

// Jet Phi - Central
TL1Resolution jetPhiBE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetPhiBE";
    std::string yparam   = "l1JetPhiBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Central Jet #phi");
    resolution.SetY(yparam, "L1 Central Jet #phi");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| < 3.0}");
    return resolution;
}

// Jet Phi - HF
TL1Resolution jetPhiHF(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetPhiHF";
    std::string yparam   = "l1JetPhiHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline HF Jet #phi");
    resolution.SetY(yparam, "L1 HF Jet #phi");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| > 3.0}");
    return resolution;
}

// Jet Eta - Barrel
TL1Resolution jetEtaB(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetEtaB";
    std::string yparam   = "l1JetEtaB";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Barrel Jet #eta");
    resolution.SetY(yparam, "L1 Barrel Jet #eta");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| < 1.479}");
    return resolution;
}

// Jet Eta - Endcap
TL1Resolution jetEtaE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetEtaE";
    std::string yparam   = "l1JetEtaE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Endcap Jet #eta");
    resolution.SetY(yparam, "L1 Endcap Jet #eta");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{1.479 < |#eta| < 3.0}");
    return resolution;
}

// Jet Eta - Central
TL1Resolution jetEtaBE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetEtaBE";
    std::string yparam   = "l1JetEtaBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline Central Jet #eta");
    resolution.SetY(yparam, "L1 Central Jet #eta");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| < 3.0}");
    return resolution;
}

// Jet Eta - HF
TL1Resolution jetEtaHF(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "recoJetEtaHF";
    std::string yparam   = "l1JetEtaHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/ResolutionJets/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline HF Jet #eta");
    resolution.SetY(yparam, "L1 HF Jet #eta");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("#splitline{Offline Jet E_{T} > 30 GeV}{|#eta| > 3.0}");
    return resolution;
}

// Binning
std::vector<double> bins(std::string plotType)
{
    std::vector<double> temp;
    if( plotType == "Position" ) for(double binLowerEdge=-0.3; binLowerEdge<=0.3; binLowerEdge+= 0.005) temp.push_back(binLowerEdge);
    else if( plotType == "Energy" ) for(double binLowerEdge=-1.0; binLowerEdge<=1.5; binLowerEdge+= 0.05) temp.push_back(binLowerEdge);
    return temp;
}

#endif
