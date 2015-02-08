#define probe_tree_cxx
// The class definition in probe_tree.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("probe_tree.C")
// Root > T->Process("probe_tree.C","some options")
// Root > T->Process("probe_tree.C+")
//

#include "../include/probe_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include "TClonesArray.h"
#include "TLorentzVector.h"

double probe_tree::GetRhoCh( double eta)
{
	double RhoCorr[7];
	RhoCorr[0]  = 0.0089;	
	RhoCorr[1]  = 0.0062;	
	RhoCorr[2]  = 0.0086;	
	RhoCorr[3]  = 0.0041;	
	RhoCorr[4]  = 0.0113;	
	RhoCorr[5]  = 0.0085;	
	RhoCorr[6]  = 0.0039;	

	double feta = fabs(eta);
	
	if(feta <= 1.0) return RhoCorr[0];
	if(feta > 1.0 && feta <= 1.479) return RhoCorr[1];
	if(feta > 1.479 && feta <= 2.0) return RhoCorr[2];
	if(feta > 2.000 && feta <= 2.2) return RhoCorr[3];
	if(feta > 2.200 && feta <= 2.3) return RhoCorr[4];
	if(feta > 2.300 && feta <= 2.4) return RhoCorr[5];
	if(feta > 2.4) return RhoCorr[6];
	
	return -1;
			
}

double probe_tree::GetRhoNh( double eta)
{
	double RhoCorr[7];

	RhoCorr[0]  = 0.0049;	
	RhoCorr[1]  = 0.0108;	
	RhoCorr[2]  = 0.0019;	
	RhoCorr[3]  = 0.0037;	
	RhoCorr[4]  = 0.0062;	
	RhoCorr[5]  = 0.0130;	
	RhoCorr[6]  = 0.1699;	
	
	double feta = fabs(eta);
	
	if(feta <= 1.0) return RhoCorr[0];
	if(feta > 1.0 && feta <= 1.479) return RhoCorr[1];
	if(feta > 1.479 && feta <= 2.0) return RhoCorr[2];
	if(feta > 2.000 && feta <= 2.2) return RhoCorr[3];
	if(feta > 2.200 && feta <= 2.3) return RhoCorr[4];
	if(feta > 2.300 && feta <= 2.4) return RhoCorr[5];
	if(feta > 2.4) return RhoCorr[6];
			
}

double probe_tree::GetRhoPh( double eta)
{
	double RhoCorr[7];
	RhoCorr[0]  = 0.0894;
	RhoCorr[1]  = 0.0750;
	RhoCorr[2]  = 0.0423;
	RhoCorr[3]  = 0.0561;
	RhoCorr[4]  = 0.0882;
	RhoCorr[5]  = 0.1144;
	RhoCorr[6]  = 0.1684;
	
	double feta = fabs(eta);
	
	if(feta <= 1.0) return RhoCorr[0];
	if(feta > 1.0 && feta <= 1.479) return RhoCorr[1];
	if(feta > 1.479 && feta <= 2.0) return RhoCorr[2];
	if(feta > 2.000 && feta <= 2.2) return RhoCorr[3];
	if(feta > 2.200 && feta <= 2.3) return RhoCorr[4];
	if(feta > 2.300 && feta <= 2.4) return RhoCorr[5];
	if(feta > 2.4) return RhoCorr[6];
			
}

void probe_tree::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).
	
   bool DoId = false;

   TString option = GetOption();
   Init(fChain);
   
   TString FileOut("probe_tree_out_csa14.root");
   if(option.Contains(".root")) FileOut = option;
   outFile = new TFile(FileOut, "recreate");
   
   if(option.Contains("id") || option.Contains("ID") || option.Contains("Id") ) DoId = true;
//
   //hists
    _hists = new TClonesArray("TH1F");
    _2Dhists = new TClonesArray("TH2F");

   new((*_hists)[0]) TH1F("meeg", "DiElectron+Photon Invariant Mass; M_{ee#gamma} (GeV)", 100, 0, 160);
   new((*_hists)[1]) TH1F("muug", "DiMuon+Photon Invariant Mass; M_{#mu#mu#gamma} (GeV)", 100, 0, 160);

   new((*_hists)[2]) TH1F("mee", "DiElectron Invariant Mass; M_{ee} (GeV)", 100, 0, 130);
   new((*_hists)[3]) TH1F("muu", "DiMuon Invariant Mass; M_{#mu#mu} (GeV)", 100, 0, 130);

   new((*_hists)[4]) TH1F("g1_pt", "1st Photon P_{T}; P^{#gamma}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[5]) TH1F("g1_phi", "1st Photon #phi; #phi^{#gamma}", 100, -4, 4);
   new((*_hists)[6]) TH1F("g1_eta", "1st Photon #eta; #eta^{#gamma}", 100, -4, 4);

   new((*_hists)[7]) TH1F("e1_pt", "1st Electron P_{T}; P^{e1}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[8]) TH1F("e1_phi", "1st Electron #phi; #phi^{e1}", 100, -4, 4);
   new((*_hists)[9]) TH1F("e1_eta", "1st Electron #eta; #eta^{e1}", 100, -4, 4);

   new((*_hists)[10]) TH1F("mu1_pt", "1st Muon P_{T}; P^{#mu1}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[11]) TH1F("mu1_phi", "1st Muon #phi; #phi^{#mu1}", 100, -4, 4);
   new((*_hists)[12]) TH1F("mu1_eta", "1st Muon #eta; #eta^{#mu1}", 100, -4, 4);
   
   new((*_hists)[13]) TH1F("l1_pdgid", "PDGID of first lepton; PDGID", 80, -20, 20);
   
   new((*_hists)[14]) TH1F("g1id_pt", "1st ID Photon P_{T}; P^{#gamma}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[15]) TH1F("g1id_phi", "1st ID Photon #phi; #phi^{#gamma}", 100, -4, 4);
   new((*_hists)[16]) TH1F("g1id_eta", "1st ID Photon #eta; #eta^{#gamma}", 100, -4, 4);
   
   new((*_hists)[17]) TH1F("g1iso_pt", "1st ISO Photon P_{T}; P^{#gamma}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[18]) TH1F("g1iso_phi", "1st ISO Photon #phi; #phi^{#gamma}", 100, -4, 4);
   new((*_hists)[19]) TH1F("g1iso_eta", "1st ISO Photon #eta; #eta^{#gamma}", 100, -4, 4);
   
   new((*_hists)[20]) TH1F("g1idiso_pt", "1st ID+ISO Photon P_{T}; P^{#gamma}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[21]) TH1F("g1idiso_phi", "1st ID+ISO Photon #phi; #phi^{#gamma}", 100, -4, 4);
   new((*_hists)[22]) TH1F("g1idiso_eta", "1st ID+ISO Photon #eta; #eta^{#gamma}", 100, -4, 4);
   
   new((*_hists)[23]) TH1F("g1v_pt", "1st eVeto Photon P_{T}; P^{#gamma}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[24]) TH1F("g1v_phi", "1st eVeto Photon #phi; #phi^{#gamma}", 100, -4, 4);
   new((*_hists)[25]) TH1F("g1v_eta", "1st eVeto Photon #eta; #eta^{#gamma}", 100, -4, 4);
   
   new((*_hists)[26]) TH1F("g1idisov_pt", "1st ID+ISO+eVeto Photon P_{T}; P^{#gamma}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[27]) TH1F("g1idisov_phi", "1st ID+ISO+eVeto Photon #phi; #phi^{#gamma}", 100, -4, 4);
   new((*_hists)[28]) TH1F("g1idisov_eta", "1st ID+ISO+eVeto Photon #eta; #eta^{#gamma}", 100, -4, 4);

   new((*_hists)[29]) TH1F("g1_hoe", "1st Photon H/E; H/E_{#gamma1} (GeV)", 100, 0, 0.1);
   new((*_hists)[30]) TH1F("g1_sieie", "1st Photon #sigma_{i#eta i#eta}; #sigma_{i#eta i#eta}", 100, 0., 0.035);
   new((*_hists)[31]) TH1F("g1_pix", "1st Photon - Presence of Pixel Seed; Has Pixel seed?", 10., 0., 3);
   new((*_hists)[32]) TH1F("g1_chiso", "1st Photon CH-Iso; CH-Iso", 100., 0., 4.);
   new((*_hists)[33]) TH1F("g1_nhiso", "1st Photon NH-Iso; NH-Iso", 100., 0., 4.);
   new((*_hists)[34]) TH1F("g1_phiso", "1st Photon PH-Iso; PH-Iso", 100., 0., 4.);  

   new((*_hists)[35]) TH1F("jet1_pt", "1st Jet Pt; P^{Jet1}_{T} (GeV)", 100., 0., 150.);   
   new((*_hists)[36]) TH1F("m_gg", "Diphoton Invariant Mass; M_{#gamma#gamma} (GeV)", 100., -90., 155.);   
   new((*_hists)[37]) TH1F("m_gidgid", "Diphoton Invariant Mass - Both ID; M_{#gamma#gamma} (GeV)", 100., 90., 155.);   
   new((*_hists)[38]) TH1F("m_gidisogidiso", "Diphoton Invariant Mass - Both ID+ISO; M_{#gamma#gamma} (GeV)", 100., 90., 155.);   

   new((*_hists)[39]) TH1F("g1_conv", "1st Photon - Conversion Safe Veto; CSV", 10., 0., 3);
     
   new((*_hists)[41]) TH1F("g2_pt", "2nd Photon P_{T}; P^{#gamma}_{T} (GeV)", 100, 0, 150);
   new((*_hists)[42]) TH1F("g2_phi", "2nd Photon #phi; #phi^{#gamma}", 100, -4, 4);
   new((*_hists)[43]) TH1F("g2_eta", "2nd Photon #eta; #eta^{#gamma}", 100, -4, 4);

   new((*_2Dhists)[0]) TH2F("dre1g_e2g", "DR(e1,g) vs DR(e2,g); DR(e1,g); DR(e2,g)", 100, 0., 2., 100, 0., 10.);
   new((*_2Dhists)[1]) TH2F("drm1g_m2g", "DR(m1,g) vs DR(m2,g); DR(m1,g); DR(m2,g)", 100, 0., 2., 100, 0., 10.);
      
}

void probe_tree::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t probe_tree::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either probe_tree::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

	//probe_tree::GetEntry(entry);
	int entries = fChain->GetEntriesFast();
	if(entry > entries) return 0;
		fChain->GetEntry(entry);
	
	if(entry%100 == 0)	cout << entry <<  " " << endl;
	if(v_photon1->Pt() < 5 ) return 1;
	
	// cout << mllg << endl;
		 // cout << v_photon1->Pt() << " ";
		 //      	 cout << v_lepton1->Pt() << " ";
		 //    	   	 cout << v_jet1->Pt() << endl << endl;
	  
		
	if( v_photon1->Pt() > 10 ){
		((TH1F*)(_hists->At(4)))->Fill(v_photon1->Pt());
		((TH1F*)(_hists->At(5)))->Fill(v_photon1->Phi());
		((TH1F*)(_hists->At(6)))->Fill(v_photon1->Eta());	
	}

	if( v_photon2->Pt() > 10 ){
		((TH1F*)(_hists->At(41)))->Fill(v_photon2->Pt());
		((TH1F*)(_hists->At(42)))->Fill(v_photon2->Phi());
		((TH1F*)(_hists->At(43)))->Fill(v_photon2->Eta());	
	}

	if(fabs(pdgid1) == 11 && v_lepton1->Pt() > 10){
		((TH1F*)(_hists->At(0)))->Fill(mllg);
		((TH1F*)(_hists->At(2)))->Fill(mll);
		((TH1F*)(_hists->At(7)))->Fill(v_lepton1->Pt());
		if(v_lepton1->Pt() > 10) {
			((TH1F*)(_hists->At(8)))->Fill(v_lepton1->Phi());
			((TH1F*)(_hists->At(9)))->Fill(v_lepton1->Eta());
		}
	}
	if(fabs(pdgid1) == 13 && v_lepton1->Pt() > 10){
		((TH1F*)(_hists->At(1)))->Fill(mllg);
		((TH1F*)(_hists->At(3)))->Fill(mll);
		((TH1F*)(_hists->At(10)))->Fill(v_lepton1->Pt());
		if(v_lepton1->Pt() > 10) {
			((TH1F*)(_hists->At(11)))->Fill(v_lepton1->Phi());
			((TH1F*)(_hists->At(12)))->Fill(v_lepton1->Eta());		
		}
	}
	
	((TH1F*)(_hists->At(13)))->Fill(pdgid1);
	
	bool IsPhoId = true;
	if(pho_HoE > 0.020) IsPhoId = false;
	if(pho_sietaieta > 0.0099) IsPhoId = false;
	if(fabs(v_photon1->Eta()) > 1.45)  IsPhoId = false;
	
	if(IsPhoId){
		((TH1F*)(_hists->At(14)))->Fill(v_photon1->Pt());
		if( v_photon1->Pt() > 5 ){
			((TH1F*)(_hists->At(15)))->Fill(v_photon1->Phi());
			((TH1F*)(_hists->At(16)))->Fill(v_photon1->Eta());	
		}
	}
	
	bool IsPhoIso = true;
	double medium_charged = 2.62;
	double medium_neutral = 2.69 + 0.0023*v_photon1->Pt();
	double medium_photon  = 1.35 + 0.0004*v_photon1->Pt();
	double pho_charged = max(pho_chIso - probe_tree::GetRhoCh(v_photon1->Eta()) , 0.);
	double pho_neutral = max(pho_nhIso - probe_tree::GetRhoNh(v_photon1->Eta()) , 0.);
	double pho_photon  = max(pho_phIso - probe_tree::GetRhoPh(v_photon1->Eta()) , 0.);
	if(pho_charged > medium_charged) IsPhoIso = false;
	if(pho_neutral > medium_neutral) IsPhoIso = false;
	if(pho_photon  > medium_photon ) IsPhoIso = false;
	if(fabs(v_photon1->Eta()) > 1.45)  IsPhoIso = false;
	
	if(IsPhoIso){
		((TH1F*)(_hists->At(17)))->Fill(v_photon1->Pt());
		if( v_photon1->Pt() > 5 ){
			((TH1F*)(_hists->At(18)))->Fill(v_photon1->Phi());
			((TH1F*)(_hists->At(19)))->Fill(v_photon1->Eta());	
		}
	}

	if(IsPhoIso && IsPhoId){
		((TH1F*)(_hists->At(20)))->Fill(v_photon1->Pt());
		if( v_photon1->Pt() > 5 ){
			((TH1F*)(_hists->At(21)))->Fill(v_photon1->Phi());
			((TH1F*)(_hists->At(22)))->Fill(v_photon1->Eta());	
		}
	}

	if(IsPhoIso && IsPhoId && pho_hasPixelSeed==0){
		((TH1F*)(_hists->At(26)))->Fill(v_photon1->Pt());
		if( v_photon1->Pt() > 5 ){
			((TH1F*)(_hists->At(27)))->Fill(v_photon1->Phi());
			((TH1F*)(_hists->At(28)))->Fill(v_photon1->Eta());	
		}
	}

	if(pho_hasPixelSeed==0){
		((TH1F*)(_hists->At(23)))->Fill(v_photon1->Pt());
		if( v_photon1->Pt() > 5 ){
			((TH1F*)(_hists->At(24)))->Fill(v_photon1->Phi());
			((TH1F*)(_hists->At(25)))->Fill(v_photon1->Eta());	
		}
	}
	
	((TH1F*)(_hists->At(29)))->Fill(pho_HoE);
	((TH1F*)(_hists->At(30)))->Fill(pho_sietaieta);
	((TH1F*)(_hists->At(31)))->Fill(pho_hasPixelSeed);
	((TH1F*)(_hists->At(32)))->Fill(pho_charged);
	((TH1F*)(_hists->At(33)))->Fill(pho_neutral);
	((TH1F*)(_hists->At(34)))->Fill(pho_photon);
	((TH1F*)(_hists->At(39)))->Fill(pho_passElecVeto);
	
	
	TLorentzVector l1(v_lepton1->Px(), v_lepton1->Py(), v_lepton1->Pz(), v_lepton1->E());
	TLorentzVector l2(v_lepton2->Px(), v_lepton2->Py(), v_lepton2->Pz(), v_lepton2->E());
	TLorentzVector g1;// = 0;
	g1.SetPtEtaPhiE(v_photon1->Pt(), v_photon1->Eta(), v_photon1->Phi(), v_photon1->E());
	TLorentzVector g2;// = 0;
	g1.SetPtEtaPhiE(v_photon2->Pt(), v_photon2->Eta(), v_photon2->Phi(), v_photon2->E());
//	TLorentzVector g2(v_photon2->Px(), v_photon2->Py(), v_photon2->Pz(), v_photon2->E());
	if(v_photon1->Pt() > 10 && v_lepton1->Pt() > 10 && v_lepton2->Pt() > 10){
		double dr1 = l1.DeltaR(g1);
		double dr2 = l2.DeltaR(g1);
		if(fabs(pdgid1) == 11 && fabs(pdgid2) == 11) ((TH2F*)(_2Dhists->At(0)))->Fill(dr1, dr2);
		if(fabs(pdgid1) == 13 && fabs(pdgid2) == 13) ((TH2F*)(_2Dhists->At(1)))->Fill(dr1, dr2);
	}
	if(v_photon1->Pt() > 10 && v_photon2->Pt() > 10)
	{
		TLorentzVector Hgg = g1 + g2;
		//(v_photon1->Px()+v_photon2->Px(), v_photon1->Py()+v_photon2->Py(),v_photon1->Pz()+v_photon2->Pz(), v_photon1->E()+v_photon2->E());
//		if(entry%100 == 0)      cout << "Hgg mass " << Hgg.M() << endl;
		((TH1F*)(_hists->At(36)))->Fill(Hgg.M());
	}

	if(v_jet1->Pt() > 5)  ((TH1F*)(_hists->At(35)))->Fill(v_jet1->Pt());
	
   return kTRUE;
}

void probe_tree::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void probe_tree::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

	 outFile->Write();
	 outFile->Close();
}
