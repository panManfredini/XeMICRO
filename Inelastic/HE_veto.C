{

TFile *veto = TFile::Open("co_veto.root");
TFile *no_veto = TFile::Open("co_noveto.root");

TH2D *s1s2_veto = (TH2D*) veto->Get("log_s2_s1_Co60");
TH2D *s1s2_noveto = (TH2D*) no_veto->Get("log_s2_s1_Co60");


TH1F *s1_veto = (TH1F*) s1s2_veto->ProjectionX();
TH1F *s1_noveto = (TH1F*) s1s2_noveto->ProjectionX();

s1_veto->Draw();
s1_noveto->Draw("same");
}

