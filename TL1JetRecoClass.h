#ifndef TL1JETRECOCLASS_H
#define TL1JETRECOCLASS_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TL1DataClass.h"

#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoJetDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMetDataFormat.h"

class TL1JetRecoClass
{
    private:
        void Fill();

        std::unique_ptr<TChain> fChain;
        std::unique_ptr<TTreeReader> fReader;

    public:
        TL1JetRecoClass(std::string chainPath, std::string inDir);
        bool Next();

        TTreeReaderValue<UShort_t>        nJets;
        TTreeReaderValue<vector<float>>   e;
        TTreeReaderValue<vector<float>>   et;
        TTreeReaderValue<vector<float>>   etCorr;
        TTreeReaderValue<vector<float>>   corrFactor;
        TTreeReaderValue<vector<float>>   eta;
        TTreeReaderValue<vector<float>>   phi;
        TTreeReaderValue<vector<bool>>    isPF;
        TTreeReaderValue<vector<float>>   eEMF;
        TTreeReaderValue<vector<float>>   eHadHB;
        TTreeReaderValue<vector<float>>   eHadHE;
        TTreeReaderValue<vector<float>>   eHadHO;
        TTreeReaderValue<vector<float>>   eHadHF;
        TTreeReaderValue<vector<float>>   eEmEB;
        TTreeReaderValue<vector<float>>   eEmEE;
        TTreeReaderValue<vector<float>>   eEmHF;
        TTreeReaderValue<vector<float>>   eMaxEcalTow;
        TTreeReaderValue<vector<float>>   eMaxHcalTow;
        TTreeReaderValue<vector<float>>   towerArea;
        TTreeReaderValue<vector<short>>   towerSize;
        TTreeReaderValue<vector<short>>   n60;
        TTreeReaderValue<vector<short>>   n90;
        TTreeReaderValue<vector<short>>   n90hits;
        TTreeReaderValue<vector<float>>   fHPD;
        TTreeReaderValue<vector<float>>   fRBX;
        TTreeReaderValue<vector<float>>   chef;
        TTreeReaderValue<vector<float>>   nhef;
        TTreeReaderValue<vector<float>>   pef;
        TTreeReaderValue<vector<float>>   eef;
        TTreeReaderValue<vector<float>>   mef;
        TTreeReaderValue<vector<float>>   hfhef;
        TTreeReaderValue<vector<float>>   hfemef;
        TTreeReaderValue<vector<short>>   chMult;
        TTreeReaderValue<vector<short>>   nhMult;
        TTreeReaderValue<vector<short>>   phMult;
        TTreeReaderValue<vector<short>>   elMult;
        TTreeReaderValue<vector<short>>   muMult;
        TTreeReaderValue<vector<short>>   hfhMult;
        TTreeReaderValue<vector<short>>   hfemMult;
        TTreeReaderValue<vector<float>>   cemef;
        TTreeReaderValue<vector<float>>   cmef;
        TTreeReaderValue<vector<float>>   nemef;
        TTreeReaderValue<vector<int>>     cMult;
        TTreeReaderValue<vector<int>>     nMult;
        //L1Analysis::L1AnalysisRecoMetDataFormat *Sums;
        TTreeReaderValue<Float_t>         met;
        TTreeReaderValue<Float_t>         metPhi;
        TTreeReaderValue<Float_t>         caloMet;
        TTreeReaderValue<Float_t>         caloMetPhi;
        TTreeReaderValue<Float_t>         caloSumEt;
        TTreeReaderValue<Float_t>         caloMetBE;
        TTreeReaderValue<Float_t>         caloMetPhiBE;
        TTreeReaderValue<Float_t>         caloSumEtBE;
        TTreeReaderValue<Float_t>         Ht;
        TTreeReaderValue<Float_t>         mHt;
        TTreeReaderValue<Float_t>         mHtPhi;
        TTreeReaderValue<Float_t>         sumEt;
        TTreeReaderValue<UShort_t>        ecalFlag;
        TTreeReaderValue<UShort_t>        hcalFlag;
};

TL1JetRecoClass::TL1JetRecoClass(std::string chainPath, std::string inDir)
{
    std::shared_ptr<TChain> chain(new TChain(chainPath.c_str()) );
    chain->Add( Form("%s/*.root",inDir.c_str()) );
    fChain = chain;

    std::shared_ptr<TTreeReader> reader(new TTreeReader(fChain.get()));
    fReader = reader;

    Fill();
}

void TL1JetRecoClass::Fill()
{
    nJets        = TTreeReaderValue<UShort_t>     (*fReader, "nJets");
    e            = TTreeReaderValue<vector<float>>(*fReader, "e");
    et           = TTreeReaderValue<vector<float>>(*fReader, "et");
    etCorr       = TTreeReaderValue<vector<float>>(*fReader, "etCorr");
    corrFactor   = TTreeReaderValue<vector<float>>(*fReader, "corrFactor");
    eta          = TTreeReaderValue<vector<float>>(*fReader, "eta");
    phi          = TTreeReaderValue<vector<float>>(*fReader, "phi");
    isPF         = TTreeReaderValue<vector<bool>> (*fReader, "isPF");
    eEMF         = TTreeReaderValue<vector<float>>(*fReader, "eEMF");
    eHadHB       = TTreeReaderValue<vector<float>>(*fReader, "eHadHB");
    eHadHE       = TTreeReaderValue<vector<float>>(*fReader, "eHadHE");
    eHadHO       = TTreeReaderValue<vector<float>>(*fReader, "eHadHO");
    eHadHF       = TTreeReaderValue<vector<float>>(*fReader, "eHadHF");
    eEmEB        = TTreeReaderValue<vector<float>>(*fReader, "eEmEB");
    eEmEE        = TTreeReaderValue<vector<float>>(*fReader, "eEmEE");
    eEmHF        = TTreeReaderValue<vector<float>>(*fReader, "eEmHF");
    eMaxEcalTow  = TTreeReaderValue<vector<float>>(*fReader, "eMaxEcalTow");
    eMaxHcalTow  = TTreeReaderValue<vector<float>>(*fReader, "eMaxHcalTow");
    towerArea    = TTreeReaderValue<vector<float>>(*fReader, "towerArea");
    towerSize    = TTreeReaderValue<vector<short>>(*fReader, "towerSize");
    n60          = TTreeReaderValue<vector<short>>(*fReader, "n60");
    n90          = TTreeReaderValue<vector<short>>(*fReader, "n90");
    n90hits      = TTreeReaderValue<vector<short>>(*fReader, "n90hits");
    fHPD         = TTreeReaderValue<vector<float>>(*fReader, "fHPD");
    fRBX         = TTreeReaderValue<vector<float>>(*fReader, "fRBX");
    chef         = TTreeReaderValue<vector<float>>(*fReader, "chef");
    nhef         = TTreeReaderValue<vector<float>>(*fReader, "nhef");
    pef          = TTreeReaderValue<vector<float>>(*fReader, "pef");
    eef          = TTreeReaderValue<vector<float>>(*fReader, "eef");
    mef          = TTreeReaderValue<vector<float>>(*fReader, "mef");
    hfhef        = TTreeReaderValue<vector<float>>(*fReader, "hfhef");
    hfemef       = TTreeReaderValue<vector<float>>(*fReader, "hfemef");
    chMult       = TTreeReaderValue<vector<short>>(*fReader, "chMult");
    nhMult       = TTreeReaderValue<vector<short>>(*fReader, "nhMult");
    phMult       = TTreeReaderValue<vector<short>>(*fReader, "phMult");
    elMult       = TTreeReaderValue<vector<short>>(*fReader, "elMult");
    muMult       = TTreeReaderValue<vector<short>>(*fReader, "muMult");
    hfhMult      = TTreeReaderValue<vector<short>>(*fReader, "hfhMult");
    hfemMult     = TTreeReaderValue<vector<short>>(*fReader, "hfemMult");
    cemef        = TTreeReaderValue<vector<float>>(*fReader, "cemef");
    cmef         = TTreeReaderValue<vector<float>>(*fReader, "cmef");
    nemef        = TTreeReaderValue<vector<float>>(*fReader, "nemef");
    cMult        = TTreeReaderValue<vector<int>>  (*fReader, "cMult");
    nMult        = TTreeReaderValue<vector<int>>  (*fReader, "nMult");
    met          = TTreeReaderValue<Float_t> (*fReader, "met");
    metPhi       = TTreeReaderValue<Float_t> (*fReader, "metPhi");
    caloMet      = TTreeReaderValue<Float_t> (*fReader, "caloMet");
    caloMetPhi   = TTreeReaderValue<Float_t> (*fReader, "caloMetPhi");
    caloSumEt    = TTreeReaderValue<Float_t> (*fReader, "caloSumEt");
    caloMetBE    = TTreeReaderValue<Float_t> (*fReader, "caloMetBE");
    caloMetPhiBE = TTreeReaderValue<Float_t> (*fReader, "caloMetPhiBE");
    caloSumEtBE  = TTreeReaderValue<Float_t> (*fReader, "caloSumEtBE");
    Ht           = TTreeReaderValue<Float_t> (*fReader, "Ht");
    mHt          = TTreeReaderValue<Float_t> (*fReader, "mHt");
    mHtPhi       = TTreeReaderValue<Float_t> (*fReader, "mHtPhi");
    sumEt        = TTreeReaderValue<Float_t> (*fReader, "sumEt");
    ecalFlag     = TTreeReaderValue<UShort_t>(*fReader, "ecalFlag");
    hcalFlag     = TTreeReaderValue<UShort_t>(*fReader, "hcalFlag");
}

bool TL1JetRecoClass::Next()
{
    return fReader->Next();
}

#endif
