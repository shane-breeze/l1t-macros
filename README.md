# l1t-macros

## How to make it work

There are three different types of macros to produce different plots:
- XvsY plots some variable x against another y. Mostly done for level-1 against offline, but can also do level-1 HW vs. level-1 EMU for example.
- Resolutions plots (level-1 - offline)/offline. I was trying to add some functionality to also plot the RMS/mean of this distribution.
- Turnons plots the turnon for a level-1 and offline variable combination.
These are further split into energy sums (looping over events) and jets (looping over events and then jets)

### General things to change

1. Change the sample (only Data is really implemented thus far)
2. Choose the trigger name and title (name is placed in file names and title is placed on plot titles - this is the naming convention used throughout)
3. Choose the run number, or make it a range, or something like "2016B\_v1"
4. Input the output directory in outDirBase
5. Select the pile-up bin splitting. This will generate the plots in the chosen pile-up bins (note that the plots inclusive of pile-up are still produced)
6. Change inDir to point at the directory that contains all root-files you want to run over. The code uses the wildcard "\*.root" in this directory to select the root-files
7. Change outDir to conform to how you want the output directory to look like. I like:
    ```bash
    ${OUTDIRBASE}/${DATE}_${SAMPLE}_${RUN}_${TRIGGER}/
        - XvsY/
        - XvsYJets/
        - Resolutions/
        - ResolutionsJets/
        - Turnons/
        - TurnonsJets/
    ```

### makeXvsY.cxx
The object xvsy is a vector of TL1XvsY objects. Each one represents a different type of xvsy plot. `xvsy.emplace_back(new TL1XvsY());` to create a new element in the vector, then set:

1. `SetXBins(bins)` where `bins` is a vector with the edges of the bins desired (I typically have functions that generate this vector)
2. `SetX(name,title)` where `name` and `title` are the respective x-name and x-title as strings
3. `SetYBins(bins)` to set the y binning (typically the same as the x binning)
4. `SetY(name,title)` to set the y-name and y-title
5. `SetOutName(name)` to set the output name for this plot, e.g. `triggerName+"_"+xName+"_vs_"+yName+"_"+requirements` where `requirements` is a string describing any requirements for this plot (e.g. barrel only)
6. `SetAddMark(mark)` adds a `mark` (some test) on the plot that can describe any requirements if desired (e.g. eta range selected)

Now repeat this for all plots desired. Further down in the code inside the event loop (`while( event->Next() )`) is the logic of filling the plots. After getting the pile-up start filling using `Fill(xval, yval, pu)` applying some requirements:

1. For XvsY I typically include a requirement of `xval>0.0` and `yval>0.0` to prevent the z-scale from screwing up
2. For the `xval` and `yval` these are obtained from `event->GetPEvent()` if they are found in the ntuples originally. If they are created in `TL1EventClass.h` (such as level-1 values) then they are acquired via `event`, e.g.
    ```C++
    double offlineMht = event->GetPEvent->fSums->mHt;
    double l1Mht = event->fL1Mht; 
    ```
3. There are a few flags in `TL1EventClass` (`event` is an object of this). For MET in SingleMuon I typically use:
    ```C++
    bool muonFilterFlag = event->fMuonFilterPassFlag;
    bool metFilterFlag = event->fMetFilterPassFlag;
    ```
4. If using a phi variable as x or y, I send it through the `FoldPhi(phi)` function to get it in the range of 0 to pi.

### makeResolutions.cxx

### makeTurnons.cxx
