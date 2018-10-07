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
void Mbb_For_Sig_Bkg_Obs()
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
   reader->AddVariable( "NJ_ingap",              &NJ_ingap );
   reader->AddVariable( "pt_All",                 &pt_All );
   reader->AddVariable( "pz_All",                 &pz_All );
   reader->AddVariable( "Njet_20",                 &Njet_20 );
   reader->AddVariable( "HTT_rest_20",            &HTT_rest_20 );
   reader->AddVariable( "E_rest_20",            &E_rest_20 );
   reader->AddSpectator( "minvbb",                 &minvbb );

   reader->BookMVA("TMVAClassification_BDTG", "dataset/weights/TMVAClassification_BDTG.weights.xml" );

// ***************************************************************************************************************
   TFile * f0  = new TFile("../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_VBFHToBB_M_125_.root");
   TFile * f1  = new TFile("../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_GluGluHToBB_M125_.root");
   TFile * f2  = new TFile("../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_Data_5perc_.root");
   TFile * f3  = new TFile("../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_Full_Data_.root");

   TTree * ntps0 = (TTree*)f0->Get("Sig");
   TTree * ntps1 = (TTree*)f1->Get("Sig");
   TTree * ntpb = (TTree*)f2->Get("Bkg");
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

   Float_t MyS1_weight,MyS1_minvqq,MyS1_detaqq,MyS1_dphiqq,MyS1_btgb1_D,MyS1_btgb2_D,MyS1_qtgq1,MyS1_qtgq2,MyS1_NJ_ingap,MyS1_pt_All,MyS1_pz_All,MyS1_Njet_20,MyS1_HTT_rest_20,MyS1_E_rest_20,MyS1_minvbb;
   ntps1->SetBranchAddress( "weight",                   &MyS1_weight );
   ntps1->SetBranchAddress( "mqq",                   &MyS1_minvqq );
   ntps1->SetBranchAddress( "detaqq",                &MyS1_detaqq );
   ntps1->SetBranchAddress( "dphiqq",                &MyS1_dphiqq );
   ntps1->SetBranchAddress( "btgb1_D",                 &MyS1_btgb1_D );
   ntps1->SetBranchAddress( "btgb2_D",                 &MyS1_btgb2_D );
   ntps1->SetBranchAddress( "qtgq1",                 &MyS1_qtgq1 );
   ntps1->SetBranchAddress( "qtgq2",                 &MyS1_qtgq2 );
   ntps0->SetBranchAddress( "NJ_ingap",                 &MyS1_NJ_ingap );
   ntps1->SetBranchAddress( "pt_All",                 &MyS1_pt_All );
   ntps1->SetBranchAddress( "pz_All",                 &MyS1_pz_All );
   ntps1->SetBranchAddress( "Njet_20",                 &MyS1_Njet_20 );
   ntps1->SetBranchAddress( "HTT_rest_20",                 &MyS1_HTT_rest_20 );
   ntps1->SetBranchAddress( "E_rest_20",                 &MyS1_E_rest_20 );
   ntps1->SetBranchAddress( "minvbb",                 &MyS1_minvbb );


   Float_t MyB_weight,MyB_minvqq,MyB_detaqq,MyB_dphiqq,MyB_btgb1_D,MyB_btgb2_D,MyB_qtgq1,MyB_qtgq2,MyB_NJ_ingap,MyB_pt_All,MyB_pz_All,MyB_Njet_20,MyB_HTT_rest_20,MyB_E_rest_20,MyB_minvbb;
   ntpb->SetBranchAddress( "weight",                   &MyB_weight );
   ntpb->SetBranchAddress( "mqq",                   &MyB_minvqq );
   ntpb->SetBranchAddress( "detaqq",                &MyB_detaqq );
   ntpb->SetBranchAddress( "dphiqq",                &MyB_dphiqq );
   ntpb->SetBranchAddress( "btgb1_D",                 &MyB_btgb1_D );
   ntpb->SetBranchAddress( "btgb2_D",                 &MyB_btgb2_D );
   ntpb->SetBranchAddress( "qtgq1",                 &MyB_qtgq1 );
   ntpb->SetBranchAddress( "qtgq2",                 &MyB_qtgq2 );
   ntpb->SetBranchAddress( "NJ_ingap",                 &MyB_NJ_ingap );
   ntpb->SetBranchAddress( "pt_All",                 &MyB_pt_All );
   ntpb->SetBranchAddress( "pz_All",                 &MyB_pz_All );
   ntpb->SetBranchAddress( "Njet_20",                 &MyB_Njet_20 );
   ntpb->SetBranchAddress( "HTT_rest_20",                 &MyB_HTT_rest_20 );
   ntpb->SetBranchAddress( "E_rest_20",                 &MyB_E_rest_20 );
   ntpb->SetBranchAddress( "minvbb",                 &MyB_minvbb );

   Float_t MyO_weight,MyO_minvqq,MyO_detaqq,MyO_dphiqq,MyO_btgb1_D,MyO_btgb2_D,MyO_qtgq1,MyO_qtgq2,MyO_NJ_ingap,MyO_pt_All,MyO_pz_All,MyO_Njet_20,MyO_HTT_rest_20,MyO_E_rest_20,MyO_minvbb;
   ntpo->SetBranchAddress( "weight",                   &MyO_weight );
   ntpo->SetBranchAddress( "mqq",                   &MyO_minvqq );
   ntpo->SetBranchAddress( "detaqq",                &MyO_detaqq );
   ntpo->SetBranchAddress( "dphiqq",                &MyO_dphiqq );
   ntpo->SetBranchAddress( "btgb1_D",                 &MyO_btgb1_D );
   ntpo->SetBranchAddress( "btgb2_D",                 &MyO_btgb2_D );
   ntpo->SetBranchAddress( "qtgq1",                 &MyO_qtgq1 );
   ntpo->SetBranchAddress( "qtgq2",                 &MyO_qtgq2 );
   ntpb->SetBranchAddress( "NJ_ingap",                 &MyO_NJ_ingap );
   ntpo->SetBranchAddress( "pt_All",                 &MyO_pt_All );
   ntpo->SetBranchAddress( "pz_All",                 &MyO_pz_All );
   ntpo->SetBranchAddress( "Njet_20",                 &MyO_Njet_20 );
   ntpo->SetBranchAddress( "HTT_rest_20",                 &MyO_HTT_rest_20 );
   ntpo->SetBranchAddress( "E_rest_20",                 &MyO_E_rest_20 );
   ntpo->SetBranchAddress( "minvbb",                 &MyO_minvbb );

//***************************************************************************************
  TFile *f = new TFile("Mbb_All.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");
  TH1D * _MinvS0  = new TH1D("sig0","sig0",50,0,500);
  TH1D * _MinvS1  = new TH1D("sig1","sig1",50,0,500);
  TH1D * _MinvB   = new TH1D("bkg","bkg",50,0,500);
  TH1D * _MinvO   = new TH1D("data_obs","data_obs",50,0,500);

//***************************************************************************************
   double BDT_Cut_Max= 1.0;
   double BDT_Cut_Min= 0.8;

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
     if(reader->EvaluateMVA("TMVAClassification_BDTG")<=BDT_Cut_Min) continue;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")>BDT_Cut_Max) continue;
    _MinvS0->Fill(minvbb,My_weight);
    }
    _MinvS0->Scale(0.003405276);

   for(int i=0;i<ntps1->GetEntries();i++)
    {
     ntps1->GetEntry(i);
     minvqq   = MyS1_minvqq;
     detaqq   = MyS1_detaqq;
     dphiqq   = MyS1_dphiqq;
     btgb1_D  = MyS1_btgb1_D;
     btgb2_D  = MyS1_btgb2_D;
     qtgq1    = MyS1_qtgq1;
     qtgq2    = MyS1_qtgq2;
     NJ_ingap = MyS1_NJ_ingap;
     pt_All   = MyS1_pt_All;
     pz_All   = MyS1_pz_All;
     Njet_20  = MyS1_Njet_20;
     HTT_rest_20  = MyS1_HTT_rest_20;
     E_rest_20  = MyS1_E_rest_20;
     minvbb   = MyS1_minvbb;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")<=BDT_Cut_Min) continue;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")>BDT_Cut_Max) continue;
    _MinvS1->Fill(minvbb,MyS1_weight);
    }
    _MinvS1->Scale(0.023927598);


   for(int i=0;i<ntpb->GetEntries();i++)
    {
     ntpb->GetEntry(i);
     minvqq   = MyB_minvqq;
     detaqq   = MyB_detaqq;
     dphiqq   = MyB_dphiqq;
     btgb1_D  = MyB_btgb1_D;
     btgb2_D  = MyB_btgb2_D;
     qtgq1    = MyB_qtgq1;
     qtgq2    = MyB_qtgq2;
     NJ_ingap = MyB_NJ_ingap;
     pt_All   = MyB_pt_All;
     pz_All   = MyB_pz_All;
     Njet_20  = MyB_Njet_20;
     HTT_rest_20  = MyB_HTT_rest_20;
     E_rest_20  = MyB_E_rest_20;
     minvbb   = MyB_minvbb;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")<=BDT_Cut_Min) continue;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")>BDT_Cut_Max) continue;
    _MinvB->Fill(minvbb,MyB_weight);
    }
    _MinvB->Scale(20);


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
     if(reader->EvaluateMVA("TMVAClassification_BDTG")<=BDT_Cut_Min) continue;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")>BDT_Cut_Max) continue;
    _MinvO->Fill(minvbb,MyO_weight);
    }
  f->Write();
  delete f1;
}

