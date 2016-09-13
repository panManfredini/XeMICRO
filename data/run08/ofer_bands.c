{
  double a[11]={3.0390 , 5.9394 , 7.9839 , 9.6852 , 11.2227 , 12.6913 , 14.1600 , 15.6975, 17.3988 , 19.4433 , 22.3437 };
  double b[11]={172.5165 , 169.7464 , 167.7938 , 166.1689 , 164.7004 , 163.2977 , 161.8951 , 160.4266,158.8017 , 156.8491 , 154.0789 };
  double c[11]={-204.1434 , -142.1765 , -98.4968 , -62.1488 , -29.2996 , 2.0779 , 33.4553 ,66.3046, 102.6526 , 146.3323 , 208.2992 };
  TF1 *bands=new TF1[11];
  TF1 *ebandflat = new TF1("ebandflat","pol9",2,50);
ebandflat->SetParameters(2.66695+0.267047+0.00019154,-0.0960315-0.155731+0.000101306,0.00604496+0.0331754,-0.000200455-0.00357708,3.29415e-06+0.000222689,-2.10034e-08-8.49461e-06,2.01609e-07,-2.8995e-09,2.30693e-11,-7.76065e-14);
  for (int i=0; i<11; i++) { 
    bands[i]=new TF1(Form("fa%d",i),"[0]*x+[1]*sqrt(x)+[2]",3,40);
    bands[i].SetParameter(0,a[10-i]);
    bands[i].SetParameter(1,b[10-i]);
    bands[i].SetParameter(2,c[10-i]);
}
  
  float flatband1[26];
  float flatband2[26];
  float band_res;

  gROOT->ProcessLine(".L compute_single_band_content.c");

  for (int i=0;i<12;i++)
    {
      if (i==0)
	{
	  for (int j=0;j<26;j++)
	    {
	      flatband1[j]=10;
	      flatband2[j]=log10(bands[i]->Eval(4.5+j)/(4.5+j))-ebandflat->Eval(4.5+j);
	 //   cout<<" band "<<i-1<<" and "<<i<<", bin "<<4.5+j<<"  f1="<<flatband1[j]<<" f2="<<flatband2[j]<<endl;
	    }	  
	}
      else if (i==11)
	{
	  for (int j=0;j<26;j++)
	    {
	      flatband1[j]=log10(bands[i-1]->Eval(4.5+j)/(4.5+j))-ebandflat->Eval(4.5+j);
	      flatband2[j]=-10;
	//    cout<<" band "<<i-1<<" and "<<i<<", bin "<<4.5+j<<"  f1="<<flatband1[j]<<" f2="<<flatband2[j]<<endl;
	    }	  
	  
	}
      else
	{
	  for (int j=0;j<26;j++)
	    {
	      flatband1[j]=log10(bands[i-1]->Eval(4.5+j)/(4.5+j))-ebandflat->Eval(4.5+j);
	      flatband2[j]=log10(bands[i]->Eval(4.5+j)/(4.5+j))-ebandflat->Eval(4.5+j);
	//    cout<<" band "<<i-1<<" and "<<i<<", bin "<<4.5+j<<"  f1="<<flatband1[j]<<" f2="<<flatband2[j]<<endl;
	    }	  
	  
	}
      band_res=compute_single_band_content(flatband1, flatband2);
      	
      cout << band_res <<"(band "<<i<<")\n";
    }
  cout << endl;
}
