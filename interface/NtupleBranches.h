#ifndef NtupleBranches_H
#define NtupleBranches_H

#include "DataFormats/FWLite/interface/Event.h"
#include "DataFormats/Common/interface/Handle.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "FWCore/Framework/interface/Event.h"
// #include "TMatrixD.h"
// #include "TMatrix.h"

#include "TTree.h"
#include "TLorentzVector.h"

/*here we declare the input and output variables*/

class NtupleBranches {

public:
  NtupleBranches( std::map< std::string, bool >& runFlags, TTree* tree = 0);
  ~NtupleBranches( void );

  void branch( std::map< std::string, bool >& runFlags );
  void getEventByLabels( edm::EventBase const & event );
  void reset( void );
  void fillTree( void ){ tree_->Fill(); };

  //===================================================================================================================
  /* output tree variables*/

  /** genParticles */
  int                             genParticle_N;
  std::vector<float>              genParticle_pt       ;
//  std::vector<float>              genParticle_px       ;
//  std::vector<float>              genParticle_py       ;
//  std::vector<float>              genParticle_pz       ;
//  std::vector<float>              genParticle_e        ;
  std::vector<float>              genParticle_eta      ;
  std::vector<float>              genParticle_phi      ;
  std::vector<float>              genParticle_mass     ;
  std::vector<int  >              genParticle_pdgId    ;
  std::vector<int  >              genParticle_isPrompt ;
  std::vector<int  >              genParticle_isDirectPromptTauDecayProduct;
  std::vector<int  >              genParticle_fromHardProcessFinalState;
  std::vector<int  >              genParticle_isDirectHardProcessTauDecayProductFinalState;
  std::vector<int  >              genParticle_status   ;
  std::vector<int  >              genParticle_nDau     ;
  std::vector<int  >              genParticle_nMoth    ;
  std::vector<std::vector<int> >  genParticle_mother   ;
  std::vector<std::vector<int> >  genParticle_dau      ;
  std::vector<float >  genParticle_tauvispt      ;
  std::vector<float >  genParticle_tauviseta      ;
  std::vector<float >  genParticle_tauvisphi      ;
  std::vector<float >  genParticle_tauvismass      ;
  std::vector<int >  genParticle_taudecay      ;

  /** generator info */
  float                           lheV_pt              ;
  float                           lheHT                ;
  int                             lheNj                ;
  int                             lheNb                ;
  int                             lheNl                ;
  float                           lheV_mass            ;
  float                           genWeight            ;
  float                           genFacWeightUp       ;
  float                           genFacWeightDown     ;
  float                           genRenWeightUp       ;
  float                           genRenWeightDown     ;
  float                           genFacRenWeightUp    ;
  float                           genFacRenWeightDown  ;
  float                           qScale               ;
  float                           PDF_rms              ;
  std::vector<int  >              PDF_id               ;
  std::vector<float>              PDF_x                ;
  std::vector<float>              PDF_xPDF             ;

  /** AK4 genJets*/
  int			      genJetAK4_N               ;
  std::vector<float>  	      genJetAK4_pt              ;
  std::vector<float>  	      genJetAK4_eta             ;
  std::vector<float>  	      genJetAK4_mass            ;
  std::vector<float>  	      genJetAK4_phi             ;
  std::vector<float>  	      genJetAK4_e               ;
  std::vector<float>  	      genJetNoNuAK4_pt          ;
  std::vector<float>  	      genJetNoNuAK4_mass        ;
  std::vector<float>  	      genJetNoNuAK4_e           ;

  /*-------------------------AK8 genJets---------------------------*/
  int			      genJetAK8_N               ;

  std::vector<float>  	      genJetAK8_pt              ;
  std::vector<float>  	      genJetAK8_eta             ;
  std::vector<float>  	      genJetAK8_mass            ;
  std::vector<float>  	      genJetAK8_phi             ;
  std::vector<float>  	      genJetAK8_e               ;
  std::vector<float>  	      genJetAK8_prunedmass      ;
  std::vector<float>  	      genJetAK8_softdropmass    ;
  std::vector<float>  	      genJetAK8_tau1            ;
  std::vector<float>  	      genJetAK8_tau2            ;
  std::vector<float>  	      genJetAK8_tau3            ;

  /*------------------------EVENT infos-------------------------*/
  int                               EVENT_event            ;
  int                               EVENT_run              ;
  int                               EVENT_lumiBlock        ;

private:
  TTree* tree_;

};

#endif // NtupleBranches_H
