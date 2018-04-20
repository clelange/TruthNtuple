// -*- C++ -*-
//
// Package:    Analysis/TruthNtuple
// Class:      TruthNtuple
//
/**\class TruthNtuple TruthNtuple.cc Analysis/TruthNtuple/plugins/TruthNtuple.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Clemens Lange
//         Created:  Fri, 20 Apr 2018 08:00:33 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "../interface/TruthNtuple.h"
#include "../interface/CandidateNtuplizer.h"
#include "../interface/GenJetsNtuplizer.h"
#include "../interface/GenEventNtuplizer.h"
#include "../interface/GenParticlesNtuplizer.h"


#include "FWCore/ParameterSet/interface/FileInPath.h"


//
// class declaration
//
//
// class TruthNtuple : public edm::stream::EDProducer<> {
//    public:
//       explicit TruthNtuple(const edm::ParameterSet&);
//       ~TruthNtuple();
//
//       static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
//
//    private:
//       virtual void beginStream(edm::StreamID) override;
//       virtual void produce(edm::Event&, const edm::EventSetup&) override;
//       virtual void endStream() override;
//
//       //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
//       //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
//       //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
//       //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
//
//       // ----------member data ---------------------------
// };

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
TruthNtuple::TruthNtuple(const edm::ParameterSet& iConfig):

geneventToken_        	    (consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("genEventInfo"))),
lheEventProductToken_       (consumes<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("externallheProducer"))),
genparticleToken_     	    (consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genparticles"))),

genJetToken_	      	    (consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("genJets"))),
genJetAK8Token_	      	    (consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("genJetsAK8")))

{

   edm::Service<TFileService> fs;
   TTree* tree = fs->make<TTree>( "tree", "tree" );

   std::map< std::string, bool > runFlags;
   runFlags["doGenParticles"] = iConfig.getParameter<bool>("doGenParticles");
   runFlags["doGenJets"] = iConfig.getParameter<bool>("doGenJets");
   runFlags["doGenEvent"] = iConfig.getParameter<bool>("doGenEvent");

   nBranches_ = new NtupleBranches( runFlags, tree );

   if (runFlags["doGenJets"])
      nTuplizers_["genJets"]   = new GenJetsNtuplizer   ( genJetToken_, genJetAK8Token_, nBranches_    );

   if (runFlags["doGenParticles"]) {
      std::vector<edm::EDGetTokenT<reco::GenParticleCollection>> genpTokens;
      genpTokens.push_back( genparticleToken_ );
      nTuplizers_["genParticles"] = new GenParticlesNtuplizer( genpTokens, nBranches_ );
   }

   if (runFlags["doGenEvent"]) {
      std::vector<edm::EDGetTokenT< GenEventInfoProduct > > geneTokens;
      geneTokens.push_back( geneventToken_ );
      std::vector<edm::EDGetTokenT<  LHEEventProduct > > lheTokens;
      lheTokens.push_back( lheEventProductToken_);
      nTuplizers_["genEvent"] = new GenEventNtuplizer( geneTokens, nBranches_ , lheTokens);
   }

   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");

   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed

}


TruthNtuple::~TruthNtuple()
{

   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)
   for( std::map<std::string,CandidateNtuplizer*>::iterator it = nTuplizers_.begin(); it != nTuplizers_.end(); ++it )
      delete it->second;
   nTuplizers_.clear();
   delete nBranches_;

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TruthNtuple::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which
   // is put into the Event
   iEvent.put(std::make_unique<ExampleData2>(*pIn));
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
   nBranches_->reset();

   nBranches_->EVENT_event     = iEvent.id().event();
   nBranches_->EVENT_run       = iEvent.id().run();
   nBranches_->EVENT_lumiBlock = iEvent.id().luminosityBlock();

   for( std::map<std::string,CandidateNtuplizer*>::iterator it = nTuplizers_.begin(); it != nTuplizers_.end(); ++it )
      (it->second)->fillBranches( iEvent, iSetup );

   nBranches_->fillTree();

   nBranches_->reset();

}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
// void
// TruthNtuple::beginStream(edm::StreamID)
// {
// }

// ------------ method called once each stream after processing all runs, lumis and events  ------------
// void
// TruthNtuple::endStream() {
// }

// ------------ method called when starting to processes a run  ------------
/*
void
TruthNtuple::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void
TruthNtuple::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void
TruthNtuple::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
TruthNtuple::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TruthNtuple::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TruthNtuple);
