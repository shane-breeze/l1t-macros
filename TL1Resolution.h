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

#include "TL1EventClass.h"
#include "tdrstyle.C"

class TL1Resolution
{
    public:
        void InitPlots();
        void Fill(const double & xVal, const double & yVal);
        void DrawPlots();

        void SetSample(const std::string & sampleName, const std::string & sampleTitle);
        void SetTrigger(const std::string & triggerName, const std::string & triggerTitle);
        void SetRun(const std::string & run);
        void SetBins(const vector<double> & bins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetY(const std::string & yName, const std::string & yTitle);
        void SetOutName(const std::string & outName);
    private:
        std::shared_ptr<TH1F> fPlots;

        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        std::string fXName, fXTitle;
        std::string fYName, fYTitle;
        vector<double> fBins;
        std::string fOutName;
};

void TL1Resolution::InitPlots()
{
    fPlots = std::shared_ptr<TH1F>(new TH1F(Form("res_%s_over_%s",fXName.c_str(),fYName.c_str()),"", fBins.size()-1,&(fBins)[0]));
    fPlots->SetDirectory(0);
    fPlots->GetXaxis()->SetTitle(Form("%s / %s",fYTitle.c_str(),fXTitle.c_str()));
    fPlots->GetYaxis()->SetTitle("Number of Entries");
}

void TL1Resolution::Fill(const double & xVal, const double & yVal)
{
    double div = 0.0;
    if( xVal != 0.0 ) div = yVal/xVal;
    fPlots->Fill(div);
}

void TL1Resolution::DrawPlots()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1")); 
    fPlots->SetLineColor(kBlue);
    fPlots->Draw();
    fPlots->Write();
    //can->SetLogy();

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

    std::string outName = Form("res_%s.pdf", fOutName.c_str());
    can->SaveAs(outName.c_str());
}

void TL1Resolution::SetSample(const std::string & sampleName, const std::string & sampleTitle)
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
}

void TL1Resolution::SetTrigger(const std::string & triggerName, const std::string & triggerTitle)
{
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
}

void TL1Resolution::SetRun(const std::string & run)
{
    fRun = run;
}

void TL1Resolution::SetBins(const vector<double> & bins)
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

void TL1Resolution::SetOutName(const std::string & outName)
{
    fOutName = outName;
}

#endif
