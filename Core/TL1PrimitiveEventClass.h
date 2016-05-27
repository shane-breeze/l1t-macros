#ifndef TL1PRIMITIVEEVENTCLASS_H
#define TL1PRIMITIVEEVENTCLASS_H

#include <string>
#include <memory>

#include <TMath.h>
#include <TVector2.h>

#include "TL1DataClass.h"

//#include "../160510_l1t-integration-v46p0/CMSSW_8_0_7/src/L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"
//#include "../160510_l1t-integration-v46p0/CMSSW_8_0_7/src/L1Trigger/L1TNtuples/interface/L1AnalysisRecoJetDataFormat.h"
//#include "../160510_l1t-integration-v46p0/CMSSW_8_0_7/src/L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetDataFormat.h"
//#include "../160510_l1t-integration-v46p0/CMSSW_8_0_7/src/L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
//#include "../160510_l1t-integration-v46p0/CMSSW_8_0_7/src/L1Trigger/L1TNtuples/interface/L1AnalysisRecoVertexDataFormat.h"
//#include "../160510_l1t-integration-v46p0/CMSSW_8_0_7/src/L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetFilterDataFormat.h"
//#include "../160510_l1t-integration-v46p0/CMSSW_8_0_7/src/L1Trigger/L1TNtuples/interface/L1AnalysisRecoMuon2DataFormat.h"

class TL1PrimitiveEventClass
{
    public:
        TL1PrimitiveEventClass(std::string inDir);
        bool Next();
        void GetEntry(int i);

        std::shared_ptr<L1Analysis::L1AnalysisL1CaloTowerDataFormat>   fCaloTowers;
        std::shared_ptr<L1Analysis::L1AnalysisRecoJetDataFormat>       fJets;
        std::shared_ptr<L1Analysis::L1AnalysisRecoMetDataFormat>       fSums;
        std::shared_ptr<L1Analysis::L1AnalysisL1UpgradeDataFormat>     fUpgrade;
        std::shared_ptr<L1Analysis::L1AnalysisRecoVertexDataFormat>    fVertex;
        std::shared_ptr<L1Analysis::L1AnalysisRecoMetFilterDataFormat> fMetFilters;
        std::shared_ptr<L1Analysis::L1AnalysisRecoMuon2DataFormat>     fMuons;     

    private:
        std::shared_ptr<TL1DataClass> caloTower, jetReco, metFilterReco, muonReco, recoTree, upgrade;
        Long64_t fPos;
};

TL1PrimitiveEventClass::TL1PrimitiveEventClass(std::string inDir) :
    caloTower(new TL1DataClass("l1CaloTowerTree/L1CaloTowerTree",inDir)),
    jetReco(new TL1DataClass("l1JetRecoTree/JetRecoTree",inDir)),
    metFilterReco(new TL1DataClass("l1MetFilterRecoTree/MetFilterRecoTree",inDir)),
    muonReco(new TL1DataClass("l1MuonRecoTree/Muon2RecoTree",inDir)),
    recoTree(new TL1DataClass("l1RecoTree/RecoTree",inDir)),
    upgrade(new TL1DataClass("l1UpgradeTree/L1UpgradeTree",inDir)),
    fCaloTowers(new L1Analysis::L1AnalysisL1CaloTowerDataFormat()),
    fJets      (new L1Analysis::L1AnalysisRecoJetDataFormat()),
    fSums      (new L1Analysis::L1AnalysisRecoMetDataFormat()),
    fUpgrade   (new L1Analysis::L1AnalysisL1UpgradeDataFormat()),
    fVertex    (new L1Analysis::L1AnalysisRecoVertexDataFormat()),
    fMetFilters(new L1Analysis::L1AnalysisRecoMetFilterDataFormat()),
    fMuons     (new L1Analysis::L1AnalysisRecoMuon2DataFormat()),
    fPos(0)
{
    caloTower->SetBranchAddress("L1CaloTower", &fCaloTowers);
    jetReco->SetBranchAddress("Jet", &fJets);
    jetReco->SetBranchAddress("Sums", &fSums);
    metFilterReco->SetBranchAddress("MetFilters", &fMetFilters);
    muonReco->SetBranchAddress("Muon", &fMuons);
    recoTree->SetBranchAddress("Vertex", &fVertex);
    upgrade->SetBranchAddress("L1Upgrade", &fUpgrade);
}

bool TL1PrimitiveEventClass::Next()
{
    if( fPos >= caloTower->GetEntries()-1 ) return false;
    caloTower->LoadTree(fPos);
    jetReco->LoadTree(fPos);
    metFilterReco->LoadTree(fPos);
    muonReco->LoadTree(fPos);
    recoTree->LoadTree(fPos);
    upgrade->LoadTree(fPos);

    caloTower->GetEntry(fPos);
    jetReco->GetEntry(fPos);
    metFilterReco->GetEntry(fPos);
    muonReco->GetEntry(fPos);
    recoTree->GetEntry(fPos);
    upgrade->GetEntry(fPos);
    
    ++fPos;

    return true;
}

void TL1PrimitiveEventClass::GetEntry(int i)
{
    caloTower->LoadTree(i);
    jetReco->LoadTree(i);
    metFilterReco->LoadTree(i);
    muonReco->LoadTree(i);
    recoTree->LoadTree(i);
    upgrade->LoadTree(i);

    caloTower->GetEntry(i);
    jetReco->GetEntry(i);
    metFilterReco->GetEntry(i);
    muonReco->GetEntry(i);
    recoTree->GetEntry(i);
    upgrade->GetEntry(i);
}

#endif
