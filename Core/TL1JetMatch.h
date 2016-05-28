#ifndef TL1JETMATCH_H
#define TL1JETMATCH_H

class TL1JetMatch
{
    public:
        TL1JetMatch(double l1Et, double l1Eta, double l1Phi, double recoEt, double recoEta, double recoPhi);
        
        double GetL1Et() const;
        double GetL1Eta() const;
        double GetL1Phi() const;

        double GetRecoEt() const;
        double GetRecoEta() const;
        double GetRecoPhi() const;

    private:
        double fL1Et, fL1Eta, fL1Phi;
        double fRecoEt, fRecoEta, fRecoPhi;
};

TL1JetMatch::TL1JetMatch(double l1Et, double l1Eta, double l1Phi, double recoEt, double recoEta, double recoPhi) :
    fL1Et(l1Et), fL1Eta(l1Eta), fL1Phi(l1Phi),
    fRecoEt(recoEt), fRecoEta(recoEta), fRecoPhi(recoPhi)
{
}


double TL1JetMatch::GetL1Et() const
{
    return fL1Et;
}

double TL1JetMatch::GetL1Eta() const
{
    return fL1Eta;
}

double TL1JetMatch::GetL1Phi() const
{
    return fL1Phi;
}

double TL1JetMatch::GetRecoEt() const
{
    return fRecoEt;
}

double TL1JetMatch::GetRecoEta() const
{
    return fRecoEta;
}

double TL1JetMatch::GetRecoPhi() const
{
    return fRecoPhi;
}

#endif
