#ifndef TL1TURNON_H
#define TL1TURNON_H

#include <string>

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
        virtual void Fill(const double & xVal, const double & seedVal, const int & pu);
        virtual void DrawPlots();
        void DrawCmsStamp(std::string stampPos="Left");
        void DrawTurnons();
        void DrawCmsStampTurnon();
        TF1 fit(TGraphAsymmErrors * eff, int p50);


        void SetSeeds(const vector<double> & seeds);
        void SetXBins(const vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetSeed(const std::string & seedName, const std::string & seedTitle);
        void SetFit(const bool & doFit);
    private:
        void SetColor(TH1F * hist, float fraction, int index);

        std::vector<std::vector<TH1F*>> fPlots;
        std::vector<std::vector<TGraphAsymmErrors*>> fTurnons;
        std::vector<std::vector<TF1*>> fFits;

        TFile* fPlotsRoot;
        TFile* fTurnonsRoot;

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
    fPlotsRoot = new TFile(Form("%s/dists_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");
    fTurnonsRoot = new TFile(Form("%s/effs_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        std::vector<TH1F*> temp;
        temp.emplace_back(new TH1F(Form("dist_%s_%s_%g",fXName.c_str(),fSeedName.c_str(),fSeeds[i]),"", fXBins.size()-1,&(fXBins)[0]));
        temp.back()->SetDirectory(0);
        temp.back()->GetXaxis()->SetTitle(fXTitle.c_str());
        temp.back()->GetYaxis()->SetTitle("Number of Entries");
        SetColor(temp.back(), (double)(i-1)/(double)(fSeeds.size()-2), i);

        for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
        {
            temp.emplace_back(new TH1F(Form("dist_%s_%s_%g_%s",fXName.c_str(),fSeedName.c_str(),fSeeds[i],this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
            temp.back()->SetDirectory(0);
            temp.back()->GetXaxis()->SetTitle(fXTitle.c_str());
            temp.back()->GetYaxis()->SetTitle("Number of Entries");
            SetColor(temp.back(), (double)(ipu)/(double)(this->GetPuType().size()-2), ipu);
        }
        fPlots.push_back(temp);
    }
}

void TL1Turnon::Fill(const double & xVal, const double & seedVal, const int & pu)
{
    for(unsigned i=0; i<fSeeds.size(); ++i)
    {
        if( !(seedVal >= fSeeds[i]) ) break;
        fPlots[i][0]->Fill(xVal);

        for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
        {
            if( pu >= this->GetPuBins()[ipu] && pu < this->GetPuBins()[ipu+1] )
                fPlots[i][ipu+1]->Fill(xVal);
        }
    }
}

void TL1Turnon::DrawPlots()
{
    TCanvas * can(new TCanvas("c1","c1")); 
    TLegend * leg(new TLegend(0.58,0.35,0.88,0.55));
    for(unsigned i=0; i<fPlots.size(); ++i)
    {
        if(i==0) fPlots[i][0]->Draw();
        else fPlots[i][0]->Draw("same");
        fPlotsRoot->WriteTObject(fPlots[i][0]);
        leg->AddEntry(fPlots[i][0], Form("%s > %g GeV", fSeedTitle.c_str(), fSeeds[i]));

        for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
        {
            fPlots[i][ipu+1]->Draw("same");
            fPlotsRoot->WriteTObject(fPlots[i][ipu+1]);

            std::stringstream entryName;
            if( ipu < this->GetPuType().size()-1 ) entryName << this->GetPuBins()[ipu] << " #leq PU < " << this->GetPuBins()[ipu+1];
            else entryName << this->GetPuBins()[ipu] << " #leq PU";
            leg->AddEntry(fPlots[i][ipu+1],entryName.str().c_str());
            entryName.str("");
        }
    }
    can->SetLogy();
    leg->Draw();

    DrawCmsStamp();

    std::string outName = Form("%s/dists_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());
}

void TL1Turnon::DrawCmsStamp(std::string stampPos="Left")
{
    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->SetTextAlign(32);
    latex->DrawLatex(0.18,0.92,"#bf{CMS} #it{Preliminary}");
    latex->DrawLatex(0.92,0.92,"(13 TeV)");
    if( this->GetSampleName() == "Data" )
    {
        //latex->DrawLatex(0.89,0.80,"#it{Preliminary}");
        latex->SetTextAlign(31);
        std::string runNo = "run " + this->GetRun() + ", ";
        //latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),this->GetTriggerTitle().c_str()));
        //latex->DrawLatex(0.92,0.92,"(13 TeV)");
    }
    else
    {
        latex->DrawLatex(0.89,0.80,"#it{Simulation}");
        latex->DrawLatex(0.89,0.75,"#it{Preliminary}");
        latex->SetTextAlign(31);
        latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",this->GetSampleTitle().c_str()));
    }
    latex->SetTextAlign(11);
    //latex->DrawLatex(0.18,0.92,this->GetAddMark().c_str());
}

void TL1Turnon::DrawTurnons()
{
    TCanvas * nomCan(new TCanvas("c1","c1"));
    TLegend * nomLeg(new TLegend(0.62,0.15,0.87,0.15+0.2*(2+fSeeds.size())/5.0,this->GetAddMark().c_str()));
    for(int i=1; i<fSeeds.size(); ++i)
    {
        std::vector<TGraphAsymmErrors*> temp;
        temp.emplace_back(new TGraphAsymmErrors(fPlots[i][0], fPlots[0][0]));
        temp[0]->SetLineColor(fPlots[i][0]->GetLineColor());
        temp[0]->SetMarkerColor(fPlots[i][0]->GetMarkerColor());
        temp[0]->GetXaxis()->SetTitle(fPlots[i][0]->GetXaxis()->GetTitle());
        temp[0]->GetXaxis()->SetLimits(fXBins.front(), fXBins.back());
        temp[0]->GetYaxis()->SetTitle("Efficiency");
        temp[0]->SetMinimum(0.0);
        temp[0]->SetMaximum(1.1);
        nomCan->cd();
        if( i == 1 ) temp[0]->Draw("ap");
        else temp[0]->Draw("psame");
        fTurnonsRoot->WriteTObject(temp[0]);

        std::vector<TF1*> fitTemp;
        fitTemp.emplace_back(new TF1(fit(temp[0], fSeeds[i])));
        if( fDoFit ) fitTemp[0]->Draw("apsame");
        fTurnonsRoot->WriteTObject(fitTemp[0]);
        nomLeg->AddEntry(temp[0], Form("%s > %g",fSeedTitle.c_str(),fSeeds[i]));

        TCanvas * puCan(new TCanvas(Form("puCan_%i",i),"puCan"));
        TLegend * puLeg(new TLegend(0.65,0.15,0.9,0.15+0.08*this->GetPuType().size(),Form("%s > %g",fSeedTitle.c_str(),fSeeds[i])));
        for(int ipu=0; ipu<GetPuType().size(); ++ipu)
        {
            temp.emplace_back(new TGraphAsymmErrors(fPlots[i][ipu+1], fPlots[0][ipu+1]));
            temp[ipu+1]->SetLineColor(fPlots[i][ipu+1]->GetLineColor());
            temp[ipu+1]->SetMarkerColor(fPlots[i][ipu+1]->GetMarkerColor());
            temp[ipu+1]->GetXaxis()->SetTitle(fPlots[i][ipu+1]->GetXaxis()->GetTitle());
            temp[ipu+1]->GetXaxis()->SetLimits(fXBins.front(), fXBins.back());
            temp[ipu+1]->GetYaxis()->SetTitle("Efficiency");
            temp[ipu+1]->SetMinimum(0.0);
            temp[ipu+1]->SetMaximum(1.1);
            puCan->cd();
            if( ipu == 0 ) temp[ipu+1]->Draw("ap");
            else temp[ipu+1]->Draw("psame");
            fTurnonsRoot->WriteTObject(temp[ipu+1]);
            
            fitTemp.emplace_back(new TF1(fit(temp[ipu+1], fSeeds[i])));
            if( fDoFit ) fitTemp[ipu+1]->Draw("apsame");
            fTurnonsRoot->WriteTObject(fitTemp[ipu+1]);

            std::stringstream entryName;
            if( ipu < this->GetPuType().size()-1 ) entryName << this->GetPuBins()[ipu] << " #leq PU < " << this->GetPuBins()[ipu+1];
            else entryName << this->GetPuBins()[ipu] << " #leq PU";
            puLeg->AddEntry(temp[ipu+1],entryName.str().c_str());
            entryName.str("");
        }
        puLeg->Draw();
        DrawCmsStampTurnon();
        TLatex * latex = new TLatex();
        latex->SetNDC();
        latex->SetTextFont(42);
        latex->DrawLatex(0.65,0.41,this->GetAddMark().c_str());

        std::string puOutName = Form("%s/effs_%s_puBins_seed%i.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str(),(int)fSeeds[i]);
        puCan->SaveAs(puOutName.c_str());
    }
    nomCan->cd();
    nomLeg->Draw();
    DrawCmsStampTurnon();

    TLatex * nomlatex = new TLatex();
    nomlatex->SetNDC();
    nomlatex->SetTextFont(42);
    nomlatex->SetTextAlign(31);
    //nomlatex->DrawLatex(0.8,0.15+0.2*(2+fSeeds.size())/5.0+0.02,"<PU>=14");

    std::string nomOutName = Form("%s/effs_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    nomCan->SaveAs(nomOutName.c_str());
}

void TL1Turnon::DrawCmsStampTurnon()
{
    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    double min = fXBins.front();
    double max = fXBins.back();
    TLine * line(new TLine(min,1.,max,1.));
    line->SetLineStyle(7);
    line->DrawClone();
    if( this->GetSampleName() == "Data" )
    {
        latex->DrawLatex(0.15,0.92,"#bf{CMS} #it{Preliminary} 2016 Data");
        latex->SetTextAlign(31);
        std::string runNo = "run " + this->GetRun() + ", ";
        //latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),this->GetTriggerTitle().c_str()));
        latex->DrawLatex(0.92, 0.92, Form("%s (13 TeV)",this->GetRun().c_str()));
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
    //latex->DrawLatex(0.18,0.92,this->GetAddMark().c_str());
}

TF1 TL1Turnon::fit(TGraphAsymmErrors * eff, int p50)
{
    std::string func = Form("[0]*0.5*(1+TMath::Erf((x-[1])/TMath::Sqrt([2])))");
    TF1 fitFcn(Form("fit_%s",eff->GetName()),func.c_str(),fXBins.front(),fXBins.back());
    if( fDoFit )
    {
        fitFcn.SetParameters( 1.0000,(double)p50,150.0);
        eff->Fit(fitFcn.GetName(),"E0"); 

        for(int i=0; i<10; ++i)
            eff->Fit(fitFcn.GetName(),"E0M");

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

void TL1Turnon::SetColor(TH1F * hist, float fraction, int index)
{
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * (1.0-2.0*modifier) + modifier) * gStyle->GetNumberOfColors();
        colour = gStyle->GetColorPalette(colorIndex);
    }
    hist->SetLineColor(colour);
    hist->SetMarkerColor(colour);
}

#endif
