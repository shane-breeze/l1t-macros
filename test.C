#include "TL1EventClass.h"

#include "tdrstyle.C"

struct turnon
{
    std::string sampleName, triggerName, run;
    std::string sampleTitle, triggerTitle;
    vector<double> seeds, xBins, xyBins;
    double xVal, seedVal;
    double xPhi, seedPhi;
    std::string xValName, seedValName;
    std::string xValTitle, seedValTitle;
    std::string xPhiTitle, seedPhiTitle;
    std::string outName;
    bool doFit;
};

void setMyStyle(int palette, double rmarg, TStyle * myStyle);
void setColor(TH1F * hist, float fraction, TStyle * myStyle);
bool muonFilter(TL1EventClass * event, int iMu);
bool jetFilter(TL1EventClass * event, int iJet);
bool sumsFilter(TL1EventClass * event);
vector<double> metBins();
vector<double> mhtBins();
vector<double> ettBins();
vector<double> httBins();
vector<double> xyBins(double max);
vector<TH1F*> generateHists(turnon myTurnon, TStyle * myStyle);
TH2F generateXYs(turnon myTurnons, TStyle * myStyle, bool isPhi);
vector<TGraphAsymmErrors*> generateEffs(turnon myTurnon, vector<TH1F*> hists);
void fillDist(turnon myTurnon, vector<TH1F*> hists);
void fillXY(turnon myTurnon, TH2F * hist, bool isPhi);
void drawHists(turnon myTurnon, vector<TH1F*> hists, bool setLogy, bool setLogz, bool is2D, bool isPhi);
void drawHists(turnon myTurnon, TH2F * hists, bool setLogy, bool setLogz, bool is2D, bool isPhi);
TF1 fit(TGraphAsymmErrors * eff, int p50, bool doFit);

void test()
{
    std::shared_ptr<TStyle> myStyle(new TStyle(TDRStyle()));
    setMyStyle(55,0.07,myStyle.get());

    // std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160511_l1t-integration-v48p2/SingleMu/Ntuples";
    std::string inDir = "/afs/cern.ch/work/s/sbreeze/public/jets_and_sums/160519_l1t-integration-v53p1/SingleMu_273301/Ntuples";
    std::shared_ptr<TL1EventClass> event(new TL1EventClass(inDir));

    // Turnon structs:
    turnon caloMetBE_l1MetSeed, mht_l1Mht, ett_l1Ett, htt_l1Htt;

    caloMetBE_l1MetSeed.sampleName = "Data";
    caloMetBE_l1MetSeed.triggerName = "SingleMu";
    caloMetBE_l1MetSeed.run = "273301";
    caloMetBE_l1MetSeed.sampleTitle = "";
    caloMetBE_l1MetSeed.triggerTitle = "Single Muon";
    caloMetBE_l1MetSeed.doFit = true;

    mht_l1Mht.sampleName = "Data";
    mht_l1Mht.triggerName = "SingleMu";
    mht_l1Mht.run = "273301";
    mht_l1Mht.sampleTitle = "";
    mht_l1Mht.triggerTitle = "Single Muon";
    mht_l1Mht.doFit = true;

    ett_l1Ett.sampleName = "Data";
    ett_l1Ett.triggerName = "SingleMu";
    ett_l1Ett.run = "273301";
    ett_l1Ett.sampleTitle = "";
    ett_l1Ett.triggerTitle = "Single Muon";
    ett_l1Ett.doFit = true;

    htt_l1Htt.sampleName = "Data";
    htt_l1Htt.triggerName = "SingleMu";
    htt_l1Htt.run = "273301";
    htt_l1Htt.sampleTitle = "";
    htt_l1Htt.triggerTitle = "Single Muon";
    htt_l1Htt.doFit = true;

    caloMetBE_l1MetSeed.seeds = {0.,40.,50.,60.,70.,80.,90.,100.,120.};
    caloMetBE_l1MetSeed.xBins = metBins();
    caloMetBE_l1MetSeed.xValName = "caloMetBE";
    caloMetBE_l1MetSeed.seedValName = "l1MetSeed";
    caloMetBE_l1MetSeed.xValTitle = "Calo E_{T}^{miss} no HF (GeV)";
    caloMetBE_l1MetSeed.xPhiTitle = "Calo E_{T}^{miss} Phi (no HF)";
    caloMetBE_l1MetSeed.seedValTitle = "L1 MET";
    caloMetBE_l1MetSeed.seedPhiTitle = "L1 E_{T}^{miss} Phi";
    caloMetBE_l1MetSeed.outName = caloMetBE_l1MetSeed.triggerName+"_caloMetBE_l1MetSeeds_muonFilter.pdf";

    mht_l1Mht.seeds = {0.,50.,70.,100.,120.,130.,140.,150.};
    mht_l1Mht.xBins = mhtBins();
    mht_l1Mht.xValName = "mht";
    mht_l1Mht.seedValName = "l1Mht";
    mht_l1Mht.xValTitle = "H_{T}^{miss} (GeV)";
    mht_l1Mht.xPhiTitle = "H_{T}^{miss} Phi";
    mht_l1Mht.seedValTitle = "L1 MHT";
    mht_l1Mht.seedPhiTitle = "L1 H_{T}^{miss} Phi";
    mht_l1Mht.outName = mht_l1Mht.triggerName+"_mht_l1MhtSeeds_recalcMht.pdf";

    ett_l1Ett.seeds = {0.,40.,60.};
    ett_l1Ett.xBins = ettBins();
    ett_l1Ett.xValName = "caloEttBE";
    ett_l1Ett.seedValName = "l1ett";
    ett_l1Ett.xValTitle = "Total Calo E_{T} no HF (GeV)";
    ett_l1Ett.xPhiTitle = "Total Calo E_{T} Phi (no HF)";
    ett_l1Ett.seedValTitle = "L1 ETT";
    ett_l1Ett.seedPhiTitle = "L1 Total E_{T} Phi";
    ett_l1Ett.outName = ett_l1Ett.triggerName+"_caloEttBE_l1EttSeeds.pdf";

    htt_l1Htt.seeds = {0.,120.,160.,200.,240.,270.,280.,300.,320.};
    htt_l1Htt.xBins = httBins();
    htt_l1Htt.xValName = "htt";
    htt_l1Htt.seedValName = "l1htt";
    htt_l1Htt.xValTitle = "Total H_{T} (GeV)";
    htt_l1Htt.xPhiTitle = "Total H_{T} Phi";
    htt_l1Htt.seedValTitle = "L1 HTT";
    htt_l1Htt.seedPhiTitle = "L1 Total H_{T} Phi";
    htt_l1Htt.outName = htt_l1Htt.triggerName+"_htt_l1HttSeeds.pdf";

    caloMetBE_l1MetSeed.xyBins = xyBins(200.0);
    mht_l1Mht.xyBins = xyBins(200.0);
    ett_l1Ett.xyBins = xyBins(600.0);
    htt_l1Htt.xyBins = xyBins(400.0);

    std::vector<TH1F*> metDists = generateHists(caloMetBE_l1MetSeed, myStyle.get());
    std::vector<TH1F*> mhtDists = generateHists(mht_l1Mht, myStyle.get());
    std::vector<TH1F*> ettDists = generateHists(ett_l1Ett, myStyle.get());
    std::vector<TH1F*> httDists = generateHists(htt_l1Htt, myStyle.get());

    std::shared_ptr<TH2F> xyCaloMetBE_l1Met(new TH2F(generateXYs(caloMetBE_l1MetSeed, myStyle.get(), false)));
    std::shared_ptr<TH2F> xyCaloMetBEPhi_l1MetPhi(new TH2F(generateXYs(caloMetBE_l1MetSeed, myStyle.get(), true)));

    std::shared_ptr<TH2F> xyMht_l1Mht(new TH2F(generateXYs(mht_l1Mht, myStyle.get(), false)));
    std::shared_ptr<TH2F> xyMhtPhi_l1MhtPhi(new TH2F(generateXYs(mht_l1Mht, myStyle.get(), true)));

    std::shared_ptr<TH2F> xyCaloEttBE_l1Ett(new TH2F(generateXYs(ett_l1Ett, myStyle.get(), false)));
    std::shared_ptr<TH2F> xyHtt_l1Htt(new TH2F(generateXYs(htt_l1Htt, myStyle.get(), false)));

    while( event->Next() )
    {
        // Muon loop
        bool passMuonFilter = false;
        for(int iMu=0; iMu<event->fMuons->nMuons; ++iMu)
            if( muonFilter(event.get(), iMu) )
                passMuonFilter = true;

        // Jet loop
        double jetEx(0.0), jetEy(0.0), jetEt(0.0);
        for(int iJet=0; iJet<event->fJets->nJets; ++iJet)
        {
            bool passJetFilter = jetFilter(event.get(), iJet);
            if( passJetFilter )
            {
                jetEx += event->fJets->et[iJet]*TMath::Cos(event->fJets->phi[iJet]);
                jetEy += event->fJets->et[iJet]*TMath::Sin(event->fJets->phi[iJet]);
                jetEt += event->fJets->et[iJet];
            }
        }
        double recalcMht = sqrt(jetEx*jetEx + jetEy*jetEy);
        double recalcMhtPhi = TMath::ATan(jetEy/jetEx);
        double recalcHtt = jetEt;
            

        // Sums
        bool passSumsFilter = sumsFilter(event.get());

        // Get l1 variables
        double l1met, l1mht, l1ett, l1htt, l1metPhi, l1mhtPhi;
        for(int iter=0; iter<event->fUpgrade->nSums; ++iter)
        {
            double et = event->fUpgrade->sumEt[iter];
            double phi = event->fUpgrade->sumPhi[iter];
            if (event->fUpgrade->sumBx[iter] == 0 )
            {
                if (event->fUpgrade->sumType[iter] == L1Analysis::kTotalEt)   l1ett = et;
                if (event->fUpgrade->sumType[iter] == L1Analysis::kTotalHt)   l1htt = et;
                if (event->fUpgrade->sumType[iter] == L1Analysis::kMissingEt)
                {
                    l1met = et;
                    l1metPhi = phi;
                }
                if (event->fUpgrade->sumType[iter] == L1Analysis::kMissingHt)
                {
                    l1mht = et;
                    l1mhtPhi = phi;
                }
            }
        }

        if( !passMuonFilter ) continue;
        
        if( passSumsFilter )
        {
            caloMetBE_l1MetSeed.xVal = event->fSums->caloMetBE;
            caloMetBE_l1MetSeed.seedVal = l1met;
            caloMetBE_l1MetSeed.xPhi = event->fSums->caloMetPhiBE;
            caloMetBE_l1MetSeed.seedPhi = l1metPhi;
            fillDist(caloMetBE_l1MetSeed, metDists);
            fillXY(caloMetBE_l1MetSeed, xyCaloMetBE_l1Met.get(), false);
            fillXY(caloMetBE_l1MetSeed, xyCaloMetBEPhi_l1MetPhi.get(), true);
        }

        mht_l1Mht.xVal = event->fSums->mHt;
        //mht_l1Mht.xVal = recalcMht;
        mht_l1Mht.seedVal = l1mht;
        //mht_l1Mht.xPhi = event->fSums->mHtPhi;
        mht_l1Mht.xPhi = recalcMhtPhi;
        mht_l1Mht.seedPhi = l1mhtPhi;
        fillDist(mht_l1Mht, mhtDists);
        fillXY(mht_l1Mht, xyMht_l1Mht.get(), false);
        fillXY(mht_l1Mht, xyMhtPhi_l1MhtPhi.get(), true);
        
        ett_l1Ett.xVal = event->fSums->caloSumEtBE;
        ett_l1Ett.seedVal = l1ett;
        fillDist(ett_l1Ett, ettDists);
        fillXY(ett_l1Ett, xyCaloEttBE_l1Ett.get(), false);

        //htt_l1Htt.xVal = event->fSums->Ht;
        htt_l1Htt.xVal = recalcHtt;
        htt_l1Htt.seedVal = l1htt;
        fillDist(htt_l1Htt, httDists);
        fillXY(htt_l1Htt, xyHtt_l1Htt.get(), false);
    }

    drawHists(caloMetBE_l1MetSeed, metDists, true, false, false, false);
    drawHists(mht_l1Mht, mhtDists, true, false, false, false);
    drawHists(ett_l1Ett, ettDists, true, false, false, false);
    drawHists(htt_l1Htt, httDists, true, false, false, false);
    
    // Divide and conquer:
    std::vector<TGraphAsymmErrors*> metEffs = generateEffs(caloMetBE_l1MetSeed, metDists);
    std::vector<TGraphAsymmErrors*> mhtEffs = generateEffs(mht_l1Mht, mhtDists);
    std::vector<TGraphAsymmErrors*> ettEffs = generateEffs(ett_l1Ett, ettDists);
    std::vector<TGraphAsymmErrors*> httEffs = generateEffs(htt_l1Htt, httDists);

    setMyStyle(57,0.13,myStyle.get());
    drawHists(caloMetBE_l1MetSeed, xyCaloMetBE_l1Met.get(), false, true, true, false);
    drawHists(mht_l1Mht, xyMht_l1Mht.get(), false, true, true, false);
    drawHists(ett_l1Ett, xyCaloEttBE_l1Ett.get(), false, true, true, false);
    drawHists(htt_l1Htt, xyHtt_l1Htt.get(), false, true, true, false);

    drawHists(caloMetBE_l1MetSeed, xyCaloMetBEPhi_l1MetPhi.get(), false, true, true, true);
    drawHists(mht_l1Mht, xyMhtPhi_l1MhtPhi.get(), false, true, true, true);
}

void setMyStyle(int palette, double rmarg, TStyle * myStyle)
{
    myStyle->SetCanvasDefW(800);
    myStyle->SetNumberContours(255);
    myStyle->SetPalette(palette);
    myStyle->SetPadRightMargin(rmarg);
    myStyle->cd();
}

void setColor(TH1F * hist, float fraction, TStyle * myStyle)
{
    double modifier(0.15), colorIndex;
    int colour(1);
    if( fraction >= 0.0 )
    {
        colorIndex = (fraction * ( 1.0 - 2.0*modifier ) + modifier ) * myStyle->GetNumberOfColors();
        colour = myStyle->GetColorPalette(colorIndex);
    }
    hist->SetLineColor(colour);
    hist->SetMarkerColor(colour);
}

void drawCmsStamp(bool isEfficiency, bool is2D, turnon myTurnon, bool isPhi)
{
    std::shared_ptr<TLatex> latex(new TLatex());  
    latex->SetNDC();
    latex->SetTextFont(42);

    double min = myTurnon.xBins.front();
    double max = myTurnon.xBins.back();
    if( is2D )
    {
        min = myTurnon.xyBins.front();
        max = myTurnon.xyBins.back();
    }

    if( isEfficiency ) // Efficiency plots
    {
        std::shared_ptr<TLine> line(new TLine(min, 1., max, 1.));
        line->SetLineStyle(7);
        line->DrawClone();
        if( myTurnon.sampleName == "Data" )
        {
            latex->DrawLatex(0.17, 0.84, "#bf{CMS}");
            latex->DrawLatex(0.17, 0.79, "#it{Preliminary}");
            
            latex->SetTextAlign(32);
            latex->SetTextAlign(31); 
            std::string runNo = "run " + myTurnon.run + ", ";
            latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),myTurnon.triggerName.c_str()));
        }
        else
        {
            latex->DrawLatex(0.17, 0.80, "#bf{CMS}");
            latex->DrawLatex(0.17, 0.75, "#it{Simulation}");
            latex->DrawLatex(0.17, 0.70, "#it{Preliminary}");
            latex->SetTextAlign(32);
            latex->SetTextAlign(31); 
            latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",myTurnon.sampleTitle.c_str()));
        }
    }
    else if( !is2D ) // Dist plots for efficiency
    {
        if( myTurnon.sampleName == "Data" )
        {
            latex->SetTextAlign(32);
            latex->DrawLatex(0.89, 0.85, "#bf{CMS}");
            latex->DrawLatex(0.89, 0.80, "#it{Preliminary}");
            latex->SetTextAlign(31); 
            std::string runNo = "run " + myTurnon.run + ", ";
            latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),myTurnon.triggerName.c_str()));
        }
        else
        {
            latex->SetTextAlign(32);
            latex->DrawLatex(0.89, 0.85, "#bf{CMS}");
            latex->DrawLatex(0.89, 0.80, "#it{Simulation}");
            latex->DrawLatex(0.89, 0.75, "#it{Preliminary}");
            latex->SetTextAlign(31); 
            latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",myTurnon.sampleTitle.c_str()));
        }
    }
    else // 2D plots
    {
        std::shared_ptr<TLine> line(new TLine(min, min, max, max));
        line->SetLineWidth(3);
        line->SetLineStyle(9);
        if( isPhi ) line->DrawLine(-TMath::Pi(),-TMath::Pi(),TMath::Pi(),TMath::Pi());
        else line->DrawClone();
        if( myTurnon.sampleName == "Data" )
        {
            latex->SetTextAlign(31); 
            std::string runNo = "run " + myTurnon.run + ", ";
            latex->DrawLatex(0.92, 0.92, Form("%s%s, #sqrt{s} = 13 TeV",runNo.c_str(),myTurnon.triggerName.c_str()));
        }
        else
        {
            latex->SetTextAlign(31); 
            latex->DrawLatex(0.92, 0.92, Form("%s, #sqrt{s} = 13 TeV",myTurnon.sampleTitle.c_str()));
        }
    }
}

bool muonFilter(TL1EventClass * event, int iMu)
{
    double pt = event->fMuons->pt[iMu];
    double iso = event->fMuons->iso[iMu];
    double isLoose = event->fMuons->isLooseMuon[iMu];
    int nMuons = event->fMuons->nMuons;

    return (pt>=20.0 && iso<=0.1 && isLoose==1.0 && nMuons>=1);
}

bool jetFilter(TL1EventClass * event, int iJet)
{
    double eta = event->fJets->eta[iJet];
    double nhef = event->fJets->nhef[iJet];
    double pef = event->fJets->pef[iJet];
    double mef = event->fJets->mef[iJet];
    double chef = event->fJets->chef[iJet];
    double eef = event->fJets->eef[iJet];
    int chMult = event->fJets->chMult[iJet];
    int nhMult = event->fJets->nhMult[iJet];
    int phMult = event->fJets->phMult[iJet];
    int elMult = event->fJets->elMult[iJet];
    int muMult = event->fJets->muMult[iJet];
    bool jetPass;
    if (abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8 
            && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
        jetPass = true;}//this jet has passed
    else{jetPass = false;}//this jet has failed, or is outside the central zone           
    return (jetPass && muMult==0);
}

bool sumsFilter(TL1EventClass * event)
{
    return event->fMetFilters->hbheNoiseFilter;
}

vector<double> metBins()
{
    vector<double> temp;
    for(double binLowerEdge=-20.0; binLowerEdge<  0.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=  0.0; binLowerEdge< 40.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 40.0; binLowerEdge< 70.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 70.0; binLowerEdge<200.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge=100.0; binLowerEdge<200.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge<300.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge=250.0; binLowerEdge<300.1; binLowerEdge+=50.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> mhtBins()
{
    vector<double> temp;
    //for(double binLowerEdge=-30.0; binLowerEdge<  0.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=  0.0; binLowerEdge< 50.0; binLowerEdge+= 1.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge= 25.0; binLowerEdge< 50.0; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 50.0; binLowerEdge< 80.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 80.0; binLowerEdge<140.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=140.0; binLowerEdge<200.0; binLowerEdge+=15.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=200.0; binLowerEdge<300.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=300.0; binLowerEdge<400.1; binLowerEdge+=50.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> ettBins()
{
    vector<double> temp;
    //for(double binLowerEdge=-30.0; binLowerEdge<  0.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=  0.0; binLowerEdge< 30.0; binLowerEdge+=30.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 30.0; binLowerEdge< 50.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 50.0; binLowerEdge< 90.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge= 90.0; binLowerEdge<140.1; binLowerEdge+= 2.0) temp.push_back(binLowerEdge);
    //for(double binLowerEdge=100.0; binLowerEdge<700.1; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    return temp;
}

vector<double> httBins()
{
    vector<double> temp;
    for(double binLowerEdge=  0.0; binLowerEdge<100.0; binLowerEdge+= 5.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=100.0; binLowerEdge<250.0; binLowerEdge+=10.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=250.0; binLowerEdge<600.0; binLowerEdge+=20.0) temp.push_back(binLowerEdge);
    for(double binLowerEdge=600.0; binLowerEdge<800.1; binLowerEdge+=50.0) temp.push_back(binLowerEdge);
    return temp;

}

vector<double> xyBins(double max)
{
    vector<double> temp;
    for(double edge=0.0; edge<=max; edge+=1.0) temp.push_back(edge);
    return temp;
}

vector<TH1F*> generateHists(turnon myTurnons, TStyle * myStyle)
{
    vector<TH1F*> temp;
    for(int i=0; i<myTurnons.seeds.size(); ++i)
    {
        temp.emplace_back(new TH1F(Form("dist_%s_%s_%g",myTurnons.xValName.c_str(),myTurnons.seedValName.c_str(),myTurnons.seeds[i]),"", myTurnons.xBins.size()-1,&(myTurnons.xBins)[0]));
        temp[i]->GetXaxis()->SetTitle(myTurnons.xValTitle.c_str());
        temp[i]->GetYaxis()->SetTitle("Number of Entries");
        setColor(temp[i], (double)(i-1)/(double)(myTurnons.seeds.size()-2), myStyle);
    }
    return temp;
}

TH2F generateXYs(turnon myTurnons, TStyle * myStyle, bool isPhi)
{
    std::vector<double> bins;
    std::string xTitle = myTurnons.xValTitle;
    std::string yTitle = myTurnons.seedValTitle;
    if( isPhi )
    {
        for(double phi=-2*TMath::Pi(); phi<=2*TMath::Pi(); phi+=TMath::Pi()/36.0) bins.push_back(phi);
        xTitle = myTurnons.xPhiTitle;
        yTitle = myTurnons.seedPhiTitle;
    }
    else
    {
        bins = myTurnons.xyBins;
    }
    TH2F temp(Form("xy_%sPhi_vs_%sPhi",myTurnons.xValName.c_str(),myTurnons.seedValName.c_str()), "", bins.size()-1, &(bins)[0], bins.size()-1, &(bins)[0]);
    temp.GetXaxis()->SetTitle(xTitle.c_str());
    temp.GetYaxis()->SetTitle(yTitle.c_str());
    return temp;
}

vector<TGraphAsymmErrors*> generateEffs(turnon myTurnon, vector<TH1F*> hists)
{
    vector<TGraphAsymmErrors*> temp;
    vector<TF1*> fits;
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1"));
    std::shared_ptr<TLegend> leg(new TLegend(0.62,0.15,0.87,0.15+0.2*myTurnon.seeds.size()/5.0));
    for(int i=1; i<myTurnon.seeds.size(); ++i)
    {
        temp.emplace_back(new TGraphAsymmErrors(hists[i], hists[0]));
        temp[i-1]->SetLineColor(hists[i]->GetLineColor());
        temp[i-1]->SetMarkerColor(hists[i]->GetMarkerColor());
        temp[i-1]->GetXaxis()->SetTitle(hists[i]->GetXaxis()->GetTitle());
        temp[i-1]->GetXaxis()->SetLimits(myTurnon.xBins.front(), myTurnon.xBins.back());
        temp[i-1]->GetYaxis()->SetTitle("Efficiency");
        if( i == 1 ) temp[i-1]->Draw("ap");
        else temp[i-1]->Draw("psame");
        fits.emplace_back(new TF1(fit(temp[i-1], myTurnon.seeds[i], myTurnon.doFit)));
        if( myTurnon.doFit ) fits[i-1]->Draw("lsame");
        leg->AddEntry(temp[i-1], Form("%s > %g",myTurnon.seedValTitle.c_str(),myTurnon.seeds[i]));
    }
    drawCmsStamp(true, false, myTurnon, false);
    leg->Draw();
    can->SaveAs(Form("effs_%s",myTurnon.outName.c_str()));

    return temp;
}

void fillDist(turnon myTurnon, vector<TH1F*> hists)
{
    for(int i=0; i<hists.size(); ++i)
        if( myTurnon.seedVal >= myTurnon.seeds[i] )
            hists[i]->Fill(myTurnon.xVal);
}

void fillXY(turnon myTurnon, TH2F * hist, bool isPhi)
{
    if( isPhi ) hist->Fill(myTurnon.xPhi, myTurnon.seedPhi);
    else hist->Fill(myTurnon.xVal, myTurnon.seedVal);
}

void drawHists(turnon myTurnon, vector<TH1F*> hists, bool setLogy, bool setLogz, bool is2D, bool isPhi)
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1"));
    std::shared_ptr<TLegend> leg(new TLegend(0.55,0.35,0.85,0.55));
    for(int i=0; i<hists.size(); ++i)
    {
        if( i == 0 ) hists[i]->Draw();
        else hists[i]->Draw("same");
        leg->AddEntry(hists[i], Form("%s > %g GeV", myTurnon.seedValTitle.c_str(), myTurnon.seeds[i]));
    }
    if( setLogy ) can->SetLogy();
    if( setLogz ) can->SetLogz();
    drawCmsStamp(false,is2D,myTurnon,isPhi);
    if( !is2D ) leg->Draw();

    std::string outName;
    if( isPhi ) outName = Form("xyPhi_%s",myTurnon.outName.c_str());
    else if( is2D ) outName = Form("xy_%s",myTurnon.outName.c_str());
    else outName = Form("dists_%s",myTurnon.outName.c_str());
    can->SaveAs(outName.c_str());
}

void drawHists(turnon myTurnon, TH2F * hists, bool setLogy, bool setLogz, bool is2D, bool isPhi)
{
    std::shared_ptr<TCanvas> can(new TCanvas("c1","c1"));
    
    hists->Draw("colz");
    hists->SetMinimum(1.0);

    if( setLogy ) can->SetLogy();
    if( setLogz ) can->SetLogz();
    drawCmsStamp(false,is2D,myTurnon,false);

    std::string outName;
    if( isPhi ) outName = Form("xyPhi_%s",myTurnon.outName.c_str());
    else if( is2D ) outName = Form("xy_%s",myTurnon.outName.c_str());
    else outName = Form("dists_%s",myTurnon.outName.c_str());
    can->SaveAs(outName.c_str());
}

TF1 fit(TGraphAsymmErrors * eff, int p50, bool doFit)
{
    TF1 fitFcn( "fit_fcn","[0]*0.5*(1+TMath::Erf((x-[1])/(sqrt([2]))))",0,500); 
    if( doFit )
    {
        fitFcn.SetParameters( 0.937871,(double)p50,1378.23);
        TFitResultPtr fitRes_p = (TFitResultPtr)eff->Fit(fitFcn.GetName(),"ES0"); 
        TFitResult* fitRes = (TFitResult*)fitRes_p.Get();

        fitFcn.SetLineColor(eff->GetLineColor());
    }

    return fitFcn;
}
