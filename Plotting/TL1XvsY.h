#ifndef TL1XVSY_H
#define TL1XVSY_H

#include <string>
#include <vector>

#include <TFile.h>
#include <TH2F.h>

#include "TL1Plots.h"

class TL1XvsY : public TL1Plots
{
    public:
        ~TL1XvsY();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu);
        virtual void DrawPlots();

        void SetXBins(const std::vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetYBins(const std::vector<double> & yBins);
        void SetY(const std::string & yName, const std::string & yTitle);
    private:
        TH2F * fPlot;
        std::vector<TH2F*> fPuPlots;
        TFile * fRootFile;

        std::string fXName, fXTitle;
        std::string fYName, fYTitle;
        std::vector<double> fXBins, fYBins;

};

TL1XvsY::~TL1XvsY()
{
    fRootFile->Close();
}

void TL1XvsY::InitPlots()
{
    fRootFile = new TFile(Form("%s/xy_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");

    fPlot = new TH2F(Form("xy_%s_vs_%s",fXName.c_str(),fYName.c_str()),"", fXBins.size()-1,&(fXBins)[0], fYBins.size()-1,&(fYBins)[0]);
    fPlot->SetDirectory(0);
    fPlot->GetXaxis()->SetTitle(fXTitle.c_str());
    fPlot->GetYaxis()->SetTitle(fYTitle.c_str());

    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fPuPlots.emplace_back(new TH2F(Form("xy_%s_vs_%s_%s",fXName.c_str(),fYName.c_str(), this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0], fYBins.size()-1,&(fYBins)[0]));
        fPuPlots.back()->SetDirectory(0);
        fPuPlots.back()->GetXaxis()->SetTitle(fXTitle.c_str());
        fPuPlots.back()->GetYaxis()->SetTitle(fYTitle.c_str());
    }
}

void TL1XvsY::Fill(const double & xVal, const double & yVal, const int & pu)
{
    fPlot->Fill(xVal,yVal);
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        if( pu >= this->GetPuBins()[ipu] && pu < this->GetPuBins()[ipu+1] )
            fPuPlots[ipu]->Fill(xVal,yVal);
    }
}

void TL1XvsY::DrawPlots()
{
    fPlot->SetMinimum(1);
    fRootFile->WriteTObject(fPlot);

    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fPuPlots[ipu]->SetMinimum(1);
        fRootFile->WriteTObject(fPuPlots[ipu]);
    }
}

void TL1XvsY::SetXBins(const std::vector<double> & xBins)
{
    fXBins = xBins;
}

void TL1XvsY::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1XvsY::SetYBins(const std::vector<double> & yBins)
{
    fYBins = yBins;
}

void TL1XvsY::SetY(const std::string & yName, const std::string & yTitle)
{
    fYName = yName;
    fYTitle = yTitle;
}

#endif
