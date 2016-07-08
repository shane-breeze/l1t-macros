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

#include "Core/TL1Plots.h"

class TL1Resolution : public TL1Plots
{
    public:
        ~TL1Resolution();

        virtual void InitPlots();
        virtual void Fill(const double & xVal, const double & yVal, const int & pu);
        virtual void DrawPlots();

        void RelFill(const double & xVal, const double & yVal, const int & pu, const std::vector<double> & relVals);
        void DrawRelPlots();
        TH1F GetRelHist(const int & i, const int & j);

        void SetBins(const std::vector<double> & bins);
        void SetX(const std::string & xName, const std::string & xTitle);
        void SetY(const std::string & yName, const std::string & yTitle);
        void SetColor(TH1F * plot, float fraction, int index);
        void DrawCmsStamp(std::string stampPos="Left");

        void AddRelBins(const std::vector<double> & bins);
        void AddRelTitle(const std::string & name, const std::string & title);

    private:
        std::vector<TH1F*> fPlot;
        TFile * fRootFile;

        std::string fXName, fXTitle;
        std::string fYName, fYTitle;
        std::vector<double> fBins;

        std::vector<std::vector<TH2F*>> fRelPlot;
        std::vector<std::vector<double>> fRelBins;
        std::vector<std::string> fRelTitles, fRelNames;

};

TL1Resolution::~TL1Resolution()
{
    fRootFile->Close();
}

void TL1Resolution::InitPlots()
{
    fRootFile = new TFile(Form("%s/res_%s.root",this->GetOutDir().c_str(),this->GetOutName().c_str()),"RECREATE");

    fPlot.emplace_back(new TH1F(Form("res_%s_over_%s",fXName.c_str(),fYName.c_str()),"", fBins.size()-1,&(fBins)[0]));
    fPlot.back()->SetDirectory(0);
    fPlot.back()->GetXaxis()->SetTitle(Form("(%s - %s)/%s",fYTitle.c_str(),fXTitle.c_str(),fXTitle.c_str()));
    fPlot.back()->GetYaxis()->SetTitle("a.u.");
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        fPlot.emplace_back(new TH1F(Form("res_%s_over_%s_%s",fXName.c_str(),fYName.c_str(),this->GetPuType()[i].c_str()),"", fBins.size()-1,&(fBins)[0]));
        fPlot.back()->SetDirectory(0);
        fPlot.back()->GetXaxis()->SetTitle(Form("(%s - %s)/%s",fYTitle.c_str(),fXTitle.c_str(),fXTitle.c_str()));
        fPlot.back()->GetYaxis()->SetTitle("a.u.");
    }

    for(int i=0; i<fRelTitles.size(); ++i)
    {
        std::vector<TH2F*> temp;
        temp.emplace_back(new TH2F(Form("relRes_%s_over_%s_vs_%s",fXName.c_str(),fYName.c_str(),fRelTitles[i].c_str()),"", fBins.size()-1,&(fBins)[0], fRelBins[0].size()-1,&(fRelBins[0])[0]));
        temp.back()->SetDirectory(0);
        temp.back()->GetXaxis()->SetTitle(fRelTitles[i].c_str());
        temp.back()->GetYaxis()->SetTitle(Form("%s / %s",fYTitle.c_str(),fXTitle.c_str()));

        for(int j=0; j<this->GetPuType().size(); ++j)
        {
            temp.emplace_back(new TH2F(Form("relRes_%s_over_%s_vs_%s_%s",fXName.c_str(),fYName.c_str(),fRelTitles[i].c_str(),this->GetPuType()[j].c_str()),"", fBins.size()-1,&(fBins)[0], fRelBins[i].size()-1,&(fRelBins[i])[0]));
            temp.back()->SetDirectory(0);
            temp.back()->GetXaxis()->SetTitle(fRelTitles[i].c_str());
            temp.back()->GetYaxis()->SetTitle(Form("%s / %s",fYTitle.c_str(),fXTitle.c_str()));
        }
        fRelPlot.push_back(temp);
    }

}

void TL1Resolution::Fill(const double & xVal, const double & yVal, const int & pu)
{
    double div = 0.0;
    if( xVal != 0.0 ) div = (yVal-xVal)/xVal;
    fPlot[0]->Fill(div);
    for(int i=0; i<this->GetPuType().size(); ++i)
    {
        if( pu >= this->GetPuBins()[i] && pu < this->GetPuBins()[i+1] )
            fPlot[i+1]->Fill(div);
    }
}

void TL1Resolution::RelFill(const double & xVal, const double & yVal, const int & pu, const std::vector<double> & relVals)
{
    return;
    double div = 0.0;
    if( xVal != 0.0 ) div = yVal/xVal;
    if( relVals.size() != fRelTitles.size() )
        std::cerr << "ERROR: Size of relVals is not equal to the size of fRelTitles" << std::endl;

    for(int i=0; i<fRelTitles.size(); ++i)
    {
        fRelPlot[i][0]->Fill(relVals[i],div);
        for(int j=0; j<this->GetPuType().size(); ++j)
        {
            if( pu >= this->GetPuBins()[j] && pu < this->GetPuBins()[j+1] )
                fRelPlot[i][j+1]->Fill(relVals[i],div);
        }
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
        this->SetColor(fPlot[i+1], (double)(this->GetPuType().size()-i-1)/(double)(this->GetPuType().size()-2),i+1);
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

//    DrawRelPlots();
}

void TL1Resolution::DrawRelPlots()
{
    for(int i=0; i<fRelTitles.size(); ++i)
    {
        TCanvas * can = new TCanvas(Form("relResC3_%i",i),"relResC3");

        TH1F * relHist0 = new TH1F(GetRelHist(i,0));
        relHist0->GetXaxis()->SetTitle(fRelTitles[i].c_str());
        relHist0->GetYaxis()->SetTitle(Form("%s resolution",fYTitle.c_str()));
        relHist0->SetLineColor(kBlue-4);
        relHist0->SetMarkerColor(kBlue-4);

        for(int bin=1; bin<=relHist0->GetNbinsX(); ++bin)
        {
            double binWidth = relHist0->GetBinWidth(bin);
            double binCenter = relHist0->GetBinCenter(bin);
            double binContent = relHist0->GetBinContent(bin);
            TLine * line2 = new TLine();
            line2->SetLineColor(relHist0->GetLineColor());
            line2->DrawLine(binCenter-0.5*binWidth,binContent,binCenter+0.5*binWidth,binContent);
        }

        relHist0->Draw("pe");
        fRootFile->WriteTObject(relHist0);
        DrawCmsStamp("Right");

        std::string outName = Form("%s/relRes_%s_vs_%s.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str(),fRelNames[i].c_str());
        can->SaveAs(outName.c_str());

        TCanvas * can2(new TCanvas(Form("relResC4_%i",i),"relResC4"));
        TLegend * leg(new TLegend(0.65,0.6,0.9,0.5+0.08*this->GetPuType().size(),this->GetAddMark().c_str()));
        THStack * hs(new THStack(Form("stack_%s",relHist0->GetName()),"hs"));
        hs->GetXaxis()->SetTitle(fRelTitles[i].c_str());
        hs->GetYaxis()->SetTitle(Form("%s resolution",fYTitle.c_str()));
        for(int j=0; j<this->GetPuType().size(); ++j)
        {
            TH1F * relHist = new TH1F(GetRelHist(i,j+1));
            relHist->SetMaximum(1.2*relHist->GetMaximum());
            relHist->GetXaxis()->SetTitle(fRelTitles[i].c_str());
            relHist->GetYaxis()->SetTitle(Form("%s resolution",fYTitle.c_str()));
            this->SetColor(relHist, (double)(this->GetPuType().size()-j-1)/(double)(this->GetPuType().size()-2),j+1);
            hs->Add(relHist);

            //if( j==0 ) relHist->Draw("pe1");
            //else relHist->Draw("pe1same");

            //for(int bin=1; bin<=relHist->GetNbinsX(); ++bin)
            //{
            //    double binWidth = relHist->GetBinWidth(bin);
            //    double binCenter = relHist->GetBinCenter(bin);
            //    double binContent = relHist->GetBinContent(bin);
            //    TLine * line2 = new TLine();
            //    line2->SetLineColor(relHist->GetLineColor());
            //    line2->DrawLine(binCenter-0.5*binWidth,binContent,binCenter+0.5*binWidth,binContent);
            //}

            fRootFile->WriteTObject(relHist);

            std::stringstream entryName;
            if( j<this->GetPuType().size()-1 ) entryName << this->GetPuBins()[j] << " #leq PU < " << this->GetPuBins()[j+1];
            else entryName << this->GetPuBins()[j] << " #leq PU";
            leg->AddEntry(relHist,entryName.str().c_str());
            entryName.str("");
        }
        hs->Draw("penostack");
        //TIter next(hs->GetHists());
        //while( TH1F * hist = (TH1F*)next() )
        //{
        //    for(int bin=1; bin<=hist->GetNbinsX(); ++bin)
        //    {
        //        double binWidth = hist->GetBinWidth(bin);
        //        double binCenter = hist->GetBinCenter(bin);
        //        double binContent = hist->GetBinContent(bin);
        //        TLine * line2 = new TLine();
        //        line2->SetLineColor(hist->GetLineColor());
        //        line2->DrawLine(binCenter-0.5*binWidth,binContent,binCenter+0.5*binWidth,binContent);
        //    }
        //}

        DrawCmsStamp("Right");
        leg->Draw();
        
        outName = Form("%s/relRes_%s_vs_%s_puBins.pdf",this->GetOutDir().c_str(),this->GetOutName().c_str(),fRelNames[i].c_str());
        can2->SaveAs(outName.c_str());
    }
}

TH1F TL1Resolution::GetRelHist(const int & i, const int & j)
{
    TH1F relHist(Form("relHist_%s",fRelPlot[i][j]->GetName()),"", fRelBins[i].size()-1,&(fRelBins[i])[0]);
    TH1F hMean(Form("relHistMean_%s",fRelPlot[i][j]->GetName()),"", fRelBins[i].size()-1,&(fRelBins[i])[0]);
    TH1F hRms(Form("relHistRms_%s",fRelPlot[i][j]->GetName()),"", fRelBins[i].size()-1,&(fRelBins[i])[0]);
    for(int k=1; k<=fRelPlot[i][j]->GetNbinsX(); ++k)
    {
        double mean = TMath::Abs(fRelPlot[i][j]->ProjectionY("_py",k,k)->GetMean());
        double meanErr = fRelPlot[i][j]->ProjectionY("_py",k,k)->GetMeanError();
        hMean.SetBinContent(k,mean);
        hMean.SetBinError(k,meanErr);

        double rms = fRelPlot[i][j]->ProjectionY("_py",k,k)->GetRMS();
        double rmsErr = fRelPlot[i][j]->ProjectionY("_py",k,k)->GetRMSError();
        hRms.SetBinContent(k,rms);
        hRms.SetBinError(k,rmsErr);
    }
    relHist.Divide(&hRms,&hMean);
    return relHist;
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

void TL1Resolution::SetColor(TH1F * plot, float fraction, int index)
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

void TL1Resolution::AddRelBins(const std::vector<double> & bins)
{
    fRelBins.push_back(bins);
}

void TL1Resolution::AddRelTitle(const std::string & name, const std::string & title)
{
    fRelNames.push_back(name);
    fRelTitles.push_back(title);
}

#endif
