
void corr_res(){

//  Double_t mbbv[] ={131.001,130.568,130.178,130.046,129.962,129.389,129.105,129.711,129.312,129.017,128.838,128.608,129.327,128.9,128.893,128.385,129.077,127.842,128.401,130.508};
//  Double_t mbbe[] ={0.176679,0.147737,0.171472,0.197273,0.218648,0.238932,0.260601,0.285475,0.309072,0.33116,0.354903,0.370463,0.380301,0.389217,0.405531,0.410608,0.425536,0.463579,0.564854,1.25899};
  Double_t mbbv[] ={130.9,130.583,130.15,130.143,129.802,129.592,129.031,129.612,129.543,128.883,128.826,128.943,128.84,129.132,129.376,128.073,128.917,128.481,128.391,130.005};
  Double_t mbbe[] ={0.181765,0.146847,0.170342,0.196542,0.218442,0.23726,0.258302,0.285976,0.307566,0.330145,0.353384,0.37039,0.386175,0.390259,0.404075,0.410947,0.428199,0.463235,0.557416,1.24611};
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