#include <string>
#include <vector>
#include <algorithm>

#include "Core/TL1EventClass.h"
#include "TL1XvsY.h"

vector<double> bins(double max);
vector<double> phiBins();
double foldPhi(double phi);
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);

void testTL1XvsY()
{
    std::shared_ptr<TStyle> myStyle(new TStyle(TDRStyle()));
    SetMyStyle(57, 0.14, myStyle.get());

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string run = "273301";
    bool doFit = true;

    std::shared_ptr<TFile> rootFile(new TFile(Form("%s_%s_r%s.root",sample.c_str(),triggerName.c_str(),run.c_str()), "UPDATE"));

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1XvsY>> xvsy;

    // Jet Et
    xvsy.emplace_back(new TL1XvsY());
    xvsy[0]->SetSample(sample,"");
    xvsy[0]->SetTrigger(triggerName,triggerTitle);
    xvsy[0]->SetRun(run);
    xvsy[0]->SetXBins(bins(200.0));
    xvsy[0]->SetX("jetEt","Reco Jet E_{T} (GeV)");
    xvsy[0]->SetYBins(bins(200.0));
    xvsy[0]->SetY("l1JetEt","L1 Jet E_{T} (GeV)");
    xvsy[0]->SetOutName(triggerName+"_jetEt_vs_l1JetEt");

    // Jet phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[0]->SetSample(sample,"");
    xvsy[0]->SetTrigger(triggerName,triggerTitle);
    xvsy[0]->SetRun(run);
    xvsy[0]->SetXBins(phiBins());
    xvsy[0]->SetX("jetPhi","Reco Jet Phi");
    xvsy[0]->SetYBins(phiBins());
    xvsy[0]->SetY("l1JetPhi","L1 Jet Phi");
    xvsy[0]->SetOutName(triggerName+"_jetPhi_vs_l1JetPhi");

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->InitPlots();

    while( event->Next() )
    {
        event->GetL1Variables();
         
    }

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
        (*it)->DrawPlots();

    rootFile->Close();
}

vector<double> bins(double max)
{
    vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=max; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> phiBins()
{
    vector<double> temp;
    for(double binLowerEdge=0.0; binLowerEdge<=TMath::Pi(); binLowerEdge+= (TMath::Pi())/36.) temp.push_back(binLowerEdge);
    return temp;
}

double foldPhi(double phi)
{
    return min( (float)abs(phi), (float)abs(2*TMath::Pi()-phi) );
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
