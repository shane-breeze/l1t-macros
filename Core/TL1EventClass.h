#ifndef TL1EVENTCLASS_H
#define TL1EVENTCLASS_H

#include <string>
#include <memory>
#include <vector>

#include <TMath.h>
#include <TVector2.h>

#include "TL1PrimitiveEventClass.h"
#include "TL1JetMatch.h"

class TL1EventClass
{
    public:
        TL1EventClass(std::string inDir);

        bool Next();
        void GetEntry(int i);
        void GetDerivatives();

        TL1PrimitiveEventClass const * GetPEvent() const;

        // Get L1
        double fL1Met, fL1Mht, fL1Ett, fL1Htt, fL1MetPhi, fL1MhtPhi;
        std::vector<double> fL1JetEt, fL1JetPhi, fL1JetEta;

        // Filter flags
        bool fMuonFilterPassFlag, fMetFilterPassFlag;
        std::vector<bool> fJetFilterPassFlags;

        // Recalc L1 Ht/Et Sums
        double fRecalcL1Mht, fRecalcL1MhtPhi;
        int fNJetL1Mht;
        double fRecalcL1Ett;

        // Recalc Reco Ht/Et Sums
        double fRecalcRecoMht, fRecalcRecoMhtPhi, fRecalcRecoHtt;
        int fNJetRecoMht;
        bool fMhtPassFlag;
        double fRecalcRecoEtt;

        // L1 and Reco Jet Matching
        bool GetMatchedJet(TL1JetMatch * jetMatch);

    private:
        std::shared_ptr<TL1PrimitiveEventClass> fPrimitiveEvent;

        // Get L1
        void GetL1Jets();
        void GetL1Sums();

        // Filters
        void MuonFilter();
        void JetFilter();
        void SumsFilter();

        // Recalc L1 Ht/Et Sums
        void GetRecalcL1Mht();
        void GetRecalcL1Ett();

        // Recalc Reco Ht/Et Sums
        void GetRecalcRecoHtSums();
        void GetRecalcRecoEtt();

};

TL1EventClass::TL1EventClass(std::string inDir) :
    fPrimitiveEvent(new TL1PrimitiveEventClass(inDir)),
    fMuonFilterPassFlag(true), fMetFilterPassFlag(true),
    fMhtPassFlag(true)
{
}

bool TL1EventClass::Next()
{
    bool isNext = fPrimitiveEvent->Next();
    this->GetDerivatives();
    return isNext;
}

void TL1EventClass::GetEntry(int i)
{
    fPrimitiveEvent->GetEntry(i);
    this->GetDerivatives();
}

void TL1EventClass::GetDerivatives()
{
    // L1
    this->GetL1Jets();
    this->GetL1Sums();

    // Filter
    this->MuonFilter();
    this->JetFilter();
    this->SumsFilter();

    // Recalc
    this->GetRecalcL1Mht();
    this->GetRecalcL1Ett();
    
    this->GetRecalcRecoHtSums();
    this->GetRecalcRecoEtt();
}

TL1PrimitiveEventClass const * TL1EventClass::GetPEvent() const
{
    return fPrimitiveEvent.get();
}

void TL1EventClass::GetL1Jets()
{
    fL1JetEt.clear();
    fL1JetEta.clear();
    fL1JetPhi.clear();
    for(unsigned iJet=0; iJet<fPrimitiveEvent->fUpgrade->nJets; ++iJet)
    {
        if( fPrimitiveEvent->fUpgrade->jetBx[iJet] == 0 )
        {
            fL1JetEt.push_back(fPrimitiveEvent->fUpgrade->jetEt[iJet]);
            fL1JetEta.push_back(fPrimitiveEvent->fUpgrade->jetEta[iJet]);
            fL1JetPhi.push_back(fPrimitiveEvent->fUpgrade->jetPhi[iJet]);
        }
    }
}

void TL1EventClass::GetL1Sums()
{
    std::shared_ptr<L1Analysis::L1AnalysisL1UpgradeDataFormat> upgrades = fPrimitiveEvent->fUpgrade;
    for(int iter=0; iter<upgrades->nSums; ++iter)
    {
        double et = upgrades->sumEt[iter];
        double phi = upgrades->sumPhi[iter];
        if( upgrades->sumBx[iter] == 0 )
        {
            short int sumType = upgrades->sumType[iter];
            if(sumType == L1Analysis::kTotalEt)   fL1Ett = et;
            if(sumType == L1Analysis::kTotalHt)   fL1Htt = et;
            if(sumType == L1Analysis::kMissingEt)
            {
                fL1Met = et;
                fL1MetPhi = phi;
            }
            if(sumType == L1Analysis::kMissingHt)
            {
                fL1Mht = et;
                fL1MhtPhi = phi;
            }
        }
    }
}

void TL1EventClass::MuonFilter()
{
    bool pass(false);
    for(unsigned jMuon=0; jMuon<fPrimitiveEvent->fMuons->nMuons; ++jMuon)
    {
        double pt = fPrimitiveEvent->fMuons->pt[jMuon];
        double iso = fPrimitiveEvent->fMuons->iso[jMuon];
        double isLoose = fPrimitiveEvent->fMuons->isLooseMuon[jMuon];
        if( pt>=20.0 && iso<=0.1 && isLoose==1.0 )
            pass = true;
    }
    fMuonFilterPassFlag = pass;
}

void TL1EventClass::JetFilter()
{
    for(unsigned iJet=0; iJet<fPrimitiveEvent->fJets->nJets; ++iJet)
    {
        std::shared_ptr<L1Analysis::L1AnalysisRecoJetDataFormat> recoJets = fPrimitiveEvent->fJets;

        double eta  = fPrimitiveEvent->fJets->eta[iJet];
        double nhef = fPrimitiveEvent->fJets->nhef[iJet];
        double pef  = fPrimitiveEvent->fJets->pef[iJet];
        double mef  = fPrimitiveEvent->fJets->mef[iJet];
        double chef = fPrimitiveEvent->fJets->chef[iJet];
        double eef  = fPrimitiveEvent->fJets->eef[iJet];
        int chMult  = fPrimitiveEvent->fJets->chMult[iJet];
        int nhMult  = fPrimitiveEvent->fJets->nhMult[iJet];
        int phMult  = fPrimitiveEvent->fJets->phMult[iJet];
        int elMult  = fPrimitiveEvent->fJets->elMult[iJet];
        int muMult  = fPrimitiveEvent->fJets->muMult[iJet];
        bool jetPass;
        if (abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8 
                && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90))){
            jetPass = true;}//this jet has passed
        else{jetPass = false;}//this jet has failed, or is outside the central zone           
        fJetFilterPassFlags.push_back(jetPass && muMult==0);
    }


//        // Muon mult filter
        //int muMult  = recoJets->muMult[iJet];
//        if( muMult != 0 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // No hf jets
//        double eta  = recoJets->eta[iJet];
//        if( TMath::Abs(eta) > 3. )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // nhef
//        double nhef = recoJets->nhef[iJet];
//        if( nhef >= 0.9 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // pef
//        double pef  = recoJets->pef[iJet];
//        if( pef >= 0.9 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // mef
//        double mef  = recoJets->mef[iJet];
//        if( mef >= 0.8 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // sumMult
//        //int sumMult = recoJets->chMult[iJet];
//        int chMult = recoJets->chMult[iJet];
//        int elMult = recoJets->elMult[iJet];
//        int muMult = recoJets->muMult[iJet];
//        int nhMult  = recoJets->nhMult[iJet];
//        int phMult  = recoJets->phMult[iJet];
//        if( sumMult+nhMult+phMult <= 1 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        if( TMath::Abs(eta)>2.4 )
//        {
//            fJetFilterPassFlags.push_back(true);
//            continue;
//        }
//
//        // sumMult
//        if( sumMult <= 0 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // chef
//        double chef = recoJets->chef[iJet];
//        if( chef <= 0 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // eef
//        double eef  = recoJets->eef[iJet];
//        if( eef >= 0.9 )
//        {
//            fJetFilterPassFlags.push_back(false);
//            continue;
//        }
//
//        // pass
//        fJetFilterPassFlags.push_back(true);
//
//        if (abs(eta)<=3.00 && nhef<0.90 && pef<0.90 && (chMult+nhMult+phMult+elMult+muMult)>1 && mef<0.8 && (abs(eta)>2.4||(abs(eta)<=2.4 && chef>0 && (chMult+elMult+muMult)>0 && eef<0.90)))
//        {
//             if( muMult == 0 ) fJetFilterPassFlags.push_back(true);
//             else fJetFilterPassFlags.push_back(false);
//        }
//    }
}

void TL1EventClass::SumsFilter()
{
    fMetFilterPassFlag = fPrimitiveEvent->fMetFilters->hbheNoiseFilter;
}

void TL1EventClass::GetRecalcL1Mht()
{
    std::shared_ptr<TVector2> mht(new TVector2(0.0,0.0));
    int jetCount=0;
    for(unsigned iJet=0; iJet<fL1JetEt.size(); ++iJet)
    {
        if( TMath::Abs(fL1JetEta[iJet]) > 3.0 ) continue;
        if( fL1JetEt[iJet] < 30.0 ) continue;
        std::shared_ptr<TVector2> jet(new TVector2(0.0,0.0));
        jet->SetMagPhi(fL1JetEt[iJet], fL1JetPhi[iJet]);
        ++jetCount;
        *(mht.get()) -= *(jet.get());
    }
    fRecalcL1Mht = mht->Mod();
    fRecalcL1MhtPhi = mht->Phi();
    fNJetL1Mht = jetCount;
}

void TL1EventClass::GetRecalcL1Ett()
{
    int iEtaMax = 28;
    Double_t sumEt = 0.0;
    int jetCount = 0;
    for(int jTower=0; jTower<fPrimitiveEvent->fCaloTowers->nTower; ++jTower)
    {
        int ieta = fPrimitiveEvent->fCaloTowers->ieta[jTower];
        int iet  = fPrimitiveEvent->fCaloTowers->iet[jTower];
        if( TMath::Abs(ieta) <= iEtaMax )
        {
            sumEt += 0.5 * (double)iet;
            ++jetCount;
        }
    }
    fRecalcL1Ett = sumEt;
    fNJetsL1Ett = jetCount;
}

void TL1EventClass::GetRecalcRecoHtSums()
{
    std::shared_ptr<TVector2> mht(new TVector2(0.,0.));
    double jetEt(0.0);
    unsigned jetCount(0);
    fMhtPassFlag = true;
    for(int iJet=0; iJet<fPrimitiveEvent->fJets->nJets; ++iJet)
    {
        bool passJetFilter = fJetFilterPassFlags[iJet];
        if( fPrimitiveEvent->fJets->etCorr[iJet] < 30.0 ) continue;
        if( !passJetFilter )
        {
            fMhtPassFlag = false;
            break;
        }
        std::shared_ptr<TVector2> jet(new TVector2(0.,0.));
        jet->SetMagPhi(fPrimitiveEvent->fJets->etCorr[iJet], fPrimitiveEvent->fJets->phi[iJet]);
        jetEt += fPrimitiveEvent->fJets->etCorr[iJet];
        ++jetCount;
        *(mht.get()) -= *(jet.get());
    }
    fRecalcRecoMht = mht->Mod();
    fRecalcRecoMhtPhi = mht->Phi();
    fRecalcRecoHtt = jetEt;
    fNJetRecoMht = jetCount;
}

void TL1EventClass::GetRecalcRecoEtt()
{
    double jetEt(0.0);
    int jetCount = 0;
    for(int iJet=0; iJet<fPrimitiveEvent->fJets->nJets; ++iJet)
        if( fPrimitiveEvent->fJets->etCorr[iJet] >= 30.0 )
        {
            jetEt += fPrimitiveEvent->fJets->etCorr[iJet];
            ++jetCount;
        }
    fRecalcRecoEtt = jetEt;
    fNJetsRecoEtt = jetCount;
}

bool TL1EventClass::GetMatchedJet(TL1JetMatch * jetMatch)
{
    unsigned iRecoJet = jetMatch->GetIReco();
    double recoJetEta = fPrimitiveEvent->fJets->eta[iRecoJet];
    double recoJetPhi = fPrimitiveEvent->fJets->phi[iRecoJet];
    double minDeltaR = 0.3;
    unsigned iMinL1Jet = 0;
    for(unsigned iL1=0; iL1<fL1JetEt.size(); ++iL1)
    {
        double l1JetEta = fL1JetEta[iL1];
        double l1JetPhi = fL1JetPhi[iL1];

        double deltaEta = l1JetEta-recoJetEta;
        if( deltaEta > minDeltaR ) continue;
        double deltaPhi = l1JetPhi-recoJetPhi;
        if( deltaPhi > minDeltaR ) continue;

        double deltaR = TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);

        if( deltaR < minDeltaR )
        {
            minDeltaR = deltaR;
            iMinL1Jet = iL1;
        }
    }
    if( minDeltaR < 0.3 )
    {
        jetMatch->SetIL1(iMinL1Jet);
        return true;
    }
    return false;
}

#endif
