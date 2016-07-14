#include <string>
#include <vector>
#include <algorithm>

#include "Core/TL1EventClass.h"
#include "Core/TL1Progress.C"
#include "TL1XvsY.h"

std::vector<double> bins(double max, double width, double min);
std::vector<double> phiBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void testTL1XvsY()
{
    std::shared_ptr<TStyle> myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle.get());

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";

    std::string run = "2016B_v1";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    //std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1XvsY>> xvsy;

    xvsy.emplace_back(new TL1XvsY());
    std::string outDir = outDirBase+"/"+xvsy.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/xy/";

    // l1HwMetBE vs l1ReMetBE
    xvsy[0]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetX("l1HwMetBE","L1 HW E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetY("l1ReMetBE","L1 Re E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetOutName(triggerName+"_l1HwMetBE_vs_l1ReMetBE");
    xvsy[0]->SetAddMark("no HF");

    // l1HwMetBE vs l1EmMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetX("l1HwMetBE","L1 HW E_{T}^{miss} BE (GeV)");
    xvsy[1]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetY("l1EmMetBE","L1 EM E_{T}^{miss} BE (GeV)");
    xvsy[1]->SetOutName(triggerName+"_l1HwMetBE_vs_l1EmMetBE");
    xvsy[1]->SetAddMark("no HF");
    
    // l1ReMetBE vs l1EmMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[2]->SetX("l1ReMetBE","L1 Re E_{T}^{miss} BE (GeV)");
    xvsy[2]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[2]->SetY("l1EmMetBE","L1 EM E_{T}^{miss} BE (GeV)");
    xvsy[2]->SetOutName(triggerName+"_l1ReMetBE_vs_l1EmMetBE");
    xvsy[2]->SetAddMark("no HF");
    
    // l1ReMetHF vs l1EmMetHF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[3]->SetX("l1EmMetHF","L1 Re E_{T}^{miss} HF (GeV)");
    xvsy[3]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[3]->SetY("l1EmMetHF","L1 Em E_{T}^{miss} HF (GeV)");
    xvsy[3]->SetOutName(triggerName+"_l1ReMetHF_vs_l1EmMetHF");
    xvsy[3]->SetAddMark("HF");

    // l1EmMetBE vs caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[4]->SetX("l1EmMetBE","L1 EM E_{T}^{miss} BE (GeV)");
    xvsy[4]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[4]->SetY("caloMetBE","Offline E_{T}^{miss} BE (GeV)");
    xvsy[4]->SetOutName(triggerName+"_l1EmMetBE_vs_caloMetBE");
    xvsy[4]->SetAddMark("no HF");

    // l1EmMetBE vs caloMetHF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[5]->SetX("l1EmMetBE","L1 EM E_{T}^{miss} BE (GeV)");
    xvsy[5]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[5]->SetY("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[5]->SetOutName(triggerName+"_l1EmMetBE_vs_caloMetHF");
   
    // l1EmMetHF vs caloMetHF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[6]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[6]->SetX("l1EmMetHF","L1 EM E_{T}^{miss} HF (GeV)");
    xvsy[6]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[6]->SetY("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[6]->SetOutName(triggerName+"_l1EmMetHF_vs_caloMetHF");
    xvsy[6]->SetAddMark("HF");

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
    {
        (*it)->SetSample(sample,"");
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(run);
        (*it)->SetOutDir(outDir);
        (*it)->SetPuType(puType);
        (*it)->SetPuBins(puBins);
        (*it)->InitPlots();
    }

    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        int pu = event->GetPEvent()->fVertex->nVtx;
        auto sums = event->GetPEvent()->fSums;

        //----- MET -----//
        if( !event->fMuonFilterPassFlag ) continue;
        if( event->fMetFilterPassFlag )
        {
            double recoMetBE = sums->caloMetBE;
            double recoMetHF = sums->caloMet;

            double l1HwMetBE = event->fL1Met;
            //double l1HwMetHF = event->fL1MetHF;
            double l1ReMetBE = event->fRecalcL1Met;
            double l1ReMetHF = event->fRecalcL1MetHF;
            double l1EmMetBE = event->fL1EmuMet;
            double l1EmMetHF = event->fL1EmuMetHF;

            if( l1EmMetBE > 0.0 && recoMetBE > 0.0 )
                xvsy[4]->Fill(l1EmMetBE, recoMetBE, pu);
            if( l1EmMetHF > 0.0 && recoMetBE > 0.0 )
                xvsy[5]->Fill(l1EmMetBE, recoMetHF, pu);
            if( l1EmMetHF > 0.0 && recoMetHF > 0.0 )
                xvsy[6]->Fill(l1EmMetHF, recoMetHF, pu);

            if( l1ReMetBE > 0.0 )
                xvsy[0]->Fill(l1HwMetBE, l1ReMetBE, pu);
            xvsy[1]->Fill(l1HwMetBE, l1EmMetBE, pu);
            if( l1ReMetBE > 0.0 )
                xvsy[2]->Fill(l1ReMetBE, l1EmMetBE, pu);
            if( l1ReMetHF > 0.0 )
                xvsy[3]->Fill(l1ReMetHF, l1EmMetHF, pu);
        }
    }

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->DrawPlots();
}

std::vector<double> bins(double max, double width, double min)
{
    std::vector<double> temp;
    for(double binLowerEdge=min; binLowerEdge<=max; binLowerEdge+= width) temp.push_back(binLowerEdge);
    return temp;
}

std::vector<double> phiBins()
{
    std::vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=TMath::Pi(); binLowerEdge+= (TMath::Pi())/36.) temp.push_back(binLowerEdge);
    return temp;
}

void SetMyStyle(int palette, double rmarg, TStyle * myStyle)
{
    myStyle->SetCanvasDefW(800);
    myStyle->SetCanvasDefH(600);
    myStyle->SetNumberContours(255);
    myStyle->SetPalette(palette);
    myStyle->SetPadRightMargin(rmarg);
    myStyle->cd();
}

double FoldPhi(double phi)
{
    return TMath::Min( (float)TMath::Abs(phi), (float)TMath::Abs(2*TMath::Pi()-phi) );
}
