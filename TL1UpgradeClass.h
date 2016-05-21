#ifndef TL1UPGRADECLASS
#define TL1UPGRADECLASS

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TL1DataClass.h"

#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1UpgradeDataFormat.h"

class TL1UpgradeClass : public TL1DataClass
{
    public:
        using TL1DataClass::TL1DataClass;
        void Fill();

        // Declaration of leaf types
        //L1Analysis::L1AnalysisL1UpgradeDataFormat *L1Upgrade;
        TTreeReaderValue<UShort_t>               nEGs;
        TTreeReaderValue<vector<float>>          egEt;
        TTreeReaderValue<vector<float>>          egEta;
        TTreeReaderValue<vector<float>>          egPhi;
        TTreeReaderValue<vector<short>>          egIEt;
        TTreeReaderValue<vector<short>>          egIEta;
        TTreeReaderValue<vector<short>>          egIPhi;
        TTreeReaderValue<vector<short>>          egIso;
        TTreeReaderValue<vector<short>>          egBx;
        TTreeReaderValue<UShort_t>               nTaus;
        TTreeReaderValue<vector<float>>          tauEt;
        TTreeReaderValue<vector<float>>          tauEta;
        TTreeReaderValue<vector<float>>          tauPhi;
        TTreeReaderValue<vector<short>>          tauIEt;
        TTreeReaderValue<vector<short>>          tauIEta;
        TTreeReaderValue<vector<short>>          tauIPhi;
        TTreeReaderValue<vector<short>>          tauIso;
        TTreeReaderValue<vector<short>>          tauBx;
        TTreeReaderValue<UShort_t>               nJets;
        TTreeReaderValue<vector<float>>          jetEt;
        TTreeReaderValue<vector<float>>          jetEta;
        TTreeReaderValue<vector<float>>          jetPhi;
        TTreeReaderValue<vector<short>>          jetIEt;
        TTreeReaderValue<vector<short>>          jetIEta;
        TTreeReaderValue<vector<short>>          jetIPhi;
        TTreeReaderValue<vector<short>>          jetBx;
        TTreeReaderValue<UShort_t>               nMuons;
        TTreeReaderValue<vector<float>>          muonEt;
        TTreeReaderValue<vector<float>>          muonEta;
        TTreeReaderValue<vector<float>>          muonPhi;
        TTreeReaderValue<vector<short>>          muonIEt;
        TTreeReaderValue<vector<short>>          muonIEta;
        TTreeReaderValue<vector<short>>          muonIPhi;
        TTreeReaderValue<vector<short>>          muonChg;
        TTreeReaderValue<vector<unsigned short>> muonIso;
        TTreeReaderValue<vector<unsigned short>> muonQual;
        TTreeReaderValue<vector<unsigned short>> muonTfMuonIdx;
        TTreeReaderValue<vector<short>>          muonBx;
        TTreeReaderValue<UShort_t>               nSums;
        TTreeReaderValue<vector<short>>          sumType;
        TTreeReaderValue<vector<float>>          sumEt;
        TTreeReaderValue<vector<float>>          sumPhi;
        TTreeReaderValue<vector<short>>          sumIEt;
        TTreeReaderValue<vector<short>>          sumIPhi;
        TTreeReaderValue<vector<float>>          sumBx;
};

void TL1UpgradeClass::Fill()
{
    nEGs          = TTreeReaderValue<UShort_t>              (*fReader, "nEGs");
    egEt          = TTreeReaderValue<vector<float>>         (*fReader, "egEt");
    egEta         = TTreeReaderValue<vector<float>>         (*fReader, "egEta");
    egPhi         = TTreeReaderValue<vector<float>>         (*fReader, "egPhi");
    egIEt         = TTreeReaderValue<vector<short>>         (*fReader, "egIEt");
    egIEta        = TTreeReaderValue<vector<short>>         (*fReader, "egIEta");
    egIPhi        = TTreeReaderValue<vector<short>>         (*fReader, "egIPhi");
    egIso         = TTreeReaderValue<vector<short>>         (*fReader, "egIso");
    egBx          = TTreeReaderValue<vector<short>>         (*fReader, "egBx");
    nTaus         = TTreeReaderValue<UShort_t>              (*fReader, "nTaus");
    tauEt         = TTreeReaderValue<vector<float>>         (*fReader, "tauEt");
    tauEta        = TTreeReaderValue<vector<float>>         (*fReader, "tauEta");
    tauPhi        = TTreeReaderValue<vector<float>>         (*fReader, "tauPhi");
    tauIEt        = TTreeReaderValue<vector<short>>         (*fReader, "tauIEt");
    tauIEta       = TTreeReaderValue<vector<short>>         (*fReader, "tauIEta");
    tauIPhi       = TTreeReaderValue<vector<short>>         (*fReader, "tauIPhi");
    tauIso        = TTreeReaderValue<vector<short>>         (*fReader, "tauIso");
    tauBx         = TTreeReaderValue<vector<short>>         (*fReader, "tauBx");
    nJets         = TTreeReaderValue<UShort_t>              (*fReader, "nJets");
    jetEt         = TTreeReaderValue<vector<float>>         (*fReader, "jetEt");
    jetEta        = TTreeReaderValue<vector<float>>         (*fReader, "jetEta");
    jetPhi        = TTreeReaderValue<vector<float>>         (*fReader, "jetPhi");
    jetIEt        = TTreeReaderValue<vector<short>>         (*fReader, "jetIEt");
    jetIEta       = TTreeReaderValue<vector<short>>         (*fReader, "jetIEta");
    jetIPhi       = TTreeReaderValue<vector<short>>         (*fReader, "jetIPhi");
    jetBx         = TTreeReaderValue<vector<short>>         (*fReader, "jetBx");
    nMuons        = TTreeReaderValue<UShort_t>              (*fReader, "nMuons");
    muonEt        = TTreeReaderValue<vector<float>>         (*fReader, "muonEt");
    muonEta       = TTreeReaderValue<vector<float>>         (*fReader, "muonEta");
    muonPhi       = TTreeReaderValue<vector<float>>         (*fReader, "muonPhi");
    muonIEt       = TTreeReaderValue<vector<short>>         (*fReader, "muonIEt");
    muonIEta      = TTreeReaderValue<vector<short>>         (*fReader, "muonIEta");
    muonIPhi      = TTreeReaderValue<vector<short>>         (*fReader, "muonIPhi");
    muonChg       = TTreeReaderValue<vector<short>>         (*fReader, "muonChg");
    muonIso       = TTreeReaderValue<vector<unsigned short>>(*fReader, "muonIso");
    muonQual      = TTreeReaderValue<vector<unsigned short>>(*fReader, "muonQual");
    muonTfMuonIdx = TTreeReaderValue<vector<unsigned short>>(*fReader, "muonTfMuonIdx");
    muonBx        = TTreeReaderValue<vector<short>>         (*fReader, "muonBx");
    nSums         = TTreeReaderValue<UShort_t>              (*fReader, "nSums");
    sumType       = TTreeReaderValue<vector<short>>         (*fReader, "sumType");
    sumEt         = TTreeReaderValue<vector<float>>         (*fReader, "sumEt");
    sumPhi        = TTreeReaderValue<vector<float>>         (*fReader, "sumPhi");
    sumIEt        = TTreeReaderValue<vector<short>>         (*fReader, "sumIEt");
    sumIPhi       = TTreeReaderValue<vector<short>>         (*fReader, "sumIPhi");
    sumBx         = TTreeReaderValue<vector<float>>         (*fReader, "sumBx");
}

#endif
