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
    std::string run = "273301";
    std::string outDirBase = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput";

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    std::vector<std::shared_ptr<TL1XvsY>> xvsy;

    // caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    std::string outDir = outDirBase+"/"+xvsy.front()->GetDate()+"_"+sample+"_"+"run-"+run+"_"+triggerName+"/xy/";
    xvsy[0]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    xvsy[0]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[0]->SetY("l1Met","L1 E_{T}^{miss} (GeV)");
    xvsy[0]->SetOutName(triggerName+"_caloMetBE_vs_l1Met_lowPU");
    xvsy[0]->SetAddMark("0PU12");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[1]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[1]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[1]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[1]->SetOutName(triggerName+"_recalcRecoMht_vs_l1Mht_lowPU");
    xvsy[1]->SetAddMark("0PU12");

    // caloEttBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[2]->SetXBins(bins(600.0,10,0.0));
    xvsy[2]->SetX("recoEtt","Reco Total E_{T} (GeV)");
    xvsy[2]->SetYBins(bins(600.0,10,0.0));
    xvsy[2]->SetY("l1Ett","L1 Total E_{T}");
    xvsy[2]->SetOutName(triggerName+"_recoEtt_vs_l1Ett_lowPU");
    xvsy[2]->SetAddMark("0PU12");

    // htt
    xvsy.emplace_back(new TL1XvsY());
    xvsy[3]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[3]->SetX("recohtt","Reco Total H_{T} (GeV)");
    xvsy[3]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[3]->SetY("l1Htt","L1 Total H_{T}");
    xvsy[3]->SetOutName(triggerName+"_htt_vs_l1Htt_lowPU");
    xvsy[3]->SetAddMark("0PU12");
    
    // caloMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[4]->SetXBins(phiBins());
    xvsy[4]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    xvsy[4]->SetYBins(phiBins());
    xvsy[4]->SetY("l1MetPhi","L1 E_{T}^{miss} Phi");
    xvsy[4]->SetOutName(triggerName+"_caloMetBEPhi_vs_l1MetPhi_lowPU");
    xvsy[4]->SetAddMark("0PU12");

    // mht Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[5]->SetXBins(phiBins());
    xvsy[5]->SetX("recalcRecoMhtPhi","Reco H_{T}^{miss} Phi");
    xvsy[5]->SetYBins(phiBins());
    xvsy[5]->SetY("l1MhtPhi","L1 H_{T}^{miss} Phi");
    xvsy[5]->SetOutName(triggerName+"_recalcRecoMhtPhi_vs_l1MhtPhi_lowPU");
    xvsy[5]->SetAddMark("0PU12");

    // l1MhtFloat
    xvsy.emplace_back(new TL1XvsY());
    xvsy[6]->SetXBins(bins(200.0,2.5,0.0));
    xvsy[6]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[6]->SetYBins(bins(200.0,2.5,0.0));
    xvsy[6]->SetY("recalcl1mht","Recalc L1 H_{T}^{miss} (GeV)");
    xvsy[6]->SetOutName(triggerName+"_recalcRecoMht_vs_recalcL1Mht_lowPU");
    xvsy[6]->SetAddMark("0PU12");
    //xvsy[6]->SetAddMark("n_{j}^{MHT}=4");
    
    // l1EttNjet vs recoEttNjet
    xvsy.emplace_back(new TL1XvsY());
    xvsy[7]->SetXBins(bins(10,1,0));
    xvsy[7]->SetX("nJetRecoEtt","Njet in Recalc Reco H_{T}^{miss}");
    xvsy[7]->SetYBins(bins(10,1,0));
    xvsy[7]->SetY("nJetL1Ett","Njet in Recalc L1 H_{T}^{miss}");
    xvsy[7]->SetOutName(triggerName+"_nJetRecoMht_vs_nJetL1Mht_lowPU");
    xvsy[7]->SetAddMark("0PU12");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[8]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[8]->SetX("recoMht","Reco H_{T}^{miss} (GeV)");
    xvsy[8]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[8]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[8]->SetOutName(triggerName+"_recoMht_vs_l1Mht_lowPU");
    xvsy[8]->SetAddMark("0PU12");


    // caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[9]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[9]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    xvsy[9]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[9]->SetY("l1Met","L1 E_{T}^{miss} (GeV)");
    xvsy[9]->SetOutName(triggerName+"_caloMetBE_vs_l1Met_medPU");
    xvsy[9]->SetAddMark("13PU19");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[10]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[10]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[10]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[10]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[10]->SetOutName(triggerName+"_recalcRecoMht_vs_l1Mht_medPU");
    xvsy[10]->SetAddMark("13PU19");

    // caloEttBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[11]->SetXBins(bins(600.0,10,0.0));
    xvsy[11]->SetX("recoEtt","Reco Total E_{T} (GeV)");
    xvsy[11]->SetYBins(bins(600.0,10,0.0));
    xvsy[11]->SetY("l1Ett","L1 Total E_{T}");
    xvsy[11]->SetOutName(triggerName+"_recoEtt_vs_l1Ett_medPU");
    xvsy[11]->SetAddMark("13PU19");

    // htt
    xvsy.emplace_back(new TL1XvsY());
    xvsy[12]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[12]->SetX("recohtt","Reco Total H_{T} (GeV)");
    xvsy[12]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[12]->SetY("l1Htt","L1 Total H_{T}");
    xvsy[12]->SetOutName(triggerName+"_htt_vs_l1Htt_medPU");
    xvsy[12]->SetAddMark("13PU19");
    
    // caloMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[13]->SetXBins(phiBins());
    xvsy[13]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    xvsy[13]->SetYBins(phiBins());
    xvsy[13]->SetY("l1MetPhi","L1 E_{T}^{miss} Phi");
    xvsy[13]->SetOutName(triggerName+"_caloMetBEPhi_vs_l1MetPhi_medPU");
    xvsy[13]->SetAddMark("13PU19");

    // mht Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[14]->SetXBins(phiBins());
    xvsy[14]->SetX("recalcRecoMhtPhi","Reco H_{T}^{miss} Phi");
    xvsy[14]->SetYBins(phiBins());
    xvsy[14]->SetY("l1MhtPhi","L1 H_{T}^{miss} Phi");
    xvsy[14]->SetOutName(triggerName+"_recalcRecoMhtPhi_vs_l1MhtPhi_medPU");
    xvsy[14]->SetAddMark("13PU19");

    // l1MhtFloat
    xvsy.emplace_back(new TL1XvsY());
    xvsy[15]->SetXBins(bins(200.0,2.5,0.0));
    xvsy[15]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[15]->SetYBins(bins(200.0,2.5,0.0));
    xvsy[15]->SetY("recalcl1mht","Recalc L1 H_{T}^{miss} (GeV)");
    xvsy[15]->SetOutName(triggerName+"_recalcRecoMht_vs_recalcL1Mht_medPU");
    xvsy[15]->SetAddMark("13PU19");
    //xvsy[6]->SetAddMark("n_{j}^{MHT}=4");
    
    // l1EttNjet vs recoEttNjet
    xvsy.emplace_back(new TL1XvsY());
    xvsy[16]->SetXBins(bins(10,1,0));
    xvsy[16]->SetX("nJetRecoEtt","Njet in Recalc Reco H_{T}^{miss}");
    xvsy[16]->SetYBins(bins(10,1,0));
    xvsy[16]->SetY("nJetL1Ett","Njet in Recalc L1 H_{T}^{miss}");
    xvsy[16]->SetOutName(triggerName+"_nJetRecoMht_vs_nJetL1Mht_medPU");
    xvsy[16]->SetAddMark("13PU19");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[17]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[17]->SetX("recoMht","Reco H_{T}^{miss} (GeV)");
    xvsy[17]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[17]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[17]->SetOutName(triggerName+"_recoMht_vs_l1Mht_medPU");
    xvsy[17]->SetAddMark("13PU19");

    // caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[18]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[18]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    xvsy[18]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[18]->SetY("l1Met","L1 E_{T}^{miss} (GeV)");
    xvsy[18]->SetOutName(triggerName+"_caloMetBE_vs_l1Met_highPU");
    xvsy[18]->SetAddMark("20PU");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[19]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[19]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[19]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[19]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[19]->SetOutName(triggerName+"_recalcRecoMht_vs_l1Mht_highPU");
    xvsy[19]->SetAddMark("20PU");

    // caloEttBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[20]->SetXBins(bins(600.0,10,0.0));
    xvsy[20]->SetX("recoEtt","Reco Total E_{T} (GeV)");
    xvsy[20]->SetYBins(bins(600.0,10,0.0));
    xvsy[20]->SetY("l1Ett","L1 Total E_{T}");
    xvsy[20]->SetOutName(triggerName+"_recoEtt_vs_l1Ett_highPU");
    xvsy[20]->SetAddMark("20PU");

    // htt
    xvsy.emplace_back(new TL1XvsY());
    xvsy[21]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[21]->SetX("recohtt","Reco Total H_{T} (GeV)");
    xvsy[21]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[21]->SetY("l1Htt","L1 Total H_{T}");
    xvsy[21]->SetOutName(triggerName+"_htt_vs_l1Htt_highPU");
    xvsy[21]->SetAddMark("20PU");
    
    // caloMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[22]->SetXBins(phiBins());
    xvsy[22]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    xvsy[22]->SetYBins(phiBins());
    xvsy[22]->SetY("l1MetPhi","L1 E_{T}^{miss} Phi");
    xvsy[22]->SetOutName(triggerName+"_caloMetBEPhi_vs_l1MetPhi_highPU");
    xvsy[22]->SetAddMark("20PU");

    // mht Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[23]->SetXBins(phiBins());
    xvsy[23]->SetX("recalcRecoMhtPhi","Reco H_{T}^{miss} Phi");
    xvsy[23]->SetYBins(phiBins());
    xvsy[23]->SetY("l1MhtPhi","L1 H_{T}^{miss} Phi");
    xvsy[23]->SetOutName(triggerName+"_recalcRecoMhtPhi_vs_l1MhtPhi_highPU");
    xvsy[23]->SetAddMark("20PU");

    // l1MhtFloat
    xvsy.emplace_back(new TL1XvsY());
    xvsy[24]->SetXBins(bins(200.0,2.5,0.0));
    xvsy[24]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[24]->SetYBins(bins(200.0,2.5,0.0));
    xvsy[24]->SetY("recalcl1mht","Recalc L1 H_{T}^{miss} (GeV)");
    xvsy[24]->SetOutName(triggerName+"_recalcRecoMht_vs_recalcL1Mht_highPU");
    xvsy[24]->SetAddMark("20PU");
    //xvsy[6]->SetAddMark("n_{j}^{MHT}=4");
    
    // l1EttNjet vs recoEttNjet
    xvsy.emplace_back(new TL1XvsY());
    xvsy[25]->SetXBins(bins(10,1,0));
    xvsy[25]->SetX("nJetRecoEtt","Njet in Recalc Reco H_{T}^{miss}");
    xvsy[25]->SetYBins(bins(10,1,0));
    xvsy[25]->SetY("nJetL1Ett","Njet in Recalc L1 H_{T}^{miss}");
    xvsy[25]->SetOutName(triggerName+"_nJetRecoMht_vs_nJetL1Mht_highPU");
    xvsy[25]->SetAddMark("20PU");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[26]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[26]->SetX("recoMht","Reco H_{T}^{miss} (GeV)");
    xvsy[26]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[26]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[26]->SetOutName(triggerName+"_recoMht_vs_l1Mht_highPU");
    xvsy[26]->SetAddMark("20PU");

    // caloMetBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[27]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[27]->SetX("caloMetBE","Calo E_{T}^{miss} no HF (GeV)");
    xvsy[27]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[27]->SetY("l1Met","L1 E_{T}^{miss} (GeV)");
    xvsy[27]->SetOutName(triggerName+"_caloMetBE_vs_l1Met");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[28]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[28]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[28]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[28]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[28]->SetOutName(triggerName+"_recalcRecoMht_vs_l1Mht");

    // caloEttBE
    xvsy.emplace_back(new TL1XvsY());
    xvsy[29]->SetXBins(bins(600.0,10,0.0));
    xvsy[29]->SetX("recoEtt","Reco Total E_{T} (GeV)");
    xvsy[29]->SetYBins(bins(600.0,10,0.0));
    xvsy[29]->SetY("l1Ett","L1 Total E_{T}");
    xvsy[29]->SetOutName(triggerName+"_recoEtt_vs_l1Ett");

    // htt
    xvsy.emplace_back(new TL1XvsY());
    xvsy[30]->SetXBins(bins(600.0,1.0,0.0));
    xvsy[30]->SetX("recohtt","Reco Total H_{T} (GeV)");
    xvsy[30]->SetYBins(bins(600.0,1.0,0.0));
    xvsy[30]->SetY("l1Htt","L1 Total H_{T}");
    xvsy[30]->SetOutName(triggerName+"_htt_vs_l1Htt");
    
    // caloMetBE Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[31]->SetXBins(phiBins());
    xvsy[31]->SetX("caloMetBEPhi","Calo E_{T}^{miss} Phi (no HF)");
    xvsy[31]->SetYBins(phiBins());
    xvsy[31]->SetY("l1MetPhi","L1 E_{T}^{miss} Phi");
    xvsy[31]->SetOutName(triggerName+"_caloMetBEPhi_vs_l1MetPhi");

    // mht Phi
    xvsy.emplace_back(new TL1XvsY());
    xvsy[32]->SetXBins(phiBins());
    xvsy[32]->SetX("recalcRecoMhtPhi","Reco H_{T}^{miss} Phi");
    xvsy[32]->SetYBins(phiBins());
    xvsy[32]->SetY("l1MhtPhi","L1 H_{T}^{miss} Phi");
    xvsy[32]->SetOutName(triggerName+"_recalcRecoMhtPhi_vs_l1MhtPhi");

    // l1MhtFloat
    xvsy.emplace_back(new TL1XvsY());
    xvsy[33]->SetXBins(bins(200.0,2.5,0.0));
    xvsy[33]->SetX("recalcRecoMht","Recalc Reco H_{T}^{miss} (GeV)");
    xvsy[33]->SetYBins(bins(200.0,2.5,0.0));
    xvsy[33]->SetY("recalcl1mht","Recalc L1 H_{T}^{miss} (GeV)");
    xvsy[33]->SetOutName(triggerName+"_recalcRecoMht_vs_recalcL1Mht");
    //xvsy[6]->SetAddMark("n_{j}^{MHT}=4");
    
    // l1EttNjet vs recoEttNjet
    xvsy.emplace_back(new TL1XvsY());
    xvsy[34]->SetXBins(bins(10,1,0));
    xvsy[34]->SetX("nJetRecoEtt","Njet in Recalc Reco H_{T}^{miss}");
    xvsy[34]->SetYBins(bins(10,1,0));
    xvsy[34]->SetY("nJetL1Ett","Njet in Recalc L1 H_{T}^{miss}");
    xvsy[34]->SetOutName(triggerName+"_nJetRecoMht_vs_nJetL1Mht");

    // mht
    xvsy.emplace_back(new TL1XvsY());
    xvsy[35]->SetXBins(bins(200.0,1.0,0.0));
    xvsy[35]->SetX("recoMht","Reco H_{T}^{miss} (GeV)");
    xvsy[35]->SetYBins(bins(200.0,1.0,0.0));
    xvsy[35]->SetY("l1Mht","L1 H_{T}^{miss}");
    xvsy[35]->SetOutName(triggerName+"_recoMht_vs_l1Mht");

    for(auto it=xvsy.begin(); it!=xvsy.end(); ++it)
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

        int pu = event->GetPEvent()->fVertex->nVtx;
        int add = 0;
        if( pu >= 13 && pu <= 19 ) add = 9;
        else if( pu >= 20 ) add = 18;

        //----- HTT -----//
        xvsy[3+add]->Fill(event->GetPEvent()->fSums->Ht, event->fL1Htt);
        xvsy[30]->Fill(event->GetPEvent()->fSums->Ht, event->fL1Htt);
        //xvsy[3]->Fill(event->fRecalcRecoHtt, event->fL1Htt);
        
        //----- MHT -----//
        if( event->fMhtPassFlag && event->fRecalcRecoMht != 0.0 && event->fL1Mht != 0.0 )
        {
            xvsy[1+add]->Fill(event->fRecalcRecoMht, event->fL1Mht);
            xvsy[28]->Fill(event->fRecalcRecoMht, event->fL1Mht);
        }
        //xvsy[1]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);
        if( event->fMhtPassFlag && event->fRecalcRecoMht != 0.0 && event->fRecalcL1Mht != 0.0 )
        {
            xvsy[5+add]->Fill(FoldPhi(event->fRecalcRecoMhtPhi), FoldPhi(event->fL1MhtPhi));
            xvsy[6+add]->Fill(event->fRecalcRecoMht, event->fRecalcL1Mht);
            xvsy[7+add]->Fill(event->fNJetRecoMht, event->fNJetL1Mht);
            xvsy[32]->Fill(FoldPhi(event->fRecalcRecoMhtPhi), FoldPhi(event->fL1MhtPhi));
            xvsy[33]->Fill(event->fRecalcRecoMht, event->fRecalcL1Mht);
            xvsy[34]->Fill(event->fNJetRecoMht, event->fNJetL1Mht);
        }
        if( event->GetPEvent()->fSums->mHt != 0.0 && event->fL1Mht != 0.0 )
        {
            xvsy[8+add]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);
            xvsy[35]->Fill(event->GetPEvent()->fSums->mHt, event->fL1Mht);
        }

        if( !event->fMuonFilterPassFlag ) continue;
        //----- MET -----//
        if( event->fMetFilterPassFlag )
        {
            xvsy[add]->Fill(event->GetPEvent()->fSums->caloMetBE, event->fL1Met);
            xvsy[27]->Fill(event->GetPEvent()->fSums->caloMetBE, event->fL1Met);
        }

        //----- ETT -----//
        xvsy[2+add]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett);
        xvsy[29]->Fill(event->GetPEvent()->fSums->caloSumEtBE, event->fL1Ett);

        //----- MET Phi -----//
        xvsy[4+add]->Fill(FoldPhi(event->GetPEvent()->fSums->caloMetPhiBE), FoldPhi(event->fL1MetPhi));
        xvsy[31]->Fill(FoldPhi(event->GetPEvent()->fSums->caloMetPhiBE), FoldPhi(event->fL1MetPhi));

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
