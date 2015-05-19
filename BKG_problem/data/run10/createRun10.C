#include "XePhys.h"

void createRun10(){
 Xenon100Detector det(10);
 det.dump(1);

 TFile *tf=new TFile("../data/run10/dm_results.root","OLD");
 TGraph* gdm=new TGraph();
 gdm->Read("grlog");
 TGraph* xdm=XeDisplay::unflatten(gdm);
 tf->Close();
 
 TGraph grambe("../data/run10/ambe_34kg.dat");
 TGraph* xambe=XeDisplay::unflatten(&grambe);


 TGraph grCo60("../data/run10/er_34kg.from_Marc.dat");
 TGraph* xCo60=XeDisplay::unflatten(&grCo60);


 TFile *tfn=new TFile("../data/run10/bands.root","recreate");
 tfn->cd();
 xdm->Write("grData");
 xambe->Write("grAmBe");
 xCo60->Write("grCo60");
 tfn->Close();

}
