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
        TL1Turnon();

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

        const std::string & GetSampleName() const;
        const std::string & GetSampleTitle() const;
        const std::string & GetTriggerName() const;
        const std::string & GetTriggerTitle() const;
        const std::string & GetRun() const;
        const vector<double> & GetSeeds() const;
        const double & GetSeed(int i) const;
        const vector<double> & GetXBins() const;
        const double & GetXBin(int i) const;
        const std::string & GetXName() const;
        const std::string & GetXTitle() const;
        const std::string & GetSeedName() const;
        const std::string & GetSeedTitle() const;
        const std::string & GetOutName(std::string outName) const;
        const bool & IsFit(bool doFit) const;

    private:
        void SetMyStyle(int palette, double rmarg);
        void SetColor(float fraction, int index);

        std::shared_ptr<TStyle> fMyStyle;
        vector<std::shared_ptr<TH1F>> fDists;
        vector<std::shared_ptr<TGraphAsymmErrors>> fTurnons;
        vector<std::shared_ptr<TF1>> fFits;

        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        vector<double> fSeeds, fXBins;
        std::string fXName, fSeedName;
        std::string fXTitle, fSeedTitle;
        std::string fOutName;
        bool fDoFit;
};

TL1Turnon::TL1Turnon() :
    fMyStyle(new TStyle(TDRStyle()))
{
    SetMyStyle(55,0.07);
}

void TL1Turnon::InitDists()
{
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        fDists.emplace_back(new TH1F(Form("dist_%s_%s_%g",fXName.c_str(),fSeedName.c_str(),fSeeds[i]),"", fXBins.size()-1,&(fXBins)[0]));
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

const std::string & TL1Turnon::GetSampleName() const
{
    return fSampleName;
}

const std::string & TL1Turnon::GetSampleTitle() const
{
    return fSampleTitle;
}

const std::string & TL1Turnon::GetTriggerName() const
{
    return fTriggerName;
}

const std::string & TL1Turnon::GetTriggerTitle() const
{
    return fTriggerTitle;
}

const std::string & TL1Turnon::GetRun() const
{
    return fRun;
}

const vector<double> & TL1Turnon::GetSeeds() const
{
    return fSeeds;
}

const double & TL1Turnon::GetSeed(int i) const
{
    if( i < 0 || i >= fSeeds.size() ) throw "Index is out of fSeeds range";
    return fSeeds[i];
}

const vector<double> & TL1Turnon::GetXBins() const
{
    return fXBins;
}

const double & TL1Turnon::GetXBin(int i) const
{
    if( i < 0 || i >= fXBins.size() ) throw "Index is out of fXBins range";
    return fXBins[i];
}

const std::string & TL1Turnon::GetXName() const
{
    return fXName;
}

const std::string & TL1Turnon::GetXTitle() const
{
    return fXTitle;
}

const std::string & TL1Turnon::GetSeedName() const
{
    return fSeedName;
}

const std::string & TL1Turnon::GetSeedTitle() const
{
    return fSeedTitle;
}

const std::string & TL1Turnon::GetOutName(std::string outName) const
{
    return fOutName;
}

const bool & TL1Turnon::IsFit(bool doFit) const
{
    return fDoFit;
}

void TL1Turnon::SetColor(float fraction, int index)
{
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * (1.0-2.0*modifier) + modifier) * fMyStyle->GetNumberOfColors();
        colour = fMyStyle->GetColorPalette(colorIndex);
    }
    fDists[index]->SetLineColor(colour);
    fDists[index]->SetMarkerColor(colour);
}

void TL1Turnon::SetMyStyle(int palette, double rmarg)
{
    fMyStyle->SetCanvasDefW(800);
    fMyStyle->SetNumberContours(255);
    fMyStyle->SetPalette(palette);
    fMyStyle->SetPadRightMargin(rmarg);
    fMyStyle->cd();
}

#endif
