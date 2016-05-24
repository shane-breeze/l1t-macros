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

~~~~~
TL1EventClass event(inDir)
~~~~~

where `inDir` is the path to your Ntuples (can be multiple or single - it loads all root-files in this directory).

- Constructor initializes member variables and points these to the branches.
- `Next()` loops to the next event returning true if it exists. Use like so:

    ~~~~~
    while( event.Next() )
    {
        std::cout << event->fSums->nJets << std::endl;
    }
    ~~~~~

- `GetEntry(int i)` skips to a particular entry. This does not change the position of `Next()`.
- The other functions are Filters that I use and functions which set additional variables that I use.
- `GetL1Variables()` extracts the L1 variables from the array-leaves.
