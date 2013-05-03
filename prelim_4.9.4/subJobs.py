import os, re, sys
from subprocess import *


nEventsPerJob = 100000
nJobsPerConfig = 10
baseDir = "/global/scratch/sd/jasondet/mbnm"
if not os.path.isdir(baseDir):
    print "making dir", baseDir
    os.makedirs(baseDir)


muEnergies = [ "100 GeV", "190 GeV", "280 GeV" ]
physicsLists = [ "Shielding", "QGSP_BERT_HP" ]
newMuNuclearFlags = [ "on", "off" ]
targetMaterials = ["G4_Cu"]
targetLengths = [ "50 cm" ]
targetRadii = [ "12.5 cm", "25 cm", "50 cm" ]

for muEnergy in muEnergies:
  for physicsList in physicsLists:
    for newMuNuclearFlag in newMuNuclearFlags:
      for targetMaterial in targetMaterials:
        for targetLength in targetLengths:
          for targetRadius in targetRadii:
	      # build jobGroupDir and jobGroupName
              jobGroupName = "mbnm_" + muEnergy + "_" + physicsList + "_" 
	      jobGroupName += "newMuN" + newMuNuclearFlag + "_" + targetMaterial + "_"
              jobGroupName += "TargetL" + targetLength + "_" + "R" + targetRadius
	      jobGroupName = re.sub(" ", "_", jobGroupName)
	      jobGroupDir = baseDir + "/" + jobGroupName
              if not os.path.isdir(jobGroupDir):
                  print "making dir", jobGroupDir
                  os.makedirs(jobGroupDir)
	      for i in range(nJobsPerConfig):
	          jobName = jobGroupName + "_" + str(nEventsPerJob) + "_" + str(i)

		  # generate .sub's
	          sedCommand = "sed s/@JOBNAME@/'" + jobName + "'/g muBeamTemplate.sub "
		  sedCommand += "> " + jobGroupDir + "/" + jobName + ".sub"
		  print sedCommand
		  Popen(['-c', sedCommand], shell=True).wait()

		  # generate .mac's
	          sedCommand = "sed s/@MUENERGY@/'" + muEnergy + "'/ muBeamTemplate.mac "
	          sedCommand += "| sed s/@PHYSICSLIST@/'" + physicsList + "'/ "
	          sedCommand += "| sed s/@NEWMUNUCLEARFLAG@/'" + newMuNuclearFlag + "'/ "
	          sedCommand += "| sed s/@TARGETMATERIAL@/'" + targetMaterial + "'/ "
	          sedCommand += "| sed s/@TARGETLENGTH@/'" + targetLength + "'/ "
	          sedCommand += "| sed s/@TARGETRADIUS@/'" + targetRadius + "'/ "
	          sedCommand += "| sed s/@NEVENTS@/'" + str(nEventsPerJob) + "'/ "
	          sedCommand += "| sed s/@ROOTFILENAME@/'" + jobName + ".root'/ "
		  sedCommand += "> " + jobGroupDir + "/" + jobName + ".mac"
		  Popen(['-c', sedCommand], shell=True).wait()

		  # submit Job
		  print "Submitting job", jobName
		  jobCommand = "cd " + jobGroupDir + "; qsub " + jobName + ".sub"
		  Popen(['-c', jobCommand], shell=True).wait()

