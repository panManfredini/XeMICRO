{

TRandom rand_gaus;

TH2D *h = new TH2D("h","",1000,0.,1000., 1000,0.,200000.);

double var = 0;

double corr =0; 

double ro = -0.307394;

/*
mean X 338.256
mean Y 58087.3
var X 55.0877
var Y 5309.19
covariance -0.307394
*/

for(int i=0; i < 100000; i++){

	double X =   rand_gaus.Gaus();
	double eps =  rand_gaus.Gaus();
	double Y = ro*X + sqrt(1. - ro*ro)*eps;

	var += Y*Y;

		
	corr += X * Y ;

//	X += 0.5 * rand_gaus.Gaus();
//	Y += 0.2 * rand_gaus.Gaus();

	h->Fill(55.0877*X + 338.256, 5309.19*Y + 58087.3);

}

corr = corr / 100000.;
var = sqrt(var / 100000.);

cout << corr << endl;
cout << "var  " << var << "   " << sqrt( 1. + 25.) << endl;
//h.GetXaxis()->SetLimits(-20.,20.);
//h.GetYaxis()->SetLimits(-20.,20.);


h->Draw();


}
