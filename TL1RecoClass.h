#ifndef TL1RECOCLASS
#define TL1RECOCLASS

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TL1DataClass.h"

#include "L1Trigger/L1TNtuples/interface/L1AnalysisRecoVertexDataFormat.h"

class TL1RecoClass : public TL1DataClass
{
    public:
        using TL1DataClass::TL1DataClass;
        void Fill();

        // Declaration of leaf types
        //L1Analysis::L1AnalysisRecoVertexDataFormat *Vertex;
        TTreeReaderValue<UInt_t>               nVtx;
        TTreeReaderValue<vector<unsigned int>> NDoF;
        TTreeReaderValue<vector<double>>       Z;
        TTreeReaderValue<vector<double>>       Rho;
};

void TL1RecoClass::Fill()
{
    nVtx = TTreeReaderValue<UInt_t>              (*fReader, "nVtx");
    NDoF = TTreeReaderValue<vector<unsigned int>>(*fReader, "NDoF");
    Z    = TTreeReaderValue<vector<double>>      (*fReader, "Z");
    Rho  = TTreeReaderValue<vector<double>>      (*fReader, "Rho");
}

#endif
