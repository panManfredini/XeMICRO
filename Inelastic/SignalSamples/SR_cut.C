TH1D SR_cut(TH2D *input_histo){

 int bincounter = 1; 

 TH1D input_histo_PL_SR ("temp_PL_SR_"+((TString)input_histo->GetName()),"",16,0.5,16.5);

 for(int xbin=1; xbin <= input_histo->GetNbinsX(); xbin++) {
 	for(int ybin=1; ybin <= input_histo->GetNbinsY(); ybin++) {

		double s1 = input_histo->GetXaxis()->GetBinCenter(xbin);
		double s2 = input_histo->GetYaxis()->GetBinCenter(ybin);

		//inside SR
		if(s1 > 60. && s1 < 210. && s2 >6000. && s2 < 14000.){
			
			if(s1 <100. && s2 < 8000. ) 	continue;
			
			if(s1 >180. && s2 > 12000.)	continue;

			if(s1 >180. && s2 < 12000.) {
				input_histo_PL_SR.AddBinContent(16,input_histo->GetBinContent(xbin,ybin));
				double err = sqrt(pow(input_histo_PL_SR.GetBinError(16),2) + pow(input_histo->GetBinError(xbin,ybin),2)) ;
				input_histo_PL_SR.SetBinError(16, err);
			}
			else{
				input_histo_PL_SR.SetBinContent(bincounter,input_histo->GetBinContent(xbin,ybin));
				input_histo_PL_SR.SetBinError(bincounter, input_histo->GetBinError(xbin,ybin));
				cout << " Rel err " << input_histo_PL_SR.GetBinError(bincounter)/ input_histo_PL_SR.GetBinContent(bincounter) << endl;
				bincounter++;	
			}
			
		}
	}
 }

TH1D  input_PL_SR_reb("PL_SR_"+((TString)input_histo->GetName()),"",9,0.5,9.5);

 int bin_serie[6] = {1,2,4,5,6};

 for (int b = 0; b < 5; b++) {

        int bin = bin_serie[b];
        input_PL_SR_reb.SetBinContent(b+1, input_histo_PL_SR.GetBinContent(bin));
        input_PL_SR_reb.SetBinError(b+1, input_histo_PL_SR.GetBinError(bin));

 }


 double bin_11_co = input_histo_PL_SR.GetBinContent(11) + input_histo_PL_SR.GetBinContent(15);
 double bin_11_err = pow(input_histo_PL_SR.GetBinError(11),2.) + pow(input_histo_PL_SR.GetBinError(15),2.);
 input_PL_SR_reb.SetBinContent(8, bin_11_co);
 input_PL_SR_reb.SetBinError(8, sqrt(bin_11_err) );

 double bin_10_co = input_histo_PL_SR.GetBinContent(10) + input_histo_PL_SR.GetBinContent(9);
 double bin_10_err = pow(input_histo_PL_SR.GetBinError(10),2.) + pow(input_histo_PL_SR.GetBinError(9),2.);
 input_PL_SR_reb.SetBinContent(6, bin_10_co);
 input_PL_SR_reb.SetBinError(6, sqrt(bin_10_err) );


 double bin_3_co = input_histo_PL_SR.GetBinContent(3) + input_histo_PL_SR.GetBinContent(7);
 double bin_3_err = pow(input_histo_PL_SR.GetBinError(3),2.) + pow(input_histo_PL_SR.GetBinError(7),2.);
 input_PL_SR_reb.SetBinContent(7, bin_3_co);
 input_PL_SR_reb.SetBinError(7, sqrt(bin_3_err) );


 double bin_8_co =  input_histo_PL_SR.GetBinContent(8) + input_histo_PL_SR.GetBinContent(12) + input_histo_PL_SR.GetBinContent(13) + input_histo_PL_SR.GetBinContent(14) + input_histo_PL_SR.GetBinContent(16);
 double bin_8_err = pow(input_histo_PL_SR.GetBinError(8),2.) + pow(input_histo_PL_SR.GetBinError(12),2) + pow(input_histo_PL_SR.GetBinError(13),2) + pow(input_histo_PL_SR.GetBinError(14),2) +pow( input_histo_PL_SR.GetBinError(16),2);
 input_PL_SR_reb.SetBinContent(9, bin_8_co);
 input_PL_SR_reb.SetBinError(9, sqrt(bin_8_err) );





 return input_PL_SR_reb;



}
