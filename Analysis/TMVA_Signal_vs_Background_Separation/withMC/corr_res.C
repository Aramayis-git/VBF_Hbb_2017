
void corr_res(){

  Double_t mbbv[] = {130.984,129.92,128.26,129.76,129.783,124.42,127.464,126.721,129.92,125.975,128.27,126.905,121.612,124.311,128.781,126.894,127.537,126.581,125.567,118.84};
  Double_t mbbe[] = {1.19948,0.928551,1.07379,1.43114,1.64206,1.62529,1.85535,1.55302,1.73308,1.87485,4.00375,2.08445,1.98114,2.28267,2.88742,3.10108,2.05979,2.47662,2.56583,6.95803};
  Int_t nbin = sizeof(mbbv)/sizeof(mbbv[0]);
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
  TGraphErrors* gr = new TGraphErrors(nbin,bdtv,mbbv,bdte,mbbe);
//  gr->SetMarkerSize(1.5);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(2);
  gr->SetLineColor(2);
  gr->GetXaxis()->SetRangeUser(-1,1);
  gr->GetYaxis()->SetRangeUser(80,200);
  gr->GetXaxis()->SetTitle("BDT-out");
  gr->GetYaxis()->SetTitle("< m_{bb} > (GeV)");
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->SetTitle("");
  gr->Draw("ap");

}