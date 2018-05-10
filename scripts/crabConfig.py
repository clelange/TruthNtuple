from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'request_DATASET_DATE_TAG'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'configs/CONFIG.py'

config.Data.outputPrimaryDataset = 'CONFIG_TuneCP5_13TeV-madgraphMLM-pythia8'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = EVENTSJOB
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = True
config.Data.outputDatasetTag = 'TAG_DATE'
config.JobType.numCores = 4

config.Site.storageSite = 'T2_CH_CERN'
config.Site.blacklist = ['T3_US_Baylor']
