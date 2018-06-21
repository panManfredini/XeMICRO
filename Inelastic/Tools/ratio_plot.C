TCanvas* ratio_plot(TH1D* h_num, TH1D* h_den, TString title, TH1D* h_den2 =NULL){


//Options
   gStyle->SetOptStat(0); 
   int den_color   = 2;
   int den2_color  = 4;
   int num_color   = 1;

  

//Setting the canvas
  TCanvas *c1 = new TCanvas("c_"+title,title,800,800);
  TPad *pad1 = new TPad("pad1"+title, "The pad 80% of the height",0.0,0.2,1.0,1.0);
  TPad *pad2 = new TPad("pad2"+title, "The pad 20% of the height",0.0,0.0,1.0,0.3);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();

//Stack plot
  TLegend* lego = new TLegend(0.2,0.9,0.5,0.7);
  lego->SetTextSize(0.033);
  lego->SetFillColor(0);
  lego->SetBorderSize(0);
  lego->AddEntry(h_num,h_num->GetTitle());
  lego->AddEntry(h_den,h_den->GetTitle());
  if(h_den2 != NULL) lego->AddEntry(h_den2,h_den2->GetTitle());

  h_den->SetLineColor(den_color);
  h_num->SetLineColor(num_color);
  if(h_den2 != NULL) h_den2->SetLineColor(den2_color);
  
  h_den->SetLineWidth(3);
  h_num->SetLineWidth(3);
  if(h_den2 != NULL) h_den2->SetLineWidth(3);


  h_den->SetTitle(title);   // title 

  h_den->GetXaxis()->SetLabelOffset(10);
  h_den->Draw("hist");
  if(h_den2 != NULL) h_den2->Draw("hist same");

  h_num->Draw("hist same");

  lego->Draw();



  // the ratio 
  pad2->cd();

  TH1D *divide_h = (TH1D*) h_num->Clone("divide_"+title);
  TH1D *divide2_h = NULL;

  if(h_den2 != NULL) divide2_h = (TH1D*) h_num->Clone("divide2_"+title);
  h_num->Sumw2();
  h_den->Sumw2();
  if(h_den2 != NULL) h_den2->Sumw2();
	  
  divide_h->Divide(h_den);
  if(h_den2 != NULL) divide2_h->Divide(h_den2);

 
  divide_h->SetLineColor(den_color);
  divide_h->SetMarkerColor(den_color);
  divide_h->SetMarkerStyle(20);
  if(h_den2 != NULL)  divide2_h->SetLineColor(den2_color);
  if(h_den2 != NULL)  divide2_h->SetMarkerColor(den2_color);
  if(h_den2 != NULL)  divide2_h->SetMarkerStyle(22);

  divide_h->SetTitle("");
  divide_h->GetXaxis()->SetLabelSize(0.1);
  divide_h->GetYaxis()->SetLabelSize(0.08);
  divide_h->GetYaxis()->SetRangeUser(0.5,1.5);
  divide_h->GetYaxis()->SetNdivisions(10);
  divide_h->Draw("P"); 
  if(h_den2 != NULL)  divide2_h->Draw("P same"); 

  pad2->SetGrid();
  
  pad2->Update();  
  pad2->RedrawAxis();  
  pad2->RedrawAxis("G");  

  gPad->RedrawAxis();
  gPad->RedrawAxis("G");

  return c1; 

}
