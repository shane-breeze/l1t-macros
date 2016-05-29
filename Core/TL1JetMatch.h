#ifndef TL1JETMATCH_H
#define TL1JETMATCH_H

class TL1JetMatch
{
    public:
        TL1JetMatch(unsigned iL1, unsigned iReco);

        void SetIL1(unsigned iL1);
        void SetIReco(unsigned iReco);
        
        unsigned GetIL1() const;
        unsigned GetIReco() const;

    private:
        unsigned fIL1, fIReco;
};

TL1JetMatch::TL1JetMatch(unsigned iL1, unsigned iReco) :
    fIL1(iL1), fIReco(iReco)
{
}

void TL1JetMatch::SetIL1(unsigned iL1)
{
    fIL1 = iL1;
}

void TL1JetMatch::SetIReco(unsigned iReco)
{
    fIReco = iReco;
}

unsigned TL1JetMatch::GetIL1() const
{
    return fIL1;
}

unsigned TL1JetMatch::GetIReco() const
{
    return fIReco;
}

#endif
