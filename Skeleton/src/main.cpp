// #include "Simulation.h"
#include <iostream>
#include <Settlement.h>
#include <Facility.h>
 #include <SelectionPolicy.h>
#include <vector>

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
    FacilityType f= Facility("school",s->getName(),FacilityCategory::ECONOMY,1,3,2,1);
    Facility f1= Facility("park",s->getName(),FacilityCategory::ENVIRONMENT,2,4,1,1);
    Facility f2= Facility("office",s->getName(),FacilityCategory::ECONOMY,3,3,2,2);
    Facility f3= Facility("gym",s->getName(),FacilityCategory::ECONOMY,3,5,2,1);

    vector<FacilityType> v1;
    v1.push_back(f);v1.push_back(f1);v1.push_back(f2);v1.push_back(f3);
     //for(int i = 0 ; i <v1.size(); i+=1){cout<<v1[i].toString()<<endl;}
     //std::cout<<f.getName()<<endl;
     NaiveSelection n =NaiveSelection();
    EconomySelection e = EconomySelection();
     //SustainabilitySelection sus = SustainabilitySelection();
     //BalancedSelection b = BalancedSelection(0,0,0);


    cout<<n.toString()<<endl;
    FacilityType example1 =n.selectFacility(v1);
    FacilityType example2 =n.selectFacility(v1);
    FacilityType example3 =n.selectFacility(v1);
    FacilityType example4 =n.selectFacility(v1);
    FacilityType example5 =n.selectFacility(v1);


    FacilityType example6 =e.selectFacility(v1);
    FacilityType example7 =e.selectFacility(v1);
    FacilityType example8 =e.selectFacility(v1);
    FacilityType example9 =e.selectFacility(v1);
    FacilityType example10 =e.selectFacility(v1);

    // FacilityType example11 =sus.selectFacility(v1);
    // FacilityType example12 =sus.selectFacility(v1);
    // FacilityType example13 =sus.selectFacility(v1);
    // FacilityType example14 =sus.selectFacility(v1);
    // FacilityType example15 =sus.selectFacility(v1);

    // FacilityType example16 =b.selectFacility(v1);
    // FacilityType example17 =b.selectFacility(v1);
    // FacilityType example18 =b.selectFacility(v1);
    // FacilityType example19 =b.selectFacility(v1);
    // FacilityType example20 =b.selectFacility(v1);

    

    cout<<"___________________________Naive________________________"<<endl;


    std::cout<<"name is = " + example1.getName()<<endl;
    std::cout<<"name is = " + example2.getName()<<endl;
    std::cout<<"name is = " + example3.getName()<<endl;
    std::cout<<"name is = " + example4.getName()<<endl;
    std::cout<<"name is = " + example5.getName()<<endl;

    cout<<"___________________________Economy________________________"<<endl;

    std::cout<<"name is = " + example6.getName()<<endl;
    std::cout<<"name is = " + example7.getName()<<endl;
    std::cout<<"name is = " + example8.getName()<<endl;
    std::cout<<"name is = " + example9.getName()<<endl;
    std::cout<<"name is = " + example10.getName()<<endl;

    // cout<<"___________________sustainability_________________________"<<endl;


    
    // std::cout<<"name is = " + example11.getName()<<endl;
    // std::cout<<"name is = " + example12.getName()<<endl;
    // std::cout<<"name is = " + example13.getName()<<endl;
    // std::cout<<"name is = " + example14.getName()<<endl;
    // std::cout<<"name is = " + example15.getName()<<endl;

    // cout<<"___________________balanced_________________________"<<endl;

    // std::cout<<"name is = " + example16.getName()<<endl;
    // std::cout<<"name is = " + example17.getName()<<endl;
    // std::cout<<"name is = " + example18.getName()<<endl;
    // std::cout<<"name is = " + example19.getName()<<endl;
    // std::cout<<"name is = " + example20.getName()<<endl;
    





    //cout<<f->toString()<<endl;
    //f->step();
    //cout<<f->getTimeLeft()<<endl;
    delete s;
  
    return 0;
}