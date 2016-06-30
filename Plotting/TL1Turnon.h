#ifndef TL1TURNON_H
#define TL1TURNON_H

#include <string>

#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TGraphAsymmErrors.h>

#include "TL1Plots.h"

class TL1Turnon : public TL1Plots
{
    public:
        ~TL1Turnon();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & seedVal, const int & pu);
        virtual void DrawPlots();
        void DrawTurnons();
        TF1 fit(TGraphAsymmErrors * eff, int p50);

        void SetSeeds(const vector<double> & seeds);
        void SetXBins(const vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetSeed(const std::string & seedName, const std::string & seedTitle);
        void SetFit(const bool & doFit);

    private:
        std::vector<TH1F*> fPlots;
        std::vector<std::vector<TH1F*>> fPuPlots;
        std::vector<TGraphAsymmErrors*> fTurnons;
        std::vector<std::vector<TGraphAsymmErrors*>> fPuTurnons;
        std::vector<TF1*> fFits;
        std::vector<std::vector<TF1*>> fPuFits;

        TFile* fPlotsRoot;
        TFile* fTurnonsRoot;

        vector<double> fSeeds, fXBins;
        std::string fXName, fSeedName;
        std::string fXTitle, fSeedTitle;
        bool fDoFit;

};

TL1Turnon::~TL1Turnon()
{
    fPlotsRoot->Close();
    fTurnonsRoot->Close();
}

void TL1Turnon::InitPlots()
{
    fPlotsRoot = new TFile(Form("%s/dists_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");
    fTurnonsRoot = new TFile(Form("%s/effs_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        fPlots.emplace_back(new TH1F(Form("dist_%s_%s_%g",fXName.c_str(),fSeedName.c_str(),fSeeds[i]),"", fXBins.size()-1,&(fXBins)[0]));
        fPlots.back()->SetDirectory(0);
        fPlots.back()->GetXaxis()->SetTitle(fXTitle.c_str());
        fPlots.back()->GetYaxis()->SetTitle("Number of Entries");

        std::vector<TH1F*> singleSeedPlots;
        for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
        {
            singleSeedPlots.emplace_back(new TH1F(Form("dist_%s_%s_%g_%s",fXName.c_str(),fSeedName.c_str(),fSeeds[i],this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
            singleSeedPlots.back()->SetDirectory(0);
            singleSeedPlots.back()->GetXaxis()->SetTitle(fXTitle.c_str());
            singleSeedPlots.back()->GetYaxis()->SetTitle("Number of Entries");
        }
        fPuPlots.push_back(singleSeedPlots);
    }
}

void TL1Turnon::Fill(const double & xVal, const double & seedVal, const int & pu)
{
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        if( seedVal < fSeeds[i] ) break;
        fPlots[i]->Fill(xVal);

        for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
        {
            if( pu >= this->GetPuBins()[ipu] && pu < this->GetPuBins()[ipu+1] )
                fPuPlots[i][ipu]->Fill(xVal);
        }
    }
}

void TL1Turnon::DrawPlots()
{
    for(unsigned i=0; i<fPlots.size(); ++i)
    {
        fPlotsRoot->WriteTObject(fPlots[i]);

        for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
            fPlotsRoot->WriteTObject(fPuPlots[i][ipu]);
    }
}

void TL1Turnon::DrawTurnons()
{
    for(int i=1; i<fSeeds.size(); ++i)
    {
        TGraphAsymmErrors * turnon(new TGraphAsymmErrors(fPlots[i], fPlots[0]));
        turnon->GetXaxis()->SetTitle(fPlots[i]->GetXaxis()->GetTitle());
        turnon->GetXaxis()->SetLimits(fXBins.front(), fXBins.back());
        turnon->GetYaxis()->SetTitle("Efficiency");
        turnon->SetMinimum(0.0);
        turnon->SetMaximum(1.1);
        fTurnonsRoot->WriteTObject(turnon);

        TF1 * turnonFit(new TF1(fit(turnon, fSeeds[i])));
        fTurnonsRoot->WriteTObject(turnonFit);

        for(int ipu=0; ipu<GetPuType().size(); ++ipu)
        {
            TGraphAsymmErrors * puTurnon(new TGraphAsymmErrors(fPuPlots[i][ipu], fPuPlots[0][ipu]));
            puTurnon->GetXaxis()->SetTitle(fPuPlots[i][ipu]->GetXaxis()->GetTitle());
            puTurnon->GetXaxis()->SetLimits(fXBins.front(), fXBins.back());
            puTurnon->GetYaxis()->SetTitle("Efficiency");
            puTurnon->SetMinimum(0.0);
            puTurnon->SetMaximum(1.1);
            fTurnonsRoot->WriteTObject(puTurnon);

            TF1 * puTurnonFit(new TF1(fit(puTurnon, fSeeds[i])));
            fTurnonsRoot->WriteTObject(puTurnonFit);
        }
    }
}

TF1 TL1Turnon::fit(TGraphAsymmErrors * eff, int p50)
{
    std::string func = Form("[0]*0.5*(1+TMath::Erf((x-[1])/TMath::Sqrt([2])))");
    TF1 fitFcn(Form("fit_%s",eff->GetName()),func.c_str(),fXBins.front(),fXBins.back());
    if( fDoFit )
    {
        fitFcn.SetParameters( 1.0000,(double)p50,150.0);
        eff->Fit(fitFcn.GetName(),"E0"); 

        for(int i=0; i<10; ++i)
            eff->Fit(fitFcn.GetName(),"E0M");

        fitFcn.SetLineColor(eff->GetLineColor());
    }

    return fitFcn;
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

void TL1Turnon::SetFit(const bool & doFit)
{
    fDoFit = doFit;
}

#endif
