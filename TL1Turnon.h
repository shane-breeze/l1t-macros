#ifndef TL1TURNON_H
#define TL1TURNON_H

#include <iostream>
#include <memory>

#include <TStyle.h>

#include "TL1EventClass.h"
#include "tdrstyle.C"

class TL1Turnon
{
    public:
        TL1Turnon();

        void Fill(const double & xVal, const double & seedVal);

        void SetSample(const std::string & sampleName, const std::string & sampleTitle);
        void SetTrigger(const std::string & triggerName, const std::String & triggerTitle);
        void SetRun(const std::string & run);
        void SetSeeds(const vector<double> & seeds);
        void SetXBins(const vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetSeed(const std::string & seedName, const std::string & seedTitle);
        void SetOutName(const std::string & outName);
        void SetFit(const bool & doFit);

        const std::string & GetSampleName() const;
        const std::string & GetSampleTitle() const;
        const std::string & GetTriggerName() const;
        const std::string & GetTriggerTitle() const;
        const std::string & GetRun() const;
        const vector<double> & GetSeeds() const;
        const double & GetSeed(int i) const;
        const vector<double> & GetXBins() const;
        const double & GetXBin(int i) const;
        const std::string & GetXName() const;
        const std::string & GetXTitle() const;
        const std::string & GetSeedName() const;
        const std::string & GetSeedTitle() const;
        const std::string & GetOutName(std::string outName) const;
        const bool & IsFit(bool doFit) const;

    private:
        std::shared_ptr<TStyle> fMyStyle;
        vector<std::shared_ptr<TH1F>> fDists;
        vector<std::shared_ptr<TGraphAsymmErrors>> fTurnons;

        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        vector<double> fSeeds, fXBins;
        std::string fXName, fSeedName;
        std::string fXTitle, fSeedTitle;
        std::string outName;
        bool fDoFit;
};

TL1Turnon::TL1Turnon() :
    fMyStyle(new TStyle(TDRStyle())),
{
    SetMyStyle(55,0.07,fMyStyle.Get());
}

void TL1Turnon::SetSample(const std::string & sampleName, const std::string & sampleTitle)
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
}

void TL1Turnon::SetTrigger(const std::string & triggerName, const std::String & triggerTitle)
{
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
}

void TL1Turnon::SetRun(const std::string & run)
{
    fRun = run;
}

void TL1Turnon::SetSeeds(const vector<double> & seeds)
{
    fSeeds = seeds;
}

void TL1Turnon::SetXBins(const vector<double> & xBins)
{
    fXBins = xBins;
}

void TL1Turnon::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1Turnon::SetSeed(const std::string & seedName, const std::string & seedTitle)
{
    fSeedName = seedName;
    fSeedTitle = seedTitle;
}

void TL1Turnon::SetOutName(const std::string & outName)
{
    fOutName = outName;
}

void TL1Turnon::SetFit(const bool & doFit)
{
    fDoFit = doFit;
}

const std::string & TL1Turnon::GetSampleName() const
{
    return fSampleName;
}

const std::string & TL1Turnon::GetSampleTitle() const
{
    return fSampleTitle;
}

const std::string & TL1Turnon::GetTriggerName() const
{
    return fTriggerName;
}

const std::string & TL1Turnon::GetTriggerTitle() const
{
    return fTriggerTitle;
}

const std::string & TL1Turnon::GetRun() const
{
    return fRun;
}

const vector<double> & TL1Turnon::GetSeeds() const
{
    return fSeeds;
}

const double & TL1Turnon::GetSeed(int i) const
{
    if( i < 0 || i >= fSeeds.size() ) throw "Index is out of fSeeds range";
    return fSeeds[i];
}

const vector<double> & TL1Turnon::GetXBins() const
{
    return fXBins;
}

const double & TL1Turnon::GetXBin(int i) const
{
    if( i < 0 || i >= fXBins.size() ) throw "Index is out of fXBins range";
    return fXBins[i];
}

const std::string & TL1Turnon::GetXName() const
{
    return fXName;
}

const std::string & TL1Turnon::GetXTitle() const
{
    return fXTitle;
}

const std::string & TL1Turnon::GetSeedName() const
{
    return fSeedName;
}

const std::string & TL1Turnon::GetSeedTitle() const
{
    return fSeedTitle;
}

const std::string & TL1Turnon::GetOutName(std::string outName) const
{
    return fOutName;
}

const bool & TL1Turnon::IsFit(bool doFit) const
{
    return fDoFit;
}

#endif
