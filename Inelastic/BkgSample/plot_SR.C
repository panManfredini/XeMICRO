{


  gROOT->ProcessLine(".L convert_function.C"); 
  TCanvas canv("canv", "First canvas", 1000, 800);
  TPad *upper =new TPad("upper","plot", 0.01,0.01,0.99,0.99);
  upper->SetLeftMargin(0.15);
  upper->SetTopMargin(0.00);
  upper->SetBottomMargin(0.11);
  upper->SetRightMargin(0.17);

  upper->Draw();

  gStyle->SetOptStat(0);
   const Int_t Number = 2;
   Double_t Red[Number]    = {51./255, 0.00 } ;
   Double_t Green[Number]  = {1.0, 0.0};
   Double_t Blue[Number]   = { 1.0, 0.40};
   Double_t Length[Number] = { 0.00, 1.00};
   Int_t nb=50;
   TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
//  gStyle->SetPalette(51);

  TFile *f = TFile::Open("../DATA/final_merge.root");

  TH2D *ambe = (TH2D*)f->Get("s1_s2_AmBe");
  TH2D *co60 = (TH2D*)f->Get("s1_s2_Co60");
  TH2D *dm = (TH2D*)f->Get("s1_s2_DM");

  TH2D *ambe_l = (TH2D*)f->Get("log_s2_s1_SR_AmBe");
  TH2D *co60_l = (TH2D*)f->Get("log_s2_s1_SR_Co60");
  TH2D *dm_l = (TH2D*)f->Get("log_s2_s1_SR_DM");

  cout << ambe->GetNbinsX() << endl; 
  cout << ambe->GetNbinsY() << endl; 
  ambe->Rebin2D(4,4);
  co60->Rebin2D(8,8);
//  dm->Rebin2D(30,20);

  ambe->SetLineColor(2);
  ambe->SetLineWidth(3);

  co60->SetLineColor(4);
  co60->SetLineWidth(3);

  ambe->SetContour(5);
  co60->SetContour(5);



 // ambe->Draw("colz");
//  ambe->Scale(1./ambe->Integral());
  //ambe->Draw("cont3");
 // co60->Draw("cont3same");
  co60->Scale(0.034 / co60->GetXaxis()->GetBinWidth(5) / co60->GetYaxis()->GetBinWidth(5) );//*1000.);
  cout << " x width - " << co60->GetXaxis()->GetBinWidth(5)<< "   y width - " << co60->GetYaxis()->GetBinWidth(5) << endl;
  cout << " x width - " << co60->GetXaxis()->GetBinLowEdge(5)<< "   y width - " << co60->GetYaxis()->GetBinLowEdge(5) << endl;

  double xmin = 48;
  double xmax = 224;
  double ymin = 3200;
  double ymax = 16800;
  co60->GetXaxis()->SetRangeUser(xmin, xmax);
  co60->GetYaxis()->SetRangeUser(ymin, ymax);
  ambe->GetXaxis()->SetRangeUser(xmin, xmax);
  ambe->GetYaxis()->SetRangeUser(ymin, ymax);

  
upper->cd();
//  co60->Draw("COLZ");
  //co60->GetZaxis()->SetLimits(0.01,0.0001);
  co60->GetZaxis()->SetTitle("Expected events / PE^{2}");
  co60->GetZaxis()->SetAxisColor(0);
  co60->GetZaxis()->SetTitleOffset(1.2);
  co60->GetYaxis()->SetTitleOffset(1.6);
  co60->GetXaxis()->SetTitleOffset(1.2);
  co60->GetXaxis()->SetTitleSize(0.05);
  co60->GetXaxis()->SetLabelSize(0.05);
  co60->GetYaxis()->SetTitleSize(0.05);
  co60->GetYaxis()->SetLabelSize(0.05);
  co60->GetZaxis()->SetTitleSize(0.05);
  co60->GetZaxis()->SetLabelSize(0.05);
  //co60->GetZaxis()->SetTitle("Expected events #times 10^{-3} / [PE]^{2}");
  co60->GetXaxis()->SetTitle("cS1  [PE]");
  co60->GetYaxis()->SetTitle("cS2  [PE]");
  co60->GetZaxis()->SetRangeUser(3.5E-5,6.E-3);
  co60->GetXaxis()->SetLabelFont(132);
  co60->GetYaxis()->SetLabelFont(132);
  co60->GetZaxis()->SetLabelFont(132);
  co60->GetXaxis()->SetTitleFont(132);
  co60->GetYaxis()->SetTitleFont(132);
  co60->GetZaxis()->SetTitleFont(132);
  
 //co60->Reset();
 co60->Draw("CONT4Z");

//  co60->Draw("COLZ");
 // ambe->Draw("CONT4Z")
  double x1 = giveMeX(60,xmin, xmax);
  double x2 = giveMeX(210,xmin, xmax);
  double y11 = giveMeX(4000, ymin, ymax);
  double y2 = giveMeX(16000, ymin, ymax);
 
  TLine *line1 = new TLine(x2, y11, x1, y11);
  line1->SetLineColor(0);
  line1->SetLineWidth(5);
  line1->Draw("same");
  TLine *line2 = new TLine(x2, y2, x1, y2);
  line2->SetLineColor(0);
  line2->SetLineWidth(5);
  line2->Draw("same");
  TLine *line3 = new TLine(x1, y11, x1, y2);
  line3->SetLineColor(0);
  line3->SetLineWidth(5);
  line3->Draw("same");
  TLine *line4 = new TLine(x2, y11, x2, y2);
  line4->SetLineColor(0);
  line4->SetLineWidth(5);
  line4->Draw("same");

   x1 = giveMeX(60,xmin, xmax);
   x2 = giveMeX(210,xmin, xmax);
   y11 = giveMeX(12000, ymin, ymax);
   y2 = giveMeX(16000, ymin, ymax);

  TLine *line5 = new TLine(x1, y11, x2, y11);
  line5->SetLineColor(0);
  line5->SetLineWidth(5);
  line5->Draw("same");

   x1 = giveMeX(60,xmin, xmax);
   x2 = giveMeX(180,xmin, xmax);
   y11 = giveMeX(14000, ymin, ymax);
   y2 = giveMeX(16000, ymin, ymax);
  TLine *line6 = new TLine(x1, y11, x2, y11);
  line6->SetLineColor(0);
  line6->SetLineWidth(5);
  line6->Draw("same");

   x1 = giveMeX(60,xmin, xmax);
   x2 = giveMeX(120,xmin, xmax);
   y11 = giveMeX(10000, ymin, ymax);
   y2 = giveMeX(16000, ymin, ymax);
  TLine *line7 = new TLine(x1, y11, x2, y11);
  line7->SetLineColor(0);
  line7->SetLineWidth(5);
  line7->Draw("same");

  x1 = giveMeX(60,xmin, xmax);
   x2 = giveMeX(150,xmin, xmax);
   y11 = giveMeX(8000, ymin, ymax);
   y2 = giveMeX(16000, ymin, ymax);
  TLine *line8 = new TLine(x1, y11, x2, y11);
  line8->SetLineColor(0);
  line8->SetLineWidth(5);
  line8->Draw("same");

  x1 = giveMeX(90,xmin, xmax);
   x2 = giveMeX(210,xmin, xmax);
   y11 = giveMeX(6000, ymin, ymax);
   y2 = giveMeX(16000, ymin, ymax);
  TLine *line9 = new TLine(x1, y11, x2, y11);
  line9->SetLineColor(0);
  line9->SetLineWidth(5);
  line9->Draw("same");

  x1 = giveMeX(90,xmin, xmax);
   x2 = giveMeX(210,xmin, xmax);
   y11 = giveMeX(6000, ymin, ymax);
   y2 = giveMeX(12000, ymin, ymax);
  TLine *line10 = new TLine(x1, y11, x1, y2);
  line10->SetLineColor(0);
  line10->SetLineWidth(5);
  line10->Draw("same");

  x1 = giveMeX(120,xmin, xmax);
   x2 = giveMeX(210,xmin, xmax);
   y11 = giveMeX(6000, ymin, ymax);
   y2 = giveMeX(14000, ymin, ymax);
 
   TLine *line11 = new TLine(x1, y11, x1, y2);
  line11->SetLineColor(0);
  line11->SetLineWidth(5);
  line11->Draw("same");
     
  x1 = giveMeX(150,xmin, xmax);
   x2 = giveMeX(210,xmin, xmax);
   y11 = giveMeX(8000, ymin, ymax);
   y2 = giveMeX(12000, ymin, ymax);
 
   TLine *line12 = new TLine(x1, y11, x1, y2);
  line12->SetLineColor(0);
  line12->SetLineWidth(5);
  line12->Draw("same");

  x1 = giveMeX(180,xmin, xmax);
   x2 = giveMeX(210,xmin, xmax);
   y11 = giveMeX(12000, ymin, ymax);
   y2 = giveMeX(14000, ymin, ymax);
 
   TLine *line13 = new TLine(x1, y11, x1, y2);
  line13->SetLineColor(0);
  line13->SetLineWidth(5);
  line13->Draw("same")   ;

  x1 = giveMeX(130,xmin, xmax);
  y11 = giveMeX(4700, ymin, ymax);
  TText *t = new TText(x1,y11,"CR1");
//   t->SetTextAlign(132);
   t->SetTextColor(0);
   t->SetTextFont(132);
//   t->SetTextSize(40);
//   t->SetTextAngle(45);
   t->SetTextSize(0.05);
   t->Draw("same");

  x1 = giveMeX(130,xmin, xmax);
  y11 = giveMeX(14700, ymin, ymax);
  TText *t1 = new TText(x1,y11,"CR2");
   t1->SetTextColor(0);
   t1->SetTextFont(132);
   t1->SetTextSize(0.05);
   t1->Draw("same");

   x1 = giveMeX(72,xmin, xmax);
  y11 = giveMeX(8700, ymin, ymax);
 
  TText *t2 = new TText(x1,y11,"1");
   t2->SetTextColor(0);
   t2->SetTextFont(132);
   t2->SetTextSize(0.05);
   t2->Draw("same");

   x1 = giveMeX(72,xmin, xmax);
  y11 = giveMeX(10700, ymin, ymax);
 
  TText *t3 = new TText(x1,y11,"2");
   t3->SetTextColor(0);
   t3->SetTextFont(132);
   t3->SetTextSize(0.05);
   t3->Draw("same");

   x1 = giveMeX(102,xmin, xmax);
  y11 = giveMeX(10700, ymin, ymax);
 
  TText *t4 = new TText(x1,y11,"5");
   t4->SetTextColor(0);
   t4->SetTextFont(132);
   t4->SetTextSize(0.05);
   t4->Draw("same");

   x1 = giveMeX(102,xmin, xmax);
  y11 = giveMeX(8700, ymin, ymax);
 
  TText *t5 = new TText(x1,y11,"4");
   t5->SetTextColor(0);
   t5->SetTextFont(132);
   t5->SetTextSize(0.05);
   t5->Draw("same");

   x1 = giveMeX(102,xmin, xmax);
  y11 = giveMeX(6700, ymin, ymax);
 
  TText *t6 = new TText(x1,y11,"3");
   t6->SetTextColor(0);
   t6->SetTextFont(132);
   t6->SetTextSize(0.05);
   t6->Draw("same");
 
   x1 = giveMeX(87,xmin, xmax);
  y11 = giveMeX(12700, ymin, ymax);
 
  TText *t7 = new TText(x1,y11,"7");
   t7->SetTextColor(0);
   t7->SetTextFont(132);
   t7->SetTextSize(0.05);
   t7->Draw("same");

   x1 = giveMeX(147,xmin, xmax);
  y11 = giveMeX(12700, ymin, ymax);
 
  TText *t8 = new TText(x1,y11,"8");
   t8->SetTextColor(0);
   t8->SetTextFont(132);
   t8->SetTextSize(0.05);
   t8->Draw("same");

   x1 = giveMeX(132,xmin, xmax);
  y11 = giveMeX(9700, ymin, ymax);
 
  TText *t9 = new TText(x1,y11,"6");
   t9->SetTextColor(0);
   t9->SetTextFont(132);
   t9->SetTextSize(0.05);
   t9->Draw("same");

   x1 = giveMeX(177,xmin, xmax);
  y11 = giveMeX(8700, ymin, ymax);
 

  TText *t10 = new TText(x1,y11,"9");
   t10->SetTextColor(0);
   t10->SetTextFont(132);
   t10->SetTextSize(0.05);
   t10->Draw("same");
 
   gPad->SetLogz();
  gPad->Update();

  canv.Print("/home/pan/work/XeMICRO/Inelastic/BkgSample/Co60_SR.png");
  canv.Print("/home/pan/work/XeMICRO/Inelastic/BkgSample/Co60_SR.eps");
  canv.Print("/home/pan/Documents/Papers/mypapers/Inelastic/images/bkg_in_sr.eps");
  canv.Print("/home/pan/Documents/Papers/mypapers/Inelastic/images/bkg_in_sr.png");

}

