{

TCanvas *c = new TCanvas();

TFile *f = TFile::Open("ambesimulation_cut.root");

TH2F * ambehistcut = (TH2F*) f->Get("ambehistcut");
TH2F * simhistcut = (TH2F*) f->Get("simhistcut");

//ambehistcut->Scale(1./ambehistcut->GetEntries());
ambehistcut->Scale(1./ambehistcut->GetMaximum());
//simhistcut->Scale(1./simhistcut->GetEntries());
simhistcut->Scale(1./simhistcut->GetMaximum());
TH2F *sim_clone = (TH2F*) simhistcut->Clone("clonesim");
sim_clone->Divide(ambehistcut);
sim_clone->GetZaxis()->SetRangeUser(0.,2.);
sim_clone->SetTitle("Ratio: simulation/AmBe");
sim_clone->Draw("colz");
c->Print("sim_ambe_comparison.pdf(");

// slicing
TH1D* ambe_py_80_100 = ambehistcut->ProjectionY("ambe_py_80_100", ambehistcut->GetXaxis()->FindBin(80.), ambehistcut->GetXaxis()->FindBin(100.));
TH1D* sim_py_80_100 = simhistcut->ProjectionY("sim_py_80_100", simhistcut->GetXaxis()->FindBin(80.), simhistcut->GetXaxis()->FindBin(100.));
//new TCanvas();
ambe_py_80_100->SetTitle("80 < S1 < 100");
ambe_py_80_100->GetYaxis()->SetRangeUser(0.,3.5);
ambe_py_80_100->Draw();
sim_py_80_100->SetLineColor(2);
sim_py_80_100->Draw("same");
c->Print("sim_ambe_comparison.pdf(");

TH1D* ambe_py_100_120 = ambehistcut->ProjectionY("ambe_py_100_120", ambehistcut->GetXaxis()->FindBin(100.), ambehistcut->GetXaxis()->FindBin(120.));
TH1D* sim_py_100_120 = simhistcut->ProjectionY("sim_py_100_120", simhistcut->GetXaxis()->FindBin(100.), simhistcut->GetXaxis()->FindBin(120.));
//new TCanvas();
ambe_py_100_120->SetTitle("100 < S1 < 120");
ambe_py_100_120->GetYaxis()->SetRangeUser(0.,3.5);
ambe_py_100_120->Draw();
sim_py_100_120->SetLineColor(2);
sim_py_100_120->Draw("same");
c->Print("sim_ambe_comparison.pdf(");

TH1D* ambe_py_120_140 = ambehistcut->ProjectionY("ambe_py_120_140", ambehistcut->GetXaxis()->FindBin(120.), ambehistcut->GetXaxis()->FindBin(140.));
TH1D* sim_py_120_140 = simhistcut->ProjectionY("sim_py_120_140", simhistcut->GetXaxis()->FindBin(120.), simhistcut->GetXaxis()->FindBin(140.));
//new TCanvas();
ambe_py_120_140->SetTitle("120 < S1 < 140");
ambe_py_120_140->GetYaxis()->SetRangeUser(0.,3.5);
ambe_py_120_140->Draw();
sim_py_120_140->SetLineColor(2);
sim_py_120_140->Draw("same");
c->Print("sim_ambe_comparison.pdf(");

TH1D* ambe_py_140_160 = ambehistcut->ProjectionY("ambe_py_140_160", ambehistcut->GetXaxis()->FindBin(140.), ambehistcut->GetXaxis()->FindBin(160.));
TH1D* sim_py_140_160 = simhistcut->ProjectionY("sim_py_140_160", simhistcut->GetXaxis()->FindBin(140.), simhistcut->GetXaxis()->FindBin(160.));
//new TCanvas();
ambe_py_140_160->SetTitle("140 < S1 < 160");
ambe_py_140_160->GetYaxis()->SetRangeUser(0.,3.5);
ambe_py_140_160->Draw();
sim_py_140_160->SetLineColor(2);
sim_py_140_160->Draw("same");
c->Print("sim_ambe_comparison.pdf)");


}
