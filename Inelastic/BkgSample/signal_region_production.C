{

  TFile *f = TFile::Open("../DATA/final_merge.root");

  TH2D *ambe = (TH2D*)f->Get("s1_s2_AmBe");
  TH2D *co60 = (TH2D*)f->Get("s1_s2_Co60");
  TH2D *th232 = (TH2D*)f->Get("s1_s2_Th232");
  TH2D *dm = (TH2D*)f->Get("s1_s2_DM");

  TH2D *ambe_l = (TH2D*)f->Get("log_s2_s1_SR_AmBe");
  TH2D *co60_l = (TH2D*)f->Get("log_s2_s1_SR_Co60");
  TH2D *dm_l = (TH2D*)f->Get("log_s2_s1_SR_DM");

  cout << ambe->GetNbinsX() << endl; 
  cout << ambe->GetNbinsY() << endl; 
  ambe->Rebin2D(30,20);
  co60->Rebin2D(30,20);
  th232->Rebin2D(30,20);
  dm->Rebin2D(30,20);

  ambe->SetLineColor(2);
  ambe->SetLineWidth(3);

  co60->SetLineColor(4);
  co60->SetLineWidth(3);

  ambe->SetContour(5);
  co60->SetContour(5);


  cout << ambe->GetXaxis()->GetBinWidth(1) << "    " <<   ambe->GetYaxis()->GetBinWidth(1) << endl;

  ambe->Draw("colz");
//  ambe->Scale(1./ambe->Integral());
  //ambe->Draw("cont3");
 // co60->Draw("cont3same");
  new TCanvas();
//  co60->Scale(1./co60->Integral());
  co60->GetXaxis()->SetRangeUser(60,200);
  co60->GetYaxis()->SetRangeUser(6000,14000);
  
  co60->Draw("CONTZ");

// log(s2/s1) 
  ambe_l->Rebin2D(4,4);
  co60_l->Rebin2D(4,4);

  ambe_l->SetLineColor(2);
  ambe_l->SetLineWidth(3);

  co60_l->SetLineColor(4);
  co60_l->SetLineWidth(3);

  ambe_l->SetContour(5);
  co60_l->SetContour(5);

  new TCanvas();
  ambe_l->Draw("cont3");
  co60_l->Draw("cont3same");


 //Signal region production PL
 TH1F *ambe_PL_SR = new TH1F("ambe_PL_SR","",16,0.5,16.5);
 TH1F *co60_PL_SR = new TH1F("co60_PL_SR","",16,0.5,16.5);
 TH1F *th232_PL_SR = new TH1F("th232_PL_SR","",16,0.5,16.5);
 TH1F *dm_PL_SR =   new TH1F("dm_PL_SR","",16,0.5,16.5);

 TH2D *CR_ambe  = (TH2D*) ambe->Clone("CR_ambe");
 CR_ambe->Reset();
 TH2D *CR_co60  = (TH2D*) ambe->Clone("CR_co60");
 CR_co60->Reset();
 TH2D *CR_th232  = (TH2D*) ambe->Clone("CR_th232");
 CR_th232->Reset();
 TH2D *CR_dm  = (TH2D*) ambe->Clone("CR_dm");
 CR_dm->Reset();

 int bincounter = 1; 

 for(int xbin=1; xbin <= ambe->GetNbinsX(); xbin++) {
 	for(int ybin=1; ybin <= ambe->GetNbinsY(); ybin++) {

		double s1 = ambe->GetXaxis()->GetBinCenter(xbin);
		double s2 = ambe->GetYaxis()->GetBinCenter(ybin);

		//inside SR
		if(s1 > 60. && s1 < 210. && s2 >6000. && s2 < 14000.){
			
			if(s1 <100. && s2 < 8000. ) {
				CR_ambe->SetBinContent(xbin,ybin,ambe->GetBinContent(xbin,ybin));
				CR_co60->SetBinContent(xbin,ybin,co60->GetBinContent(xbin,ybin));
				CR_th232->SetBinContent(xbin,ybin,th232->GetBinContent(xbin,ybin));
				CR_dm->SetBinContent(xbin,ybin,dm->GetBinContent(xbin,ybin));

				CR_ambe->SetBinError(xbin,ybin,ambe->GetBinError(xbin,ybin));
				CR_co60->SetBinError(xbin,ybin,co60->GetBinError(xbin,ybin));
				CR_th232->SetBinError(xbin,ybin,th232->GetBinError(xbin,ybin));
				CR_dm->SetBinError(xbin,ybin,dm->GetBinError(xbin,ybin));

				continue;
			}
			if(s1 >180. && s2 > 12000.) {
				CR_ambe->SetBinContent(xbin,ybin,ambe->GetBinContent(xbin,ybin));
				CR_co60->SetBinContent(xbin,ybin,co60->GetBinContent(xbin,ybin));
				CR_th232->SetBinContent(xbin,ybin,th232->GetBinContent(xbin,ybin));
				CR_dm->SetBinContent(xbin,ybin,dm->GetBinContent(xbin,ybin));

				CR_ambe->SetBinError(xbin,ybin,ambe->GetBinError(xbin,ybin));
				CR_co60->SetBinError(xbin,ybin,co60->GetBinError(xbin,ybin));
				CR_th232->SetBinError(xbin,ybin,th232->GetBinError(xbin,ybin));
				CR_dm->SetBinError(xbin,ybin,dm->GetBinError(xbin,ybin));
				continue;
			}

			if(s1 >180. && s2 < 12000.) {
				ambe_PL_SR->AddBinContent(16,ambe->GetBinContent(xbin,ybin));
				co60_PL_SR->AddBinContent(16,co60->GetBinContent(xbin,ybin));
				th232_PL_SR->AddBinContent(16,th232->GetBinContent(xbin,ybin));
				dm_PL_SR->AddBinContent(16,dm->GetBinContent(xbin,ybin));

				double err_dm = sqrt(pow(dm_PL_SR->GetBinError(16),2) + pow(dm->GetBinError(xbin,ybin),2)) ;
				double err_ambe = sqrt(pow(ambe_PL_SR->GetBinError(16),2) + pow(ambe->GetBinError(xbin,ybin),2)) ;
				double err_co = sqrt(pow(co60_PL_SR->GetBinError(16),2) + pow(co60->GetBinError(xbin,ybin),2)) ;
				double err_th = sqrt(pow(th232_PL_SR->GetBinError(16),2) + pow(th232->GetBinError(xbin,ybin),2)) ;
				ambe_PL_SR->SetBinError(16,err_ambe);
				dm_PL_SR->SetBinError(16,err_dm);
				co60_PL_SR->SetBinError(16,err_co);
				th232_PL_SR->SetBinError(16,err_th);
			}
			else{
				ambe_PL_SR->SetBinContent(bincounter,ambe->GetBinContent(xbin,ybin));
				co60_PL_SR->SetBinContent(bincounter,co60->GetBinContent(xbin,ybin));
				th232_PL_SR->SetBinContent(bincounter,th232->GetBinContent(xbin,ybin));
				dm_PL_SR->SetBinContent(bincounter,dm->GetBinContent(xbin,ybin));

				ambe_PL_SR->SetBinError(bincounter,ambe->GetBinError(xbin,ybin));
				co60_PL_SR->SetBinError(bincounter,co60->GetBinError(xbin,ybin));
				th232_PL_SR->SetBinError(bincounter,th232->GetBinError(xbin,ybin));
				dm_PL_SR->SetBinError(bincounter,dm->GetBinError(xbin,ybin));
		
				bincounter++;	
			}
			
		}
		else{
			
			CR_ambe->SetBinContent(xbin,ybin,ambe->GetBinContent(xbin,ybin));
			CR_co60->SetBinContent(xbin,ybin,co60->GetBinContent(xbin,ybin));
			CR_th232->SetBinContent(xbin,ybin,th232->GetBinContent(xbin,ybin));
			CR_dm->SetBinContent(xbin,ybin,dm->GetBinContent(xbin,ybin));

			CR_ambe->SetBinError(xbin,ybin,ambe->GetBinError(xbin,ybin));
			CR_co60->SetBinError(xbin,ybin,co60->GetBinError(xbin,ybin));
			CR_th232->SetBinError(xbin,ybin,th232->GetBinError(xbin,ybin));
			CR_dm->SetBinError(xbin,ybin,dm->GetBinError(xbin,ybin));
		}
	}
 }
 	

 // signal region rebinning
TH1D*  co60_PL_SR_reb = new TH1D("co60_PL_SR_reb","",9,0.5,9.5);
TH1D*  th232_PL_SR_reb = new TH1D("th232_PL_SR_reb","",9,0.5,9.5);
TH1D*  dm_PL_SR_reb = new TH1D("dm_PL_SR_reb","",9,0.5,9.5);


 int bin_serie[6] = {1,2,4,5,6};

 for (int b = 0; b < 5; b++) {

	int bin = bin_serie[b];
 	co60_PL_SR_reb->SetBinContent(b+1, co60_PL_SR->GetBinContent(bin));
	co60_PL_SR_reb->SetBinError(b+1, co60_PL_SR->GetBinError(bin));

 	th232_PL_SR_reb->SetBinContent(b+1, th232_PL_SR->GetBinContent(bin));
	th232_PL_SR_reb->SetBinError(b+1, th232_PL_SR->GetBinError(bin));

	dm_PL_SR_reb->SetBinContent(b+1, dm_PL_SR->GetBinContent(bin));
	dm_PL_SR_reb->SetBinError(b+1, dm_PL_SR->GetBinError(bin));
 }

 double bin_11_dm = dm_PL_SR->GetBinContent(11) + dm_PL_SR->GetBinContent(15);
 dm_PL_SR_reb->SetBinContent(8, bin_11_dm);
 dm_PL_SR_reb->SetBinError(8, sqrt(bin_11_dm) );

 double bin_11_co = co60_PL_SR->GetBinContent(11) + co60_PL_SR->GetBinContent(15);
 co60_PL_SR_reb->SetBinContent(8, bin_11_co);
 co60_PL_SR_reb->SetBinError(8, sqrt(bin_11_co) );

 double bin_11_th = th232_PL_SR->GetBinContent(11) + th232_PL_SR->GetBinContent(15);
 th232_PL_SR_reb->SetBinContent(8, bin_11_th);
 th232_PL_SR_reb->SetBinError(8, sqrt(bin_11_th) );

 double bin_10_co = co60_PL_SR->GetBinContent(10) + co60_PL_SR->GetBinContent(9);
 co60_PL_SR_reb->SetBinContent(6, bin_10_co);
 co60_PL_SR_reb->SetBinError(6, sqrt(bin_10_co) );

 double bin_10_th = th232_PL_SR->GetBinContent(10) + th232_PL_SR->GetBinContent(9);
 th232_PL_SR_reb->SetBinContent(6, bin_10_th);
 th232_PL_SR_reb->SetBinError(6, sqrt(bin_10_th) );

 double bin_10_dm = dm_PL_SR->GetBinContent(10) + dm_PL_SR->GetBinContent(9);
 dm_PL_SR_reb->SetBinContent(6, bin_10_dm);
 dm_PL_SR_reb->SetBinError(6, sqrt(bin_10_dm) );
   
 double bin_3_co = co60_PL_SR->GetBinContent(3) + co60_PL_SR->GetBinContent(7);
 co60_PL_SR_reb->SetBinContent(7, bin_3_co);
 co60_PL_SR_reb->SetBinError(7, sqrt(bin_3_co) );
 
 double bin_3_th = th232_PL_SR->GetBinContent(3) + th232_PL_SR->GetBinContent(7);
 th232_PL_SR_reb->SetBinContent(7, bin_3_th);
 th232_PL_SR_reb->SetBinError(7, sqrt(bin_3_th) );

 double bin_8_co = co60_PL_SR->GetBinContent(8) + co60_PL_SR->GetBinContent(12) + co60_PL_SR->GetBinContent(13) + co60_PL_SR->GetBinContent(14) + co60_PL_SR->GetBinContent(16);
 co60_PL_SR_reb->SetBinContent(9, bin_8_co);
 co60_PL_SR_reb->SetBinError(9, sqrt(bin_8_co) );
 
 double bin_8_th = th232_PL_SR->GetBinContent(8) + th232_PL_SR->GetBinContent(12) + th232_PL_SR->GetBinContent(13) + th232_PL_SR->GetBinContent(14) + th232_PL_SR->GetBinContent(16);
 th232_PL_SR_reb->SetBinContent(9, bin_8_th);
 th232_PL_SR_reb->SetBinError(9, sqrt(bin_8_th) );

 double bin_3_dm = dm_PL_SR->GetBinContent(3) + dm_PL_SR->GetBinContent(7);
 dm_PL_SR_reb->SetBinContent(7, bin_3_dm);
 dm_PL_SR_reb->SetBinError(7, sqrt(bin_3_dm) );
 

 double bin_8_dm = dm_PL_SR->GetBinContent(8) + dm_PL_SR->GetBinContent(12) + dm_PL_SR->GetBinContent(13) + dm_PL_SR->GetBinContent(14) + dm_PL_SR->GetBinContent(16);
 dm_PL_SR_reb->SetBinContent(9, bin_8_dm);
 dm_PL_SR_reb->SetBinError(9, sqrt(bin_8_dm) );


 TFile signal_region("SR_CR_file.root","RECREATE");

 dm_PL_SR_reb->Write();
 co60_PL_SR_reb->Write();
 th232_PL_SR_reb->Write();

 ambe_PL_SR->Write();
 co60_PL_SR->Write();
 th232_PL_SR->Write();
 dm_PL_SR->Write();

 CR_ambe->Write();
 CR_co60->Write();
 CR_th232->Write();
 CR_dm->Write();


 signal_region.Close();
 

}





