import os

# TO RUN
# $ python ~/l1t-macros/copyFromEOS.py

#######################################################################
#######################################################################
#######################################################################
#######################################################################
#######################################################################
#######################################################################
# user defined input

eosLocationBase = "/eos/cms/store/group/dpg_trigger/comm_trigger/L1Trigger/L1Menu2016/Stage2/Collision2016-wRECO-l1t-integration-v71p1/SingleMuon/"
localLocation = "/hdfs/user/jt15104/copiesFromEOS/singleMuon2016_v71p1/"

# subDirectories... KEY:how they occur on eos. VALUE:how you want them on /hdfs
# (use dateStampInfo.py on lxplus to find the necessary info)
subDirDict = {
				"crab_Collision2016-wRECO-l1t-integration-v71p1__276242_SingleMuon/160713_011258/0000/":"run276242/",
				"crab_Collision2016-wRECO-l1t-integration-v71p1__276243_SingleMuon/160713_010926/0000/":"run276243/",
				"crab_Collision2016-wRECO-l1t-integration-v71p1__276244_SingleMuon/160713_010210/0000/":"run276244/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276282_SingleMuon/160713_011747/0000/":"run276282/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276283_SingleMuon/160713_011101/0000/":"run276283/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276315_SingleMuon/160713_011624/0000/":"run276315/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276317_SingleMuon/160713_011002/0000/":"run276317/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276318_SingleMuon/160713_011559/0000/":"run276318/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276326_SingleMuon/160713_153648/0000/":"run276326/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276327_SingleMuon/160713_010451/0000/":"run276327/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276352_SingleMuon/160713_011033/0000/":"run276352/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276355_SingleMuon/160713_010714/0000/":"run276355/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276357_SingleMuon/160713_012210/0000/":"run276357/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276361_SingleMuon/160713_011534/0000/":"run276361/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276363_SingleMuon/160713_011945/0000/":"run276363/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276384_SingleMuon/160713_010558/0000/":"run276384/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276437_SingleMuon/160713_012016/0000/":"run276437/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276453_SingleMuon/160713_154023/0000/":"run276453/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276454_SingleMuon/160713_154139/0000/":"run276454/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276455_SingleMuon/160713_154436/0000/":"run276455/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276456_SingleMuon/160713_154306/0000/":"run276456/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276457_SingleMuon/160713_154350/0000/":"run276457/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276458_SingleMuon/160713_154415/0000/":"run276458/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276495_SingleMuon/160713_154052/0000/":"run276495/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276501_SingleMuon/160713_153938/0000/":"run276501/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276502_SingleMuon/160713_154244/0000/":"run276502/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276525_SingleMuon/160713_153738/0000/":"run276525/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276527_SingleMuon/160713_153913/0000/":"run276527/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276528_SingleMuon/160713_154201/0000/":"run276528/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276542_SingleMuon/160713_153619/0000/":"run276542/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276543_SingleMuon/160713_153848/0000/":"run276543/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276544_SingleMuon/160713_154118/0000/":"run276544/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276545_SingleMuon/160713_154221/0000/":"run276545/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276581_SingleMuon/160713_154327/0000/":"run276581/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276582_SingleMuon/160713_153823/0000/":"run276582/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276583_SingleMuon/160713_153713/0000/":"run276583/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276584_SingleMuon/160713_154000/0000/":"run276584/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276585_SingleMuon/160713_153801/0000/":"run276585/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276586_SingleMuon/160713_154458/0000/":"run276586/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276653_SingleMuon/160715_224916/0000/":"run276653/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276655_SingleMuon/160715_224942/0000/":"run276655/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276659_SingleMuon/160715_224707/0000/":"run276659/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276775_SingleMuon/160715_224730/0000/":"run276775/",
				# "crab_Collision2016-wRECO-l1t-integration-v71p1__276776_SingleMuon/160715_224856/0000/":"run276776/",
			}

# form of ntuple name on eos (can't use wildcards)
rootFileFormat = "L1Ntuple_"

# end of user defined section
#######################################################################
#######################################################################
#######################################################################
#######################################################################
#######################################################################
#######################################################################
c=1
for subDir in subDirDict:
	os.system("hadoop fs -mkdir -p %s%s" % (localLocation[5:],subDirDict[subDir]))
	print("*********************************")
	print("*********************************")
	print("*********************************")
	print("*** Doing %s: %d of %d ***" %(subDirDict[subDir][:-1], c, len(subDirDict)))
	print("*********************************")
	print("*********************************")
	print("*********************************")
	c=c+1

	for i in range(1,1000):
		os.system("xrdcp root://eoscms.cern.ch/%s%s%s%d.root %s%s%s_%s%d.root" % (eosLocationBase, subDir, 
				rootFileFormat, i,  localLocation, subDirDict[subDir], subDirDict[subDir][:-1], rootFileFormat, i))
