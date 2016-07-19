#ifndef TL1PRIMITIVEEVENTCLASS_H
#define TL1PRIMITIVEEVENTCLASS_H

#include <string>

#include "TL1DataClass.h"

#include "L1Trigger/L1TNtuples/interface/L1AnalysisEventDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisGeneratorDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisEventDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisSimulationDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisGCTDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisGTDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisGMTDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisGTDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRCTDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisDTTFDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisCSCTFDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoJetDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoClusterDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMuonDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoRpcHitDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1ExtraDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoVertexDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoTrackDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1MenuDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisCaloTPDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetFilterDataFormat.h"


class TL1PrimitiveEventClass
{
    public:
        TL1PrimitiveEventClass(std::vector<std::string> inDir);
        bool Next();
        void GetEntry(int i);

        unsigned GetNEntries() const;
        unsigned GetPosition() const;

        L1Analysis::L1AnalysisL1CaloTowerDataFormat   * fCaloTowers;
        L1Analysis::L1AnalysisRecoJetDataFormat       * fJets;
        L1Analysis::L1AnalysisRecoMetDataFormat       * fSums;
        L1Analysis::L1AnalysisL1UpgradeDataFormat     * fUpgrade;
        L1Analysis::L1AnalysisL1UpgradeDataFormat     * fEmuUpgrade;
        L1Analysis::L1AnalysisRecoVertexDataFormat    * fVertex;
        L1Analysis::L1AnalysisRecoMetFilterDataFormat * fMetFilters;
        L1Analysis::L1AnalysisRecoMuon2DataFormat     * fMuons;     

        bool fIsCaloTower, fIsJetReco, fIsMetFilterReco, fIsMuonReco, fIsRecoTree, fIsUpgrade, fIsEmuUpgrade;

    private:
        TL1DataClass * caloTower, * jetReco, * metFilterReco, * muonReco, * recoTree, * upgrade, * emuUpgrade;
        Long64_t fPos;

};

TL1PrimitiveEventClass::TL1PrimitiveEventClass(std::vector<std::string> inDir) :
    caloTower(new TL1DataClass("l1CaloTowerTree/L1CaloTowerTree",inDir)),
    jetReco(new TL1DataClass("l1JetRecoTree/JetRecoTree",inDir)),
    metFilterReco(new TL1DataClass("l1MetFilterRecoTree/MetFilterRecoTree",inDir)),
    muonReco(new TL1DataClass("l1MuonRecoTree/Muon2RecoTree",inDir)),
    recoTree(new TL1DataClass("l1RecoTree/RecoTree",inDir)),
    upgrade(new TL1DataClass("l1UpgradeTree/L1UpgradeTree",inDir)),
    emuUpgrade(new TL1DataClass("l1UpgradeEmuTree/L1UpgradeTree",inDir)),
    fCaloTowers(new L1Analysis::L1AnalysisL1CaloTowerDataFormat()),
    fJets      (new L1Analysis::L1AnalysisRecoJetDataFormat()),
    fSums      (new L1Analysis::L1AnalysisRecoMetDataFormat()),
    fUpgrade   (new L1Analysis::L1AnalysisL1UpgradeDataFormat()),
    fEmuUpgrade(new L1Analysis::L1AnalysisL1UpgradeDataFormat()),
    fVertex    (new L1Analysis::L1AnalysisRecoVertexDataFormat()),
    fMetFilters(new L1Analysis::L1AnalysisRecoMetFilterDataFormat()),
    fMuons     (new L1Analysis::L1AnalysisRecoMuon2DataFormat()),
    fIsCaloTower(true), fIsJetReco(true), fIsMetFilterReco(true), fIsMuonReco(true), 
    fIsRecoTree(true), fIsUpgrade(true), fIsEmuUpgrade(true),
    fPos(0)
{
    if( caloTower->SetBranchAddress("L1CaloTower", &fCaloTowers) < 0 ) fIsCaloTower = false;
    if( jetReco->SetBranchAddress("Jet", &fJets) < 0 ) fIsJetReco = false;
    if( jetReco->SetBranchAddress("Sums", &fSums) < 0 ) fIsJetReco = false;
    if( metFilterReco->SetBranchAddress("MetFilters", &fMetFilters) < 0 ) fIsMetFilterReco = false;
    if( muonReco->SetBranchAddress("Muon", &fMuons) < 0 ) fIsMuonReco = false;
    if( recoTree->SetBranchAddress("Vertex", &fVertex) < 0 ) fIsRecoTree = false;
    if( upgrade->SetBranchAddress("L1Upgrade", &fUpgrade) < 0 ) fIsUpgrade = false;
    if( emuUpgrade->SetBranchAddress("L1Upgrade", &fEmuUpgrade) < 0 ) fIsEmuUpgrade = false;
}

bool TL1PrimitiveEventClass::Next()
{
    if( fPos >= emuUpgrade->GetEntries()-1 ) return false;
    if( fIsCaloTower ) caloTower->LoadTree(fPos);
    if( fIsJetReco ) jetReco->LoadTree(fPos);
    if( fIsMetFilterReco ) metFilterReco->LoadTree(fPos);
    if( fIsMuonReco ) muonReco->LoadTree(fPos);
    if( fIsRecoTree ) recoTree->LoadTree(fPos);
    if( fIsUpgrade ) upgrade->LoadTree(fPos);
    if( fIsEmuUpgrade ) emuUpgrade->LoadTree(fPos);

    if( fIsCaloTower ) caloTower->GetEntry(fPos);
    if( fIsJetReco ) jetReco->GetEntry(fPos);
    if( fIsMetFilterReco ) metFilterReco->GetEntry(fPos);
    if( fIsMuonReco ) muonReco->GetEntry(fPos);
    if( fIsRecoTree ) recoTree->GetEntry(fPos);
    if( fIsUpgrade ) upgrade->GetEntry(fPos);
    if( fIsEmuUpgrade ) emuUpgrade->GetEntry(fPos);
    
    ++fPos;

    return true;
}

void TL1PrimitiveEventClass::GetEntry(int i)
{
    if( fIsCaloTower ) caloTower->LoadTree(i);
    if( fIsJetReco ) jetReco->LoadTree(i);
    if( fIsMetFilterReco ) metFilterReco->LoadTree(i);
    if( fIsMuonReco ) muonReco->LoadTree(i);
    if( fIsRecoTree ) recoTree->LoadTree(i);
    if( fIsUpgrade ) upgrade->LoadTree(i);
    if( fIsEmuUpgrade ) emuUpgrade->LoadTree(i);

    if( fIsCaloTower ) caloTower->GetEntry(i);
    if( fIsJetReco ) jetReco->GetEntry(i);
    if( fIsMetFilterReco ) metFilterReco->GetEntry(i);
    if( fIsMuonReco ) muonReco->GetEntry(i);
    if( fIsRecoTree ) recoTree->GetEntry(i);
    if( fIsUpgrade ) upgrade->GetEntry(i);
    if( fIsEmuUpgrade ) emuUpgrade->GetEntry(i);
}

unsigned TL1PrimitiveEventClass::GetNEntries() const
{
    if( fIsEmuUpgrade ) return emuUpgrade->GetEntries();
    if( fIsUpgrade ) return upgrade->GetEntries();
    if( fIsCaloTower ) return caloTower->GetEntries();
    if( fIsJetReco ) return jetReco->GetEntries();
    if( fIsMetFilterReco ) return metFilterReco->GetEntries();
    if( fIsMuonReco ) return muonReco->GetEntries();
    if( fIsRecoTree ) return recoTree->GetEntries();
    return 0;
}

unsigned TL1PrimitiveEventClass::GetPosition() const
{
    return fPos;
}

#endif
