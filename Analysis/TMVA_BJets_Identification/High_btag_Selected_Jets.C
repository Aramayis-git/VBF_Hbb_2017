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
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include "TString.h"
#include "TSystem.h"
#include "TStopwatch.h"

using namespace std;

// *********************************** My Functions ********************************************
// D-phi
double phi_Dist(double a, double b){
   if(fabs(a - b) > 3.14159265)
    return 6.2831853 - fabs(a - b);
   return fabs(a - b);
}

// *********************************** My Functions END ****************************************

void High_btag_Selected_Jets()
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

//*************************************** Pt > 20 jets[7] ***************************************
  TString Ntuple_Name[7];
  for(int i=0;i<7;i++) {  Ntuple_Name[i] = "Training/Reco_Jet_Real_";   Ntuple_Name[i] += i;  }
  TTree *jet[7] = { (TTree*)f1->Get(Ntuple_Name[0]), (TTree*)f1->Get(Ntuple_Name[1]), (TTree*)f1->Get(Ntuple_Name[2]),
                    (TTree*)f1->Get(Ntuple_Name[3]), (TTree*)f1->Get(Ntuple_Name[4]), (TTree*)f1->Get(Ntuple_Name[5]),
                    (TTree*)f1->Get(Ntuple_Name[6])
                  };

  TTree *other = (TTree*)f1->Get("Training/Other_variables");
  Float_t weight;
  other->SetBranchAddress("weight", &weight);

  TFile *f = new TFile("high_btg_Results.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");

//***************************************************************************************

  TH1D * _Pt_B1  = new TH1D("Pt_B1","Pt_B1",500,0,500);
  TH1D * _Pt_B2  = new TH1D("Pt_B2","Pt_B2",500,0,500);
  TH1D * _Pt_Q1  = new TH1D("Pt_Q1","Pt_Q1",500,0,500);
  TH1D * _Pt_Q2  = new TH1D("Pt_Q2","Pt_Q2",500,0,500);
  TH1D * _Eta_B1 = new TH1D("Eta_B1","Eta_B1",100,-5,5);
  TH1D * _Eta_B2 = new TH1D("Eta_B2","Eta_B2",100,-5,5);
  TH1D * _Eta_Q1 = new TH1D("Eta_Q1","Eta_Q1",140,-7,7);
  TH1D * _Eta_Q2 = new TH1D("Eta_Q2","Eta_Q2",140,-7,7);
  TH1D * _MinvBB  = new TH1D("MinvBB","MinvBB",600,0,600);
  TH1D * _MinvQQ  = new TH1D("MinvQQ","MinvQQ",1200,0,1200);
  TH1D * _DEtaQQ  = new TH1D("DEtaQQ","DEtaQQ",120,0,12);
  TH1D * _DEtaBB  = new TH1D("DEtaBB","DEtaBB",70,0,7);
  TH1D * _DPhiBB  = new TH1D("DPhiBB","DPhiBB",63,0,3.15);
  TH1D * _DEta_B1Q12  = new TH1D("DEta_B1Q12","DEta_B1Q12",70,0,7);
  TH1D * _DPhi_B1Q12  = new TH1D("DPhi_B1Q12","DPhi_B1Q12",63,0,3.15);

  TH1D * _BDiscQ_D  = new TH1D("BDiscQ_D","BDiscQ_D",100,-2,2);
  TH1D * _BDiscB1_D = new TH1D("BDiscB1_D","BDiscB1_D",100,-2,2);
  TH1D * _BDiscB2_D = new TH1D("BDiscB2_D","BDiscB2_D",100,-2,2);
  TH1D * _BDiscQ    = new TH1D("BDiscQ","BDiscQ",100,-2,2);
  TH1D * _BDiscB1   = new TH1D("BDiscB1","BDiscB1",100,-2,2);
  TH1D * _BDiscB2   = new TH1D("BDiscB2","BDiscB2",100,-2,2);
  TH1D * _QDiscQ    = new TH1D("QDiscQ","QDiscQ",100,-2,2);
  TH1D * _QDiscB1   = new TH1D("QDiscB1","QDiscB1",100,-2,2);
  TH1D * _QDiscB2   = new TH1D("QDiscB2","QDiscB2",100,-2,2);
  TH1D * _PUDiscQ   = new TH1D("PUDiscQ","PUDiscQ",100,-2,2);
  TH1D * _PUDiscB1  = new TH1D("PUDiscB1","PUDiscB1",100,-2,2);
  TH1D * _PUDiscB2  = new TH1D("PUDiscB2","PUDiscB2",100,-2,2);

// ***********************************************************************************
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

// For Checking **********************************************************************
  // True
  float Global_Check   = 0;
  float Categ_check_Tr = 0;
  float first_sel      = 0;
  float second_sel     = 0;
  float dphi_sel       = 0;
  float Confirm_BB     = 0;
  float tagging_sel    = 0;

  // Real
  int   Preselected    = 0;
  float Presel_weight  = 0;
  float b1_Nofail      = 0;
  float CAT_Nofail     = 0;
  float b2_Nofail      = 0;
  float dphi_Nofail    = 0;
  float VBF_Nofail     = 0;
// Begin ******************************************************************************

  for(int i=0;i<jet[0]->GetEntries();i++)
   {
    partb1->GetEntry(i);
    partb2->GetEntry(i);
    partq1->GetEntry(i);
    partq2->GetEntry(i);
    other ->GetEntry(i);
    for(int n=0;n<7;n++)
     jet[n]->GetEntry(i);

   Preselected++; Presel_weight+=weight;

// cuts
   double pu_min     = -100.63;
   double PT_min_B1  = 20;
   double PT_min_B2  = 20;
   double PT_min_QQ  = 20;
   double btg_min_B1 = 0.8838;
   double qq_ETA_cut = 4.2;
   double qq_M_cut   = 500;
   double dPHI_Max   = 1.6;
   double btg_min_B2 = -100.5803;

// *************************** True Check Begin ****************************
   bool true_Norm=true;
   int glcheck=0;
   if(ptb1_True>PT_min_B1 && ptb2_True>PT_min_B2 && puidb1_True>pu_min && puidb2_True>pu_min && phi_Dist(phib1_True,phib2_True)<dPHI_Max)
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

    if(glcheck==0) true_Norm=false;                // True Combination can't pass final selection (e.g. secondB was used in qq-cuts at preselection)
    int ntrueB=0;
    for(int k=0;k<7;k++)
       if(ptj[k]==ptb1_True || ptj[k]==ptb2_True)
         ntrueB++;
    if(ntrueB!=2) true_Norm=false;                 // At least one of b-jets is not within 7 PT-leading

    if(true_Norm)                                  // If eveything is OK and True combination in principle can pass final selection
      Global_Check+=weight;
// *************************** True Check End ****************************

    double ptb1   = 0;
    double eb1    = 0;
    double etab1  = 0;
    double phib1  = 0;
    double btgb1  = 0;
    double btgb1_D= 0;
    double qtgb1  = 0;
    double puidb1 = 0;
    double btgD_MAX1=-101;

    double ptb2   = 0;
    double eb2    = 0;
    double etab2  = 0;
    double phib2  = 0;
    double btgb2  = 0;
    double btgb2_D= 0;
    double qtgb2  = 0;
    double puidb2 = 0;
    double btgD_MAX2=-101;


// First b-selection as highest btg-out
   for(int k=0;k<7;k++)
    if(ptj[k]>PT_min_B1 && btgj_D[k]>btgD_MAX1)      // DeepCSV b-tagging
//    if(ptj[k]>PT_min_B1 && btgj[k]>btgD_MAX1)      // CSV b-tagging
      {
       ptb1   = ptj[k];
       eb1    = ej[k];
       etab1  = etaj[k];
       phib1  = phij[k];
       btgb1  = btgj[k];
       btgb1_D= btgj_D[k];
       qtgb1  = qtgj[k];
       puidb1 = puidj[k];
       btgD_MAX1 = btgj_D[k];              // DeepCSV b-tagging
//       btgD_MAX1 = btgj[k];              // CSV b-tagging
      }

     if(ptb1>=PT_min_B1) b1_Nofail+=weight;
     else continue;
     if(true_Norm)
      if(ptb1==ptb1_True || ptb1==ptb2_True)
        first_sel+=weight;                            // Checking first b-jet selection accuracy

// ************************ Decision of the Choice of TMVA by mqq combinations categories Begin

   int N_mqq[]={0,0,0,0,0,0,0};
   double q1pt=0;
   double q2pt=0;
   int CatCheck=0;
     for(int m=0;m<6;m++)
      for(int n=m;n<7;n++)
       if((ptj[m]>PT_min_QQ && ptj[m]!=ptb1 && puidj[m]>=pu_min) && (ptj[n]>PT_min_QQ && ptj[n]!=ptb1 && puidj[n]>=pu_min) )
        {
         double pxqq2 = (ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]))*(ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]));
         double pyqq2 = (ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]))*(ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]));
         double pzqq2 = (ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]))*(ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]));
         double eqq2  = (ej[m]+ej[n])*(ej[m]+ej[n]);
         if( (sqrt(eqq2-pxqq2-pyqq2-pzqq2) > qq_M_cut) && (fabs(etaj[m]-etaj[n]) > qq_ETA_cut) )
           {
            CatCheck++;
            q1pt=ptj[m];
            q2pt=ptj[n];
            N_mqq[m]++;
            N_mqq[n]++;
           }
        }
    if (CatCheck>0) CAT_Nofail+=weight;
    else continue;                         // Anyway need for final selection. This cuts the cases of boosted H OR no 2 b-jets within 7 PT-ledaing
//    if (CatCheck!=1) continue;         // if need to consider specific category

    // True-Check
     if(true_Norm)
      if(ptb1==ptb1_True || ptb1==ptb2_True)
       if(CatCheck>0) Categ_check_Tr+=weight;  // Categ_check_Tr little bit differ from Global_Check: 1st b selection at preselection is differ
                                               // form that of final selection, and final 1st b can be choosen the one from preselected tagging jets
                                            // form that of final selection, and final 1st b can be choosen the one from preselected tagging jets
// ******************************************************************
   float Comb_factor=0.5;

   for(int k=0;k<7;k++)
    if(ptj[k]>PT_min_B2 && ptj[k]!=ptb1 && btgj_D[k]>btgD_MAX2 && (float)N_mqq[k]<=(float)CatCheck*Comb_factor)      // DeepCSV b-tagging
//    if(ptj[k]>PT_min_B2 && ptj[k]!=ptb1 && btgj[k]>btgD_MAX2 && (float)N_mqq[k]<=(float)CatCheck*Comb_factor)      // CSV b-tagging
      {
       ptb2   = ptj[k];
       eb2    = ej[k];
       etab2  = etaj[k];
       phib2  = phij[k];
       btgb2  = btgj[k];
       btgb2_D= btgj_D[k];
       qtgb2  = qtgj[k];
       puidb2 = puidj[k];
       btgD_MAX2 = btgj_D[k];        // DeepCSV b-tagging
//       btgD_MAX2 = btgj[k];        // CSV b-tagging
      }

     if(ptb2>=PT_min_B2) b2_Nofail+=weight;
     else continue;

    // True-Check
    if(true_Norm)
     if(ptb1==ptb1_True || ptb1==ptb2_True)
      if(CatCheck>0)
       if((ptb2==ptb1_True || ptb2==ptb2_True) && ptb2!=ptb1)
         second_sel+=weight;


     if(phi_Dist(phib1,phib2)<=dPHI_Max) dphi_Nofail+=weight;
     else continue;

    // True-Check
    if(true_Norm)
     if(ptb1==ptb1_True || ptb1==ptb2_True)
      if(CatCheck>0)
       if((ptb2==ptb1_True || ptb2==ptb2_True) && ptb2!=ptb1)
        if(phi_Dist(phib1,phib2)<=dPHI_Max)
          dphi_sel+=weight;

// **************************** Tagging-jets BEGIN
    double ptq1   =0;
    double eq1    =0;
    double etaq1  =0;
    double phiq1  =0;
    double btgq1  =0;
    double btgq1_D=0;
    double qtgq1  =0;
    double puidq1 =0;
    double ptq2   =0;
    double eq2    =0;
    double etaq2  =0;
    double phiq2  =0;
    double btgq2  =0;
    double btgq2_D=0;
    double qtgq2  =0;
    double puidq2 =0;

    int N_Q1=10;
    int N_Q2=10;
    double dETAqq_Max=0;
    for(int m=0;m<6;m++)
     for(int n=m;n<7;n++)
      if( (ptj[m]>PT_min_QQ && ptj[m]!=ptb1 && ptj[m]!=ptb2 && puidj[m]>=pu_min) && (ptj[n]>PT_min_QQ && ptj[n]!=ptb1 && ptj[n]!=ptb2 && puidj[n]>=pu_min) )
       {
        double pxqq2 = (ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]))*(ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]));
        double pyqq2 = (ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]))*(ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]));
        double pzqq2 = (ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]))*(ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]));
        double eqq2  = (ej[m]+ej[n])*(ej[m]+ej[n]);
        if( (sqrt(eqq2-pxqq2-pyqq2-pzqq2) > qq_M_cut) && (fabs(etaj[m]-etaj[n]) > dETAqq_Max) && (fabs(etaj[m]-etaj[n]) > qq_ETA_cut) )
          {
           N_Q1=m;
           N_Q2=n;
           dETAqq_Max = fabs(etaj[N_Q1]-etaj[N_Q2]);
          }
       }

      if(dETAqq_Max>=qq_ETA_cut) VBF_Nofail+=weight;
      else continue;

      ptq1   = ptj[N_Q1];
      eq1    = ej[N_Q1];
      etaq1  = etaj[N_Q1];
      phiq1  = phij[N_Q1];
      btgq1  = btgj[N_Q1];
      btgq1_D  = btgj_D[N_Q1];
      qtgq1  = qtgj[N_Q1];
      puidq1 = puidj[N_Q1];
      ptq2   = ptj[N_Q2];
      eq2    = ej[N_Q2];
      etaq2  = etaj[N_Q2];
      phiq2  = phij[N_Q2];
      btgq2  = btgj[N_Q2];
      btgq2_D  = btgj_D[N_Q2];
      qtgq2  = qtgj[N_Q2];
      puidq2 = puidj[N_Q2];

      // True-Check
    if(true_Norm)
     if(ptb1==ptb1_True || ptb1==ptb2_True)
      if(CatCheck>0)
       if((ptb2==ptb1_True || ptb2==ptb2_True) && ptb2!=ptb1)
        if(phi_Dist(phib1,phib2)<=dPHI_Max)
         if(dETAqq_Max>=qq_ETA_cut)
           tagging_sel+=weight;

// Histo ********************************************************************************

    double pxb1 = ptb1*cos(phib1),  pxb2 = ptb2*cos(phib2),  pxq1 = ptq1*cos(phiq1),  pxq2 = ptq2*cos(phiq2);
    double pyb1 = ptb1*sin(phib1),  pyb2 = ptb2*sin(phib2),  pyq1 = ptq1*sin(phiq1),  pyq2 = ptq2*sin(phiq2);
    double pzb1 = ptb1*sinh(etab1), pzb2 = ptb2*sinh(etab2), pzq1 = ptq1*sinh(etaq1), pzq2 = ptq2*sinh(etaq2);

    double minvbb = sqrt( (eb1+eb2)*(eb1+eb2) - (pxb1+pxb2)*(pxb1+pxb2) - (pyb1+pyb2)*(pyb1+pyb2) - (pzb1+pzb2)*(pzb1+pzb2) );
    double minvqq = sqrt( (eq1+eq2)*(eq1+eq2) - (pxq1+pxq2)*(pxq1+pxq2) - (pyq1+pyq2)*(pyq1+pyq2) - (pzq1+pzq2)*(pzq1+pzq2) );

     _MinvBB  -> Fill(minvbb,weight);
     _Pt_B1   -> Fill(ptb1,weight);
     _Pt_B2   -> Fill(ptb2,weight);
     _Eta_B1  -> Fill(etab1,weight);
     _Eta_B2  -> Fill(etab2,weight);
     _BDiscB1 -> Fill(btgb1,weight);
     _BDiscB2 -> Fill(btgb2,weight);
     _BDiscB1_D -> Fill(btgb1_D,weight);
     _BDiscB2_D -> Fill(btgb2_D,weight);
     _QDiscB1 -> Fill(qtgb1,weight);
     _QDiscB2 -> Fill(qtgb2,weight);
     _PUDiscB1 -> Fill(puidb1,weight);
     _PUDiscB2 -> Fill(puidb2,weight);
     _DEtaBB  -> Fill(fabs(etab1-etab2),weight);
     _DPhiBB  -> Fill(fabs(phi_Dist(phib1,phib2)),weight);

     _MinvQQ  -> Fill(minvqq,weight);
     _Pt_Q1   -> Fill(ptq1,weight);
     _Pt_Q2   -> Fill(ptq2,weight);
     _Eta_Q1  -> Fill(etaq1,weight);
     _Eta_Q2  -> Fill(etaq2,weight);
     _DEtaQQ  -> Fill(fabs(etaq1-etaq2),weight);
     _BDiscQ  -> Fill(btgq1,weight);
     _BDiscQ  -> Fill(btgq2,weight);
     _BDiscQ_D  -> Fill(btgq1_D,weight);
     _BDiscQ_D  -> Fill(btgq2_D,weight);
     _QDiscQ  -> Fill(qtgq1,weight);
     _QDiscQ  -> Fill(qtgq2,weight);
     _PUDiscQ -> Fill(puidq1,weight);
     _PUDiscQ -> Fill(puidq2,weight);

     _DEta_B1Q12 -> Fill(fabs(etab1-etaq1),weight);
     _DEta_B1Q12 -> Fill(fabs(etab1-etaq2),weight);
     _DPhi_B1Q12 -> Fill(fabs(phi_Dist(phib1,phiq1)),weight);
     _DPhi_B1Q12 -> Fill(fabs(phi_Dist(phib1,phiq2)),weight);
 }

// ******************************************************************************
  cout<<endl<<endl<<endl<<"************************************* Summary of Real selection *************************************"<<endl<<endl;
  cout<<"Total Number of Preselected Events:                                                                       "<<Preselected<<endl<<endl;
  cout<<"Total Number of Preselected and PuReWeighted Events:                                                      "<<Presel_weight<<endl;
  cout<<"Remaining after 1st b-jet selection (Always True as selection by MAX_likelyhood):                         "<<b1_Nofail<<endl;
  cout<<"Remaining after CTA_Check (Sometimes false as 1st b-jet at preselection by btg, but at secondary by MVA)  "<<CAT_Nofail<<endl;
  cout<<"Remaining after 2nd b-jet selection (Always True as selection by MAX_likelyhood):                         "<<b2_Nofail<<endl;
  cout<<"Remaining after b-jets dPHI selection:                                                                    "<<dphi_Nofail<<endl;
  cout<<"Remaining after VBF selection:                                                                            "<<VBF_Nofail<<endl;


  cout<<endl<<endl<<endl<<"************************************* Summary of True selection *************************************"<<endl<<endl;
  cout<<"Number of Events where:"<<endl;
  cout<<"#2-bjets from H have PT>20, eta<4.7, pass PuLooseId, within 7-leading PT, dPHI<1.6"<<endl;
  cout<<"#One of them passes CSV btg-medium"<<endl;
  cout<<"#also 2 additional jets passing jet cuts and satisfying VBF criteria:                                     "<<Global_Check<<endl;
  cout<<"Remaining after 1st b-jet selection:                                                                      "<<first_sel<<endl;
  cout<<"Remaining after CTA_Check:                                                                                "<<Categ_check_Tr<<endl;
  cout<<"Remaining after 2nd b-jet selection:                                                                      "<<second_sel<<endl;
  cout<<"Remaining after b-jets dPHI selection:                                                                    "<<dphi_sel<<endl;
  cout<<"Remaining after VBF selection:                                                                            "<<tagging_sel<<endl;
  cout<<endl<<endl;
  f->Write();
}


