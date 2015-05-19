{
  float HighPE=30;
  float LowPE=3;
  int NPE=(HighPE-LowPE)/1.;
  float HighS1S2=1;
  float LowS1S2=-1;
  int NS1S2=200;
  int Nbands=12;
  double R=0.0271;  
  TH2D *h_erdata=new TH2D("h_erdata","h2",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);		//fille with data from text file
  TH2D *h_data_m_gauss=new TH2D("h_erdata","h2",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  TH2D *h_erModel=new TH2D("h_erModel","ER Model; S1 [pe]; Flattened",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  TH2D *h_erModelg=new TH2D("h_erModelg","Gaussian ER Model; S1 [pe]; Flattened",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  TH2D *h_erModelng=new TH2D("h_erModelng","None Gaussian ER Model; S1 [pe]; Flattened",HighPE-LowPE,LowPE,HighPE,NS1S2,LowS1S2,HighS1S2);
  double S1S2Bin = h_erModelng->GetYaxis()->GetBinWidth(1);
  cout << "S1S2Bin " << S1S2Bin << endl;   //Ale;
  TH1F *gLeakageTop=new TH1F("gLeakageTop","Leakage top+bottom (All s1s2); S1 [pe] ; N events",HighPE-LowPE,LowPE,HighPE);
  TH1F *gLeakageBottom=new TH1F("gLeakageBottom","Leakage Bottom (s1s2<0); S1 [pe] ; N events",HighPE-LowPE,LowPE,HighPE);
  TH1F *gLeakageProfileS1S2=new TH1F("gLeakageProfileS1S2","Leakage events projection on Y; Flattenend S1S2; # events",NS1S2,LowS1S2,HighS1S2);

  TCanvas *c1=new TCanvas("c1","c1",1000,600);

  // Read in the ER calibration point
  TGraph *g_erdata=new TGraph("data/run10/er_34kg.from_Marc.dat");
  for (int i=0; i<g_erdata->GetN(); i++) {
    double x,y;
    g_erdata->GetPoint(i,x,y);
    h_erdata->Fill(x,y);
  }


  // Make slices in S1, and fit gaussian

  TCanvas *c5=new TCanvas("c5","c5",1000,600);
  c5->Divide(3,3);
  double leak_ale = 0;
  for (float pe=LowPE; pe<HighPE; pe=pe+1) {
    int bin=h_erdata->GetXaxis()->FindBin(pe);
    // histogram a holds the pe-pe+1 slice
    TH1D *a=h_erdata->ProjectionY(Form("p%d",(int) pe), bin,bin);
    a->SetTitle(Form("Gaussian only, PE Slice %d-%d pe; Flattened; Events",(int) pe,(int) (pe+1.)));    
   
    TF1 *fg=new TF1(Form("fg%d",pe),"gaus",-0.4,0.4); // Fit Function
    TF1 *fgd=new TF1(Form("fg%dd",pe),"gaus",-1,1);     // Fit function for wider range for drawing
    c1->cd();
    if (pe==3) c5->cd(1);
    if (pe==4) c5->cd(2);
    if (pe==6) c5->cd(3);
    if (pe==8) c5->cd(4);
    if (pe==10) c5->cd(5);
    if (pe==15) c5->cd(6);
    if (pe==20) c5->cd(7);
    if (pe==25) c5->cd(8);
    if (pe==29) c5->cd(9);
    //    ai->Fit(fg,"r");    
    a->Fit(fg,"rl");
    double par0=fg->GetParameter(0);
    double par1=fg->GetParameter(1);
    double par2=fg->GetParameter(2);
    fgd->SetParameters(par0,par1,par2);
    gPad->SetLogy();
    gPad->SetGridx();
    gPad->SetGridy();
    a->DrawClone("e");
    fgd->DrawClone("same");
    a->DrawClone("e:same");


    cout<<"tot for "<<pe<<" pe is "<<fgd->Integral(-1,1)/S1S2Bin<<"  vs "<<a->Integral()<<endl;
    // Fill the 2d histogram that holds the gaussian leakage info:
    for (float s1s2=-1; s1s2<1; s1s2=s1s2+S1S2Bin){
      int bin2d=h_erModelg->FindBin(pe,s1s2);
      double current=h_erModelg->GetBinContent(bin2d);
      if (current > 1e-10) cout<<"************ \n **    problem  : "<<current<<"  ** \n ************** \n";
      h_erModelg->SetBinContent(bin2d,R*fg->Eval(s1s2)); // Using 1pe bin width in X, and identical bin width in s1s2 as what was used in the fit above
    }

    // Count the leakage events and check their profile in S1S2
    double leakageLimit = 3.5*par2;//par2 * 2.875; //2.875 ; // 3.8 ;
    for (int i=0; i<g_erdata->GetN(); i++) {
      double x,y;
      g_erdata->GetPoint(i,x,y);
      if (x>=pe && x<pe+1 && y>leakageLimit)   {gLeakageProfileS1S2->Fill(y);}
      if (x>=pe && x<pe+1 && y<-leakageLimit)   {gLeakageProfileS1S2->Fill(y);}
    }

    // Count number of event outside the leakage limit
    double dataTop = a->Integral(a->FindBin(par1+leakageLimit),a->FindBin(1));		//Ale:  This is sum of bin content, which should be multiplied by binwith to compare to below.
    double modelTop = fgd->Integral(par1+leakageLimit,1)/S1S2Bin;  			//Ale:  This is number of events
    //double modelTop = fgd->Integral(par1+leakageLimit,1);  				//Ale:  This is "real" Integral 
    double dataBottom = a->Integral(a->FindBin(-1),a->FindBin(par1-leakageLimit));
    double modelBottom = fgd->Integral(-1,par1-leakageLimit)/S1S2Bin;			//Ale
    //double modelBottom = fgd->Integral(-1,par1-leakageLimit);
    bin = gLeakageTop->FindBin(pe);

    double norm = 2./(1-leakageLimit); // The total rate is calculated between 1 and leakageLimit. It should acount for the full S1S2 range of /pm 1
    gLeakageTop->SetBinContent(bin,(dataTop-modelTop + dataBottom - modelBottom)*norm/2.);  // Extra norm factor 2 because this is done using top and bottom 
    gLeakageBottom->SetBinContent(bin,(dataBottom-modelBottom)*norm); 
    cout<<"Leackage  -- "<<"model "<< modelBottom<<" - data "<<dataBottom<< "  --- Leackage  " << (dataTop-modelTop + dataBottom - modelBottom)*norm/2. <<endl;  // Ale
    if((dataTop-modelTop + dataBottom - modelBottom)*norm/2. > 0.)    leak_ale += (dataTop-modelTop + dataBottom - modelBottom)*norm/2.;  // Ale
  } // End of loop on PE
  // Make integrated figures

  cout << "TOT Leak  --- "  << leak_ale  << "   Normalized  " << leak_ale *R<< endl;   // Ale
  

  TCanvas *c6=new TCanvas("c6","c6",1000,600);
  c6->Divide(2,1);
  
  c6->cd(2); gPad->SetGrid();
  gLeakageTop->Fit("expo","l"); gLeakageTop->Draw("e");
  c6->cd(1);  gPad->SetGrid();
  gLeakageBottom->Fit("expo","l"); gLeakageBottom->Draw("e");

  TCanvas *c7=new TCanvas("c7","c7",1000,600);
  gLeakageProfileS1S2->Draw(); 



  for (float pe=LowPE; pe<HighPE; pe++) {
    for (float s1s2=-1; s1s2<1; s1s2=s1s2+S1S2Bin){
      int bin2=h_erModelng->FindBin(pe,s1s2);

      //double Leak = gLeakageTop->GetFunction("expo")->Eval(pe)/NS1S2 * R;       // Ale 
      double Leak = gLeakageTop->GetFunction("expo")->Eval(pe)*S1S2Bin * R;   // why times S1S2Bin??  // Ale
      double Gauss= h_erModelg->GetBinContent(bin2);
      h_erModelng->SetBinContent(bin2,Leak);
      h_erModel->SetBinContent(bin2,Gauss+Leak);
    }
  }

  TCanvas *c8=new TCanvas("c8","c8",1200,800);
  gStyle->SetOptStat(0);
  c8->Divide(3,1);
  c8->cd(1); h_erModelg->Draw("colz"); gPad->SetLogz();
  c8->cd(2); h_erModelng->Draw("colz"); gPad->SetLogz();
  c8->cd(3); h_erModel->Draw("colz"); gPad->SetLogz();

  int x1=h_erModelg->GetXaxis()->FindBin(3);
  int x2=h_erModelg->GetXaxis()->FindBin(20);
  int y_1=h_erModelg->GetYaxis()->FindBin(-1);
  int y2=h_erModelg->GetYaxis()->FindBin(1);

  cout<<"calib Sample has a total of "<<g_erdata->GetN()<<" Events. R="<<R<<"   =" <<R*g_erdata->GetN()<<endl;
  cout<<" from 3-20pe ER="<<h_erModel->Integral(x1,x2,y_1,y2)<<"   Out of which non gaus="<<h_erModelng->Integral(x1,x2,y_1,y2)<<endl;
  x2=h_erModelg->GetXaxis()->FindBin(30);
  cout<<" from 3-30pe ER="<<h_erModel->Integral(x1,x2,y_1,y2)<<"   Out of which non gaus="<<h_erModelng->Integral(x1,x2,y_1,y2)<<endl;

  TFile *fout = new TFile ("ER_Background.run10.root","recreate");
  h_erModel->Write("h_erModel");
  fout->Close();

}
