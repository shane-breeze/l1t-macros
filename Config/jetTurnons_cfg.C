#include "jetTurnons_cfg.h"

// All Jet Turnons
std::map<std::string &, TL1Turnon *> jetTurnons(const std::string & triggerName, const bool & doFit)
{
    std::map<std::string &, TL1Turnon *> turnons;
    turnons.emplace("jetEtBarrel", new TL1Turnon(jetEtBarrel(triggerName, doFit)));
    turnons.emplace("jetEtEndcap", new TL1Turnon(jetEtEndcap(triggerName, doFit)));
    turnons.emplace("jetEtCentral", new TL1Turnon(jetEtCentral(triggerName, doFit)));
    turnons.emplace("jetEtHF", new TL1Turnon(jetEtHF(triggerName, doFit))();
    return turnons;
}

// Jet Et - barrel
TL1Turnon jetEtBarrel(const std::string & triggerName, const bool & doFit)
{
    TL1Turnon turnon();
    turnon->SetSeed("l1JetEt", "L1 Jet E_{T}");
    turnon->SetSeeds({0., 36., 68., 128., 200.});
    turnon->SetX("recoJetEt", "Offline Jet E_{T} (GeV)");
    turnon->SetXBins(bins());
    turnon->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_barrel");
    turnon->SetFit(doFit);
    turnon->SetAddMark("|#eta| < 1.479");
    return turnon;
}

// Jet Et - end cap
TL1Turnon jetEtEndcap(const std::string & triggerName, const bool & doFit)
{
    TL1Turnon turnon();
    turnon->SetSeed("l1JetEt", "L1 Jet E_{T}");
    turnon->SetSeeds({0., 36., 68., 128., 200.});
    turnon->SetX("recoJetEt", "Offline Jet E_{T} (GeV)");
    turnon->SetXBins(bins());
    turnon->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_endcap");
    turnon->SetFit(doFit);
    turnon->SetAddMark("1.479 < |#eta| < 3.0");
    return turnon;
}

// Jet Et - central
TL1Turnon jetEtCentral(const std::string & triggerName, const bool & doFit)
{
    TL1Turnon turnon();
    turnon->SetSeed("l1JetEt", "L1 Jet E_{T}");
    turnon->SetSeeds({0., 36., 68., 128., 200.});
    turnon->SetX("recoJetEt", "Offline Jet E_{T} (GeV)");
    turnon->SetXBins(bins());
    turnon->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_central");
    turnon->SetFit(doFit);
    turnon->SetAddMark("|#eta| < 3.0");
    return turnon;
}

// Jet Et - HF
TL1Turnon jetEtHF(const std::string & triggerName, const bool & doFit)
{
    TL1Turnon turnon();
    turnon->SetSeed("l1JetEt", "L1 Jet E_{T}");
    turnon->SetSeeds({0., 36., 68., 128., 200.});
    turnon->SetX("recoJetEt", "Offline Jet E_{T} (GeV)");
    turnon->SetXBins(bins());
    turnon->SetOutName(triggerName+"_recoJetEt_l1JetEtSeeds_hf");
    turnon->SetFit(doFit);
    turnon->SetAddMark("|#eta| > 3.0");
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
