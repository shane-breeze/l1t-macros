#ifndef TL1RESOLUTION_H
#define TL1RESOLUTION_H

#include <string>
#include <vector>

#include <TFile.h>
#include <TH1F.h>

#include "TL1Plots.h"

class TL1Resolution : public TL1Plots
{
    public:
        ~TL1Resolution();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu);
        virtual void DrawPlots();

        void SetBins(const std::vector<double> & bins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetY(const std::string & yName, const std::string & yTitle);

    private:
        TH1F * fPlot;
        std::vector<TH1F*> fPuPlots;
        TFile * fRootFile;

        std::string fXName, fXTitle;
        std::string fYName, fYTitle;
        std::vector<double> fBins;

};

TL1Resolution::~TL1Resolution()
{
    fRootFile->Close();
}

void TL1Resolution::InitPlots()
{
    fRootFile = new TFile(Form("%s/res_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");

    fPlot = new TH1F(Form("res_%s_minus_%s", fYName.c_str(), fXName.c_str()), "", fBins.size()-1,&(fBins)[0]);
    fPlot->SetDirectory(0);
    fPlot->GetXaxis()->SetTitle(Form("%s - %s",fYTitle.c_str(),fXTitle.c_str()));
    fPlot->GetYaxis()->SetTitle("a.u.");
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        fPuPlots.emplace_back(new TH1F(Form("res_%s_over_%s_%s",fYName.c_str(),fXName.c_str(),this->GetPuType()[i].c_str()),"", fBins.size()-1,&(fBins)[0]));
        fPuPlots.back()->SetDirectory(0);
        fPuPlots.back()->GetXaxis()->SetTitle(Form("%s - %s",fYTitle.c_str(),fXTitle.c_str()));
        fPuPlots.back()->GetYaxis()->SetTitle("a.u.");
    }

}

void TL1Resolution::Fill(const double & xVal, const double & yVal, const int & pu)
{
    //double div = 0.0;
    //if( xVal != 0.0 ) div = yVal/xVal;
    //fPlot[0]->Fill(div);
    fPlot->Fill((yVal-xVal));
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        if( pu >= this->GetPuBins()[i] && pu < this->GetPuBins()[i+1] )
            fPuPlots[i]->Fill((yVal-xVal));
    }
}

void TL1Resolution::DrawPlots()
{
    fPlot->Sumw2();
    fPlot->Scale(1./fPlot->Integral());
    fPlot->SetMinimum(0.0);
    fRootFile->WriteTObject(fPlot);

    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        fPuPlots[i]->Sumw2();
        fPuPlots[i]->Scale(1./fPuPlots[i]->Integral());
        fPuPlots[i]->SetMinimum(0.0);
        fRootFile->WriteTObject(fPuPlots[i]);
    }
}

void TL1Resolution::SetBins(const std::vector<double> & bins)
{
    fBins = bins;
}

void TL1Resolution::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1Resolution::SetY(const std::string & yName, const std::string & yTitle)
{
    fYName = yName;
    fYTitle = yTitle;
}

#endif
