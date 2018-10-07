#include "TStyle.h"
#include "TGaxis.h"
#include "TRandom.h"

#include <iostream>
#include <math.h>
#include <TF1.h>
#include <TH1D.h>
#include "TCanvas.h"

void Compare()
{
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(0);

  TString hist_name[] = {"BDTOb","BDTS0"};
  int Nhisto = sizeof(hist_name)/sizeof(hist_name[0]);

    TCanvas *Convas_1 = new TCanvas();
//    Convas_1->SetWindowSize(800, 800);
      TFile* f1 = new TFile("BDT_Output.root");

  for( int j=0; j<Nhisto; j++)
   {
      TH1D * histo = (TH1D*)f1->Get(hist_name[j]);
      histo->GetXaxis()->SetTitle("BDT Output");
      histo->GetXaxis()->SetLabelFont(42);
      histo->GetXaxis()->SetLabelOffset(0.001);
      histo->GetXaxis()->SetTitleOffset(1.);
      histo->GetXaxis()->SetTitleFont(42);
      histo->GetYaxis()->SetNdivisions(502);
      histo->GetYaxis()->SetTitle("Events");
      histo->GetYaxis()->SetLabelFont(42);
      histo->GetYaxis()->SetLabelOffset(0.0001);
      histo->GetYaxis()->SetTitleOffset(1.4);
      histo->GetYaxis()->SetTitleFont(42);
      histo->SetTitle("");
//      histo->Scale(1.0/histo->Integral());
      histo->SetLineColor(j+2+j*j);
      histo->SetLineStyle(1);
      histo->Draw("HIST same");

   }
     Convas_1->SetLogy();
//     Convas_1->SaveAs("aaa.png");
//     Convas_1->Close();

}