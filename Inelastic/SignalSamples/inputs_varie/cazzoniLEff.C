void cazzoniLEff()
{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 10 18:28:19 2016) by ROOT version6.02/08
   TCanvas *c1 = new TCanvas("c1", "c1",10,52,700,500);
   c1->Range(-41.2375,-4.945324,371.1375,1.240573);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t gxenon100run81sigma_fx1[43] = {
   1,
   1.1,
   1.2,
   1.3,
   1.4,
   1.5,
   1.6,
   1.7,
   1.8,
   1.9,
   2,
   2.1,
   2.2,
   2.3,
   2.4,
   2.5,
   2.6,
   2.7,
   2.8,
   2.9,
   3,
   4,
   5,
   6,
   7,
   8,
   9,
   10,
   12.5,
   15,
   20,
   25,
   30,
   40,
   50,
   60,
   70,
   80,
   90,
   100,
   120,
   140,
   300
};

double cazzoneDimerdaX[43] = 
{
   300,
   140,
   120,
   100,
   90,
   80,
   70,
   60,
   50,
   40,
   30,
   25,
   20,
   15,
   12.5,
   10,
   9,
   8,
   7,
   6,
   5,
   4,
   3,
   2.9,
   2.8,
   2.7,
   2.6,
   2.5,
   2.4,
   2.3,
   2.2,
   2.1,
   2,
   1.9,
   1.8,
   1.7,
   1.6,
   1.5,
   1.4,
   1.3,
   1.2,
   1.1,
   1};
   Double_t gxenon100run81sigma_fy1[43] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0.009440283,
   0.01903689,
   0.02784359,
   0.03598193,
   0.04354715,
   0.05061533,
   0.05724822,
   0.0643977,
   0.07160851,
   0.07949962,
   0.08816915,
   0.09732726,
   0.1061285,
   0.1146955,
   0.1221353,
   0.1284432,
   0.1338894,
   0.1380758,
   0.1424988,
   0.1486802,
   0.1561778,
   0.164418,
   0.1734407,
   0.181161,
   0.1855415,
   0.1870715,
   0.1874146,
   0.18711,
   0.1874033,
   0.1873654,
   0.1891081,
   0.1869};

double cazzoneDiMedraY [43]= {
   0.2069,
   0.2095899,
   0.2072441,
   0.2065183,
   0.2050026,
   0.2045034,
   0.2037614,
   0.2023463,
   0.1994118,
   0.193327,
   0.1853153,
   0.177478,
   0.1695935,
   0.161608,
   0.155571,
   0.1504117,
   0.1447098,
   0.1386255,
   0.1321198,
   0.1246833,
   0.116926,
   0.1102013,
   0.103101,
   0.1018724,
   0.1002378,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1,
   0.1};

   TGraph *graph = new TGraph(43,gxenon100run81sigma_fx1,gxenon100run81sigma_fy1);
   TGraph *graph_high = new TGraph(43,cazzoneDimerdaX , cazzoneDiMedraY);
   graph->SetName("gxenon100run81sigma");
   graph->SetTitle("");


   graph->Draw("aL");
  graph_high->Draw("Lsame");



  TFile *leff = TFile::Open("Leff.root");
  TFile *qy = TFile::Open("Qy.root");

  TGraph *g_qy_m = (TGraph*)qy->Get("Qy_LM_run58_median");
  TGraph *g_qy_1sl = (TGraph*)qy->Get("Qy_LM_run58_1sigma_lower");
  TGraph *g_qy_1su = (TGraph*)qy->Get("Qy_LM_run58_1sigma_upper");
 
  TGraph *g_leff = (TGraph*)leff->Get("Leff");
   

  TFile *f = new TFile("ligth_charge_yeld.root","RECREATE");

  f->cd();
  g_qy_m->Write("Qy_median");
  g_qy_1sl->Write("Qy_lowSigma");
  g_qy_1su->Write("Qy_upSigma");

  g_leff->Write("Leff_median");
  graph_high->Write("Leff_upSigma");
  graph->Write("Leff_lowSigma");

  f->Close();

 


}







