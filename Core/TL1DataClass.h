#ifndef TL1DATACLASS_H
#define TL1DATACLASS_H

#include <string>

#include <TROOT.h>
#include <TChain.h>

class TL1DataClass
{
    public:
        TL1DataClass(std::string chainPath, std::string inDir);

        Long64_t GetEntries();
        Long64_t LoadTree(int iEntry);
        Long64_t GetEntry(int iEntry);
        int GetNFiles() const;
        void SetBranchAddress(std::string leaf, void * add);
        
    private:
        TChain * fChain;
        int fNFiles;   

};

TL1DataClass::TL1DataClass(std::string chainPath, std::string inDir) :
    fChain(new TChain(chainPath.c_str()))
{
     fNFiles = fChain->Add( Form("%s/*.root",inDir.c_str()), -1);
}

Long64_t TL1DataClass::GetEntries()
{
    return fChain->GetEntries();
}

Long64_t TL1DataClass::LoadTree(int iEntry)
{
    return fChain->LoadTree(iEntry);
}

Long64_t TL1DataClass::GetEntry(int iEntry)
{
    return fChain->GetEntry(iEntry);
}

int TL1DataClass::GetNFiles() const
{
    return fNFiles;
}

void TL1DataClass::SetBranchAddress(std::string leaf, void * add)
{
    fChain->SetBranchAddress(leaf.c_str(), add);
}


#endif
