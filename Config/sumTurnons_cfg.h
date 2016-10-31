#ifndef SUMTURNONS_CFG_H
#define SUMTURNONS_CFG_H

#include <string>
#include <vector>
#include <map>

#include "../Plotting/TL1Turnon.h"
#include "ntuple_cfg.h"

TL1Turnon metBE(ntuple_cfg const * dataset);
TL1Turnon htt(ntuple_cfg const * dataset);
std::vector<double> metBins();
std::vector<double> mhtBins();
std::vector<double> ettBins();
std::vector<double> httBins();

// All Sums Turnons
std::map< std::string, TL1Turnon* > sumTurnons(ntuple_cfg const * dataset)
{
    std::map< std::string, TL1Turnon* > turnons;
    turnons.emplace("metBE", new TL1Turnon(metBE(dataset)));
    turnons.emplace("htt", new TL1Turnon(htt(dataset)));
    return turnons;
}

// caloMetBE and l1MetBE seeds
TL1Turnon metBE(ntuple_cfg const * dataset)
{
    TL1Turnon turnon;
    std::string seed = "l1MetBESeed";
    std::string xparam = "caloMetBE";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+seed;
    turnon.SetOverwriteNames(dataset->baseOWdir+"/Turnons/dists_"+outName+".root", "dist_"+xparam+"_"+seed);
    turnon.SetSeed(seed, "L1 MET BE");
    turnon.SetSeeds({0., 40., 60., 80., 100., 120.});
    turnon.SetX(xparam, "Offline E_{T}^{miss} BE (GeV)");
    turnon.SetXBins(metBins());
    turnon.SetOutName(outName);
    turnon.SetFit(dataset->doFit);
    return turnon;
}

// htt and l1Htt seeds
TL1Turnon htt(ntuple_cfg const * dataset)
{
    TL1Turnon turnon;
    std::string seed = "l1HttSeed";
    std::string xparam = "recoHtt";
    std::string outName = dataset->triggerName+"_"+xparam+"_"+seed;
    turnon.SetOverwriteNames(dataset->baseOWdir+"/Turnons/dists_"+outName+".root", "dist_"+xparam+"_"+seed);
    turnon.SetSeed(seed, "L1 HTT");
    turnon.SetSeeds({0., 40., 60., 80., 100., 120.});
    turnon.SetX(xparam, "Offline Total H_{T} (GeV)");
    turnon.SetXBins(httBins());
    turnon.SetOutName(outName);
    turnon.SetFit(dataset->doFit);
    return turnon;
}

vector<double> metBins()
{
    vector<double> temp;

    //for(double binLowerEdge=  0.0; binLowerEdge< 200.1; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);

    for(double binLowerEdge=  0.0; binLowerEdge< 40.0; binLowerEdge+=  2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+=  5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 70.0; binLowerEdge< 90.0; binLowerEdge+= 10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 90.0; binLowerEdge<150.0; binLowerEdge+= 20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=150.0; binLowerEdge<300.0; binLowerEdge+= 50.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge<400.0; binLowerEdge+=100.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=400.0; binLowerEdge<800.1; binLowerEdge+=200.0) temp.push_back(binLowerEdge);

    return temp;
}

vector<double> mhtBins()
{
    vector<double> temp;
    //for(double binLowerEdge=-30.0; binLowerEdge<  0.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 30.0; binLowerEdge< 50.0; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge= 25.0; binLowerEdge< 50.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 50.0; binLowerEdge< 80.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 80.0; binLowerEdge<140.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=140.0; binLowerEdge<200.0; binLowerEdge+=15.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge<300.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge<400.1; binLowerEdge+=50.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> ettBins()
{
    vector<double> temp;
    //for(double binLowerEdge=-30.0; binLowerEdge<  0.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=  0.0; binLowerEdge< 30.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 30.0; binLowerEdge< 50.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 50.0; binLowerEdge< 90.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 90.0; binLowerEdge<140.1; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge=100.0; binLowerEdge<700.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> httBins()
{
    vector<double> temp;
    for(double binLowerEdge=  0.0; binLowerEdge< 100.0; binLowerEdge+=  2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge< 200.0; binLowerEdge+=  5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge< 400.0; binLowerEdge+= 10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=400.0; binLowerEdge< 500.0; binLowerEdge+= 25.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=500.0; binLowerEdge< 600.0; binLowerEdge+= 50.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=600.0; binLowerEdge<1000.0; binLowerEdge+=100.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=1000.0; binLowerEdge<8000.1; binLowerEdge+=200.0) temp.push_back(binLowerEdge);

    return temp;

}

#endif
