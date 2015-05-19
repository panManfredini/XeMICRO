{

TFile *f = TFile::Open("merge_34kg_full.root");
//TFile *f = TFile::Open("merge_34kg.root");

TH2D *co60 = (TH2D*) f->Get("log_s2_s1_Rot_Co60");
TH2D *ambe = (TH2D*) f->Get("log_s2_s1_Rot_AmBe");
TH2D *th232 = (TH2D*) f->Get("log_s2_s1_Rot_Th232");
TH2D *cs137 = (TH2D*) f->Get("log_s2_s1_Rot_Cs137");
TH2D *DM = (TH2D*) f->Get("log_s2_s1_Rot_DM");

TH1F *livetime = (TH1F*) f->Get("livetime_DM");

co60->Rebin2D(20,25);  // 50 bins X and 40 in Y
ambe->Rebin2D(20,25);
th232->Rebin2D(20,25);
cs137->Rebin2D(20,25);
DM->Rebin2D(20,25);

TH1D *ambe_SR = new TH1D("ambe_SR","",40,0.5,40.5);
TH1D *co60_SR = new TH1D("co60_SR","",40,0.5,40.5);
TH1D *th232_SR = new TH1D("th232_SR","",40,0.5,40.5);
TH1D *cs137_SR = new TH1D("cs137_SR","",40,0.5,40.5);
TH1D *DM_SR = new TH1D("DM_SR","",40,0.5,40.5);

//--- just for test -----//
TH1D *DM_SR_flat = new TH1D("DM_SR_flat","",40,0.5,40.5);
TH1D *co60_SR_flat = new TH1D("co60_SR_flat","",40,0.5,40.5);
TH1D *ambe_SR_flat = new TH1D("ambe_SR_flat","",40,0.5,40.5);
//---------------------//


int counter = 1;

double CR_DM        =  0;
double CR_Co60 	    =  0;
double CR_AmBe 	    =  0;
double tot_Co60_SR  =  0;
double tot_AmBe_SR  =  0;
double tot_DM_SR  =  0;


for(int y=1; y <= co60->GetNbinsY(); y++)
	{
	  for(int x=1; x <= co60->GetNbinsX(); x++)
		{
		  double X_center =  co60->GetXaxis()->GetBinCenter(x);
		  double Y_center =  co60->GetYaxis()->GetBinCenter(y);

		  if(X_center < 160. && X_center > 60. && Y_center < 2.7 && Y_center > 2.3)  // Signal Region 
			{
			  ambe_SR->SetBinContent(counter, ambe->GetBinContent(x,y));
			  co60_SR->SetBinContent(counter, co60->GetBinContent(x,y));
			  th232_SR->SetBinContent(counter, th232->GetBinContent(x,y));
			  cs137_SR->SetBinContent(counter, cs137->GetBinContent(x,y));
			  DM_SR->SetBinContent(counter, DM->GetBinContent(x,y));

			  tot_Co60_SR +=  co60->GetBinContent(x,y);	
			  tot_AmBe_SR +=  ambe->GetBinContent(x,y);
			  tot_DM_SR += DM->GetBinContent(x,y);

			  counter++;

			} 
		  else if(X_center > 60. && X_center < 230. && Y_center > 2.7 && Y_center < 3.4)  // Control Region 
			{
			  CR_DM   += DM->GetBinContent(x,y) ;
			  CR_Co60 += co60->GetBinContent(x,y) ;
			  CR_AmBe += ambe->GetBinContent(x,y) ;
			}
		
		}
	}

if(counter >40) cout << "warning " << counter << endl;


//---- just for test-------------//
for(int k=1; k<= 40; k++) {
	ambe_SR_flat->SetBinContent( k, tot_AmBe_SR / 40.);
	ambe_SR_flat->SetBinError(k, sqrt(tot_AmBe_SR / 40.));

	co60_SR_flat->SetBinContent( k, tot_Co60_SR / 40.);
	co60_SR_flat->SetBinError(k, sqrt(tot_Co60_SR / 40.));
	
	DM_SR_flat->SetBinContent( k, tot_DM_SR / 40.);
	DM_SR_flat->SetBinError(k, sqrt(tot_DM_SR / 40.));
	
}
//------------------------------//

cout << "----------- GLOBAL VARIABLES ------ " << endl;
cout << "Events in CR data  " << CR_DM   << endl;
cout << "Events in CR Co60  " << CR_Co60 << endl;
cout << "Events in CR AmBe  " << CR_AmBe << endl;
cout << "Norm Factor        " << CR_DM / CR_Co60  << "  +-  "  << CR_DM / CR_Co60 * sqrt(1./CR_DM + 1./CR_Co60)  <<"  (rel in % = " <<  sqrt(1./CR_DM + 1./CR_Co60) *100. << " )" << endl;
cout << "Events in SR Co60  " << tot_Co60_SR <<  endl;
cout << "Events in SR AmBe  " << tot_AmBe_SR <<  endl;
cout << "Events in TOTAL for AmBe  " << ambe->Integral() <<  endl;
cout << "Events in TOTAL for Co60  " << co60->Integral() <<  endl;
cout << "Events in TOTAL for DATA  " << DM->Integral() <<  endl;
cout << "TOTAL integrated livetime " << livetime->Integral() << " days"<<  endl;



/*
ambe_SR->Scale(1./ambe_SR->Integral());
co60_SR->Scale(1./co60_SR->Integral());
ambe_SR->Draw();
co60_SR->Draw("same");
*/

TFile *h_for_limits = new TFile("h_for_limits.root","RECREATE");

h_for_limits->cd();

ambe_SR->Write();
co60_SR->Write();
th232_SR->Write();
cs137_SR->Write();
DM_SR->Write();

DM_SR_flat->Write();
ambe_SR_flat->Write();
co60_SR_flat->Write();

h_for_limits->Close();



}
