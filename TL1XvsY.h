#ifndef TL1XVSY_H
#define TL1XVSY_H

#include <string>
#include <memory>

#include <TStyle.h>
#include <TF1.h>
#include <TH1F.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TLine.h>

#include "Core/TL1EventClass.h"
#include "Core/tdrstyle.C"

class TL1XvsY
{
    public:
        void InitPlots();
        void Fill(const double & xVal, const double & yVal);
        void DrawPlots();

        void SetSample(const std::string & sampleName, const std::string & sampleTitle);
        void SetTrigger(const std::string & triggerName, const std::string & triggerTitle);
        void SetRun(const std::string & run);
        void SetXBins(const vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetYBins(const vector<double> & yBins);
        void SetY(const std::string & yName, const std::string & yTitle);
        void SetOutName(const std::string & outName);
        void SetAddMark(const std::string & addMark);
    private:
        std::shared_ptr<TH2F> fPlots;

        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        std::string fXName, fXTitle;
        std::string fYName, fYTitle;
        vector<double> fXBins, fYBins;
        std::string fOutName;

        std::string fAddMark;
};

void TL1XvsY::InitPlots()
{
    fPlots = std::shared_ptr<TH2F>(new TH2F(Form("xy_%s_vs_%s",fXName.c_str(),fYName.c_str()),"", fXBins.size()-1,&(fXBins)[0], fYBins.size()-1,&(fYBins)[0]));
    fPlots->SetDirectory(0);
    fPlots->GetXaxis()->SetTitle(fXTitle.c_str());
    fPlots->GetYaxis()->SetTitle(fYTitle.c_str());
}

void TL1XvsY::Fill(const double & xVal, const double & yVal)
{
    fPlots->Fill(xVal,yVal);
}

void TL1XvsY::DrawPlots()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1")); 
    fPlots->SetMinimum(1);
    fPlots->Draw("colz");
    fPlots->Write();
    can->SetLogz();

    std::shared_ptr<TLatex> latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->SetTextAlign(12);
    latex->DrawLatex(0.18,0.85,"#bf{CMS}");
    if( fSampleName == "Data" )
    {
        latex->DrawLatex(0.18,0.80,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + fRun + ", ";
        latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),fTriggerTitle.c_str()));
    }
    else
    {
        latex->DrawLatex(0.18,0.80,"#it{Simulation}");
        latex->DrawLatex(0.18,0.75,"#it{Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",fSampleTitle.c_str()));
    }
    latex->SetTextAlign(11);
    latex->DrawLatex(0.18,0.92,fAddMark.c_str());

    std::shared_ptr<TLine> line(new TLine());
    line->SetLineStyle(7);
    line->SetLineWidth(3);
    line->DrawLine(fXBins.front(),fYBins.front(),fXBins.back(),fYBins.back());

    std::string outName = Form("xy_%s.pdf", fOutName.c_str());
    can->SaveAs(outName.c_str());
}

void TL1XvsY::SetSample(const std::string & sampleName, const std::string & sampleTitle)
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
}

void TL1XvsY::SetTrigger(const std::string & triggerName, const std::string & triggerTitle)
{
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
}

void TL1XvsY::SetRun(const std::string & run)
{
    fRun = run;
}

void TL1XvsY::SetXBins(const vector<double> & xBins)
{
    fXBins = xBins;
}

void TL1XvsY::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1XvsY::SetYBins(const vector<double> & yBins)
{
    fYBins = yBins;
}

void TL1XvsY::SetY(const std::string & yName, const std::string & yTitle)
{
    fYName = yName;
    fYTitle = yTitle;
}

void TL1XvsY::SetOutName(const std::string & outName)
{
    fOutName = outName;
}

void TL1XvsY::SetAddMark(const std::string & addMark)
{
    fAddMark = addMark;
}

#endif
