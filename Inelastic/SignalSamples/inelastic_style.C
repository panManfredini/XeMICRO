void setInelasticStyle(){

	TStyle *inel =  (TStyle*) gStyle; //new TStyle("inel","style for inelastic");

	inel->SetLabelFont(22,"XYZ");
	inel->SetLabelSize(0.05,"XYZ");
	inel->SetTitleSize(0.05,"XYZ");
	inel->SetTitleFont(22,"XYZ");
	inel->SetTitleOffset(1.2,"XYZ");
	inel->SetOptStat(0);

	inel->cd();
	gROOT->ForceStyle();

//	gStyle->SetStyle(
//	gROOT->SetStyle()





}
