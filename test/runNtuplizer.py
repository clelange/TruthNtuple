####### Process initialization ##########
import FWCore.ParameterSet.Config as cms

process = cms.Process("NTUP")

####### Config parser ##########
import FWCore.ParameterSet.VarParsing as VarParsing

options = VarParsing.VarParsing('analysis')
options.maxEvents = -1
options.inputFiles = 'file:/eos/cms//store/user/clange/WJetsToQQ_HT-800toInf/93X_mc2017_realistic_v3_2018-04-16/180416_160925/0000/WJetsToQQ_HT-800toInf_1.root'
options.outputFile = 'flatTuple.root'
options.parseArguments()
process.options = cms.untracked.PSet(
    wantSummary=cms.untracked.bool(False),
    SkipEvent=cms.untracked.vstring('ProductNotFound'),
    allowUnscheduled=cms.untracked.bool(True)
)

process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string(options.outputFile)
                                   )

process.maxEvents = cms.untracked.PSet(
    input=cms.untracked.int32(options.maxEvents))

process.source = cms.Source("PoolSource",
                            fileNames=cms.untracked.vstring(
                                options.inputFiles),
                            duplicateCheckMode=cms.untracked.string(
                                'noDuplicateCheck')
                            )

# ####### Logger ##########
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Ntuple')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit=cms.untracked.int32(1)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

####### Redo Jet clustering sequence ##########
from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJets
from RecoJets.Configuration.RecoGenJets_cff import ak8GenJets

process.genParForJets = genParticlesForJets.clone(
    src=cms.InputTag("genParticles"))

process.ak8GenJets = ak8GenJets.clone(src='genParForJets')

process.NjettinessGenAK8 = cms.EDProducer("NjettinessAdder",
                                          src=cms.InputTag("ak8GenJets"),
                                          # compute 1-, 2-, 3-, 4- subjettiness
                                          Njets=cms.vuint32(1, 2, 3, 4),
                                          # variables for measure definition:
                                          # CMS default is normalized measure
                                          measureDefinition=cms.uint32(0),
                                          # CMS default is 1
                                          beta=cms.double(1.0),
                                          # CMS default is jet cone size
                                          R0=cms.double(0.8),
                                          # not used by default
                                          Rcutoff=cms.double(999.0),
                                          # variables for axes definition:
                                          # CMS default is 1-pass KT axes
                                          axesDefinition=cms.uint32(6),
                                          # not used by default
                                          nPass=cms.int32(999),
                                          # not used by default
                                          akAxesR0=cms.double(-999.0)
                                          )

from RecoJets.JetProducers.SubJetParameters_cfi import SubJetParameters
process.ak8GenJetsPruned = ak8GenJets.clone(
    SubJetParameters,
    usePruning=cms.bool(True),
    writeCompound=cms.bool(True),
    jetCollInstanceName=cms.string("SubJets"),
    src=cms.InputTag("genParForJets")
)

process.ak8GenJetsSoftDrop = ak8GenJets.clone(
    SubJetParameters,
    useSoftDrop=cms.bool(True),
    R0=cms.double(0.8),
    beta=cms.double(0.0),
    writeCompound=cms.bool(True),
    jetCollInstanceName=cms.string("SubJets"),
    src=cms.InputTag("genParForJets")
)

process.ak8GenJetsPrunedMass = cms.EDProducer("RecoJetDeltaRValueMapProducer",
                                              src=cms.InputTag("ak8GenJets"),
                                              matched=cms.InputTag(
                                                  "ak8GenJetsPruned"),
                                              distMax=cms.double(0.8),
                                              value=cms.string('mass')
                                              )

process.ak8GenJetsSoftDropMass = cms.EDProducer("RecoJetDeltaRValueMapProducer",
                                                src=cms.InputTag("ak8GenJets"),
                                                matched=cms.InputTag(
                                                    "ak8GenJetsSoftDrop"),
                                                distMax=cms.double(0.8),
                                                value=cms.string('mass')
                                                )

# Redo pat jets from gen AK8
process.genJetsAK8 = cms.EDProducer("PATJetProducer",
                                    addJetCharge=cms.bool(False),
                                    addGenJetMatch=cms.bool(False),
                                    embedGenJetMatch=cms.bool(False),
                                    addAssociatedTracks=cms.bool(False),
                                    addBTagInfo=cms.bool(False),
                                    partonJetSource=cms.InputTag(
                                        "NOT_IMPLEMENTED"),
                                    addGenPartonMatch=cms.bool(False),
                                    JetPartonMapSource=cms.InputTag(""),
                                    resolutions=cms.PSet(),
                                    genPartonMatch=cms.InputTag(""),
                                    addTagInfos=cms.bool(False),
                                    addPartonJetMatch=cms.bool(False),
                                    embedGenPartonMatch=cms.bool(False),
                                    efficiencies=cms.PSet(),
                                    genJetMatch=cms.InputTag(""),
                                    useLegacyJetMCFlavour=cms.bool(False),
                                    userData=cms.PSet(
                                        userCands=cms.PSet(
                                            src=cms.VInputTag("")
                                        ),
                                        userInts=cms.PSet(
                                            src=cms.VInputTag("")
                                        ),
                                        userFloats=cms.PSet(
                                            src=cms.VInputTag("ak8GenJetsPrunedMass",
                                                              "ak8GenJetsSoftDropMass",
                                                              "NjettinessGenAK8:tau1",
                                                              "NjettinessGenAK8:tau2",
                                                              "NjettinessGenAK8:tau3")
                                        ),
                                        userClasses=cms.PSet(
                                            src=cms.VInputTag("")
                                        ),
                                        userFunctionLabels=cms.vstring(),
                                        userFunctions=cms.vstring()
                                    ),
                                    jetSource=cms.InputTag("ak8GenJets"),
                                    addEfficiencies=cms.bool(False),
                                    discriminatorSources=cms.VInputTag(),
                                    trackAssociationSource=cms.InputTag(""),
                                    tagInfoSources=cms.VInputTag(
                                        cms.InputTag("")),
                                    jetCorrFactorsSource=cms.VInputTag(
                                        cms.InputTag("")),
                                    embedPFCandidates=cms.bool(False),
                                    addJetFlavourInfo=cms.bool(False),
                                    addResolutions=cms.bool(False),
                                    getJetMCFlavour=cms.bool(False),
                                    addDiscriminators=cms.bool(False),
                                    jetChargeSource=cms.InputTag(""),
                                    JetFlavourInfoSource=cms.InputTag(""),
                                    addJetCorrFactors=cms.bool(False),
                                    jetIDMap=cms.InputTag(""),
                                    addJetID=cms.bool(False)
                                    )

process.selectedGenJetsAK8 = cms.EDFilter("PATJetSelector",
                                          src=cms.InputTag("genJetsAK8"),
                                          cut=cms.string('pt > 15')
                                          )

process.redoPatJets = cms.Sequence(process.genJetsAK8 +
                                   process.selectedGenJetsAK8)

genAK8 = 'selectedGenJetsAK8'
################## Ntuplizer ###################
process.ntuplizer = cms.EDAnalyzer("TruthNtuple",
                                   doGenParticles=cms.bool(True),
                                   doGenJets=cms.bool(True),
                                   doGenEvent=cms.bool(True),
                                   genJets=cms.InputTag("ak4GenJets"),
                                   genJetsAK8=cms.InputTag(genAK8),
                                   genparticles=cms.InputTag("genParticles"),
                                   genEventInfo=cms.InputTag("generator"),
                                   externallheProducer=cms.InputTag(
                                       "externalLHEProducer"),
                                   )

process.p = cms.Path(process.genParForJets + process.ak8GenJets + process.NjettinessGenAK8 + process.ak8GenJetsPruned + process.ak8GenJetsSoftDrop +
                     process.ak8GenJetsSoftDropMass + process.ak8GenJetsPrunedMass + process.genJetsAK8 + process.selectedGenJetsAK8 + process.ntuplizer)
