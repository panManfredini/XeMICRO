{

TFile *f = TFile::Open("ambe_study_10.root");

TH2D *s1_s2 = (TH2D*) f->Get("s1_s2_AmBe");
TH2D *for_projection = new TH2D("for_projection","",1000,0.,1000., 1000,0.,200000.);


s1_s2->Draw();

// Line for cuts
TF1 *lineTop = new TF1 ("lineTop","[0]*x + [1]",200.,550.);
lineTop->SetParameter(0,-88.6);
lineTop->SetParameter(1,104237. - 2000.);

// Line for cuts
TF1 *lineBot = new TF1 ("lineBot","[0]*x + [1]",200.,550.);
lineBot->SetParameter(0,-98.2);
lineBot->SetParameter(1,69809. + 5000.);
lineTop->Draw("same");
lineBot->Draw("same");


int Xstart = s1_s2->GetXaxis()->FindBin(200.);
int Ystart = s1_s2->GetYaxis()->FindBin(lineBot->Eval(200.) );

int x_itr = Xstart;
int y_itr = Ystart;

double X = 200.;
double Y = lineBot->Eval(200.);

double entries = 0;
double cov =0;
 
double mean_X = 0.;
double mean_Y = 0.;
double var_X = 0.;
double var_Y = 0.;


// The code needs to run twice... (It's ugly I know) one to get the mean value and other to calculate variance ecc...
// so the capital letter MEAN_ are the precomputed ones...
//double MEAN_x = 338.256;
//double MEAN_y = 58087.3;
double MEAN_x = 349.094;
double MEAN_y = 54702.8;
double VAR_x  = 60.4357;
double VAR_y =  7268.77;

// compute mean, variance and covariance...
while ( X <= 550. && X >= 200.) 
	{
	  x_itr++;
	  X = s1_s2->GetXaxis()->GetBinCenter(x_itr);

	  y_itr = Ystart+1;
	  Y = s1_s2->GetYaxis()->GetBinCenter(y_itr); 
	  
  	  while (Y <= lineTop->Eval(X) && Y >= lineBot->Eval(X) )
		{
		  y_itr++;
	  	  Y = s1_s2->GetYaxis()->GetBinCenter(y_itr);
			
		  double content = s1_s2->GetBinContent(x_itr,y_itr);
		  entries +=  content;

		  mean_X += content * X;
		  mean_Y += content * Y;
		  
		  var_X += content * ( X - MEAN_x)*(X - MEAN_x);
		  var_Y += content * ( Y - MEAN_y)*(Y - MEAN_y);

		  cov += content * (X - MEAN_x)*(Y - MEAN_y);

		  for_projection->Fill(X,Y,content);
		  
		}
	  
	}

mean_X = mean_X / entries;
mean_Y = mean_Y / entries;
var_X = sqrt(var_X / entries);
var_Y = sqrt(var_Y / entries);

double correlation  = cov / entries / VAR_x / VAR_y;

cout << "entries " << entries << endl;
cout << "mean X " << mean_X << endl;
cout << "mean Y " << mean_Y << endl;
cout << "var X " << var_X << endl;
cout << "var Y " << var_Y << endl;
cout << "covariance " << cov << endl;
cout << "CORRELATION  " << correlation << endl;


//----------------- replot all below here is just a test---//
TRandom rand_gaus;

TH2D *h = new TH2D("h","",1000,0.,1000., 1000,0.,200000.);

double ro = -0.5; 
//double ro = -0.446136; 
//double ro = -0.365002; 

/*
mean X 338.256
mean Y 58087.3
var X 55.0877
var Y 5309.19
covariance -0.307394
*/


/*
test 2
mean X 349.094
mean Y 54702.8
var X 60.4357
var Y 7268.77
covariance -0.365002
*/

for(int i=0; i < 500; i++){

	double X =   rand_gaus.Gaus();
	double eps =  rand_gaus.Gaus();
	double Y = ro*X + sqrt(1. - ro*ro)*eps;

	h->Fill(60.4357*X + 349.094, 7268.77*Y + 54702.8);

}

h->SetMarkerColor(2);
h->Draw("same");


TH1D *px = for_projection->ProjectionX();
TH1D *py = for_projection->ProjectionY();
new TCanvas();
px->Draw();
new TCanvas();
py->Draw();


}
