float compute_single_band_content(float* flatband1, float* flatband2)
{
  float bandcontent;
  float gausleak=0.;
  float neutleak=0.;
  float anomleak=0.;
  float npb;
  float flat1, flat2;
  int jindex;

  float npbg=896.5;



  TF1 *fsigmaco60 = new TF1("fsigmaco60", "(-0.438131/3.09+0.000597874/3.09*x)", 0, 50);//Sigma of the Co60 band as a function of S1
  //3.09 is the number of signals in the 99.8 area. dividing by 3.09 gives the 1 sigma level.
  int npco60=17595;//Number of Co60 points passing all cuts
  float factorco60=43.3;//Factor to convert from the Co60 exposure to the DM exposure
  float factorer=26./32.;//Factor to correct from the 3-35pe range where the leakage is computed to the actual 4-30pe range
  TFile *fco60 = new TFile("Run08eband.root");

  TGraph *grco60 = (TGraph *) fco60->Get("greband");
  TFile *fambe = new TFile("Run08nband.root");
  TGraph *grambe = (TGraph *) fambe->Get("grnband");

  float gausc, anomc, neutc;

  double x, y;
  int nleak;
  float gauscopred;

      npb=0;
      for (int j=4;j<30;j++)
	{
	  jindex=j-4;
	  flat1=flatband1[jindex];
	  flat2=flatband2[jindex];

	  ////////////////////////////////////////////////////////////
	  //Gaussian Contribution
	  // https://xecluster.lngs.infn.it/dokuwiki/doku.php?id=xenon:xenon100:analysis:bgprediction:erleakagerun08flat3
	  ////////////////////////////////////////////////////////////
	  gausc=0;
	  float meanbg=0.022242;    // Constants for gaussian are taken from run8 note. 
	  float sigmabg=0.135846;
	  gausc=npbg*(0.5*(TMath::Erf((flat1-meanbg)/sqrt(2)/sigmabg)-TMath::Erf((flat2-meanbg)/sqrt(2)/sigmabg)));
	  /* cout << gausc << endl; */

	  ////////////////////////////////////////////////////////////
	  //Anomalous Leakage Contribution
	  // https://xecluster.lngs.infn.it/dokuwiki/doku.php?id=xenon:xenon100:analysis:bgprediction:erleakagerun08flat2#uncertainty_in_the_er_rejection
	  // https://xecluster.lngs.infn.it/dokuwiki/doku.php?id=xenon:xenon100:analysis:bgprediction:erleakagerun08flat3
	  ////////////////////////////////////////////////////////////
	  nleak=0;
	  for (int erloop=0;erloop<grco60->GetN();erloop++)
	    {
	      grco60->GetPoint(erloop, x, y);
	      if (x>3&&x<35)
		{
		  if (y<flat1 && y>flat2)nleak++;
		}
	    }
	  // Check number of events expected for this pe range (gauscorped).
	  // if the number of events observed in this range (nleak above) is larger than the expected background take the difference as the estimation. If it is smaller, use 0.
	  gauscopred=npco60*(0.5*(TMath::Erf(flat2/sqrt(2)/fsigmaco60->Eval(j+0.5))-TMath::Erf(flat1/sqrt(2)/fsigmaco60->Eval(j+0.5))));	
	  if (nleak>gauscopred) anomc=(nleak-gauscopred)*factorer/factorco60;
	  else anomc=0.;

//  cout<<"nleak="<<nleak<<" gaus="<<gauscopred<<"  f1="<<flat1<<"   flat2="<<flat2<<endl;

	  /* cout << nleak << "  "  << gauscopred << endl; */


	  ////////////////////////////////////////////////////////////
	  //Neutron contribution
	  // https://xecluster.lngs.infn.it/dokuwiki/doku.php?id=xenon:xenon100:analysis:bgprediction:erleakagerun08flat3
	  // https://xecluster.lngs.infn.it/dokuwiki/doku.php?id=xenon:xenon100:analysis:run8ubp:nrbg
	  ////////////////////////////////////////////////////////////
	  float nneut=0.11/0.36; // Total number of NR between 4-30 pe predicted for run 8
	  int nbandneut=56530;
	  neutc=0;
	  // Count how many events are in the corresponding pe range and the corresponding band.
	  // Normalise them accorsing to the data sample. multiply by 0.11/0.36 which is 
	  for (int loopnr=0;loopnr<grambe->GetN();loopnr++)
	    {
	      grambe->GetPoint(loopnr, x, y);
	      if (x>j&&x<j+1&&y<flat1&&y>flat2)
	      neutc+=1;
	    }
	  neutc=neutc*nneut/nbandneut;
	  //cout<<j+4.5<<" gausc="<<gausc<<" anomc="<<anomc<<" neutc="<<neutc<<endl;

	  npb+=(gausc+anomc)/26.+neutc;
	  neutleak+=neutc;
	  gausleak+=gausc/26.;
	  anomleak+=anomc/26.;
	  
	}

      bandcontent=npb;    

      cout <<gausleak << "  "   << anomleak << "   "  << neutleak<< "=" ; 
      /* cout << (flat1-meanbg)/sigmabg << "   "  << (flat2-meanbg)/sigmabg << endl << "   "  << 0.5*(TMath::Erf((flat1-meanbg)/sqrt(2)/sigmabg)-TMath::Erf((flat2-meanbg)/sqrt(2)/sigmabg)) << endl; */
      return bandcontent;
}
