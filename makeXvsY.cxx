#include <string>
#include <vector>
#include <algorithm>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1XvsY.h"

std::vector<double> bins(double max, double width, double min);
std::vector<double> phiBins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void makeXvsY()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle);

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";

    std::string run = "Run2016B";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0";
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/xy/";
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1XvsY*> xvsy;

    // caloMetBE vs l1EmuMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[0]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetX("caloMetBE","Offline E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetY("l1EmuMetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1EmuMetBE");

    // caloMetHF vs l1EmuMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[1]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetY("l1EmuMetBE","L1 E_{T}^{miss} BE (GeV)");
    xvsy[1]->SetOutName(triggerName+"_caloMetHF_vs_l1EmuMetBE");

    // caloMetHF vs l1EmuMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[2]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    xvsy[2]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[2]->SetY("l1EmuMetHF","L1 E_{T}^{miss} HF (GeV)");
    xvsy[2]->SetOutName(triggerName+"_caloMetHF_vs_l1EmuMetHF");

    // caloMetBE Phi vs l1EmuMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(phiBins());
    xvsy[3]->SetX("caloMetPhiBE","Offline E_{T}^{miss} Phi BE");
    xvsy[3]->SetYBins(phiBins());
    xvsy[3]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    xvsy[3]->SetOutName(triggerName+"_caloMetPhiBE_vs_l1MetPhiBE");

    // caloMetHF Phi vs l1EmuMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1MetPhiBE","L1 E_{T}^{miss} Phi BE");
    xvsy[4]->SetOutName(triggerName+"_caloMetPhiHF_vs_l1MetPhiBE");

    // caloMetHF Phi vs l1EmuMetHF Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1MetPhiHF","L1 E_{T}^{miss} Phi HF");
    xvsy[5]->SetOutName(triggerName+"_caloMetPhiHF_vs_l1MetPhiHF");

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

        double l1EmuMetBE = event->fL1EmuMet;
        double l1EmuMetHF = event->fL1EmuMetHF;
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double l1EmuMetPhiBE = event->fL1EmuMetPhi;
        double l1EmuMetPhiHF = event->fL1EmuMetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;

        if( !event->fMuonFilterPassFlag ) continue;
        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            xvsy[0]->Fill(recoMetBE, l1EmuMetBE, pu);
            xvsy[1]->Fill(recoMetHF, l1EmuMetBE, pu);
            xvsy[2]->Fill(recoMetHF, l1EmuMetHF, pu);

            xvsy[3]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1EmuMetPhiBE), pu);
            xvsy[4]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1EmuMetPhiBE), pu);
            xvsy[5]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1EmuMetPhiHF), pu);
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
