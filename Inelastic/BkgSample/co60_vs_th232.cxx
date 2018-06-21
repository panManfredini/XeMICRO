{

   gStyle->SetOptStat(0); 

  TFile *f = TFile::Open("SR_CR_file.root");



  // determining scale factor and its uncertainty ///
  TH1D *SR_co60 = (TH1D*)f->Get("co60_PL_SR_reb");
  TH1D *SR_th232 = (TH1D*)f->Get("th232_PL_SR_reb");

//  SR_co60->Rebin();
//  SR_th232->Rebin();

  double bkg_scale = 0.034; 



  TCanvas *c1 = new TCanvas("c1","Example 2 pads (20,80)",800,800);
  TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0);
  TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.3);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();

  SR_co60->Scale(SR_th232->Integral()/SR_co60->Integral());

/*  TH1D* SR_co60_err = (TH1D*) SR_co60->Clone("SR_co60_err");

  for(int b = 1; b <= SR_co60->GetNbinsX(); b++) {
	double stat_err = SR_co60->GetBinError(b) /  SR_co60->GetBinContent(b);  // relative stat error
	double stat_sys_err = sqrt( pow(stat_err,2.) + pow(0.06,2.) ) * SR_co60->GetBinContent(b) ;
	SR_co60_err->SetBinError(b,stat_sys_err);
	

  }

  SR_co60_err->SetFillColor(3);
  SR_co60_err->Draw("E2");
*/
  
  SR_co60->Draw("hist");
  SR_th232->Draw("sameP");


  TLegend* lego = new TLegend(0.2,0.9,0.5,0.7);
  lego->SetTextSize(0.033);
  lego->SetFillColor(0);
  lego->SetBorderSize(0);
  lego->AddEntry(SR_th232,"^{232}Th");
  lego->AddEntry(SR_co60,"Normalized ^{60}Co");
  lego->Draw();


  // the divide looks Ugly (unfortunately) need to use reb for a nice plot

  TH1D *divide_th232_co = (TH1D*) SR_th232->Clone("divide_th232_o_co");
  divide_th232_co->Divide(SR_co60);

  TH1D *divide_th232_co_err = (TH1D*) SR_th232->Clone("divide_co_err") ;
  TH1D *divide_th232_co_err_stat = (TH1D*) SR_th232->Clone("divide_co_err_stat") ;
  divide_th232_co_err->Reset();
  divide_th232_co_err_stat->Reset();

  //set error correctly 
  for(int b = 1; b <= divide_th232_co->GetNbinsX(); b++) {
	
	double stat_err = SR_co60->GetBinError(b) /  SR_co60->GetBinContent(b);  // relative stat error
	double stat_sys_err = sqrt( pow(stat_err,2.) + pow(0.04,2.) );
	divide_th232_co_err->SetBinContent(b,1.);
	divide_th232_co_err->SetBinError(b,stat_sys_err);
	divide_th232_co_err_stat->SetBinContent(b,1.);
	divide_th232_co_err_stat->SetBinError(b,stat_err);
		
  }

  
  pad2->cd();

  divide_th232_co_err->SetFillColor(858);
  divide_th232_co_err->GetYaxis()->SetRangeUser(0.8,1.2);
  divide_th232_co_err->GetYaxis()->SetNdivisions(14);
  divide_th232_co_err->Draw("E2");
  divide_th232_co_err_stat->SetFillColor(920);
  divide_th232_co_err_stat->Draw("AsameE2");
 
  divide_th232_co->Draw("Psame"); 




  pad2->SetGrid();
  
  pad2->Update();  
  pad2->RedrawAxis();  
  pad2->RedrawAxis("G");  

  gPad->RedrawAxis();
  gPad->RedrawAxis("G");
}
