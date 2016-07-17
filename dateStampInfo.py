import os

# TO RUN (on lxplus)
# $ python <pathToFile>/dateStampInfo.py

eosLocationBase = "/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v71p1/SingleMuon/"

# $ eos ls eosLocationBase
# to get the following list

directories = [
"crab_Collision2016-wRECO-l1t-integration-v71p1__276242_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276243_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276244_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276282_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276283_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276315_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276317_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276318_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276326_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276327_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276352_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276355_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276357_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276361_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276363_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276384_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276437_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276453_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276454_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276455_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276456_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276457_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276458_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276495_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276501_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276502_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276525_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276527_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276528_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276542_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276543_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276544_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276545_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276581_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276582_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276583_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276584_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276585_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276586_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276653_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276655_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276659_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276775_SingleMuon/",
"crab_Collision2016-wRECO-l1t-integration-v71p1__276776_SingleMuon/",
]

# run w/o datestamps line to get the required
# datestamps list...can then put in to check 0000's

dateStamps = [
"160713_011258",
"160713_010926",
"160713_010210",
"160713_011747",
"160713_011101",
"160713_011624",
"160713_011002",
"160713_011559",
"160713_153648",
"160713_010451",
"160713_011033",
"160713_010714",
"160713_012210",
"160713_011534",
"160713_011945",
"160713_010558",
"160713_012016",
"160713_154023",
"160713_154139",
"160713_154436",
"160713_154306",
"160713_154350",
"160713_154415",
"160713_154052",
"160713_153938",
"160713_154244",
"160713_153738",
"160713_153913",
"160713_154201",
"160713_153619",
"160713_153848",
"160713_154118",
"160713_154221",
"160713_154327",
"160713_153823",
"160713_153713",
"160713_154000",
"160713_153801",
"160713_154458",
"160715_224916",
"160715_224942",
"160715_224707",
"160715_224730",
"160715_224856",
]

# script running
# (assumes if there are two timeStamps that the most recent one, ie later stamp, is correct)
os.system("source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh")
i=0
for directory in directories:
    os.system("eos ls %s%s | tail -1" % (eosLocationBase,directory))  
    #os.system("eos ls %s%s%s" % (eosLocationBase,directory,dateStamps[i]))
    #i=i+1
