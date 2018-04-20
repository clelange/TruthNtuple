#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "../interface/NtupleBranches.h"

// #include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "GeneratorInterface/LHEInterface/interface/LHEEvent.h"
class NtupleBranches;
class CandidateNtuplizer;

class TruthNtuple : public edm::EDAnalyzer {
public:
  explicit TruthNtuple(const edm::ParameterSet&);
  ~TruthNtuple();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  // virtual void beginJob()                                                                   override;
  // virtual void beginStream(edm::StreamID) override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&)                           override;
  // virtual void endJob()                                                                     override;
  // virtual void endStream() override;

  // virtual void beginRun(edm::Run const&, edm::EventSetup const&)                            override;
  // virtual void endRun(edm::Run const&, edm::EventSetup const&)                              override;
  // virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)    override;
  // virtual void endLuminosityBlock(edm::LuminosityBlock const  &, edm::EventSetup const&)    override;

  // ----------member data ---------------------------

  NtupleBranches* nBranches_;
  std::map<std::string,CandidateNtuplizer*>                 nTuplizers_         ;

  edm::EDGetTokenT< GenEventInfoProduct >                   geneventToken_      ;
  edm::EDGetTokenT<LHEEventProduct>	                    lheEventProductToken_;

  edm::EDGetTokenT<reco::GenParticleCollection>             genparticleToken_   ;

  edm::EDGetTokenT<reco::GenJetCollection>                  genJetToken_	;
  edm::EDGetTokenT<pat::JetCollection>                      genJetAK8Token_	;

};
