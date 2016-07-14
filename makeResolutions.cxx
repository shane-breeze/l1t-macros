#include <string>
#include <vector>

#include "Plotting/tdrstyle.C"
#include "Event/TL1EventClass.h"
#include "Utilities/TL1Progress.C"
#include "Utilities/TL1DateTime.C"
#include "Plotting/TL1Resolution.h"

std::vector<double> bins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void makeResolutions()
{
    TStyle * myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle);

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";

    std::string run = "2016B_v1";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";
    std::vector<std::string> puType = {"0PU12","13PU19","20PU"};
    std::vector<int> puBins = {0,13,20,999};

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160602_r273450_SingleMu_l1t-int-v53p1";
    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160607_combinedRuns_SingleMu";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160704_SingleMu2016Bv1_l1t-int-v67p0";
    TL1EventClass * event(new TL1EventClass(inDir));

    std::vector<TL1Resolution*> resolution;
    std::string outDir = outDirBase+"/"+TL1DateTime::GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/Resolutions/";

    // caloMetBE vs l1EmuMetBE
    resolution.emplace_back(new TL1Resolution());
    resolution[0]->SetBins(bins());
    resolution[0]->SetX("caloMetBE","Offline E_{T}^{miss} BE (GeV)");
    resolution[0]->SetY("l1EmuMetBE","L1 E_{T}^{miss} BE (GeV)");
    resolution[0]->SetOutName(triggerName+"_caloMetBE_over_l1EmuMetBE");
    resolution[0]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetHF vs l1EmuMetBE
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetBins(bins());
    resolution[1]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    resolution[1]->SetY("l1EmuMetBE","L1 E_{T}^{miss} BE (GeV)");
    resolution[1]->SetOutName(triggerName+"_caloMetHF_over_l1EmuMetBE");
    resolution[1]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetHF vs l1EmuMetHF
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetBins(bins());
    resolution[2]->SetX("caloMetHF","Offline E_{T}^{miss} HF (GeV)");
    resolution[2]->SetY("l1EmuMetHF","L1 E_{T}^{miss} HF (GeV)");
    resolution[2]->SetOutName(triggerName+"_caloMetHF_over_l1EmuMetHF");
    resolution[2]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetPhiBE vs l1EmuMetPhiBE
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetBins(bins());
    resolution[3]->SetX("caloMetPhiBE","Offline E_{T}^{miss} Phi BE");
    resolution[3]->SetY("l1EmuMetPhiBE","L1 E_{T}^{miss} Phi BE");
    resolution[3]->SetOutName(triggerName+"_caloMetPhiBE_over_l1EmuMetPhiBE");
    resolution[3]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetPhiHF vs l1EmuMetPhiBE
    resolution.emplace_back(new TL1Resolution());
    resolution[4]->SetBins(bins());
    resolution[4]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    resolution[4]->SetY("l1EmuMetPhiBE","L1 E_{T}^{miss} Phi BE");
    resolution[4]->SetOutName(triggerName+"_caloMetPhiHF_over_l1EmuMetPhiBE");
    resolution[4]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    // caloMetPhiHF vs l1EmuMetPhiHF
    resolution.emplace_back(new TL1Resolution());
    resolution[5]->SetBins(bins());
    resolution[5]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi HF");
    resolution[5]->SetY("l1EmuMetPhiHF","L1 E_{T}^{miss} Phi HF");
    resolution[5]->SetOutName(triggerName+"_caloMetPhiHF_over_l1EmuMetPhiHF");
    resolution[5]->SetAddMark("Offline E_{T}^{miss} > 40 GeV");

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
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

        if( !event->fMuonFilterPassFlag ) continue;

        // MET
        double l1EmuMetBE = event->fL1EmuMet;
        double l1EmuMetHF = event->fL1EmuMetHF;
        double recoMetBE = sums->caloMetBE;
        double recoMetHF = sums->caloMet;

        double l1EmuMetPhiBE = event->fL1EmuMetPhi;
        double l1EmuMetPhiHF = event->fL1EmuMetPhiHF;
        double recoMetPhiBE = sums->caloMetPhiBE;
        double recoMetPhiHF = sums->caloMetPhi;
        
        if( event->fMetFilterPassFlag )
        {
            if( recoMetBE > 40.0 && l1EmuMetBE > 0.0 )
            {
                resolution[0]->Fill(recoMetBE, l1EmuMetBE, pu);
                resolution[3]->Fill(FoldPhi(recoMetPhiBE), FoldPhi(l1EmuMetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1EmuMetBE > 0.0 )
            {
                resolution[1]->Fill(recoMetHF, l1EmuMetBE, pu);
                resolution[4]->Fill(FoldPhi(recoMetPhiHF), FoldPhi(l1EmuMetPhiBE), pu);
            }
            if( recoMetHF > 40.0 && l1EmuMetHF > 0.0 )
            {
                resolution[2]->Fill(recoMetHF, l1EmuMetHF, pu);
                resolution[5]->Fill(recoMetPhiHF, l1EmuMetPhiHF, pu);
            }
        }
    }

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
        (*it)->DrawPlots();
        
}

std::vector<double> bins()
{
    std::vector<double> temp;
    for(double binLowerEdge=-1.0; binLowerEdge<=1.5; binLowerEdge+= 0.05) temp.push_back(binLowerEdge);
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
    return TMath::Min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
}
