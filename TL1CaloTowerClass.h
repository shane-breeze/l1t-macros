#ifndef TL1CALOTOWERCLASS_H
#define TL1CALOTOWERCLASS_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TL1DataClass.h"

#include "L1Trigger/L1TNtuples/interface/L1AnalysisCaloTPDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloTowerDataFormat.h"
#include "L1Trigger/L1TNtuples/interface/L1AnalysisL1CaloClusterDataFormat.h"

class TL1CaloTowerClass : public TL1DataClass
{
    public:
        using TL1DataClass::TL1DataClass;
        void Fill();

        // Declaration of leaf types - removed ambiguous leaves
        //L1Analysis::L1AnalysisCaloTPDataFormat *CaloTP;
        TTreeReaderValue<Short_t>         nHCALTP;
        TTreeReaderValue<vector<short>>   hcalTPieta;
        TTreeReaderValue<vector<short>>   hcalTPiphi;
        TTreeReaderValue<vector<short>>   hcalTPCaliphi;
        TTreeReaderValue<vector<float>>   hcalTPet;
        TTreeReaderValue<vector<short>>   hcalTPcompEt;
        TTreeReaderValue<vector<short>>   hcalTPfineGrain;
        TTreeReaderValue<Short_t>         nECALTP;
        TTreeReaderValue<vector<short>>   ecalTPieta;
        TTreeReaderValue<vector<short>>   ecalTPiphi;
        TTreeReaderValue<vector<short>>   ecalTPCaliphi;
        TTreeReaderValue<vector<float>>   ecalTPet;
        TTreeReaderValue<vector<short>>   ecalTPcompEt;
        TTreeReaderValue<vector<short>>   ecalTPfineGrain;
        //L1Analysis::L1AnalysisL1CaloTowerDataFormat *L1CaloTower;
        TTreeReaderValue<Short_t>         nTower;
        //vector<short>   ieta;
        //vector<short>   iphi;
        //vector<short>   iet;
        TTreeReaderValue<vector<short>>   iem;
        TTreeReaderValue<vector<short>>   ihad;
        TTreeReaderValue<vector<short>>   iratio;
        //vector<short>   iqual;
        //vector<float>   et;
        //vector<float>   eta;
        //vector<float>   phi;
        //L1Analysis::L1AnalysisL1CaloClusterDataFormat *L1CaloCluster;
        TTreeReaderValue<Short_t>         nCluster;
        //vector<short>   ieta;
        //vector<short>   iphi;
        //vector<short>   iet;
        //vector<short>   iqual;
        //vector<float>   et;
        //vector<float>   eta;
        //vector<float>   phi;
};

void TL1CaloTowerClass::Fill()
{
    nHCALTP         = TTreeReaderValue<Short_t>      (*fReader, "nHCALTP");
    hcalTPieta      = TTreeReaderValue<vector<short>>(*fReader, "hcalTPieta");
    hcalTPiphi      = TTreeReaderValue<vector<short>>(*fReader, "hcalTPiphi");
    hcalTPCaliphi   = TTreeReaderValue<vector<short>>(*fReader, "hcalTPCaliphi");
    hcalTPet        = TTreeReaderValue<vector<float>>(*fReader, "hcalTPet");
    hcalTPcompEt    = TTreeReaderValue<vector<short>>(*fReader, "hcalTPcompEt");
    hcalTPfineGrain = TTreeReaderValue<vector<short>>(*fReader, "hcalTPfineGrain");
    nECALTP         = TTreeReaderValue<Short_t>      (*fReader, "nECALTP");
    ecalTPieta      = TTreeReaderValue<vector<short>>(*fReader, "ecalTPieta");
    ecalTPiphi      = TTreeReaderValue<vector<short>>(*fReader, "ecalTPiphi");
    ecalTPCaliphi   = TTreeReaderValue<vector<short>>(*fReader, "ecalTPCaliphi");
    ecalTPet        = TTreeReaderValue<vector<float>>(*fReader, "ecalTPet");
    ecalTPcompEt    = TTreeReaderValue<vector<short>>(*fReader, "ecalTPcompEt");
    ecalTPfineGrain = TTreeReaderValue<vector<short>>(*fReader, "ecalTPfineGrain");
    nTower          = TTreeReaderValue<Short_t>      (*fReader, "nTower");
    iem             = TTreeReaderValue<vector<short>>(*fReader, "iem");
    ihad            = TTreeReaderValue<vector<short>>(*fReader, "ihad");
    iratio          = TTreeReaderValue<vector<short>>(*fReader, "iratio");
    nCluster        = TTreeReaderValue<Short_t>      (*fReader, "nCluster");
}

#endif
