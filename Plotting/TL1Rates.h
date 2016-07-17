#ifndef TL1RATES_H
#define TL1RATES_H

#include <string>
#include <vector>
#include <sstream>

#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>
#include <TLatex.h>
#include <TStyle.h>

#include "TL1Plots.h"

class TL1Rates : public TL1Plots
{
    public:
        ~TL1Rates();
        
        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu);
        virtual void DrawPlots();
        void DrawCmsStamp();

        void SetX(const std::string & xName, const std::string & xTitle);
        void SetXBins(const std::vector<double> & xBins);
        void SetColor(TH1F * plot, float fraction, int index);
        
    private:
        std::vector<TH1F*> fPlot;
        TFile * fRootFile;

        std::string fXName, fXTitle;
        std::vector<double> fXBins;

};

TL1Rates::~TL1Rates()
{
    fRootFile->Close();
}

void TL1Rates::InitPlots()
{
    fRootFile = new TFile(Form("%s/rates_%s.root", this->GetOutDir().c_str(), this->GetOutName().c_str()), "RECREATE");
    fPlot.emplace_back(new TH1F(Form("rates_%s",fXName.c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    fPlot.back()->Sumw2();
    fPlot.back()->SetDirectory(0);
    fPlot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    fPlot.back()->GetYaxis()->SetTitle("Rate (Hz)");
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fPlot.emplace_back(new TH1F(Form("rates_%s_%s",fXName.c_str(),this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
        fPlot.back()->Sumw2();
        fPlot.back()->SetDirectory(0);
        fPlot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
        fPlot.back()->GetYaxis()->SetTitle("Rate (Hz)");
    }
}

void TL1Rates::Fill(const double & xVal, const double & yVal, const int & pu)
{
    fPlot[0]->Fill(xVal,pu);
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        if( pu >= this->GetPuBins()[ipu] && pu < this->GetPuBins()[ipu+1] )
            fPlot[ipu+1]->Fill(xVal,pu);
    }
}

void TL1Rates::DrawPlots()
{
    TCanvas * can(new TCanvas("c1","c1"));
    TH1F * fCumulative = (TH1F*)fPlot[0]->GetCumulative(false);
    double bin1 = fCumulative->GetBinContent(1);
    fCumulative->Scale(4.0e7/bin1);

    fRootFile->WriteTObject(fPlot[0]);
    fRootFile->WriteTObject(fCumulative);

    fCumulative->Draw();
    can->SetLogy();

    DrawCmsStamp();

    std::string outName = Form("%s/rates_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());

    TCanvas * can2(new TCanvas("c2","c2"));
    TLegend * leg2(new TLegend(0.65,0.55,0.88,0.55+0.05*this->GetPuType().size()));
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        TH1F * fPuCumulative = (TH1F*)fPlot[ipu+1]->GetCumulative(false);
        bin1 = fPuCumulative->GetBinContent(1);
        fPuCumulative->Scale(4.0e7/bin1);

        this->SetColor(fPuCumulative, (double)(this->GetPuType().size()-ipu-1)/(double)(this->GetPuType().size()-2),ipu+1);

        fRootFile->WriteTObject(fPlot[ipu+1]);
        fRootFile->WriteTObject(fPuCumulative);

        if( ipu==0 ) fPuCumulative->Draw();
        else fPuCumulative->Draw("same");

        std::stringstream entryName;
        if( ipu<this->GetPuType().size()-1 ) entryName << this->GetPuBins()[ipu] << " #leq PU < " << this->GetPuBins()[ipu+1];
        else entryName << this->GetPuBins()[ipu] << " #leq PU";
        leg2->AddEntry(fPuCumulative, entryName.str().c_str());
        entryName.str("");
    }
    can2->SetLogy();
    DrawCmsStamp();
    leg2->Draw();
    can2->Update();

    outName = Form("%s/rates_%s_puBins.pdf", this->GetOutDir().c_str(), this->GetOutName().c_str());
    can2->SaveAs(outName.c_str());
}

void TL1Rates::DrawCmsStamp()
{
    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    if( this->GetSampleName() == "Data" )
    {
        latex->DrawLatex(0.15,0.92,"#bf{CMS} #it{Preliminary} 2016 Data");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92,0.92,Form("%s (13 TeV)",this->GetRun().c_str()));
    }
    else
    {
        latex->DrawLatex(0.15,0.92,"#bf{CMS} #it{Simulation Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92,0.92,Form("%s (13 TeV)",this->GetSampleName().c_str()));
    }
    latex->SetTextAlign(32);
    latex->DrawLatex(0.82,0.25,this->GetAddMark().c_str());
}

void TL1Rates::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1Rates::SetXBins(const std::vector<double> & xBins)
{
    fXBins = xBins; 
}

void TL1Rates::SetColor(TH1F * plot, float fraction, int index)
{
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * (1.0-2.0*modifier) + modifier) * gStyle->GetNumberOfColors();
        colour = gStyle->GetColorPalette(colorIndex);
    }
    plot->SetLineColor(colour);
    plot->SetMarkerColor(colour);
}

#endif
