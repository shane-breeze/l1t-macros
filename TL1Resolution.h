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
        virtual void Fill(const double & xVal, const double & yVal, const int & pu);
        virtual void DrawPlots();

        void SetBins(const std::vector<double> & bins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetY(const std::string & yName, const std::string & yTitle);
        void SetColor(float fraction, int index);

    private:
        std::vector<std::shared_ptr<TH1F>> fPlot;
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
    fRootFile = std::shared_ptr<TFile>(new TFile(Form("%s/res_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE"));

    fPlot.emplace_back(new TH1F(Form("res_%s_over_%s",fXName.c_str(),fYName.c_str()),"", fBins.size()-1,&(fBins)[0]));
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        fPlot.emplace_back(new TH1F(Form("res_%s_over_%s_%s",fXName.c_str(),fYName.c_str(),this->GetPuType()[i].c_str()),"", fBins.size()-1,&(fBins)[0]));
        fPlot.back()->SetDirectory(0);
        fPlot.back()->GetXaxis()->SetTitle(Form("%s / %s",fYTitle.c_str(),fXTitle.c_str()));
        fPlot.back()->GetYaxis()->SetTitle("a.u.");
    }
}

void TL1Resolution::Fill(const double & xVal, const double & yVal, const int & pu)
{
    double div = 0.0;
    if( xVal != 0.0 ) div = yVal/xVal;
    fPlot[0]->Fill(div);
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        if( pu >= this->GetPuBins()[i] && pu < this->GetPuBins()[i+1] )
            fPlot[i+1]->Fill(div);
    }
}

void TL1Resolution::DrawPlots()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1")); 

    fPlot[0]->SetLineColor(kBlack);
    fPlot[0]->SetMarkerColor(kBlack);
    fPlot[0]->Sumw2();
    fPlot[0]->Scale(1./fPlot[0]->Integral());
    fPlot[0]->Draw("pe");
    fRootFile->WriteTObject(fPlot[0].get());

    std::shared_ptr<TF1> fitFcn(new TF1(Form("fit_%s",fPlot[0]->GetName()),"gaus(0)",-1,3));
    fPlot[0]->Fit(fitFcn.get(),"E0");
    for(int i=0; i<10; ++i) fPlot[0]->Fit(fitFcn.get(),"E0M");
    fitFcn->SetLineColor(kBlue-4);
    fitFcn->Draw("same");

    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        this->SetColor((double)(i-1)/(double)(this->GetPuType().size()-2),i);
        fPlot[i+1]->Sumw2();
        fPlot[i+1]->Scale(1./fPlot[i+1]->Integral());
        fPlot[i+1]->Draw("pesame");
        fRootFile->WriteTObject(fPlot[i+1].get());

        std::shared_ptr<TF1> fitFcn(new TF1(Form("fit_%s",fPlot[i+1]->GetName()),"gaus(0)",-1,3));
        fPlot[i+1]->Fit(fitFcn.get(),"E0");
        for(int j=0; j<10; ++j) fPlot[i+1]->Fit(fitFcn.get(),"E0M");
        fitFcn->SetLineColor(fPlot[i+1]->GetLineColor());
        fitFcn->Draw("same");
        fRootFile->WriteTObject(fitFcn.get());
    }
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
    latex->SetTextAlign(11);
    latex->DrawLatex(0.18,0.92,this->GetAddMark().c_str());

    std::shared_ptr<TLine> line(new TLine());
    line->SetLineColor(kRed-4);
    line->SetLineStyle(7);
    line->DrawLine(1.0,0.0,1.0,fPlot[0]->GetMaximum()*1.05);

    std::string outName = Form("%s/res_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
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

void TL1Resolution::SetColor(float fraction, int index)
{
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * (1.0-2.0*modifier) + modifier) * gStyle->GetNumberOfColors();
        colour = gStyle->GetColorPalette(colorIndex);
    }
    fPlot[index]->SetLineColor(colour);
    fPlot[index]->SetMarkerColor(colour);
}

#endif
