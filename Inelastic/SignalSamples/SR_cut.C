TH1D SR_cut(TH2D *input_histo){

 int bincounter = 1; 

 TH1D input_histo_PL_SR ("PL_SR_"+((TString)input_histo->GetName()),"",16,0.5,16.5);

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


 return input_histo_PL_SR;



}
