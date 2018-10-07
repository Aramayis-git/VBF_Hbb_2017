
void MC_Data_comp(){

  Double_t mbbvD[] ={131.001,130.568,130.178,130.046,129.962,129.389,129.105,129.711,129.312,129.017,128.838,128.608,129.327,128.9,128.893,128.385,129.077,127.842,128.401,130.508};
  Double_t mbbeD[] ={0.176679,0.147737,0.171472,0.197273,0.218648,0.238932,0.260601,0.285475,0.309072,0.33116,0.354903,0.370463,0.380301,0.389217,0.405531,0.410608,0.425536,0.463579,0.564854,1.25899};
  Double_t mbbvM[] = {131.661,129.225,129.578,127.779,129.507,125.874,127.557,126.4,129.863,123.68,129.493,129.215,122.293,123.632,128.63,127.179,124.59,127.921,126.65,119.024};
  Double_t mbbeM[] = {1.17264,0.945202,1.0645,1.42782,1.6122,1.68252,1.92562,1.5402,1.78317,3.37451,2.02637,2.38712,2.01768,2.3162,3.38436,2.09407,2.23293,2.1208,2.71124,7.51188};

  Int_t nbin = sizeof(mbbvD)/sizeof(mbbvD[0]);
  Double_t binw = 2.0/nbin;
  Double_t bdtv[nbin];
  Double_t bdte[nbin];
  double binCent = -1 + binw/2;
  for(int i=0;i<nbin;i++)
    {
     bdtv[i]=binCent+i*binw;
     bdte[i]=binw/2;
    }
  TCanvas *c1 = new TCanvas("a","a",600,600,700,600);
  TMultiGraph *mg = new TMultiGraph();
  TGraphErrors *gr1 = new TGraphErrors(nbin,bdtv,mbbvD,bdte,mbbeD);
  TGraphErrors *gr2 = new TGraphErrors(nbin,bdtv,mbbvM,bdte,mbbeM);

  gr1->SetMarkerStyle(20);
  gr1->SetMarkerColor(2);
  gr1->SetLineColor(2);
  gr1->SetTitle("");

  gr2->SetMarkerStyle(4);
  gr2->SetMarkerColor(4);
  gr2->SetLineColor(4);
  gr2->GetYaxis()->SetTitleOffset(1.4);
  gr2->SetTitle("");

  mg->SetMaximum(200);
  mg->SetMinimum(80);
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("BDT-out");
  mg->GetYaxis()->SetTitle("< m_{bb} > (GeV)");
  gPad->Update();

  TLegend *leg = new TLegend(0.6, 0.7, 0.8, 0.8);
//  leg->SetFillColor(0);
  leg->SetLineWidth(0);
  leg->AddEntry(gr1, "2017F Data", "lp");
  leg->AddEntry(gr2, "QCD MC", "lp");
  leg->Draw();

}