{

//TFile *f = TFile::Open("merge_noS1_34kg.root");
//TFile *f = TFile::Open("merge_34kg_full.root");  // s1 cut @ 200 PE
TFile *f = TFile::Open("merge_34kg_gaudenzCut.root");  // s1 cut @ 200 PE  Gaudenz Xwidht cut
//TFile *f = TFile::Open("merge_34kg.root");
//TFile *f = TFile::Open("merge.root");



//------------- SENSITIVITY --------------------------//
TH2D *co60 = (TH2D*) f->Get("log_s2_s1_Rot_Co60");
TH2D *ambe = (TH2D*) f->Get("log_s2_s1_Rot_AmBe");

//co60->Rebin2D(20,20);
//ambe->Rebin2D(20,20);

TH2D *sqrt_co60 = (TH2D*)co60->Clone("sqrt_co60");
TH2D *ambe_c = (TH2D*)ambe->Clone("ambe_c");

for(int x=0; x < sqrt_co60->GetNbinsX(); x++){
	for(int y=0; y < sqrt_co60->GetNbinsY(); y++){
		double sqrt_content = sqrt(sqrt_co60->GetBinContent(x,y));
		sqrt_co60->SetBinContent(x,y, sqrt_content);
	}
	
}


//sqrt_co60->Draw("colz");
ambe_c->Divide(sqrt_co60);

ambe_c->GetXaxis()->SetRangeUser(50,200);
ambe_c->GetYaxis()->SetRangeUser(2.2,3);
ambe_c->SetTitle("Sensitivity");
ambe_c->Draw("colz");
new TCanvas();
ambe->GetXaxis()->SetRangeUser(50,200);
ambe->GetYaxis()->SetRangeUser(2.2,3);
ambe->Draw("colz");

new TCanvas();
co60->GetXaxis()->SetRangeUser(50,200);
co60->GetYaxis()->SetRangeUser(2.2,3);
co60->Draw("colz");
//---------------------------------------------------//



/// --- data CO60 comparison

  TCanvas canv("canv", "First canvas", 500, 600);
  TPad *upper =new TPad("upper","plot", 0.01,0.26,0.99,0.99);
  TPad *lower =new TPad("lower","ratio", 0.01,0.01,0.99,0.35);
  lower->SetBottomMargin(0.3);
  lower->SetGridx();
  lower->SetGridy();
  upper->SetTopMargin(0.07);
  upper->Draw();
  lower->Draw();	
  
upper->cd();


TH2D *co60_noSR = (TH2D*) f->Get("s1_s2_noSR_Th232");
TH2D *data = (TH2D*) f->Get("s1_s2_noSR_DM");
//TH2D *co60_noSR = (TH2D*) f->Get("log_s2_s1_Co60");
//TH2D *data = (TH2D*) f->Get("log_s2_s1_DM");
//TH2D *co60_noSR = (TH2D*) f->Get("log_s2_s1_Rot_noSR_Co60");
//TH2D *data = (TH2D*) f->Get("log_s2_s1_Rot_noSR_DM");

co60_noSR->Rebin2D(20,20);
data->Rebin2D(20,20);

co60_noSR->Sumw2();
data->Sumw2();

data->Scale(1./data->GetEntries());
co60_noSR->Scale(1./co60_noSR->GetEntries());

TH1D *pro_co60 = co60_noSR->ProjectionX("ciccio_co");
TH1D *pro_data = data->ProjectionX("ciccio_data");
//TH1D *pro_co60 = co60_noSR->ProjectionX("ciccio_co", co60_noSR->GetYaxis()->FindBin(2.5));
//TH1D *pro_data = data->ProjectionX("ciccio_data", data->GetYaxis()->FindBin(2.5));

pro_co60->GetXaxis()->SetRangeUser(0.,200.);
//pro_co6->GetXaxis()->SetRange(0.,200.);
pro_co60->Draw("hist");
pro_data->SetLineColor(2);
pro_data->Draw("same");

TLegend* lego = new TLegend(0.2,0.9,0.5,0.7);
  lego->SetTextSize(0.033);
  lego->SetFillColor(0);
  lego->SetBorderSize(0);
  lego->AddEntry(pro_co60,"calibration Co60");
  lego->AddEntry(pro_data,"DM data");
lego->Draw();

lower->cd();

TH1D *divide_clone = (TH1D*) pro_data->Clone("divide_d");
divide_clone->Divide(pro_co60);
divide_clone->GetXaxis()->SetRangeUser(0.,200.);
divide_clone->Draw();

new TCanvas();
TH1D *pro_co60_Y = co60_noSR->ProjectionY("ciccio_co_Y", co60_noSR->GetXaxis()->FindBin(0.));
TH1D *pro_data_Y = data->ProjectionY("ciccio_data_Y", data->GetXaxis()->FindBin(0.));


pro_co60_Y->Draw("hist");
pro_data_Y->SetLineColor(2);
pro_data_Y->Draw("same");

//pro_data_Y->Divide(pro_co60_Y);
//pro_data_Y->Draw();

new TCanvas();
co60_noSR->SetTitle("Co60 NoSR - Rotated");
co60_noSR->Draw("colz");
new TCanvas();
data->SetTitle("DM NoSR - Rotated");
data->Draw("colz");




//---------------------Deviation in CR ------------//
TH2D *residuals = (TH2D*) data->Clone("residuals");

for (int x=0; x < data->GetNbinsX(); x++){
	for (int y=0; y < data->GetNbinsX(); y++){
		double x_center = data->GetXaxis()->GetBinCenter(x) ;
		double y_center = data->GetYaxis()->GetBinCenter(y);
//		if(x_center > 60. && x_center < 220. && y_center > 2.6 && y_center < 3.4) {
		   if(data->GetBinContent(x,y) > 0.) {
		   double res = sqrt(pow(co60_noSR->GetBinContent(x,y) - data->GetBinContent(x,y),2 )) / data->GetBinError(x,y);
			residuals->SetBinContent(x,y,res);
		    }
		   else residuals->SetBinContent(x,y,0.);	
	
//		}
//		else {
//			residuals->SetBinContent(x,y,0.);
//			residuals->SetBinError(x,y,0.);
//		}
	}
}

new TCanvas();
residuals->SetTitle("Residuals");
residuals->Draw("colz");
	


}
