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

  TFile finallySignals("final_signals_LeffP1s.root","RECREATE");

  for(unsigned int m=0; m< mass_list.size() ; m++){

	TString porcamadonna(mass_list[m]);
	TH2D *mass_100 = smearing(porcamadonna);

	cout << "Mass " + mass_list[m] + " Before Acc "<< mass_100->Integral() << endl;
	apply_acc(mass_100); 
	cout <<"Mass " + mass_list[m] + " After Acc " << mass_100->Integral() << endl;

//	mass_100->Draw("colz");

	TH1D SR_mass100 (SR_cut(mass_100));

	cout <<"Mass " + mass_list[m] + " AFTER SR  " << SR_mass100.Integral() << endl;

	finallySignals.cd();
	SR_mass100.Write(TString(SR_mass100.GetName()) + "_LeffP1s");
//	new TCanvas();
//	SR_mass100.Draw();
  }
  
  finallySignals.Close();
}
