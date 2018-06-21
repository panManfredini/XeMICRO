{

gROOT->ProcessLine(".L ../inelastic_style.C "); 

setInelasticStyle();

TCanvas canv("canv", "First canvas", 1000, 800);
  gPad->SetLeftMargin(0.13);
  gPad->SetTopMargin(0.00);
  gPad->SetBottomMargin(0.12);
  gPad->SetRightMargin(0.04);

  TFile *f = TFile::Open("SR_CR_file.root");

  TFile *s = TFile::Open("../SignalSamples/final_signals_with_sys_reb.root");


  // determining scale factor and its uncertainty ///
  TH1D *SR_co60 = (TH1D*)f->Get("co60_PL_SR_reb");
  TH1D *SR_dm = (TH1D*)f->Get("dm_PL_SR_reb");
  TH1D *SR_100 = (TH1D*)s->Get("PL_SR_s1s2_mass_100_sys");

//  SR_co60->Rebin();
//  SR_dm->Rebin();

  double bkg_scale = 0.034; 



//  TCanvas *c1 = new TCanvas("c1","Example 2 pads (20,80)",800,800);
  TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.3,1.0,1.0);
  TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.35 );
  pad1->SetTopMargin(0.05);
  pad1->SetRightMargin(0.05);
  pad2->SetTopMargin(0.1);
  pad2->SetRightMargin(0.05);
  pad2->SetBottomMargin(0.30);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();

  cout << " total observed Co60 " << SR_co60->Integral() << endl;
  SR_co60->Scale(bkg_scale);
  cout << " Expected  " << SR_co60->Integral() << endl;
  cout << " Observed DM " << SR_dm->Integral() << endl;


//  TH1D* SR_co60_err = (TH1D*) SR_co60->Clone("SR_co60_err");

	cout << "bin " <<  " bkg content " << "  Unc stat + sys  " << endl;
  for(int b = 1; b <= SR_co60->GetNbinsX(); b++) {
	double stat_err = SR_co60->GetBinError(b) /  SR_co60->GetBinContent(b);  // relative stat error
	double stat_sys_err = sqrt( pow(stat_err,2.) + pow(0.06,2.) + pow(0.04,2.) ) * SR_co60->GetBinContent(b) ;
//	SR_co60_err->SetBinError(b,stat_sys_err);
	cout << b <<  "       " << SR_co60->GetBinContent(b) << "         " << stat_sys_err << endl;
	

  }
/*
  SR_co60_err->SetFillColor(3);
  SR_co60_err->Draw("E2");
*/
  
  //SR_co60->SetFillColor(807);
  SR_co60->SetFillColor(425);
  SR_co60->SetLineColor(425);
  SR_co60->SetLineWidth(3);
  SR_co60->GetYaxis()->SetRangeUser(0.,220.);
  SR_co60->GetYaxis()->SetTitle("Events");
  SR_co60->GetYaxis()->SetTitleSize(0.05/0.7);
  SR_co60->GetYaxis()->SetLabelSize(0.05/0.7);
  SR_co60->GetXaxis()->SetTitleSize(0.05/0.7);
  SR_co60->GetYaxis()->SetTitleOffset(0.75);
  SR_co60->GetXaxis()->SetTitleOffset(1.);
  SR_co60->GetXaxis()->SetLabelOffset(1.);
  SR_co60->GetXaxis()->SetLabelSize(0.05/0.7);
  SR_co60->SetMarkerColor(425);
  SR_co60->Draw("hist");

  SR_100->Scale(50./SR_100->Integral());
  SR_100->Add(SR_co60);
  SR_100->SetLineColor(603);
  SR_100->SetLineWidth(4);
  SR_100->SetLineStyle(9);
  SR_100->Draw("histsame");

  SR_dm->SetLineWidth(3);
  SR_dm->SetLineColor(1);
  SR_dm->SetMarkerStyle(20);
  SR_dm->Draw("sameP");

  TLegend* lego = new TLegend(0.15,0.93,0.6,0.7);
  lego->SetTextSize(0.05/0.7);
  lego->SetTextFont(132);
  lego->SetFillColor(0);
  lego->SetBorderSize(0);
  lego->AddEntry(SR_dm,"Data");
  lego->AddEntry(SR_co60,"Normalized Calibration ^{60}Co");
  lego->AddEntry(SR_100,"Signal M_{#chi}=100GeV, scaled to 50 events");
  lego->Draw();


  // the divide looks Ugly (unfortunately) need to use reb for a nice plot

  TH1D *divide_dm_co = (TH1D*) SR_dm->Clone("divide_dm_o_co");
  divide_dm_co->Divide(SR_co60);

  TH1D *divide_dm_co_err = (TH1D*) SR_dm->Clone("divide_co_err") ;
  TH1D *divide_dm_co_err_stat = (TH1D*) SR_dm->Clone("divide_co_err_stat") ;
  divide_dm_co_err->Reset();
  divide_dm_co_err_stat->Reset();

  //set error correctly 
  for(int b = 1; b <= divide_dm_co->GetNbinsX(); b++) {
	
	double stat_err = SR_co60->GetBinError(b) /  SR_co60->GetBinContent(b);  // relative stat error
	double stat_sys_err = sqrt( pow(stat_err,2.) + pow(0.06,2.) + pow(0.04,2.));
	divide_dm_co_err->SetBinContent(b,1.);
	divide_dm_co_err->SetBinError(b,stat_sys_err);
	divide_dm_co_err_stat->SetBinContent(b,1.);
	divide_dm_co_err_stat->SetBinError(b,stat_err);
		
  }

  
  pad2->cd();
setInelasticStyle(0.35);

  divide_dm_co_err->GetYaxis()->SetRangeUser(0.8,1.2);
  divide_dm_co_err->GetYaxis()->SetTitleSize(0.05/0.35);
  divide_dm_co_err->GetYaxis()->SetLabelSize(0.05/0.35);
  divide_dm_co_err->GetXaxis()->SetTitleSize(0.05/0.35);
  divide_dm_co_err->GetXaxis()->SetLabelSize(0.05/0.35);
  divide_dm_co_err->SetFillColor(861);
  divide_dm_co_err->GetYaxis()->SetNdivisions(5, true);
  divide_dm_co_err->GetYaxis()->SetTitle("Ratio");
  divide_dm_co_err->GetYaxis()->SetTitleOffset(0.35);
  divide_dm_co_err->GetXaxis()->SetTitle("Sub-regions");
  divide_dm_co_err->GetXaxis()->SetTitleOffset(1.);
  divide_dm_co_err->SetMarkerStyle(0);
  divide_dm_co_err->SetMarkerColor(861);
  divide_dm_co_err->GetYaxis()->CenterTitle();
  divide_dm_co_err->Draw("E2");
  divide_dm_co_err_stat->SetMarkerStyle(0);
  divide_dm_co_err_stat->SetMarkerColor(861);
  divide_dm_co_err_stat->SetFillColor(425);
  divide_dm_co_err_stat->Draw("AsameE2");
 
  divide_dm_co->Draw("Psame"); 




  pad2->SetGrid();
  
  pad2->Update();  
  pad2->RedrawAxis();  
  pad2->RedrawAxis("G");  

  pad1->Update();  
  pad1->RedrawAxis();  
  pad1->RedrawAxis("G");  

  gPad->RedrawAxis();
  gPad->RedrawAxis("G");

  canv.Print("/home/pan/work/XeMICRO/Inelastic/SignalSamples/data_vs_bkg.png");
  canv.Print("/home/pan/work/XeMICRO/Inelastic/SignalSamples/data_vs_bkg.eps");
  canv.Print("/home/pan/Documents/Papers/mypapers/Inelastic/images/data_vs_bkg.png");
  canv.Print("/home/pan/Documents/Papers/mypapers/Inelastic/images/data_vs_bkg.eps");




}
