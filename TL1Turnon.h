#ifndef TL1TURNON_H
#define TL1TURNON_H

#include <string>
#include <memory>

#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TLine.h>

#include "Core/TL1Plots.h"

class TL1Turnon : public TL1Plots
{
    public:
        ~TL1Turnon();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & seedVal);
        virtual void DrawPlots();
        void DrawTurnons();
        TF1 fit(TGraphAsymmErrors * eff, int p50);

        void SetSeeds(const vector<double> & seeds);
        void SetXBins(const vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetSeed(const std::string & seedName, const std::string & seedTitle);
        void SetFit(const bool & doFit);
    private:
        void SetColor(float fraction, int index);

        std::vector<std::shared_ptr<TH1F>> fPlots;
        std::vector<std::shared_ptr<TGraphAsymmErrors>> fTurnons;
        std::vector<std::shared_ptr<TF1>> fFits;

        std::shared_ptr<TFile> fPlotsRoot;
        std::shared_ptr<TFile> fTurnonsRoot;

        vector<double> fSeeds, fXBins;
        std::string fXName, fSeedName;
        std::string fXTitle, fSeedTitle;
        bool fDoFit;
};

TL1Turnon::~TL1Turnon()
{
    fPlotsRoot->Close();
    fTurnonsRoot->Close();
}

void TL1Turnon::InitPlots()
{
    fPlotsRoot = std::shared_ptr<TFile>(new TFile(Form("%s/dists_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE"));
    fTurnonsRoot = std::shared_ptr<TFile>(new TFile(Form("%s/effs_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE"));
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        fPlots.emplace_back(new TH1F(Form("dist_%s_%s_%g",fXName.c_str(),fSeedName.c_str(),fSeeds[i]),"", fXBins.size()-1,&(fXBins)[0]));
        fPlots[i]->SetDirectory(0);
        fPlots[i]->GetXaxis()->SetTitle(fXTitle.c_str());
        fPlots[i]->GetYaxis()->SetTitle("Number of Entries");
        SetColor((double)(i-1)/(double)(fSeeds.size()-2), i);
    }
}

void TL1Turnon::Fill(const double & xVal, const double & seedVal)
{
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        if( !(seedVal >= fSeeds[i]) ) break;
        fPlots[i]->Fill(xVal);
    }
}

void TL1Turnon::DrawPlots()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1")); 
    std::shared_ptr<TLegend> leg(new TLegend(0.55,0.35,0.85,0.55));
    for(unsigned i=0; i<fPlots.size(); ++i)
    {
        if(i==0) fPlots[i]->Draw();
        else fPlots[i]->Draw("same");
        fPlotsRoot->WriteTObject(fPlots[i].get());
        leg->AddEntry(fPlots[i].get(), Form("%s > %g GeV", fSeedTitle.c_str(), fSeeds[i]));
    }
    can->SetLogy();
    leg->Draw();

    std::shared_ptr<TLatex> latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->SetTextAlign(32);
    latex->DrawLatex(0.89,0.85,"#bf{CMS}");
    if( this->GetSampleName() == "Data" )
    {
        latex->DrawLatex(0.89,0.80,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + this->GetRun() + ", ";
        latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),this->GetTriggerTitle().c_str()));
    }
    else
    {
        latex->DrawLatex(0.89,0.80,"#it{Simulation}");
        latex->DrawLatex(0.89,0.75,"#it{Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",this->GetSampleTitle().c_str()));
    }
    latex->SetTextAlign(11);
    latex->DrawLatex(0.18,0.92,this->GetAddMark().c_str());

    std::string outName = Form("%s/dists_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());
}

void TL1Turnon::DrawTurnons()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1"));
    std::shared_ptr<TLegend> leg(new TLegend(0.62,0.15,0.87,0.15+0.2*fSeeds.size()/5.0));
    for(int i=1; i<fSeeds.size(); ++i)
    {
        fTurnons.emplace_back(new TGraphAsymmErrors(fPlots[i].get(), fPlots[0].get()));
        fTurnons[i-1]->SetLineColor(fPlots[i]->GetLineColor());
        fTurnons[i-1]->SetMarkerColor(fPlots[i]->GetMarkerColor());
        fTurnons[i-1]->GetXaxis()->SetTitle(fPlots[i]->GetXaxis()->GetTitle());
        fTurnons[i-1]->GetXaxis()->SetLimits(fXBins.front(), fXBins.back());
        fTurnons[i-1]->GetYaxis()->SetTitle("Efficiency");
        fTurnons[i-1]->SetMinimum(0.0);
        fTurnons[i-1]->SetMaximum(1.1);
        if( i == 1 ) fTurnons[i-1]->Draw("ap");
        else fTurnons[i-1]->Draw("psame");
        fTurnonsRoot->WriteTObject(fTurnons[i-1].get());
        fFits.emplace_back(new TF1(fit(fTurnons[i-1].get(), fSeeds[i])));
        if( fDoFit ) fFits[i-1]->Draw("lsame");
        leg->AddEntry(fTurnons[i-1].get(), Form("%s > %g",fSeedTitle.c_str(),fSeeds[i]));
    }
    leg->Draw();
    
    std::shared_ptr<TLatex> latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    double min = fXBins.front();
    double max = fXBins.back();
    std::shared_ptr<TLine> line(new TLine(min,1.,max,1.));
    line->SetLineStyle(7);
    line->DrawClone();
    if( this->GetSampleName() == "Data" )
    {
        latex->DrawLatex(0.17,0.84,"#bf{CMS}"); 
        latex->DrawLatex(0.17,0.79,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + this->GetRun() + ", ";
        latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),this->GetTriggerTitle().c_str()));
    }
    else
    {
       
        latex->DrawLatex(0.17, 0.80, "#bf{CMS}");
        latex->DrawLatex(0.17, 0.75, "#it{Simulation}");
        latex->DrawLatex(0.17, 0.70, "#it{Preliminary}");
        latex->SetTextAlign(31); 
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",this->GetSampleTitle().c_str()));
    }
    latex->SetTextAlign(11);
    latex->DrawLatex(0.18,0.92,this->GetAddMark().c_str());

    can->SaveAs(Form("%s/effs_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str()));
}

TF1 TL1Turnon::fit(TGraphAsymmErrors * eff, int p50)
{
    std::string func = Form("[0]*0.5*(1+TMath::Erf((x-[1])/TMath::Sqrt([2])))");
    TF1 fitFcn( "fit_fcn",func.c_str(),fXBins.front(),fXBins.back());
    if( fDoFit )
    {
        fitFcn.SetParameters( 1.0000,(double)p50,200.0);
        //fitFcn.SetParameters( 0.937871,(double)p50,1378.23);
        TFitResultPtr fitRes_p = (TFitResultPtr)eff->Fit(fitFcn.GetName(),"ES0"); 
        //TFitResult* fitRes = (TFitResult*)fitRes_p.Get();

        fitFcn.SetLineColor(eff->GetLineColor());
    }

    return fitFcn;
}

void TL1Turnon::SetSeeds(const vector<double> & seeds)
{
    fSeeds = seeds;
}

void TL1Turnon::SetXBins(const vector<double> & xBins)
{
    fXBins = xBins;
}

void TL1Turnon::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

void TL1Turnon::SetSeed(const std::string & seedName, const std::string & seedTitle)
{
    fSeedName = seedName;
    fSeedTitle = seedTitle;
}

void TL1Turnon::SetFit(const bool & doFit)
{
    fDoFit = doFit;
}

void TL1Turnon::SetColor(float fraction, int index)
{
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * (1.0-2.0*modifier) + modifier) * gStyle->GetNumberOfColors();
        colour = gStyle->GetColorPalette(colorIndex);
    }
    fPlots[index]->SetLineColor(colour);
    fPlots[index]->SetMarkerColor(colour);
}

#endif
