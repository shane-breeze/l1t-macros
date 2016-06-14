#ifndef TL1PRIMITIVEEVENTCLASS_H
#define TL1PRIMITIVEEVENTCLASS_H

#include <string>

#include "TL1DataClass.h"

class TL1PrimitiveEventClass
{
    public:
        TL1PrimitiveEventClass(std::string inDir);
        bool Next();
        void GetEntry(int i);

        unsigned GetNEntries() const;
        unsigned GetPosition() const;

        L1Analysis::L1AnalysisL1CaloTowerDataFormat   * fCaloTowers;
        L1Analysis::L1AnalysisRecoJetDataFormat       * fJets;
        L1Analysis::L1AnalysisRecoMetDataFormat       * fSums;
        L1Analysis::L1AnalysisL1UpgradeDataFormat     * fUpgrade;
        L1Analysis::L1AnalysisRecoVertexDataFormat    * fVertex;
        L1Analysis::L1AnalysisRecoMetFilterDataFormat * fMetFilters;
        L1Analysis::L1AnalysisRecoMuon2DataFormat     * fMuons;     

    private:
        TL1DataClass * caloTower, * jetReco, * metFilterReco, * muonReco, * recoTree, * upgrade;
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

unsigned TL1PrimitiveEventClass::GetNEntries() const
{
    return caloTower->GetEntries();
}

unsigned TL1PrimitiveEventClass::GetPosition() const
{
    return fPos;
}

#endif
