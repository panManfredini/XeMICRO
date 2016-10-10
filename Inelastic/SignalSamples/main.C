{

  gROOT->ProcessLine(".L smearing.cxx");

  gROOT->ProcessLine(".L apply_acc.C");

  gROOT->ProcessLine(".L SR_cut.C");

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

  std::vector <double*> sys_list;
	double s0[5] = {0.,0.,0.,0.,0.};
        sys_list.push_back(s0);
	double su1[5] = {1.,0.,0.,0.,0.};
        sys_list.push_back(su1);
	double su2[5] = {0.,1.,0.,0.,0.};
        sys_list.push_back(su2);
	double su3[5] = {0.,0.,1.,0.,0.};
        sys_list.push_back(su3);
	double su4[5] = {0.,0.,0.,1.,0.};
        sys_list.push_back(su4);
	double su5[5] = {0.,0.,0.,0.,1.};
        sys_list.push_back(su5);

	double sd1[5] = {-1.,0.,0.,0.,0.};
        sys_list.push_back(sd1);
	double sd2[5] = {0.,-1.,0.,0.,0.};
        sys_list.push_back(sd2);
	double sd3[5] = {0.,0.,-1.,0.,0.};
        sys_list.push_back(sd3);
	double sd4[5] = {0.,0.,0.,-1.,0.};
        sys_list.push_back(sd4);
	double sd5[5] = {0.,0.,0.,0.,-1.};
        sys_list.push_back(sd5);
 

  TFile finallySignals("final_signals_test.root","RECREATE");

  for(unsigned int m=0; m< mass_list.size() ; m++){
  	for(unsigned int s=0; s< sys_list.size() ; s++){

	double a1 = sys_list[s][0];
	double a2 = sys_list[s][1];
	double a3 = sys_list[s][2];
	double a4 = sys_list[s][3];
	double a5 = sys_list[s][4];

	TString porcamadonna(mass_list[m]);
	TH2D *mass_100 = smearing(porcamadonna, a1, a2, a3, a4, a5); 

	cout << "Mass " + mass_list[m] + " Before Acc "<< mass_100->Integral() << endl;
	apply_acc(mass_100); 
	cout <<"Mass " + mass_list[m] + " After Acc " << mass_100->Integral() << endl;

//	mass_100->Draw("colz");

	TH1D SR_mass100 (SR_cut(mass_100));

	cout <<"Mass " + mass_list[m] + " AFTER SR  " << SR_mass100.Integral() << endl;

	finallySignals.cd();
	SR_mass100.Write(TString(SR_mass100.GetName()));
//	new TCanvas();
//	SR_mass100.Draw();
      }
  }
  
  finallySignals.Close();
}
