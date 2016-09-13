void apply_acc(TH2D *inputHist) {

  TFile f_acc("../acceptace_computation/acceptance.root");

  inputHist->Rebin2D(30,20);


  TH2D *acc_map = (TH2D*) f_acc.Get("total_acceptance");


  for(int x =1; x < inputHist->GetXaxis()->GetNbins(); x++){

	double x_center  = inputHist->GetXaxis()->GetBinCenter(x);

	for(int y =1; y < inputHist->GetYaxis()->GetNbins(); y++){

		double y_center  = inputHist->GetYaxis()->GetBinCenter(y);

		double acc = acc_map->GetBinContent(acc_map->GetXaxis()->FindBin(x_center), acc_map->GetYaxis()->FindBin(y_center) );

		
		double content = inputHist->GetBinContent(x,y);
		double err     = inputHist->GetBinError(x,y);

		if(!(acc > 0.) || !(content > 0.) ) continue;
		
		inputHist->SetBinContent(x,y, content* acc);
		
		inputHist->SetBinError(x,y, err * acc);
		
	//	cout << "Rel errors bin " << x_center << " " << y_center << "   ---   " << inputHist->GetBinError(x,y) / inputHist->GetBinContent(x,y) << "   " << err  << " pp " << content<< endl;	
		 
	}
	
  }

	       inputHist->Sumw2();
}


