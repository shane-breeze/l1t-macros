#ifndef TL1MUONRECOCLASS_H
#define TL1MUONRECOCLASS_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TL1DataClass.h"

#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoMuon2DataFormat.h"

class TL1MuonRecoClass : public TL1DataClass
{
    public:
        using TL1DataClass::TL1DataClass;
        void Fill();

        TTreeReaderValue<UShort_t>        nMuons;
        TTreeReaderValue<vector<float>>   e;
        TTreeReaderValue<vector<float>>   et;
        TTreeReaderValue<vector<float>>   pt;
        TTreeReaderValue<vector<float>>   eta;
        TTreeReaderValue<vector<float>>   phi;
        TTreeReaderValue<vector<bool>>    isLooseMuon;
        TTreeReaderValue<vector<bool>>    isMediumMuon;
        TTreeReaderValue<vector<float>>   iso;
        TTreeReaderValue<vector<short>>   hlt_isomu;
        TTreeReaderValue<vector<short>>   hlt_mu;
        TTreeReaderValue<vector<float>>   hlt_isoDeltaR;
        TTreeReaderValue<vector<float>>   hlt_deltaR;
};

void TL1MuonRecoClass::Fill()
{
    nMuons        = TTreeReaderValue<UShort_t>     (*fReader, "nMuons");
    e             = TTreeReaderValue<vector<float>>(*fReader, "e");
    et            = TTreeReaderValue<vector<float>>(*fReader, "et");
    pt            = TTreeReaderValue<vector<float>>(*fReader, "pt");
    eta           = TTreeReaderValue<vector<float>>(*fReader, "eta");
    phi           = TTreeReaderValue<vector<float>>(*fReader, "phi");
    isLooseMuon   = TTreeReaderValue<vector<bool>> (*fReader, "isLooseMuon");
    isMediumMuon  = TTreeReaderValue<vector<bool>> (*fReader, "isMediumMuon");
    iso           = TTreeReaderValue<vector<float>>(*fReader, "iso");
    hlt_isomu     = TTreeReaderValue<vector<short>>(*fReader, "hlt_isomu");
    hlt_mu        = TTreeReaderValue<vector<short>>(*fReader, "hlt_mu");
    hlt_isoDeltaR = TTreeReaderValue<vector<float>>(*fReader, "hlt_isoDeltaR");
    hlt_deltaR    = TTreeReaderValue<vector<float>>(*fReader, "hlt_deltaR");
}

#endif
