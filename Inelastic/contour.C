{


TFile *f = TFile::Open("merge_34kg.root");
TFile *fSit = TFile::Open("fout.root");
/*
TH2D *co60 = (TH2D*) f->Get("log_s2_s1_Rot_Co60");
TH2D *ambe = (TH2D*) f->Get("log_s2_s1_Rot_AmBe");
TH2D *th232 = (TH2D*) f->Get("log_s2_s1_Rot_Th232");
TH2D *cs137 = (TH2D*) f->Get("log_s2_s1_Rot_Cs137");
*/

TH2D *co60 = (TH2D*) f->Get("log_s2_s1_Co60");
TH2D *ambe = (TH2D*) f->Get("log_s2_s1_AmBe");
TH2D *th232 = (TH2D*) f->Get("log_s2_s1_Th232");
TH2D *cs137 = (TH2D*) f->Get("log_s2_s1_Cs137");

TH2F *sit = (TH2F*) fSit->Get("combinedGammaAndNuclearRecoil");


co60->Rebin2D(20,20);
ambe->Rebin2D(20,20);
th232->Rebin2D(20,20);
cs137->Rebin2D(20,20);

sit->Rebin2D(20,20);



ambe->SetLineColor(2);
ambe->SetLineWidth(3);
th232->SetLineWidth(3);
co60->SetLineWidth(3);
co60->SetLineColor(4);
cs137->SetLineWidth(3);
th232->SetLineColor(6);
cs137->SetLineColor(3);

ambe->SetContour(5);
co60->SetContour(5);
th232->SetContour(5);
cs137->SetContour(5);

sit->SetContour(5);

gStyle->SetOptStat(0);

co60->SetMarkerColor(4);
ambe->SetMarkerColor(2);

co60->Draw("cont2");
ambe->Draw("cont2 same");
//ambe->Draw("cont2 same");


//th232->Draw("cont2 same");
//cs137->Draw("cont2 same");


TLegend* lego = new TLegend(0.2,0.9,0.5,0.7);
  lego->SetTextSize(0.033);
  lego->SetFillColor(0);
  lego->SetBorderSize(0);
  lego->AddEntry(ambe,"Nuclear Recoil Interaction from AmBe data");
  lego->AddEntry(co60, "Compton Scattering from Co^{60} data");
  lego->Draw();



}
