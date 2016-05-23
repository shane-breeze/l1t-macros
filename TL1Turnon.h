#ifndef TL1TURNON_H
#define TL1TURNON_H

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

class TL1Turnon
{
    public:
        void InitDists();
        void Fill(const double & xVal, const double & seedVal);
        void DrawDists();
        void DrawTurnons();
        TF1 fit(TGraphAsymmErrors * eff, int p50);

        void SetSample(const std::string & sampleName, const std::string & sampleTitle);
        void SetTrigger(const std::string & triggerName, const std::string & triggerTitle);
        void SetRun(const std::string & run);
        void SetSeeds(const vector<double> & seeds);
        void SetXBins(const vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetSeed(const std::string & seedName, const std::string & seedTitle);
        void SetOutName(const std::string & outName);
        void SetFit(const bool & doFit);
    private:
        void SetMyStyle(int palette, double rmarg);
        void SetColor(float fraction, int index);

        std::vector<std::shared_ptr<TH1F>> fDists;
        std::vector<std::shared_ptr<TGraphAsymmErrors>> fTurnons;
        std::vector<std::shared_ptr<TF1>> fFits;

        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        vector<double> fSeeds, fXBins;
        std::string fXName, fSeedName;
        std::string fXTitle, fSeedTitle;
        std::string fOutName;
        bool fDoFit;
};

void TL1Turnon::InitDists()
{
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        fDists.emplace_back(new TH1F(Form("dist_%s_%s_%g",fXName.c_str(),fSeedName.c_str(),fSeeds[i]),"", fXBins.size()-1,&(fXBins)[0]));
        fDists[i]->SetDirectory(0);
        fDists[i]->GetXaxis()->SetTitle(fXTitle.c_str());
        fDists[i]->GetYaxis()->SetTitle("Number of Entries");
        SetColor((double)(i-1)/(double)(fSeeds.size()-2), i);
    }
}

void TL1Turnon::Fill(const double & xVal, const double & seedVal)
{
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        if( !(seedVal >= fSeeds[i]) ) break;
        fDists[i]->Fill(xVal);
    }
}

void TL1Turnon::DrawDists()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1")); 
    std::shared_ptr<TLegend> leg(new TLegend(0.55,0.35,0.85,0.55));
    for(unsigned i=0; i<fDists.size(); ++i)
    {
        if(i==0) fDists[i]->Draw();
        else fDists[i]->Draw("same");
        fDists[i]->Write();
        leg->AddEntry(fDists[i].get(), Form("%s > %g GeV", fSeedTitle.c_str(), fSeeds[i]));
    }
    can->SetLogy();
    leg->Draw();

    std::shared_ptr<TLatex> latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->SetTextAlign(32);
    latex->DrawLatex(0.89,0.85,"#bf{CMS}");
    if( fSampleName == "Data" )
    {
        latex->DrawLatex(0.89,0.80,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + fRun + ", ";
        latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),fTriggerTitle.c_str()));
    }
    else
    {
        latex->DrawLatex(0.89,0.80,"#it{Simulation}");
        latex->DrawLatex(0.89,0.75,"#it{Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",fSampleTitle.c_str()));
    }

    std::string outName = Form("dists_%s.pdf", fOutName.c_str());
    can->SaveAs(outName.c_str());
}

void TL1Turnon::DrawTurnons()
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1"));
    std::shared_ptr<TLegend> leg(new TLegend(0.62,0.15,0.87,0.15+0.2*fSeeds.size()/5.0));
    for(int i=1; i<fSeeds.size(); ++i)
    {
        fTurnons.emplace_back(new TGraphAsymmErrors(fDists[i].get(), fDists[0].get()));
        fTurnons[i-1]->SetLineColor(fDists[i]->GetLineColor());
        fTurnons[i-1]->SetMarkerColor(fDists[i]->GetMarkerColor());
        fTurnons[i-1]->GetXaxis()->SetTitle(fDists[i]->GetXaxis()->GetTitle());
        fTurnons[i-1]->GetXaxis()->SetLimits(fXBins.front(), fXBins.back());
        fTurnons[i-1]->GetYaxis()->SetTitle("Efficiency");
        if( i == 1 ) fTurnons[i-1]->Draw("ap");
        else fTurnons[i-1]->Draw("psame");
        fTurnons[i-1]->Write();
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
    if( fSampleName == "Data" )
    {
        latex->DrawLatex(0.17,0.84,"#bf{CMS}"); 
        latex->DrawLatex(0.17,0.79,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + fRun + ", ";
        latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),fTriggerTitle.c_str()));
    }
    else
    {
       
        latex->DrawLatex(0.17, 0.80, "#bf{CMS}");
        latex->DrawLatex(0.17, 0.75, "#it{Simulation}");
        latex->DrawLatex(0.17, 0.70, "#it{Preliminary}");
        latex->SetTextAlign(31); 
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",fSampleTitle.c_str()));
    }

    can->SaveAs(Form("effs_%s.pdf",fOutName.c_str()));
}

TF1 TL1Turnon::fit(TGraphAsymmErrors * eff, int p50)
{
    TF1 fitFcn( "fit_fcn","[0]*0.5*(1+TMath::Erf((x-[1])/(sqrt([2]))))",fXBins.front(),fXBins.back());
    if( fDoFit )
    {
        fitFcn.SetParameters( 0.937871,(double)p50,1378.23);
        TFitResultPtr fitRes_p = (TFitResultPtr)eff->Fit(fitFcn.GetName(),"ES0"); 
        //TFitResult* fitRes = (TFitResult*)fitRes_p.Get();

        fitFcn.SetLineColor(eff->GetLineColor());
    }

    return fitFcn;
}

void TL1Turnon::SetSample(const std::string & sampleName, const std::string & sampleTitle)
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
}

void TL1Turnon::SetTrigger(const std::string & triggerName, const std::string & triggerTitle)
{
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
}

void TL1Turnon::SetRun(const std::string & run)
{
    fRun = run;
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

void TL1Turnon::SetOutName(const std::string & outName)
{
    fOutName = outName;
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
    fDists[index]->SetLineColor(colour);
    fDists[index]->SetMarkerColor(colour);
}

#endif
