#include "../interface/NtupleBranches.h"

//===================================================================================================================
NtupleBranches::NtupleBranches( std::map< std::string, bool >& runFlags, TTree* tree )
   : tree_( tree )
{
   branch( runFlags );
}

//===================================================================================================================
NtupleBranches::~NtupleBranches( void )
{
}

//===================================================================================================================
void NtupleBranches::branch( std::map< std::string, bool >& runFlags ){

        if ( runFlags["doGenParticles"] ){
        /** genParticles */
        tree_->Branch( "genParticle_N"	     , &genParticle_N	       );
        tree_->Branch( "genParticle_pt"	     , &genParticle_pt	       );
        //      tree_->Branch( "genParticle_px"	     , &genParticle_px	       );
        //      tree_->Branch( "genParticle_py"	     , &genParticle_py	       );
        //      tree_->Branch( "genParticle_pz"	     , &genParticle_pz	       );
        //      tree_->Branch( "genParticle_e" 	     , &genParticle_e	       );
        tree_->Branch( "genParticle_eta"	     , &genParticle_eta        );
        tree_->Branch( "genParticle_phi"	     , &genParticle_phi        );
        tree_->Branch( "genParticle_mass"	     , &genParticle_mass       );
        tree_->Branch( "genParticle_pdgId"     , &genParticle_pdgId      );
        tree_->Branch( "genParticle_status"    , &genParticle_status     );
        tree_->Branch( "genParticle_isPrompt"  , &genParticle_isPrompt   );
        tree_->Branch( "genParticle_isDirectPromptTauDecayProduct"  , &genParticle_isDirectPromptTauDecayProduct);
        tree_->Branch( "genParticle_isDirectHardProcessTauDecayProductFinalState"  , &genParticle_isDirectHardProcessTauDecayProductFinalState);
        tree_->Branch( "genParticle_fromHardProcessFinalState"  , &genParticle_fromHardProcessFinalState   );
        tree_->Branch( "genParticle_mother"    , &genParticle_mother     );
        tree_->Branch( "genParticle_nMoth"     , &genParticle_nMoth      );
        tree_->Branch( "genParticle_nDau"	     , &genParticle_nDau       );
        tree_->Branch( "genParticle_dau"	     , &genParticle_dau        );
        tree_->Branch( "genParticle_tauvispt"	     , &genParticle_tauvispt        );
        tree_->Branch( "genParticle_tauviseta"	     , &genParticle_tauviseta        );
        tree_->Branch( "genParticle_tauvisphi"	     , &genParticle_tauvisphi       );
        tree_->Branch( "genParticle_tauvismass"	     , &genParticle_tauvismass        );
        tree_->Branch( "genParticle_taudecay"	     , &genParticle_taudecay        );

    } //doGenParticles

    if ( runFlags["doGenEvent"] ){
      /** generator info */
      tree_->Branch( "lheV_pt"	             , &lheV_pt                );
      tree_->Branch( "lheHT"	             , &lheHT                  );
      tree_->Branch( "lheNj"	             , &lheNj                  );
      tree_->Branch( "lheNb"	             , &lheNb                  );
      tree_->Branch( "lheNl"	             , &lheNl                  );
      tree_->Branch( "lheV_mass"           , &lheV_mass              );
      tree_->Branch( "genWeight"	         , &genWeight              );
      tree_->Branch( "genFacWeightUp"	     , &genFacWeightUp         );
      tree_->Branch( "genFacWeightDown"	   , &genFacWeightDown       );
      tree_->Branch( "genRenWeightUp"	     , &genRenWeightUp         );
      tree_->Branch( "genRenWeightDown"	   , &genRenWeightDown       );
      tree_->Branch( "genFacRenWeightUp"	 , &genFacRenWeightUp      );
      tree_->Branch( "genFacRenWeightDown" , &genFacRenWeightDown    );
      tree_->Branch( "qScale"	             , &qScale                 );
      tree_->Branch( "PDF_rms"	           , &PDF_rms                );
      tree_->Branch( "PDF_x"	             , &PDF_x                  );
      tree_->Branch( "PDF_xPDF"	           , &PDF_xPDF               );
      tree_->Branch( "PDF_id"	             , &PDF_id                 );

    } //doGenEvent


    if (runFlags["doGenJets"]) {
      /*-------------------------AK4 GenJets---------------------------*/
      tree_->Branch( "genJetAK4_N"	    , &genJetAK4_N 	  );
      tree_->Branch( "genJetAK4_pt"         , &genJetAK4_pt	  );
      tree_->Branch( "genJetAK4_eta"	    , &genJetAK4_eta	  );
      tree_->Branch( "genJetAK4_mass"	    , &genJetAK4_mass	  );
      tree_->Branch( "genJetAK4_phi"	    , &genJetAK4_phi	  );
      tree_->Branch( "genJetAK4_e"	    , &genJetAK4_e 	  );
      tree_->Branch( "genJetNoNuAK4_pt"	    , &genJetNoNuAK4_pt	  );
      tree_->Branch( "genJetNoNuAK4_mass"   , &genJetNoNuAK4_mass );
      tree_->Branch( "genJetNoNuAK4_e"	    , &genJetNoNuAK4_e    );
      tree_->Branch( "genJetAK8_N"	     , &genJetAK8_N 	       );
      tree_->Branch( "genJetAK8_pt"	     , &genJetAK8_pt	       );
      tree_->Branch( "genJetAK8_eta"	     , &genJetAK8_eta	       );
      tree_->Branch( "genJetAK8_mass"	     , &genJetAK8_mass	       );
      tree_->Branch( "genJetAK8_phi"	     , &genJetAK8_phi	       );
      tree_->Branch( "genJetAK8_e"	     , &genJetAK8_e 	       );
      tree_->Branch( "genJetAK8_prunedmass"  , &genJetAK8_prunedmass   );
      tree_->Branch( "genJetAK8_softdropmass", &genJetAK8_softdropmass );
      tree_->Branch( "genJetAK8_tau1", &genJetAK8_tau1 );
      tree_->Branch( "genJetAK8_tau2", &genJetAK8_tau2 );
      tree_->Branch( "genJetAK8_tau3", &genJetAK8_tau3 );

  } //doGenJets

  /*------------- ------EVENT infos-----------------------------*/
  tree_->Branch("EVENT_event"	 , &EVENT_event     );
  tree_->Branch("EVENT_run"	 , &EVENT_run	    );
  tree_->Branch("EVENT_lumiBlock", &EVENT_lumiBlock );

}

//===================================================================================================================
void NtupleBranches::reset( void ){

  /** genParticle */
  genParticle_N = 0;
  genParticle_pt.clear();
//  genParticle_px.clear();
//  genParticle_py.clear();
//  genParticle_pz.clear();
//  genParticle_e.clear();
  genParticle_eta.clear();
  genParticle_phi.clear();
  genParticle_mass.clear();
  genParticle_pdgId.clear();
  genParticle_isPrompt.clear();
  genParticle_isDirectPromptTauDecayProduct.clear();
  genParticle_fromHardProcessFinalState.clear();
  genParticle_isDirectHardProcessTauDecayProductFinalState.clear();
  genParticle_status.clear();
  genParticle_mother.clear();
  genParticle_nMoth.clear();
  genParticle_nDau.clear();
  genParticle_dau.clear();
  genParticle_tauvispt.clear();
  genParticle_tauviseta.clear();
  genParticle_tauvisphi.clear();
  genParticle_tauvismass.clear();
  genParticle_taudecay.clear();

  /** generator info */
  genWeight   = 0;
  qScale      = 0;
  genFacWeightUp       = 0;
  genFacWeightDown     = 0;
  genRenWeightUp       = 0;
  genRenWeightDown     = 0;
  genFacRenWeightUp    = 0;
  genFacRenWeightDown  = 0;
  PDF_rms = 0;
  PDF_id.clear();
  PDF_x.clear();
  PDF_xPDF.clear();
  lheV_pt = 0;
  lheHT = 0;
  lheNj = 0;
  lheNb = 0;
  lheV_mass = 0;

  /** AK4 genJets*/
  genJetAK4_N = 0;
  genJetAK4_pt.clear();
  genJetAK4_eta.clear();
  genJetAK4_mass.clear();
  genJetAK4_phi.clear();
  genJetAK4_e.clear();
  genJetNoNuAK4_pt.clear();
  genJetNoNuAK4_mass.clear();
  genJetNoNuAK4_e.clear();
  genJetAK8_N = 0;
  genJetAK8_pt              .clear();
  genJetAK8_eta             .clear();
  genJetAK8_mass            .clear();
  genJetAK8_phi             .clear();
  genJetAK8_e	              .clear();
  genJetAK8_prunedmass      .clear();
  genJetAK8_softdropmass    .clear();
  genJetAK8_tau1            .clear();
  genJetAK8_tau2            .clear();
  genJetAK8_tau3            .clear();

  /*------------------------EVENT infos-------------------------*/
  EVENT_event = 0;
  EVENT_run = 0;
  EVENT_lumiBlock = 0;

}
