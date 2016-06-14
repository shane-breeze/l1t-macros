#ifndef TL1PLOTS_H
#define TL1PLOTS_H

#include <string>
#include <stdlib.h>

class TL1Plots
{
    public:
        virtual void InitPlots() = 0;
        virtual void Fill(const double & xVal, const double & yVal, const int & pu) = 0;
        virtual void DrawPlots() = 0;

        virtual void SetOutName(const std::string & outName);
        virtual void SetOutDir(const std::string & outDir);
        virtual void SetPuType(const std::vector<std::string> & puType);
        virtual void SetPuBins(const std::vector<int> & puBins);

    protected:
        std::string GetOutName() const;
        std::string GetOutDir() const;
        std::vector<std::string> GetPuType() const;
        std::vector<int> GetPuBins() const;

    private:
        std::string fOutName, fOutDir;
        std::vector<std::string> fPuType;
        std::vector<int> fPuBins;

};

void TL1Plots::SetOutName(const std::string & outName)
{
    fOutName = outName;
}

void TL1Plots::SetOutDir(const std::string & outDir)
{
    std::system(Form("mkdir -p %s",outDir.c_str()));
    fOutDir = outDir;
}

void TL1Plots::SetPuType(const std::vector<std::string> & puType)
{
    fPuType = puType;
}

void TL1Plots::SetPuBins(const std::vector<int> & puBins)
{
    fPuBins = puBins;
}

std::string TL1Plots::GetOutName() const
{
    return fOutName;
}

std::string TL1Plots::GetOutDir() const
{
    return fOutDir;
}

std::vector<std::string> TL1Plots::GetPuType() const
{
    return fPuType;
}

std::vector<int> TL1Plots::GetPuBins() const
{
    return fPuBins;
}

#endif
