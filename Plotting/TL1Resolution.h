#ifndef TL1RESOLUTION_H
#define TL1RESOLUTION_H

#include <string>
#include <vector>
#include <sstream>

#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>

#include "TL1Plots.h"
#include "../Debug/DebugHandler.h"

class TL1Resolution : public TL1Plots
{
    public:
        ~TL1Resolution();

        virtual void InitPlots();
        virtual void OverwritePlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu=0);
        virtual void DrawPlots();

        void SetBins(const std::vector<double> & bins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetY(const std::string & yName, const std::string & yTitle);
        void SetPlotType(const std::string & plotType);
        void DrawCmsStamp();

        std::string GetXAxisTitle() const;
        double GetFillVal(const double & xVal, const double & yVal) const;

    private:
        std::vector<TH1F*> fPlot;
        TFile * fRootFile;

        std::string fXName, fXTitle;
        std::string fYName, fYTitle;
        std::vector<double> fBins;

        std::string fPlotType;

};

TL1Resolution::~TL1Resolution()
{
    delete fRootFile;
    for(auto it=fPlot.begin(); it!=fPlot.end(); ++it) delete *it;
    fPlot.clear();
}

void TL1Resolution::InitPlots()
{
    fRootFile = TFile::Open(Form("%s/res_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");
    DebugHandler::CheckTFile(fRootFile, __FILE__, __LINE__);

    fPlot.emplace_back(new TH1F(Form("res_%s_%s_%s",fPlotType.c_str(),fXName.c_str(),fYName.c_str()),"", fBins.size()-1,&(fBins)[0]));
    fPlot.back()->SetDirectory(0);
    fPlot.back()->Sumw2();
    fPlot.back()->GetXaxis()->SetTitle(GetXAxisTitle().c_str());
    fPlot.back()->GetYaxis()->SetTitle("a.u.");
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fPlot.emplace_back(new TH1F(Form("res_%s_%s_%s_%s",fPlotType.c_str(),fXName.c_str(),fYName.c_str(),this->GetPuType()[ipu].c_str()),"", fBins.size()-1,&(fBins)[0]));
        fPlot.back()->SetDirectory(0);
        fPlot.back()->Sumw2();
        fPlot.back()->GetXaxis()->SetTitle(GetXAxisTitle().c_str());
        fPlot.back()->GetYaxis()->SetTitle("a.u.");
    }
}

void TL1Resolution::OverwritePlots()
{
    fPlot.clear();
    TFile * rootFile = TFile::Open(this->GetOverwriteRootFilename().c_str(),"READ");
    DebugHandler::CheckTFile(rootFile, __FILE__, __LINE__);

    fRootFile = TFile::Open(Form("%s/res_%s_overwrite.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");
    DebugHandler::CheckTFile(fRootFile, __FILE__, __LINE__);

    fPlot.push_back((TH1F*)rootFile->Get(this->GetOverwriteHistname().c_str()));
    fPlot.back()->SetDirectory(0);
    fPlot.back()->GetXaxis()->SetTitle(GetXAxisTitle().c_str());
    fPlot.back()->GetYaxis()->SetTitle("a.u.");
    double norm(fPlot.back()->Integral());
    if( norm > 0.0 ) fPlot.back()->Scale(1./norm);

    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        fPlot.push_back((TH1F*)rootFile->Get(Form("%s_%s",this->GetOverwriteHistname().c_str(),this->GetPuType()[ipu].c_str())));
        fPlot.back()->SetDirectory(0);
        fPlot.back()->GetXaxis()->SetTitle(GetXAxisTitle().c_str());
        fPlot.back()->GetYaxis()->SetTitle("a.u.");
        norm = fPlot.back()->Integral();
        if( norm > 0.0 ) fPlot.back()->Scale(1./norm);
    }
    delete rootFile;
}

void TL1Resolution::Fill(const double & xVal, const double & yVal, const int & pu=0)
{
    double div(GetFillVal(xVal, yVal));
    fPlot[0]->Fill(div,this->GetPuWeight(pu));
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        if( pu >= this->GetPuBins()[ipu] && pu < this->GetPuBins()[ipu+1] )
            fPlot[ipu+1]->Fill(div,this->GetPuWeight(pu));
    }
}

void TL1Resolution::DrawPlots()
{
    TCanvas * can(new TCanvas(Form("can_%f",this->GetRnd()),"")); 

    fPlot[0]->SetLineColor(kBlue-4);
    fPlot[0]->SetMarkerColor(kBlue-4);
    fPlot[0]->SetMinimum(0.0);
    fPlot[0]->Draw("pe");
    fPlot[0]->Draw("histsame");
    fRootFile->WriteTObject(fPlot[0]);

    //TF1 * fitFcn(new TF1(Form("fit_%s",fPlot[0]->GetName()),"gaus(0)",-1,3));
    //fPlot[0]->Fit(fitFcn,"E0");
    //for(int i=0; i<10; ++i) fPlot[0]->Fit(fitFcn,"E0M");
    //fitFcn->SetLineColor(fPlot[0]->GetLineColor());
    //fitFcn->Draw("same");
    //fRootFile->WriteTObject(fitFcn);

    DrawCmsStamp();
    TLine * line(new TLine());
    line->SetLineStyle(7);
    //can->Update();
    line->SetNDC();
    line->DrawLine(0.0,0.0,0.0,can->GetUymax());

    std::string outName = Form("%s/res_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());
    delete can;

    THStack * stack(new THStack("hs",""));
    double norm(0.0);
    for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    {
        this->SetColor(fPlot[ipu+1], ipu, this->GetPuType().size()); 
        fPlot[ipu+1]->SetMinimum(0.0);
        fRootFile->WriteTObject(fPlot[ipu+1]);

        std::string entryName("");
        if( ipu < this->GetPuType().size()-1 ) entryName = Form("%i #leq PU < %i",this->GetPuBins()[ipu],this->GetPuBins()[ipu+1]);
        else entryName = Form("%i #leq PU",this->GetPuBins()[ipu]);
        fPlot[ipu+1]->SetName(entryName.c_str());

        stack->Add(fPlot[ipu+1],"pe");

        //TF1 * fitFcn2(new TF1(Form("fit_%s",fPlot[i+1]->GetName()),"gaus(0)",-1,3));
        //fPlot[i+1]->Fit(fitFcn2,"E0");
        //for(int j=0; j<10; ++j) fPlot[i+1]->Fit(fitFcn2,"E0M");
        //fitFcn2->SetLineColor(fPlot[i+1]->GetLineColor());
        //fitFcn2->Draw("same");
        //fRootFile->WriteTObject(fitFcn2);
    }

    TCanvas * can2(new TCanvas(Form("can_%f",this->GetRnd()),"")); 
    TLegend * leg(new TLegend(0.65,0.55,0.88,0.55+0.05*this->GetPuType().size()));
    leg->AddEntry(stack);

    stack->Draw("nostack");
    leg->Draw();
    DrawCmsStamp();

    //can2->Update();
    line->DrawLine(0.0,0.0,0.0,can2->GetUymax());
    outName = Form("%s/res_%s_puBins.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can2->SaveAs(outName.c_str());
    delete can2;
    delete leg;
    delete stack;
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

void TL1Resolution::SetPlotType(const std::string & plotType)
{
    fPlotType = plotType;
}

void TL1Resolution::DrawCmsStamp()
{
    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->SetTextAlign(11);
    if( this->GetSampleName() == "Data" )
        latex->DrawLatex(0.15,0.92,Form("#bf{CMS} #it{Preliminary} %s",this->GetSampleTitle().c_str()));
    else
        latex->DrawLatex(0.15,0.92,Form("#bf{CMS} #it{Simulation Preliminary} %s",this->GetSampleTitle().c_str()));
    latex->SetTextAlign(31);
    latex->DrawLatex(0.92,0.92,Form("%s (13 TeV)",this->GetRun().c_str()));
    latex->DrawLatex(0.9,0.8,this->GetAddMark().c_str());
}

std::string TL1Resolution::GetXAxisTitle() const
{
    std::string temp("");
    if( fPlotType == "Energy" ) temp = Form("(%s - %s)/%s",fYTitle.c_str(),fXTitle.c_str(),fXTitle.c_str());
    else if( fPlotType == "Position" ) temp = Form("%s - %s",fYTitle.c_str(),fXTitle.c_str());
    return temp;
}

double TL1Resolution::GetFillVal(const double & xVal, const double & yVal) const
{
    double div(0.0);
    if( fPlotType == "Energy" )
    {
        if( xVal != 0.0 )
            div = (yVal-xVal)/xVal;
    }
    else if( fPlotType == "Position" )
    {
        div = yVal - xVal;
    }
    return div;
}

#endif
