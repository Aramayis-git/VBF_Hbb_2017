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

  TFile* f1 = new TFile("PileupMC.root");
  TFile* f2 = new TFile("MyDataPileupHistogram.root");
  TH1D * histo1 = (TH1D*)f1->Get("input_Event/N_TrueInteractions");
  TH1D * histo2 = (TH1D*)f2->Get("pileup");

  cout<<histo1->GetSumOfWeights()<<endl;
  cout<<histo2->GetSumOfWeights()<<endl;

  histo1->Scale(1/histo1->GetSumOfWeights());
  histo2->Scale(1/histo2->GetSumOfWeights());

  histo2->Draw("HIST same");
  histo1->Draw("HIST same");

  for(int i=0;i<100;i++)
    cout<<histo2->GetBinContent(i+1)/histo1->GetBinContent(i+1)<<",";
  cout<<endl;

}