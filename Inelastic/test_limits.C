{
/*
----------- GLOBAL VARIABLES ------ 
Events in CR data  836
Events in CR Co60  22017
Events in CR AmBe  628
Norm Factor        0.0379707  +-  0.00133794  (rel in % = 3.52362 )
Events in SR Co60  24200
Events in SR AmBe  13083
Events in TOTAL for AmBe  111752
Events in TOTAL for Co60  72157
Events in TOTAL for DATA  2685
TOTAL integrated livetime 225.009 days
*/

 double bkg = 22017. * 0.0379707;
 double bkg_err = sqrt(bkg);

 double signal = 1.;
 double b_plus_s = bkg + signal;
 double b_plus_s_err = sqrt(b_plus_s);

 TF1 *test = new TF1("test","exp(-0.5*((x-[0])/[1])**2)/([1]*sqrt(3.1415*2.)) ",0.,2000.);
 
 test->SetParameters(bkg,bkg_err);
 cout << test->Integral(bkg, 1500.) << endl;
 cout << 1. - test->Integral(bkg + 3.* bkg_err, 1500.) * 2. << endl;

 for (double k =0; k < 1000. ; k++)
     {
	signal = k;
	test->SetParameters(bkg + signal, sqrt(bkg + signal));
	if( test->Integral(0., bkg) < 0.1) {
		cout <<" Signal = " << signal << endl;
		cout << test->Integral(0., bkg) << endl;
		break;
	}
     }


//REMOVEME
//bkg=5.;
double p_val = 0.;
for (int j = 1; j < 1000. ; j++){
	signal = j;
	p_val = 0.;

	for(int i =0; i <= (int)bkg; i++) p_val += TMath::PoissonI(i, bkg + signal);
	if(p_val <= 0.1) { cout << " equiv.. p-val  " << p_val << " Signal = " << signal<<endl; break;}
}


//-----------------  Pearson Chi2 test

TFile *f = TFile::Open("h_for_limits.root");

TH1D *s = (TH1D*)f->Get("ambe_SR");
TH1D *co = (TH1D*)f->Get("co60_SR");

s->Sumw2();
co->Sumw2();
s->Scale(1./ 13690.);
co->Scale(1./24318. );

s->Rebin( 10);
co->Rebin(10);

cout << " Itegrals  " << s->Integral(1,40) << "   " << co->Integral(1,40) << endl; 

co->SetLineColor(2);
s->Draw();
co->Draw("same");


// NDoF == 40 -1 
for(int j =0; j< 1000; j++){
	signal = j;

	TRandom p;
	p.SetSeed(11254.);
//	signal =1. ;
	double chi2 = 0.;
	for(int bin =1; bin <= co->GetNbinsX() ; bin ++){
		double bkg_bin_i = bkg * co->GetBinContent(bin);
		double bkg_obs_i = p.PoissonD(bkg_bin_i);
		double signal_bin_i = signal * s->GetBinContent(bin);
//		double tot_bin_i =   bkg_bin_i;
		double tot_bin_i =  signal_bin_i + bkg_bin_i;
		chi2 += pow(bkg_obs_i - tot_bin_i, 2.) / tot_bin_i;
//		cout << " B_obs_i " << bkg_obs_i << "  B_i " << bkg_bin_i << " ---  " << pow(bkg_obs_i - bkg_bin_i, 2.) / bkg_bin_i << endl;
	}	

	if(chi2 > TMath::ChisquareQuantile(0.9,co->GetNbinsX() -1.) )   {
		cout <<"Pearson test  Signal Excluded = " << signal << endl;
                cout << "Chi2  " << chi2 << endl;
		break;
	}
}



////--------------- test the sigma!!

cout << " Sigma one bin  for signal 40 " << (40. + bkg) / sqrt(bkg) << endl;

	double inv_sigma = 0.;

	for(int bin =1; bin <= co->GetNbinsX() ; bin ++){
		double bkg_bin_i = bkg * co->GetBinContent(bin);
		double signal_bin_i = 40. * s->GetBinContent(bin);
		inv_sigma += bkg_bin_i * pow(s->GetBinContent(bin),2.) / pow(bkg_bin_i + signal_bin_i, 2.) ;
	}
	
cout << " Sigma many bin for S=4. " <<	sqrt(1./inv_sigma) << endl;


s->Scale(6.);
co->Scale(916.);
co->SetLineColor(2);
co->Draw();
s->Draw("same");

}
