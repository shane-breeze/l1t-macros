#ifndef TL1RATEEFFICIENCY_H
#define TL1RATEEFFICIENCY_H

#include <string>
#include <vector>

#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TLine.h>

#include "TL1Plots.h"

class TL1RateEfficiency : public TL1Plots
{
    public:
        ~TL1RateEfficiency();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu=0);
        virtual void DrawPlots();
        TH1F * GetCumulative(TH1F * plot);
        void DrawCmsStamp();

        void SetRatePlot(const std::string & filename, const std::string & plotname);
        void SetXBins(const std::vector<double> & xBins);
        void SetX(const std::string & xName, const std::string & xTitle);

    private:
        std::vector<TH1F*> fAbove, fTotal;
        TH1F * fRates;
        TFile * fRootFile;

        std::vector<double> fXBins;
        std::string fXName, fXTitle;

};

TL1RateEfficiency::~TL1RateEfficiency()
{
    delete fRootFile;
}

void TL1RateEfficiency::InitPlots()
{
    fRootFile = TFile::Open(Form("%s/rateEff_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");

    fAbove.emplace_back(new TH1F(Form("nabove_%s",fXName.c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    fAbove.back()->SetDirectory(0);
    fAbove.back()->Sumw2();
    fAbove.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    fAbove.back()->GetYaxis()->SetTitle("N Above");

    fTotal.emplace_back(new TH1F(Form("ntotal_%s",fXName.c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    fTotal.back()->SetDirectory(0);
    fTotal.back()->Sumw2();
    fTotal.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    fTotal.back()->GetYaxis()->SetTitle("N Total");

    //for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    //{
    //    fAbove.emplace_back(new TH1F(Form("nabove_%s_%s",fXName.c_str(),this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    //    fAbove.back()->SetDirectory(0);
    //    fAbove.back()->Sumw2();
    //    fAbove.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    //    fAbove.back()->GetYaxis()->SetTitle("N Above");

    //    fTotal.emplace_back(new TH1F(Form("ntotal_%s_%s",fXName.c_str(),this->GetPuType()[ipu].c_str()),"", fXBins.size()-1,&(fXBins)[0]));
    //    fTotal.back()->SetDirectory(0);
    //    fTotal.back()->Sumw2();
    //    fTotal.back()->GetXaxis()->SetTitle(fXTitle.c_str());
    //    fTotal.back()->GetYaxis()->SetTitle("N Total");
    //}
}

void TL1RateEfficiency::Fill(const double & xVal, const double & yVal, const int & pu=0)
{
    double weight(this->GetPuWeight(pu));
    fTotal[0]->Fill(xVal, weight);
    if( yVal >= xVal ) fAbove[0]->Fill(xVal, weight);

    //for(int ipu=0; ipu<this->GetPuType().size(); ++ipu)
    //{
    //    fTotal[ipu+1]->Fill(xVal, weight);
    //    if( yVal >= xVal ) fAbove[ipu+1]->Fill(xVal, weight);
    //}
}

void TL1RateEfficiency::DrawPlots()
{
    TH1F * fAboveCumu = GetCumulative(fAbove[0]);
    TH1F * fTotalCumu = GetCumulative(fTotal[0]);

    TGraphAsymmErrors * fEff(new TGraphAsymmErrors(fAboveCumu, fTotalCumu));

    TH1F * fY(new TH1F(Form("y_%f",this->GetRnd()),"", fXBins.size()-1, &(fXBins[0])));
    TH1F * fEYL(new TH1F(Form("eyl_%f",this->GetRnd()),"", fXBins.size()-1, &(fXBins[0])));
    TH1F * fEYH(new TH1F(Form("eyh_%f",this->GetRnd()),"", fXBins.size()-1, &(fXBins[0])));

    double x(0.0);
    for(int bin=0; bin<fEff->GetN(); ++bin)
    {
        x = fEff->GetX()[bin];
        fY->Fill(x, fEff->GetY()[bin]);
        fEYL->Fill(x, fEff->GetErrorYlow(bin));
        fEYH->Fill(x, fEff->GetErrorYhigh(bin));
    }

    vector<double> xvec, yvec, eylvec, eyhvec;
    for(int bin=1; bin<fY->GetNbinsX()+1; ++bin)
    {
        xvec.push_back(fRates->GetBinContent(bin));
        yvec.push_back(fY->GetBinContent(bin));
        eylvec.push_back(fEYL->GetBinContent(bin));
        eyhvec.push_back(fEYH->GetBinContent(bin));
    }
    TGraphAsymmErrors * fRateEff(new TGraphAsymmErrors(xvec.size(), &(xvec[0]), &(yvec[0]), 0, 0, &(eylvec[0]), &(eyhvec[0])));
    fRateEff->SetName(Form("rateEff_%s",this->GetOutName().c_str()));

    fRootFile->WriteTObject(fAbove[0]);
    fRootFile->WriteTObject(fTotal[0]);
    fRootFile->WriteTObject(fAboveCumu);
    fRootFile->WriteTObject(fTotalCumu);
    fRootFile->WriteTObject(fRateEff);

    TCanvas * can(new TCanvas(Form("can_%f",this->GetRnd()),""));    
    can->SetLogx();

    fRateEff->SetMarkerColor(kBlue-7);
    fRateEff->SetLineColor(kBlue-7);
    fRateEff->Draw();

    std::string outName = Form("%s/rateEffs_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str());
    can->SaveAs(outName.c_str());

    delete fY;
    delete fEYL;
    delete fEYH;
    delete can;
}

TH1F * TL1RateEfficiency::GetCumulative(TH1F * plot)
{
    std::string newName = Form("cumulative_%s",plot->GetName());
    TH1F * temp = (TH1F*)plot->Clone(newName.c_str());  
    temp->SetDirectory(0);
    for(int i=0; i<plot->GetNbinsX()+1; ++i)
    {
        double content(0.0), error2(0.0);
        for(int j=i; j<plot->GetNbinsX()+1; ++j)
        {
            content += plot->GetBinContent(j);
            error2 += plot->GetBinError(j)*plot->GetBinError(j);
        }
        temp->SetBinContent(i,content);
        temp->SetBinError(i,TMath::Sqrt(error2));
    }
    return temp;
}

void TL1RateEfficiency::DrawCmsStamp()
{

}

void TL1RateEfficiency::SetRatePlot(const std::string & filename, const std::string & plotname)
{
    TFile * ratefile = TFile::Open(filename.c_str(),"READ");
    fRates = (TH1F*)ratefile->Get(plotname.c_str());
    fRates->SetDirectory(0);
    delete ratefile;
}

void TL1RateEfficiency::SetXBins(const std::vector<double> & xBins)
{
    fXBins = xBins;
}

void TL1RateEfficiency::SetX(const std::string & xName, const std::string & xTitle)
{
    fXName = xName;
    fXTitle = xTitle;
}

#endif
