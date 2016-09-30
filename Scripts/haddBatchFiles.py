import glob
import os
import subprocess

# optparse
import optparse
parser = optparse.OptionParser()
parser.add_option("-i","--inDir",type="string",default=None,help="Input File (surrounded by quotes) with a wild card for the CHUNK number")
options, args = parser.parse_args()

if options.inDir == None:
    raise RuntimeError, "Please provide -i options (--inDir)"

outdir = options.inDir.replace("_CHUNK*","_hadd")
basedirs = glob.glob(options.inDir)

if os.path.exists(outdir):
    print "Output directory already exists. I will not overwrite."
    print "\t"+outdir
    raise RuntimeError
os.makedirs(outdir)

outputRootFiles = []
for fileToHadd in os.listdir(basedirs[0]):
    if ".root" not in fileToHadd: continue
    if any(removeFile in fileToHadd for removeFile in ["effs_",".pdf"]): continue

    haddFilePath = os.path.join(outdir,fileToHadd)
    outputRootFiles.append(haddFilePath)

    process = ["hadd"]
    process.append(haddFilePath) 

    haddList = []
    for basedir in basedirs:
        rootFilePath = os.path.join(basedir,fileToHadd)
        if not os.path.exists(rootFilePath):
            print "Warning: Cannot find", rootFilePath
            continue
        haddList.append(rootFilePath)
    process += haddList
    subprocess.call(process)

if any([not os.path.exists(outFile) for outFile in outputRootFiles]):
    print "Seems like some of the output hadded files are missing. I will not "\
            +"remove the separate CHUNKS yet"
    raise RuntimeError
for rmdir in glob.glob(options.inDir.replace(options.inDir.split("/")[-1],"")):
    if rmdir[-1] == '/': rmdir = rmdir[:-1]
    print "rm -r", rmdir
    os.system("rm -r "+rmdir)

    rmdir = rmdir.replace(rmdir.split('/')[-1],"")
    if len(os.listdir(rmdir))==0:
        print "rm -r", rmdir
        os.system("rm -r "+rmdir)
