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
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;
using namespace std;

// *********************************** Spec Functions ********************************************
// D-phi
double phi_Dist(double a, double b){
   if(fabs(a - b) > 3.14159265)
    return 6.2831853 - fabs(a - b);
   return fabs(a - b);
}

// PU_reweighting
double rew[]  = {0.798126,18.1207,14.7655,8.96119,2.78256,2.39094,1.80281,1.18334,0.866385,4.50645,5.11604,4.87425,3.63377,2.3087,1.48188,1.03325,0.838923,0.773768,0.741412,0.698234,0.670365,0.687718,0.725647,0.740976,0.720316,0.684778,0.656715,0.639069,0.638062,0.63056,0.628136,0.624424,0.625472,0.628517,0.640495,0.668228,0.711752,0.768685,0.811498,0.860919,0.969558,1.12861,1.35588,1.66454,2.05542,2.50623,2.96154,3.21858,3.36422,3.26354,3.01841,2.63201,2.18626,1.7381,1.3301,0.963607,0.681615,0.465635,0.319755,0.220719,0.153924,0.108758,0.0779425,0.0566201,0.0416081,0.0263959,0.016734,0.0121966,0.00889823,0.00647328,0.00467944,0.00335151,0.00237284,0.00165781,0.000908819,0.000508386,0.000337097,0.000219905,0.000141031,8.88541e-05,5.49556e-05,3.33457e-05,1.98403e-05,9.02122e-06,4.21836e-06,2.36058e-06,1.29579e-06,6.98202e-07,3.69623e-07,1.92468e-07,9.87022e-08,4.99156e-08,1.91257e-08,7.61235e-09,3.69361e-09,1.77501e-09,8.43189e-10,3.99759e-10,1.83632e-10,1};
double ReWeight(int npu) {return rew[npu];}

// Sorting
vector <int> Order(int size, float pt[], float value[])
{
  std::vector <int> ord;
  for(int i=0;i<size;i++)
   {
    int position=1;
    for(int j=0;j<size;j++)
      if(pt[j]>0  && (value[j]>value[i] || (pt[j]>pt[i] && value[j]==value[i])))
        position++;
    ord.push_back(position);
   }
  return ord;
}
// *********************************** Spec Functions END ****************************************

void MC_Derived()
{
  // Inputs
   double pi=3.14159265;
   double pu_min     = -100.63;
   double PT_min_B1  = 20;
   double PT_min_B2  = 20;
   double PT_min_QQ  = 20;
   double btg_min_B1 = 0.8838;
   double qq_dETA_cut = 4.2;
   double qq_M_cut   = 500;
   double dPHI_Max   = 1.6;
   double btg_min_B2 = -100.5803;

 map<string,pair<double,int>> Processes
 {
  #include "Info_Map/Map.txt"
 };

 for (pair<string, pair<double,int>> Proc : Processes)
 {
  TString TnTname;
  TFile *f1 = new TFile("../../../Preselected_NTuples/Training__" + (TString)Proc.first + "__.root");

   TnTname = "Training/";
   if(Proc.first=="Full_Data" || Proc.first=="Data_5perc")
     TnTname = "Test_On_Data/";

//********************************** Get NTuples and Create New **********************************
  TString Ntuple_Name[7];
  for(int i=0;i<7;i++) {  Ntuple_Name[i] = TnTname + "Reco_Jet_Real_";   Ntuple_Name[i] += i;  }
  TTree *jet[7] = { (TTree*)f1->Get(Ntuple_Name[0]), (TTree*)f1->Get(Ntuple_Name[1]), (TTree*)f1->Get(Ntuple_Name[2]),
                    (TTree*)f1->Get(Ntuple_Name[3]), (TTree*)f1->Get(Ntuple_Name[4]), (TTree*)f1->Get(Ntuple_Name[5]),
                    (TTree*)f1->Get(Ntuple_Name[6])
                  };
  TTree *Other = (TTree*)f1->Get(TnTname+"Other_variables");

  TFile *f = new TFile("NTuples_"+(TString)Proc.first+"_.root","RECREATE");
  TString  Datatype = "Bkg";
  if (Proc.first == "VBFHToBB_M_125" || Proc.first =="GluGluHToBB_M125")
     Datatype = "Sig";

// new_1
//  TNtuple *ntuple = new TNtuple(Datatype,Datatype,"mqq:detaqq:dphiqq:btgb1_D:btgb2_D:qtgq1:qtgq2:NJ_ingap:pz_All:Njet_10:Njet_20:HTT_rest_10:HTT_rest_20:HTT_bbqq:minvbb");
// new_2
//  TNtuple *ntuple = new TNtuple(Datatype,Datatype,"mqq:detaqq:dphiqq:btgb1_D:btgb2_D:qtgq1:qtgq2:NJ_ingap:pt_All:pz_All:Njet_10:HTT_rest_10:E_rest_10:HTT_bbqq:minvbb");
// new_3
  TNtuple *ntuple = new TNtuple(Datatype,Datatype,"weight:mqq:detaqq:dphiqq:btgb1_D:btgb2_D:qtgq1:qtgq2:NJ_ingap:pt_All:pz_All:Njet_20:HTT_rest_20:E_rest_20:minvbb");

//********************************** Get Variables  **********************************
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

  Float_t Tnpv,Njet_20,HTT_20,E_20,Njet_10,HTT_10,E_10;
  Other->SetBranchAddress("Tnpv",&Tnpv);
  Other->SetBranchAddress("Njet_20",&Njet_20);
  Other->SetBranchAddress("HTT_20",&HTT_20);
  Other->SetBranchAddress("E_20",&E_20);
  Other->SetBranchAddress("Njet_10",&Njet_10);
  Other->SetBranchAddress("HTT_10",&HTT_10);
  Other->SetBranchAddress("E_10",&E_10);

// TMVA *******************************************************************************
  Float_t ptj_MVA,ptj_ord_MVA,fetaj_MVA,fetaj_ord_MVA,btgj_MVA,btgj_ord_MVA,btgj_D_MVA,btgj_D_ord_MVA,puidj_MVA,puidj_I_MVA;

// TMVA
  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
  reader->AddVariable( "pt",                   &ptj_MVA);
  reader->AddVariable( "pt_ord",               &ptj_ord_MVA);
  reader->AddVariable( "feta",                 &fetaj_MVA);
  reader->AddVariable( "feta_ord",             &fetaj_ord_MVA);
  reader->AddVariable( "btg_D",                  &btgj_D_MVA);
  reader->AddVariable( "btg_D_ord",              &btgj_D_ord_MVA);
  reader->AddVariable( "puid",                 &puidj_MVA);
  reader->BookMVA("TMVAClassification_BDTG", "dataset/weights/TMVAClassification_BDTG.weights.xml" );

// ***********************************************************************************

for(int i=0;i<jet[0]->GetEntries();i++)
   {
    for(int n=0;n<7;n++)
      jet[n]->GetEntry(i);
    Other->GetEntry(i);

// ************************************** TMVA Evaluation
    Float_t fetaj[7];
    Int_t ptj_ord[7],fetaj_ord[7],btgj_ord[7],btgj_D_ord[7];
    Float_t b_likehood[7];
    for(int k=0;k<7;k++)
     {
       fetaj[k]     = fabs(etaj[k]);
       b_likehood[k]=-1;
     }

    for(int k=0;k<7;k++)
      {
       ptj_ord[k]   = Order(7,ptj,ptj)[k];
       fetaj_ord[k] = Order(7,ptj,fetaj)[k];
       btgj_ord[k]  = Order(7,ptj,btgj)[k];
       btgj_D_ord[k]= Order(7,ptj,btgj_D)[k];
      }

      // BDT evaluation
    for(int k=0;k<7;k++)
      {
        ptj_MVA       = ptj[k];
        ptj_ord_MVA   = ptj_ord[k];
        fetaj_MVA     = fetaj[k];
        fetaj_ord_MVA = fetaj_ord[k];
        btgj_D_MVA      = btgj_D[k];
        btgj_D_ord_MVA  = btgj_D_ord[k];
        puidj_MVA     = puidj[k];
        b_likehood[k] = reader->EvaluateMVA( "TMVAClassification_BDTG");
      }

// ************************************************* b-jets selection
    double ptb1   = 0;
    double eb1    = 0;
    double etab1  = 0;
    double phib1  = 0;
    double btgb1  = 0;
    double btgb1_D= 0;
    double qtgb1  = 0;
    double puidb1 = 0;
    double b_likehood_MAX1=-1;

    double ptb2   = 0;
    double eb2    = 0;
    double etab2  = 0;
    double phib2  = 0;
    double btgb2  = 0;
    double btgb2_D= 0;
    double qtgb2  = 0;
    double puidb2 = 0;
    double b_likehood_MAX2=-1;


// First b-selection as highest MVA_out
   for(int k=0;k<7;k++)
    if(ptj[k]>PT_min_B1 && b_likehood[k]>b_likehood_MAX1 && btgj[k] >= btg_min_B1)
      {
       ptb1   = ptj[k];
       eb1    = ej[k];
       etab1  = etaj[k];
       phib1  = phij[k];
       btgb1  = btgj[k];
       btgb1_D= btgj_D[k];
       qtgb1  = qtgj[k];
       puidb1 = puidj[k];
       b_likehood_MAX1 = b_likehood[k];
      }

    if(ptb1<PT_min_B1) {continue;}         // No First b-jet

// Second b-jet selection BEGIN
// Decision of the Choice of TMVA by mqq combinations categories Begin
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
         if( (sqrt(eqq2-pxqq2-pyqq2-pzqq2) > qq_M_cut) && (fabs(etaj[m]-etaj[n]) > qq_dETA_cut) )
           {
            CatCheck++;
            q1pt=ptj[m];
            q2pt=ptj[n];
            N_mqq[m]++;
            N_mqq[n]++;
           }
        }
   if (CatCheck==0) continue; // Anyway need for final selection.

   float Comb_factor=0.5;
   for(int k=0;k<7;k++)
    if(ptj[k]>PT_min_B2 && ptj[k]!=ptb1 && b_likehood[k]>b_likehood_MAX2 && (float)N_mqq[k]<=(float)CatCheck*Comb_factor)
      {
       ptb2   = ptj[k];
       eb2    = ej[k];
       etab2  = etaj[k];
       phib2  = phij[k];
       btgb2  = btgj[k];
       btgb2_D= btgj_D[k];
       qtgb2  = qtgj[k];
       puidb2 = puidj[k];
       b_likehood_MAX2 = b_likehood[k];
      }

     if(ptb2<PT_min_B2 || phi_Dist(phib1,phib2)>dPHI_Max) {continue; }      // No Second b-jet

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
        if( (sqrt(eqq2-pxqq2-pyqq2-pzqq2) > qq_M_cut) && (fabs(etaj[m]-etaj[n]) > dETAqq_Max) && (fabs(etaj[m]-etaj[n]) > qq_dETA_cut) )
          {
           N_Q1=m;
           N_Q2=n;
           dETAqq_Max = fabs(etaj[N_Q1]-etaj[N_Q2]);
          }
       }

    if(dETAqq_Max<qq_dETA_cut) {continue;}    // No tagging jets

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

// ***********************************************************************************

    double pxb1 = ptb1*cos(phib1),  pxb2 = ptb2*cos(phib2),  pxq1 = ptq1*cos(phiq1),  pxq2 = ptq2*cos(phiq2);
    double pyb1 = ptb1*sin(phib1),  pyb2 = ptb2*sin(phib2),  pyq1 = ptq1*sin(phiq1),  pyq2 = ptq2*sin(phiq2);
    double pzb1 = ptb1*sinh(etab1), pzb2 = ptb2*sinh(etab2), pzq1 = ptq1*sinh(etaq1), pzq2 = ptq2*sinh(etaq2);

    double minvbb = sqrt( (eb1+eb2)*(eb1+eb2) - (pxb1+pxb2)*(pxb1+pxb2) - (pyb1+pyb2)*(pyb1+pyb2) - (pzb1+pzb2)*(pzb1+pzb2) );
    double minvqq = sqrt( (eq1+eq2)*(eq1+eq2) - (pxq1+pxq2)*(pxq1+pxq2) - (pyq1+pyq2)*(pyq1+pyq2) - (pzq1+pzq2)*(pzq1+pzq2) );
    double pt_All = sqrt((pxb1+pxb2+pxq1+pxq2)*(pxb1+pxb2+pxq1+pxq2) + (pyb1+pyb2+pyq1+pyq2)*(pyb1+pyb2+pyq1+pyq2));
    double pz_All = (pzb1+pzb2+pzq1+pzq2);

    double pt_5 =0;
    double eta_5 =0;
    double puid_5 =-100;
    int    puid_I_5=-10;
    for(int k=0;k<7;k++)
     if(ptj[k]!=ptb1 && ptj[k]!=ptb2 && ptj[k]!=ptq1 && ptj[k]!=ptq2 && puidj[k]> pu_min)
      {
       pt_5=ptj[k];
       eta_5=etaj[k];
       puid_5=puidj[k];
       puid_I_5=puidj_I[k];
       break;
      }

    double pt_6 =0;
    double eta_6 =0;
    double puid_6 =-100;
    for(int k=0;k<7;k++)
     if(ptj[k]!=ptb1 && ptj[k]!=ptb2 && ptj[k]!=ptq1 && ptj[k]!=ptq2 && ptj[k]!=pt_5 && puidj[k]> pu_min)
      {
       pt_6=ptj[k];
       eta_6=etaj[k];
       puid_6=puidj[k];
       break;
      }

    int NJ_ingap=0;
    for(int k=0;k<7;k++)
      if((etaj[k]<etaq1 && etaj[k]>etaq2) || (etaj[k]<etaq2 && etaj[k]>etaq1) )
       if(ptj[k]>20 && puidj[k]>pu_min)
        NJ_ingap++;

// Other_variables - Njets_20, HTT_20, E_20, Njets_10 ...
   double HTT_bbqq    = ptb1+ptb2+ptq1+ptq2;
   double HTT_rest_20 = HTT_20 - HTT_bbqq;
   double HTT_rest_10 = HTT_10 - HTT_bbqq;
   double E_rest_20   = E_20-(eb1+eb2+eq1+eq2);
   double E_rest_10   = E_10-(eb1+eb2+eq1+eq2);

   double weight=1;
   if (TnTname == "Training/")
      weight = ReWeight(Tnpv)*(Proc.second.first*7730.0/(double)Proc.second.second);           // XSec scale factors are added

//    ntuple->Fill(minvqq,dETAqq_Max,phi_Dist(phiq1,phiq2),pt_5,eta_5,pt_6,eta_6,NJ_ingap,btgb1_D,btgb2_D,qtgq1,qtgq2,pt_All,pz_All,minvbb);
//    ntuple->Fill(minvqq,dETAqq_Max,phi_Dist(phiq1,phiq2),pt_5,eta_5,puid_5,puid_I_5,NJ_ingap,btgb1_D,btgb2_D,qtgq1,qtgq2,pt_All,pz_All,minvbb);

// new_1
//    ntuple->Fill(minvqq,dETAqq_Max,phi_Dist(phiq1,phiq2),btgb1_D,btgb2_D,qtgq1,qtgq2,NJ_ingap,pz_All,Njet_10,Njet_20,HTT_rest_10,HTT_rest_20,HTT_bbqq,minvbb);
// new_2
//    ntuple->Fill(minvqq,dETAqq_Max,phi_Dist(phiq1,phiq2),btgb1_D,btgb2_D,qtgq1,qtgq2,NJ_ingap,pt_All,pz_All,Njet_10,HTT_rest_10,E_rest_10,HTT_bbqq,minvbb);
// new_3
    ntuple->Fill(weight,minvqq,dETAqq_Max,phi_Dist(phiq1,phiq2),btgb1_D,btgb2_D,qtgq1,qtgq2,NJ_ingap,pt_All,pz_All,Njet_20,HTT_rest_20,E_rest_20,minvbb);
 }
//    cout<<Proc.first<<endl;

// ******************************************************************************
  ntuple->Write();
//  f1->close();
  delete f1;

 } // Nproc loop END

}  // END


