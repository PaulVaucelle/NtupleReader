#define LLTopAna_cxx
#include "LLTopAna.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TH1F.h"
#include "TH2F.h"
#include "HistogramManager.h"
#include "TLorentzVector.h"
#include "TRandom.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
void SetSebStyle()
{
 gStyle->SetTitleFillColor(42);
 gStyle->SetTitleFont(1);
 gStyle->SetStatColor(29);
 gStyle->SetCanvasColor(25);   
 gStyle->SetOptStat(1111111);
 gStyle->SetHistFillColor(5);
}

void SaveInFile(TH1* ahisto, TFile* afile)
{
 if (!ahisto) { std::cout << "!! no histo !!" << std::endl; return ;}
 TDirectory* current = gDirectory ;
 afile->cd();
 ahisto->Write();
 current->cd();
}

void LLTopAna::Loop(int aNN, float aTagCut, float aPtMin, float aPtMax, 
                float aEtaMin, float aEtaMax, float aFreeCut, int aIntCut, 
		TString afilename)
{

      int    NN           = aNN;      // 0/1 JP, 2/3 TC, 4/5 SSV, 6 CSV, 7 SL
  float  TagCut       = aTagCut;  // tag cut
  float  PtMin        = aPtMin;   // pt jet min
  float  PtMax        = aPtMax;   // pt jet max
  float  EtaMin       = aEtaMin;  // eta jet min
  float  EtaMax       = aEtaMax;  // eta jet max
  float  FreeCut      = aFreeCut; 
  int    IntCut       = aIntCut; 
  TString  filename   = afilename;//   In a ROOT session, you can do:
//      root> .L LLTopAna.C
//      root> LLTopAna t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch



//$$
  float HTcut =  aTagCut; 
//   float dRcut =  FreeCut; 
//$$

///////////////////////////////////////////////////////////////////
 
//$$
//$$ TH1F::SetDefaultSumw2(kTRUE);
//$$

//**********************************
// Histograms
//**********************************

 TH1F* hDataAll_nZMu     = new TH1F("hDataAll_nZMu","",11,-0.5,10.5);
 TH1F* hDataAll_Jet_njet = new TH1F("hDataAll_Jet_njet","",31,0,30);
 TH1F* hDataAll_Jet_pt   = new TH1F("hDataAll_Jet_pt","",100,0.,1000.);
 TH1F* hDataAll_Jet_eta	 = new TH1F("hDataAll_Jet_eta","",50,-2.5,2.5);
 TH1F* hDataAll_Jet_phi	 = new TH1F("hDataAll_Jet_phi","",66,-3.3,3.3);
 TH1F* hDataAll_Jet_HT   = new TH1F("hDataAll_Jet_HT","",100,0.,2500.);
 TH1F* hDataAll_nMu      = new TH1F("hDataAll_nMu","",11,-0.5,10.5);
 TH1F* hDataAll_nMuGlob  = new TH1F("hDataAll_nMuGlob","",11,-0.5,10.5);
 TH1F* hDataAll_Mu_ptmax = new TH1F("hDataAll_Mu_ptmax","",100,0.,400.);
 TH1F* hDataAll_nMuGlob_ptGT28  = new TH1F("hDataAll_nMuGlob_ptGT28","",11,-0.5,10.5);

 TH1F* hData_Mu_dVr      = new TH1F("hData_Mu_dVr","",100,0.,1.);
 TH1F* hData_Mu_dVz      = new TH1F("hData_Mu_dVz","",100,-1.,1.);
 TH1F* hData_Mu_pt	 = new TH1F("hData_Mu_pt","",100,0.,400.);
 TH1F* hData_Mu_eta	 = new TH1F("hData_Mu_eta","",50,-2.5,2.5);
 TH1F* hData_Mu_phi	 = new TH1F("hData_Mu_phi","",66,-3.3,3.3);
 TH1F* hData_nMuRec      = new TH1F("hData_nMuRec","",11,-0.5,10.5);
 TH1F* hData_MuMu_mass   = new TH1F("hData_MuMu_mass","",100,0.,400.);
 TH1F* hData_Mu_pt1	 = new TH1F("hData_Mu_pt1","",100,0.,400.);
 TH1F* hData_Mu_pt2	 = new TH1F("hData_Mu_pt2","",100,0.,400.);

 TH1F* hData_nPV        = new TH1F("hData_nPV","",81,-0.5,80.5);
 TH1F* hData_PVx        = new TH1F("hData_PVx","",100,-0.4,0.4);
 TH1F* hData_PVy        = new TH1F("hData_PVy","",100,-0.4,0.4);
 TH1F* hData_PVz        = new TH1F("hData_PVz","",100,-20.,20.);
 TH1F* hGen_PVx	        = new TH1F("hGen_PVx","",200,-0.4,0.4);
 TH1F* hGen_PVy	        = new TH1F("hGen_PVy","",200,-0.4,0.4);
 TH1F* hGen_PVz	        = new TH1F("hGen_PVz","",100,-20.,20.);
 TH1F* hDataGen_PV_dx	= new TH1F("hDataGen_PV_dx","",100,-0.05,0.05);
 TH1F* hDataGen_PV_dy	= new TH1F("hDataGen_PV_dy","",100,-0.05,0.05);
 TH1F* hDataGen_PV_dz	= new TH1F("hDataGen_PV_dz","",100,-0.05,0.05);

 TH1F* hGen_smu_test	= new TH1F("hGen_smu_test","",3,-1.5,1.5);
 TH1F* hGen_smu_testM   = new TH1F("hGen_smu_testM","",100,-0.5,0.5);
 TH1F* hGen_smu_pt      = new TH1F("hGen_smu_pt","",50,0.,1000.);
 TH1F* hGen_smu_eta     = new TH1F("hGen_smu_eta","",50,-5.,5.);
 TH1F* hGen_smusmu_DR   = new TH1F("hGen_smusmu_DR","",100,0.,5.);
 TH1F* hGen_smusmu_dphi = new TH1F("hGen_smusmu_dphi","",33,0.,3.3);

 TH1F* hGen_muon	= new TH1F("hGen_muon","",10,-0.5,9.5);
 TH1F* hGen_muon_pt     = new TH1F("hGen_muon_pt","",50,0.,500.);
 TH1F* hGen_muon_eta    = new TH1F("hGen_muon_eta","",50,-2.5,2.5);
 TH1F* hGen_mumu_mass   = new TH1F("hGen_mumu_mass","",100,0.,400.);
 TH1F* hGen_muonsmu_DR   = new TH1F("hGen_muonsmu_DR","",100,0.,5.);
 TH1F* hGen_muonsmu_dphi = new TH1F("hGen_muonsmu_dphi","",33,0.,3.3);

 TH1F* hGen_neu         = new TH1F("hGen_neu","",5,-0.5,4.5);
 TH1F* hGen_neu_pt      = new TH1F("hGen_neu_pt","",50,0.,1000.);
 TH1F* hGen_neu_eta     = new TH1F("hGen_neu_eta","",50,-5.,5.);
 TH1F* hGen_neuneu_DR   = new TH1F("hGen_neuneu_dR","",33,0.,3.3);
 TH1F* hGen_neuneu_dphi = new TH1F("hGen_neuneu_dphi","",33,0.,3.3);
 TH1F* hGen_neusmu_DR   = new TH1F("hGen_neusmu_dR","",33,0.,3.3);
 TH1F* hGen_neusmu_dphi = new TH1F("hGen_neusmu_dphi","",33,0.,3.3);
 TH1F* hGen_neumu_DR    = new TH1F("hGen_neumu_DR","",100,0.,5.);
 TH1F* hGen_neumu_dphi  = new TH1F("hGen_neumu_dphi","",33,0.,3.3);
 TH1F* hGen_neu_testE   = new TH1F("hGen_neu_testE","",100,-0.5,0.5);
 TH1F* hGen_neuqtop_DR  = new TH1F("hGen_neuqtop_dR","",33,0.,3.3);
 TH1F* hGen_neuqtop_dphi= new TH1F("hGen_neuqtop_dphi","",33,0.,3.3);
 TH1F* hGen_neuqtop_deta= new TH1F("hGen_neuqtop_deta","",33,0.,3.3);
 TH1F* hGen_neulepW_DR  = new TH1F("hGen_neulepW_dR","",33,0.,3.3);
 TH1F* hGen_neulepW_dphi= new TH1F("hGen_neulepW_dphi","",33,0.,3.3);
 TH1F* hGen_neulepW_deta= new TH1F("hGen_neulepW_deta","",33,0.,3.3);
 TH1F* hGen_neusq_DR    = new TH1F("hGen_neusq_dR","",33,0.,3.3);
 TH1F* hGen_neusq_dphi  = new TH1F("hGen_neusq_dphi","",33,0.,3.3);
 TH1F* hGen_neusq_deta  = new TH1F("hGen_neusq_deta","",33,0.,3.3);

 TH1F* hGen_top         = new TH1F("hGen_top","",5,-0.5,4.5);
 TH1F* hGen_top_r       = new TH1F("hGen_top_r","",100,0.,100.);
 TH1F* hGen_top_z       = new TH1F("hGen_top_z","",100,0.,200.);
 TH1F* hGen_top_d       = new TH1F("hGen_top_d","",100,0.,1000.);
 TH1F* hGen_top_pt      = new TH1F("hGen_top_pt","",50,0.,500.);
 TH1F* hGen_top_eta     = new TH1F("hGen_top_eta","",50,-5.,5.);
 TH1F* hGen_top_bg      = new TH1F("hGen_top_bg","",50,0.,20.);
 TH1F* hGen_top_ctau    = new TH1F("hGen_top_ctau","",100,0.,200.);
 TH1F* hGen_top_Vphi    = new TH1F("hGen_top_Vphi","",66,-3.3,3.3);
 TH1F* hGen_top_dVphi   = new TH1F("hGen_top_dVphi","",33,0.,3.3);
 TH1F* hGen_toptop_DR   = new TH1F("hGen_toptop_DR","",100,0.,5.);
 TH1F* hGen_toptop_dV   = new TH1F("hGen_toptop_dV","",100,0.,200.);
 TH1F* hGen_toptop_dVphi = new TH1F("hGen_toptop_dVphi","",33,0.,3.3);

 TH1F* hGen_qtop	= new TH1F("hGen_qtop","",10,-0.5,9.5);
 TH1F* hGen_qtop_pt     = new TH1F("hGen_qtop_pt","",50,0.,500.);
 TH1F* hGen_qtop_eta    = new TH1F("hGen_qtop_eta","",50,-2.5,2.5);
 TH1F* hGen_qtop_dV     = new TH1F("hGen_qtop_dV","",100,0.,0.01);

 TH1F* hGen_genb	= new TH1F("hGen_genb","",10,-0.5,9.5);
 TH1F* hGen_genc	= new TH1F("hGen_genc","",10,-0.5,9.5);
 TH1F* hGen_genb_test	= new TH1F("hGen_genb_test","",9,-4.5,4.5);
 TH1F* hGen_genc_test	= new TH1F("hGen_genc_test","",9,-4.5,4.5);

 TH1F* hGen_lepW	= new TH1F("hGen_lepW","",10,-0.5,9.5);
 TH1F* hGen_lepW_pt     = new TH1F("hGen_lepW_pt","",50,0.,500.);
 TH1F* hGen_lepW_eta    = new TH1F("hGen_lepW_eta","",50,-2.5,2.5);
 TH1F* hGen_lepW_dV     = new TH1F("hGen_lepW_dV","",100,0.,0.01);

 TH1F* hGen_stoq 	= new TH1F("hGen_stoq","",10,-0.5,9.5);
 TH1F* hGen_stoq_pt	= new TH1F("hGen_stoq_pt","",50,0.,500.);
 TH1F* hGen_stoq_eta	= new TH1F("hGen_stoq_eta","",50,-2.5,2.5);
 TH1F* hGen_stoq_dV     = new TH1F("hGen_stoq_dV","",100,0.,0.01);

 TH1F* hData_MET           = new TH1F("hData_MET","",100,0.,1000.);
 TH1F* hData_MET_phi	   = new TH1F("hData_MET_phi","",66,-3.3,3.3);

 TH1F* hData_Jet_njet      = new TH1F("hData_Jet_njet","",20,-0.5,19.5);
//  TH1F* hData_Jet_pt        = new TH1F("hData_Jet_pt","",100,0.,1000.);
 TH1F* hData_Jet_eta	   = new TH1F("hData_Jet_eta","",50,-2.5,2.5);
 TH1F* hData_Jet_phi	   = new TH1F("hData_Jet_phi","",66,-3.3,3.3);
 TH1F* hData_Jet_pt1       = new TH1F("hData_Jet_pt1","",100,0.,1000.);
 TH1F* hData_Jet_pt2       = new TH1F("hData_Jet_pt2","",100,0.,1000.);
 TH1F* hData_Jet_dRmu      = new TH1F("hData_Jet_dRmu","",66,0.,3.3);
 TH1F* hData_Jet_pt_test   = new TH1F("hData_Jet_pt_test","",100,0.,1000.);
 TH1F* hData_Jet_ntrksel   = new TH1F("hData_Jet_ntrksel","",41,-0.5,40.5);
 TH1F* hData_Jet_njet_forLLP = new TH1F("hData_Jet_njet_forLLP","",20,-0.5,19.5);

 TH1F* hData_Jetseed_pt       = new TH1F("hData_Jetseed_pt","",100,0.,1000.);
 TH1F* hData_Jetseed_eta      = new TH1F("hData_Jetseed_eta","",50,-2.5,2.5);
 TH1F* hData_Jet_njet1     = new TH1F("hData_Jet_njet1","",21,-0.5,20.5);
 TH1F* hData_Jet_njet2     = new TH1F("hData_Jet_njet2","",21,-0.5,20.5);
 TH1F* hData_Jet1_METpt    = new TH1F("hData_Jet1_METpt","",100,0.,2.);
 TH1F* hData_Jet1_METdphi  = new TH1F("hData_Jet1_METdphi","",33,0.,3.3);
 TH1F* hData_Jet1_ntrksel  = new TH1F("hData_Jet1_ntrksel","",41,-0.5,40.5);

 TH1F* hData_axis12_dR  = new TH1F("hData_axis12_dR","",33,0.,3.3);
 TH1F* hData_axis12_dphi= new TH1F("hData_axis12_dphi","",33,0.,3.3);
 TH1F* hData_axis12_deta= new TH1F("hData_axis12_deta","",33,0.,3.3);

 TH1F* hData_museed_pt      = new TH1F("hData_museed_pt","",100,0.,400.);
 TH1F* hData_museed_eta     = new TH1F("hData_museed_eta","",50,-2.5,2.5);
 TH1F* hData_museed_dphiMET = new TH1F("hData_museed_dphiMET","",33,0.,3.3);
 TH1F* hData_museed_MET     = new TH1F("hData_museed_MET","",100,0.,400.);
 TH1F* hDataGen_museed_dR   = new TH1F("hDataGen_museed_dR","",33,0.,3.3);

 TH1F* hData_elseed_pt	    = new TH1F("hData_elseed_pt","",100,0.,400.);
 TH1F* hData_elseed_eta	    = new TH1F("hData_elseed_eta","",50,-2.5,2.5);
 TH1F* hData_elseed_dphiMET = new TH1F("hData_elseed_dphiMET","",33,0.,3.3);
 TH1F* hData_elseed_MET	    = new TH1F("hData_elseed_MET","",100,0.,400.);
 TH1F* hDataGen_elseed_dR   = new TH1F("hDataGen_elseed_dR","",33,0.,3.3);

 TH1F* hDataGen_LLP_dR        = new TH1F("hDataGen_LLP_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP1_dR       = new TH1F("hDataGen_LLP1_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP1_dphi     = new TH1F("hDataGen_LLP1_dphi","",33,0.,3.3);
 TH1F* hDataGen_LLP1_deta     = new TH1F("hDataGen_LLP1_deta","",33,0.,3.3);
 TH1F* hDataGen_LLP2_sym_dR   = new TH1F("hDataGen_LLP2_sym_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP2_sym_dphi = new TH1F("hDataGen_LLP2_sym_dphi","",33,0.,3.3);
 TH1F* hDataGen_LLP2_dR       = new TH1F("hDataGen_LLP2_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP2_dphi     = new TH1F("hDataGen_LLP2_dphi","",33,0.,3.3);
 TH1F* hDataGen_LLP2_deta     = new TH1F("hDataGen_LLP2_deta","",33,0.,3.3);
 TH1F* hDataGen_Jet_dpt       = new TH1F("hDataGen_Jet_dpt" ,"",100,-1.,1.);
 TH1F* hDataGen_Jet_deta      = new TH1F("hDataGen_Jet_deta","",100,-1.,1.);
 TH1F* hDataGen_Jet_dphi      = new TH1F("hDataGen_Jet_dphi","",100,-1.,1.);
 TH1F* hDataGen_Jet_pt        = new TH1F("hDataGen_Jet_pt","",100,0.,1000.);
 TH1F* hDataGen_Jet_eta	      = new TH1F("hDataGen_Jet_eta","",50,-2.5,2.5);

 TH1F* hDataGen_seed_dR            = new TH1F("hDataGen_seed_dR","",33,0.,3.3);
 TH1F* hDataGen_seed_deta          = new TH1F("hDataGen_seed_deta","",33,0.,3.3);
 TH1F* hDataGen_seed_dphi          = new TH1F("hDataGen_seed_dphi","",33,0.,3.3);
 TH1F* hDataGen_seed_dR1GT15_dR    = new TH1F("hDataGen_seed_dR1GT15_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP1_dRseedGT15_dR = new TH1F("hDataGen_LLP1_dRseedGT15_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP1_dR2GT15_dR    = new TH1F("hDataGen_LLP1_dR2GT15_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP2_dR1GT15_dR    = new TH1F("hDataGen_LLP2_dR1GT15_dR","",33,0.,3.3);

 TH1F* hDataGen_seed_dRLT15_ntrk     = new TH1F("hDataGen_seed_dRLT15_ntrk","",51,-0.5,50.5);
 TH1F* hDataGen_seed_dRLT15_ntrksel  = new TH1F("hDataGen_seed_dRLT15_ntrksel","",51,-0.5,50.5);
 TH1F* hDataGen_seed_dRLT15_ntrkbdt  = new TH1F("hDataGen_seed_dRLT15_ntrkbdt","",51,-0.5,50.5);
 TH1F* hDataGen_seed_dRLT15_trkQ     = new TH1F("hDataGen_seed_dRLT15_trkQ","",51,-25.5,25.5);
 TH1F* hDataGen_seed_dRLT15_trkPt    = new TH1F("hDataGen_seed_dRLT15_trkPt","",100,0.,1000.);
 TH1F* hDataGen_seed_dRLT15_trkPtRel = new TH1F("hDataGen_seed_dRLT15_trkPtRel","",100,0.,5.);

 TH1F* hDataGen_seed_dRGT15_ntrk     = new TH1F("hDataGen_seed_dRGT15_ntrk","",51,-0.5,50.5);
 TH1F* hDataGen_seed_dRGT15_ntrksel  = new TH1F("hDataGen_seed_dRGT15_ntrksel","",51,-0.5,50.5);
 TH1F* hDataGen_seed_dRGT15_ntrkbdt  = new TH1F("hDataGen_seed_dRGT15_ntrkbdt","",51,-0.5,50.5);
 TH1F* hDataGen_seed_dRGT15_trkQ     = new TH1F("hDataGen_seed_dRGT15_trkQ","",51,-25.5,25.5);
 TH1F* hDataGen_seed_dRGT15_trkPt    = new TH1F("hDataGen_seed_dRGT15_trkPt","",100,0.,1000.);
 TH1F* hDataGen_seed_dRGT15_trkPtRel = new TH1F("hDataGen_seed_dRGT15_trkPtRel","",100,0.,5.);

 TH1F* hData_nTk        = new TH1F("hData_nTk","",501,-0.5,500.5);

 TH1F* hSimGen_dq        = new TH1F("hSimGen_dq","",5,-2.5,2.5);
 TH1F* hSimGen_dpt       = new TH1F("hSimGen_dpt","",100,-0.1,0.1);
 TH1F* hSimGen_deta      = new TH1F("hSimGen_deta","",100,-0.1,0.1);
 TH1F* hSimGen_dphi      = new TH1F("hSimGen_dphi","",100,-0.1,0.1);
 TH1F* hSimGen_dpt_cut   = new TH1F("hSimGen_dpt_cut","",100,-0.1,0.1);
 TH1F* hSimGen_deta_cut  = new TH1F("hSimGen_deta_cut","",100,-0.1,0.1);
 TH1F* hSimGen_dphi_cut  = new TH1F("hSimGen_dphi_cut","",100,-0.1,0.1);

 TH1F* hTkGen_dq	 = new TH1F("hTkGen_dq","",5,-2.5,2.5);
 TH1F* hTkGen_dpt        = new TH1F("hTkGen_dpt","",200,-1.0,1.0);
 TH1F* hTkGen_deta       = new TH1F("hTkGen_deta","",100,-0.5,0.5);
 TH1F* hTkGen_dphi       = new TH1F("hTkGen_dphi","",100,-0.1,0.1);
 TH1F* hTkGen_dphiraw    = new TH1F("hTkGen_dphiraw","",100,-0.1,0.1);

 TH1F* hTkGen_dpt_ptLT4      	  = new TH1F("hTkGen_dpt_ptLT4","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_ptGT4      	  = new TH1F("hTkGen_dpt_ptGT4","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_etaLT08    	= new TH1F("hTkGen_dpt_etaLT08","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_etaGT08    	= new TH1F("hTkGen_dpt_etaGT08","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_drsigLT170 = new TH1F("hTkGen_dpt_drsigLT170","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_drsigGT170 = new TH1F("hTkGen_dpt_drsigGT170","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_inJet      	  = new TH1F("hTkGen_dpt_inJet","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_NOTinJet     = new TH1F("hTkGen_dpt_NOTinJet","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_hitLE15    	= new TH1F("hTkGen_dpt_hitLE15","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_hitGT15    	= new TH1F("hTkGen_dpt_hitGT15","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_ctauLT9    	= new TH1F("hTkGen_dpt_ctauLT9","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_ctauGT9    	= new TH1F("hTkGen_dpt_ctauGT9","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_hitLE10    	= new TH1F("hTkGen_dpt_hitLE10","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_11hit13    	= new TH1F("hTkGen_dpt_11hit13","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_14hit17    	= new TH1F("hTkGen_dpt_14hit17","",200,-1.0,1.0);
 TH1F* hTkGen_dpt_hitGE18    	= new TH1F("hTkGen_dpt_hitGE18","",200,-1.0,1.0);
 
 TH1F* hTkGen_deta_ptLT4           = new TH1F("hTkGen_deta_ptLT4","",100,-0.5,0.5);
 TH1F* hTkGen_deta_ptGT4           = new TH1F("hTkGen_deta_ptGT4","",100,-0.5,0.5);
 TH1F* hTkGen_deta_etaLT08       = new TH1F("hTkGen_deta_etaLT08","",100,-0.5,0.5);
 TH1F* hTkGen_deta_etaGT08       = new TH1F("hTkGen_deta_etaGT08","",100,-0.5,0.5);
 TH1F* hTkGen_deta_drsigLT170 = new TH1F("hTkGen_deta_drsigLT170","",100,-0.5,0.5);
 TH1F* hTkGen_deta_drsigGT170 = new TH1F("hTkGen_deta_drsigGT170","",100,-0.5,0.5);
 TH1F* hTkGen_deta_inJet           = new TH1F("hTkGen_deta_inJet","",100,-0.5,0.5);
 TH1F* hTkGen_deta_NOTinJet     = new TH1F("hTkGen_deta_NOTinJet","",100,-0.5,0.5);
 TH1F* hTkGen_deta_hitLE15       = new TH1F("hTkGen_deta_hitLE15","",100,-0.5,0.5);
 TH1F* hTkGen_deta_hitGT15       = new TH1F("hTkGen_deta_hitGT15","",100,-0.5,0.5);
 TH1F* hTkGen_deta_ctauLT9       = new TH1F("hTkGen_deta_ctauLT9","",100,-0.5,0.5);
 TH1F* hTkGen_deta_ctauGT9       = new TH1F("hTkGen_deta_ctauGT9","",100,-0.5,0.5);
 TH1F* hTkGen_deta_hitLE10       = new TH1F("hTkGen_deta_hitLE10","",100,-0.5,0.5);
 TH1F* hTkGen_deta_11hit13       = new TH1F("hTkGen_deta_11hit13","",100,-0.5,0.5);
 TH1F* hTkGen_deta_14hit17       = new TH1F("hTkGen_deta_14hit17","",100,-0.5,0.5);
 TH1F* hTkGen_deta_hitGE18       = new TH1F("hTkGen_deta_hitGE18","",100,-0.5,0.5);

 TH1F* hTkGen_dphi_ptLT4           = new TH1F("hTkGen_dphi_ptLT4","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_ptGT4           = new TH1F("hTkGen_dphi_ptGT4","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_etaLT08       = new TH1F("hTkGen_dphi_etaLT08","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_etaGT08       = new TH1F("hTkGen_dphi_etaGT08","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_drsigLT170 = new TH1F("hTkGen_dphi_drsigLT170","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_drsigGT170 = new TH1F("hTkGen_dphi_drsigGT170","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_inJet           = new TH1F("hTkGen_dphi_inJet","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_NOTinJet     = new TH1F("hTkGen_dphi_NOTinJet","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_hitLE15       = new TH1F("hTkGen_dphi_hitLE15","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_hitGT15       = new TH1F("hTkGen_dphi_hitGT15","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_ctauLT9       = new TH1F("hTkGen_dphi_ctauLT9","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_ctauGT9       = new TH1F("hTkGen_dphi_ctauGT9","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_hitLE10       = new TH1F("hTkGen_dphi_hitLE10","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_11hit13       = new TH1F("hTkGen_dphi_11hit13","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_14hit17       = new TH1F("hTkGen_dphi_14hit17","",100,-0.1,0.1);
 TH1F* hTkGen_dphi_hitGE18       = new TH1F("hTkGen_dphi_hitGE18","",100,-0.1,0.1);
       
 TH1F* hTkSim_dq         = new TH1F("hTkSim_dq","",5,-2.5,2.5);
 TH1F* hTkSim_dpt        = new TH1F("hTkSim_dpt","",100,-0.2,0.2);
 TH1F* hTkSim_deta       = new TH1F("hTkSim_deta","",100,-0.2,0.2);
 TH1F* hTkSim_dphiraw    = new TH1F("hTkSim_dphiraw","",100,-0.2,0.2);
 TH1F* hTkSim_dphi       = new TH1F("hTkSim_dphi","",100,-0.2,0.2);
 TH1F* hTkSim_dpt_cut    = new TH1F("hTkSim_dpt_cut","",100,-0.2,0.2);
 TH1F* hTkSim_deta_cut   = new TH1F("hTkSim_deta_cut","",100,-0.2,0.2);
 TH1F* hTkSim_dphi_cut   = new TH1F("hTkSim_dphi_cut","",100,-0.2,0.2);

 TH1F* hTkAll            = new TH1F("hTkAll","",201,-0.5,200.5);
 TH1F* hTkSim            = new TH1F("hTkSim","",101,-0.5,100.5);
 TH1F* hTkSim_pt         = new TH1F("hTkSim_pt","",100,0.,100.);
 TH1F* hTkSim_eta        = new TH1F("hTkSim_eta","",50,-2.5,2.5);
 TH1F* hTkSim_dr         = new TH1F("hTkSim_dr","",200,0.,10.);
 TH1F* hTkSim_dz         = new TH1F("hTkSim_dz","",200,0.,50.);
 TH1F* hTkSim_dd         = new TH1F("hTkSim_dd","",200,0.,50.);
 TH1F* hTkSim_drSig      = new TH1F("hTkSim_drSig","",200,0.,1000.);
 TH1F* hTkSim_dzSig      = new TH1F("hTkSim_dzSig","",200,0.,1000.);
 TH1F* hTkSim_ddSig      = new TH1F("hTkSim_ddSig","",200,0.,1000.);
 TH1F* hTkSim_inJet      = new TH1F("hTkSim_inJet","",2,-0.5,1.5);
 TH1F* hTkSim_pix        = new TH1F("hTkSim_pix","",30,-0.5,29.5);
 TH1F* hTkSim_hit        = new TH1F("hTkSim_hit","",30,-0.5,29.5);
 TH1F* hTkSim_chi        = new TH1F("hTkSim_chi","",50,0.,50.);
 TH1F* hTkSim_r1         = new TH1F("hTkSim_r1","",200,0.,100.);
 TH1F* hTkSim_z1         = new TH1F("hTkSim_z1","",210,0.,210.);
 TH1F* hTkSim_at10       = new TH1F("hTkSim_at10","",101,-0.5,100.5);
 TH1F* hTkSim_at20       = new TH1F("hTkSim_at20","",101,-0.5,100.5);
 TH1F* hTkSim_at30       = new TH1F("hTkSim_at30","",101,-0.5,100.5);
 TH1F* hTkSim_at40       = new TH1F("hTkSim_at40","",101,-0.5,100.5);
 TH1F* hTkSim_r1_PXB     = new TH1F("hTkSim_r1_PXB","",200,0.,100.);
 TH1F* hTkSim_r1_TIB     = new TH1F("hTkSim_r1_TIB","",200,0.,100.);
 TH1F* hTkSim_r1_TOB     = new TH1F("hTkSim_r1_TOB","",200,0.,100.);
 TH1F* hTkSim_z1_PXF     = new TH1F("hTkSim_z1_PXF","",210,0.,210.);
 TH1F* hTkSim_z1_TID     = new TH1F("hTkSim_z1_TID","",210,0.,210.);
 TH1F* hTkSim_z1_TEC     = new TH1F("hTkSim_z1_TEC","",210,0.,210.);
 TH1F* hTkSim_ctauLLP    = new TH1F("hTkSim_ctauLLP","",200,0.,200.);
 TH1F* hTkSim_tkneu_DR   = new TH1F("hTkSim_tkneu_DR","",100,0.,5.);
 TH1F* hTkSim_tkneu_dphi = new TH1F("hTkSim_tkneu_dphi","",33,0.,3.3);
 TH1F* hTkSim_tkjet_DR   = new TH1F("hTkSim_tkjet_DR","",100,0.,5.);
 TH1F* hTkSim_tkjet_dphi = new TH1F("hTkSim_tkjet_dphi","",33,0.,3.3);
 TH1F* hTkSim_tkjet_ok_DR   = new TH1F("hTkSim_tkjet_ok_DR","",100,0.,5.);
 TH1F* hTkSim_tkjet_ok_dphi = new TH1F("hTkSim_tkjet_ok_dphi","",33,0.,3.3);
 TH1F* hTkSim_tkjet_op_DR   = new TH1F("hTkSim_tkjet_op_DR","",100,0.,5.);
 TH1F* hTkSim_tkjet_op_dphi = new TH1F("hTkSim_tkjet_op_dphi","",33,0.,3.3);

 TH1F* hTkOth            = new TH1F("hTkOth","",101,-0.5,100.5);
 TH1F* hTkOth_pt	 = new TH1F("hTkOth_pt","",100,0.,100.);
 TH1F* hTkOth_eta        = new TH1F("hTkOth_eta","",50,-2.5,2.5);
 TH1F* hTkOth_dr	 = new TH1F("hTkOth_dr","",200,0.,10.);
 TH1F* hTkOth_dz	 = new TH1F("hTkOth_dz","",200,0.,50.);
 TH1F* hTkOth_dd	 = new TH1F("hTkOth_dd","",200,0.,50.);
 TH1F* hTkOth_drSig      = new TH1F("hTkOth_drSig","",200,0.,1000.);
 TH1F* hTkOth_dzSig      = new TH1F("hTkOth_dzSig","",200,0.,1000.);
 TH1F* hTkOth_ddSig      = new TH1F("hTkOth_ddSig","",200,0.,1000.);
 TH1F* hTkOth_inJet      = new TH1F("hTkOth_inJet","",2,-0.5,1.5);
 TH1F* hTkOth_pix        = new TH1F("hTkOth_pix","",30,-0.5,29.5);
 TH1F* hTkOth_hit        = new TH1F("hTkOth_hit","",30,-0.5,29.5);
 TH1F* hTkOth_chi        = new TH1F("hTkOth_chi","",50,0.,50.);
 TH1F* hTkOth_r1	 = new TH1F("hTkOth_r1","",200,0.,100.);
 TH1F* hTkOth_z1	 = new TH1F("hTkOth_z1","",210,0.,210.);
 TH1F* hTkOth_at10       = new TH1F("hTkOth_at10","",101,-0.5,100.5);
 TH1F* hTkOth_at20       = new TH1F("hTkOth_at20","",101,-0.5,100.5);
 TH1F* hTkOth_at30       = new TH1F("hTkOth_at30","",101,-0.5,100.5);
 TH1F* hTkOth_at40       = new TH1F("hTkOth_at40","",101,-0.5,100.5);
 TH1F* hTkOth_tkjet_DR   = new TH1F("hTkOth_tkjet_DR","",100,0.,5.);
 TH1F* hTkOth_tkjet_dphi = new TH1F("hTkOth_tkjet_dphi","",33,0.,3.3);

 TH1F* hTkMatch_LLP_hit     = new TH1F("hTkMatch_LLP_hit","",30,-0.5,29.5);
 TH1F* hTkNoMatch_LLP_hit   = new TH1F("hTkNoMatch_LLP_hit","",30,-0.5,29.5);
 TH1F* hTkMatch_NoLLP_hit   = new TH1F("hTkMatch_NoLLP_hit","",30,-0.5,29.5);
 TH1F* hTkNoMatch_NoLLP_hit = new TH1F("hTkNoMatch_NoLLP_hit","",30,-0.5,29.5);

 TH1F* hTkMatch_LLP_dpt_hitLE10   = new TH1F("hTkMatch_LLP_dpt_hitLE10","",200,-1.0,1.0);
 TH1F* hTkMatch_LLP_dpt_11hit13   = new TH1F("hTkMatch_LLP_dpt_11hit13","",200,-1.0,1.0);
 TH1F* hTkMatch_LLP_dpt_14hit17   = new TH1F("hTkMatch_LLP_dpt_14hit17","",200,-1.0,1.0);
 TH1F* hTkMatch_LLP_dpt_hitGE18   = new TH1F("hTkMatch_LLP_dpt_hitGE18","",200,-1.0,1.0);
 TH1F* hTkMatch_NoLLP_dpt_hitLE10 = new TH1F("hTkMatch_NoLLP_dpt_hitLE10","",200,-1.0,1.0);
 TH1F* hTkMatch_NoLLP_dpt_11hit13 = new TH1F("hTkMatch_NoLLP_dpt_11hit13","",200,-1.0,1.0);
 TH1F* hTkMatch_NoLLP_dpt_14hit17 = new TH1F("hTkMatch_NoLLP_dpt_14hit17","",200,-1.0,1.0);
 TH1F* hTkMatch_NoLLP_dpt_hitGE18 = new TH1F("hTkMatch_NoLLP_dpt_hitGE18","",200,-1.0,1.0);

 TH1F* hDataGen_LLP_nTrks         = new TH1F("hDataGen_LLP_nTrks","",101,-0.5,100.5);
 TH1F* hDataGen_LLP_track_mvatest = new TH1F("hDataGen_LLP_track_mvatest","",200,-1.,1.);
 TH1F* hDataGen_LLP_track0_mva    = new TH1F("hDataGen_LLP_track0_mva","",200,-1.,1.);
 TH1F* hDataGen_LLP_track0_dR     = new TH1F("hDataGen_LLP_track0_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP_track_dR      = new TH1F("hDataGen_LLP_track_dR","",33,0.,3.3);
 TH1F* hDataGen_LLP_track_deta    = new TH1F("hDataGen_LLP_track_deta","",33,0.,3.3);
 TH1F* hDataGen_LLP_track_dphi    = new TH1F("hDataGen_LLP_track_dphi","",33,0.,3.3);

 TH1F* hData_Hemi_Vtx_NChi2_all = new TH1F("hData_Hemi_Vtx_NChi2_all","",70,-20.,50.);
 TH1F* hData_Hemi_Vtx_NChi2     = new TH1F("hData_Hemi_Vtx_NChi2","",50,-10.,40.);
 TH1F* hData_Hemi_Vtx_nTrks     = new TH1F("hData_Hemi_Vtx_nTrks","",40,0.5,40.5);
 TH1F* hData_Hemi_Vtx_nTrks_step1 = new TH1F("hData_Hemi_Vtx_nTrks_step1","",40,0.5,40.5);
 TH1F* hData_Hemi_Vtx_nTrks_step2 = new TH1F("hData_Hemi_Vtx_nTrks_step2","",40,0.5,40.5);
 TH1F* hData_Hemi_Vtx_nTrks_step3 = new TH1F("hData_Hemi_Vtx_nTrks_step3","",40,0.5,40.5);
//  TH1F* hData_Hemi_Vtx_dist      = new TH1F("hData_Hemi_Vtx_dist","",50,0.,100.);

 TH1F* hSim_Hemi_LLP_dist       = new TH1F("hSim_Hemi_LLP_dist","",10,0.,100.);
 TH1F* hSim_Hemi_LLP_dist_chiOK = new TH1F("hSim_Hemi_LLP_dist_chiOK","",10,0.,100.);
 TH1F* hSim_Hemi_Vtx_dx         = new TH1F("hSim_Hemi_Vtx_dx","",200,-1.,1.);
 TH1F* hSim_Hemi_Vtx_dy         = new TH1F("hSim_Hemi_Vtx_dy","",200,-1.,1.);
 TH1F* hSim_Hemi_Vtx_dz         = new TH1F("hSim_Hemi_Vtx_dz","",200,-1.,1.);
 TH1F* hSim_Hemi_Vtx_dd         = new TH1F("hSim_Hemi_Vtx_dd","",100,0.,1.);
 TH1F* hSim_Hemi_LLP_dist_ping  = new TH1F("hSim_Hemi_LLP_dist_ping","",10,0.,100.);

//  TH1F*  hData_Hemi_Vtx_dist_step1 = new TH1F("hData_Hemi_Vtx_dist_step1","",50,0.,100.);
 TH1F*  hData_Hemi_Vtx_dist_step2 = new TH1F("hData_Hemi_Vtx_dist_step2","",50,0.,100.);
 TH1F*  hData_Hemi_Vtx_dist_step3 = new TH1F("hData_Hemi_Vtx_dist_step3","",50,0.,100.);

 TH1F* hSim_Hemi_LLP_dist_ping_step1 = new TH1F("hSim_Hemi_LLP_dist_ping_step1","",10,0.,100.);
 TH1F* hSim_Hemi_LLP_dist_ping_step2 = new TH1F("hSim_Hemi_LLP_dist_ping_step2","",10,0.,100.);
 TH1F* hSim_Hemi_LLP_dist_ping_step3 = new TH1F("hSim_Hemi_LLP_dist_ping_step3","",10,0.,100.);

  TH1F*   hData_track_dpt           = new TH1F("hData_track_dpt","hData_track_dpt",100,0.,15.);
  TH1F*   hData_track_deta          = new TH1F("hData_track_deta","hData_track_deta",201,-6.5,6.5);
  TH1F*   hData_track_dphi0         = new TH1F("hData_track_dphi0","hData_track_dphi0",101,-3.2,3.2);
  TH1F*   hData_track_dphi          = new TH1F("hData_track_dphi","hData_track_dphi",101,-3.2,3.2);
  
  TH3F*    hData_track_dpt_eta_dphi0   = new TH3F("hData_track_dpt_eta_dphi0","hData_track_dpt_eta_dphi0",51,0.,1,51,-0.3,0.3,51,-0.3,0.3);

  TH2F*    hData_Hemi_Vtx_dpt_deta     = new TH2F("hData_Hemi_Vtx_dpt_deta","hData_Hemi_Vtx_dpt_deta",51,0.,2,51,-1,1);
  TH2F*    hData_Hemi_Vtx_deta_dphi0   = new TH2F("hData_Hemi_Vtx_deta_dphi0","hData_Hemi_Vtx_deta_dphi0",51,-1,1,51,-1,1);
  TH2F*    hData_Hemi_Vtx_dpt_dphi0    = new TH2F("hData_Hemi_Vtx_dpt_dphi0","hData_Hemi_Vtx_dpt_dphi0",51,0.,2,51,-1,1);

  TH1F*    hData_Hemi_Vtx_bkg_r            = new TH1F("hData_Hemi_Vtx_bkg_r","hData_Hemi_Vtx_bkg_r",1001,0,50);
  TH1F*    hData_Hemi_Vtx_bkg_z            = new TH1F("hData_Hemi_Vtx_bkg_z","hData_Hemi_Vtx_bkg_z",401,-200,200);
  TH2F*    hData_Hemi_Vtx_bkg_rvsz         = new TH2F("hData_Hemi_Vtx_bkg_rvsz","hData_Hemi_Vtx_bkg_rvsz",401,-200,200,1001,5,50);

  // TH1F*    hData_Hemi_Vtx_r            = new TH1F("hData_Hemi_Vtx_r","hData_Hemi_Vtx_r",1001,0,50);
  TH1F*    hData_Hemi_Vtx_z            = new TH1F("hData_Hemi_Vtx_z","hData_Hemi_Vtx_z",401,-200,200);
  TH2F*    hData_Hemi_Vtx_rvsz         = new TH2F("hData_Hemi_Vtx_rvsz","hData_Hemi_Vtx_rvsz",401,-200,200,1001,5,50);
  TH2F*    hData_Hemi_Vtx_xvsy         = new TH2F("hData_Hemi_Vtx_xvsy","hData_Hemi_Vtx_xvsy",10001,-26,26,1001,-26,26);

  TH1F*    hData_track_PU_dz            = new TH1F("hData_track_PU_dz","hData_track_PU_dz",101,-50,50);
  TH1F*    hData_track_PU_dxy           = new TH1F("hData_track_PU_dxy","hData_track_PU_dxy",101,-50,50);
  TH2F*    hData_track_PU_dxyvsdz       = new TH2F("hData_track_PU_dxyvsdz","hData_track_PU_dxyvsdz",101,-50,50,101,-50,50);

  TH1F*    hData_track_dxy            = new TH1F("hData_track_dxy","hData_track_dxy",101,-50,50);       
  TH1F*    hData_track_dz             = new TH1F("hData_track_dz","hData_track_dz",101,-50,50);
  TH2F*    hData_track_dxyvsdz       = new TH2F("hData_track_dxyvsdz","hData_track_dxyvsdz",101,-50,50,101,-50,50);

//---------------------13/03/223-------------------//
  TH1F*   hData_dR_GenReco           = new TH1F("hData_dR_GenReco","hData_dR_GenReco",201,0,6);
  TH1F*   hData_dR_GenGen            = new TH1F("hData_dR_GenGen","hData_dR_GenGen",201,0,6);
  TH1F*   hData_dR_RecoReco          = new TH1F("hData_dR_RecoReco","hData_dR_RecoReco",201,0,6);         
  

  TH2F*          hData_Yc_xy       = new TH2F("hData_Yc_xy","hData_Yc_xy",601,-25,25,601,-25,25);
  TH2F*          hData_SecInt_xy   = new TH2F("hData_SecInt_xy","hData_SecInt_xy",10001,-25,25,10001,-25,25);
  // TH1F*          hData_SecInt_eta =     = new TH1F()
  TH1F*          hData_reco_K0Mass      = new TH1F("hData_reco_K0Mass","hData_reco_K0Mass",101,0.42,0.58);
  TH1F*          hData_reco_L0Mass      = new TH1F("hData_reco_L0Mass","hData_reco_L0Mass",101,1.06,1.18);
  TH2F*         hData_reco_V0xy         = new TH2F("hData_reco_V0xy","hData_reco_V0xy",101,-50,50,101,-50,50);

          TH1F*          hData_K0Mass      = new TH1F("hData_K0Mass","hData_K0Mass",101,0.42,0.58);
          TH1F*          hData_K0x      = new TH1F("hData_K0x","hData_K0x",200,-100,100);
          TH1F*          hData_K0y      = new TH1F("hData_K0y","hData_K0y",200,-100,100);
          TH1F*          hData_K0z      = new TH1F("hData_K0z","hData_K0z",401,-200,200);
          TH1F*          hData_K0r      = new TH1F("hData_K0r","hData_K0r",200,0,100);
          TH1F*          hData_L0Mass   = new TH1F("hData_L0Mass","hData_L0Mass",101,1.06,1.18);
          TH1F*          hData_L0x      = new TH1F("hData_L0x","hData_L0x",200,-100,100);
          TH1F*          hData_L0y      = new TH1F("hData_L0y","hData_L0y",200,-100,100);
          TH1F*          hData_L0z      = new TH1F("hData_L0z","hData_L0z",401,-200,200);
          TH1F*          hData_L0r      = new TH1F("hData_L0r","hData_L0r",200,0,100);

  TH1F*          hData_Hemi_Vtx_dist_rel = new TH1F("hData_Hemi_Vtx_dist_rel","hData_Hemi_Vtx_dist_rel",50,0,100);

  TH1F*          hData_MVAVal     = new TH1F("hData_MVAVal","hData_MVAVal",101,-1,1);
  TH1F*          hData_IsFromLLP  =  new TH1F("hData_IsFromLLP","hData_IsFromLLP",6,-1,5);
  TH2F*          hGenReco_dR   = new TH2F("hGenReco_dR","hGenReco_dR",201,0,6,201,0,6);

  // TH2F*          hSignalEff = new TH2F("hSignalEff","hSignalEff",20,-1,1,100,0,10000) ;
  // TH2F*          hBkgEff = new TH2F("hBkgEff","hBkgEff",20,-1,1,100,0,10000);
    TH1F*          hSignalEff = new TH1F("hSignalEff","hSignalEff",201,-1,1) ;
  TH1F*          hBkgEff = new TH1F("hBkgEff","hBkgEff",201,-1,1);
  TH2F*          hBkfEff_SigEff = new TH2F("hBkfEff_SigEff","hBkfEff_SigEff",201,0,1,201,0,1);
  TH1F*          h_sig = new TH1F("h_sig","h_sig",201,-1,1);
  
  TH2F*          hData_Veto = new TH2F("hData_Veto","hData_Veto",125,-3,3,125,-3,3);
  TH2F*          hData_WoVeto = new TH2F("hData_WoVeto","hData_WoVeto",125,-3,3,125,-3,3);

  //----------Vtx Selection Variables
  TH1F*          hData_Vtx_MeanTrackWeight = new TH1F("hData_Vtx_MeanTrackWeight","hData_Vtx_MeanTrackWeight",1001,1.5,2.5);
  TH1F*          hData_Vtx_MeanTrackWeight_Step1 = new TH1F("hData_Vtx_MeanTrackWeight_Step1 ","hData_Vtx_MeanTrackWeight_Step1 ",1001,1.5,2.5);
  TH2F*          hData_Vts_nTrks_vs_MWT = new TH2F("hData_Vts_nTrks_vs_MWT","hData_Vts_nTrks_vs_MWT",10,0,10,10000,0,10);

  TH1F*     hData_Vtx_nTrk10 = new TH1F("hData_Vtx_nTrk10","hData_Vtx_nTrk10",50,0,50);
  TH1F*     hData_Vtx_nTrk10_Step1 = new TH1F("hData_Vtx_nTrk10_Step1","hData_Vtx_nTrk10_Step1",50,0,50);
  TH1F*     hData_Vtx_nTrk20 = new TH1F("hData_Vtx_nTrk20","hData_Vtx_nTrk20",50,0,50);
  TH1F*    hData_Vtx_nTrk20_Step1 = new TH1F("hData_Vtx_nTrk20_Step1","hData_Vtx_nTrk20_Step1",50,0,50);
  
  TH1F*     hData_Vtx_Vtx_dd = new TH1F("hData_Vtx_Vtx_dd","hData_Vtx_Vtx_dd",250,0,250);
  TH1F*     hData_Vtx_Vtx_dd_Step1 = new TH1F("hData_Vtx_Vtx_dd_Step1","hData_Vtx_Vtx_dd_Step1",250,0,250);

  TH1F*    hData_Vtx_nTrks = new TH1F("hData_Vtx_nTrks","hData_Vtx_nTrks",50,2,52);
  TH1F*    hData_Vtx_nTrks_Step1 = new TH1F("hData_Vtx_nTrks_Step1","hData_Vtx_nTrks_Step1",50,2,52);
//--------------------------//
  TH1F*    hData_Vtx_nVtx = new TH1F("hData_Vtx_nVtx","hData_Vtx_nVtx",3,0,3);
  TH1F*    hData_Vtx_nVtx_Step1 = new TH1F("hData_Vtx_nVtx_Step1","hData_Vtx_nVtx_Step1",3,0,3);

  TH1F*    hData_Vtx_NChi2 = new TH1F("hData_Vtx_NChi2","hData_Vtx_NChi2",100,0,100);
  TH1F*    hData_Vtx_NChi2_Step1 = new TH1F("hData_Vtx_NChi2_Step1","hData_Vtx_NChi2_Step1",100,0,100);

  TH1F*    hData_Vtx_Step = new TH1F("hData_Vtx_Step","hData_Vtx_Step",4,0,4);
  TH1F*    hData_Vtx_Step_Step1 = new TH1F("hData_Vtx_Step_Step1","hData_Vtx_Step_Step1",4,0,4);

  TH1F*    hData_Vtx_Mass = new TH1F("hData_Vtx_Mass","hData_Vtx_Mass",280,0,14000);
  TH1F*    hData_Vtx_Mass_Step1 = new TH1F("hData_Vtx_Mass_Step1","hData_Vtx_Mass_Step1",280,0,14000);

  TH1F*    hData_Vtx_DCA = new TH1F("hData_Vtx_DCA","hData_Vtx_DCA",700,0,70);
  TH1F*    hData_Vtx_DCA_Step1 = new TH1F("hData_Vtx_DCA_Step1","hData_Vtx_DCA_Step1",50,2,52);

  //-----------EVTS selectino variables
  TH1F*          hData_Evts_LeadingJetPt = new TH1F("hData_Evts_LeadingJetPt","hData_Evts_LeadingJetPt",100,30,1030);
  TH1F*          hData_Evts_LeadingJet2Pt = new TH1F("hData_Evts_LeadingJet2Pt","hData_Evts_LeadingJet2Pt",100,20,1020);
  TH1F*          hData_Evts_LeadingMuonPt = new TH1F("hData_Evts_LeadingMuonPt","hData_Evts_LeadingMuonPt",50,20,520);
  TH1F*          hData_Evts_LeadingMuon2Pt = new TH1F("hData_Evts_LeadingMuon2Pt","hData_Evts_LeadingMuon2Pt",10,20,220);
  TH1F*          hData_Evts_HT  = new TH1F("hData_Evts_HT","hData_Evts_HT",200,100,2100);
  TH1F*          hData_Evts_ST  = new TH1F("hData_Evts_ST","hData_Evts_ST",50,30,530);
  TH1F*          hData_Evts_nJets = new TH1F("hData_Evts_nJets","hData_Evts_nJets",20,0,19);
  TH1F*          hData_Evts_nVtx = new TH1F("hData_Evts_nVtx","hData_Evts_nVtx",3,0,3);

  TH1F*  hData_Evts_nMuon = new TH1F("hData_Evts_nMuon","hData_Evts_nMuon",50,0,5);

  TH1F*  hData_Evts_MuondR = new TH1F("hData_Evts_MuondR","hData_Evts_MuondR",100,30,1030);

  TH1F*  hData_Evts_MuondPhi = new TH1F("hData_Evts_MuondPhi","hData_Evts_MuondPhi",50,0,3.2);

  TH1F*  hData_Evts_MuondEta = new TH1F("hData_Evts_MuondEta","hData_Evts_MuondEta",50,0,4);

  TH1F*  hData_Evts_jet_jet_dR = new TH1F("hData_Evts_jet_jet_dR","hData_Evts_jet_jet_dR",50,0.4,5.4);

  TH1F*  hData_Evts_jet_jet_dPhi = new TH1F("hData_Evts_jet_jet_dPhi","hData_Evts_jet_jet_dPhi",50,0,3.2);

  TH1F*  hData_Evts_jet_jet_dEta = new TH1F("hData_Evts_jet_jet_dEta","hData_Evts_jet_jet_dEta",50,0,5);

  TH1F*  hData_Evts_muon_jet_dRmin = new TH1F("hData_Evts_muon_jet_dRmin","hData_Evts_muon_jet_dRmin",50,0,5);

  TH1F*  hData_Evts_muon_jet_dRmax = new TH1F("hData_Evts_muon_jet_dRmax","hData_Evts_muon_jet_dRmax",50,0,5);

  //-----------------r-z plane efficiencies------------//
  TH1F*         hSim_Hemi_LLP_r_ping    = new TH1F("hSim_Hemi_LLP_r_ping","hSim_Hemi_LLP_r_ping",100,0,100);
  TH1F*         hSim_Hemi_LLP_eta_ping  = new TH1F("hSim_Hemi_LLP_eta_ping","hSim_Hemi_LLP_eta_ping",260,-6.5,6.5);
  TH1F*         hSim_Hemi_LLP_r_ping_step1 = new TH1F("hSim_Hemi_LLP_r_ping_step1","hSim_Hemi_LLP_r_ping_step1",100,0,100);
  TH1F*         hSim_Hemi_LLP_r_ping_step2 = new TH1F("hSim_Hemi_LLP_r_ping_step2","hSim_Hemi_LLP_r_ping_step2",100,0,100);
  TH1F*         hSim_Hemi_LLP_r_ping_step3 = new TH1F("hSim_Hemi_LLP_r_ping_step3","hSim_Hemi_LLP_r_ping_step3",100,0,100);
  TH1F*         hSim_Hemi_LLP_eta_ping_step1 = new TH1F("hSim_Hemi_LLP_eta_ping_step1","hSim_Hemi_LLP_eta_ping_step1",260,-6.5,6.5);
  TH1F*         hSim_Hemi_LLP_eta_ping_step2 = new TH1F("hSim_Hemi_LLP_eta_ping_step2","hSim_Hemi_LLP_eta_ping_step2",260,-6.5,6.5);
  TH1F*         hSim_Hemi_LLP_eta_ping_step3 = new TH1F("hSim_Hemi_LLP_eta_ping_step3","hSim_Hemi_LLP_eta_ping_step3",260,-6.5,6.5);

  //------------resolution----------------------------//
  TH1F*         hData_SecInt_res_r = new TH1F("hData_SecInt_res_r","hData_SecInt_res_r",100,-1,1);
  TH1F*         hData_SecInt_res_z = new TH1F("hData_SecInt_res_z","hData_SecInt_res_z",100,-1,1);

  TH1F*         hData_SecInt_res_r_inf15 = new TH1F("hData_SecInt_res_r_inf15","hData_SecInt_res_r_inf15",100,-1,1);
  TH1F*         hData_SecInt_res_z_inf15 = new TH1F("hData_SecInt_res_z_inf15","hData_SecInt_res_z_inf15",100,-1,1);

  TH1F*         hData_SecInt_res_r_sup15 = new TH1F("hData_SecInt_res_r_sup15","hData_SecInt_res_r_sup15",100,-1,1);
  TH1F*         hData_SecInt_res_z_sup15 = new TH1F("hData_SecInt_res_z_sup15","hData_SecInt_res_z_sup15",100,-1,1);

  TH1F*         hData_SecInt_res_r_inf15_step1 = new TH1F("hData_SecInt_res_r_inf15_step1","hData_SecInt_res_r_inf15_step1",50,0,3);
  TH1F*         hData_SecInt_res_z_inf15_step1 = new TH1F("hData_SecInt_res_z_inf15_step1","hData_SecInt_res_z_inf15_step1",50,0,3);
  TH1F*         hData_SecInt_res_r_sup15_step1 = new TH1F("hData_SecInt_res_r_sup15_step1","hData_SecInt_res_r_sup15_step1",50,0,3);
  TH1F*         hData_SecInt_res_z_sup15_step1 = new TH1F("hData_SecInt_res_z_sup15_step1","hData_SecInt_res_z_sup15_step1",50,0,3);

  TH1F*         hData_SecInt_res_r_PIXB = new TH1F("hData_SecInt_res_r_PIXB","hData_SecInt_res_r_PIXB",60,0,3);
  TH1F*         hData_SecInt_res_r_TIB = new TH1F("hData_SecInt_res_r_TIB","hData_SecInt_res_r_TIB",60,0,3);
  TH1F*         hData_SecInt_res_r_TOB = new TH1F("hData_SecInt_res_r_TOB","hData_SecInt_res_r_TOB",60,0,3);

  TH1F*         hData_SecInt_res_z_PIXB = new TH1F("hData_SecInt_res_z_PIXB","hData_SecInt_res_z_PIXB",60,0,3);
  TH1F*         hData_SecInt_res_z_TIB = new TH1F("hData_SecInt_res_z_TIB","hData_SecInt_res_z_TIB",60,0,3);
  TH1F*         hData_SecInt_res_z_TOB = new TH1F("hData_SecInt_res_z_TOB","hData_SecInt_res_z_TOB",60,0,3);

  TH1F*         hData_SecInt_res_r_PIXF = new TH1F("hData_SecInt_res_r_PIXF","hData_SecInt_res_r_PIXF",60,0,3);
  TH1F*         hData_SecInt_res_r_TID = new TH1F("hData_SecInt_res_r_TID","hData_SecInt_res_r_TID",60,0,3);
  TH1F*         hData_SecInt_res_r_TEC = new TH1F("hData_SecInt_res_r_TEC","hData_SecInt_res_r_TEC",60,0,3);

  TH1F*         hData_SecInt_res_z_PIXF = new TH1F("hData_SecInt_res_z_PIXF","hData_SecInt_res_z_PIXF",60,0,3);
  TH1F*         hData_SecInt_res_z_TID = new TH1F("hData_SecInt_res_z_TID","hData_SecInt_res_z_TID",60,0,3);
  TH1F*         hData_SecInt_res_z_TEC = new TH1F("hData_SecInt_res_z_TEC","hData_SecInt_res_z_TEC",60,0,3);


  TH1F*       hData_Hemi_Vtx_r = new TH1F("hData_Hemi_Vtx_r","hData_Hemi_Vtx_r",20,0,100);
  TH1F*       hData_Hemi_Vtx_eta = new TH1F("hData_Hemi_Vtx_eta","hData_Hemi_Vtx_eta",260,-6.5,6.5);
   TH1F*      hData_Hemi_Vtx_dist  = new TH1F("hData_Hemi_Vtx_dist","hData_Hemi_Vtx_dist",20,0.,100.);
 
  TH1F*       hData_Hemi_Vtx_r_step1 = new TH1F("hData_Hemi_Vtx_r_step1","hData_Hemi_Vtx_r_step1",20,0,100);
  TH1F*       hData_Hemi_Vtx_eta_step1 = new TH1F("hData_Hemi_Vtx_eta_step1","hData_Hemi_Vtx_eta_step1",260,-6.5,6.5);
   TH1F*      hData_Hemi_Vtx_dist_step1  = new TH1F("hData_Hemi_Vtx_dist_step1","hData_Hemi_Vtx_dist_step1",20,0.,100.);


  TH1F*        hData_Hemi_Vtx_r_chiok = new TH1F("hData_Hemi_Vtx_r_chiok","hData_Hemi_Vtx_r_chiok",20,0,100);
  TH1F*        hData_Hemi_Vtx_eta_chiok = new TH1F("hData_Hemi_Vtx_eta_chiok","hData_Hemi_Vtx_eta_chiok",260,-6.5,6.5);
  TH1F*        hData_Hemi_Vtx_dist_chiok = new TH1F("hData_Hemi_Vtx_dist_chiok","hData_Hemi_Vtx_dist_chiok",20,0.,100.);

   TH1F*      hData_Hemi_Vtx_r_chiok_step1 = new TH1F("hData_Hemi_Vtx_r_chiok_step1","hData_Hemi_Vtx_r_chiok_step1",20,0,100);
   TH1F*      hData_Hemi_Vtx_eta_chiok_step1 = new TH1F("hData_Hemi_Vtx_eta_chiok_step1","hData_Hemi_Vtx_eta_chiok_step1",260,-6.5,6.5);
   TH1F*      hData_Hemi_Vtx_dist_chiok_step1 = new TH1F("hData_Hemi_Vtx_dist_chiok_step1","hData_Hemi_Vtx_dist_chiok_step1",20,0.,100.);

  TH1F*       hData_Hemi_Vtx_r_ping = new TH1F("hData_Hemi_Vtx_r_ping","hData_Hemi_Vtx_r_ping",20,0,100);
  TH1F*       hData_Hemi_Vtx_eta_ping = new TH1F("hData_Hemi_Vtx_eta_ping","hData_Hemi_Vtx_eta_ping",260,-6.5,6.5);
  TH1F*       hData_Hemi_Vtx_dist_ping = new TH1F("hData_Hemi_Vtx_dist_ping","hData_Hemi_Vtx_dist_ping",20,0.,100.);

   TH1F*      hData_Hemi_Vtx_r_ping_step1 = new TH1F("hData_Hemi_Vtx_r_ping_step1","hData_Hemi_Vtx_r_ping_step1",20,0,100);
   TH1F*      hData_Hemi_Vtx_eta_ping_step1 = new TH1F("hData_Hemi_Vtx_eta_ping_step1","hData_Hemi_Vtx_eta_ping_step1",260,-6.5,6.5);
  TH1F*       hData_Hemi_Vtx_dist_ping_step1 = new TH1F("hData_Hemi_Vtx_dist_ping_step1","hData_Hemi_Vtx_dist_ping_step1",20,0.,100.);

/////////////
  TH1F*  hGen_dRneuneu = new TH1F("hGen_dRneuneu","hGen_dRneuneu",201,0,6);
  TH1F*  hGen_dPhineuneu = new TH1F("hGen_dPhineuneu","hGen_dPhineuneu",201,0,6);
  TH1F*  hGen_dEtaneuneu = new TH1F("hGen_dEtaneuneu","hGen_dEtaneuneu",201,0,6);

  TH1F*    hGen_Jet_pt = new TH1F("hGen_Jet_pt","hGen_Jet_pt",100,0,1000);
  TH1F*    hGen_leadingjet_pt = new TH1F("hGen_leadingjet_pt","hGen_leadingjet_pt",100,0,1000);
  TH1F*    hGen_subleadingjet_pt = new TH1F("hGen_subleadingjet_pt","hGen_subleadingjet_pt",100,0,1000);

  TH1F*    hData_Jet_pt = new TH1F("hData_Jet_pt","hData_Jet_pt",100,0,1000);
  TH1F*    hData_leadingjet_pt = new TH1F("hData_leadingjet_pt","hData_leadingjet_pt",100,0,1000);
  TH1F*    hData_subleadingjet_pt = new TH1F("hData_subleadingjet_pt","hData_subleadingjet_pt",100,0,1000);

  TH1F*    hGen_Muon_pt = new TH1F("hGen_Muon_pt","hGen_Muon_pt",100,0,1000);
  TH1F*    hGen_leadingmuon_pt = new TH1F("hGen_leadingmuon_pt","hGen_leadingmuon_pt",100,0,1000);
  TH1F*    hGen_subleadingmuon_pt = new TH1F("hGen_subleadingmuon_pt","hGen_subleadingmuon_pt",100,0,1000);

  TH1F*    hData_Muon_pt = new TH1F("hData_Muon_pt","hData_Muon_pt",100,0,1000);
  TH1F*    hData_leadingmuon_pt = new TH1F("hData_leadingmuon_pt","hData_leadingmuon_pt",100,0,1000);
  TH1F*    hData_subleadingmuon_pt = new TH1F("hData_subleadingmuon_pt","hData_subleadingmuon_pt",100,0,1000);

///////////////////////////////////////////////////////////////////
   if (fChain == 0) return;
int tracks =0;
int nVertex = 0;
int allevents = 0;
      int nSTracks = 0;
      int nDTracks = 0;
      float bdtcut = -1;
      float delta = 0.01;
      int nStep= 2* abs(bdtcut/delta);
float nSelecTracks[200] = {0};
float nDiscardTracks[200] =  {0};
float sig[200] = {0};
float nRecoVertex = 0;
float MeanDistance = 0;
float nRecoVertexStep1 = 0;
float MeanDistanceStep1 = 0;
float nRecoVertexStep2 = 0;
float MeanDistanceStep2 = 0;
float nRecoVertexStep3 = 0;
float MeanDistanceStep3 = 0;
float nRecoVertexPing = 0;
float MeanDistancePing = 0;
float nRecoVertexStep1Ping = 0;
float MeanDistanceStep1Ping = 0;
float nRecoVertexStep2Ping = 0;
float MeanDistanceStep2Ping = 0;
float nRecoVertexStep3Ping = 0;
float MeanDistanceStep3Ping = 0;
float TotalnVertex = 0;
float nEvts = 0;
float nRecoVertexMTW2= 0 ;
float nRecoVertexStep1MTW2 = 0;
float nRecoVertexStep2MTW2 = 0;
float nRecoVertexStep3MTW2 = 0;
float nRecoVertexMTW2Ping = 0 ;
float nRecoVertexStep1MTW2Ping=0;
float nRecoVertexStep2MTW2Ping=0;
float nRecoVertexStep3MTW2Ping=0;


float nTrks085 = 0;
float nTrks0 = 0;


//-------------Signal/bkg----------//
bool Signal = true;
//------------------------------//



//--------VtxSelection Variables-------
int nvert = 0;
int nvertStep1 = 0;
float MeanTWcut = 1.5;
float dTW = 0.001;
int nSteps = 1/dTW;
float nSelecVtx[1000] = {0};
float nSelecVtxStep1[1000] = {0};
//--------ntrk10------
int ntrk10Cut = 0;
int dntrk10 = 1;
int nStep_10 = (50-ntrk10Cut)/dntrk10;
float nEvts_ntrk10[50] = {0};
float nEvts_ntrk10_step1[50] = {0};
//-----------------------------
//--------ntrk20------
int ntrk20Cut = 0;
int dntrk20 = 1;
int nStep_20 = (50-ntrk20Cut)/dntrk20;
float nEvts_ntrk20[50] = {0};
float nEvts_ntrk20_step1[50] = {0};
//-----------------------------
//--------Vtx_dd------
int VtxddCut = 0;
int ddd = 1;
int nStep_dd = (250-VtxddCut)/ddd;
float nEvts_Vtx_dd[250] = {0};
float nEvts_Vtx_dd_step1[250] = {0};
//-----------------------------
//--------Vtx_nTrks------
int VtxnTrksCut = 2;
int dnTrks = 1;
int nStep_nTrks = (52-VtxddCut)/dnTrks;
float nEvts_Vtx_nTrks[50] = {0};
float nEvts_Vtx_nTrks_step1[50] = {0};
//-----------------------------
//--------Vtx_nVtx------
int VtxnVtxCut = 0;
int dnVtx = 1;
int nStep_nVtx = (3-VtxnVtxCut)/dnVtx;
float nEvts_Vtx_nVtx[3] = {0};
float nEvts_Vtx_nVtx_step1[3] = {0};
//-----------------------------------------------

//--------Vtx_Chi2------
int VtxChi2Cut = 0;
float dChi2 = 0.1;
int nStep_Chi2 = (10-VtxChi2Cut)/dChi2;
float nEvts_Vtx_Chi2[100] = {0};
float nEvts_Vtx_Chi2_step1[100] = {0};
//-----------------------------------------------

//--------Vtx_Step------
int VtxStepCut = 0;
int dStep = 1;
int nStep_Step = (4-VtxStepCut)/dStep;
float nEvts_Vtx_Step[4] = {0};
float nEvts_Vtx_Step_step1[4] = {0};
//-----------------------------------------------

//--------Vtx_InvMass------
int VtxMassCut = 0;
int dMass = 50;
int nStep_Mass = (14000-VtxMassCut)/dMass;
float nEvts_Vtx_Mass[280] = {0};
float nEvts_Vtx_Mass_step1[280] = {0};
//-----------------------------------------------

//--------Vtx_DCA tracks------
int VtxDCACut = 0;
float dDCA = 0.1;
int nStep_DCA = (70-VtxDCACut)/dDCA;
float nEvts_Vtx_DCA[700] = {0};
float nEvts_Vtx_DCA_step1[700] = {0};
//-----------------------------------------------

//--------------------EvtsSelection Varaibles----
//--------Leadingjet pt------
int JetPTCut = 20;
int dpt = 10;
int nStep_jet_pt = (1020-JetPTCut)/dpt;//1000-20/dpt
float nEvts_jetpt[100] = {0};
//---------------------------
//--------subLeadingjet pt------
int Jet2PTCut = 20;
int dpt2 = 10;
int nStep_jet2_pt = (1020-Jet2PTCut)/dpt2;//1000-20/dpt
float nEvts_jetpt2[100] = {0};
//---------------------------
//--------Leadingmuon pt------
int MuonPTCut = 20;
int dpt_muon = 10;
int nStep_muon_pt = (520-MuonPTCut)/dpt_muon;//1000-20/dpt
float nEvts_muonpt[50] = {0};
//---------------------------
//--------subLeading muon pt------
int Muon2PTCut = 20;
int dpt_muon2 = 10;
int nStep_muon2_pt = (220-Muon2PTCut)/dpt_muon2;//1000-20/dpt
float nEvts_muon2pt[20] = {0};
//---------------------------
//--------HT------
int HTCut = 100;
int dpt_HT = 10;
int nStep_HT_pt = (2100-HTCut)/dpt_HT;//1000-20/dpt
float nEvts_HT[200] = {0};
//---------------------------
//--------ST------
int STCut = 30;
int dpt_ST = 10;
int nStep_ST_pt = (530-STCut)/dpt_ST;//1000-20/dpt
float nEvts_ST[50] = {0};
//---------------------------
//--------nJet------
int nJetCut = 0;
int dnJet_ST = 1;
int nStep_nJet = (20-nJetCut)/dnJet_ST;//1000-20/dpt
float nEvts_nJet[20] = {0};

//-------------nmu----------//
int nMuonCut = 0;
int dnMuon = 1;
int nStep_nMuon = (20-nMuonCut)/dnMuon;//1000-20/dpt
float nEvts_nMuon[20] = {0};
// //------------------------------

// //-------------muon_muon_dR----------//
int MuondRCut = 0;
float dMuondR = 0.01;
int nStep_MuondR = (5-MuondRCut)/dMuondR;//1000-20/dpt
float nEvts_MuondR[50] = {0};
// //------------------------------

// //-------------muon_muon_dPhi----------//
int MuondPhiCut = 0;
float dMuondPhi = 0.064;
int nStep_MuondPhi = (3.2-MuondPhiCut)/dMuondPhi;//1000-20/dpt
float nEvts_MuondPhi[50] = {0};
// //------------------------------

// //-------------muon_muon_dEta----------//
int MuondEtaCut = 0;
float dMuondEta = 0.08;
int nStep_MuondEta = (4-MuondEtaCut)/dMuondEta;//1000-20/dpt
float nEvts_MuondEta[50] = {0};
// //------------------------------

// //-------------jet_jet_dR----------//
int JetdRCut = 0.4;
float dJetdR = 0.1;
int nStep_JetdR = (5.4-JetdRCut)/dJetdR;//1000-20/dpt
float nEvts_JetdR[50] = {0};
// //------------------------------

// //-------------jet_jet_dPhi----------//
int JetdPhiCut = 0;
float dJetdPhi = 0.064;
int nStep_JetdPhi = (3.2-JetdPhiCut)/dJetdPhi;//1000-20/dpt
float nEvts_JetdPhi[50] = {0};
// //------------------------------

// //-------------jet_jet_dEta----------//
int JetdEtaCut = 0;
float dJetdEta = 0.1;
int nStep_JetdEta = (5-JetdEtaCut)/dJetdEta;//1000-20/dpt
float nEvts_JetdEta[50] = {0};
// //------------------------------

// //-------------muon_jet_dRmin----------//
int MuonJetdRminCut = 0;
float dMuonJetdRmin = 0.1;
int nStep_MuonJetdRmin = (5-MuonJetdRminCut)/dMuonJetdRmin;//1000-20/dpt
float nEvts_MuonJetdRmin[50] = {0};
// //------------------------------
// //-------------muon_jet_dRmax----------//
int MuonJetdRCutmax = 0;
float dMuonJetdRmax = 0.12;
int nStep_MuonMuonJetdRmax = (6-MuonJetdRCutmax)/dMuonJetdRmax;//1000-20/dpt
float nEvts_MuonJetdRmax[50] = {0};
//------------------------------


    Long64_t nentries = fChain->GetEntriesFast();
     std::cout << "Total Entries : " << nentries << std::endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
    
      Long64_t ientry = LoadTree(jentry);
      
      if (ientry < 0) break;
      
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      // if (Cut(ientry) < 0) continue;int itest = 0;
int itest = 0;
 float deltaR;
 float mu_mass = 0.1057, smu_mass = 275.;
 float dRcut = 1.5;
 TLorentzVector v1, v2, v;

////////////////
// Event loop //
////////////////
   
   allevents++;
   if ( allevents%1000 == 0 ) std::cout << "events : " << allevents << std::endl;

//$$
//   itest++;
//   if ( itest > 10 ) break;
//  std::cout << " " << std::endl;
//  std::cout << " Event " << eventNumber << std::endl;
//$$

   int ngenpart =  tree_genParticle_pt->size();

// ///////////////////////
// // ZMu filter
// 
//    hDataAll_nZMu->Fill( tree_NbrOfZCand );
//    bool ZMu = false;
//    if ( tree_NbrOfZCand > 0 ) ZMu = true;
// //$$
//  if ( ngenpart > 0 && !ZMu ) continue; // only for MC at the moment
// //$$


///////////////////////
// Jet for HT computation
if (tree_Filter)
{
   float HTjet = 0.;

// Jets PF AK4
   int njetall = tree_jet_pt->size();
   for (int i=0; i<njetall; i++)    // Loop on jet
   {
     float jet_pt  = tree_jet_pt->at(i);
     float jet_eta = tree_jet_eta->at(i);
     float jet_phi = tree_jet_phi->at(i);
   if ( jet_pt < 20. ) continue;        // used in HTFilter !
   if ( abs(jet_eta) > 2.4 ) continue;  // used in HTFilter !
     hDataAll_Jet_pt->Fill( jet_pt );
     hDataAll_Jet_eta->Fill( jet_eta );
     hDataAll_Jet_phi->Fill( jet_phi );
     HTjet += jet_pt;
   }	   // end Loop on jet
   hDataAll_Jet_njet->Fill( njetall );
   hDataAll_Jet_HT->Fill( HTjet );

//$$
//$$ if ( HTjet < TagCut ) continue; 
//$$


///////////////////////
// reco muons

   int nmu =  tree_muon_pt->size();
   
   int nmuglob = 0;
   int NMU = 0;
   float muptmax = 0.;
   TLorentzVector vmuon[2];

   for (int i=0; i<nmu; i++) 
    {	     // Loop on reco muons
      if ( !tree_muon_isGlobal->at(i) ) continue;
      float mupt1  = tree_muon_pt->at(i);
      if ( mupt1 < 10. ) continue;
      if ( mupt1 > muptmax ) muptmax = mupt1;
      nmuglob++;
      //  NMU += tree_muon_nmu->at(i);x
      if ( tree_muon_pt->at(i) < 3. ) continue;
      if ( abs(tree_muon_eta->at(i)) > 2.5 ) continue;  // muon acceptance
      NMU++;
   }	   // end loop on reco muons

   hDataAll_nMuGlob->Fill( nmuglob );
   hDataAll_Mu_ptmax->Fill( muptmax );
   if ( muptmax > 25. ) hDataAll_nMuGlob_ptGT28->Fill( nmuglob );
hDataAll_nMu->Fill( NMU );

//$$
//  if ( muptmax < 25. || nmuglob < 2 ) continue;  // used in HTFilter ! 
//$$
   

///////////////////////
// Primary Vertex

   int nPV =  tree_nPV;
   float PVx = tree_PV_x;//tree_PV_x->at(0)
   float PVy = tree_PV_y;
   float PVz = tree_PV_z;

   float GenPVx = tree_GenPVx;
   float GenPVy = tree_GenPVy;
   float GenPVz = tree_GenPVz;
   

///////////////////////
// reco muons 

   bool ZMuRec = false;
   int PFiso, MVAiso, CutBasedId;
   float dVr, dVz;
   float Mmumu = 0.;
   int nmurec = 0, imu1 = -1, imu2 = -1;
   float mupt1, mueta1, muphi1, mupt2, mueta2, muphi2;

   for (int i=0; i<nmu; i++) {	     // Loop on reco muons
   if ( !tree_muon_isGlobal->at(i) ) continue;
     mupt1  = tree_muon_pt->at(i);
   if ( mupt1 < 10. ) continue;
     dVr = TMath::Sqrt( (tree_muon_x->at(i)-PVx)*(tree_muon_x->at(i)-PVx) + (tree_muon_y->at(i)-PVy)*(tree_muon_y->at(i)-PVy) );
     dVz = tree_muon_z->at(i)-PVz;
     hData_Mu_dVr->Fill( dVr );
     hData_Mu_dVz->Fill( dVz );
  //  if ( dVr > 0.1 || abs(dVz) > 0.2 ) continue;

     mueta1 = tree_muon_eta->at(i);
     muphi1 = tree_muon_phi->at(i);
     hData_Mu_pt->Fill( mupt1 );
     hData_Mu_eta->Fill( mueta1 );
     hData_Mu_phi->Fill( muphi1 );

     v1.SetPtEtaPhiM(mupt1,mueta1,muphi1,mu_mass);
     vmuon[0].SetPtEtaPhiM(mupt1,mueta1,muphi1,0);
     nmurec++;

   if ( i == nmu-1 ) continue;
     for (int j=i+1; j<nmu; j++) {	   // Loop on other reco muons
     if ( !tree_muon_isGlobal->at(j) ) continue;
     if ( tree_muon_charge->at(i) == tree_muon_charge->at(j) ) continue;
       dVr = TMath::Sqrt( (tree_muon_x->at(j)-PVx)*(tree_muon_x->at(j)-PVx) + (tree_muon_y->at(j)-PVy)*(tree_muon_y->at(j)-PVy) );
       dVz = tree_muon_z->at(j)-PVz;
    //  if ( dVr > 0.1 || abs(dVz) > 0.2 ) continue;
       mupt2  = tree_muon_pt->at(j);
     if ( mupt2 < 10. ) continue;
     if ( mupt1 < 25. && mupt2 < 25. ) continue;
       mueta2 = tree_muon_eta->at(j);
       muphi2 = tree_muon_phi->at(j);
       v2.SetPtEtaPhiM(mupt2,mueta2,muphi2,mu_mass);
       vmuon[1].SetPtEtaPhiM(mupt2,mueta2,muphi2,0);
       v = v1 + v2;
       if ( v.Mag() > Mmumu ) {
         Mmumu = v.Mag();
	 imu1 = i;
	 imu2 = j;
       }
     }	     // end loop on other reco muons
   }	   // end loop on reco muons

   hData_nMuRec->Fill( nmurec );
   hData_MuMu_mass->Fill( Mmumu );
//$$
//$$   if ( Mmumu < 60. ) continue;
   if ( Mmumu < 10. ) continue;
//$$

   if ( tree_muon_pt->at(imu2) > tree_muon_pt->at(imu1) ) {
     int imu0 = imu2;
     imu2 = imu1;
     imu1 = imu0;
     v = vmuon[0];
     vmuon[0] = vmuon[1];
     vmuon[1] = v;
   }
   mupt1  = tree_muon_pt->at(imu1);
   mueta1 = tree_muon_eta->at(imu1);
   muphi1 = tree_muon_phi->at(imu1);
   mupt2  = tree_muon_pt->at(imu2);
   mueta2 = tree_muon_eta->at(imu2);
   muphi2 = tree_muon_phi->at(imu2);
   hData_Mu_pt1->Fill( mupt1 );
   hData_Mu_pt2->Fill( mupt2 );

   hData_nPV->Fill(nPV);
   hData_PVx->Fill( PVx );
   hData_PVy->Fill( PVy );
   hData_PVz->Fill( PVz );

   hGen_PVx->Fill( GenPVx );
   hGen_PVy->Fill( GenPVy );
   hGen_PVz->Fill( GenPVz );

   hDataGen_PV_dx->Fill( PVx - GenPVx );
   hDataGen_PV_dy->Fill( PVy - GenPVy );
   hDataGen_PV_dz->Fill( PVz - GenPVz );

///////////////////////
// GenParticle



   int ntop=0, nstoq=0, nqtop=0, nlepW=0, lep1=0, lep2=0;
   float Gen_neu1_pt, Gen_neu1_eta, Gen_neu1_phi, Gen_neu1_m; 
   float Gen_neu2_pt, Gen_neu2_eta, Gen_neu2_phi, Gen_neu2_m; 
   float Gen_top1_pt, Gen_top1_eta, Gen_top1_phi, Gen_top1_x, Gen_top1_y, Gen_top1_z, Gen_top1_r=-1., Gen_top1_d, Gen_top1_Vphi; 
   float Gen_top2_pt, Gen_top2_eta, Gen_top2_phi, Gen_top2_x, Gen_top2_y, Gen_top2_z, Gen_top2_r=-1., Gen_top2_d, Gen_top2_Vphi; 
   int Gen_top1_id = -1, Gen_top2_id = -1;
   float dV, dV1, dV2, Vphi, deltaPhi, Vr, Vd, Vz, Veta;

   float genpt1 = 0., geneta1 = 0., genphi1 = 0.;
   float genpt2 = 0., geneta2 = 0., genphi2 = 0.;
   
   int smu[2], neu[2], genmu[2], top[2], sq1[2], sq3[2], nneu = 0, ngenmu = 0;
   int qsmu[2], qgenmu[2]; 
   int ngenb = 0, ngenc = 0;
   TLorentzVector vsmu[2], vneu[2], vgenmu[2], vtop[2], vsq1[2], vsq3[2]; 
   float bg1, bg2, gamma, ctau, dRneuneu = 0.; 
   for (int k=0; k<2; k++) {
     smu[k] = -1;
     neu[k] = -1;
     top[k] = -1;
     sq1[k] = -1;
     sq3[k] = -1;
     genmu[k] = -1;
   }
   
   for (int i=0; i<ngenpart; i++)    // Loop on GenParticle
   {
     float pdgId = tree_genParticle_pdgId->at(i); 
     float mother_pdgId = tree_genParticle_mother_pdgId->at(i); 
     float Gen_pt  = tree_genParticle_pt->at(i);
     float Gen_eta = tree_genParticle_eta->at(i);
     float Gen_phi = tree_genParticle_phi->at(i);
     float Gen_m = tree_genParticle_mass->at(i);

//  std::cout << "id mother status " << pdgId << " " << mother_pdgId << " " << tree_genParticle_statusCode->at(i) 
//            << " pt " << tree_genParticle_pt->at(i) 
// 	   << " xyz " << tree_genParticle_x->at(i) << " " << tree_genParticle_y->at(i) << " " << tree_genParticle_z->at(i) << std::endl; 

// muon from smuon
     if ( abs(pdgId) == 13 && abs(mother_pdgId) == 1000013 ) {
       hGen_muon_pt->Fill( Gen_pt );
       hGen_muon_eta->Fill( Gen_eta );
       if ( genmu[0] < 0 ) {
         genmu[0] = i;
	 vgenmu[0].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 qgenmu[0] = tree_genParticle_charge->at(i);
       }
       else if ( genmu[1] < 0 ) {
         genmu[1] = i;
	 vgenmu[1].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 qgenmu[1] = tree_genParticle_charge->at(i);
       }
       ngenmu++;
     }

// neutralino
     if ( pdgId == 1000023 && abs(mother_pdgId) == 1000013 ) {
       hGen_neu_pt->Fill( Gen_pt );
       hGen_neu_eta->Fill( Gen_eta );
       if ( neu[0] < 0 ) {
         neu[0] = i;
	 vneu[0].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 Gen_neu1_pt = Gen_pt;
	 Gen_neu1_eta = Gen_eta;
	 Gen_neu1_phi = Gen_phi;
	 Gen_neu1_m = Gen_m;
       }
       else if ( neu[1] < 0 ) {
         neu[1] = i;
	 vneu[1].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 Gen_neu2_pt = Gen_pt;
	 Gen_neu2_eta = Gen_eta;
	 Gen_neu2_phi = Gen_phi;
	 Gen_neu2_m = Gen_m;
       }
       nneu++;
     }

// top quark from neutralino
     if ( abs(pdgId) == 6 && abs(mother_pdgId) == 1000023 ) {
       if ( top[0] < 0 ) {
         top[0] = i;
	 vtop[0].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
         Gen_top1_id  = abs(pdgId);
         Gen_top1_pt  = tree_genParticle_pt->at(i);
         Gen_top1_eta = tree_genParticle_eta->at(i);
         Gen_top1_phi = tree_genParticle_phi->at(i);
         Gen_top1_x   = tree_genParticle_x->at(i);
         Gen_top1_y   = tree_genParticle_y->at(i);
         Gen_top1_z   = tree_genParticle_z->at(i);
         Gen_top1_r = TMath::Sqrt( (Gen_top1_x-GenPVx)*(Gen_top1_x-GenPVx) 
	                         + (Gen_top1_y-GenPVy)*(Gen_top1_y-GenPVy) );
         Gen_top1_d = TMath::Sqrt( Gen_top1_r*Gen_top1_r + (Gen_top1_z-GenPVz)*(Gen_top1_z-GenPVz) );
	 Vphi = TMath::ATan2( Gen_top1_y-GenPVy, Gen_top1_x-GenPVx );
         Gen_top1_Vphi = Vphi;
	 Vr = Gen_top1_r;
	 Vd = Gen_top1_d;
         Vz  = Gen_top1_z;
         Veta = Gen_top1_eta;
         ntop++;
//  std::cout << " Top " << ntop << " pdgId " << pdgId
//            << "  pt eta phi " << tree_genParticle_pt->at(i) << " " << tree_genParticle_eta->at(i) << " " << tree_genParticle_phi->at(i)
//            << "  x y z " << tree_genParticle_x->at(i) << " " << tree_genParticle_y->at(i) << " " << tree_genParticle_z->at(i)
//            << std::endl;
       }
       else if ( top[1] < 0 ) {
         deltaR = DeltaR( tree_genParticle_eta->at(i), tree_genParticle_phi->at(i), tree_genParticle_eta->at(top[0]), tree_genParticle_phi->at(top[0]) );
         top[1] = i;
	 vtop[1].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
         Gen_top2_id  = abs(pdgId);
         Gen_top2_pt  = tree_genParticle_pt->at(i);
         Gen_top2_eta = tree_genParticle_eta->at(i);
         Gen_top2_phi = tree_genParticle_phi->at(i);
         Gen_top2_x   = tree_genParticle_x->at(i);
         Gen_top2_y   = tree_genParticle_y->at(i);
         Gen_top2_z   = tree_genParticle_z->at(i);
         Gen_top2_r = TMath::Sqrt( (Gen_top2_x-GenPVx)*(Gen_top2_x-GenPVx) 
	 			 + (Gen_top2_y-GenPVy)*(Gen_top2_y-GenPVy) );
         Gen_top2_d = TMath::Sqrt( Gen_top2_r*Gen_top2_r + (Gen_top2_z-GenPVz)*(Gen_top2_z-GenPVz) );
	 Vphi = TMath::ATan2( Gen_top2_y-GenPVy, Gen_top2_x-GenPVx );
         Gen_top2_Vphi = Vphi;
	 Vr = Gen_top2_r;
	 Vd = Gen_top2_d;
         Vz   = Gen_top2_z;
         Veta = Gen_top2_eta;
         ntop++;
//  std::cout << " Top " << ntop << " pdgId " << pdgId
//            << "  pt eta phi " << tree_genParticle_pt->at(i) << " " << tree_genParticle_eta->at(i) << " " << tree_genParticle_phi->at(i)
//            << "  x y z " << tree_genParticle_x->at(i) << " " << tree_genParticle_y->at(i) << " " << tree_genParticle_z->at(i)
//            << std::endl;

       }
       hGen_top_z->Fill( abs(Vz) );
       hGen_top_r->Fill( Vr );
       hGen_top_d->Fill( Vd );
       hGen_top_pt->Fill( tree_genParticle_pt->at(i) );
       hGen_top_eta->Fill( Veta );
       hGen_top_Vphi->Fill( Vphi );
       deltaPhi = DeltaPhi( Vphi, tree_genParticle_phi->at(i) );
       hGen_top_dVphi->Fill( abs(deltaPhi) );
     }

// quarks from top
     if ( abs(pdgId) >= 1 && abs(pdgId) <= 5 
          && (abs(mother_pdgId) == 6 || abs(mother_pdgId) == 24) ) {
       dV = 10000.;
       int iLLP = -1;
       for (int k=0; k<2; k++) {
       if ( top[k] < 0 ) continue;
         dV1 = (tree_genParticle_x->at(i) - tree_genParticle_x->at(top[k]))*(tree_genParticle_x->at(i) - tree_genParticle_x->at(top[k]))
             + (tree_genParticle_y->at(i) - tree_genParticle_y->at(top[k]))*(tree_genParticle_y->at(i) - tree_genParticle_y->at(top[k]))
             + (tree_genParticle_z->at(i) - tree_genParticle_z->at(top[k]))*(tree_genParticle_z->at(i) - tree_genParticle_z->at(top[k]));
         if ( dV1 < dV ) {
	   iLLP = k;
	   dV = dV1;
	 }
       }
       if ( iLLP >= 0 ) {
         dV = TMath::Sqrt( dV );
         hGen_qtop_dV->Fill( dV );
         hGen_qtop_pt->Fill( Gen_pt );
         hGen_qtop_eta->Fill( Gen_eta );

         deltaR = DeltaR( vneu[iLLP].Eta(), vneu[iLLP].Phi(), Gen_eta, Gen_phi );
         deltaPhi = DeltaPhi( vneu[iLLP].Phi(), Gen_phi );
         hGen_neuqtop_DR->Fill( deltaR );
         hGen_neuqtop_dphi->Fill( abs(deltaPhi) );
         hGen_neuqtop_deta->Fill( abs( Gen_eta - vneu[iLLP].Eta() ) );
         nqtop++;
	 
	 if ( abs(pdgId) == 5 ) ngenb++;
	 if ( abs(pdgId) == 4 ) ngenc++;
       }
     }

// leptons from W
     if ( (abs(pdgId) == 11 || abs(pdgId) == 13 || abs(pdgId) == 15) && abs(mother_pdgId) == 24 ) {
       dV = 10000.;
       int iLLP = -1;
       for (int k=0; k<2; k++) {
       if ( top[k] < 0 ) continue;
         dV1 = (tree_genParticle_x->at(i) - tree_genParticle_x->at(top[k]))*(tree_genParticle_x->at(i) - tree_genParticle_x->at(top[k]))
             + (tree_genParticle_y->at(i) - tree_genParticle_y->at(top[k]))*(tree_genParticle_y->at(i) - tree_genParticle_y->at(top[k]))
             + (tree_genParticle_z->at(i) - tree_genParticle_z->at(top[k]))*(tree_genParticle_z->at(i) - tree_genParticle_z->at(top[k]));
         if ( dV1 < dV ) {
	   iLLP = k;
	   dV = dV1;
	 }
       }
       if ( iLLP >= 0 ) {
         dV = TMath::Sqrt( dV );
         hGen_lepW_dV->Fill( dV );
         hGen_lepW_pt->Fill( Gen_pt );
         hGen_lepW_eta->Fill( Gen_eta );

         deltaR = DeltaR( vneu[iLLP].Eta(), vneu[iLLP].Phi(), Gen_eta, Gen_phi );
         deltaPhi = DeltaPhi( vneu[iLLP].Phi(), Gen_phi );
         hGen_neulepW_DR->Fill( deltaR );
         hGen_neulepW_dphi->Fill( abs(deltaPhi) );
         hGen_neulepW_deta->Fill( abs( Gen_eta - vneu[iLLP].Eta() ) );
         nlepW++;
	 if ( iLLP == 0 ) lep1 = abs(pdgId);
	 if ( iLLP == 1 ) lep2 = abs(pdgId);
       }
     }

// quarks from stop
     if ( (abs(pdgId) == 1 || abs(pdgId) == 3) && abs(mother_pdgId) == 1000023 ) {
       if ( abs(pdgId) == 1 ) {
         if ( sq1[0] < 0 ) {
           sq1[0] = i;
	   vsq1[0].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 }
	 else if ( sq1[1] < 0 ) {
           sq1[1] = i;
	   vsq1[1].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 }
       }
       if ( abs(pdgId) == 3 ) {
         if ( sq3[0] < 0 ) {
           sq3[0] = i;
	   vsq3[0].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 }
	 else if ( sq3[1] < 0 ) {
           sq3[1] = i;
	   vsq3[1].SetPtEtaPhiM( Gen_pt, Gen_eta, Gen_phi, Gen_m );
	 }
       }
       hGen_stoq_pt->Fill( Gen_pt );
       hGen_stoq_eta->Fill( Gen_eta );
       nstoq++;
     }

   }    // End Loop on GenParticle

   hGen_muon->Fill( ngenmu );
   hGen_neu->Fill( nneu );
   hGen_top->Fill( ntop );
   hGen_qtop->Fill( nqtop );
   hGen_stoq->Fill( nstoq );
   hGen_lepW->Fill( nlepW );
   hGen_genb->Fill( ngenb );
   hGen_genc->Fill( ngenc );

// smuon
   int itest_smu = -1;
   if ( ngenmu == 2 && nneu == 2 ) {
     itest_smu = 0;
     vsmu[0] = vgenmu[0] + vneu[0];
     vsmu[1] = vgenmu[1] + vneu[1];
     float test_Msmu0 = vsmu[0].Mag() / smu_mass - 1.;
     float test_Msmu1 = vsmu[1].Mag() / smu_mass - 1.;
     hGen_smu_testM->Fill( test_Msmu0 );
     hGen_smu_testM->Fill( test_Msmu1 );
     if ( abs(test_Msmu0) > 0.1 || abs(test_Msmu1) > 0.1 ) {
       itest_smu = 1;
       vsmu[0] = vgenmu[1] + vneu[0];
       vsmu[1] = vgenmu[0] + vneu[1];
       v = vgenmu[0];
       vgenmu[0] = vgenmu[1];
       vgenmu[1] = v;
     }
     for (int i=0; i<2; i++) {
       hGen_smu_pt->Fill( vsmu[i].Pt() );
       hGen_smu_eta->Fill( vsmu[i].Eta() );
     }
     deltaR = DeltaR( vsmu[0].Eta(), vsmu[0].Phi(), vsmu[1].Eta(), vsmu[1].Phi() );
     deltaPhi = DeltaPhi( vsmu[0].Phi(), vsmu[1].Phi() );
     hGen_smusmu_DR->Fill( deltaR );
     hGen_smusmu_dphi->Fill( abs(deltaPhi) );
   }
   hGen_smu_test->Fill( itest_smu );     
   
   if ( ngenmu == 2 ) {
     v = vgenmu[0] + vgenmu[1];
     hGen_mumu_mass->Fill( v.Mag() );
     for (int i=0; i<2; i++) {
       deltaR = DeltaR( vgenmu[i].Eta(), vgenmu[i].Phi(), vsmu[i].Eta(), vsmu[i].Phi() );
       deltaPhi = DeltaPhi( vgenmu[i].Phi(), vsmu[i].Phi() );
       hGen_muonsmu_DR->Fill( deltaR );
       hGen_muonsmu_dphi->Fill( abs(deltaPhi) );
     }
   }

   if ( nneu == 2 ) {
     dRneuneu = DeltaR( Gen_neu1_eta, Gen_neu1_phi, Gen_neu2_eta, Gen_neu2_phi );
     deltaPhi = DeltaPhi( Gen_neu1_phi, Gen_neu2_phi );
     hGen_neuneu_DR->Fill( dRneuneu );
     hGen_neuneu_dphi->Fill( abs(deltaPhi) );
     for (int i=0; i<2; i++) {
       deltaR = DeltaR( vneu[i].Eta(), vneu[i].Phi(), vsmu[i].Eta(), vsmu[i].Phi() );
       deltaPhi = DeltaPhi( vneu[i].Phi(), vsmu[i].Phi() );
       hGen_neusmu_DR->Fill( deltaR );
       hGen_neusmu_dphi->Fill( abs(deltaPhi) );
       deltaR = DeltaR( vgenmu[i].Eta(), vgenmu[i].Phi(), vneu[i].Eta(), vneu[i].Phi() );
       deltaPhi = DeltaPhi( vgenmu[i].Phi(), vneu[i].Phi() );
       hGen_neumu_DR->Fill( deltaR );
       hGen_neumu_dphi->Fill( abs(deltaPhi) );
     }
   }

   if ( ntop == 2 ) {
     deltaR = DeltaR( Gen_top1_eta, Gen_top1_phi, Gen_top2_eta, Gen_top2_phi );
     hGen_toptop_DR->Fill( deltaR );
     dV = (Gen_top2_x - Gen_top1_x)*(Gen_top2_x - Gen_top1_x)
        + (Gen_top2_y - Gen_top1_y)*(Gen_top2_y - Gen_top1_y)
        + (Gen_top2_z - Gen_top1_z)*(Gen_top2_z - Gen_top1_z);
     dV = TMath::Sqrt(dV);
     hGen_toptop_dV->Fill( dV );
     deltaPhi = DeltaPhi( Gen_top2_Vphi, Gen_top1_Vphi );
     hGen_toptop_dVphi->Fill( abs(deltaPhi) );
   }

   if ( nstoq == 4 ) {
     for (int i=0; i<2; i++) {
       deltaR = DeltaR( vneu[i].Eta(), vneu[i].Phi(), vsq1[i].Eta(), vsq1[i].Phi() );
       deltaPhi = DeltaPhi( vneu[i].Phi(), vsq1[i].Phi() );
       hGen_neusq_DR->Fill( deltaR );
       hGen_neusq_dphi->Fill( abs(deltaPhi) );
       hGen_neusq_deta->Fill( abs(vsq1[i].Eta() - vneu[i].Eta()) );
       deltaR = DeltaR( vneu[i].Eta(), vneu[i].Phi(), vsq3[i].Eta(), vsq3[i].Phi() );
       deltaPhi = DeltaPhi( vneu[i].Phi(), vsq3[i].Phi() );
       hGen_neusq_DR->Fill( deltaR );
       hGen_neusq_dphi->Fill( abs(deltaPhi) );
       hGen_neusq_deta->Fill( abs(vsq3[i].Eta() - vneu[i].Eta()) );

       if ( top[i] >= 0 ) {
         dV = (tree_genParticle_x->at(sq1[i]) - tree_genParticle_x->at(top[i]))*(tree_genParticle_x->at(sq1[i]) - tree_genParticle_x->at(top[i]))
            + (tree_genParticle_y->at(sq1[i]) - tree_genParticle_y->at(top[i]))*(tree_genParticle_y->at(sq1[i]) - tree_genParticle_y->at(top[i]))
            + (tree_genParticle_z->at(sq1[i]) - tree_genParticle_z->at(top[i]))*(tree_genParticle_z->at(sq1[i]) - tree_genParticle_z->at(top[i]));
         dV = TMath::Sqrt( dV );
         hGen_stoq_dV->Fill( dV );
         dV = (tree_genParticle_x->at(sq3[i]) - tree_genParticle_x->at(top[i]))*(tree_genParticle_x->at(sq3[i]) - tree_genParticle_x->at(top[i]))
            + (tree_genParticle_y->at(sq3[i]) - tree_genParticle_y->at(top[i]))*(tree_genParticle_y->at(sq3[i]) - tree_genParticle_y->at(top[i]))
            + (tree_genParticle_z->at(sq3[i]) - tree_genParticle_z->at(top[i]))*(tree_genParticle_z->at(sq3[i]) - tree_genParticle_z->at(top[i]));
         dV = TMath::Sqrt( dV );
         hGen_stoq_dV->Fill( dV );
       }
     }
   }

// neutralino beta gamma and ctau
   float ctau1 = -1., ctau2 = -1.;
   if ( neu[0]>=0 && neu[1]>=0 && top[0]>=0 && top[1]>=0 && ntop == 2 && nstoq == 4 ) {
     v = vtop[0] + vsq1[0] + vsq3[0];
     float testE = v.E() / vneu[0].E() - 1.;
     hGen_neu_testE->Fill( testE );
     gamma = vneu[0].E() / Gen_neu1_m;
     bg1 = TMath::Sqrt( gamma*gamma - 1 );
     gamma = vneu[1].E() / Gen_neu2_m;
     bg2 = TMath::Sqrt( gamma*gamma - 1 );
     hGen_top_bg->Fill( bg1 );
     hGen_top_bg->Fill( bg2 );
     if ( abs(testE) < 0.1 ) {  // neu0 gives top0
       ctau1 = Gen_top1_d / bg1;
       hGen_top_ctau->Fill( ctau1 );
       ctau2 = Gen_top2_d / bg2;
       hGen_top_ctau->Fill( ctau2 );
     } 
   }
 

///////////////////////
// MET

   float MET = tree_PFMet_et;
   float METphi = tree_PFMet_phi;
   hData_MET->Fill( MET );
   hData_MET_phi->Fill( METphi );

///////////////////////
// Jet

   int njet = 0, njet1 = 0, njet2 = 0;
   bool isjet[99], isjet1[99], isjet2[99];
   TLorentzVector vaxis1, vaxis2, vjet[99], vseed_jet;

   int ntrkseed = 0, ntrkseed_sel = 0, ntrkseed_bdt = 0, trkseed_q = 0;
   float trkseed_pt = 0., jetseed_pt = -1.;

   int ntrack =  tree_nTracks;
   hData_nTk->Fill(ntrack);
   
// genJet AK4
   int ngenjet = tree_genJet_pt->size();

// Jets PF AK4
   for (int i=0; i<njetall; i++)    // Loop on jet
   {
     float jet_pt  = tree_jet_pt->at(i);
     float jet_eta = tree_jet_eta->at(i);
     float jet_phi = tree_jet_phi->at(i);
     isjet[i] = false;
     v.SetPtEtaPhiM( jet_pt, jet_eta, jet_phi, 0. );

   if ( jet_pt < PtMin ) continue;
   if ( abs(jet_eta) > EtaMax ) continue;

     if ( i>=0 && i<njetall-1 ) hData_Jet_pt_test->Fill( jet_pt - tree_jet_pt->at(i+1) );
      
// look if prompt muon inside
     float deltaR1 = 1000., deltaR2 = 1000.;
     if ( imu1 >= 0 ) deltaR1 = DeltaR( jet_eta, jet_phi, tree_muon_eta->at(imu1), tree_muon_phi->at(imu1) );
     hData_Jet_dRmu->Fill( deltaR1 );
     if ( imu2 >= 0 ) deltaR2 = DeltaR( jet_eta, jet_phi, tree_muon_eta->at(imu2), tree_muon_phi->at(imu2) );
     hData_Jet_dRmu->Fill( deltaR2 );
     if ( deltaR1 < 0.4 || deltaR2 < 0.4 ) {
       if ( deltaR1 < 0.4 ) {
         v1.SetPtEtaPhiM( tree_muon_pt->at(imu1), 
	                  tree_muon_eta->at(imu1), 
			  tree_muon_phi->at(imu1), 0 );
	 v -= v1;
       }
       if ( deltaR2 < 0.4 ) {
         v2.SetPtEtaPhiM( tree_muon_pt->at(imu2), 
	                  tree_muon_eta->at(imu2), 
			  tree_muon_phi->at(imu2), 0 );
	 v -= v2;
       }
       jet_pt  = v.Pt(); 
       jet_eta = v.Eta(); 
       jet_phi = v.Phi(); 
     }  
     hData_Jet_pt->Fill( jet_pt );
     hData_Jet_eta->Fill( jet_eta );
     hData_Jet_phi->Fill( jet_phi );

     njet++;
     isjet[i] = true;
     vjet[i] = v;
     if ( njet1 == 0 && jet_pt > PtMin && abs(jet_eta) < EtaMax ) {
       njet1 = 1;
       isjet1[i] = true;
       vaxis1 = v;
       vseed_jet = v;
       hData_Jetseed_pt->Fill( jet_pt );
       hData_Jetseed_eta->Fill( jet_eta );
       jetseed_pt = jet_pt;
       for (int k=0; k<ntrack; k++) {   // Loop on Tracks in jet seed
         float pt  = tree_track_pt->at(k);
       if ( pt < 1. ) continue;
         deltaR = DeltaR( jet_eta, jet_phi, tree_track_eta->at(k), tree_track_phi->at(k) );
       if ( deltaR > 0.4 ) continue;
         ntrkseed++;
	 trkseed_pt += pt;
	 trkseed_q  += tree_track_charge->at(k);
	 if ( tree_track_Hemi->at(k)  > 0 ) ntrkseed_sel++;
	 if ( tree_track_MVAval->at(k)  > -0.0401 ) ntrkseed_bdt++;
       }	   // end Loop on Track in jet
     }

     if ( njet == 1 ) {
       hData_Jet1_METpt->Fill( jet_pt / MET );
       deltaPhi = DeltaPhi( jet_phi, METphi );
       hData_Jet1_METdphi->Fill( abs(deltaPhi) );
     }
     if ( njet == 1 ) hData_Jet_pt1->Fill( jet_pt );
     if ( njet == 2 ) hData_Jet_pt2->Fill( jet_pt );

     bool isMatched = false;
     for (int j=0; j<ngenjet; j++)    // Loop on genJet
     {
       float genjet_pt  = tree_genJet_pt->at(j);
       float genjet_eta = tree_genJet_eta->at(j);
       float genjet_phi = tree_genJet_phi->at(j);

       hDataGen_Jet_deta->Fill( jet_eta - genjet_eta );
       hDataGen_Jet_dphi->Fill( jet_phi - genjet_phi );
       if ( abs(jet_eta - genjet_eta)<0.1 && abs(jet_phi - genjet_phi)<0.1 ) {
         hDataGen_Jet_dpt->Fill( jet_pt/genjet_pt - 1. );
	 isMatched = true;
       }
     }	   // end Loop on genJet
     if ( isMatched ) {
       hDataGen_Jet_pt->Fill( jet_pt );
       hDataGen_Jet_eta->Fill( jet_eta );
     }
   }	   // end Loop on jet

   hData_Jet_njet->Fill( njet );

// look for muon seed
   int imuseed = -1;
   float museed_pt = 0., museed_eta, museed_phi;
   TLorentzVector vseed_mu, vmet;
   for (int m=0; m<nmu; m++) {	     // Loop on reco muons
   if ( m == imu1 || m == imu2 ) continue;
   if ( !(tree_muon_isGlobal->at(m)) ) continue;
     float mu_pt  = tree_muon_pt->at(m);
     float mu_eta = tree_muon_eta->at(m);
     float mu_phi = tree_muon_phi->at(m);
//      bool isIsoMu = true;
//      for (int i=1; i<njetall; i++) {   // Loop on jet
//        float jet_eta = tree_jet_eta->at(i);
//        float jet_phi = tree_jet_phi->at(i);
//        deltaR = DeltaR( mu_eta, mu_phi, jet_eta, jet_phi );
//        hData_mujet_dR->Fill( deltaR );
//        if ( deltaR < 0.4 ) {
//          isIsoMu = false;
// 	 break;
//        }
//      }	   // end Loop on jet
//      if ( isIsoMu ) {
       if ( mu_pt > museed_pt && mu_pt > 20. ) {
         museed_phi = mu_phi;
         float dphiMET = abs(DeltaPhi( museed_phi, METphi ));
         hData_museed_dphiMET->Fill( dphiMET );
	 if ( dphiMET < dRcut ) {
           museed_pt = mu_pt;
           museed_eta = mu_eta;
	   imuseed = m;
	 }
       }
//      }
   }	 // end Loop on reco muons
   if ( imuseed >= 0 ) {
     hData_museed_pt->Fill( museed_pt );
     hData_museed_eta->Fill( museed_eta );
     vseed_mu.SetPtEtaPhiM( museed_pt, museed_eta, museed_phi, 0. );
// add MET
     hData_museed_MET->Fill( MET );
//      if ( MET > 50. ) {
//        vmet.SetPtEtaPhiM( MET, 0., METphi, 0. );
//        vseed_mu += vmet; 
//      }     
   }

// look for electron seed
   int ielseed = -1;
   float elseed_pt = 0., elseed_eta, elseed_phi;
   TLorentzVector vseed_el;
   int nel =  tree_electron_pt->size();
   for (int k=0; k<nel; k++) {	     // Loop on reco electrons
     float el_pt  = tree_electron_pt->at(k);
     float el_eta = tree_electron_eta->at(k);
     float el_phi = tree_electron_phi->at(k);
     if ( el_pt > elseed_pt && el_pt > 20. ) {
       elseed_phi = el_phi;
       float dphiMET = abs(DeltaPhi( elseed_phi, METphi ));
       hData_elseed_dphiMET->Fill( dphiMET );
       if ( dphiMET < dRcut ) {
     	 elseed_pt = el_pt;
     	 elseed_eta = el_eta;
         ielseed = k;
       }
     }
   }	 // end Loop on reco electrons
   if ( ielseed >= 0 ) {
     hData_elseed_pt->Fill( elseed_pt );
     hData_elseed_eta->Fill( elseed_eta );
     vseed_el.SetPtEtaPhiM( elseed_pt, elseed_eta, elseed_phi, 0. );
     hData_elseed_MET->Fill( MET );
   }

     
///////////////////////
// Event axes

   int iLLPrec1 = 1, iLLPrec2 = 2;
   float dR, dR1 = 10., dR2 = 10., deta, dphi;
   TLorentzVector vel, vmu;

//    if ( imuseed >= 0 ) vaxis1 = vseed_mu;

// first pass
   for (int i=0; i<njetall; i++) {   // Loop on jet
     isjet1[i] = false;
     isjet2[i] = false;
   if ( !isjet[i] ) continue;
     float jet_eta = vjet[i].Eta();
     float jet_phi = vjet[i].Phi();
//      if ( njet1 == 0 && imuseed >= 0 ) dR1 = DeltaR( jet_eta, jet_phi, vaxis1.Eta(), vaxis1.Phi() );
     if ( njet1 > 0 ) dR1 = DeltaR( jet_eta, jet_phi, vaxis1.Eta(), vaxis1.Phi() );
     if ( njet2 > 0 ) dR2 = DeltaR( jet_eta, jet_phi, vaxis2.Eta(), vaxis2.Phi() );
// axis 1
//      if ( njet1 == 0 && imuseed < 0 ) {
//        njet1 = 1;
//        vaxis1 = vjet[i];
//        isjet1[i] = true;
//        vseed_jet = vjet[i];
//      }
//      else if ( njet1 == 0 && !isjet2[i] && dR1 < dRcut  ) {
//        njet1 = 1;
//        vaxis1 += vjet[i];
//        isjet1[i] = true;
//      }
     if ( njet1 > 0 && !isjet2[i] && dR1 < dRcut ) {
       njet1++;
       vaxis1 += vjet[i];
       isjet1[i] = true;
     }
// axis 2
     if ( njet2 == 0 && !isjet1[i] ) {
       njet2 = 1;
       vaxis2 = vjet[i];
       isjet2[i] = true;
     }
     else if ( njet2 > 0 && !isjet1[i] && !isjet2[i] && dR2 < dRcut ) {
       njet2++;
       vaxis2 += vjet[i];
       isjet2[i] = true;
     }
   }	 // end Loop on jet

// // second pass
//    for (int i=0; i<njetall; i++) {   // Loop on jet
//    if ( !isjet[i] ) continue;
//      float jet_eta = vjet[i].Eta();
//      float jet_phi = vjet[i].Phi();
//      if ( njet1 > 0 ) dR1 = DeltaR( jet_eta, jet_phi, vaxis1.Eta(), vaxis1.Phi() );
//      if ( njet2 > 0 ) dR2 = DeltaR( jet_eta, jet_phi, vaxis2.Eta(), vaxis2.Phi() );
// // axis 1
//      if ( njet1 >= 2 && isjet1[i] && dR1 > dRcut ) {
//        njet1--;
//        vaxis1 -= vjet[i];
//        isjet1[i] = false;
//        if ( !isjet2[i] && dR2 < dRcut ) {
//          njet2++;
//          vaxis2 += vjet[i];
//          isjet2[i] = true;
//        }
//      }
// // axis 2
//      else if ( njet2 >= 1 && isjet2[i] && dR2 > dRcut  ) {
//        njet2--;
//        vaxis2 -= vjet[i];
//        isjet2[i] = false;
//        if ( !isjet1[i] && dR1 < dRcut ) {
//          njet1++;
//          vaxis1 += vjet[i];
//          isjet1[i] = true;
//        }
//      }
//    }	 // end Loop on jet
// 
// // third pass
//    for (int i=0; i<njetall; i++) {   // Loop on jet
//    if ( !isjet[i] ) continue;
//    if ( njet1 <= 1 || njet2 == 0 ) continue;
//    if ( !isjet1[i] || !isjet2[i] ) continue;
//      float jet_eta = vjet[i].Eta();
//      float jet_phi = vjet[i].Phi();
//      dR1 = DeltaR( jet_eta, jet_phi, vaxis1.Eta(), vaxis1.Phi() );
//      dR2 = DeltaR( jet_eta, jet_phi, vaxis2.Eta(), vaxis2.Phi() );
// // axis 1
//      if ( isjet1[i] && !isjet2[i] && dR1 > dR2 && dR2 < dRcut ) {
//        njet1--;
//        vaxis1 -= vjet[i];
//        isjet1[i] = false;
//        njet2++;
//        vaxis2 += vjet[i];
//        isjet2[i] = true;
//      }
// // axis 2
//      else if ( isjet2[i] && !isjet1[i] && dR2 > dR1 && dR1 < dRcut ) {
//        njet2--;
//        vaxis2 -= vjet[i];
//        isjet2[i] = false;
//        njet1++;
//        vaxis1 += vjet[i];
//        isjet1[i] = true;
//      }
//    }	 // end Loop on jet

   hData_Jet_njet_forLLP->Fill( njet1+njet2 );
   hData_Jet_njet1->Fill( njet1 );
   hData_Jet_njet2->Fill( njet2 );

// compare with neutralino axis
   float axis1_eta = vaxis1.Eta();
   float axis1_phi = vaxis1.Phi();
   if ( neu[0] >= 0 ) dR1 = DeltaR( axis1_eta, axis1_phi, Gen_neu1_eta, Gen_neu1_phi );
   if ( neu[1] >= 0 ) dR2 = DeltaR( axis1_eta, axis1_phi, Gen_neu2_eta, Gen_neu2_phi );
   dR = dR1;
   if ( dR2 < dR1 ) {
     iLLPrec1 = 2;
     iLLPrec2 = 1;
     dR = dR2;
   }
   if ( iLLPrec1 == 1 ) {
     dphi = abs(DeltaPhi( axis1_phi, Gen_neu1_phi ));
     deta = abs(axis1_eta - Gen_neu1_eta);
   }
   else {
     dphi = abs(DeltaPhi( axis1_phi, Gen_neu2_phi ));
     deta = abs(axis1_eta - Gen_neu2_eta);
   }
   float axis1_dR = dR;
   float axis1_deta = deta;
   float axis1_dphi = dphi;
   
   float axis2_eta = vaxis2.Eta();
   float axis2_phi = vaxis2.Phi();
   if ( njet2 == 0 ) {         // compute an axis 2 even without jet, by taking the opposite in phi to axis 1
     axis2_eta = axis1_eta;
     axis2_phi = axis1_phi - 3.14159;
     if ( axis1_phi < 0 ) axis2_phi = axis1_phi + 3.14159;
     vaxis2.SetPtEtaPhiM( vaxis1.Pt(), axis2_eta, axis2_phi, 0 );
   }
   if ( iLLPrec2 == 1 ) {
     dR = DeltaR( axis2_eta, axis2_phi, Gen_neu1_eta, Gen_neu1_phi );
     dphi = abs(DeltaPhi( axis2_phi, Gen_neu1_phi ));
     deta = abs(axis2_eta - Gen_neu1_eta);
   }
   else {
     dR = DeltaR( axis2_eta, axis2_phi, Gen_neu2_eta, Gen_neu2_phi );
     dphi = abs(DeltaPhi( axis2_phi, Gen_neu2_phi ));
     deta = abs(axis2_eta - Gen_neu2_eta);
   }
   if ( njet2 == 0 ) {
     hDataGen_LLP2_sym_dR->Fill( dR );
     hDataGen_LLP2_sym_dphi->Fill( dphi );
   }
   float axis2_dR = dR;
   float axis2_deta = deta;
   float axis2_dphi = dphi;

// compare seeds with neutralino axis
   dR1 = DeltaR( vseed_jet.Eta(), vseed_jet.Phi(), Gen_neu1_eta, Gen_neu1_phi );
   dR2 = DeltaR( vseed_jet.Eta(), vseed_jet.Phi(), Gen_neu2_eta, Gen_neu2_phi );
   dR = dR1;
   deta = abs( vseed_jet.Eta()-Gen_neu1_eta );
   dphi = abs( DeltaPhi(vseed_jet.Phi(), Gen_neu1_phi) );
   if ( dR2 < dR1 ) {
     dR = dR2;
     deta = abs( vseed_jet.Eta()-Gen_neu2_eta );
     dphi = abs( DeltaPhi(vseed_jet.Phi(), Gen_neu2_phi) );
   }

   hDataGen_seed_dR->Fill( dR );
   hDataGen_seed_deta->Fill( deta );
   hDataGen_seed_dphi->Fill( dphi );
   if ( dR < dRcut ) {
     hDataGen_seed_dRLT15_ntrk->Fill( ntrkseed );
     hDataGen_seed_dRLT15_ntrksel->Fill( ntrkseed_sel );
     hDataGen_seed_dRLT15_ntrkbdt->Fill( ntrkseed_bdt );
     hDataGen_seed_dRLT15_trkQ->Fill( trkseed_q );
     hDataGen_seed_dRLT15_trkPt->Fill( trkseed_pt );
     hDataGen_seed_dRLT15_trkPtRel->Fill( trkseed_pt/jetseed_pt);
   }
   else {
     hDataGen_seed_dRGT15_ntrk->Fill( ntrkseed );
     hDataGen_seed_dRGT15_ntrksel->Fill( ntrkseed_sel );
     hDataGen_seed_dRGT15_ntrkbdt->Fill( ntrkseed_bdt );
     hDataGen_seed_dRGT15_trkQ->Fill( trkseed_q );
     hDataGen_seed_dRGT15_trkPt->Fill( trkseed_pt );
     hDataGen_seed_dRGT15_trkPtRel->Fill( trkseed_pt/jetseed_pt);
   }
   
   if ( axis1_dR > dRcut ) hDataGen_seed_dR1GT15_dR->Fill( dR );
   if ( dR > dRcut )       hDataGen_LLP1_dRseedGT15_dR->Fill( axis1_dR );

   if ( imuseed >= 0 ) {
     dR1 = DeltaR( vseed_mu.Eta(), vseed_mu.Phi(), Gen_neu1_eta, Gen_neu1_phi );
     dR2 = DeltaR( vseed_mu.Eta(), vseed_mu.Phi(), Gen_neu2_eta, Gen_neu2_phi );
     dR = dR1;
     if ( dR2 < dR1 ) dR = dR2; 
     hDataGen_museed_dR->Fill( dR );
   }
   if ( ielseed >= 0 ) {
     dR1 = DeltaR( vseed_el.Eta(), vseed_el.Phi(), Gen_neu1_eta, Gen_neu1_phi );
     dR2 = DeltaR( vseed_el.Eta(), vseed_el.Phi(), Gen_neu2_eta, Gen_neu2_phi );
     dR = dR1;
     if ( dR2 < dR1 ) dR = dR2; 
     hDataGen_elseed_dR->Fill( dR );
   }

   hDataGen_LLP_dR->Fill( axis1_dR );
   hDataGen_LLP_dR->Fill( axis2_dR );
   hDataGen_LLP1_dR->Fill( axis1_dR );
   hDataGen_LLP1_deta->Fill( axis1_deta );
   hDataGen_LLP1_dphi->Fill( axis1_dphi );
   hDataGen_LLP2_dR->Fill( axis2_dR );
   hDataGen_LLP2_deta->Fill( axis2_deta );
   hDataGen_LLP2_dphi->Fill( axis2_dphi );

   if ( axis2_dR > dRcut ) hDataGen_LLP1_dR2GT15_dR->Fill( axis1_dR );
   if ( axis1_dR > dRcut ) hDataGen_LLP2_dR1GT15_dR->Fill( axis2_dR );

   dR = DeltaR( axis1_eta, axis1_phi, axis2_eta, axis2_phi );
   dphi = abs(DeltaPhi( axis1_phi, axis2_phi ));
   deta = abs(axis1_eta - axis2_eta);
   hData_axis12_dR->Fill( dR );
   hData_axis12_deta->Fill( deta );
   hData_axis12_dphi->Fill( dphi );

//    if ( nneu == 2 && dRneuneu > dRcut && axis2_dR > dRcut ) {
//      std::cout << "event dRneuneu " << allevents << " " << dRneuneu << "   njet1 dR1 "<< njet1 << " " << axis1_dR << "   njet2 dR2 " << njet2 << " " << axis2_dR << std::endl;     
//    }     


///////////////////////
// Tracks

   int nTkSim = 0, nTkOth = 0;
   int track_isfromLLP[1000], track_SEL40[1000];
   bool track_SELEC[1000];
   if ( ntrack >= 1000 ) std::cout << " ##### ERROR ntrack ##### " << ntrack << std::endl;

   int ntrack_LLP1 = 0, ntrack_LLP2 = 0;
   int itrack_LLP1[100], itrack_LLP2[100];
   float track_mva_LLP1[100], track_mva_LLP2[100];

   for (int i=0; i<ntrack; i++)    // Loop on Tracks
   {
     track_isfromLLP[i] = tree_track_sim_LLP->at(i);
     int ntrk10 = 0, ntrk20 = 0, ntrk30 = 0, ntrk40 = 0;
     track_SEL40[i] = 0;
     track_SELEC[i] = false;
    tracks ++;
     float q   = tree_track_charge->at(i);
     float pt  = tree_track_pt->at(i);
     float eta = tree_track_eta->at(i);
     float phi = tree_track_phi->at(i);
     float dr = abs(tree_track_dxy->at(i));
     float drSig = -1., dzSig = -1., ddSig = -1.;
     if ( tree_track_dxyError->at(i) > 0 ) drSig = dr / tree_track_dxyError->at(i);
     float dz = abs(tree_track_dz->at(i));
     if ( tree_track_dzError->at(i) > 0 )  dzSig = dz / tree_track_dzError->at(i);
     float dd = TMath::Sqrt( dr*dr + dz*dz );
     if ( drSig>0 && dzSig>0 ) ddSig = TMath::Sqrt( drSig*drSig + dzSig*dzSig );
     float pix = tree_track_nHitPixel->at(i);
     float hit = tree_track_nHit->at(i);
     float chi = tree_track_NChi2->at(i);
     float x1 = tree_track_firstHit_x->at(i);
     float y1 = tree_track_firstHit_y->at(i);
     float z1 = tree_track_firstHit_z->at(i);
     float r1 = TMath::Sqrt( x1*x1 + y1*y1 );
     int inJet = 0;
     int jet = tree_track_iJet->at(i);
     if ( jet >= 0 ) inJet = 1;

     if ( pt >= 1. && chi <= 5. && drSig >= 5. ) track_SELEC[i] = true;
   if ( !track_SELEC[i] ) continue;

     for (int k=0; k<ntrack; k++)    // Loop on other Tracks
     {
     if ( k == i ) continue;
       float pt2  = tree_track_pt->at(k);
       float dr2  = abs(tree_track_dxy->at(k));
       float drSig2 = -1.;
       if ( tree_track_dxyError->at(k) > 0 ) drSig2 = dr2 / tree_track_dxyError->at(k);
       float chi2 = tree_track_NChi2->at(k);
     if ( !(pt2 >= 1. && chi2 <= 5. && drSig2 >= 5.) ) continue;
       float x2   = tree_track_firstHit_x->at(k);
       float y2   = tree_track_firstHit_y->at(k);
       float z2   = tree_track_firstHit_z->at(k);
       float dist = TMath::Sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2) );
       if ( dist < 10. ) ntrk10++; 
       if ( dist < 20. ) ntrk20++; 
       if ( dist < 30. ) ntrk30++; 
       if ( dist < 40. ) ntrk40++;
     }  // end Loop on other Tracks

// sim tracks associated to reco tracks
     float ptSim = tree_track_sim_pt->at(i);
     if ( ptSim > 0. && track_isfromLLP[i] >= 1 ) {
       nTkSim++;

       hTkSim_pt->Fill( pt );
       hTkSim_eta->Fill( eta );
       hTkSim_dr->Fill( dr );
       hTkSim_dz->Fill( dz );
       hTkSim_dd->Fill( dd );
       hTkSim_drSig->Fill( drSig );
       hTkSim_dzSig->Fill( dzSig );
       hTkSim_ddSig->Fill( ddSig );
       hTkSim_inJet->Fill( inJet );
       hTkSim_pix->Fill( pix );
       hTkSim_hit->Fill( hit );
       hTkSim_chi->Fill( chi );
       hTkSim_r1->Fill( r1 );
       hTkSim_z1->Fill( abs(z1) );
       hTkSim_at10->Fill( ntrk10 );
       hTkSim_at20->Fill( ntrk20 );
       hTkSim_at30->Fill( ntrk30 );
       hTkSim_at40->Fill( ntrk40 );
       
       if ( tree_track_nHitPXB->at(i) > 0 )                                     hTkSim_r1_PXB->Fill( r1 );
       if ( tree_track_nHitTIB->at(i) > 0 && tree_track_nHitPixel->at(i) == 0 ) hTkSim_r1_TIB->Fill( r1 );
       if ( tree_track_nHitTOB->at(i) > 0 && tree_track_nHitTIB->at(i) == 0 )   hTkSim_r1_TOB->Fill( r1 );
       if ( tree_track_nHitPXF->at(i) > 0 )                                     hTkSim_z1_PXF->Fill( abs(z1) );
       if ( tree_track_nHitTID->at(i) > 0 && tree_track_nHitPXF->at(i) == 0 )   hTkSim_z1_TID->Fill( abs(z1) );
       if ( tree_track_nHitTEC->at(i) > 0 && tree_track_nHitTID->at(i) == 0 )   hTkSim_z1_TEC->Fill( abs(z1) );

       float ctauLLP = ctau1;
       if ( track_isfromLLP[i] == 2 ) ctauLLP = ctau2; 
       hTkSim_ctauLLP->Fill( ctauLLP );

       float deltaR_neu, deltaPhi_neu;
       deltaR   = DeltaR( eta, phi, vaxis1.Eta(), vaxis1.Phi() );
       deltaPhi = DeltaPhi( phi, vaxis1.Phi() );
       float deltaRop   = DeltaR( eta, phi, vaxis2.Eta(), vaxis2.Phi() );
       float deltaPhiop = DeltaPhi( phi, vaxis2.Phi() );
       if ( track_isfromLLP[i] == 1 ) {
         deltaR_neu = DeltaR( eta, phi, vneu[0].Eta(), vneu[0].Phi() );
         deltaPhi_neu = DeltaPhi( phi, vneu[0].Phi() );
	 if ( -vaxis1*vneu[0] > 0 ) {
           hTkSim_tkjet_ok_DR->Fill( deltaR );
           hTkSim_tkjet_ok_dphi->Fill( abs(deltaPhi) );
	 }
	 else {
           hTkSim_tkjet_op_DR->Fill( deltaRop );
           hTkSim_tkjet_op_dphi->Fill( abs(deltaPhiop) );
	 }
       }
       else {
         deltaR_neu = DeltaR( eta, phi, vneu[1].Eta(), vneu[1].Phi() );
         deltaPhi_neu = DeltaPhi( phi, vneu[1].Phi() );
	 if ( -vaxis1*vneu[1] > 0 ) {
           hTkSim_tkjet_ok_DR->Fill( deltaR );
           hTkSim_tkjet_ok_dphi->Fill( abs(deltaPhi) );
         }
	 else {
           hTkSim_tkjet_op_DR->Fill( deltaRop );
           hTkSim_tkjet_op_dphi->Fill( abs(deltaPhiop) );
	 }
       }
       hTkSim_tkneu_DR->Fill( deltaR_neu );
       hTkSim_tkneu_dphi->Fill( abs(deltaPhi_neu) );
       hTkSim_tkjet_DR->Fill( deltaR );
       hTkSim_tkjet_dphi->Fill( abs(deltaPhi) );       
       float qSim   = tree_track_sim_charge->at(i);
       float etaSim = tree_track_sim_eta->at(i);
       float phiSim = tree_track_sim_phi->at(i);
       float vxgen  = tree_track_sim_x->at(i);
       float vygen  = tree_track_sim_y->at(i);
       float vzgen  = tree_track_sim_z->at(i);

       float qR = qSim * ptSim * 100 / 0.3 / 3.8;
       float sin0 = qR * sin( phiSim ) + (vxgen - tree_GenPVx);
       float cos0 = qR * cos( phiSim ) - (vygen - tree_GenPVy);
       float phi0 = TMath::ATan2( sin0, cos0 ); // but note that it can be wrong by +_pi ! 

       float dpt_TkSim  = (pt - ptSim) / pt;
       float deta_TkSim = eta - etaSim;
       float dphi_TkSim = phi - phi0;
       if      ( dphi_TkSim < -3.14159 / 2. ) dphi_TkSim += 3.14159;
       else if ( dphi_TkSim >  3.14159 / 2. ) dphi_TkSim -= 3.14159;

       hTkSim_dq->Fill( q - qSim ); // why half of the reco tracks have a wrong charge ?
       hTkSim_dpt->Fill( dpt_TkSim );
       hTkSim_deta->Fill( deta_TkSim );
       hTkSim_dphiraw->Fill( DeltaPhi( phi , phiSim ) );
       hTkSim_dphi->Fill( dphi_TkSim );
       if ( abs(deta_TkSim) < 0.1 && abs(dphi_TkSim) < 0.1 ) hTkSim_dpt_cut->Fill( dpt_TkSim );
       if ( abs(dpt_TkSim)  < 0.1 && abs(dphi_TkSim) < 0.1 ) hTkSim_deta_cut->Fill( deta_TkSim );
       if ( abs(dpt_TkSim)  < 0.1 && abs(deta_TkSim) < 0.1 ) hTkSim_dphi_cut->Fill( dphi_TkSim );
	 
       for (int k=0; k<ngenpart; k++)    // Loop on final Gen Particles
       {
       if ( tree_genParticle_statusCode->at(k) != 1 ) continue; 
       if ( tree_genParticle_charge->at(k) == 0 ) continue; 
       if ( tree_genParticle_pdgId->at(k) != tree_track_sim_pdgId->at(i) ) continue; 

         float qGen   = tree_genParticle_charge->at(k);
         float ptGen  = tree_genParticle_pt->at(k);
         float etaGen = tree_genParticle_eta->at(k);
         float phiGen = tree_genParticle_phi->at(k);
         float xGen   = tree_genParticle_x->at(k);
         float yGen   = tree_genParticle_y->at(k);

         float dpt_SimGen   = ptSim / ptGen -1.;
         float deta_SimGen  = etaSim - etaGen;
         float dphi_SimGen  = DeltaPhi( phiSim , phiGen );

         hSimGen_dq->Fill( qSim - qGen );
         hSimGen_dpt->Fill( dpt_SimGen );
         hSimGen_deta->Fill( deta_SimGen );
         hSimGen_dphi->Fill( dphi_SimGen );
         if ( abs(deta_SimGen) < 0.01 && abs(dphi_SimGen) < 0.01 ) hSimGen_dpt_cut->Fill( dpt_SimGen );
         if ( abs(dpt_SimGen)  < 0.01 && abs(dphi_SimGen) < 0.01 ) hSimGen_deta_cut->Fill( deta_SimGen );
         if ( abs(dpt_SimGen)  < 0.01 && abs(deta_SimGen) < 0.01 ) hSimGen_dphi_cut->Fill( dphi_SimGen );

       if ( !(abs(dpt_SimGen)  < 0.01 && abs(deta_SimGen)  < 0.01 && abs(dphi_SimGen) < 0.01) ) continue;

         qR = qGen * ptGen * 100 / 0.3 / 3.8;
         sin0 = qR * sin( phiGen ) + (xGen - tree_GenPVx);
         cos0 = qR * cos( phiGen ) - (yGen - tree_GenPVy);
         phi0 = TMath::ATan2( sin0, cos0 ); // but note that it can be wrong by +_pi ! 

         float dptGen  = (pt - ptGen) / pt;
         float detaGen = eta - etaGen;
         float dphiGen = phi - phi0;
         if      ( dphiGen < -3.14159 / 2. ) dphiGen += 3.14159;
         else if ( dphiGen >  3.14159 / 2. ) dphiGen -= 3.14159;

         hTkGen_dq->Fill( q - qGen ); // why half of the reco tracks have a wrong charge ?
         hTkGen_dpt->Fill( dptGen );
         hTkGen_deta->Fill( detaGen );
         hTkGen_dphi->Fill( dphiGen );
         hTkGen_dphiraw->Fill( DeltaPhi( phi , phiGen ) );

         if ( pt < 4. ) {
            hTkGen_dpt_ptLT4->Fill( dptGen );
           hTkGen_deta_ptLT4->Fill( detaGen );
           hTkGen_dphi_ptLT4->Fill( dphiGen );
         }
         else {
              hTkGen_dpt_ptGT4->Fill( dptGen );
           hTkGen_deta_ptGT4->Fill( detaGen );
           hTkGen_dphi_ptGT4->Fill( dphiGen );
         }
         if ( abs(eta) < 0.8 ) {
            hTkGen_dpt_etaLT08->Fill( dptGen );
           hTkGen_deta_etaLT08->Fill( detaGen );
           hTkGen_dphi_etaLT08->Fill( dphiGen );
         }
         else {
            hTkGen_dpt_etaGT08->Fill( dptGen );
           hTkGen_deta_etaGT08->Fill( detaGen );
           hTkGen_dphi_etaGT08->Fill( dphiGen );
         }
         if ( drSig < 170. ) {
            hTkGen_dpt_drsigLT170->Fill( dptGen );
           hTkGen_deta_drsigLT170->Fill( detaGen );
           hTkGen_dphi_drsigLT170->Fill( dphiGen );
         }
         else {
            hTkGen_dpt_drsigGT170->Fill( dptGen );
           hTkGen_deta_drsigGT170->Fill( detaGen );
           hTkGen_dphi_drsigGT170->Fill( dphiGen );
         }
         if ( inJet ) {
            hTkGen_dpt_inJet->Fill( dptGen );
           hTkGen_deta_inJet->Fill( detaGen );
           hTkGen_dphi_inJet->Fill( dphiGen );
         }
         else {
            hTkGen_dpt_NOTinJet->Fill( dptGen );
           hTkGen_deta_NOTinJet->Fill( detaGen );
           hTkGen_dphi_NOTinJet->Fill( dphiGen );
         }
         if ( hit <= 15 ) {
            hTkGen_dpt_hitLE15->Fill( dptGen );
           hTkGen_deta_hitLE15->Fill( detaGen );
           hTkGen_dphi_hitLE15->Fill( dphiGen );
         }
         else {
            hTkGen_dpt_hitGT15->Fill( dptGen );
           hTkGen_deta_hitGT15->Fill( detaGen );
           hTkGen_dphi_hitGT15->Fill( dphiGen );
         }
         if ( ctauLLP < 9. ) {
            hTkGen_dpt_ctauLT9->Fill( dptGen );
           hTkGen_deta_ctauLT9->Fill( detaGen );
           hTkGen_dphi_ctauLT9->Fill( dphiGen );
         }
         else {
            hTkGen_dpt_ctauGT9->Fill( dptGen );
           hTkGen_deta_ctauGT9->Fill( detaGen );
           hTkGen_dphi_ctauGT9->Fill( dphiGen );
         }

if ( hit <= 10 ) {
            hTkGen_dpt_hitLE10->Fill( dptGen );
           hTkGen_deta_hitLE10->Fill( detaGen );
           hTkGen_dphi_hitLE10->Fill( dphiGen );
         }
         else if ( hit <= 13 ) {
            hTkGen_dpt_11hit13->Fill( dptGen );
           hTkGen_deta_11hit13->Fill( detaGen );
           hTkGen_dphi_11hit13->Fill( dphiGen );
         }
         else if ( hit <= 17 ) {
            hTkGen_dpt_14hit17->Fill( dptGen );
           hTkGen_deta_14hit17->Fill( detaGen );
           hTkGen_dphi_14hit17->Fill( dphiGen );
         }
         else {
            hTkGen_dpt_hitGE18->Fill( dptGen );
           hTkGen_deta_hitGE18->Fill( detaGen );
           hTkGen_dphi_hitGE18->Fill( dphiGen );
         }
       }  // end Loop on final Gen Particles

     } // endif simtrack

     else {
       nTkOth++;
       hTkOth_pt->Fill( pt );
       hTkOth_eta->Fill( eta );
       hTkOth_dr->Fill( dr );
       hTkOth_dz->Fill( dz );
       hTkOth_dd->Fill( dd );
       hTkOth_drSig->Fill( drSig );
       hTkOth_dzSig->Fill( dzSig );
       hTkOth_ddSig->Fill( ddSig );
       hTkOth_inJet->Fill( inJet );
       hTkOth_pix->Fill( pix );
       hTkOth_hit->Fill( hit );
       hTkOth_chi->Fill( chi );
       hTkOth_r1->Fill( r1 );
       hTkOth_z1->Fill( abs(z1) );
       hTkOth_at10->Fill( ntrk10 );
       hTkOth_at20->Fill( ntrk20 );
       hTkOth_at30->Fill( ntrk30 );
       hTkOth_at40->Fill( ntrk40 );

       deltaR = DeltaR( eta, phi, vaxis1.Eta(), vaxis1.Phi() );
       deltaPhi = DeltaPhi( phi, vaxis1.Phi() );
       hTkOth_tkjet_DR->Fill( deltaR );
       hTkOth_tkjet_dphi->Fill( abs(deltaPhi) );
     } // endif other tracks
     
     if ( track_isfromLLP[i] == 1 && tree_track_MVAval->at(i) > -0.0401 ) {
       itrack_LLP1[ntrack_LLP1]    = i;
       track_mva_LLP1[ntrack_LLP1] = tree_track_MVAval->at(i);
       ntrack_LLP1++;
     }
     if ( track_isfromLLP[i] == 2 && tree_track_MVAval->at(i) > -0.0401 ) {
       itrack_LLP2[ntrack_LLP2]    = i;
       track_mva_LLP2[ntrack_LLP2] = tree_track_MVAval->at(i);
       ntrack_LLP2++;
     }

     // match gen track to reco track
     bool matchGen = false;
     for (int k=0; k<ngenpart; k++)    // reLoop on final Gen Particles
     {
     if ( tree_genParticle_statusCode->at(k) != 1 ) continue; 
     if ( tree_genParticle_charge->at(k) != q ) continue; 

       float qGen   = tree_genParticle_charge->at(k);
       float ptGen  = tree_genParticle_pt->at(k);
       float etaGen = tree_genParticle_eta->at(k);
       float phiGen = tree_genParticle_phi->at(k);
       float xGen   = tree_genParticle_x->at(k);
       float yGen   = tree_genParticle_y->at(k);

       float qR = qGen * ptGen * 100 / 0.3 / 3.8;
       float sin0 = qR * sin( phiGen ) + (xGen - tree_GenPVx);
       float cos0 = qR * cos( phiGen ) - (yGen - tree_GenPVy);
       float phi0 = TMath::ATan2( sin0, cos0 ); // but note that it can be wrong by +_pi ! 

       float dptGen  = (pt - ptGen) / pt;
       float detaGen = eta - etaGen;
       float dphiGen = phi - phi0;
       if      ( dphiGen < -3.14159 / 2. ) dphiGen += 3.14159;
       else if ( dphiGen >  3.14159 / 2. ) dphiGen -= 3.14159;

       if ( hit <= 10 ) {
         if ( abs(dptGen) < 0.70 && abs(detaGen) < 0.30 && abs(dphiGen) < 0.08 ) matchGen = true; 
         if ( ptSim > 0. && track_isfromLLP[i] >= 1 ) {
           if ( abs(detaGen) < 0.30 && abs(dphiGen) < 0.08 ) hTkMatch_LLP_dpt_hitLE10->Fill( dptGen );
	 }
	 else {
           if ( abs(detaGen) < 0.30 && abs(dphiGen) < 0.08 ) hTkMatch_NoLLP_dpt_hitLE10->Fill( dptGen );
	 }
       }
       else if ( hit <= 13 ) {
         if ( abs(dptGen) < 0.20 && abs(detaGen) < 0.12 && abs(dphiGen) < 0.05 ) matchGen = true; 
         if ( ptSim > 0. && track_isfromLLP[i] >= 1 ) {
           if ( abs(detaGen) < 0.12 && abs(dphiGen) < 0.05 ) hTkMatch_LLP_dpt_11hit13->Fill( dptGen );
	 }
	 else {
           if ( abs(detaGen) < 0.12 && abs(dphiGen) < 0.05 ) hTkMatch_NoLLP_dpt_11hit13->Fill( dptGen );
	 }
       }
       else if ( hit <= 17 ) {
         if ( abs(dptGen) < 0.08 && abs(detaGen) < 0.04 && abs(dphiGen) < 0.03 ) matchGen = true; 
         if ( ptSim > 0. && track_isfromLLP[i] >= 1 ) {
           if ( abs(detaGen) < 0.04 && abs(dphiGen) < 0.03 ) hTkMatch_LLP_dpt_14hit17->Fill( dptGen );
	 }
	 else {
           if ( abs(detaGen) < 0.04 && abs(dphiGen) < 0.03 ) hTkMatch_NoLLP_dpt_14hit17->Fill( dptGen );
	 }
       }
       else {
         if ( abs(dptGen) < 0.07 && abs(detaGen) < 0.02 && abs(dphiGen) < 0.02 ) matchGen = true; 
         if ( ptSim > 0. && track_isfromLLP[i] >= 1 ) {
           if ( abs(detaGen) < 0.02 && abs(dphiGen) < 0.02 ) hTkMatch_LLP_dpt_hitGE18->Fill( dptGen );
	 }
	 else {
           if ( abs(detaGen) < 0.02 && abs(dphiGen) < 0.02 ) hTkMatch_NoLLP_dpt_hitGE18->Fill( dptGen );
	 }
       }
     }  // end Loop on final Gen Particles

     if ( ptSim > 0. && track_isfromLLP[i] >= 1 ) {
       if (  matchGen ) hTkMatch_LLP_hit->Fill( hit );
       if ( !matchGen ) hTkNoMatch_LLP_hit->Fill( hit );
     }
     else {
       if (  matchGen ) hTkMatch_NoLLP_hit->Fill( hit );
       if ( !matchGen ) hTkNoMatch_NoLLP_hit->Fill( hit );
     }

   }  // end Loop on Tracks

   hTkSim->Fill( nTkSim );
   hTkOth->Fill( nTkOth );
   hTkAll->Fill( nTkSim + nTkOth );
   
   hDataGen_LLP_nTrks->Fill( ntrack_LLP1 );
   hDataGen_LLP_nTrks->Fill( ntrack_LLP2 );
   int index_LLP1[100], index_LLP2[100];
   int ii0, ii;
   if ( ntrack_LLP1 > 1 ) {
     TMath::Sort( ntrack_LLP1, track_mva_LLP1, index_LLP1 );
     for (int i=0; i<ntrack_LLP1; i++) {
       ii = index_LLP1[i];
       float pt  = tree_track_pt->at(itrack_LLP1[ii]);
       float eta = tree_track_eta->at(itrack_LLP1[ii]);
       float phi = tree_track_phi->at(itrack_LLP1[ii]);
       dR = DeltaR( eta, phi, vneu[0].Eta(), vneu[0].Phi() );
       deta = abs(eta - vneu[0].Eta());
       dphi = abs(DeltaPhi( vneu[0].Phi(), phi ));
       hDataGen_LLP_track_dR->Fill( dR );
       hDataGen_LLP_track_deta->Fill( deta );
       hDataGen_LLP_track_dphi->Fill( dphi );
       if (i == 0 ) {
         hDataGen_LLP_track0_mva->Fill( track_mva_LLP1[ii] );
         hDataGen_LLP_track0_dR->Fill( dR );
       }
       else {
         ii0 = index_LLP1[i-1];
         hDataGen_LLP_track_mvatest->Fill( track_mva_LLP1[ii0] - track_mva_LLP1[ii] );
       }
     }
   }
   if ( ntrack_LLP2 > 1 ) {
     TMath::Sort( ntrack_LLP2, track_mva_LLP2, index_LLP2 );
     for (int i=0; i<ntrack_LLP2; i++) {
       ii = index_LLP2[i];
       float pt  = tree_track_pt->at(itrack_LLP2[ii]);
       float eta = tree_track_eta->at(itrack_LLP2[ii]);
       float phi = tree_track_phi->at(itrack_LLP2[ii]);
       dR = DeltaR( eta, phi, vneu[1].Eta(), vneu[1].Phi() );
       deta = abs(eta - vneu[1].Eta());
       dphi = abs(DeltaPhi( vneu[1].Phi(), phi ));
       hDataGen_LLP_track_dR->Fill( dR );
       hDataGen_LLP_track_deta->Fill( deta );
       hDataGen_LLP_track_dphi->Fill( dphi );
       if (i == 0 ) {
         hDataGen_LLP_track0_mva->Fill( track_mva_LLP2[ii] );
         hDataGen_LLP_track0_dR->Fill( dR );
       }
       else {
         ii0 = index_LLP2[i-1];
         hDataGen_LLP_track_mvatest->Fill( track_mva_LLP2[ii0] - track_mva_LLP2[ii] );
       }
     }
   }

// Hemisphere study

   for (unsigned int i=0; i<tree_Hemi->size(); i++) {
              float Hemi_LLP_dist  = 0;//when MC Signal
          bool  Hemi_LLP_ping  = 0;//when MC Signal
          // float  Hemi_Vtx_eta = 0 ;
    if(Signal)
        {
          Hemi_LLP_dist  = tree_Hemi_LLP_dist->at(i);//to change when ttbar
          Hemi_LLP_ping  = tree_Hemi_LLP_ping->at(i);//to change when ttbar
          
        }
     //Allez Paul bouge toi le cul
     float Hemi_Vtx_r     = tree_Hemi_Vtx_r->at(i);
     float Hemi_Vtx_eta     = tree_Hemi_Vtx_eta->at(i);
     float Hemi_Vtx_NChi2 = tree_Hemi_Vtx_NChi2->at(i);
     int   Hemi_Vtx_step  = tree_Hemi_Vtx_step->at(i);
     int   Hemi_Vtx_dist  = tree_Hemi_Vtx_dist->at(i);
     hData_Hemi_Vtx_NChi2_all->Fill( Hemi_Vtx_NChi2 );
     hData_Hemi_Vtx_r->Fill(Hemi_Vtx_r);
     hData_Hemi_Vtx_eta->Fill(Hemi_Vtx_eta);
     hData_Hemi_Vtx_dist->Fill(Hemi_Vtx_dist);
     if(Hemi_Vtx_step==1)
      {
        hData_Hemi_Vtx_r_step1->Fill(Hemi_Vtx_r) ;
        hData_Hemi_Vtx_eta_step1->Fill(Hemi_Vtx_eta) ;
        hData_Hemi_Vtx_dist_step1->Fill(Hemi_Vtx_dist);
      }
    if(Hemi_Vtx_NChi2>0 && Hemi_Vtx_NChi2<10)
      {
          hData_Hemi_Vtx_r_chiok->Fill(Hemi_Vtx_r);
          hData_Hemi_Vtx_eta_chiok->Fill(Hemi_Vtx_eta);
          hData_Hemi_Vtx_dist_chiok->Fill(Hemi_Vtx_dist);

          if (Hemi_Vtx_step==1)
            {
              hData_Hemi_Vtx_r_chiok_step1->Fill(Hemi_Vtx_r);
              hData_Hemi_Vtx_eta_chiok_step1->Fill(Hemi_Vtx_eta);
              hData_Hemi_Vtx_dist_chiok_step1->Fill(Hemi_Vtx_dist);
            }

          if (Signal)
            {
              if(tree_Hemi_LLP_ping->at(i))
              {
                hData_Hemi_Vtx_r_ping->Fill(Hemi_Vtx_r);
                hData_Hemi_Vtx_eta_ping->Fill(Hemi_Vtx_eta);
                hData_Hemi_Vtx_dist_ping->Fill(Hemi_Vtx_dist);
                if (Hemi_Vtx_step==1)
                  {
                    hData_Hemi_Vtx_r_ping_step1->Fill(Hemi_Vtx_r);
                    hData_Hemi_Vtx_eta_ping_step1->Fill(Hemi_Vtx_eta);
                    hData_Hemi_Vtx_dist_ping_step1->Fill(Hemi_Vtx_dist);
                  }
              }
            }

      }



     hSim_Hemi_LLP_dist->Fill( Hemi_LLP_dist );
 

     if ( Hemi_Vtx_NChi2 != -10 ) {
       hData_Hemi_Vtx_NChi2->Fill( Hemi_Vtx_NChi2 );
       hSim_Hemi_LLP_dist_chiOK->Fill( Hemi_LLP_dist );
     }

     if ( Hemi_Vtx_NChi2 > 0 && Hemi_Vtx_NChi2 < 10) {//TTbar 198 entries
       hData_Hemi_Vtx_nTrks->Fill( tree_Hemi_Vtx_nTrks->at(i) );//ok
       if ( Hemi_Vtx_step == 1 ) hData_Hemi_Vtx_nTrks_step1->Fill( tree_Hemi_Vtx_nTrks->at(i) );
       if ( Hemi_Vtx_step == 2 ) hData_Hemi_Vtx_nTrks_step2->Fill( tree_Hemi_Vtx_nTrks->at(i) );
       if ( Hemi_Vtx_step == 3 ) hData_Hemi_Vtx_nTrks_step3->Fill( tree_Hemi_Vtx_nTrks->at(i) );

       if ( Hemi_Vtx_step == 1 )  hData_Hemi_Vtx_dist_step1->Fill( tree_Hemi_Vtx_dist->at(i) );
       if ( Hemi_Vtx_step == 2 ) hData_Hemi_Vtx_dist_step2->Fill( tree_Hemi_Vtx_dist->at(i) );
       if ( Hemi_Vtx_step == 3 ) hData_Hemi_Vtx_dist_step3->Fill( tree_Hemi_Vtx_dist->at(i) );
       hData_Hemi_Vtx_dist->Fill( tree_Hemi_Vtx_dist->at(i) );
  
          if(Signal)
        {
        hSim_Hemi_Vtx_dx->Fill( tree_Hemi_Vtx_dx->at(i) );//to change when ttbar
       hSim_Hemi_Vtx_dy->Fill( tree_Hemi_Vtx_dy->at(i) );//to change when ttbar
        hSim_Hemi_Vtx_dz->Fill( tree_Hemi_Vtx_dz->at(i) );//to change when ttbar
        hSim_Hemi_Vtx_dd->Fill( tree_Hemi_Vtx_dd->at(i) );//to change when ttbar
        }
      //  if (tree_Hemi_Vtx_dd->at(i)<0.1)
      //   {
      //     hData_Hemi_Vtx_dist_rel->Fill(tree_Hemi_Vtx_dist->at(i));
      //   }
     }

     if ( Hemi_Vtx_NChi2 > 0 && Hemi_Vtx_NChi2 < 10 && Hemi_LLP_ping ) {
       hSim_Hemi_LLP_dist_ping->Fill( Hemi_LLP_dist );
       hSim_Hemi_LLP_r_ping->Fill(Hemi_Vtx_r);
       hSim_Hemi_LLP_eta_ping->Fill(Hemi_Vtx_eta);
       if ( Hemi_Vtx_step == 1 ) {hSim_Hemi_LLP_dist_ping_step1->Fill( Hemi_LLP_dist );hSim_Hemi_LLP_r_ping_step1->Fill(Hemi_Vtx_r);hSim_Hemi_LLP_eta_ping_step1->Fill(Hemi_Vtx_eta);}
       if ( Hemi_Vtx_step == 2 ) {hSim_Hemi_LLP_dist_ping_step2->Fill( Hemi_LLP_dist );hSim_Hemi_LLP_r_ping_step2->Fill(Hemi_Vtx_r);hSim_Hemi_LLP_eta_ping_step2->Fill(Hemi_Vtx_eta);}
       if ( Hemi_Vtx_step == 3 ) {hSim_Hemi_LLP_dist_ping_step3->Fill( Hemi_LLP_dist );hSim_Hemi_LLP_r_ping_step3->Fill(Hemi_Vtx_r);hSim_Hemi_LLP_eta_ping_step3->Fill(Hemi_Vtx_eta);}
     }
   }

   //Signal Vertex
      for (unsigned int i = 0 ; i< tree_Hemi_Vtx_NChi2->size(); i++)
        {
          if(abs(tree_Hemi_Vtx_NChi2->at(i)) < 10. && tree_Hemi_nTrks->at(i)>1 &&  tree_Hemi_Vtx_NChi2->at(i)>0)
            {
              nVertex++;
              hData_Hemi_Vtx_r->Fill(sqrt(tree_Hemi_Vtx_x->at(i)*tree_Hemi_Vtx_x->at(i)+tree_Hemi_Vtx_y->at(i)*tree_Hemi_Vtx_y->at(i)));
              hData_Hemi_Vtx_z->Fill(tree_Hemi_Vtx_z->at(i));
              hData_Hemi_Vtx_rvsz->Fill(tree_Hemi_Vtx_z->at(i),sqrt(tree_Hemi_Vtx_x->at(i)*tree_Hemi_Vtx_x->at(i)+tree_Hemi_Vtx_y->at(i)*tree_Hemi_Vtx_y->at(i)));
              if (tree_Hemi_Vtx_r->at(i)<25)  
                {
                  hData_Hemi_Vtx_xvsy->Fill(tree_Hemi_Vtx_x->at(i),tree_Hemi_Vtx_y->at(i));
                }
              
            }
        }

        //---------------------------------------------------------//

    for (unsigned int j = 0 ; j< tree_track_dxy->size();j++)
      {
        hData_track_dxy->Fill(tree_track_dxy->at(j));
        hData_track_dz->Fill(tree_track_dz->at(j));
        hData_track_dxyvsdz->Fill(tree_track_dxy->at(j),tree_track_dz->at(j));
      }
    // for (unsigned int i = 0 ; i < tree_track_PU_dxy->size(); i++ )
    //   {
    //     hData_track_PU_dxy->Fill(tree_track_PU_dxy->at(i));
    //     hData_track_PU_dz->Fill(tree_track_PU_dz->at(i));
    //     hData_track_PU_dxyvsdz->Fill(tree_track_PU_dxy->at(i),tree_track_PU_dz->at(i));
    //   }

     //-------------------------------------------------------//

// delta R between Gen and Reco
    for (unsigned int j = 0 ; j< tree_Hemi_dR->size();j++)
      {
        hData_dR_GenReco->Fill(tree_Hemi_dR->at(j));
        hData_dR_RecoReco->Fill(tree_Hemi_dR12->at(j));
            if(Signal)
        {
             hData_dR_GenGen->Fill(tree_Hemi_LLP_dR12->at(j));////
             hGenReco_dR->Fill(tree_Hemi_LLP_dR12->at(j),tree_Hemi_dR12->at(j));//
        }

      }

//Photon COnversion
    for (unsigned int j = 0 ; j< tree_Yc_x->size();j++)
      {
        if(tree_Yc_mass->at(j)>0 && tree_Yc_mass->at(j)<1 && tree_Yc_NChi2->at(j)<10 && abs(tree_Yc_eta->at(j)<1.5&&tree_Yc_r->at(j)<20))
          {
            hData_Yc_xy->Fill(tree_Yc_x->at(j),tree_Yc_y->at(j));
          }
      }

//Secodary Interaction
    for (unsigned int j = 0 ; j< tree_SecInt_x->size();j++)
      {
        if(abs(tree_SecInt_eta->at(j))<1&&tree_SecInt_r->at(j)<20&& tree_SecInt_selec->at(j))
          {
            hData_SecInt_xy->Fill(tree_SecInt_x->at(j),tree_SecInt_y->at(j));
          }
      }
//V0Candidates

    for (unsigned int j = 0 ; j< tree_V0_reco_mass->size();j++)
      {
        if(tree_V0_reco_source->at(j)==1)
          {
            hData_reco_K0Mass->Fill(tree_V0_reco_mass->at(j));
          }
        else if(tree_V0_reco_source->at(j)==2)
          {
            hData_reco_L0Mass->Fill(tree_V0_reco_mass->at(j));
          }
        
         hData_reco_V0xy->Fill(tree_V0_reco_x->at(j),tree_V0_reco_y->at(j));
      }

    for (unsigned int j = 0 ; j< tree_K0_mass->size();j++)
      {
          if (tree_K0_pt->at(j)>1)
            {
              hData_K0Mass->Fill(tree_K0_mass->at(j));
              hData_K0x->Fill(tree_K0_x->at(j));
              hData_K0y->Fill(tree_K0_y->at(j));
              hData_K0z->Fill(tree_K0_z->at(j));
              hData_K0r->Fill(tree_K0_r->at(j));
            }

      }
    for (unsigned int j = 0 ; j< tree_L0_mass->size();j++)
      {
          if (tree_L0_pt->at(j)>1)
            {
              hData_L0Mass->Fill(tree_L0_mass->at(j));
              hData_L0x->Fill(tree_L0_x->at(j));
              hData_L0y->Fill(tree_L0_y->at(j));
              hData_L0z->Fill(tree_L0_z->at(j));
              hData_L0r->Fill(tree_L0_r->at(j));
            }
      }
  // }

      //-------------------------------------------------------//
      // MVA Output
          for (unsigned int j = 0 ; j< tree_track_MVAval->size();j++)
      {
        if(tree_track_MVAval->at(j)>-2)
          {
            hData_MVAVal->Fill(tree_track_MVAval->at(j));
            hData_IsFromLLP->Fill(tree_track_sim_LLP->at(j));
          }
      }




    for (unsigned int j = 0 ; j< tree_track_MVAval->size();j++)
      {
        if (tree_track_MVAval->at(j)>-1 && tree_track_sim_LLP->at(j)>0)
            {
              nSTracks++;
            }
          else if (tree_track_MVAval->at(j)>-1 && tree_track_sim_LLP->at(j)<0)
            {
              nDTracks++;
            }
      }

  for (int i =0 ;i<nStep;i++)
    {
      float nSelecTrack = 0;
      float nDiscardTrack = 0;
    for (unsigned int j = 0 ; j< tree_track_MVAval->size();j++)
      {
        if (tree_track_MVAval->at(j)>bdtcut+i*delta && tree_track_sim_LLP->at(j)>0)
            {
              nSelecTracks[i]++;
              nSelecTrack++;
              
            }
          else if (tree_track_MVAval->at(j)>bdtcut+i*delta && tree_track_sim_LLP->at(j)<0)
            {
              nDiscardTracks[i]++;
              nDiscardTrack++;
            }
          // std::cout<<"tk pt : "<<tree_track_pt->at(j)<<" tk _eta : "<<tree_track_eta->at(j)<<" tk_phi :"<<tree_track_phi->at(j)<<" bdt_val :"<<tree_track_MVAval->at(j)<<std::endl;
      }

      float SignalEff = 0.;
      float BkgEff = 0.;
      if (nSTracks !=0)
        {
          SignalEff =  nSelecTrack/nSTracks;
        }
      if (nDTracks !=0)
        {
          BkgEff = nDiscardTrack/nDTracks;
        }

      // std::cout << "size : "<< tree_track_sim_LLP->size() << std::endl;
      // std::cout << "iteration : "<< bdtcut+i*delta << std::endl;
      // hSignalEff->Fill(bdtcut+i*delta,SignalEff);
      // hBkgEff->Fill(bdtcut+i*delta,BkgEff);
      // hBkfEff_SigEff->Fill(SignalEff,BkgEff);   
   }

// ttree->Draw("tree_SecInt_x:tree_SecInt_y","")   
//----------Veto---------/

for (unsigned int i=0;i<tree_SecInt_x->size();i++)
  {
    if(tree_SecInt_selec->at(i)&&tree_SecInt_layer->at(i)!=0 && abs(tree_SecInt_x->at(i))<25 && abs(tree_SecInt_y->at(i))<25 && abs(tree_SecInt_eta->at(i))<1.4 && abs(tree_SecInt_z->at(i))<27)
      {
        hData_Veto->Fill(tree_SecInt_x->at(i),tree_SecInt_y->at(i));
      }
    if (tree_SecInt_selec->at(i) && abs(tree_SecInt_x->at(i))<25 && abs(tree_SecInt_y->at(i))<25 && abs(tree_SecInt_eta->at(i))<1.4&&abs(tree_SecInt_z->at(i))<27)
      {
        hData_WoVeto->Fill(tree_SecInt_x->at(i),tree_SecInt_y->at(i));
      }
  }
for (unsigned int k=0 ; k < tree_Hemi->size(); k++)
  {
    TotalnVertex++;
  }




  
    //  Reco Vrtex efficiency pour MC signal
    if(Signal)
      {
        for (unsigned int j = 0 ; j < tree_Hemi_Vtx_NChi2->size(); j ++)
          {
             if ( tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 )
         {
            nRecoVertex++;
            MeanDistance += tree_Hemi_Vtx_dist->at(j);
            if (tree_Hemi_LLP_ping->at(j))
              {
                nRecoVertexPing++;
                MeanDistancePing += tree_Hemi_Vtx_dist->at(j);
                if (tree_Hemi_Vtx_step->at(j)==1)
                  {
                    nRecoVertexStep1Ping++;
                    MeanDistanceStep1Ping += tree_Hemi_Vtx_dist->at(j);
                  }
                if (tree_Hemi_Vtx_step->at(j)==2)
                  {
                    nRecoVertexStep2Ping++;
                    MeanDistanceStep2Ping += tree_Hemi_Vtx_dist->at(j);
                  }
                if (tree_Hemi_Vtx_step->at(j)==3)
                  {
                    nRecoVertexStep3Ping++;
                    MeanDistanceStep3Ping += tree_Hemi_Vtx_dist->at(j);
                  }
              }

            if (tree_Hemi_Vtx_step->at(j)==1)
              {
                nRecoVertexStep1++;
                MeanDistanceStep1 += tree_Hemi_Vtx_dist->at(j);
              }
            if (tree_Hemi_Vtx_step->at(j)==2)
              {
                nRecoVertexStep2++;
                MeanDistanceStep2 += tree_Hemi_Vtx_dist->at(j);
              }
            if (tree_Hemi_Vtx_step->at(j)==3)
              {
                nRecoVertexStep3++;
                MeanDistanceStep3 += tree_Hemi_Vtx_dist->at(j);
              }
          }
        }
      }
    else
      {
          // Reco Vrtex efficiency pour TTbar
for (unsigned int j = 0 ; j < tree_Hemi_Vtx_NChi2->size(); j ++)
   {
      if ( tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 )
         {
            nRecoVertex++;
            MeanDistance += tree_Hemi_Vtx_dist->at(j);
            if (tree_Hemi_Vtx_step->at(j)==1)
              {
                nRecoVertexStep1++;
                MeanDistanceStep1 += tree_Hemi_Vtx_dist->at(j);
              }
            if (tree_Hemi_Vtx_step->at(j)==2)
              {
                nRecoVertexStep2++;
                MeanDistanceStep2 += tree_Hemi_Vtx_dist->at(j);
              }
            if (tree_Hemi_Vtx_step->at(j)==3)
              {
                nRecoVertexStep3++;
                MeanDistanceStep3 += tree_Hemi_Vtx_dist->at(j);
              }
         }
   }
      }

    std::cout << "number of events  "<< allevents << std::endl; 
//  std::cout << "number of tracks  "<< nRecoTracks << std::endl; 
//  std::cout << "number of jets    "<< nJets << std::endl; 

//---------------Vtx Selection Variables----------------//
  //------------------MWT CUT -------------------//
  for (int i =0 ;i<nSteps+1;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_MeantrackWeight->at(j)>(MeanTWcut+i*dTW) )
            {
              nSelecVtx[i]++;
              
              if (tree_Hemi_Vtx_step->at(j)==1)
                {
                  nSelecVtxStep1[i]++;
                }
            }
        }

    for (unsigned int i = 0 ; i < tree_Hemi_Vtx_NChi2->size(); i++)
      {
        if (tree_Hemi_Vtx_NChi2->at(i)>0 && tree_Hemi_Vtx_NChi2->at(i)<10)
          {
            hData_Vts_nTrks_vs_MWT->Fill(tree_Hemi_Vtx_nTrks->at(i),tree_Hemi_Vtx_MeantrackWeight->at(i));
          }
      }
    //-----------------------------------//
    }

    for (unsigned int j = 0 ; j < tree_Hemi_Vtx_NChi2->size(); j++)
      {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_MeantrackWeight->at(j)>=2 )
            {
              nRecoVertexMTW2++;
              if (Signal){
                if (tree_Hemi_LLP_ping->at(j))
                    {
                      nRecoVertexMTW2Ping++;
                    }
              }
             
              if (tree_Hemi_Vtx_step->at(j)==1)
                {
                  nRecoVertexStep1MTW2++;
                  if(Signal)
                    {
                  if (tree_Hemi_LLP_ping->at(j))
                    {
                      nRecoVertexStep1MTW2Ping++;
                    }
                    }

                }
              if (tree_Hemi_Vtx_step->at(j)==2)
                {
                  nRecoVertexStep2MTW2++;
                  if(Signal)
                  {
                  if (tree_Hemi_LLP_ping->at(j))
                    {
                      nRecoVertexStep2MTW2Ping++;
                    }
                  }

                }
              if (tree_Hemi_Vtx_step->at(j)==3)
                {
                  nRecoVertexStep3MTW2++;
                  if(Signal)
                  {
                    if (tree_Hemi_LLP_ping->at(j))
                    {
                      nRecoVertexStep3MTW2Ping++;
                    }
                  }

                }
            }
      }
//-----------------------------
// int nStep_dR = ;
// int nStep_InvMass = ;// needs btagging to be implemented
//-----------

//-----------------------------

//--------ntrk10------
//--------ntrk20------
// std::cout<<"debug 1"<<std::endl;
  for (int i =0 ;i<nStep_10;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_ntrk10->at(j)>=(ntrk10Cut+i*dntrk10))
            {
              nEvts_ntrk10[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2)
                {
                  nEvts_ntrk10_step1[i]++;
                }
            }
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_ntrk20->at(j)>=(ntrk20Cut+i*dntrk20))
            {
              nEvts_ntrk20[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2)
                {
                  nEvts_ntrk20_step1[i]++;
                }
            }
        }
    }
// std::cout<<"debug 2"<<std::endl;
// --------Vtx_dd------

  for (int i =0 ;i<nStep_dd;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_Vtx_dd->at(j)>=(VtxddCut+i*ddd))
            {
              nEvts_Vtx_dd[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2 )
                {
                  nEvts_Vtx_dd_step1[i]++;
                }
            }
        }
    }
// std::cout<<"debug 3"<<std::endl;
    //--------Vtx_nTrks------
//-----------------------------

  for (int i =0 ;i<nStep_nTrks;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_nTrks->at(j)>=(VtxnTrksCut+i*dnTrks))
            {
              nEvts_Vtx_nTrks[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2)
                {
                  nEvts_Vtx_nTrks_step1[i]++;
                }
            }
        }
    }
// std::cout<<"debug 4"<<std::endl;
//--------Vtx_nVtx------
  for (int i =0 ;i<nStep_nVtx;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi_Vtx_nVtx->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_nVtx->at(j)>=(VtxnVtxCut+i*dnVtx))
            {
              nEvts_Vtx_nVtx[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2 )
                {
                  nEvts_Vtx_nVtx_step1[i]++;
                }
            }
        }
    }
//-----------------------------------------------

//--------Vtx_Chi2------

// float nEvts_Vtx_Chi2_step1[100] = {0};
  for (int i =0 ;i<nStep_Chi2;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_NChi2->at(j)>=(VtxChi2Cut+i*dChi2))
            {
              nEvts_Vtx_Chi2[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2)
                {
                  nEvts_Vtx_Chi2_step1[i]++;
                }
            }
        }
    }
//-----------------------------------------------

//--------Vtx_Step------

  for (int i =0 ;i<nStep_Step;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_step->at(j)>=(VtxStepCut+i*dStep))
            {
              nEvts_Vtx_Step[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2)
                {
                  nEvts_Vtx_Step_step1[i]++;
                }
            }
        }
    }
//-----------------------------------------------

//--------Vtx_InvMass------
  for (int i =0 ;i<nStep_Mass;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_Mass->at(j)>=(VtxMassCut+i*dMass))
            {
              nEvts_Vtx_Mass[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2)
                {
                  nEvts_Vtx_Mass_step1[i]++;
                }
            }
        }
    }
//-----------------------------------------------

//--------Vtx_DCA tracks------

  for (int i =0 ;i<nStep_DCA;i++)
    {
      for (unsigned int j = 0 ; j< tree_Hemi->size();j++)
        {
          if (tree_Hemi_Vtx_NChi2->at(j)>0 && tree_Hemi_Vtx_NChi2->at(j)<10 && tree_Hemi_Vtx_nTrks->at(j)>=(VtxDCACut+i*dDCA))
            {
              nEvts_Vtx_DCA[i]++;
              if (tree_Hemi_Vtx_step->at(j)==1 || tree_Hemi_Vtx_step->at(j)==2)
                {
                  nEvts_Vtx_DCA_step1[i]++;
                }
            }
        }
    }


  //-------------------------------------------------------------------//
  //--------------------------EVTS Selection Variables-----------------//
//--------Leadingjet pt------
for (int i = 0 ; i < nStep_jet_pt ; i++)
  {
    for (unsigned int j = 0 ; j < tree_jet_leadingpt->size() ; j++)
      {
        if (tree_jet_leadingpt->at(j) > (JetPTCut+i*dpt))
          {
            nEvts_jetpt[i]++;
          }
      }
  }

//--------subLeadingjet pt------
for (int i = 0 ; i < nStep_jet2_pt ; i++)
  {
    for (unsigned int j = 0 ; j < tree_jet_leadingpt2->size() ; j++)
      {
        if (tree_jet_leadingpt2->at(j) > (Jet2PTCut+i*dpt2))
          {
            nEvts_jetpt2[i]++;
          }
      }
  }

//--------Leadingmuon pt------
for (int i = 0 ; i < nStep_muon_pt ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_leadingpt->size() ; j++)
      {
        if (tree_muon_leadingpt->at(j) > (MuonPTCut+i*dpt_muon))
          {
            nEvts_muonpt[i]++;
          }
      }
  }

//--------subLeading muon pt------
for (int i = 0 ; i < nStep_muon2_pt ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_leadingpt2->size() ; j++)
      {
        if (tree_muon_leadingpt2->at(j) > (Muon2PTCut+i*dpt_muon2))
          {
            nEvts_muon2pt[i]++;
          }
      }
  }

//--------HT------
for (int i = 0 ; i < nStep_HT_pt ; i++)
  {
    // for (unsigned int j = 0 ; j < tree_ST->size() ; j++)
    //   {
        if (tree_HT > (HTCut+i*dpt_HT))
          {
            nEvts_HT[i]++;
          }
      // }
  }

//--------ST------

for (int i = 0 ; i < nStep_ST_pt ; i++)
  {
    for (unsigned int j = 0 ; j < tree_ST->size() ; j++)
      {
        if (tree_ST->at(j) > (STCut+i*dpt_ST))
          {
            nEvts_ST[i]++;
          }
      }
  }

//--------nJets
for (int i = 0 ; i < nStep_nJet ; i++)
  {
    for (unsigned int j = 0 ; j < tree_ST->size() ; j++)
      {
        if (tree_njet > (nJetCut+i*dnJet_ST))
          {
            nEvts_nJet[i]++;
          }
      }
  }

  //-------------nmu----------//

for (int i = 0 ; i < nStep_nMuon ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_nmu->size() ; j++)
      {
        if (tree_muon_nmu->at(j) > (nMuonCut+i*dnMuon))
          {
            nEvts_nMuon[i]++;
          }
      }
  }
// //------------------------------

// //-------------muon_muon_dR----------//

for (int i = 0 ; i < nStep_MuondR ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_muon_dR->size() ; j++)
      {
        if (tree_muon_muon_dR->at(j) > (MuondRCut+i*dMuondR))
          {
            nEvts_MuondR[i]++;
          }
      }
  }
// //------------------------------

// //-------------muon_muon_dPhi----------//

for (int i = 0 ; i < nStep_MuondPhi ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_muon_dPhi->size() ; j++)
      {
        if (tree_muon_muon_dPhi->at(j) > (MuondPhiCut+i*dMuondPhi))
          {
            nEvts_MuondPhi[i]++;
          }
      }
  }
// //------------------------------

// //-------------muon_muon_dEta----------//

for (int i = 0 ; i < nStep_MuondEta ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_muon_dEta->size() ; j++)
      {
        if (tree_muon_muon_dEta->at(j) > (MuondEtaCut+i*dMuondEta ))
          {
            nEvts_MuondEta[i]++;
          }
      }
  }
// //------------------------------

// //-------------jet_jet_dR----------//

for (int i = 0 ; i < nStep_JetdR ; i++)
  {
    for (unsigned int j = 0 ; j < tree_jet_jet_dR->size() ; j++)
      {
        if (tree_jet_jet_dR->at(j) > (JetdRCut+i*dJetdR))
          {
            nEvts_JetdR[i]++;
          }
      }
  }
// //------------------------------

// //-------------jet_jet_dPhi----------//

for (int i = 0 ; i < nStep_JetdPhi ; i++)
  {
    for (unsigned int j = 0 ; j < tree_jet_jet_dPhi->size() ; j++)
      {
        if (tree_jet_jet_dPhi->at(j) > (JetdPhiCut+i*dJetdPhi))
          {
            nEvts_JetdPhi[i]++;
          }
      }
  }
// //------------------------------

// //-------------jet_jet_dEta----------//

for (int i = 0 ; i < nStep_JetdEta ; i++)
  {
    for (unsigned int j = 0 ; j < tree_jet_jet_dEta->size() ; j++)
      {
        if (tree_jet_jet_dEta->at(j) > (JetdEtaCut+i*dJetdEta))
          {
            nEvts_JetdEta[i]++;
          }
      }
  }
// //------------------------------

// //-------------muon_jet_dRmin----------//

for (int i = 0 ; i < nStep_MuonJetdRmin ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_jet_dRmin->size() ; j++)
      {
        if (tree_muon_jet_dRmin->at(j) > (MuonJetdRminCut+i*dMuonJetdRmin))
          {
            nEvts_MuonJetdRmin[i]++;
          }
      }
  }
// //------------------------------
// //-------------muon_jet_dRmax----------//

for (int i = 0 ; i < nStep_MuonMuonJetdRmax ; i++)
  {
    for (unsigned int j = 0 ; j < tree_muon_jet_dRmax->size() ; j++)
      {
        if (tree_muon_jet_dRmax->at(j) > (MuonJetdRCutmax+i*dMuonJetdRmax))
          {
            nEvts_MuonJetdRmax[i]++;
          }
      }
  }
//------------------------------


//---------------------------
if (tree_Filter)
  {
    nEvts++;
  }

//----------resolution-------------//
	// in PXB:
	// ttree->Draw("tree_SecInt_LLP_dr","tree_SecInt_LLP>0&&tree_SecInt_selec&&tree_SecInt_r>2.6&&tree_SecInt_r<20&&abs(tree_SecInt_z)<27&&tree_SecInt_LLP_dr/tree_SecInt_r<0.1&&tree_SecInt_LLP_dr>0.12")
	// in TIB:
	// ttree->Draw("tree_SecInt_LLP_dr","tree_SecInt_LLP>0&&tree_SecInt_selec&&tree_SecInt_r>22&&tree_SecInt_r<52&&abs(tree_SecInt_z)<68&&tree_SecInt_LLP_dr/tree_SecInt_r<0.1&&tree_SecInt_LLP_dr>0.8")
	// in TOB:
	// ttree->Draw("tree_SecInt_LLP_dr","tree_SecInt_LLP>0&&tree_SecInt_selec&&tree_SecInt_r>50&&tree_SecInt_r<60&&abs(tree_SecInt_z)<108&&tree_SecInt_LLP_dr/tree_SecInt_r<0.1&&tree_SecInt_LLP_dr>3")
	// in PXF:
	// ttree->Draw("tree_SecInt_LLP_dz","tree_SecInt_LLP>0&&tree_SecInt_selec&&tree_SecInt_r>4.5&&tree_SecInt_r<16.5&&abs(tree_SecInt_z)>30&&abs(tree_SecInt_z)<50&&tree_SecInt_LLP_dr/tree_SecInt_r<0.1&&tree_SecInt_LLP_dz>1")
	// in TID:
	// ttree->Draw("tree_SecInt_LLP_dz","tree_SecInt_LLP>0&&tree_SecInt_selec&&tree_SecInt_r>22&&tree_SecInt_r<52&&abs(tree_SecInt_z)>70&&abs(tree_SecInt_z)<110&&tree_SecInt_LLP_dr/tree_SecInt_r<0.1&&tree_SecInt_LLP_dz>2.5")
	// in TEC:
	// ttree->Draw("tree_SecInt_LLP_dz","tree_SecInt_LLP>0&&tree_SecInt_selec&&tree_SecInt_r>20&&tree_SecInt_r<75&&abs(tree_SecInt_z)>120&&abs(tree_SecInt_z)<200&&tree_SecInt_LLP_dr/tree_SecInt_r<0.1&&tree_SecInt_LLP_dz>5")

for (unsigned int i=0;i<tree_SecInt_x->size();i++)
  {

    //GLobal
    if (tree_SecInt_LLP->at(i)>0&&tree_SecInt_selec->at(i)&&abs(tree_SecInt_LLP_dd->at(i))/tree_SecInt_d->at(i)<0.1 &&  abs(tree_SecInt_LLP_dr->at(i))<1)
      {
        hData_SecInt_res_r->Fill(tree_SecInt_LLP_dr->at(i));
        hData_SecInt_res_z->Fill(tree_SecInt_LLP_dz->at(i));
        if(abs(tree_SecInt_eta->at(i))<1.5)
          {
            hData_SecInt_res_r_inf15->Fill(tree_SecInt_LLP_dr->at(i));
            hData_SecInt_res_z_inf15->Fill(tree_SecInt_LLP_dz->at(i));
          }
        else
          {
            hData_SecInt_res_r_sup15->Fill(tree_SecInt_LLP_dr->at(i));
            hData_SecInt_res_z_sup15->Fill(tree_SecInt_LLP_dz->at(i));
          }
      }

    //PIXB 
    if (tree_SecInt_LLP->at(i)>0&&tree_SecInt_selec->at(i)&&tree_SecInt_r->at(i)>2.6&&tree_SecInt_r->at(i)<20&&abs(tree_SecInt_z->at(i))<27&&abs(tree_SecInt_LLP_dd->at(i))/tree_SecInt_d->at(i)<0.1)
      {
        hData_SecInt_res_r_PIXB->Fill(tree_SecInt_LLP_dr->at(i));
        hData_SecInt_res_z_PIXB->Fill(tree_SecInt_LLP_dz->at(i));
      }

    //TIB
    if(tree_SecInt_LLP->at(i)>0&&tree_SecInt_selec->at(i)&&tree_SecInt_r->at(i)>22&&tree_SecInt_r->at(i)<52&&abs(tree_SecInt_z->at(i))<68&&abs(tree_SecInt_LLP_dr->at(i))/tree_SecInt_r->at(i)<0.1)
      {
        hData_SecInt_res_r_TIB->Fill(tree_SecInt_LLP_dr->at(i));
        hData_SecInt_res_z_TIB->Fill(tree_SecInt_LLP_dz->at(i));
      }
    //TOB

    if(tree_SecInt_LLP->at(i)>0&&tree_SecInt_selec->at(i)&&tree_SecInt_r->at(i)>50&&tree_SecInt_r->at(i)<60&&abs(tree_SecInt_z->at(i))<108&&abs(tree_SecInt_LLP_dr->at(i))/tree_SecInt_r->at(i)<0.1)
      {
        hData_SecInt_res_r_TOB->Fill(tree_SecInt_LLP_dr->at(i));
        hData_SecInt_res_z_TOB->Fill(tree_SecInt_LLP_dz->at(i));
      }

    //PIXF
    if(tree_SecInt_LLP->at(i)>0&&tree_SecInt_selec->at(i)&&tree_SecInt_r->at(i)>4.5&&tree_SecInt_r->at(i)<16.5&&abs(tree_SecInt_z->at(i))>30&&abs(tree_SecInt_z->at(i))<50&&abs(tree_SecInt_LLP_dr->at(i))/tree_SecInt_r->at(i)<0.1)
      {
        hData_SecInt_res_r_PIXF->Fill(tree_SecInt_LLP_dr->at(i));
        hData_SecInt_res_z_PIXF->Fill(tree_SecInt_LLP_dz->at(i));
      }

    //TID
    if(tree_SecInt_LLP->at(i)>0&&tree_SecInt_selec->at(i)&&tree_SecInt_r->at(i)>22&&tree_SecInt_r->at(i)<52&&abs(tree_SecInt_z->at(i))>70&&abs(tree_SecInt_z->at(i))<110&&abs(tree_SecInt_LLP_dr->at(i))/tree_SecInt_r->at(i)<0.1)
      {
        hData_SecInt_res_r_TID->Fill(tree_SecInt_LLP_dr->at(i));
        hData_SecInt_res_z_TID->Fill(tree_SecInt_LLP_dz->at(i));
      }


    //TEC
    if(tree_SecInt_LLP->at(i)>0&&tree_SecInt_selec->at(i)&&tree_SecInt_r->at(i)>20&&tree_SecInt_r->at(i)<75&&abs(tree_SecInt_z->at(i))>120&&abs(tree_SecInt_z->at(i))<200&&abs(tree_SecInt_LLP_dr->at(i))/tree_SecInt_r->at(i)<0.1)
      {
        hData_SecInt_res_r_TEC->Fill(tree_SecInt_LLP_dr->at(i));
        hData_SecInt_res_z_TEC->Fill(tree_SecInt_LLP_dz->at(i));
      }
    
  }

for (unsigned int k =0 ; k<tree_genAxis_dRneuneu->size() ; k++)
  {
    hGen_dRneuneu->Fill(tree_genAxis_dRneuneu->at(k));
    hGen_dPhineuneu->Fill(abs(tree_genAxis_dPhineuneu->at(k)));
    hGen_dEtaneuneu->Fill(abs(tree_genAxis_dEtaneuneu->at(k)));
  }

//--------------genJets---------------------//
for (unsigned int k=0 ; k < tree_genJet_pt->size(); k++)
  {
    hGen_Jet_pt->Fill(tree_genJet_pt->at(k));
  }
if (tree_genJet_pt->size()>=2)
    {
      hGen_leadingjet_pt->Fill(tree_genJet_pt->at(0));
      hGen_subleadingjet_pt->Fill(tree_genJet_pt->at(1));
    }
//-------------recojets---------------//
  for (unsigned int k=0 ; k < tree_jet_pt->size(); k++)
  {
    hData_Jet_pt->Fill(tree_jet_pt->at(k));
  }
if (tree_jet_pt->size()>=2)
    {
      hData_leadingjet_pt->Fill(tree_jet_pt->at(0));
      hData_subleadingjet_pt->Fill(tree_jet_pt->at(1));
    }

//---GenMuons-----------------//
int Boom = 0;
for (unsigned int k=0 ; k < tree_genParticle_pdgId->size(); k++)
  {
    if(abs(tree_genParticle_pdgId->at(k))!=13) continue;
    hGen_Muon_pt->Fill(tree_genParticle_pt->at(k));
    Boom++;
  }
  
if (Boom>=2)
    {
      hGen_leadingmuon_pt->Fill(tree_genParticle_pt->at(0));
      hGen_subleadingmuon_pt->Fill(tree_genParticle_pt->at(1));
    }
//---------------------recomuons---------------///
  for (unsigned int k=0 ; k < tree_muon_pt->size(); k++)
  {
    hData_Muon_pt->Fill(tree_muon_pt->at(k));
  }
if (tree_muon_pt->size()>=2)
    {
      hData_leadingmuon_pt->Fill(tree_muon_pt->at(0));
      hData_subleadingmuon_pt->Fill(tree_muon_pt->at(1));
    }
}// end Tree_Filter Condition


 } //--------------------------- end loop on events -----------------------------------------

//  std::cout << " Bug here " << std::endl;

 float sig_max;
 float bdtcutopti = 0;
 float inte = 0;
  for (int i =0; i<nStep;i++)
    {
      // std::cout<<bdtcut+i*delta<<": bdtcut+i*delta& "<<nSelecTracks[i]<<" nSelecTracks[i] "<<std::endl;
      hSignalEff->Fill(bdtcut+i*delta,nSelecTracks[i]/nSTracks);
      hBkgEff->Fill(bdtcut+i*delta,nDiscardTracks[i]/nDTracks);
      hBkfEff_SigEff->Fill(nSelecTracks[i]/nSTracks,1-nDiscardTracks[i]/nDTracks);
      sig[i]=nSelecTracks[i]/sqrt(nSelecTracks[i]+nDiscardTracks[i]);
      inte += sig[i];
      if(i>0)
        {
          sig_max=sig[0];
          if(sig[i]>sig_max)
            {
              sig_max=sig[i];
              bdtcutopti = bdtcut+i*delta;
            } 
        }
      h_sig->Fill(bdtcut+i*delta,sig[i]);
    }
    inte= inte/nStep;
    // std::cout<<"bdtcutopti : "<<bdtcutopti<<std::endl;
    // std::cout<<"inte : "<<inte<<std::endl;
  // double error=0;
  // double AUC = hBkfEff_SigEff->IntegralAndError(0,1,0,1,error);
  // std::cout<<"Integral Value : "<<AUC<<" +-"<<error<<std::endl;
//################################################

float size= TotalnVertex;
float NRecoVertexEff = nRecoVertex/size;

//---------------------VTX Selections Variables----
  for (int i =0 ;i<nSteps+1;i++)
    {
      hData_Vtx_MeanTrackWeight->Fill(MeanTWcut+i*dTW,nSelecVtx[i]/nRecoVertex);
      hData_Vtx_MeanTrackWeight_Step1->Fill(MeanTWcut+i*dTW,nSelecVtxStep1[i]/nRecoVertexStep1);            
    }

for (int h = 0 ; h < nStep_10; h++)
  {
    // std::cout<<nSelecVtx[h]<<std::endl;
      hData_Vtx_nTrk10->Fill(ntrk10Cut+h*dntrk10,nEvts_ntrk10[h]/nRecoVertex);
      hData_Vtx_nTrk10_Step1->Fill(ntrk10Cut+h*dntrk10,nEvts_ntrk10_step1[h]/nRecoVertexStep1);
      hData_Vtx_nTrk20->Fill(ntrk20Cut+h*dntrk20,nEvts_ntrk20[h]/nRecoVertex);
      hData_Vtx_nTrk20_Step1->Fill(ntrk20Cut+h*dntrk20,nEvts_ntrk20_step1[h]/nRecoVertexStep1);
  }

for (int h = 0 ; h < nStep_dd; h++)
  {
    // std::cout<<nSelecVtx[h]<<std::endl;
      hData_Vtx_Vtx_dd->Fill(VtxddCut+h*ddd,nEvts_Vtx_dd[h]/nRecoVertex);
      hData_Vtx_Vtx_dd_Step1->Fill(VtxddCut+h*ddd,nEvts_Vtx_dd_step1[h]/nRecoVertexStep1);
  }
  for (int h = 0 ; h < nStep_nTrks; h++)
  {
    // std::cout<<nSelecVtx[h]<<std::endl;
      hData_Vtx_nTrks->Fill(VtxnTrksCut+h*dnTrks,nEvts_Vtx_nTrks[h]/nRecoVertex);
      hData_Vtx_nTrks_Step1->Fill(VtxnTrksCut+h*dnTrks,nEvts_Vtx_nTrks_step1[h]/nRecoVertexStep1);
  }

//--------------------------------//
  for (int h = 0 ; h < nStep_nVtx; h++)
  {
    // std::cout<<nSelecVtx[h]<<std::endl;
      hData_Vtx_nVtx->Fill(VtxnVtxCut+h*dnVtx,nEvts_Vtx_nVtx[h]/nRecoVertex);
      hData_Vtx_nVtx_Step1->Fill(VtxnVtxCut+h*dnVtx,nEvts_Vtx_nVtx_step1[h]/nRecoVertexStep1);
  }


  for (int h = 0 ; h < nStep_Chi2; h++)
  {
    // std::cout<<nSelecVtx[h]<<std::endl;
      hData_Vtx_NChi2->Fill(VtxChi2Cut+h*dChi2,nEvts_Vtx_Chi2[h]/nRecoVertex);
      hData_Vtx_NChi2_Step1->Fill(VtxChi2Cut+h*dChi2,nEvts_Vtx_Chi2_step1[h]/nRecoVertexStep1);
  }

//--------Vtx_Step------
  for (int h = 0 ; h < nStep_Step; h++)
  {
    // std::cout<<nSelecVtx[h]<<std::endl;
      hData_Vtx_Step->Fill(VtxStepCut+h*dStep,nEvts_Vtx_Step[h]/nRecoVertex);
      hData_Vtx_Step_Step1->Fill(VtxStepCut+h*dStep,nEvts_Vtx_Step_step1[h]/nRecoVertexStep1);
  }

//--------Vtx_InvMass------
  for (int h = 0 ; h < nStep_Mass; h++)
  {
    // std::cout<<nSelecVtx[h]<<std::endl;
      hData_Vtx_Mass->Fill(VtxMassCut+h*dMass,nEvts_Vtx_Mass[h]/nRecoVertex);
      hData_Vtx_Mass_Step1->Fill(VtxMassCut+h*dMass,nEvts_Vtx_Mass_step1[h]/nRecoVertexStep1);
  }

//-----------------------------------------------

//--------Vtx_DCA tracks------

  for (int h = 0 ; h < nStep_DCA; h++)
  {
      hData_Vtx_DCA->Fill(VtxDCACut+h*dDCA,nEvts_Vtx_DCA[h]/nRecoVertex);
      hData_Vtx_DCA_Step1->Fill(VtxDCACut+h*dDCA,nEvts_Vtx_DCA_step1[h]/nRecoVertexStep1);
  }

//--------------------------------------------

//------------Evts Selection Variables------------------------
for(int h =0 ; h < nStep_jet_pt;h++)
  {
    hData_Evts_LeadingJetPt->Fill(JetPTCut+h*dpt,nEvts_jetpt[h]/nEvts);
  }

  for(int h =0 ; h < nStep_jet2_pt;h++)
  {
    hData_Evts_LeadingJet2Pt->Fill(Jet2PTCut+h*dpt,nEvts_jetpt2[h]/nEvts);
  }

for(int h =0 ; h < nStep_muon_pt;h++)
  {
    hData_Evts_LeadingMuonPt->Fill(MuonPTCut+h*dpt_muon,nEvts_muonpt[h]/nEvts);
  }

for(int h =0 ; h < nStep_muon2_pt;h++)
  {
    hData_Evts_LeadingMuon2Pt->Fill(Muon2PTCut+h*dpt_muon2,nEvts_muon2pt[h]/nEvts);
  }

for(int h =0 ; h < nStep_HT_pt;h++)
  {
    hData_Evts_HT->Fill(HTCut+h*dpt_HT,nEvts_HT[h]/nEvts);
  }

for(int h =0 ; h < nStep_ST_pt;h++)
  {
    hData_Evts_ST->Fill(STCut+h*dpt_ST,nEvts_ST[h]/nEvts);
  }
for(int h =0 ; h < nStep_nJet;h++)
  {
    hData_Evts_nJets->Fill(nJetCut+h*dnJet_ST,nEvts_nJet[h]/nEvts);
  }
//--------------------------------//
  for(int h =0 ; h < nStep_nMuon;h++)
  {
    hData_Evts_nMuon->Fill(nMuonCut+h*dnMuon,nEvts_nMuon[h]/nEvts);
  }

// //------------------------------
  for(int h =0 ; h < nStep_MuondR;h++)
  {
    hData_Evts_MuondR->Fill(MuondRCut+h*dMuondR,nEvts_MuondR[h]/nEvts);
  }

// //------------------------------

// //-------------muon_muon_dPhi----------//
  for(int h =0 ; h < nStep_MuondPhi;h++)
  {
    hData_Evts_MuondPhi->Fill(MuondPhiCut+h*dMuondPhi,nEvts_MuondPhi[h]/nEvts);
  }

// //------------------------------

// //-------------muon_muon_dEta----------//
  for(int h =0 ; h < nStep_MuondEta;h++)
  {
    hData_Evts_MuondEta->Fill(MuondEtaCut+h*dMuondEta,nEvts_MuondEta[h]/nEvts);
  }

// //------------------------------

// //-------------jet_jet_dR----------//
  for(int h =0 ; h < nStep_JetdR;h++)
  {
    hData_Evts_jet_jet_dR->Fill(JetdRCut+h*dJetdR,nEvts_JetdR[h]/nEvts);
  }

// //------------------------------

// //-------------jet_jet_dPhi----------//

  for(int h =0 ; h < nStep_JetdPhi;h++)
  {
    hData_Evts_jet_jet_dPhi->Fill(JetdPhiCut+h*dJetdPhi,nEvts_JetdPhi[h]/nEvts);
  }
// //------------------------------

// //-------------jet_jet_dEta----------//
  for(int h =0 ; h < nStep_JetdEta;h++)
  {
    hData_Evts_jet_jet_dEta->Fill(JetdEtaCut+h*dJetdEta,nEvts_JetdEta[h]/nEvts);
  }

// //------------------------------

// //-------------muon_jet_dRmin----------//
  for(int h =0 ; h < nStep_MuonJetdRmin;h++)
  {
    hData_Evts_muon_jet_dRmin->Fill(MuonJetdRminCut+h*dMuonJetdRmin,nEvts_MuonJetdRmin[h]/nEvts);
  }

// //------------------------------
// //-------------muon_jet_dRmax----------//
  for(int h =0 ; h < nStep_MuonMuonJetdRmax;h++)
  {
    hData_Evts_muon_jet_dRmax->Fill(MuonJetdRCutmax+h*dMuonJetdRmax,nEvts_MuonJetdRmax[h]/nEvts);
  }

//------------------------------------------------

    string file = "BKG";
    // string fileNtuple = "./Efficacity_"+file+".txt";
    // std::ofstream ofs (fileNtuple,std::ofstream::out);
std::ofstream ofs ("Efficacity_BKG.txt", std::ofstream::out);







float MeanD = MeanDistance/nRecoVertex;
float MeanDping = MeanDistance/nRecoVertexPing;
float MeanDStep1 = MeanDistanceStep1/nRecoVertexStep1;
float MeanDStep1ping = MeanDistanceStep1Ping/nRecoVertexStep1Ping;
float MeanDStep2 = MeanDistanceStep2/nRecoVertexStep2;
float MeanDStep2ping = MeanDistanceStep2Ping/nRecoVertexStep2Ping;
float MeanDStep3 = MeanDistanceStep3/nRecoVertexStep3;
float MeanDStep3ping = MeanDistanceStep3Ping/nRecoVertexStep3Ping;

std::cout<<" nRecoVertex with good chi2 : "<<nRecoVertex<<std::endl;
std::cout<<" nRecoVertex with ping : "<<nRecoVertexPing<<std::endl;
std::cout<<" nRecoVertex with godd chi2 step1 : "<<nRecoVertexStep1<<std::endl;
std::cout<<" nRecoVertex with ping step1: "<<nRecoVertexStep1Ping<<std::endl;
std::cout<<" nRecoVertex with godd chi2 step2 : "<<nRecoVertexStep2<<std::endl;
std::cout<<" nRecoVertex with ping step2: "<<nRecoVertexStep2Ping<<std::endl;
std::cout<<" nRecoVertex with godd chi2 step3 : "<<nRecoVertexStep3<<std::endl;
std::cout<<" nRecoVertex with ping step3: "<<nRecoVertexStep3Ping<<std::endl;
std::cout<<" MeanDistance : "<<MeanD<<std::endl;
std::cout<<" MeanDistance ping: "<<MeanDping<<std::endl;
std::cout<<" MeanDistanceStep1 : "<<MeanDStep1<<std::endl;
std::cout<<" MeanDistance STep1 ping: "<<MeanDStep1ping<<std::endl;
std::cout<<" MeanDStep2 : "<<MeanDStep2<<std::endl;
std::cout<<" MeanDStep2ping : "<<MeanDStep2ping<<std::endl;
std::cout<<" MeanDStep3 : "<<MeanDStep3<<std::endl;
std::cout<<" MeanDStep3ping : "<<MeanDStep3ping<<std::endl;

std::cout<<" Total NRecoVertexEff : "<<NRecoVertexEff<<std::endl;
std::cout<<" Total NRecoVertexEff ping : "<<nRecoVertexPing/size<<std::endl;
std::cout<<" NRecoVertexEff step1: "<<nRecoVertexStep1/nRecoVertex<<std::endl;
std::cout<<"  NRecoVertexEff  step 1 ping: "<<nRecoVertexStep1Ping/nRecoVertex<<std::endl;
std::cout<<"  NRecoVertexEff  step 2: "<<nRecoVertexStep2/nRecoVertex<<std::endl;
std::cout<<" NRecoVertexEffstep 2 ping : "<<nRecoVertexStep2Ping/nRecoVertex<<std::endl;
std::cout<<" NRecoVertexEff step3: "<<nRecoVertexStep3/nRecoVertex<<std::endl;
std::cout<<"  NRecoVertexEff step3 ping: "<<nRecoVertexStep3Ping/nRecoVertex<<std::endl;
// Output Postscript
ofs<<" //----------------- Efficacity for the Ntuple : " << file << " ---------------\\ "<<std::endl; 
ofs<<"||        ---------         || Good Chi2 ||   Ping   || Good chi2 step1 || ping step 1 || Good chi2 step2 || ping step 2 || Good chi2 step3 || ping step 3 ||" <<std::endl;
ofs<<"||        NVertexReco      "<<" ||    "<<nRecoVertex <<"  ||   "<<nRecoVertexPing  <<"   ||       "<<nRecoVertexStep1            <<"      ||     "<<nRecoVertexStep1Ping<<"    ||       "<<nRecoVertexStep2                  <<"      ||     "<<nRecoVertexStep2Ping         <<"    ||       "<<nRecoVertexStep3<<"       ||     "<<nRecoVertexStep3Ping<<"     || "<<std::endl;
ofs<<"|| Mean Distance of flight "<<" ||  "<<MeanD         <<"  ||   "<<MeanDping         <<"  ||     "  <<MeanDStep1                  <<"     ||   "   <<MeanDStep1ping<<"   ||     "<<MeanDStep2                                 <<"     ||    "<<MeanDStep2ping                 <<"   ||     "<<MeanDStep3<<"     ||   "<<MeanDStep3ping<<"   || "<<std::endl;
ofs<<"||           Eff           "<<" ||  "<<NRecoVertexEff <<" || "<<nRecoVertexPing/size <<" ||   "    <<nRecoVertexStep1/nRecoVertex<<"      ||    " <<nRecoVertexStep1Ping/nRecoVertex<<" ||    "<<nRecoVertexStep2/nRecoVertex<<"     ||   "<<nRecoVertexStep2Ping/nRecoVertex<<"  ||     "<<nRecoVertexStep3/nRecoVertex<<"   ||  "<<nRecoVertexStep3Ping/nRecoVertex<<"  || "<<std::endl;
ofs<<"||           MTW>=2        "<<" ||  "<<nRecoVertexMTW2 <<" || "<<nRecoVertexMTW2Ping <<" ||   "    <<nRecoVertexStep1MTW2<<"      ||    " <<nRecoVertexStep1MTW2Ping<<" ||    "<<nRecoVertexStep2MTW2<<"     ||   "<<nRecoVertexStep2MTW2Ping<<"  ||     "<<nRecoVertexStep3MTW2<<"   ||  "<<nRecoVertexStep3MTW2Ping<<"  || "<<std::endl;
ofs<<"|| NVertex To be reco : "<<size<<std::endl;
ofs<<" //----------------- End of Table ---------------\\ "<<std::endl; 
ofs.close();

//   TCanvas* c = new TCanvas("c");
  hData_nPV -> Draw(); 
//   c->Print("output.ps(");
  
//################################################
  HistogramManager h ;
  
  h.WriteAllHistogramsInFile(filename.Data(),"recreate");
//################################################
}
