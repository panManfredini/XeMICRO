#include "../Tools/ratio_plot.C"

void plot_sys(double mass){

//	gROOT->ProcessLine(".L ../Tools/ratio_plot.C"); 



	TString name_mass(TString::Itoa((int)mass,10));

	TFile *f = TFile::Open("final_signals_test.root");


	std::vector <TString> sys_list;
	sys_list.push_back(TString::TString("LY"));
	sys_list.push_back(TString::TString("Y"));
	sys_list.push_back(TString::TString("rho"));
	sys_list.push_back(TString::TString("leff"));
	sys_list.push_back(TString::TString("qy"));


	TH1D *std = (TH1D*)f->Get("PL_SR_s1s2_mass_"+name_mass);
	std->SetTitle("Standard");

	for(unsigned int i =0; i < sys_list.size(); i++){

		TH1D *p = (TH1D*)f->Get("PL_SR_s1s2_mass_"+name_mass+"_p_"+sys_list[i]);
		TH1D *m = (TH1D*)f->Get("PL_SR_s1s2_mass_"+name_mass+"_m_"+sys_list[i]);
	
		p->SetTitle(sys_list[i]+" plus  1#sigma");
		m->SetTitle(sys_list[i]+" minus 1#sigma");
		TCanvas *c = ratio_plot(std,p,"Systematic variation of "+sys_list[i],m);
	}

}
