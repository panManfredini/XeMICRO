{

 ifstream in;
 in.open("mod_rcl_nr_more.dat");

 double temp =0.;

 double aboundanceXe129 = 0.2644;  // the x scetion consider only the target, the Xsec in production is 10-40 per Kg per KeV

 TFile f("signalFile.root", "RECREATE");

 TH1F *h_temp;

 while(in.good()){

 	double integral =0;

	in >> temp;

        char bla[10];
	sprintf(bla,"%1.0f",temp);

	TString name("dRdE_mass_");
	name.Append(bla);

	h_temp = new TH1F(name,"",300,0,300);

	cout << "running on mass " << temp << endl;

 	for(int i=0; i<299; i++){
		in >> temp;
		integral += temp;

		h_temp->SetBinContent(i+1,temp);

//		cout << temp << endl;
 	}
  

  	cout << name + "Integral " << integral << "  VS  " << h_temp->Integral() << endl;

	h_temp->Scale(aboundanceXe129);	

  	cout << name + "Rate with abundance " << integral * aboundanceXe129 << "   VS " << h_temp->Integral()<< endl;

	f.cd();
	h_temp->Write();

 }
 
f.Close();
}
