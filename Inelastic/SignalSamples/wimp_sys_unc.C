void wimp_sys_unc()
{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Sep 22 15:14:52 2016) by ROOT version6.02/08
   TCanvas *c1 = new TCanvas("c1", "c1",459,215,525,500);
   gStyle->SetOptStat(0);
   c1->Range(-0.6250001,-3.125,10.625,28.125);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *PL_SR_s1s2_mass_100_sys1 = new TH1D("PL_SR_s1s2_mass_100_sys1","",9,0.5,9.5);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(1,0.2020872);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(2,0.8024175);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(3,0.3564141);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(4,4.427205);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(5,7.688451);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(6,20.21514);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(7,2.303484);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(8,1.936182);
   PL_SR_s1s2_mass_100_sys1->SetBinContent(9,12.06862);
   PL_SR_s1s2_mass_100_sys1->SetBinError(1,0.1348622);
   PL_SR_s1s2_mass_100_sys1->SetBinError(2,0.2301801);
   PL_SR_s1s2_mass_100_sys1->SetBinError(3,0.2286307);
   PL_SR_s1s2_mass_100_sys1->SetBinError(4,1.302881);
   PL_SR_s1s2_mass_100_sys1->SetBinError(5,1.050055);
   PL_SR_s1s2_mass_100_sys1->SetBinError(6,0.440911);
   PL_SR_s1s2_mass_100_sys1->SetBinError(7,0.8747007);
   PL_SR_s1s2_mass_100_sys1->SetBinError(8,0.9175042);
   PL_SR_s1s2_mass_100_sys1->SetBinError(9,1.646615);
   PL_SR_s1s2_mass_100_sys1->SetMinimum(0);
   PL_SR_s1s2_mass_100_sys1->SetMaximum(25);
   PL_SR_s1s2_mass_100_sys1->SetEntries(9);
   PL_SR_s1s2_mass_100_sys1->SetFillColor(7);
   PL_SR_s1s2_mass_100_sys1->SetLineColor(7);
   PL_SR_s1s2_mass_100_sys1->SetMarkerColor(7);
   PL_SR_s1s2_mass_100_sys1->GetXaxis()->SetTitle("Regions");
   PL_SR_s1s2_mass_100_sys1->GetXaxis()->SetLabelFont(42);
   PL_SR_s1s2_mass_100_sys1->GetXaxis()->SetLabelSize(0.035);
   PL_SR_s1s2_mass_100_sys1->GetXaxis()->SetTitleSize(0.035);
   PL_SR_s1s2_mass_100_sys1->GetXaxis()->SetTitleFont(42);
   PL_SR_s1s2_mass_100_sys1->GetYaxis()->SetTitle("Events");
   PL_SR_s1s2_mass_100_sys1->GetYaxis()->SetLabelFont(42);
   PL_SR_s1s2_mass_100_sys1->GetYaxis()->SetLabelSize(0.035);
   PL_SR_s1s2_mass_100_sys1->GetYaxis()->SetTitleSize(0.035);
   PL_SR_s1s2_mass_100_sys1->GetYaxis()->SetTitleFont(42);
   PL_SR_s1s2_mass_100_sys1->GetZaxis()->SetLabelFont(42);
   PL_SR_s1s2_mass_100_sys1->GetZaxis()->SetLabelSize(0.035);
   PL_SR_s1s2_mass_100_sys1->GetZaxis()->SetTitleSize(0.035);
   PL_SR_s1s2_mass_100_sys1->GetZaxis()->SetTitleFont(42);
   PL_SR_s1s2_mass_100_sys1->Draw("E2");
   
   TH1D *s_sys_clone2 = new TH1D("s_sys_clone2","",9,0.5,9.5);
   s_sys_clone2->SetBinContent(1,0.2020872);
   s_sys_clone2->SetBinContent(2,0.8024175);
   s_sys_clone2->SetBinContent(3,0.3564141);
   s_sys_clone2->SetBinContent(4,4.427205);
   s_sys_clone2->SetBinContent(5,7.688451);
   s_sys_clone2->SetBinContent(6,20.21514);
   s_sys_clone2->SetBinContent(7,2.303484);
   s_sys_clone2->SetBinContent(8,1.936182);
   s_sys_clone2->SetBinContent(9,12.06862);
   s_sys_clone2->SetBinError(1,0.1348622);
   s_sys_clone2->SetBinError(2,0.2301801);
   s_sys_clone2->SetBinError(3,0.2286307);
   s_sys_clone2->SetBinError(4,1.302881);
   s_sys_clone2->SetBinError(5,1.050055);
   s_sys_clone2->SetBinError(6,0.440911);
   s_sys_clone2->SetBinError(7,0.8747007);
   s_sys_clone2->SetBinError(8,0.9175042);
   s_sys_clone2->SetBinError(9,1.646615);
   s_sys_clone2->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   s_sys_clone2->SetLineColor(ci);
   s_sys_clone2->SetLineWidth(3);
   s_sys_clone2->GetXaxis()->SetLabelFont(42);
   s_sys_clone2->GetXaxis()->SetLabelSize(0.035);
   s_sys_clone2->GetXaxis()->SetTitleSize(0.035);
   s_sys_clone2->GetXaxis()->SetTitleFont(42);
   s_sys_clone2->GetYaxis()->SetLabelFont(42);
   s_sys_clone2->GetYaxis()->SetLabelSize(0.035);
   s_sys_clone2->GetYaxis()->SetTitleSize(0.035);
   s_sys_clone2->GetYaxis()->SetTitleFont(42);
   s_sys_clone2->GetZaxis()->SetLabelFont(42);
   s_sys_clone2->GetZaxis()->SetLabelSize(0.035);
   s_sys_clone2->GetZaxis()->SetTitleSize(0.035);
   s_sys_clone2->GetZaxis()->SetTitleFont(42);
   s_sys_clone2->Draw("histsame");
   
   TLegend *leg = new TLegend(0.1048851,0.684322,0.375,0.8834746,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.033);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("s_sys_clone","WIMP yield scaled to 50 Events M_{#chi} = 100GeV","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("PL_SR_s1s2_mass_100_sys","Systematic + Statistical Uncertainties","lpf");
   entry->SetFillColor(7);
   entry->SetFillStyle(1001);
   entry->SetLineColor(7);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(7);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
