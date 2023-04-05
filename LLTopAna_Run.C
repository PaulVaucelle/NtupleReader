{
 gROOT->Reset() ; 

 // Compile user's analysis class //
   gROOT->ProcessLine(".L HistogramManager.C+g") ;
   gROOT->ProcessLine(".L LLTopAna.C+g") ;
  
 if (gROOT->GetClass("LLTopAna")==0) return;//LLTopTree
 
 TChain c("FlyingTop/ttree");

////////////////////////////////////////////////////////////////////////////////

// c.Add("/opt/sbg/cms/ui2_data1/blochd/NTUPLES_FLY/CMSSW_10_6_20/MC/2018_230118/UDD_bgctau50_smu275_snu225_BDTrecohp_step3.root");
// c.Add("/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_20_FLY/src/FlyingTop/FlyingTop/test/Ntuple_TT_Daniel.root");
c.Add("/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_20_FLY/src/FlyingTop/FlyingTop/test/Ntuple_TT_04_04_23_NoVeto.root");
// c.Add("/opt/sbg/cms/ui2_data1/pvaucell/CMSSW_10_6_20_FLY/src/FlyingTop/FlyingTop/test/Ntuple_10cm_Neu_Daniel.root");
////////////////////////////////////////////////////////////////////////////////


// Ntuple_50cm_TT_NewBDT.root
// Ntuple_70cm_Neu_NewBDT.root
// Ntuple_50cm_Neu_NewBDT.root
// Ntuple_30cm_Neu_NewBDT.root
// Ntuple_10cm_Neu_NewBDT.root
// Ntuple_50cm_Neu_test.root
// Ntuple_50cm_TT_test.root
 LLTopAna* t = new LLTopAna(&c);

// t->Loop(0,180.,20.,2999.,0.0,2.4,0.,1,"output/h_UDD_bgctau10_smu250_snu200.root");
// t->Loop(0,180.,20.,2999.,0.0,2.4,0.,1,"output/h_UDD_bgctau30_smu300_snu250.root");
t->Loop(0,180.,20.,2999.,0.0,10.,0.,1,"output/h_UDD_bgctau50_smu275_snu225_TT_test.root");
//  t->Loop(0,180.,20.,2999.,0.0,10.,0.,1,"output/h_UDD_bgctau50_smu275_snu225.root");
// t->Loop(0,180.,20.,2999.,0.0,10.,0.,1,"output/h_UDD_bgctau50_smu275_snu225.root");
// t->Loop(0,180.,20.,2999.,0.0,2.4,0.,1,"output/h_UDD_bgctau70_smu250_snu200.root");

////////////////////////////////////////////////////////////////////////////////

}
