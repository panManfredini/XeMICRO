void setInelasticStyle(double factor =1){

	TStyle *inel =  (TStyle*) gStyle; //new TStyle("inel","style for inelastic");

	inel->SetLabelFont(132,"XYZ");
	inel->SetLabelSize(0.05/factor,"XYZ");
	inel->SetTitleSize(0.05/factor,"XYZ");
	inel->SetTitleFont(132,"XYZ");
	inel->SetTitleOffset(1.2,"XYZ");
	inel->SetOptStat(0);
	inel->SetTitleFont(132);

	inel->cd();
	gROOT->ForceStyle();

//	gStyle->SetStyle(
//	gROOT->SetStyle()





}
