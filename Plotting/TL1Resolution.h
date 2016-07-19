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

class TL1Resolution : public TL1Plots
{
    public:
        ~TL1Resolution();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu=0);
        virtual void DrawPlots();

        void SetBins(const std::vector<double> & bins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetY(const std::string & yName, const std::string & yTitle);
        void SetPlotType(const std::string & plotType);
        void DrawCmsStamp(std::string stampPos="Left");

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
    fRootFile->Close();
}

void TL1Resolution::InitPlots()
{
    fRootFile = new TFile(Form("%s/res_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");

    fPlot.emplace_back(new TH1F(Form("res_%s_%s_%s",fPlotType.c_str(),fXName.c_str(),fYName.c_str()),"", fBins.size()-1,&(fBins)[0]));
    fPlot.back()->SetDirectory(0);
    fPlot.back()->GetXaxis()->SetTitle(GetXAxisTitle().c_str());
    fPlot.back()->GetYaxis()->SetTitle("a.u.");
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        fPlot.emplace_back(new TH1F(Form("res_%s_%s__%s%s",fPlotType.c_str(),fXName.c_str(),fYName.c_str(),this->GetPuType()[i].c_str()),"", fBins.size()-1,&(fBins)[0]));
        fPlot.back()->SetDirectory(0);
        fPlot.back()->GetXaxis()->SetTitle(GetXAxisTitle().c_str());
        fPlot.back()->GetYaxis()->SetTitle("a.u.");
    }
}

void TL1Resolution::Fill(const double & xVal, const double & yVal, const int & pu=0)
{
    double div = GetFillVal(xVal, yVal);
    fPlot[0]->Fill(div);
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        if( pu >= this->GetPuBins()[i] && pu < this->GetPuBins()[i+1] )
            fPlot[i+1]->Fill(div);
    }
}

void TL1Resolution::DrawPlots()
{
    TCanvas * can(new TCanvas("c1","c1")); 

    fPlot[0]->SetLineColor(kBlue-4);
    fPlot[0]->SetMarkerColor(kBlue-4);
    fPlot[0]->Sumw2();
    fPlot[0]->Scale(1./fPlot[0]->Integral());
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
    can->Update();
    line->SetNDC();
    line->DrawLine(0.0,0.0,0.0,can->GetUymax());

    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->SetTextAlign(31);
    //latex->DrawLatex(0.9,0.7,Form("#splitline{%s}{<PU>=14}",this->GetAddMark().c_str()));
    latex->DrawLatex(0.9,0.7,Form("%s",this->GetAddMark().c_str()));

    std::string outName = Form("%s/res_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());

    TCanvas * can2(new TCanvas("c2","c2")); 
    TLegend * leg(new TLegend(0.65,0.55,0.88,0.55+0.05*this->GetPuType().size()));
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        this->SetColor(fPlot[i+1], i, this->GetPuType().size());
        fPlot[i+1]->Sumw2();
        fPlot[i+1]->Scale(1./fPlot[i+1]->Integral());
        fPlot[i+1]->SetMinimum(0.0);
        fPlot[i+1]->SetMaximum(1.1*fPlot[i+1]->GetMaximum());
        if( i==0 ) fPlot[i+1]->Draw("pe");
        else fPlot[i+1]->Draw("pesame");
        fPlot[i+1]->Draw("histsame");
        fRootFile->WriteTObject(fPlot[i+1]);

        TF1 * fitFcn2(new TF1(Form("fit_%s",fPlot[i+1]->GetName()),"gaus(0)",-1,3));
        //fPlot[i+1]->Fit(fitFcn2,"E0");
        //for(int j=0; j<10; ++j) fPlot[i+1]->Fit(fitFcn2,"E0M");
        fitFcn2->SetLineColor(fPlot[i+1]->GetLineColor());
        //fitFcn2->Draw("same");
        //fRootFile->WriteTObject(fitFcn2);
        
        std::stringstream entryName;
        if( i < this->GetPuType().size()-1 ) entryName << this->GetPuBins()[i] << " #leq PU < " << this->GetPuBins()[i+1];
        else entryName << this->GetPuBins()[i] << " #leq PU";
        leg->AddEntry(fPlot[i+1],entryName.str().c_str());
        entryName.str("");
    }
    DrawCmsStamp();
    latex->DrawLatex(0.9,0.8,this->GetAddMark().c_str());
    leg->Draw();
    can2->Update();
    line->DrawLine(0.0,0.0,0.0,can2->GetUymax());

    outName = Form("%s/res_%s_puBins.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can2->SaveAs(outName.c_str());
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

void TL1Resolution::DrawCmsStamp(std::string stampPos="Left")
{
    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    if( stampPos == "Left" )
    {
        latex->SetTextAlign(11);
        latex->DrawLatex(0.15,0.92,"#bf{CMS} #it{Preliminary} 2016 Data");
    }
    if( stampPos == "Right" )
    {
        latex->SetTextAlign(32);
        latex->DrawLatex(0.86,0.85,"#bf{CMS}");
    }
    if( this->GetSampleName() == "Data" )
    {
        //if( stampPos == "Left" ) latex->DrawLatex(0.18,0.80,"#it{Preliminary}");
        if( stampPos == "Right" ) latex->DrawLatex(0.86,0.80,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + this->GetRun() + ", ";
        //latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),this->GetTriggerTitle().c_str()));
        latex->DrawLatex(0.92,0.92,Form("%s (13 TeV)",this->GetRun().c_str()));
    }
    else
    {
        latex->DrawLatex(0.18,0.80,"#it{Simulation}");
        latex->DrawLatex(0.18,0.75,"#it{Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",this->GetSampleTitle().c_str()));
    }
    latex->SetTextAlign(11);
    //latex->DrawLatex(0.18,0.92,this->GetAddMark().c_str());

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
