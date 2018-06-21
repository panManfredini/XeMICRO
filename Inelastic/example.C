{

gROOT->ProcessLine(".L inelastic_style.C "); 

setInelasticStyle(1./2.);

TCanvas canv("canv", "First canvas", 1000, 800);
canv.Divide(3,5);

TH1F *h = new TH1F("h","",100,0,100);
TH1F *h_temp;

for(i=1 ; i <= 15; i++){
  canv.cd(i);
  gPad->SetLeftMargin(0.13);
  gPad->SetTopMargin(0.00);
  gPad->SetBottomMargin(0.12);
  gPad->SetRightMargin(0.04);
  TString name = "name";
  name.Append(TString::Itoa(i,10));
  h_temp = new TH1F(name,"",100,0,100);

  h_temp->Draw();
 }

}
