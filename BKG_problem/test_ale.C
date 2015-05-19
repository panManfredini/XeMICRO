{

  float HighPE=30;
  float LowPE=3;
  int NPE=(HighPE-LowPE)/1.;
  float HighS1S2=1;
  float LowS1S2=-1;
  int NS1S2=200;
  int Nbands=12;
  double R=0.0271;  
  TH2D *h_erdata=new TH2D("h_erdata","h2",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  TH2D *h_data_m_gauss=new TH2D("h_erdata","h2",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  TH2D *h_erModel=new TH2D("h_erModel","ER Model; S1 [pe]; Flattened",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  TH2D *h_erModelg=new TH2D("h_erModelg","Gaussian ER Model; S1 [pe]; Flattened",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  TH2D *h_erModelng=new TH2D("h_erModelng","None Gaussian ER Model; S1 [pe]; Flattened",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  double S1S2Bin = h_erModelng->GetYaxis()->GetBinWidth(1);
  TH1F *gLeakageTop=new TH1F("gLeakageTop","Leakage top+bottom (All s1s2); S1 [pe] ; N events",HighPE-LowPE,LowPE,HighPE);
  TH1F *gLeakageBottom=new TH1F("gLeakageBottom","Leakage Bottom (s1s2<0); S1 [pe] ; N events",HighPE-LowPE,LowPE,HighPE);
  TH1F *gLeakageProfileS1S2=new TH1F("gLeakageProfileS1S2","Leakage events projection on Y; Flattenend S1S2; # events",NS1S2,LowS1S2,HighS1S2);

  TCanvas *c1=new TCanvas("c1","c1",1000,600);

  // Read in the ER calibration point
  TGraph *g_erdata=new TGraph("data/run10/er_34kg.from_Marc.dat");
  for (int i=0; i<g_erdata->GetN(); i++) {
    double x,y;
    g_erdata->GetPoint(i,x,y);
    h_erdata->Fill(x,y);
  }

  h_erdata->Draw("colz");


}
