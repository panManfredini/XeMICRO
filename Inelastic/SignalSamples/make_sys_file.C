{


  std::vector <TString> mass_list;
  	mass_list.push_back(TString::TString("20"));
  	mass_list.push_back(TString::TString("30"));
  	mass_list.push_back(TString::TString("40"));
  	mass_list.push_back(TString::TString("50"));
  	mass_list.push_back(TString::TString("60"));
  	mass_list.push_back(TString::TString("70"));
  	mass_list.push_back(TString::TString("80"));
  	mass_list.push_back(TString::TString("90"));
 	mass_list.push_back(TString::TString("100"));
  	mass_list.push_back(TString::TString("200"));
  	mass_list.push_back(TString::TString("300"));
  	mass_list.push_back(TString::TString("400"));
  	mass_list.push_back(TString::TString("500"));
  	mass_list.push_back(TString::TString("700"));
  	mass_list.push_back(TString::TString("1000"));
  	mass_list.push_back(TString::TString("2000"));
  	mass_list.push_back(TString::TString("3000"));
  	mass_list.push_back(TString::TString("5000"));

  std::vector <TString> sys_list;
  	sys_list.push_back(TString::TString("_p_LY"));
  	sys_list.push_back(TString::TString("_p_Y"));
  	sys_list.push_back(TString::TString("_p_rho"));
  	sys_list.push_back(TString::TString("_p_leff"));
  	sys_list.push_back(TString::TString("_p_qy"));
  	sys_list.push_back(TString::TString("_m_LY"));
  	sys_list.push_back(TString::TString("_m_Y"));
  	sys_list.push_back(TString::TString("_m_rho"));
  	sys_list.push_back(TString::TString("_m_leff"));
  	sys_list.push_back(TString::TString("_m_qy"));

  TFile *f = TFile::Open("final_signals_Ybott_rho04.root");
  //TFile *f = TFile::Open("final_signals_test.root");

  TFile *out = new TFile("final_signals_with_sys_reb_rho04.root","RECREATE");
  //TFile *out = new TFile("final_signals_with_sys_reb.root","RECREATE");

  TH1D *stand;
  TH1D *sys;


  // separates the uncertainty for each sys in up and down fluctuation, sum the square separately for up and down, thake average of up and down
  for(unsigned int m=0; m< mass_list.size() ; m++){

	TString mass_name(mass_list[m]);

        cout << "----------- --------------------  Mass   " << mass_name << endl;

	stand = (TH1D*)f->Get("PL_SR_s1s2_mass_"+mass_name);

        TH1D *sys_p = (TH1D*)stand->Clone("sys_up_"+mass_name);
        TH1D *sys_d = (TH1D*)stand->Clone("sys_down_"+mass_name);

  	for(unsigned int s=0; s< sys_list.size() ; s++){
          TString sys_name(sys_list[s]);
	  cout << sys_name << " -------------- " << endl;

	  sys = (TH1D*) f->Get("PL_SR_s1s2_mass_"+mass_name+sys_name);
	  cout << (sys->Integral() - stand->Integral() ) / stand->Integral() << endl;

	  double avg_up = 0.;
	  double count_up =0;
	  double count_down =0;
	  double avg_down = 0.;
	  for(int i=1 ; i <= sys->GetNbinsX(); i++) {

		if( !(stand->GetBinContent(i) > 0. )) continue;

		double residual = sys->GetBinContent(i) - stand->GetBinContent(i);
			
		if(residual> 0.) { 
			double err = sqrt( pow(sys_p->GetBinError(i),2) + pow(residual,2) );
			sys_p->SetBinError(i, err) ;
			avg_up += residual / stand->GetBinContent(i);
			count_up++;
		}
		else if(residual< 0.) { 
			double err = sqrt( pow(sys_d->GetBinError(i),2) + pow(residual,2) );
			sys_d->SetBinError(i, err) ;
			avg_down += residual / stand->GetBinContent(i);
			count_down++;
		}
	  }
	  cout << "avg_up  " << avg_up / count_up << "    avg dwn " << avg_down / count_down  << " \t AVG "<< sys_name << "  " << (avg_up / count_up - avg_down / count_down ) / 2. * 100.<< endl;
	
	}

	
        TH1D *sys_final = (TH1D*)stand->Clone("PL_SR_s1s2_mass_"+mass_name+"_sys");
	  for(int i=1 ; i <= stand->GetNbinsX(); i++) sys_final->SetBinError(i, ( sys_p->GetBinError(i) + sys_d->GetBinError(i))/2.);
	out->cd();
	sys_final->Write();
  }

  out->Close();
  f->Close();

}
