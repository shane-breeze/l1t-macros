#ifndef TL1DRAWRESOLUTION_H
#define TL1DRAWRESOLUTION_H

#include <string>
#include <regex>

#include <TGraphAsymmErrors.h>
#include <TStyle.h>

#include "TL1Draw.h"

class TL1DrawTurnon : public TL1Draw
{
    public:
        TL1DrawTurnon(std::string & rootFilePath);
        
        virtual void DrawToCanvas(const std::string & name, const int & pos, const int & max);

    private:
        void SetColor(TGraphAsymmErrors * graph, const int & pos, const int & max);

};

TL1DrawTurnon::TL1DrawTurnon(std::string & rootFilePath) :
    TL1Draw(rootFilePath)
{
}

void TL1DrawTurnon::DrawToCanvas(const std::string & name, const int & pos, const int & max)
{
    TGraphAsymmErrors * graph = (TGraphAsymmErrors*)this->GetRootFile()->Get(name.c_str()); 

    SetColor(graph, pos, max);
    if( pos == 0 ) graph->Draw("ap");
    else graph->Draw("psame");
}

void TL1DrawTurnon::SetColor(TGraphAsymmErrors * graph, const int & pos, const int & max)
{
    double fraction( (double)(pos)/(double)(max-1) );
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * (1.0-2.0*modifier) + modifier) * gStyle->GetNumberOfColors();
        colour = gStyle->GetColorPalette((int)colorIndex);
    }
    graph->SetLineColor(colour);
    graph->SetMarkerColor(colour);
}

#endif
