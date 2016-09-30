#l1t-macros

## How to run

### 1. Setup the dataset config file
Move into the `Config` folder and change the relevant config files.

`ntuple_cfg.h` contains the information on the dataset and where to get them. To
add a dataset simply:
* Create a new function which returns a `ntuple_cfg` object and set the
  following variables
    - `sampleName` for a shortened version of the sample's name, e.g. `"Data"`
    - `sampleTitle` for a longer version of the sample's name, e.g. `"2016 Data"`
    - `triggerName` for data, e.g. `"SingleMu"` or `"ZeroBias"`
    - `triggerTitle` for data, e.g. `"Single Muon"` or `"Zero Bias"`
    - `puFilename` for the pu weights for reweighting the PU distribution of MC
      samples (this file is produced using `MakePlots/generatePUWeights.cxx`
    - `run` for the run number of data
    - `outDirBase` for the base directory of all output files
    - `doFit` to add a relevent fit to the plots. If there is not relevant fit,
      then no fit is done
    - `puType` is a vector of strings in the format of `{"0PU20","20PU40","40PU"}`
    - `puBins` is a vector of ints and should match `puType`, e.g. `{0,20,40,999}`.
      The final bin is significantly large to be effectively inifinite
    - `inFiles` is a string for the location of the ntuples. I tend to use the
      EOS locations (examples are shown in `ntuple_cfg.h`). Also replace the
      ntuple number with a wildcard, e.g. `"L1Ntuple_*.root"`
    - `baseOWdir` is the directory inside `outDirBase` that contains all the hadded
      files from a set of jobs.
    - `outDir` is the directory inside `outDirBase` where the output files will
      go. This will include the date in it's name
* Then return the `ntuple_cfg` object
* Return your newly created function in the `GetNtuple_cfg()` function to use
  your dataset

### 2. Setup the plot config file
I will be using the `jetTurnons_cfg.h` as an example here (similar things apply
to the other files).

The function `jetTurnons` returns a map of strings to `TL1Turnon*` (the class
to produce turnon curves). This contains all turnons for jets (e.g. barrel,
endcap, central and HF turnons). 

To add your own turnon:
* Create a new function that returns a `TL1Turnon` and `emplace` it in the 
  `jetTurnons` function
* The function should take a `ntuple_cfg` as the argument to get details of the
  dataset
* Set the following variables:
    - `seed` is the name of the variable that is the seed for the turnon
    - `xparam` is the x-axis parameter of the turnon (y-axis is efficiency)
    - `outName` is the output name of the histograms (follow similar naming
      schemes as with the other turnon functions)
    - `SetOverwriteNames` takes 2 arguments. The first is the root-file
      associated with this turnon in the hadded directory of a set of jobs. The
      second is the name of the histogram inside the root-file for this
      particular turnon (with the seed value and PU value suppressed)
    - `SetSeed` takes 2 arguments. The first is `seed` and the second is a
      longer version of it
    - `SetSeeds` takes a vector of doubles which will be the set of seed values
      used. The first must always be `0.0` (i.e. no seed)
    - `SetX` takes 2 arguments. The first is `xparam` and the second is a longer
      version of `xparam`
    - `SetXBins` takes a vector of doubles representing all edges of the histogram's
      bins. I typically use separate functions to create these vectors
    - `SetOutName` takes `outName` as an argument
    - `SetFit` takes `dataset->doFit` as an argument
    - `SetAddMark` places additional text on the final canvas
* Return the `TL1Turnon`

We now need to add the logic to fill your turnon:
* Open the file `MakePlots/makeJetTurnons.cxx` and go inside the for-loop
  after the `// Loop` comment
* Use `continue;` to skip an event that is not desired (e.g. if it doesn't pass
  some filter defined in `Events/TL1Events.h`)
* Get the relevant event parameters from the `TL1Event` object (named `event`)
  and store them
* Fill the `turnons` object like so:
```C++
turnons[turnonName]->Fill(xparam, seed, pu);
```
where `turnonName` is a string representing the name chosen in the config file,
xparam is the value of the x-axis parameter, seed is the value of the seed for
that particular event and `pu` is the number of PU vertices (the default value
for `pu` is zero which is understood as the PU is not give).

### 3. Run the submission script locally
In this case I will continue using jet turnons as an example.

Run `cmsenv` from inside the relevant version of CMSSW with the relevant L1T
integration code. Move to the top directory of the github repository.

The scripts can be run locally using the following command:
```bash
export NFILES=123
sh submitJetTurnons.sh 0 $NFILES 1 false
```
where `NFILES` is the number on the final `L1Ntuple_*.root` in the `inFiles`
directory. This will run over all root-files locally.

### 4. Run the submission script on a batch system
You can also submit jobs to the CERN batch (simple to extend to other batch systems)
using the following command:
```bash
for i in {0..${NJOBSM1}}; do bsub -q 1nh "sh submitJetTurnons.sh $i $NFILES $NJOBS false"; done
bjobs # check the status of your jobs
```
where `${NJOBSM1}` is the number of jobs to submit minus one, `$NFILES` is the
number of root-files and `$NJOBS` is the number of jobs to submit.

Now the histograms must be hadded together using the script `Scripts/haddBatchFiles.py`
like so:
```bash
export CHUNKDIR=/path/to/output_CHUNK*/Turnons
python Scripts/haddBatchFiles.py -i "${CHUNKDIR}"
```
You must have a wildcard so that all CHUNKS (individual jobs) are hadded. The
quotes in `"${CHUNKDIR}"` must be present to allow the wildcard to work properly.
This script will delete the individual CHUNKS and leave a HADDED directory.

Now we create the plots from the hadded root-files. Double-check the config file
`Config/jetTurnons_cfg.h" and make sure that the `SetOverwriteNames` takes the
correct arguments. Once certain that they do run the following:
```bash
sh submitJetTurnons.sh 0 $NFILES $NJOBS true
```
where `NFILES` is the number of input root-files and `NJOBS` is the number of
jobs that were run over. Now the hadded output directory should contain all
turnon plots and root-files.

You can create scripts to mix and match histograms from the root-files.

## How to get variables from the ntuples
1. Create an object (named `event` for example) of class `TL1EventClass` with a single input argument, a vector of strings representing the directories where the root-files are located
2. Call the `Next()` function of class `TL1EventClass`. This returns a boolean, true if there is a next event, false if not. Hence this can be placed in the argument of a while statement
3. If we want to access the sums tree from l1RecoJetTree we can get to this like so:
    ```C++
        event->GetPEvent()->fSums   
    ```
4. The names for the ntuple trees are in `Event/TL1PrimitiveEvent.h`. `GetPEvent()` returns a constant to an object of class `TL1PrimitiveEventClass`. The trees from `TL1PrimitiveEventClass` are public, so caution must be taken if creating an object of `TL1PrimitiveEventClass`
5. To get the level-1 upgrade tree parameters (since these are stored in arrays) they are accessed from `TL1EventClass` and are public (due to laziness), e.g. fL1Met, fL1EmuMetHF, ...
