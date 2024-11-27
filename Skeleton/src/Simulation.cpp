#include <Simulation.h>



void Simulation::start(){cout<<"The simulation has started"<<endl;} //maybe add another things to the start

void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy){
    Plan newPlan = new Plan(planCounter,settlement,selectionPolicy,facilitiesOptions);
    plans.push_back(newPlan);
}

//void Simulation::addAction(){}

bool Simulation::addSettlement(Settlement* settlement){
    //checking if there is other settlement with the same name
    for(int i = 0; i <settlements.size() ; i+=1){
        if((*settlement).getName == (settlements[i] -> getName)){return false;}   
         }

    settlements.push_back(settlement);
    return true;
}


bool Simulation::addFacility(FacilityType facility){
    //checking if there is other facility with the same name
    for(int i = 0; i <facilitiesOptions.size() ; i+=1){
        if((facility).getName == (facilitiesOptions[i]->getName)){return false;}   
         }
    facilitiesOptions.push_back(facility);
    return true;
}


bool Simulation::isSettlementExists(const string &settlementName){
    for(int i = 0; i <settlements.size() ; i+=1){
        if(settlementName == (settlements[i] -> getName)){return true;}   
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
        if(plans[i].plan_id == planID){return plans[i]}
    }
}


void Simulation::step(){
    Plan& curr_plan = plans[i];

    for(int i = 0; i < plans.size() ;i+=1){
        if(curr_plan.printStatus == PlanStatus::AVALIABLE){//check if the cout is string or Enum
          curr_plan.step()
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






