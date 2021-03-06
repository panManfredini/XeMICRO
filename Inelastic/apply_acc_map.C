{


gStyle->SetOptStat(0);
TFile f_sit("fout.root");
TFile f_acc("acceptace_computation/acceptance.root");

TFile f_standard("acceptace_computation/merged_acc.root");

gROOT->ProcessLine(".L inelastic_style.C ");

//TH2D *s1_s2 = (TH2D*)f_standard.Get("s1_s2_no_Inelastic_Xs2single0");
TH2D *s1_s2 = (TH2D*)f_standard.Get("s1_s2");
s1_s2->Rebin2D(4,4);

gROOT->ProcessLine(".L inelastic_style.C ");

TH2F *h_sit = (TH2F*)f_sit.Get("combined");
h_sit->Rebin2D(4,4);

TH2F *with_acc = (TH2F*)h_sit->Clone("with_acc");

TH2D *acc_map = (TH2D*) f_acc.Get("total_acceptance");

for(int x =1; x < h_sit->GetXaxis()->GetNbins(); x++){

	double x_center  = with_acc->GetXaxis()->GetBinCenter(x);

	for(int y =1; y < h_sit->GetYaxis()->GetNbins(); y++){

		double y_center  = with_acc->GetYaxis()->GetBinCenter(y);

		double acc = acc_map->GetBinContent(acc_map->GetXaxis()->FindBin(x_center), acc_map->GetYaxis()->FindBin(y_center) );

		double content = with_acc->GetBinContent(x,y);
		with_acc->SetBinContent(x,y, content* acc);
					
		 
	}
	
}

gROOT->ProcessLine(".L inelastic_style.C ");
//new TCanvas();

h_sit->SetContour(5);
h_sit->SetLineColor(3);
with_acc->SetContour(5);
with_acc->SetLineColor(2);
s1_s2->SetContour(5);

s1_s2->Scale(1./s1_s2->Integral());
h_sit->Scale(1./h_sit->Integral());
with_acc->Scale(1./with_acc->Integral());


//h_sit->Draw("cont2 same");


  // comparison of projections

  TCanvas *c2 = new TCanvas("comparison","comp", 800,600);

  c2->Divide(2,2);

  TH1D *model_1 = s1_s2->ProjectionX("model_1",s1_s2->GetYaxis()->FindBin(6000),s1_s2->GetYaxis()->FindBin(8000)); 
  TH1D *model_2 = s1_s2->ProjectionX("model_2",s1_s2->GetYaxis()->FindBin(8000),s1_s2->GetYaxis()->FindBin(10000)); 
  TH1D *model_3 = s1_s2->ProjectionX("model_3",s1_s2->GetYaxis()->FindBin(10000),s1_s2->GetYaxis()->FindBin(12000)); 

  TH1D *data_1 = with_acc->ProjectionX("data_1",with_acc->GetYaxis()->FindBin(6000),with_acc->GetYaxis()->FindBin(8000)); 
  TH1D *data_2 = with_acc->ProjectionX("data_2",with_acc->GetYaxis()->FindBin(8000),with_acc->GetYaxis()->FindBin(10000)); 
  TH1D *data_3 = with_acc->ProjectionX("data_3",with_acc->GetYaxis()->FindBin(10000),with_acc->GetYaxis()->FindBin(12000)); 

  model_1->Scale(1./model_1->Integral());
  model_2->Scale(1./model_2->Integral());
  model_3->Scale(1./model_3->Integral());

  data_1->Scale(1./data_1->Integral());
  data_2->Scale(1./data_2->Integral());
  data_3->Scale(1./data_3->Integral());

gROOT->ProcessLine(".L inelastic_style.C ");

c2->cd(2);
gROOT->ProcessLine(".L inelastic_style.C ");
model_1->SetLineColor(2);
model_1->SetTitle("Slice 6000-8000 PE in S2"); 
data_1->SetLineColor(1);
data_1->SetMarkerStyle(20);
data_1->SetMarkerSize(0.5);
model_1->GetXaxis()->SetRangeUser(60,200);
model_1->Draw("hist");
data_1->Draw("esame");

c2->cd(3);
gROOT->ProcessLine(".L inelastic_style.C ");
model_2->SetLineColor(2);
model_2->SetTitle("Slice 8000-10000 PE in S2"); 
data_2->SetLineColor(1);
data_2->SetMarkerStyle(20);
data_2->SetMarkerSize(0.5);
model_2->GetXaxis()->SetRangeUser(60,200);
model_2->Draw("hist");
data_2->Draw("esame");

c2->cd(4);
gROOT->ProcessLine(".L inelastic_style.C ");
model_3->SetLineColor(2);
model_3->SetTitle("Slice 10000-12000 PE in S2"); 
data_3->SetLineColor(1);
data_3->SetMarkerStyle(20);
data_3->SetMarkerSize(0.5);
model_3->GetXaxis()->SetRangeUser(60,200);
model_3->Draw("hist");
data_3->Draw("esame");

c2->cd(1);

gROOT->ProcessLine(".L inelastic_style.C ");
s1_s2->GetXaxis()->SetRangeUser(60,200);
s1_s2->Draw("cont2");
with_acc->Draw("cont2 same");

TLegend* lego = new TLegend(0.2,0.9,0.5,0.7);
  lego->SetTextSize(0.033);
  lego->SetFillColor(0);
  lego->SetBorderSize(0);
  lego->AddEntry(s1_s2,"AmBe data");
  lego->AddEntry(with_acc, "Simulation");
  lego->Draw();

}
