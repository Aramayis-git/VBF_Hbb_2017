#include "TStyle.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <math.h>
#include <TF1.h>
#include <TF2.h>
#include <TH1D.h>
#include "TCanvas.h"
#include "TROOT.h"
#include "TNtuple.h"


 // D-phi
 double phi_Dist(double a, double b){
   if(fabs(a - b) > 3.14159265)
    return 6.2831853 - fabs(a - b);
   return fabs(a - b);
}


void Sort()
{

  TFile *f1 = new TFile("../../Preselected_NTuples/Training__VBFHToBB_M_125__.root");
  double pi=3.14159265;

//*************************************** True b-jets ***************************************
  TTree *partb1 = (TTree*)f1->Get("Training/B_Jets_True_1");
  TTree *partb2 = (TTree*)f1->Get("Training/B_Jets_True_2");
  TTree *partq1 = (TTree*)f1->Get("Training/Q_Jets_True_1");
  TTree *partq2 = (TTree*)f1->Get("Training/Q_Jets_True_2");
  Float_t ptb1_True,etab1_True,phib1_True,btgb1_True,btgb1_D_True,qtgb1_True,puidb1_True,puid_I_b1_True;
  Float_t ptb2_True,etab2_True,phib2_True,btgb2_True,btgb2_D_True,qtgb2_True,puidb2_True,puid_I_b2_True;
  Float_t ptq1_True,etaq1_True,phiq1_True,btgq1_True,btgq1_D_True,qtgq1_True,puidq1_True,puid_I_q1_True;
  Float_t ptq2_True,etaq2_True,phiq2_True,btgq2_True,btgq2_D_True,qtgq2_True,puidq2_True,puid_I_q2_True;

  partb1->SetBranchAddress("bj1_pt",&ptb1_True);
  partb1->SetBranchAddress("bj1_eta",&etab1_True);
  partb1->SetBranchAddress("bj1_phi",&phib1_True);
  partb1->SetBranchAddress("bj1_btg",&btgb1_True);
  partb1->SetBranchAddress("bj1_btg_D",&btgb1_D_True);
  partb1->SetBranchAddress("bj1_qtg",&qtgb1_True);
  partb1->SetBranchAddress("bj1_puid",&puidb1_True);
  partb1->SetBranchAddress("bj1_puid_I",&puid_I_b1_True);
  partb2->SetBranchAddress("bj2_pt",&ptb2_True);
  partb2->SetBranchAddress("bj2_eta",&etab2_True);
  partb2->SetBranchAddress("bj2_phi",&phib2_True);
  partb2->SetBranchAddress("bj2_btg",&btgb2_True);
  partb2->SetBranchAddress("bj2_btg_D",&btgb2_D_True);
  partb2->SetBranchAddress("bj2_qtg",&qtgb2_True);
  partb2->SetBranchAddress("bj2_puid",&puidb2_True);
  partb2->SetBranchAddress("bj2_puid_I",&puid_I_b2_True);

  partq1->SetBranchAddress("qj1_pt",&ptq1_True);
  partq1->SetBranchAddress("qj1_eta",&etaq1_True);
  partq1->SetBranchAddress("qj1_phi",&phiq1_True);
  partq1->SetBranchAddress("qj1_btg",&btgq1_True);
  partq1->SetBranchAddress("qj1_btg_D",&btgq1_D_True);
  partq1->SetBranchAddress("qj1_qtg",&qtgq1_True);
  partq1->SetBranchAddress("qj1_puid",&puidq1_True);
  partq1->SetBranchAddress("qj1_puid_I",&puid_I_q1_True);
  partq2->SetBranchAddress("qj2_pt",&ptq2_True);
  partq2->SetBranchAddress("qj2_eta",&etaq2_True);
  partq2->SetBranchAddress("qj2_phi",&phiq2_True);
  partq2->SetBranchAddress("qj2_btg",&btgq2_True);
  partq2->SetBranchAddress("qj2_btg_D",&btgq2_D_True);
  partq2->SetBranchAddress("qj2_qtg",&qtgq2_True);
  partq2->SetBranchAddress("qj2_puid",&puidq2_True);
  partq2->SetBranchAddress("qj2_puid_I",&puid_I_q2_True);

  TTree *other = (TTree*)f1->Get("Training/Other_variables");
  Float_t weight;
  other->SetBranchAddress("weight", &weight);
//*************************************** Pt > 20 jets[7] ***************************************
  TString Ntuple_Name[7];
  for(int i=0;i<7;i++) {  Ntuple_Name[i] = "Training/Reco_Jet_Real_";   Ntuple_Name[i] += i;  }
  TTree *jet[7] = { (TTree*)f1->Get(Ntuple_Name[0]), (TTree*)f1->Get(Ntuple_Name[1]), (TTree*)f1->Get(Ntuple_Name[2]),
                    (TTree*)f1->Get(Ntuple_Name[3]), (TTree*)f1->Get(Ntuple_Name[4]), (TTree*)f1->Get(Ntuple_Name[5]),
                    (TTree*)f1->Get(Ntuple_Name[6])
                  };

  TFile *f = new TFile("For_BB_MVA_Training.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");
  TNtuple * _bb = new TNtuple{"bb","bb","weight:pt:pt_ord:e:feta:feta_ord:phi:btg:btg_ord:btg_D:btg_D_ord:qtg:puid:puid_I"};
  TNtuple * _qq = new TNtuple{"qq","qq","weight:pt:pt_ord:e:feta:feta_ord:phi:btg:btg_ord:btg_D:btg_D_ord:qtg:puid:puid_I"};

//***************************************************************************************

  Float_t ptj[7],ej[7],etaj[7],phij[7],btgj[7],btgj_D[7],qtgj[7],puidj[7],puidj_I[7];
  for(int k=0;k<7;k++)
  {
   jet[k]->SetBranchAddress("j_pt",&ptj[k]);
   jet[k]->SetBranchAddress("j_e",&ej[k]);
   jet[k]->SetBranchAddress("j_eta",&etaj[k]);
   jet[k]->SetBranchAddress("j_phi",&phij[k]);
   jet[k]->SetBranchAddress("j_btg",&btgj[k]);
   jet[k]->SetBranchAddress("j_btg_D",&btgj_D[k]);
   jet[k]->SetBranchAddress("j_qtg",&qtgj[k]);
   jet[k]->SetBranchAddress("j_puid",&puidj[k]);
   jet[k]->SetBranchAddress("j_puid_I",&puidj_I[k]);
  }
// ***********************************************************************************

for(int i=0;i<jet[0]->GetEntries();i++)
 {
  other->GetEntry(i);
  partb1->GetEntry(i);
  partb2->GetEntry(i);
  partq1->GetEntry(i);
  partq2->GetEntry(i);
  for(int n=0;n<7;n++)
     jet[n]->GetEntry(i);

// cuts
   double pu_min     = -10.63;
   double PT_min_B1  = 20;
   double PT_min_B2  = 20;
   double PT_min_QQ  = 20;
   double btg_min_B1 = 0.8838;
   double qq_ETA_cut = 4.2;
   double qq_M_cut   = 500;
   double dPHI_Max   = 1.6;
   double btg_min_B2 = -10.5803;

// *************************** Global Check Begin ***************************

   int glcheck=0;
   if(ptb1_True>PT_min_B1 && ptb2_True>PT_min_B2 && puidb1_True>pu_min && puidb2_True>pu_min)// && phi_Dist(phib1_True,phib2_True)<dPHI_Max)
    if((btgb1_True>btg_min_B1 && btgb2_True>btg_min_B2) || (btgb1_True>btg_min_B2 && btgb2_True>btg_min_B1))
     for(int m=0;m<6;m++)
      for(int n=m;n<7;n++)
       if((ptj[m]>PT_min_QQ && ptj[m]!=ptb1_True && ptj[m]!=ptb2_True && puidj[m]>=pu_min) && (ptj[n]>PT_min_QQ && ptj[n]!=ptb1_True && ptj[n]!=ptb2_True && puidj[n]>=pu_min) )
        {
         double pxqq2 = (ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]))*(ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]));
         double pyqq2 = (ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]))*(ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]));
         double pzqq2 = (ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]))*(ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]));
         double eqq2  = (ej[m]+ej[n])*(ej[m]+ej[n]);
         if( (sqrt(eqq2-pxqq2-pyqq2-pzqq2) > qq_M_cut) && (fabs(etaj[m]-etaj[n]) > qq_ETA_cut) )
           glcheck++;
        }
    if(glcheck==0) continue;

// **************************** Global Check END ****************************
   for(int k=0;k<7;k++)
    {
     if(ptj[k]==ptb1_True)     // BB_Ntuple
       {
        int pt_ord=1; int feta_ord=1; int btg_ord=1; int btg_D_ord=1;
        for(int m=0;m<7;m++)
          if(ptj[m]>0)
            {
             if(ptj[m]>ptj[k]) pt_ord++;
             if(fabs(etaj[m])>fabs(etaj[k])) feta_ord++;
             if(btgj[m]>btgj[k] || (btgj[m]==btgj[k] && ptj[m]>ptj[k])) btg_ord++;
             if(btgj_D[m]>btgj_D[k] || (btgj_D[m]==btgj_D[k] && ptj[m]>ptj[k])) btg_D_ord++;
            }
        _bb -> Fill(weight,ptj[k],pt_ord,ej[k],fabs(etaj[k]),feta_ord,phij[k],btgj[k],btg_ord,btgj_D[k],btg_D_ord,qtgj[k],puidj[k],puidj_I[k]);
        continue;
       }

     if(ptj[k]==ptb2_True)     // BB_Ntuple
       {
        int pt_ord=1; int feta_ord=1; int btg_ord=1; int btg_D_ord=1;
        for(int m=0;m<7;m++)
          if(ptj[m]>0)
            {
             if(ptj[m]>ptj[k]) pt_ord++;
             if(fabs(etaj[m])>fabs(etaj[k])) feta_ord++;
             if(btgj[m]>btgj[k] || (btgj[m]==btgj[k] && ptj[m]>ptj[k])) btg_ord++;
             if(btgj_D[m]>btgj_D[k] || (btgj_D[m]==btgj_D[k] && ptj[m]>ptj[k])) btg_D_ord++;
            }
        _bb -> Fill(weight,ptj[k],pt_ord,ej[k],fabs(etaj[k]),feta_ord,phij[k],btgj[k],btg_ord,btgj_D[k],btg_D_ord,qtgj[k],puidj[k],puidj_I[k]);
        continue;
       }

     if(ptj[k]>0 && ptj[k]!=ptb1_True && ptj[k]!=ptb2_True)                    // Q1_Ntuple
       {
        int pt_ord=1; int feta_ord=1; int btg_ord=1; int btg_D_ord=1;
        for(int m=0;m<7;m++)
          if(ptj[m]>0)
            {
             if(ptj[m]>ptj[k]) pt_ord++;
             if(fabs(etaj[m])>fabs(etaj[k])) feta_ord++;
             if(btgj[m]>btgj[k] || (btgj[m]==btgj[k] && ptj[m]>ptj[k])) btg_ord++;
             if(btgj_D[m]>btgj_D[k] || (btgj_D[m]==btgj_D[k] && ptj[m]>ptj[k])) btg_D_ord++;
            }
        _qq -> Fill(weight,ptj[k],pt_ord,ej[k],fabs(etaj[k]),feta_ord,phij[k],btgj[k],btg_ord,btgj_D[k],btg_D_ord,qtgj[k],puidj[k],puidj_I[k]);
       }

   }  // End of sort loop

 }
// ******************************************************************************

  f->Write();
}


