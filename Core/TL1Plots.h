#ifndef TL1TURNON_H
#define TL1TURNON_H

#include <string>
#include <memory>

#include <TStyle.h>

#include "Core/TL1EventClass.h"
#include "Core/tdrstyle.C"

class TL1Plots
{
    public:
        virtual void InitPlots() = 0;
        virtual void Fill(const double & xVal, const double & yVal) = 0;
        virtual void DrawPlots() = 0;

        virtual void SetSample(const std::string & sampleName, const std::string & sampleTitle);
        virtual void SetTrigger(const std::string & triggerName, const std::string & triggerTitle);
        virtual void SetRun(const std::string & run);
        virtual void SetOutName(const std::string & outName);
    protected:
        template<typename Type>
        std::vector<std::shared_ptr<Type>> fPlots;

        std::string fSampleName, fTriggerName, fRun;
        std::string fSampleTitle, fTriggerTitle;
        std::string fOutName;
};

void TL1Plots::SetSample(const std::string & sampleName, const std::string & sampleTitle)
{
    fSampleName = sampleName;
    fSampleTitle = sampleTitle;
}

void TL1Plots::SetTrigger(const std::string & triggerName, const std::string & triggerTitle)
{
    fTriggerName = triggerName;
    fTriggerTitle = triggerTitle;
}

void TL1Plots::SetRun(const std::string & run)
{
    fRun = run;
}

void TL1Plots::SetOutName(const std::string & outName)
{
    fOutName = outName;
}

void TL1Plots::SetColor(float fraction, int index)
{
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * (1.0-2.0*modifier) + modifier) * gStyle->GetNumberOfColors();
        colour = gStyle->GetColorPalette(colorIndex);
    }
    fPlots[index]->SetLineColor(colour);
    fPlots[index]->SetMarkerColor(colour);
}

#endif
