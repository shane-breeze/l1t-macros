#ifndef TL1DRAW_H
#define TL1DRAW_H

#include <iostream>

#include <TFile.h>
#include <TStyle.h>

#include "tdrstyle.C"

class TL1Draw
{
    public:
        TL1Draw(std::string & rootFilePath);
        ~TL1Draw();

        void Draw();
        virtual void DrawToCanvas(const std::string & name, const int & pos, const int & max) = 0;

        void SetSample(const std::string & sampleName, const std::string & sampleTitle);
        void SetTrigger(const std::string & triggerName, const std::string & triggerTitle);
        void SetRun(const std::string & run);
        void SetAddMark(const std::string & addMark);

        void SetOutName(const std::string & outName);
        void SetOutDir(const std::string & outDir);

        void SetMerges(const bool & mergePu, const bool & mergeSeeds, const bool & mergePuSeeds);

    protected:
        std::string GetSampleName() const;
        std::string GetTriggerName() const;
        std::string GetRun() const;
        std::string GetSampleTitle() const;
        std::string GetTriggerTitle() const;
        std::string GetAddMark() const;

        std::string GetOutName() const;
        std::string GetOutDir() const;

        bool GetMergePu() const;
        bool GetMergeSeeds() const;
        bool GetMergePuSeeds() const;

        TFile * GetRootFile();

    private:
        TFile * fRootFile;

        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        std::string fAddMark;

        std::string fOutName, fOutDir;

        bool fMergePu, fMergeSeeds, fMergePuSeeds;

        TStyle * fStyle;

};

TL1Draw::TL1Draw(std::string & rootFilePath) :
    fRootFile(new TFile(rootFilePath.c_str(),"READ")),
    fStyle(new TStyle(TDRStyle(55)))
{
    fStyle->cd();
}

TL1Draw::~TL1Draw()
{
    fRootFile->Close();
}

void TL1Draw::Draw()
{
    TList * keyList = (TList*)this->GetRootFile()->GetListOfKeys();
    std::vector<std::string> keyNames;
    std::set<std::string> puNames, seedNames;
    for(int i=0; i<keyList->GetEntries(); ++i)
    {
        std::string name = keyList->At(i)->GetName();
        keyNames.push_back(name);
        std::smatch puMatch;
        std::regex puExp("[0-9]+PU[0-9]*");
        std::regex_search(name,puMatch,puExp);
        puNames.insert(puMatch.str());

        std::smatch seedMatch;
        std::regex seedExp("_[0-9]+_");
        std::regex_search(name,seedMatch,seedExp);
        seedNames.insert(seedMatch.str());
    }

    if( this->GetMergePu() )
    {
        for(auto seedName: seedNames)
        {
            int pos(0);
            TCanvas * can(new TCanvas("c1","c1"));
            for(int i=0; i<keyList->GetEntries(); ++i)
            {
                std::string name = keyList->At(i)->GetName();
                std::regex exp("(divide_dist_)(.*)("+seedName+")(.*)(_by_dist_)(.*)(_0_)(.*)");
                if( !std::regex_match(name,exp) ) continue;
                cout << name << endl;
                this->DrawToCanvas(name,pos,puNames.size()-1);
                ++pos;
            }
            can->SaveAs(Form("temp1_%s.pdf",seedName.c_str()));
        }
    }

    if( this->GetMergeSeeds() )
    {
        for(auto puName: puNames)
        {
            int pos(0);
            TCanvas * can(new TCanvas("c2","c2"));
            for(int i=0; i<keyList->GetEntries(); ++i)
            {
                std::string name = keyList->At(i)->GetName();
                std::regex exp("(divide_dist_)(.*)(_"+puName+"_by_dist_)(.*)_0_"+puName);
                if( !std::regex_match(name,exp) ) continue;
                this->DrawToCanvas(name,pos,seedNames.size());
                ++pos;
            }
            can->SaveAs(Form("temp2_%s.pdf",puName.c_str()));
        }
    }

    if( this->GetMergePuSeeds() )
    {
        int pos(0);
        TCanvas * can(new TCanvas("c3","c3"));
        for(int i=0; i<keyList->GetEntries(); ++i)
        {
            std::string name = keyList->At(i)->GetName();
            std::regex exp("(divide_dist_)(.*)(_by_dist_)(.*)");
            if( !std::regex_match(name,exp) ) continue;
            this->DrawToCanvas(name,pos,puNames.size()*seedNames.size());
            ++pos;
        }
        can->SaveAs("temp3.pdf");
    }
}

void TL1Draw::SetSample(const std::string & sampleName, const std::string & sampleTitle)
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
}

void TL1Draw::SetTrigger(const std::string & triggerName, const std::string & triggerTitle)
{
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
}

void TL1Draw::SetRun(const std::string & run)
{
    fRun = run;
}

void TL1Draw::SetAddMark(const std::string & addMark)
{
    fAddMark = addMark;
}

void TL1Draw::SetOutName(const std::string & outName)
{
    fOutName = outName;
}

void TL1Draw::SetOutDir(const std::string & outDir)
{
    std::system(Form("mkdir -p %s",outDir.c_str()));
    fOutDir = outDir;
}

void TL1Draw::SetMerges(const bool & mergePu, const bool & mergeSeeds, const bool & mergePuSeeds)
{
    fMergePu = mergePu;
    fMergeSeeds = mergeSeeds;
    fMergePuSeeds = mergePuSeeds;
}

std::string TL1Draw::GetSampleName() const
{
    return fSampleName;
}

std::string TL1Draw::GetTriggerName() const
{
    return fTriggerName;
}

std::string TL1Draw::GetRun() const
{
    return fRun;
}

std::string TL1Draw::GetSampleTitle() const
{
    return fSampleTitle;
}

std::string TL1Draw::GetTriggerTitle() const
{
    return fTriggerTitle;
}

std::string TL1Draw::GetAddMark() const
{
    return fAddMark;
}

std::string TL1Draw::GetOutName() const
{
    return fOutName;
}

std::string TL1Draw::GetOutDir() const
{
    return fOutDir;
}

bool TL1Draw::GetMergePu() const
{
    return fMergePu;
}

bool TL1Draw::GetMergeSeeds() const
{
    return fMergeSeeds;
}

bool TL1Draw::GetMergePuSeeds() const
{
    return fMergePuSeeds;
}

TFile * TL1Draw::GetRootFile()
{
    return fRootFile;
}

#endif
