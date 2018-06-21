{



TFile f("final_signals_Ybott_rho04.root");

TFile f2("final_signals_with_sys_reb.root");


TH1D *h_rho_04 = (TH1D*)f.Get("PL_SR_s1s2_mass_100");
TH1D *h_old = (TH1D*)f2.Get("PL_SR_s1s2_mass_100_sys");

h_rho_04->SetLineColor(2);
h_old->Draw("hist");
h_rho_04->Draw("same hist");


}
