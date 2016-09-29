#ifndef JETTURNONS_CFG_H
#define JETTURNONS_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Turnon.h"
#include "ntuple_cfg.h"

TL1Turnon jetEtBarrel(ntuple_cfg const * dataset);
TL1Turnon jetEtEndcap(ntuple_cfg const * dataset);
TL1Turnon jetEtCentral(ntuple_cfg const * dataset);
TL1Turnon jetEtHF(ntuple_cfg const * dataset);
std::vector<double> bins();

// All Jet Turnons
std::map< std::string, TL1Turnon* > jetTurnons(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1Turnon* > turnons;
    turnons.emplace("jetEtBarrel", new TL1Turnon(jetEtBarrel(dataset)));
    turnons.emplace("jetEtEndcap", new TL1Turnon(jetEtEndcap(dataset)));
    turnons.emplace("jetEtCentral", new TL1Turnon(jetEtCentral(dataset)));
    turnons.emplace("jetEtHF", new TL1Turnon(jetEtHF(dataset)));
    return turnons;
}

// Jet Et - barrel
TL1Turnon jetEtBarrel(ntuple_cfg const * dataset)
{
    TL1Turnon turnon;
    std::string seed = "l1JetEtSeed";
    std::string xparam = "recoJetEt";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+seed+"_barrel";
    turnon.SetOverwriteNames(dataset->baseOWdir+"/TurnonsJets/dists_"+outName+".root", "dist_"+xparam+"_"+seed);
    turnon.SetSeed(seed, "L1 Jet E_{T}");
    turnon.SetSeeds({0., 36., 68., 128., 200.});
    turnon.SetX(xparam, "Offline Jet E_{T} (GeV)");
    turnon.SetXBins(bins());
    turnon.SetOutName(outName);
    turnon.SetFit(dataset->doFit);
    turnon.SetAddMark("|#eta| < 1.479");
    return turnon;
}

// Jet Et - end cap
TL1Turnon jetEtEndcap(ntuple_cfg const * dataset)
{
    TL1Turnon turnon;
    std::string seed = "l1JetEtSeed";
    std::string xparam = "recoJetEt";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+seed+"_endcap";
    turnon.SetOverwriteNames(dataset->baseOWdir+"/TurnonsJets/dists_"+outName+".root", "dist_"+xparam+"_"+seed);
    turnon.SetSeed(seed, "L1 Jet E_{T}");
    turnon.SetSeeds({0., 36., 68., 128., 200.});
    turnon.SetX(xparam, "Offline Jet E_{T} (GeV)");
    turnon.SetXBins(bins());
    turnon.SetOutName(outName);
    turnon.SetFit(dataset->doFit);
    turnon.SetAddMark("1.479 < |#eta| < 3.0");
    return turnon;
}

// Jet Et - central
TL1Turnon jetEtCentral(ntuple_cfg const * dataset)
{
    TL1Turnon turnon;
    std::string seed = "l1JetEtSeed";
    std::string xparam = "recoJetEt";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+seed+"_central";
    turnon.SetOverwriteNames(dataset->baseOWdir+"/TurnonsJets/dists_"+outName+".root", "dist_"+xparam+"_"+seed);
    turnon.SetSeed(seed, "L1 Jet E_{T}");
    turnon.SetSeeds({0., 36., 68., 128., 200.});
    turnon.SetX(xparam, "Offline Jet E_{T} (GeV)");
    turnon.SetXBins(bins());
    turnon.SetOutName(outName);
    turnon.SetFit(dataset->doFit);
    turnon.SetAddMark("|#eta| < 3.0");
    return turnon;
}

// Jet Et - HF
TL1Turnon jetEtHF(ntuple_cfg const * dataset)
{
    TL1Turnon turnon;
    std::string seed = "l1JetEtSeed";
    std::string xparam = "recoJetEt";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+seed+"_hf";
    turnon.SetOverwriteNames(dataset->baseOWdir+"/TurnonsJets/dists_"+outName+".root", "dist_"+xparam+"_"+seed);
    turnon.SetSeed(seed, "L1 Jet E_{T}");
    turnon.SetSeeds({0., 36., 68., 128., 200.});
    turnon.SetX(xparam, "Offline Jet E_{T} (GeV)");
    turnon.SetXBins(bins());
    turnon.SetOutName(outName);
    turnon.SetFit(dataset->doFit);
    turnon.SetAddMark("|#eta| > 3.0");
    return turnon;
}

std::vector<double> bins()
{
    std::vector<double> temp;
    for(double binLowerEdge=  0.0; binLowerEdge< 100.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge< 200.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge< 300.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge< 400.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=400.0; binLowerEdge< 500.1; binLowerEdge+=25.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 2.5) temp.push_back(binLowerEdge);
//    for(double binLowerEdge= 70.0; binLowerEdge<200.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=200.0; binLowerEdge<300.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
//    for(double binLowerEdge=300.0; binLowerEdge<400.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    return temp;
}

#endif
