#include <string>
#include <vector>

#include "Core/tdrstyle.C"
#include "Core/TL1EventClass.h"
#include "Core/TL1Progress.C"
#include "TL1Resolution.h"

std::vector<double> bins();
void SetMyStyle(int palette, double rmarg, TStyle * myStyle);
double FoldPhi(double phi);

void testTL1ResolutionJets()
{
    std::shared_ptr<TStyle> myStyle(new TStyle(TDRStyle()));
    SetMyStyle(55, 0.07, myStyle.get());

    // Basic
    std::string sample = "Data";
    std::string triggerName = "SingleMu";
    std::string triggerTitle = "Single Muon";
    std::string run = "273301";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1Resolution>> resolution;

    // Jet Et - barrel
    resolution.emplace_back(new TL1Resolution());
    std::string outDir = outDirBase+"/"+resolution.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/resJets/";
    resolution[0]->SetBins(bins());
    resolution[0]->SetX("jetEt","Reco Jet E_{T}");
    resolution[0]->SetY("l1JetEt","L1 Jet E_{T})");
    resolution[0]->SetOutName(triggerName+"_jetEt_over_l1JetEt_barrel");
    resolution[0]->SetAddMark("Barrel");

    // Jet Et - end-cap
    resolution.emplace_back(new TL1Resolution());
    resolution[1]->SetBins(bins());
    resolution[1]->SetX("jetEt","Reco Jet E_{T}");
    resolution[1]->SetY("l1JetEt","L1 Jet E_{T}");
    resolution[1]->SetOutName(triggerName+"_jetEt_over_l1JetEt_endcap");
    resolution[1]->SetAddMark("Endcap");

    // Jet Et - barrel + end-cap
    resolution.emplace_back(new TL1Resolution());
    resolution[2]->SetBins(bins());
    resolution[2]->SetX("jetEt","Reco Jet E_{T}");
    resolution[2]->SetY("l1JetEt","L1 Jet E_{T}");
    resolution[2]->SetOutName(triggerName+"_jetEt_over_l1JetEt_barrel-endcap");
    resolution[2]->SetAddMark("Barrel+endcap");

    // Jet Et - HF
    resolution.emplace_back(new TL1Resolution());
    resolution[3]->SetBins(bins());
    resolution[3]->SetX("jetEt","Reco Jet E_{T}");
    resolution[3]->SetY("l1JetEt","L1 Jet E_{T}");
    resolution[3]->SetOutName(triggerName+"_jetEt_over_l1JetEt_hf");
    resolution[3]->SetAddMark("HF");

    // Jet phi - barrel
    resolution.emplace_back(new TL1Resolution());
    resolution[4]->SetBins(bins());
    resolution[4]->SetX("jetPhi","Reco Jet Phi");
    resolution[4]->SetY("l1JetPhi","L1 Jet Phi");
    resolution[4]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_barrel");
    resolution[4]->SetAddMark("Barrel");

    // Jet Phi - endcap
    resolution.emplace_back(new TL1Resolution());
    resolution[5]->SetBins(bins());
    resolution[5]->SetX("jetPhi","Reco Jet Phi");
    resolution[5]->SetY("l1JetPhi","L1 Jet Phi");
    resolution[5]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_endcap");
    resolution[3]->SetAddMark("Endcap");

    // Jet Phi - barrel + endcap
    resolution.emplace_back(new TL1Resolution());
    resolution[6]->SetBins(bins());
    resolution[6]->SetX("jetPhi","Reco Jet Phi");
    resolution[6]->SetY("l1JetPhi","L1 Jet Phi");
    resolution[6]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_barrel-endcap");
    resolution[3]->SetAddMark("Barrel+endcap");

    // Jet Phi - HF
    resolution.emplace_back(new TL1Resolution());
    resolution[7]->SetBins(bins());
    resolution[7]->SetX("jetPhi","Reco Jet Phi");
    resolution[7]->SetY("l1JetPhi","L1 Jet Phi");
    resolution[7]->SetOutName(triggerName+"_jetPhi_over_l1JetPhi_hf");
    resolution[3]->SetAddMark("HF");

    // Jet Eta
    resolution.emplace_back(new TL1Resolution());
    resolution[8]->SetBins(bins());
    resolution[8]->SetX("jetEta","Reco Jet Eta");
    resolution[8]->SetY("l1JetEta","L1 Jet Eta");
    resolution[8]->SetOutName(triggerName+"_jetEta_over_l1JetEta");

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
    {
        (*it)->SetSample(sample,"");
        (*it)->SetTrigger(triggerName,triggerTitle);
        (*it)->SetRun(run);
        (*it)->SetOutDir(outDir);
        (*it)->InitPlots();
    }
    
    unsigned NEntries = event->GetPEvent()->GetNEntries();
    while( event->Next() )
    {
        unsigned position = event->GetPEvent()->GetPosition()+1;
        TL1Progress::PrintProgressBar(position, NEntries);

        for(unsigned iRecoJet=0; iRecoJet<event->GetPEvent()->fJets->nJets; ++iRecoJet)
        {
            std::shared_ptr<TL1JetMatch> jetMatch(new TL1JetMatch(0, iRecoJet));
            if( !event->GetMatchedJet(jetMatch.get()) ) continue;

            unsigned iL1Jet = jetMatch->GetIL1();
            double l1Et = event->fL1JetEt[iL1Jet];
            double l1Eta = event->fL1JetEta[iL1Jet];
            double l1Phi = event->fL1JetPhi[iL1Jet];
            
            double recoEt = event->GetPEvent()->fJets->etCorr[iRecoJet];
            double recoEta = event->GetPEvent()->fJets->eta[iRecoJet];
            double recoPhi = event->GetPEvent()->fJets->phi[iRecoJet];

            if( abs(recoEta) >= 3.0 )
            {
                if(recoEt>=30.0001 && l1Et!=0.0) resolution[3]->Fill(recoEt, l1Et);
                if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0001) resolution[7]->Fill(recoPhi, l1Phi);
                if(recoEta!=0.0 && l1Eta!=0.0 && recoEt>=30.0001) resolution[8]->Fill(recoEta, l1Eta);
            }

            // Jet filter (tight lepton veto and zero muon multiplicity)
            if( !event->fJetFilterPassFlags[iRecoJet] ) continue;
            if( abs(recoEta) < 3.0 )
            {
                if(recoEta!=0.0 && l1Eta!=0.0 && recoEt>=30.0001) resolution[8]->Fill(recoEta, l1Eta);
                if(recoEt>=30.0001 && l1Et!=0.0 ) resolution[2]->Fill(recoEt, l1Et);
                if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0001) resolution[6]->Fill(recoPhi, l1Phi);
            }

            if( abs(recoEta) < 1.3 )
            {
                if(recoEt!=0.0 && l1Et!=0.0 && recoEt>=30.0001) resolution[0]->Fill(recoEt, l1Et);
                if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0001) resolution[4]->Fill(recoPhi, l1Phi);
            }
            else if( abs(recoEta) < 3.0 )
            {
                if(recoEt!=0.0 && l1Et!=0.0 && recoEt>=30.0001) resolution[1]->Fill(recoEt, l1Et);
                if(recoPhi!=0.0 && l1Phi!=0.0 && recoEt>=30.0001) resolution[5]->Fill(recoPhi, l1Phi);
            }
        }

    }

    for(auto it=resolution.begin(); it!=resolution.end(); ++it)
        (*it)->DrawPlots();
}

std::vector<double> bins()
{
    std::vector<double> temp;
    for(double binLowerEdge=-1.0; binLowerEdge<=3.0; binLowerEdge+= 0.02) temp.push_back(binLowerEdge);
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
