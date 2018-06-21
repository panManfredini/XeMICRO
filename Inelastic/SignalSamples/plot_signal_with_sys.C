{

gROOT->ProcessLine(".L ../inelastic_style.C "); 

setInelasticStyle();

TCanvas canv("canv", "First canvas", 1000, 800);
  //TPad *gPad =new TPad("upper","plot", 0.00,0.00,1,1);
  gPad->SetLeftMargin(0.13);
  gPad->SetTopMargin(0.04);
  gPad->SetBottomMargin(0.12);
  gPad->SetRightMargin(0.04);
  //gPad->Draw();

TFile *f_sys = TFile::Open("final_signals_with_sys_reb.root");

TH1D *s_sys = (TH1D*) f_sys->Get("PL_SR_s1s2_mass_100_sys");

s_sys->Scale(50./s_sys->Integral());
  
TH1D* s_sys_clone = (TH1D*) s_sys->Clone("s_sys_clone");

s_sys->GetXaxis()->SetTitle("Sub-regions");
s_sys->GetYaxis()->SetTitle("Events");

s_sys->SetFillColor(866);
s_sys->SetLineColor(866);
s_sys->SetLineWidth(0);
s_sys->SetMarkerColor(866);
s_sys->GetYaxis()->SetRangeUser(0.,30.);
s_sys->Draw("E2");


s_sys_clone->SetFillColor(0);
s_sys_clone->SetLineColor(603);
s_sys_clone->SetLineWidth(5);
s_sys_clone->SetMarkerColor(603);
s_sys_clone->Draw("histsame");


  TLegend* lego = new TLegend(0.2,0.95,0.5,0.75);
  lego->SetTextSize(0.05);
  lego->SetTextFont(132);
  lego->SetFillColor(0);
  lego->SetBorderSize(0);
  lego->AddEntry(s_sys_clone,"WIMP M_{#chi} = 100GeV, scaled to 50 Events");
  lego->AddEntry(s_sys,"Systematic Uncertainties");
  lego->Draw();

canv.Print("wimp_sys_unc.png");
canv.Print("/home/pan/Documents/Papers/mypapers/Inelastic/wimp_sys_unc.png");
canv.Print("wimp_sys_unc.eps");
canv.Print("/home/pan/Documents/Papers/mypapers/Inelastic/wimp_sys_unc.eps");


}
