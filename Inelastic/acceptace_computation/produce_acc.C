{

 gStyle->SetOptStat(0);
 TFile f("merged_acc.root");
 
 TH2D *s1_s2 = (TH2D*)f.Get("s1_s2");

 TH2D *s1_s2_nocut = (TH2D*)f.Get("s1_s2_nocut");

cout <<  s1_s2->GetNcells() << endl;

// s1_s2->Rebin2D(4,2);
 s1_s2->Rebin2D(8,4);
// s1_s2->Rebin2D(10,10);

// s1_s2_nocut->Rebin2D(10,10);
// s1_s2_nocut->Rebin2D(4,2);
 s1_s2_nocut->Rebin2D(8,4);

cout <<  s1_s2->GetNcells() << endl;


 s1_s2->GetXaxis()->SetRangeUser(60,200);
 s1_s2->GetYaxis()->SetRangeUser(6000,12000);
// s1_s2->GetYaxis()->SetRangeUser(1.6,2.4);

    std::vector<TString> cut_names;
        cut_names.push_back("Xsignalnoise3");
        cut_names.push_back( "Xsignalnoise4");
       cut_names.push_back( "Xs1width0");
        cut_names.push_back( "Xlownoise0_m");
        cut_names.push_back( "Xentropy0");
        cut_names.push_back( "Xs2top0");
        cut_names.push_back( "Xs2peaks2");
        cut_names.push_back( "Xs1coin2");
        cut_names.push_back( "Xhighlog1");
//        cut_names.push_back( "Inelastic_Xs2single0");  // bad cut  ----- 97.7±0.6 %
        cut_names.push_back( "Xs1single4");
//        cut_names.push_back( "Xveto2");               //  bad cut  ----- 99.6±0.4 
        cut_names.push_back( "XPL013_97");
        cut_names.push_back( "Xposrec1");
        cut_names.push_back( "Xs2chisquare0");        // bad cut      
        cut_names.push_back( "Xs2peakpos0");
        cut_names.push_back( "Xs2width0");


 TH2D *tot_acc_full = (TH2D*)s1_s2->Clone("tot_acc_full");

 tot_acc_full->Divide(s1_s2_nocut);

 TH2D *tot_acc     = (TH2D*)s1_s2->Clone("tot_acc");
 tot_acc->Reset();
// tot_acc->Draw("COLZ");


 TH2D *temp;

 double int_final = 0.; 

 double err = 0.;

 double acc = 1.; 

 for(unsigned int t=0; t < cut_names.size(); t++){

 	temp = (TH2D*) f.Get("s1_s2_no_"+cut_names[t]);
//	temp->Rebin2D(4,2);
	temp->Rebin2D(8,4);
//	temp->Rebin2D(10,10);

	int x_min = temp->GetXaxis()->FindBin(50.);
	int x_max = temp->GetXaxis()->FindBin(200.);
	int y_min = temp->GetYaxis()->FindBin(6000.);
	int y_max = temp->GetYaxis()->FindBin(12000.);
	double temp_int = temp->Integral(x_min,x_max,y_min,y_max);

	int_final = s1_s2->Integral(x_min,x_max,y_min,y_max);
	
	err += 1./(int_final) + 1./temp_int;

        acc = acc * int_final/temp_int;

	cout << temp_int << endl;	

	for(int b=0; b< tot_acc->GetNcells(); b++){

		if(tot_acc->GetBinContent(b) == 0.) tot_acc->SetBinContent(b,1.);
		if(s1_s2->GetBinContent(b) ==0.) continue;

		double content = tot_acc->GetBinContent(b) * s1_s2->GetBinContent(b) / temp->GetBinContent(b);
		double err     = sqrt( pow(tot_acc->GetBinError(b),2) + 1./s1_s2->GetBinContent(b) + 1./ temp->GetBinContent(b) ); 
		tot_acc->SetBinContent(b,content);
		tot_acc->SetBinError(b, err);  // relative error
	}
 }
 

 err = sqrt(err) * acc;

 cout << "Acc " << acc << " err " << err << endl;
 
 // need to move from relative error to full error
 for(int b=0; b< tot_acc->GetNcells(); b++){ 
	tot_acc->SetBinError(b, tot_acc->GetBinError(b) * tot_acc->GetBinContent(b) ) ;
 }
 
 
 TH2D *tot_acc_p1s     = (TH2D*)s1_s2->Clone("tot_acc_p1s");  //plus 1 sigma
 tot_acc_p1s->Reset();
 TH2D *tot_acc_m1s     = (TH2D*)s1_s2->Clone("tot_acc_m1s");  //minus 1 sigma
 tot_acc_m1s->Reset();

 for(int b=0; b< tot_acc->GetNcells(); b++){ 
	double plus_1sigma =  tot_acc->GetBinContent(b) + tot_acc->GetBinError(b);
	double minus_1sigma = tot_acc->GetBinContent(b) - tot_acc->GetBinError(b);
	if(plus_1sigma > 1.) plus_1sigma = 1.;
        if(minus_1sigma < 0. ) minus_1sigma = 0.;

	tot_acc_p1s->SetBinContent(b, plus_1sigma);
	tot_acc_m1s->SetBinContent(b, minus_1sigma);
 }
 
// tot_acc->Print("all");

 //applying additional cut acceptances Inelastic_Xs2single0 and Xveto2 
 tot_acc->Scale(0.977 * 0.996);
 tot_acc->SetTitle("Acceptance Map");
 tot_acc->SetContour(30);
 tot_acc->Draw("CONT4Z");
  new TCanvas;
 tot_acc_p1s->Scale(0.977 * 0.996);
 tot_acc_p1s->SetTitle("Acceptance Map + 1#sigma");
 tot_acc_p1s->SetContour(30);
 tot_acc_p1s->Draw("COLZ");
  new TCanvas;
 tot_acc_m1s->Scale(0.977 * 0.996);
 tot_acc_m1s->SetTitle("Acceptance Map - 1#sigma");
 tot_acc_m1s->SetContour(30);
 tot_acc_m1s->Draw("CONT4Z");
  new TCanvas;
 tot_acc_full->SetTitle("Acceptance Map for AmBe Events");
 tot_acc_full->SetContour(30);
 tot_acc_full->Draw("CONT4Z");

 TFile fout("acceptance.root","RECREATE");
 fout.cd();
 tot_acc->Write("total_acceptance");
 tot_acc_p1s->Write("total_acceptance_p1s");
 tot_acc_m1s->Write("total_acceptance_m1s");
 tot_acc_full->Write("total_acceptance_full");

 fout.Close();

/*
KEY: TH2D	s1_s2_no_Xsignalnoise3;1	Xsignalnoise3
  KEY: TH2D	s1_logs2_noXsignalnoise3;1	Xsignalnoise3
  KEY: TH2D	s1_s2_no_Xsignalnoise4;1	Xsignalnoise4
  KEY: TH2D	s1_logs2_noXsignalnoise4;1	Xsignalnoise4
  KEY: TH2D	s1_s2_no_Xs1width0;1	Xs1width0
  KEY: TH2D	s1_logs2_noXs1width0;1	Xs1width0
  KEY: TH2D	s1_s2_no_Xlownoise0_m;1	Xlownoise0_m
  KEY: TH2D	s1_logs2_noXlownoise0_m;1	Xlownoise0_m
  KEY: TH2D	s1_s2_no_Xentropy0;1	Xentropy0
  KEY: TH2D	s1_logs2_noXentropy0;1	Xentropy0
  KEY: TH2D	s1_s2_no_Xs2top0;1	Xs2top0
  KEY: TH2D	s1_logs2_noXs2top0;1	Xs2top0
  KEY: TH2D	s1_s2_no_Xs2peaks2;1	Xs2peaks2
  KEY: TH2D	s1_logs2_noXs2peaks2;1	Xs2peaks2
  KEY: TH2D	s1_s2_no_Xs1coin2;1	Xs1coin2
  KEY: TH2D	s1_logs2_noXs1coin2;1	Xs1coin2
  KEY: TH2D	s1_s2_no_Xhighlog1;1	Xhighlog1
  KEY: TH2D	s1_logs2_noXhighlog1;1	Xhighlog1
  KEY: TH2D	s1_s2_no_Inelastic_Xs2single0;1	Inelastic_Xs2single0
  KEY: TH2D	s1_logs2_noInelastic_Xs2single0;1	Inelastic_Xs2single0
  KEY: TH2D	s1_s2_no_Xs1single4;1	Xs1single4
  KEY: TH2D	s1_logs2_noXs1single4;1	Xs1single4
  KEY: TH2D	s1_s2_no_Xveto2;1	Xveto2
  KEY: TH2D	s1_logs2_noXveto2;1	Xveto2
  KEY: TH2D	s1_s2_no_XPL013_97;1	XPL013_97
  KEY: TH2D	s1_logs2_noXPL013_97;1	XPL013_97
  KEY: TH2D	s1_s2_no_Xposrec1;1	Xposrec1
  KEY: TH2D	s1_logs2_noXposrec1;1	Xposrec1
  KEY: TH2D	s1_s2_no_Xs2chisquare0;1	Xs2chisquare0
  KEY: TH2D	s1_logs2_noXs2chisquare0;1	Xs2chisquare0
  KEY: TH2D	s1_s2_no_Xs2peakpos0;1	Xs2peakpos0
  KEY: TH2D	s1_logs2_noXs2peakpos0;1	Xs2peakpos0
  KEY: TH2D	s1_s2_no_Xs2width0;1	Xs2width0
  KEY: TH2D	s1_logs2_noXs2width0;1	Xs2width0
  KEY: TH2D	s1_s2;1	
  KEY: TH2D	s1_logs2;1	
*/ 


}
