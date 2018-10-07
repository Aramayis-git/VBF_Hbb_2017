#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;
void bdt_res()
{
   Float_t minvqq,detaqq,dphiqq,btgb1_D,btgb2_D,qtgq1,qtgq2,NJ_ingap,pt_All,pz_All,Njet_20,HTT_rest_20,E_rest_20,minvbb;
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
   reader->AddVariable( "mqq",                   &minvqq );
   reader->AddVariable( "detaqq",                &detaqq );
   reader->AddVariable( "dphiqq",                &dphiqq );
   reader->AddVariable( "btgb1_D",                 &btgb1_D );
   reader->AddVariable( "btgb2_D",                 &btgb2_D );
   reader->AddVariable( "qtgq1",                 &qtgq1 );
   reader->AddVariable( "qtgq2",                 &qtgq2 );
   reader->AddVariable( "NJ_ingap",                 &NJ_ingap );
   reader->AddVariable( "pt_All",                 &pt_All );
   reader->AddVariable( "pz_All",                 &pz_All );
   reader->AddVariable( "Njet_20",                 &Njet_20 );
   reader->AddVariable( "HTT_rest_20",            &HTT_rest_20 );
   reader->AddVariable( "E_rest_20",            &E_rest_20 );
   reader->AddSpectator( "minvbb",                 &minvbb );

   reader->BookMVA("TMVAClassification_BDTG", "dataset/weights/TMVAClassification_BDTG.weights.xml" );

// ***************************************************************************************************************
   TFile * f0  = new TFile("../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_VBFHToBB_M_125_.root");
   TFile * f3  = new TFile("../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_Full_Data_.root");

   TTree * ntps0 = (TTree*)f0->Get("Sig");
   TTree * ntpo = (TTree*)f3->Get("Bkg");

   Float_t My_weight,My_minvqq,My_detaqq,My_dphiqq,My_btgb1_D,My_btgb2_D,My_qtgq1,My_qtgq2,My_NJ_ingap,My_pt_All,My_pz_All,My_Njet_20,My_HTT_rest_20,My_E_rest_20,My_minvbb;
   ntps0->SetBranchAddress( "weight",                   &My_weight );
   ntps0->SetBranchAddress( "mqq",                   &My_minvqq );
   ntps0->SetBranchAddress( "detaqq",                &My_detaqq );
   ntps0->SetBranchAddress( "dphiqq",                &My_dphiqq );
   ntps0->SetBranchAddress( "btgb1_D",                 &My_btgb1_D );
   ntps0->SetBranchAddress( "btgb2_D",                 &My_btgb2_D );
   ntps0->SetBranchAddress( "qtgq1",                 &My_qtgq1 );
   ntps0->SetBranchAddress( "qtgq2",                 &My_qtgq2 );
   ntps0->SetBranchAddress( "NJ_ingap",                 &My_NJ_ingap );
   ntps0->SetBranchAddress( "pt_All",                 &My_pt_All );
   ntps0->SetBranchAddress( "pz_All",                 &My_pz_All );
   ntps0->SetBranchAddress( "Njet_20",                 &My_Njet_20 );
   ntps0->SetBranchAddress( "HTT_rest_20",                 &My_HTT_rest_20 );
   ntps0->SetBranchAddress( "E_rest_20",                 &My_E_rest_20 );
   ntps0->SetBranchAddress( "minvbb",                 &My_minvbb );

   Float_t MyO_weight,MyO_minvqq,MyO_detaqq,MyO_dphiqq,MyO_btgb1_D,MyO_btgb2_D,MyO_qtgq1,MyO_qtgq2,MyO_NJ_ingap,MyO_pt_All,MyO_pz_All,MyO_Njet_20,MyO_HTT_rest_20,MyO_E_rest_20,MyO_minvbb;
   ntpo->SetBranchAddress( "weight",                   &MyO_weight );
   ntpo->SetBranchAddress( "mqq",                   &MyO_minvqq );
   ntpo->SetBranchAddress( "detaqq",                &MyO_detaqq );
   ntpo->SetBranchAddress( "dphiqq",                &MyO_dphiqq );
   ntpo->SetBranchAddress( "btgb1_D",                 &MyO_btgb1_D );
   ntpo->SetBranchAddress( "btgb2_D",                 &MyO_btgb2_D );
   ntpo->SetBranchAddress( "qtgq1",                 &MyO_qtgq1 );
   ntpo->SetBranchAddress( "qtgq2",                 &MyO_qtgq2 );
   ntpo->SetBranchAddress( "NJ_ingap",                 &MyO_NJ_ingap );
   ntpo->SetBranchAddress( "pt_All",                 &MyO_pt_All );
   ntpo->SetBranchAddress( "pz_All",                 &MyO_pz_All );
   ntpo->SetBranchAddress( "Njet_20",                 &MyO_Njet_20 );
   ntpo->SetBranchAddress( "HTT_rest_20",                 &MyO_HTT_rest_20 );
   ntpo->SetBranchAddress( "E_rest_20",                 &MyO_E_rest_20 );
   ntpo->SetBranchAddress( "minvbb",                 &MyO_minvbb );

//***************************************************************************************
  TFile *f = new TFile("BDT_Output.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");

  TH1D * _BDTS0  = new TH1D("BDTS0","BDTS0",100,-1,1);
  TH1D * _BDTOb  = new TH1D("BDTOb","BDTOb",100,-1,1);


//***************************************************************************************
   for(int i=0;i<ntps0->GetEntries();i++)
    {
     ntps0->GetEntry(i);
     minvqq   = My_minvqq;
     detaqq   = My_detaqq;
     dphiqq   = My_dphiqq;
     btgb1_D  = My_btgb1_D;
     btgb2_D  = My_btgb2_D;
     qtgq1    = My_qtgq1;
     qtgq2    = My_qtgq2;
     NJ_ingap = My_NJ_ingap;
     pt_All   = My_pt_All;
     pz_All   = My_pz_All;
     Njet_20  = My_Njet_20;
     HTT_rest_20  = My_HTT_rest_20;
     E_rest_20  = My_E_rest_20;
     minvbb   = My_minvbb;
     _BDTS0->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),My_weight);
    }
    _BDTS0->Scale(0.0034);

   for(int i=0;i<ntpo->GetEntries();i++)
    {
     ntpo->GetEntry(i);
     minvqq   = MyO_minvqq;
     detaqq   = MyO_detaqq;
     dphiqq   = MyO_dphiqq;
     btgb1_D  = MyO_btgb1_D;
     btgb2_D  = MyO_btgb2_D;
     qtgq1    = MyO_qtgq1;
     qtgq2    = MyO_qtgq2;
     NJ_ingap = MyO_NJ_ingap;
     pt_All   = MyO_pt_All;
     pz_All   = MyO_pz_All;
     Njet_20  = MyO_Njet_20;
     HTT_rest_20  = MyO_HTT_rest_20;
     E_rest_20  = MyO_E_rest_20;
     minvbb   = MyO_minvbb;
     _BDTOb->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyO_weight);
    }
  f->Write();
}

