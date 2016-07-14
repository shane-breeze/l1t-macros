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

    // caloMetBE
    xvsy[0]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetX("caloMetBE","Offline E_{T}^{miss} (GeV)");
    xvsy[0]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetY("l1Met","L1 E_{T}^{miss} (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1Met");
    xvsy[0]->SetAddMark("no HF");

    // caloMetHF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetX("caloMetHF","Offline E_{T}^{miss} (GeV)");
    xvsy[1]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetY("l1MetHF","L1 E_{T}^{miss} (GeV)");
    xvsy[1]->SetOutName(triggerName+"_caloMetHF_vs_l1MetHF");
    xvsy[1]->SetAddMark("HF");


    // caloMetPhiBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(phiBins());
    xvsy[2]->SetX("caloMetPhiBE","Offline E_{T}^{miss} Phi");
    xvsy[2]->SetYBins(phiBins());
    xvsy[2]->SetY("l1MetPhi","L1 E_{T}^{miss} Phi");
    xvsy[2]->SetOutName(triggerName+"_caloMetPhiBE_vs_l1MetPhi");
    xvsy[2]->SetAddMark("no HF");

    // caloMetPhiHF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(phiBins());
    xvsy[3]->SetX("caloMetPhiHF","Offline E_{T}^{miss} Phi");
    xvsy[3]->SetYBins(phiBins());
    xvsy[3]->SetY("l1MetPhiHF","L1 E_{T}^{miss} Phi");
    xvsy[3]->SetOutName(triggerName+"_caloMetPhiHF_vs_l1MetPhiHF");
    xvsy[3]->SetAddMark("HF");

    // htt - no HF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[4]->SetX("recoHtt","Offline Total H_{T} (GeV)");
    xvsy[4]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[4]->SetY("l1Htt","L1 Total H_{T} (GeV)");
    xvsy[4]->SetOutName(triggerName+"_htt_vs_l1Htt");
    xvsy[4]->SetAddMark("no HF");

    // htt - with HF
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[5]->SetX("recoHttHF","Offline Total H_{T} (GeV)");
    xvsy[5]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[5]->SetY("l1HttHF","L1 Total H_{T} (GeV)");
    xvsy[5]->SetOutName(triggerName+"_httHF_vs_l1HttHF");
    xvsy[5]->SetAddMark("HF");


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

        //----- HTT -----//
        double recoHtt = sums->Ht;
        double l1Htt = event->fL1Htt;
        if( recoHtt > 0.0 && l1Htt > 0.0 ) xvsy[4]->Fill(recoHtt, l1Htt, pu);

        double recoHttHF = sums->Ht;
        double l1HttHF = event->fL1HttHF;
        if( recoHttHF > 0.0 && l1HttHF > 0.0 ) xvsy[5]->Fill(recoHttHF, l1HttHF, pu);

        //----- MET -----//
        if( !event->fMuonFilterPassFlag ) continue;
        if( event->fMetFilterPassFlag )
        {
            double recoMet = sums->caloMetBE;
            double l1Met = event->fL1Met;
            if( recoMet > 0.0 && l1Met > 0.0 ) xvsy[0]->Fill(recoMet, l1Met, pu);

            double recoMetHF = sums->caloMet;
            double l1MetHF = event->fL1MetHF;
            if( recoMetHF > 0.0 && l1MetHF > 0.0 ) xvsy[1]->Fill(recoMetHF, l1MetHF, pu);

            double recoMetPhi = FoldPhi(sums->caloMetPhiBE);
            double l1MetPhi = FoldPhi(event->fL1MetPhi);
            xvsy[2]->Fill(recoMetPhi, l1MetPhi, pu);

            double recoMetPhiHF = FoldPhi(sums->caloMetPhi);
            double l1MetPhiHF = FoldPhi(event->fL1MetPhiHF);
            xvsy[3]->Fill(recoMetPhiHF, l1MetPhiHF, pu);
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
