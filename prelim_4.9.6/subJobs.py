#!/usr/bin/python

import os, re, sys
from subprocess import *

nEventsPerJob  = 100000
nJobsPerConfig = 25
batchSystem    = "condor" # qsub OR condor (qsub not tested) 

rootDir  = "/home/jloach/working/neuproblm/NeuProBLM"
buildDir = "%s/build" % rootDir
prodDir  = "%s/prodn" % rootDir
                
if batchSystem == "qsub":   
  jobCommand   = "qsub"
  jobExtension = "sub"
if batchSystem == "condor":   
  jobCommand   = "condor_submit"
  jobExtension = "condor"

if not os.path.isdir(prodDir):
  print "making dir", prodDir
  os.makedirs(prodDir)

os.system("cp %s/muBeamTemplate.mac %s/" % (buildDir, prodDir))
os.system("cp %s/muBeamTemplate.%s %s/" % (buildDir, jobExtension, prodDir))

muEnergies        = [ "100 GeV", "190 GeV", "280 GeV" ]
physicsLists      = [ "Shielding", "QGSP_BERT_HP" ]
newMuNuclearFlags = [ "on", "off" ]
targetMaterials   = ["G4_Cu"]
targetLengths     = [ "50 cm" ]
#targetRadii       = [ "12.5 cm", "25 cm", "50 cm" ]
targetRadii       = [ "12.5 cm" ]

for muEnergy in muEnergies:
  for physicsList in physicsLists:
    for newMuNuclearFlag in newMuNuclearFlags:
      for targetMaterial in targetMaterials:
        for targetLength in targetLengths:
          for targetRadius in targetRadii:

              # build jobGroupDir and jobGroupName
              jobGroupName = "NP_%s_%s_newMuN%s_%s_TargetL%s_R%s" % \
                (muEnergy, physicsList, newMuNuclearFlag, targetMaterial, \
                targetLength, targetRadius)
              jobGroupName = re.sub(" ", "_", jobGroupName)
              jobGroupDir = prodDir + "/" + jobGroupName

              # make the job directory
              if not os.path.isdir(jobGroupDir):
                print "making dir", jobGroupDir
                os.makedirs(jobGroupDir)

              for i in range(nJobsPerConfig):
                jobName = jobGroupName + "_" + str(nEventsPerJob) + "_" + str(i)

                # generate .sub's
                sedCommand = "sed s/@JOBNAME@/%s/g \
                                %s/muBeamTemplate.%s > %s/%s.%s" % \
                  (jobName, prodDir, jobExtension, 
                   jobGroupDir, jobName, jobExtension)
                print sedCommand
                os.system(sedCommand)

                # generate .mac's
                sedCommand = "sed s/@MUENERGY@/'%s'/ muBeamTemplate.mac | \
                              sed s/@PHYSICSLIST@/'%s'/ | \
                              sed s/@NEWMUNUCLEARFLAG@/'%s'/ | \
                              sed s/@TARGETMATERIAL@/'%s'/ | \
                              sed s/@TARGETLENGTH@/'%s'/ | \
                              sed s/@TARGETRADIUS@/'%s'/ | \
                              sed s/@NEVENTS@/'%s'/ | \
                              sed s/@ROOTFILENAME@/'%s.root'/ > %s/%s.mac" % \
                                (muEnergy, physicsList, newMuNuclearFlag,  
                                targetMaterial, targetLength, targetRadius,  
                                str(nEventsPerJob), jobName, jobGroupDir, 
                                jobName)
                print sedCommand
                os.system(sedCommand)

                # submit Job
                print "Submitting job", jobName
                subCommand = "cd %s; %s %s.%s" % \
                  (jobGroupDir, jobCommand, jobName, jobExtension)
                print subCommand
                os.system(subCommand)

