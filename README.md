# l1t-macros

## Who did what?

### `TL1DataClass.h`

This is only called inside TL1EventClass.h. No need to call it in your own macro.

`fChain` holds a particular branch (at `chainPath`) in the Ntuple (in `inDir`).

- `GetEntries()` returns the number of events in fChain.
- `LoadTree(int iEntry)` loads event number iEntry.
- `GetEntry(int iEntry)` gets the event number iEntry. Called after loading the tree.

### `TL1EventClass.h`

Create objects of this class. Initialise like so:

`````C++
TL1EventClass event(inDir)
`````

where `inDir` is the path to your Ntuples (can be multiple or single - it loads all root-files in this directory).

- Constructor initializes member variables and points these to the branches.
- `Next()` loops to the next event returning true if it exists. Use like so:

    `````C++
    while( event.Next() )
    {
        std::cout << event->fSums->nJets << std::endl;
    }
    `````

- `GetEntry(int i)` skips to a particular entry. This does not change the position of `Next()`.
- The other functions are Filters that I use and functions which set additional variables that I use.
- `GetL1Variables()` extracts the L1 variables from the array-leaves.

## Skeleton

`````C++
std::string inDir = "/path/to/root/files/directory"
TL1EventClass * event = new TL1EventClass(inDir);

while( event->Next() )
{
    event->GetL1Sums(); // Load L1 Sums as: fL1Met, fL1Mht, ...
    event->GetL1Jets(); // Load L1 Jets as: fL1JetEt[iJet], ...

    // Sums - reco
    double recoMet = event->fSums->caloMetBE;
    double recoMht = event->fSums->mHt;
    double recoEtt = event->fSums->caloSumEtBE;
    double recoHtt = event->fSums->Ht;

    double recoMetPhi = event->fSums->caloMetPhiBE;
    double recoMhtPhi = event->fSums->mHtPhi;

    // Sums - L1
    double l1Met = event->fL1Met;
    double l1Mht = event->fL1Mht;
    double l1Ett = event->fL1Ett;
    double l1Htt = event->fL1Htt;

    double l1MetPhi = event->fL1MetPhi;
    double l1MhtPhi = event->fL1MhtPhi;

    // Met Filter - hbhe met filter
    bool metFilter = event->SumsFilter();

    // Muon Filter - pt>=20.0, iso<=0.1, isLoose==1.0
    bool muonFilter = event->MuonFilter();

    // Jets
    for(unsigned iJet=0; iJet<event->fJets->nJets; ++iJet)
    {
        // reco
        double recoJetEt = event->fJets->et[iJet];
        double recoJetEta = event->fJets->eta[iJet];
        double recoJetPhi = event->fJets->phi[iJet];

        // L1
        double l1JetEt = event->fL1JetEt[iJet];
        double l1JetEta = event->fL1JetEta[iJet];
        double l1JetPhi = event->fL1JetPhi[iJet];

        // Jet Filter - tightLepVeto and muMult==0
        bool jetFilter = event->JetFilter(iJet);
    }
}
`````
