{

   gStyle->SetOptStat(0); 

  TFile *f = TFile::Open("SR_CR_file.root");


  // determining scale factor and its uncertainty ///
  TH2D *CR_co60 = (TH2D*)f->Get("CR_co60");
  TH2D *CR_dm = (TH2D*)f->Get("CR_dm");


//-- two projections one before SR in S2 one after
  int low_prj_y1 = CR_co60->GetYaxis()->FindBin(5000.);
  int low_prj_y2 = CR_co60->GetYaxis()->FindBin(7000.);

  int high_prj_y1 = CR_co60->GetYaxis()->FindBin(13000.);
  int high_prj_y2 = CR_co60->GetYaxis()->FindBin(17000.);
  
  TH1D *low_prj_co60 =  (TH1D*) CR_co60->ProjectionX("low_prj_co60",low_prj_y1,low_prj_y2);
  TH1D *low_prj_dm   =  (TH1D*) CR_dm->ProjectionX("low_prj_dm",low_prj_y1,low_prj_y2);

  TH1D *high_prj_co60 =  (TH1D*) CR_co60->ProjectionX("high_prj_co60",high_prj_y1,high_prj_y2);
  TH1D *high_prj_dm   =  (TH1D*) CR_dm->ProjectionX("high_prj_dm",high_prj_y1,high_prj_y2);

  cout << " CO60 low " << low_prj_co60->Integral() << "  DM low  " << low_prj_dm->Integral()  << "  tau = " << low_prj_dm->Integral() / low_prj_co60->Integral()<< endl;
  cout << " CO60 high " << high_prj_co60->Integral() << "  DM high  " << high_prj_dm->Integral()  << "  tau = " << high_prj_dm->Integral() / high_prj_co60->Integral()<< endl;

  double bkg_scale = ( low_prj_dm->Integral() / low_prj_co60->Integral() + high_prj_dm->Integral() / high_prj_co60->Integral() ) / 2.;

  double rel_err   = sqrt( 1. / low_prj_co60->Integral() + 1. / low_prj_dm->Integral() );

  cout << " TAU  = " << bkg_scale << "  +-  " << rel_err*100. << "\%  OR " << rel_err *bkg_scale << endl;


  TCanvas *c1 = new TCanvas("c1","Example 2 pads (20,80)",800,800);
  TPad *pad1 = new TPad("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0);
  TPad *pad2 = new TPad("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.3);
  pad1->Draw();
  pad2->Draw();

  pad1->cd();
  low_prj_co60->Scale(bkg_scale);
  high_prj_co60->Scale(bkg_scale);

  low_prj_co60->Add(high_prj_co60);
  low_prj_dm->Add(high_prj_dm);

  TH1D *divide_low_prj = (TH1D*) low_prj_dm->Clone("divide_low_prj");
  TH1D *divide_low_prj_err = (TH1D*) low_prj_dm->Clone("divide_low_prj_err");
  divide_low_prj->Divide(low_prj_co60);
  //set error correctly 
  for(int b = 1; b <= divide_low_prj->GetNbinsX(); b++) {

	divide_low_prj_err->SetBinContent(b,1.);
	if(low_prj_dm->GetBinContent(b) > 0. && low_prj_co60->GetBinContent(b) > 0.){ 
	  double err =  sqrt( 1. / low_prj_co60->GetBinContent(b) + 1. / low_prj_dm->GetBinContent(b) ); 
	  divide_low_prj->SetBinError(b, err * divide_low_prj->GetBinContent(b));
	  divide_low_prj_err->SetBinError(b, err * divide_low_prj->GetBinContent(b));
        }
	
  }

  low_prj_co60->GetXaxis()->SetRangeUser(50.,200.);
  low_prj_co60->Draw("hist");
  low_prj_dm->Draw("sameE");
  
  pad2->cd();
  
  divide_low_prj_err->GetXaxis()->SetRangeUser(50.,200.);
  divide_low_prj_err->GetYaxis()->SetRangeUser(0.8,1.2);
//  divide_low_prj_err->SetFillColor(4);
  divide_low_prj_err->Draw("hist");
  
  divide_low_prj->Draw("sameE");

/*
  new TCanvas();
  high_prj_co60->Draw("hist");
  high_prj_dm->Draw("sameE");
*/
  
}
