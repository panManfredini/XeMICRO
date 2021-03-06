#include <iostream>
#include <cmath>

//underflow and overflow of gaussian smearing not corrected deliberately
//If the code goes wrong, it is probably because L_eff is smaller than zero for low energy. start interation from i = 2 instead in the main loop

#define sigma_pmt (0.5)
//#define NAME "qy_onesigma_lower"

//parameters extracted from wiki Inelastic WIMP Scattering » Count based analysis » Signal region

//nuclear recoil light emission
const float l_y = 2.2;
const float s_nr = 0.95;
const float s_ee = 0.58;

//charge emission
const float y = 19.5;
const float r = 0.4195;


//40kev gamma parameters
//double const rho = -0.75;
double const rho = -0.50;
double const mux = 107.0;
double const muy = 8924.0;
double const sigmax = 17.0;
double const sigmay = 1312.0;


//Qy and Leff: two Tgraphs read from inputparameter.root
//redirect these two pointers to reasssign Qy and Leff
TGraph *gQy;
TGraph *gLeff;
TGraph *gmedian,*glower,*gupper;

double poisson(double k, double lambda);
double gaussian(double x, double mu, double sigma);
double gaussiancdf(double x, double mu, double sigma);
double bigaus(double x, double y, double rho, double mux, double muy, double sigmax, double sigmay);
void ra();
double rx,ry, rax, ray;



//declare the histograms used to store the results
int cs1bin = 300;	
int cs2bin = 30;
TH1F *h2 = new TH1F("h2", "smeared dR/dcS1", cs1bin,0,300);
TH1F *h3 = new TH1F("h3", "smeared dR/dcS2", cs2bin,0,3000);
int xbinm=200;
int ybinm=200;
TH2D *hcorr = new TH2D("hcorr", "40 KeV gamma", xbinm,0,500,ybinm,0,40000);
TH2D *hcomb = new TH2D("hcomb", "Combined 40keV gamma and nuclear recoil", xbinm,0,500,ybinm,0,40000);

void comp(string name);

void smearing(){

	//read the result of monte carlo simulation of nuclear recoil
	TFile *f = new TFile("hNrgPureSingleNrInel40keV-4M.root");
	TH1F *h1;	
	f->GetObject("hNrgPureSingleNrInel40keV;1",h1);
	h1->SetName("h1");
	h1->Rebin();


/*
//	smearing test input
	h1 = new TH1F("h1", "testing input", 150,0,300);
	h1->SetBinContent(5,20);
	h1->SetBinContent(50,20);
	h1->SetBinContent(95,20);
	h1->SetBinContent(140,20);
*/



	//read Qy and Leff
	TFile *f2 = new TFile("inputParameters.root");
	f2->GetObject("gQy;1",gQy);
	f2->GetObject("gLeff;1",gLeff);
	
	TCanvas *c1 = new TCanvas("Canvas", "Canvas", 1500,500);
	c1->Divide(3,2);

	h1->SetTitle("Simulated dR/dE - Nuclear Recoil Inelastic");
	h1->SetXTitle("E/keV");
	h1->SetYTitle("dR/dE");
	c1->cd(1); h1->Draw();


	h2->SetXTitle("cS1/PE");
	h2->SetYTitle("dR/dcS1");
	h3->SetXTitle("cS2/PE");
	h3->SetYTitle("dR/dcS2");
	hcorr->SetXTitle("cS1/PE");
	hcorr->SetYTitle("cS2/PE");
	hcomb->SetXTitle("cS1/PE");
	hcomb->SetYTitle("cS2/PE");


	int maxpe = 300;	//max no. of PE allowd in smearing - defines range of discrete poisson
	int gaussianbins = 300;	//no. of bins in pdf for smearing

	TH1F *h4 = new TH1F("h4", "p_cS1", gaussianbins, 0 , 300);
	h4->SetXTitle("cS1");
	h4->SetYTitle("Probability");

	
	for (int i = 1; i <= 150; i++){//loop over every bin in h1, smear and add
		double energy = h1->GetBinCenter(i);
		double drde = h1->GetBinContent(i);
		cout << "-energy:" << energy << endl;
		cout << "drde:" << drde << endl;

		double mu_ny = energy * l_y * gLeff->Eval(energy) * s_nr / s_ee;
		double meanS2 = energy * y * r * gQy->Eval(energy);
		cout << "mu_ny=" << mu_ny << " meanS2:" << meanS2 << endl;

		h4->Reset();//clear previous smearing pdf



	//create pde for this mu_ny, stored in h4
		for (int j = 1; j <= maxpe; j++){
			double probabnpe = TMath::PoissonI(j-1, mu_ny);
			//probability to get j no. of PE
			if (j == 1){
				continue; //ignore 0 Npe bin in poisson
			}
			double gmean = j-1;
			double gsd = sqrt(gmean) * sigma_pmt;	//s.d. of gaussian
//			double scale = 1.0/ (1.0 - gaussiancdf(0.0, gmean, gvar)); // correction for underflow leakage
			for (int k = 1; k <= gaussianbins; k++){
				h4->AddBinContent(k, probabnpe * (ROOT::Math::normal_cdf(h4->GetBinLowEdge(k) + h4->GetBinWidth(k), gsd, gmean) - ROOT::Math::normal_cdf(h4->GetBinLowEdge(k), gsd, gmean)));
			}			
	
		}

		c1->cd(6); h4->Draw();

//fill h2 results for cs1 smearing
		for (int l = 1; l <= cs1bin; l++){
			float n = h2->GetEntries();
			float entry = drde*(h4->GetBinContent(h4->GetXaxis()->FindBin(h2->GetBinCenter(l))));
			h2->AddBinContent(l, entry);
			h2->SetEntries(n + entry);
		}


//fill h3 results for cs2 smearing
		for (int m = 1; m <= cs2bin; m++){
			float n = h3->GetEntries();
			float entry = drde*(ROOT::Math::normal_cdf(h3->GetBinLowEdge(m) + h3->GetBinWidth(m), sqrt(1.25 * meanS2), meanS2) - ROOT::Math::normal_cdf(h3->GetBinLowEdge(m), sqrt(1.25 * meanS2), meanS2));
			h3->AddBinContent(m, entry);
			h3->SetEntries(n + entry);
		}

	}


c1->cd(2); h2->Draw();
c1->cd(3); h3->Draw("hist");

	//fill in 40KeV gamma ellipse to hcorr
	for (int xbin = 1; xbin <= xbinm; xbin++){
		for (int ybin = 1; ybin <= ybinm; ybin++){
			double x = hcorr->GetXaxis()->GetBinCenter(xbin);
			double y = hcorr->GetYaxis()->GetBinCenter(ybin);
			hcorr->Fill(x,y,bigaus(x,y,rho,mux,muy,sigmax,sigmay));
		}
	}
	c1->cd(4);hcorr->Draw("COLZ");

	cout << "2D integral:" << hcorr->Integral() << endl;


	c1->cd(5); hcomb->Draw("COLZ");

	//monte carlo addition of 40KeV line and nuclear recoil
	for (int i = 1; i <= 20000; i++)	ra();

	hcomb->Sumw2();

//remove comment to do output according to need


	//output all histograms
	TFile *fout = new TFile("fout.root", "recreate");
	hcomb->Write("combined");
	hcorr->Write("fortyKeVGamma");
	h4->Write("tmpPDF");
	h3->Write("smearedS2");
	h2->Write("smearedS1");
	h1->Write("originalSpectrum");
	fout->Close();


/*
	//output final model	
	TFile *cfout = new TFile("comp_out.root", "update");
	hcomb->SetName(NAME);
	hcomb->Write();
	cfout->Close();
*/
}

void comp(string name){
//output a comparison canvas to comp_out.root
//canvas name as parameter
//use this function to check the effect of changing parameter

	TFile *cf1 = new TFile("stdmodel.root");
	TFile *cf3 = new TFile("merge_34kg_gaudenzCut.root");

		

	TCanvas *outc = new TCanvas(name.c_str(),"outc",800,600);	

	TH2D *ch1 = (TH2D*) cf1->Get("combined");
	TH2D *ch2 = hcomb;
	ch2->SetName(name.c_str());
	ch2->SetTitle(name.c_str());
	TH2D *ch3 = (TH2D*) cf3->Get("s1_s2_AmBe");	//data	

	ch1->Rebin2D(4,4);
	ch2->Rebin2D(4,4);
	ch3->Rebin2D(20,20);

	ch1->GetXaxis()->SetRangeUser(40,200);
	ch1->GetYaxis()->SetRangeUser(4000,20000);
	ch2->GetXaxis()->SetRangeUser(40,200);
	ch2->GetYaxis()->SetRangeUser(4000,20000);
	ch3->GetXaxis()->SetRangeUser(40,200);
	ch3->GetYaxis()->SetRangeUser(4000,20000);

	TLegend *leg = new TLegend(0.15, 0.65, 0.4, 0.8);

	ch1->SetLineColor(2);
	ch2->SetLineColor(4);
	ch3->SetLineColor(14);
	ch1->SetContour(6);
	ch1->SetTitle(name.c_str());
	ch1->Draw("cont3");
	ch2->SetContour(6);
	ch2->Draw("cont3 same");
	ch3->SetContour(6);
	ch3->Draw("cont3 same");
	leg->AddEntry(ch1, "original simulation");
	leg->AddEntry(ch2, "compared");
	leg->AddEntry(ch3, "data");
	leg->Draw();

	TFile *cfout = new TFile("comp_out.root", "update");
	outc->Write();
	cfout->Close();
}

void ra(){
//monte carlo addition of 40KeV gamma line and the NR recoil spectra
	hcorr->GetRandom2(rx,ry);
	rax = h2->GetRandom();
	ray = h3->GetRandom();
	hcomb->Fill(rx + rax,ry + ray);
}

/*
//obsolete
double poisson(double k, double lambda){
	//http://www.masaers.com/2013/10/08/Implementing-Poisson-pmf.html
	return exp(k * log(lambda) - ROOT::Math::lgamma(k+1.0) - lambda);
}



double gaussian(double x, double mu, double sigma){
	return exp(-pow((x-mu),2)/(2*pow(sigma,2)))/pow(2*pow(sigma,2)*TMath::Pi(),0.5);
}

double gaussiancdf(double x, double mu, double sigma){
	return 0.5 * (1 + erf((x-mu)/(sqrt(2)*sigma)));
}

*/

double bigaus(double x, double y, double rho, double mux, double muy, double sigmax, double sigmay){
	return 1.0/(2*TMath::Pi()*sigmax*sigmay*sqrt(1-pow(rho,2)))*
exp(-1.0/(2*(1-pow(rho,2)))*(pow(x-mux,2)/pow(sigmax,2)+pow(y-muy,2)/pow(sigmay,2)-
2.0*rho*(x-mux)*(y-muy)/sigmax/sigmay));
}

//sitong an

