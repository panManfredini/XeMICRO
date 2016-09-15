{

  TFile *f = TFile::Open("../DATA/final_merge.root");

  TH2D *ambe = (TH2D*)f->Get("s1_s2_AmBe");
  TH2D *co60 = (TH2D*)f->Get("s1_s2_Co60");
  TH2D *dm = (TH2D*)f->Get("s1_s2_DM");

  TH2D *ambe_l = (TH2D*)f->Get("log_s2_s1_SR_AmBe");
  TH2D *co60_l = (TH2D*)f->Get("log_s2_s1_SR_Co60");
  TH2D *dm_l = (TH2D*)f->Get("log_s2_s1_SR_DM");

  cout << ambe->GetNbinsX() << endl; 
  cout << ambe->GetNbinsY() << endl; 
  ambe->Rebin2D(30,20);
  co60->Rebin2D(30,20);
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
  co60->Draw("colz");

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
 TH1F *dm_PL_SR =   new TH1F("dm_PL_SR","",16,0.5,16.5);

 TH2D *CR_ambe  = (TH2D*) ambe->Clone("CR_ambe");
 CR_ambe->Reset();
 TH2D *CR_co60  = (TH2D*) ambe->Clone("CR_co60");
 CR_co60->Reset();
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
				CR_dm->SetBinContent(xbin,ybin,dm->GetBinContent(xbin,ybin));

				CR_ambe->SetBinError(xbin,ybin,ambe->GetBinError(xbin,ybin));
				CR_co60->SetBinError(xbin,ybin,co60->GetBinError(xbin,ybin));
				CR_dm->SetBinError(xbin,ybin,dm->GetBinError(xbin,ybin));

				continue;
			}
			if(s1 >180. && s2 > 12000.) {
				CR_ambe->SetBinContent(xbin,ybin,ambe->GetBinContent(xbin,ybin));
				CR_co60->SetBinContent(xbin,ybin,co60->GetBinContent(xbin,ybin));
				CR_dm->SetBinContent(xbin,ybin,dm->GetBinContent(xbin,ybin));

				CR_ambe->SetBinError(xbin,ybin,ambe->GetBinError(xbin,ybin));
				CR_co60->SetBinError(xbin,ybin,co60->GetBinError(xbin,ybin));
				CR_dm->SetBinError(xbin,ybin,dm->GetBinError(xbin,ybin));
				continue;
			}

			if(s1 >180. && s2 < 12000.) {
				ambe_PL_SR->AddBinContent(16,ambe->GetBinContent(xbin,ybin));
				co60_PL_SR->AddBinContent(16,co60->GetBinContent(xbin,ybin));
				dm_PL_SR->AddBinContent(16,dm->GetBinContent(xbin,ybin));

				double err_dm = sqrt(pow(dm_PL_SR->GetBinError(16),2) + pow(dm->GetBinError(xbin,ybin),2)) ;
				double err_ambe = sqrt(pow(ambe_PL_SR->GetBinError(16),2) + pow(ambe->GetBinError(xbin,ybin),2)) ;
				double err_co = sqrt(pow(co60_PL_SR->GetBinError(16),2) + pow(co60->GetBinError(xbin,ybin),2)) ;
				ambe_PL_SR->SetBinError(16,err_ambe);
				dm_PL_SR->SetBinError(16,err_dm);
				co60_PL_SR->SetBinError(16,err_co);
			}
			else{
				ambe_PL_SR->SetBinContent(bincounter,ambe->GetBinContent(xbin,ybin));
				co60_PL_SR->SetBinContent(bincounter,co60->GetBinContent(xbin,ybin));
				dm_PL_SR->SetBinContent(bincounter,dm->GetBinContent(xbin,ybin));

				ambe_PL_SR->SetBinError(bincounter,ambe->GetBinError(xbin,ybin));
				co60_PL_SR->SetBinError(bincounter,co60->GetBinError(xbin,ybin));
				dm_PL_SR->SetBinError(bincounter,dm->GetBinError(xbin,ybin));
		
				bincounter++;	
			}
			
		}
		else{
			
			CR_ambe->SetBinContent(xbin,ybin,ambe->GetBinContent(xbin,ybin));
			CR_co60->SetBinContent(xbin,ybin,co60->GetBinContent(xbin,ybin));
			CR_dm->SetBinContent(xbin,ybin,dm->GetBinContent(xbin,ybin));

			CR_ambe->SetBinError(xbin,ybin,ambe->GetBinError(xbin,ybin));
			CR_co60->SetBinError(xbin,ybin,co60->GetBinError(xbin,ybin));
			CR_dm->SetBinError(xbin,ybin,dm->GetBinError(xbin,ybin));
		}
	}
 }
 	

 TFile signal_region("SR_CR_file.root","RECREATE");

 ambe_PL_SR->Write();
 co60_PL_SR->Write();
 dm_PL_SR->Write();

 CR_ambe->Write();
 CR_co60->Write();
 CR_dm->Write();


 signal_region.Close();
 

}





