import glob
import os
import subprocess

wilddir = "/afs/cern.ch/work/s/sbreeze/L1TriggerStudiesOutput/20160728_Data_run-276525_SingleMu_highMET_SET*/Turnons/"
outdir = wilddir.replace("_SET*","_hadd")
basedirs = glob.glob(wilddir)

if not os.path.exists(outdir):
    os.makedirs(outdir)

for fileToHadd in os.listdir(basedirs[0]):
    if ".root" not in fileToHadd: continue
    if any(removeFile in fileToHadd for removeFile in ["effs_",".pdf"]): continue
    haddFilePath = os.path.join(outdir,fileToHadd)
    
    process = ["hadd"]
    process.append(haddFilePath) 

    haddList = []
    for basedir in basedirs:
        rootFilePath = os.path.join(basedir,fileToHadd)
        if not os.path.exists(rootFilePath): continue
        haddList.append(rootFilePath)
    process += haddList

    subprocess.call(process)
