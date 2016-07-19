#ifndef TL1PUWEIGHTS_H
#define TL1PUWEIGHTS_H

#include <string>
#include <stdlib.h>
#include <vector>

#include <TH1F.h>
#include <TFile.h>

class TL1PUWeights
{
    public:
        ~TL1PUWeights();

        void InitPlots();
        void FillData(const int & pu);
        void FillMC(const int & pu);
        void DrawPlots();
        void DrawCmsStamp();

        void SetBins(const std::vector<double> & bins);
        void SetData(const std::string & sampleName, const std::string & sampleTitle,
                const std::string & triggerName, const std::string & triggerTitle,
                const std::string & run);
        void SetMC(const std::string & mcName, const std::string & mcTitle);
        void SetOutDir(const std::string & outDir);

    private:
        TH1F * fPUData, * fPUMC;
        TFile * fRootFile;

        std::vector<double> fBins;
        std::string fSampleName, fSampleTitle, fTriggerName, fTriggerTitle, fRun;
        std::string fMCName, fMCTitle;
        std::string fOutDir;

};

TL1PUWeights::~TL1PUWeights()
{
    fRootFile->Close();
}

void TL1PUWeights::InitPlots()
{
    fRootFile = new TFile(Form("%s/pu_mcReweightedToData.root",fOutDir.c_str()),"RECREATE");
    
    fPUData = new TH1F("puData","", fBins.size()-1,&(fBins)[0]);
    fPUData->SetDirectory(0);
    fPUData->GetXaxis()->SetTitle("PU");
    fPUData->GetYaxis()->SetTitle("a.u.");

    fPUMC = new TH1F("puMC","", fBins.size()-1,&(fBins)[0]);
    fPUMC->SetDirectory(0);
    fPUMC->GetXaxis()->SetTitle("PU");
    fPUMC->GetYaxis()->SetTitle("a.u.");
}

void TL1PUWeights::FillData(const int & pu)
{
    fPUData->Fill(pu);
}

void TL1PUWeights::FillMC(const int & pu)
{
    fPUMC->Fill(pu); 
}

void TL1PUWeights::DrawPlots()
{
    // Write to root file
    fRootFile->WriteTObject(fPUData);
    fRootFile->WriteTObject(fPUMC);

    fPUData->Scale(1./fPUData->Integral());
    fPUMC->Scale(1./fPUMC->Integral());

    TH1F * ratio = (TH1F*)fPUData->Clone("puRatio");
    ratio->SetDirectory(0);
    ratio->Divide(fPUMC);
    fRootFile->WriteTObject(ratio);

    TH1F * mcReweighted = (TH1F*)fPUMC->Clone("mcRewighted");
    mcReweighted->SetDirectory(0);
    mcReweighted->Sumw2();
    for(int bin=0; bin<=mcReweighted->GetNbinsX()+1; ++bin)
    {
        double oldContent(mcReweighted->GetBinContent(bin));
        double oldError(mcReweighted->GetBinError(bin));
        double scale(ratio->GetBinContent(bin));
        mcReweighted->SetBinContent(bin,oldContent*scale);
        mcReweighted->SetBinError(bin,oldError*scale);
    }

    TCanvas * can(new TCanvas("c1","c1"));
    TLegend * leg(new TLegend(0.58,0.7,0.88,0.85));

    double max(fPUMC->GetMaximum());
    double max2(fPUData->GetMaximum());
    double max3(mcReweighted->GetMaximum());
    if( max < max2 ) max = max2;
    if( max < max3 ) max = max3;
    fPUMC->SetMaximum(max);
    fPUData->SetMaximum(max);
    mcReweighted->SetMaximum(max);

    fPUMC->SetLineColor(kBlue-7);
    fPUMC->DrawCopy("hist");
    leg->AddEntry(fPUMC,"MC");

    mcReweighted->SetLineColor(kRed-7);
    mcReweighted->DrawCopy("histsame");
    leg->AddEntry(mcReweighted,"MC Reweighted");

    fPUData->DrawCopy("psame");
    leg->AddEntry(fPUData,"Data");

    leg->Draw();
    DrawCmsStamp();

    std::string outName = Form("%s/pu_mcReweightedToData.pdf",fOutDir.c_str());
    can->SaveAs(outName.c_str());
}

void TL1PUWeights::DrawCmsStamp()
{
    TLatex * latex(new TLatex());
    latex->SetNDC();
    latex->SetTextFont(42);
    latex->DrawLatex(0.15,0.92,"#bf{CMS} #it{Preliminary}");
    latex->SetTextAlign(31);
    latex->DrawLatex(0.92,0.92,"(13 TeV)");
}

void TL1PUWeights::SetBins(const std::vector<double> & bins)
{
    fBins = bins;
}

void TL1PUWeights::SetData(
        const std::string & sampleName, const std::string & sampleTitle,
        const std::string & triggerName, const std::string & triggerTitle,
        const std::string & run
        )
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
    fRun = run;
}

void TL1PUWeights::SetMC(const std::string & mcName, const std::string & mcTitle)
{
    fMCName = mcName;
    fMCTitle = mcTitle;
}

void TL1PUWeights::SetOutDir(const std::string & outDir)
{
    std::system(Form("mkdir -p %s",outDir.c_str()));
    fOutDir = outDir;
}

#endif
