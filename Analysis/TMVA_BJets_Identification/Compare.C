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

  TCanvas *Convas_1 = new TCanvas();
  TFile* f1 = new TFile("tmva_Results.root");
  TFile* f2 = new TFile("high_btg_Results.root");

      TH1D * histo1 = (TH1D*)f1->Get("MinvBB");
      TH1D * histo2 = (TH1D*)f2->Get("MinvBB");
      histo1->Draw("HIST same");
      histo2->Draw("HIST same");

     Convas_1->SaveAs("aaa.png");
}