#ifndef TL1DIST_H
#define TL1DIST_H

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
#include "../Debug/DebugHandler.h"

class TL1Dist : public TL1Plots
{
    public:
        ~TL1Dist();
        
        virtual void InitPlots();
        virtual void OverwritePlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu=0);
        virtual void DrawPlots();
        TH1F * GetCumulative(TH1F * plot);
        void PlotE2(TH1F * plot, bool puOn);
        void DrawCmsStamp();

        void SetX(const std::string & xName, const std::string & xTitle);
        void SetXBins(const std::vector<double> & xBins);
        
    private:
        std::vector<TH1F*> fL1Plot;
        std::vector<TH1F*> fOfflinePlot;
        TFile * fRootFile;

        std::string fXName, fXTitle;
        std::vector<double> fXBins;

};

TL1Dist::~TL1Dist()
{
    fRootFile->Close();
    delete fRootFile;
}

void TL1Dist::InitPlots()
{
    fRootFile = TFile::Open(Form("%s/rates_%s.root", this->GetOutDir().c_str(), this->GetOutName().c_str()), "RECREATE");

    fL1Plot.emplace_back(new TH1F(Form("rates_%s",fXName.c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    fL1Plot.back()->Sumw2();
    fL1Plot.back()->SetDirectory(0);
    fL1Plot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    fL1Plot.back()->GetYaxis()->SetTitle("Number of events");

    fOfflinePlot.emplace_back(new TH1F(Form("rates_%s",fYName.c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    fOfflinePlot.back()->Sumw2();
    fOfflinePlot.back()->SetDirectory(0);
    fOfflinePlot.back()->GetXaxis()->SetTitle(fYTitle.c_str());
    fOfflinePlot.back()->GetYaxis()->SetTitle("Number of events");

    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fL1Plot.emplace_back(new TH1F(Form("rates_%s_%s",fXName.c_str(),this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
        fL1Plot.back()->Sumw2();
        fL1Plot.back()->SetDirectory(0);
        fL1Plot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
        fL1Plot.back()->GetYaxis()->SetTitle("Number of events");

        fOfflinePlot.emplace_back(new TH1F(Form("rates_%s_%s",fYName.c_str(),this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
        fOfflinePlot.back()->Sumw2();
        fOfflinePlot.back()->SetDirectory(0);
        fOfflinePlot.back()->GetXaxis()->SetTitle(fYTitle.c_str());
        fOfflinePlot.back()->GetYaxis()->SetTitle("Number of events");
    }
}

void TL1Dist::OverwritePlots()
{
    fL1Plot.clear();
    fOfflinePlot.clear();
    TFile * rootFile = TFile::Open(this->GetOverwriteRootFilename().c_str(), "READ");
    fRootFile = TFile::Open(Form("%s/rates_%s_overwrite.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");

    std::string histName = Form(this->GetOverwriteHistname().c_str(), fXName.c_str());
    fL1Plot.push_back((TH1F*)rootFile->Get(histName.c_str()));
    fL1Plot.back()->SetDirectory(0);
    fL1Plot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    fL1Plot.back()->GetYaxis()->SetTitle("Number of events");

    histName = Form(this->GetOverwriteHistname().c_str(), fYName.c_str());
    fOfflinePlot.push_back((TH1F*)rootFile->Get(histName.c_str()));
    fOfflinePlot.back()->SetDirectory(0);
    fOfflinePlot.back()->GetXaxis()->SetTitle(fYTitle.c_str());
    fOfflinePlot.back()->GetYaxis()->SetTitle("Number of events");

    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fL1Plot.push_back((TH1F*)rootFile->Get(Form("%s_%s",this->GetOverwriteHistname().c_str(),this->GetPuType()[ipu].c_str())));
        fL1Plot.back()->SetDirectory(0);
        fL1Plot.back()->GetXaxis()->SetTitle(fXTitle.c_str());
        fL1Plot.back()->GetYaxis()->SetTitle("Rate (Hz)");
    }
    rootFile->Close();
    delete rootFile;
}

void TL1Dist::Fill(const double & xVal, const double & yVal, const int & pu=0)
{
    fL1Plot[0]->Fill(xVal,this->GetPuWeight(pu));
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        if( pu >= this->GetPuBins()[ipu] && pu < this->GetPuBins()[ipu+1] )
            fL1Plot[ipu+1]->Fill(xVal,this->GetPuWeight(pu));
    }
}

void TL1Dist::DrawPlots()
{
    TCanvas * can(new TCanvas(Form("can_%f",this->GetRnd()),""));
    
    this->SetColor(fL1Plot[0], 0, 3);
    fRootFile->WriteTObject(fL1Plot[0]);
    fL1Plot[0]->DrawCopy("E2");
    fL1Plot[0]->DrawCopy("histsame");
    DrawCmsStamp();

    std::string outName = Form("%s/dist_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());
    delete can;

    if( !(this->GetPuType().size() > 0) ) return;

    TCanvas * can2(new TCanvas(Form("can_%f",this->GetRnd()),""));
    TLegend * leg2(new TLegend(0.65,0.55,0.88,0.55+0.05*this->GetPuType().size()));
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        this->SetColor(fL1Plot[ipu+1], ipu, this->GetPuType().size());
        fRootFile->WriteTObject(fL1Plot[ipu+1]);

        if( ipu == 0 ) fL1Plot[ipu+1]->DrawCopy("E2");
        else fL1Plot[ipu+1]->Draw("E2same");
        fL1Plot[ipu+1]->DrawCopy("histsame");

        std::stringstream entryName;
        if( ipu<this->GetPuType().size()-1 ) entryName << this->GetPuBins()[ipu] << " #leq PU < " << this->GetPuBins()[ipu+1];
        else entryName << this->GetPuBins()[ipu] << " #leq PU";
        leg2->AddEntry(fL1Plot[ipu+1], entryName.str().c_str());
        entryName.str("");
    }
    can2->SetLogy();
    DrawCmsStamp();
    leg2->Draw();
    can2->Update();

    outName = Form("%s/dist_%s_puBins.pdf", this->GetOutDir().c_str(), this->GetOutName().c_str());
    can2->SaveAs(outName.c_str());
    delete can2;
}

void TL1Dist::DrawCmsStamp()
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
    latex->DrawLatex(0.87,0.82,this->GetAddMark().c_str());
}

void TL1Dist::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1Dist::SetXBins(const std::vector<double> & xBins)
{
    fXBins = xBins; 
}

#endif
