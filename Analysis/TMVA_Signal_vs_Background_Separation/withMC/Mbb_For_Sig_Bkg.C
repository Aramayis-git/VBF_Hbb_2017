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
void Mbb_For_Sig_Bkg()
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
   TFile *f0 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_VBFHToBB_M_125_.root");
   TTree * ntps0 = (TTree*)f0->Get("Sig");
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

   TFile *f1 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT200to300_TuneCP5_.root");
   TFile *f2 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT300to500_TuneCP5_.root");
   TFile *f3 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT500to700_TuneCP5_.root");
   TFile *f4 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT700to1000_TuneCP5_.root");
   TFile *f5 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1000to1500_TuneCP5_.root");
   TFile *f6 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1500to2000_TuneCP5_.root");
   TFile *f7 = TFile::Open("../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT2000toInf_TuneCP5_.root");
   TTree * ntpb[7] = { (TTree*)f1->Get("Bkg"),(TTree*)f2->Get("Bkg"),(TTree*)f3->Get("Bkg"),(TTree*)f4->Get("Bkg"),
                       (TTree*)f5->Get("Bkg"),(TTree*)f6->Get("Bkg"),(TTree*)f7->Get("Bkg")
                     };
   int nBProc = sizeof(ntpb)/sizeof(ntpb[0]);

   Float_t MyB_weight[nBProc],MyB_minvqq[nBProc],MyB_detaqq[nBProc],MyB_dphiqq[nBProc],MyB_btgb1_D[nBProc],MyB_btgb2_D[nBProc],MyB_qtgq1[nBProc],MyB_qtgq2[nBProc],MyB_NJ_ingap[nBProc],MyB_pt_All[nBProc],MyB_pz_All[nBProc],MyB_Njet_20[nBProc],MyB_HTT_rest_20[nBProc],MyB_E_rest_20[nBProc],MyB_minvbb[nBProc];
   for(int k=0;k<nBProc;k++)
   {
    ntpb[k]->SetBranchAddress( "weight",                   &MyB_weight[k]);
    ntpb[k]->SetBranchAddress( "mqq",                   &MyB_minvqq[k]);
    ntpb[k]->SetBranchAddress( "detaqq",                &MyB_detaqq[k]);
    ntpb[k]->SetBranchAddress( "dphiqq",                &MyB_dphiqq[k]);
    ntpb[k]->SetBranchAddress( "btgb1_D",                 &MyB_btgb1_D[k]);
    ntpb[k]->SetBranchAddress( "btgb2_D",                 &MyB_btgb2_D[k]);
    ntpb[k]->SetBranchAddress( "qtgq1",                 &MyB_qtgq1[k]);
    ntpb[k]->SetBranchAddress( "qtgq2",                 &MyB_qtgq2[k]);
    ntpb[k]->SetBranchAddress( "NJ_ingap",                 &MyB_NJ_ingap[k]);
    ntpb[k]->SetBranchAddress( "pt_All",                 &MyB_pt_All[k]);
    ntpb[k]->SetBranchAddress( "pz_All",                 &MyB_pz_All[k]);
    ntpb[k]->SetBranchAddress( "Njet_20",                 &MyB_Njet_20[k]);
    ntpb[k]->SetBranchAddress( "HTT_rest_20",                 &MyB_HTT_rest_20[k]);
    ntpb[k]->SetBranchAddress( "E_rest_20",                 &MyB_E_rest_20[k]);
    ntpb[k]->SetBranchAddress( "minvbb",                 &MyB_minvbb[k]);
   }
//***************************************************************************************
  TFile *f = new TFile("Mbb_All.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");
  TH1D * _MinvS0  = new TH1D("sig0","sig0",50,0,500);
  TH1D * _MinvB   = new TH1D("bkg","bkg",50,0,500);

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
     NJ_ingap    = My_NJ_ingap;
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

  for(int k=0;k<nBProc;k++)
   for(int i=0;i<ntpb[k]->GetEntries();i++)
    {
     ntpb[k]->GetEntry(i);
     minvqq   = MyB_minvqq[k];
     detaqq   = MyB_detaqq[k];
     dphiqq   = MyB_dphiqq[k];
     btgb1_D  = MyB_btgb1_D[k];
     btgb2_D  = MyB_btgb2_D[k];
     qtgq1    = MyB_qtgq1[k];
     qtgq2    = MyB_qtgq2[k];
     NJ_ingap    = MyB_NJ_ingap[k];
     pt_All   = MyB_pt_All[k];
     pz_All   = MyB_pz_All[k];
     Njet_20  = MyB_Njet_20[k];
     HTT_rest_20  = MyB_HTT_rest_20[k];
     E_rest_20  = MyB_E_rest_20[k];
     minvbb   = MyB_minvbb[k];
     if(reader->EvaluateMVA("TMVAClassification_BDTG")<=BDT_Cut_Min) continue;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")>BDT_Cut_Max) continue;
    _MinvB->Fill(minvbb,MyB_weight[k]);
    }


  f->Write();
  delete f1;
}

