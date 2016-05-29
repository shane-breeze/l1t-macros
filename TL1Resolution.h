#ifndef TL1RESOLUTION_H
#define TL1RESOLUTION_H

#include <string>
#include <memory>
#include <vector>

#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

#include "Core/TL1Plots.h"

class TL1Resolution : public TL1Plots
{
    public:
        ~TL1Resolution();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & yVal);
        virtual void DrawPlots();

        void SetBins(const std::vector<double> & bins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetY(const std::string & yName, const std::string & yTitle);
    private:
        std::shared_ptr<TH1F> fPlot;
        std::shared_ptr<TFile> fRootFile;

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
    fRootFile = std::shared_ptr<TFile>(new TFile(Form("res_%s.root",this->GetOutName().c_str()),"RECREATE"));
    fPlot = std::shared_ptr<TH1F>(new TH1F(Form("res_%s_over_%s",fXName.c_str(),fYName.c_str()),"", fBins.size()-1,&(fBins)[0]));
    fPlot->SetDirectory(0);
    fPlot->GetXaxis()->SetTitle(Form("%s / %s",fYTitle.c_str(),fXTitle.c_str()));
    fPlot->GetYaxis()->SetTitle("Number of Entries");
}

void TL1Resolution::Fill(const double & xVal, const double & yVal)
{
    double div = 0.0;
    if( xVal != 0.0 ) div = yVal/xVal;
    fPlot->Fill(div);
}

void TL1Resolution::DrawPlots()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1")); 
    fPlot->SetLineColor(kBlue);
    fPlot->Draw();
    fRootFile->WriteTObject(fPlot.get());
    //can->SetLogy();

    std::shared_ptr<TLatex> latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->SetTextAlign(12);
    latex->DrawLatex(0.18,0.85,"#bf{CMS}");
    if( this->GetSampleName() == "Data" )
    {
        latex->DrawLatex(0.18,0.80,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + this->GetRun() + ", ";
        latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),this->GetTriggerTitle().c_str()));
    }
    else
    {
        latex->DrawLatex(0.18,0.80,"#it{Simulation}");
        latex->DrawLatex(0.18,0.75,"#it{Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",this->GetSampleTitle().c_str()));
    }

    std::string outName = Form("res_%s.pdf", this->GetOutName().c_str());
    can->SaveAs(outName.c_str());
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
