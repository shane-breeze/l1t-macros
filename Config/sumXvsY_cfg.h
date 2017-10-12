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
TL1XvsY caloMetBE_l1EmuMetBE(ntuple_cfg const * dataset);
TL1XvsY caloMetHF_l1EmuMetBE(ntuple_cfg const * dataset);
TL1XvsY caloMetHF_l1EmuMetHF(ntuple_cfg const * dataset);

TL1XvsY l1MetBE_recalcL1MetBE(ntuple_cfg const * dataset);
TL1XvsY caloMetPhiBE_l1MetPhiBE(ntuple_cfg const * dataset);
TL1XvsY caloMetPhiHF_l1MetPhiBE(ntuple_cfg const * dataset);
TL1XvsY caloMetPhiHF_l1MetPhiHF(ntuple_cfg const * dataset);
TL1XvsY caloMetXBE_l1MetXBE(ntuple_cfg const * dataset);
TL1XvsY caloMetYBE_l1MetYBE(ntuple_cfg const * dataset);

TL1XvsY recoHtt_l1Htt(ntuple_cfg const * dataset);
TL1XvsY recoHtt_l1EmuHtt(ntuple_cfg const * dataset);
TL1XvsY recalcRecoHtt_l1Htt(ntuple_cfg const * dataset);
TL1XvsY recalcRecoHtt_l1EmuHtt(ntuple_cfg const * dataset);
TL1XvsY recalcRecoHttNoMEF_l1Htt(ntuple_cfg const * dataset);
TL1XvsY recalcRecoHttNoMEF_l1EmuHtt(ntuple_cfg const * dataset);

TL1XvsY l1Htt_recalcL1Htt(ntuple_cfg const * dataset);
TL1XvsY recoHtt_recalcL1Htt(ntuple_cfg const * dataset);
TL1XvsY recalcRecoHtt_recoHtt(ntuple_cfg const * dataset);

std::vector<double> bins(const double & min, const double & max, const double & width);
std::vector<double> phiBins();

// All Jet XvsYs
std::map< std::string, TL1XvsY* > sumXvsYs(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1XvsY* > xvsys;
    xvsys.emplace("caloMetBE_l1MetBE", new TL1XvsY(caloMetBE_l1MetBE(dataset)));
    xvsys.emplace("caloMetBE_l1EmuMetBE", new TL1XvsY(caloMetBE_l1EmuMetBE(dataset)));
    xvsys.emplace("caloMetHF_l1MetHF", new TL1XvsY(caloMetHF_l1MetHF(dataset)));
    xvsys.emplace("caloMetHF_l1EmuMetHF", new TL1XvsY(caloMetHF_l1EmuMetHF(dataset)));

    xvsys.emplace("recoHtt_l1Htt", new TL1XvsY(recoHtt_l1Htt(dataset)));
    xvsys.emplace("recoHtt_l1EmuHtt", new TL1XvsY(recoHtt_l1EmuHtt(dataset)));
    xvsys.emplace("recalcRecoHtt_l1Htt", new TL1XvsY(recalcRecoHtt_l1Htt(dataset)));
    xvsys.emplace("recalcRecoHtt_l1EmuHtt", new TL1XvsY(recalcRecoHtt_l1EmuHtt(dataset)));
    xvsys.emplace("recalcRecoHttNoMEF_l1Htt", new TL1XvsY(recalcRecoHttNoMEF_l1Htt(dataset)));
    xvsys.emplace("recalcRecoHttNoMEF_l1EmuHtt", new TL1XvsY(recalcRecoHttNoMEF_l1EmuHtt(dataset)));
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

// calo Met BE vs. l1 Met BE
TL1XvsY caloMetBE_l1EmuMetBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetBE";
    std::string yparam = "l1EmuMetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} BE (GeV)");
    xvsy.SetXBins(bins(0.0, 800.0, 10.0));
    xvsy.SetY(yparam, "Emualted L1 E_{T}^{miss} BE (GeV)");
    xvsy.SetYBins(bins(0.0, 800.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo Met HF vs. l1 Met BE
TL1XvsY caloMetHF_l1EmuMetBE(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetHF";
    std::string yparam = "l1EmuMetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} HF (GeV)");
    xvsy.SetXBins(bins(0.0, 800.0, 10.0));
    xvsy.SetY(yparam, "Emulated L1 E_{T}^{miss} BE (GeV)");
    xvsy.SetYBins(bins(0.0, 800.0, 10.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

// calo Met HF vs. l1 Met HF
TL1XvsY caloMetHF_l1EmuMetHF(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "caloMetHF";
    std::string yparam = "l1EmuMetHF";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline E_{T}^{miss} HF (GeV)");
    xvsy.SetXBins(bins(0.0, 800.0, 10.0));
    xvsy.SetY(yparam, "Emulated L1 E_{T}^{miss} HF (GeV)");
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

TL1XvsY l1Htt_recalcL1Htt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "l1Htt";
    std::string yparam = "recalcL1Htt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "L1 HTT (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "Recalc L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recoHtt_l1Htt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoHtt";
    std::string yparam = "l1Htt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline HTT (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recoHtt_l1EmuHtt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoHtt";
    std::string yparam = "l1EmuHtt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline HTT (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "Emulated L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recoHtt_recalcL1Htt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recoHtt";
    std::string yparam = "recalcL1Htt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Offline HTT (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "Recalc L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recalcRecoHtt_l1Htt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recalcRecoHtt";
    std::string yparam = "l1Htt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Recalc offline HTT (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recalcRecoHtt_l1EmuHtt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recalcRecoHtt";
    std::string yparam = "l1EmuHtt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Recalc offline HTT (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "Emulated L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recalcRecoHttNoMEF_l1Htt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recalcRecoHttNoMEF";
    std::string yparam = "l1Htt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Recalc offline HTT no MEF (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recalcRecoHttNoMEF_l1EmuHtt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recalcRecoHttNoMEF";
    std::string yparam = "l1EmuHtt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Recalc offline HTT no MEF (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "Emulated L1 HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetOutName(outName);
    return xvsy;
}

TL1XvsY recalcRecoHtt_recoHtt(ntuple_cfg const * dataset)
{
    TL1XvsY xvsy;
    std::string xparam = "recalcRecoHtt";
    std::string yparam = "recoHtt";
    std::string outName = dataset->triggerName+"_"+xparam+"_vs_"+yparam;
    xvsy.SetOverwriteNames(dataset->baseOWdir+"/XvsY/xy_"+outName+".root", "xy_"+xparam+"_vs_"+yparam);
    xvsy.SetX(xparam, "Recalc offline HTT (GeV)");
    xvsy.SetXBins(bins(0.0, 3000.0, 100.0));
    xvsy.SetY(yparam, "Reco HTT (GeV)");
    xvsy.SetYBins(bins(0.0, 3000.0, 100.0));
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
