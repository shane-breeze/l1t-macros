#ifndef TL1XVSY_H
#define TL1XVSY_H

#include <string>
#include <memory>
#include <vector>

#include <TFile.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TLine.h>

#include "Core/tdrstyle.C"
#include "Core/TL1Plots.h"

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
        std::shared_ptr<TH2F> fPlot;
        std::shared_ptr<TFile> fRootFile;

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
    fRootFile = std::shared_ptr<TFile>(new TFile(Form("%s/xy_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE"));
    fPlot = std::shared_ptr<TH2F>(new TH2F(Form("xy_%s_vs_%s",fXName.c_str(),fYName.c_str()),"", fXBins.size()-1,&(fXBins)[0], fYBins.size()-1,&(fYBins)[0]));
    fPlot->SetDirectory(0);
    fPlot->GetXaxis()->SetTitle(fXTitle.c_str());
    fPlot->GetYaxis()->SetTitle(fYTitle.c_str());
}

void TL1XvsY::Fill(const double & xVal, const double & yVal)
{
    fPlot->Fill(xVal,yVal);
}

void TL1XvsY::DrawPlots()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1")); 
    fPlot->SetMinimum(1);
    fPlot->Draw("colz");
    fRootFile->WriteTObject(fPlot.get());
    can->SetLogz();

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
    latex->SetTextAlign(11);
    latex->DrawLatex(0.18,0.92,this->GetAddMark().c_str());

    std::shared_ptr<TLine> line(new TLine());
    line->SetLineStyle(7);
    line->SetLineWidth(3);
    line->DrawLine(fXBins.front(),fYBins.front(),fXBins.back(),fYBins.back());

    std::string outName = Form("%s/xy_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());
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
