#include <Simulation.h>
#include <Auxiliary.h>
#include <Plan.h>
#include <SelectionPolicy.h>
#include <Facility.h>
#include <Settlement.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Simulation::Simulation(const string &configFilePath):isRunning(true),planCounter(0){
//     ifstream inputFile(configFilePath);
//     if (!inputFile.is_open()) {
//         cerr << "Error: Could not open the file." << endl;
        
//     }
//     string line;
//     while (getline(inputFile, line)) {
//         vector<string> v = Auxiliary::parseArguments(line);  // Split the line into tokens

//         if (v.empty()) {
//             continue;  // Skip empty lines
//         }

//         if (v[0] == "settlement") {
//             // Create a new Settlement object and add it to the settlements vector
//             settlements.push_back(new Settlement(v[1], stoi(v[2])));
//         }
//         else if(v[0]=="facility"){
//             facilitiesOptions.push_back(new FacilityType(v[1],stoi(v[2]),stoi(v[3]),stoi(v[4]),stoi(v[5]),stoi(v[6])));
//         }
//         else if(v[0] == "plan")
//         {
//             for (Settlement* s : settlements) {
//                 if (s->getName() == v[1]) {
//                     SelectionPolicy* p = nullptr;

//                     if (v[2] == "eco") {
//                         p = new EconomySelection();
//                     } else if (v[2] == "bal") {
//                         p = new BalancedSelection(0, 0, 0);
//                     } else if (v[2] == "env") {
//                         p = new SustainabilitySelection();
//                     } else {
//                         p = new NaiveSelection();
//                     }

//                     // Create a new Plan and add it to the plans vector
//                     plans.push_back(new Plan(planCounter, *s, p, facilitiesOptions));
//                 }
//             }
//         }
//     }
// }



void Simulation::start(){cout<<"The simulation has started"<<endl;} //maybe add another things to the start

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy){
    Plan newPlan = new Plan(planCounter,settlement,selectionPolicy,facilitiesOptions);
    plans.push_back(newPlan);
}

//void Simulation::addAction(){}

bool Simulation::addSettlement(Settlement* settlement){
    //checking if there is other settlement with the same name
    for(int i = 0; i <settlements.size() ; i+=1){
        if(settlement->getName() == (settlements[i] -> getName())){return false;}   
         }

    settlements.push_back(settlement);
    return true;
}


bool Simulation::addFacility(FacilityType facility){
    //checking if there is other facility with the same name
    for(int i = 0; i <facilitiesOptions.size() ; i+=1){
        if((facility).getName() == (facilitiesOptions[i].getName())){return false;}   
         }
    facilitiesOptions.push_back(facility);
    return true;
}


bool Simulation::isSettlementExists(const string &settlementName){
    for(int i = 0; i <settlements.size() ; i+=1){
        if(settlementName == (settlements[i] -> getName())){return true;}   
         }
         return false;
}

Settlement* Simulation::getSettlement(const string &settlementName){
    for(int i =0; i < settlements.size() ; i+=1){
        if(settlements[i] -> getName == settlementName){return settlements[i];}
    }
}

Plan& Simulation::getPlan(const int planID){
    for(int i=0 ; i<plans.size(); i+=1){
        if(plans[i].plan_id == planID){return plans[i];}
    }
}


void Simulation::step(){

    for(int i = 0; i < plans.size() ;i+=1){
        Plan& curr_plan = plans[i];
        if(curr_plan.getStatus() == PlanStatus::AVALIABLE){//check if the cout is string or Enum
          curr_plan.step();
        } 


//curr_plan.underconstruction[j] is a facility
    for(int j =0; j < curr_plan.underConstruction.size() ; j+=1 ){
        curr_plan.underConstruction[j]->step; //decrease the cost of the facility
        if(curr_plan.underConstruction[j] -> getStatus  == FacilityStatus::OPERATIONAL){
        Plan::addFacility(curr_plan.underConstruction[j]);
        curr_plan.underConstruction.erase(j); //should erase the facility at index j from the vector
    }
    }

    }
}

//to be continued
void Simulation::close(){
    for (int i =0;i < plans.size() ;i+=1){
        cout<<"PlanID: " + plans[i].plan_id<<endl;
        cout<<"SettlementName: " + plans[i].settlement->getName<<endl;
        cout<<"LifeQualityScore: " + plans[i].getlifeQualityScore<<endl;
        cout<<"EconomyScore: " + plans[i].getEconomyScore<<endl;
        cout<<"EnvironmentScore: " + plans[i].getEnvironmentScore<<endl;
    }
}

