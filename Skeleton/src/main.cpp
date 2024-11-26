// #include "Simulation.h"
#include <iostream>
#include <Settlement.h>
#include <Facility.h>

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    // if(argc!=2){
    //     cout << "usage: simulation <config_path>" << endl;
    //     return 0;
    // }
    // string configurationFile = argv[1];
    // Simulation simulation(configurationFile);
    // simulation.start();
    // if(backup!=nullptr){
    // 	delete backup;
    // 	backup = nullptr;
    // }
   string name  = "musmus";
   SettlementType num = SettlementType::VILLAGE;
   Settlement *s=new Settlement(name,num);
    cout<<(*s).toString()<<endl; 
    Facility *f=new Facility("school",s->getName(),FacilityCategory::LIFE_QUALITY,1,3,2,1);
    cout<<f->toString()<<endl;
    f->step();
    cout<<f->getTimeLeft()<<endl;
    delete s;
    delete f;
    return 0;
}