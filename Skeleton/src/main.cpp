// #include "Simulation.h"
#include <iostream>
#include <Settlement.h>

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
    int i=1;
   string name  = "musmus";
   SettlementType num = SettlementType::VILLAGE;
   Settlement *s=new Settlement(name,num);
    cout<<(*s).toString()<<endl; 
    delete s;
    return 0;
}