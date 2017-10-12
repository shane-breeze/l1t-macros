#ifndef SUMRESOLUTION_CFG_H
#define SUMRESOLUTION_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Resolution.h"
#include "ntuple_cfg.h"

TL1Resolution caloMetBE_l1MetBE(ntuple_cfg const * dataset);
TL1Resolution caloMetHF_l1MetBE(ntuple_cfg const * dataset);
TL1Resolution caloMetHF_l1MetHF(ntuple_cfg const * dataset);
TL1Resolution caloMetPhiBE_l1MetPhiBE(ntuple_cfg const * dataset);
TL1Resolution caloMetPhiHF_l1MetPhiBE(ntuple_cfg const * dataset);
TL1Resolution caloMetPhiHF_l1MetPhiHF(ntuple_cfg const * dataset);
TL1Resolution recoHtt_l1Htt(ntuple_cfg const * dataset);
std::vector<double> bins(std::string plotType);

// All Sum Resolutions
std::map< std::string, TL1Resolution* > sumResolutions(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1Resolution* > resolutions;
    //resolutions.emplace("caloMetBE_l1MetBE", new TL1Resolution(caloMetBE_l1MetBE(dataset)));
    //resolutions.emplace("caloMetHF_l1MetBE", new TL1Resolution(caloMetHF_l1MetBE(dataset)));
    //resolutions.emplace("caloMetHF_l1MetHF", new TL1Resolution(caloMetHF_l1MetHF(dataset)));
    //resolutions.emplace("caloMetPhiBE_l1MetPhiBE", new TL1Resolution(caloMetPhiBE_l1MetPhiBE(dataset)));
    //resolutions.emplace("caloMetPhiHF_l1MetPhiBE", new TL1Resolution(caloMetPhiHF_l1MetPhiBE(dataset)));
    //resolutions.emplace("caloMetPhiHF_l1MetPhiHF", new TL1Resolution(caloMetPhiHF_l1MetPhiHF(dataset)));
    resolutions.emplace("recoHtt_l1Htt", new TL1Resolution(recoHtt_l1Htt(dataset)));
    return resolutions;
}

// caloMetBE and l1MetBE
TL1Resolution caloMetBE_l1MetBE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "caloMetBE";
    std::string yparam   = "l1MetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/Resolution/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline E_{T}^{miss} BE");
    resolution.SetY(yparam, "L1 E_{T}^{miss} BE");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("Offline E_{T}^{miss} > 40 GeV");
    return resolution;
}

// caloMetHF and l1MetBE
TL1Resolution caloMetHF_l1MetBE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "caloMetHF";
    std::string yparam   = "l1MetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/Resolution/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline E_{T}^{miss} HF");
    resolution.SetY(yparam, "L1 E_{T}^{miss} BE");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("Offline E_{T}^{miss} > 40 GeV");
    return resolution;
}

// caloMetHF and l1MetHF
TL1Resolution caloMetHF_l1MetHF(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "caloMetHF";
    std::string yparam   = "l1MetHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/Resolution/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline E_{T}^{miss} HF");
    resolution.SetY(yparam, "L1 E_{T}^{miss} HF");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("Offline E_{T}^{miss} > 40 GeV");
    return resolution;
}

// caloMetPhiBE and l1MetPhiBE
TL1Resolution caloMetPhiBE_l1MetPhiBE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "caloMetPhiBE";
    std::string yparam   = "l1MetPhiBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/Resolution/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline E_{T}^{miss} #phi BE");
    resolution.SetY(yparam, "L1 E_{T}^{miss} #phi BE");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("Offline E_{T}^{miss} > 40 GeV");
    return resolution;
}

// caloMetPhiHF and l1MetPhiBE
TL1Resolution caloMetPhiHF_l1MetPhiBE(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "caloMetPhiBE";
    std::string yparam   = "l1MetPhiBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/Resolution/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline E_{T}^{miss} #phi BE");
    resolution.SetY(yparam, "L1 E_{T}^{miss} #phi BE");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("Offline E_{T}^{miss} > 40 GeV");
    return resolution;
}

// caloMetPhiHF and l1MetPhiHF
TL1Resolution caloMetPhiHF_l1MetPhiHF(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Position";
    std::string xparam   = "caloMetPhiHF";
    std::string yparam   = "l1MetPhiHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/Resolution/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline E_{T}^{miss} #phi HF");
    resolution.SetY(yparam, "L1 E_{T}^{miss} #phi HF");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("Offline E_{T}^{miss} > 40 GeV");
    return resolution;
}

TL1Resolution recoHtt_l1Htt(ntuple_cfg const * dataset)
{
    TL1Resolution resolution;
    std::string plotType = "Energy";
    std::string xparam   = "recoHtt";
    std::string yparam   = "l1Htt";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+yparam;
    resolution.SetPlotType(plotType);
    resolution.SetOverwriteNames(dataset->baseOWdir+"/Resolution/res_"+outName+".root", "res_"+xparam+"_"+yparam);
    resolution.SetX(xparam, "Offline HTT");
    resolution.SetY(yparam, "L1 HTT");
    resolution.SetBins(bins(plotType));
    resolution.SetOutName(outName);
    resolution.SetAddMark("Offline HTT > 1500 GeV");
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
