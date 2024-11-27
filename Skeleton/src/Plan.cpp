#include <Plan.h>


Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
plan_id = planId;
*settlement = &settlement; (//the field is a pointer and we were given a ref)
selectionPolicy = selectionPolicy;
status = PlanStatus::AVALIABLE;
//vector<Facility*> facilities;
underConstruction = vector<Facility*>; 
facilityOptions = facilityOptions;
life_quality_score = 0;
economy_score = 0;
environment_score = 0;

const int Plan::getlifeQualityScore() const{return life_quality_score;}
const int Plan::getEconomyScore() const {return economy_score;}
cont int Plan::getEnvironmentScore() const{return environment_score;}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){selectionPolicy = selectionPolicy;}

void Plan::printStatus(cout<< Plan::status<<endl);

const vector<Facility*>& Plan::getFacilities() const {;}
void Plan::addFacility(Facility* Facility){Plan::facilities.push_back(Facility);}
const string Plan::toString() const{;}



//additional methods
Plan::setPlanStatus(){
    ((*settlement).getType+1) == underConstruction.size()
    status = PlanStatus::BUSY;
}


void Plan::step(){
    int consLimit = this -> settlement->getType + 1; //because Enums starts from zero

    //the settlement didn't reached it's construction limit
    while(this ->underConstruction.size() < consLimit){
        FacilityType& addFacility = this -> selectionPolicy->selectFacility();
        this -> underConstruction.push_back(addFacility);
    }
    this -> status = PlanStatus::BUSY;
}


