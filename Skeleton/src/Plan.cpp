#include <Plan.h>
using namespace std;
#include <iostream>

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
plan_id(planId),settlement(&settlement),status(PlanStatus::AVALIABLE),facilityOptions(facilityOptions),life_quality_score(0),economy_score(0),environment_score(0),selectionPolicy(selectionPolicy){}
// //vector<Facility*> facilities;
// underConstruction = vector<Facility*>; 

 // Copy Constructor
    Plan::Plan(const Plan& other)
        : plan_id(other.plan_id),
          settlement(other.settlement),
          facilityOptions(other.facilityOptions),
          life_quality_score(other.life_quality_score),
          economy_score(other.economy_score),
          environment_score(other.environment_score),
          status(other.status) {

        // Deep copy of the SelectionPolicy object (assuming it has a virtual clone method)
        if (other.selectionPolicy) {
            selectionPolicy = other.selectionPolicy->clone();
        } else {
            selectionPolicy = nullptr;
        }

        // Deep copy of facilities
        for (Facility *facility : other.facilities) {
            facilities.push_back(new Facility(*facility));  // Assuming Facility has a copy constructor
        }

        // Deep copy of facilities under construction
        for (Facility *facility : other.underConstruction) {
            underConstruction.push_back(new Facility(*facility));  // Assuming Facility has a copy constructor
        }
    }

    Plan::~Plan() {
        // Clean up dynamically allocated memory
        delete selectionPolicy;
        for (Facility *facility : facilities) {
            delete facility;
        }
        for (Facility *facility : underConstruction) {
            delete facility;
        }
    }

const int Plan::getlifeQualityScore() const{return life_quality_score;}
const int Plan::getEconomyScore() const {return economy_score;}
const int Plan::getEnvironmentScore() const{return environment_score;}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){selectionPolicy = selectionPolicy;}


void Plan::printStatus()
{
    cout<<"PlanID: "<<this->plan_id<<endl;
    cout<<"SettlementName " <<settlement->getName()<<endl;
    if (status==PlanStatus::AVALIABLE){cout<<"PlanStatus: AVAILABLE"<<endl;}
    else {cout<<"PlanStatus: BUSY"<<endl;}
    cout<<"SelectionPolicy: "<<selectionPolicy->toString()<<endl;
    cout<<"LifeQualityScore: "<<life_quality_score<<endl;
    cout<<"EconomyScore: "<<economy_score<<endl;
    cout<<"EnvrionmentScore: "<<environment_score<<endl;

    for (int i = 0; i < underConstruction.size(); i++)
    {
        cout<<"FacilityName: "<<underConstruction[i]->getName()<<endl;
        cout<<"FacilityStatus: UNDER_CONSTRUCTIONS"<<endl;
    }
    



    for (int i = 0; i < facilities.size(); i++)
    {
        cout<<"FacilityName: "<<facilities[i]->getName()<<endl;
        cout<<"FacilityStatus: OPERATIONAL"<<endl;
            
    }

}

const Settlement &Plan::getSettlementOfPlan() const
{
    return *settlement;
}

const PlanStatus Plan::getStatus() const
{
 return this->status;
}

const vector<Facility*>& Plan::getFacilities() const 
{
    return this->facilities;
}

void Plan::addFacility(Facility* Facility)
{
    if(Facility->getStatus()==FacilityStatus::OPERATIONAL){
        facilities.push_back(Facility);
    }
    else underConstruction.push_back(Facility);
}

const string Plan::toString() const
{
    return "";
}

const int Plan::getID() const
{
    return plan_id;
}

const vector<Facility *> &Plan::getUnderConstructions() const
{
    return underConstruction;
}

//additional methods
void Plan::setPlanStatus(PlanStatus newStatus){
    status=newStatus;
}


void Plan::step(){
    //stage-1
    int consLimit = static_cast<int>(this -> settlement->getType())+1; //because Enums starts from zero

    // //the settlement didn't reached it's construction limit
    // while(this ->underConstruction.size() < consLimit){
    //     FacilityType addFacility (this -> selectionPolicy->selectFacility(facilityOptions));
    //     Facility* newFacility= new Facility(addFacility,settlement->getName());
    //     this -> underConstruction.push_back(newFacility);
    // }
    // this -> status = PlanStatus::BUSY;

    //stage-2
    if(this->status==PlanStatus::AVALIABLE){
         while(this ->underConstruction.size() < consLimit){
             FacilityType addFacility (this -> selectionPolicy->selectFacility(facilityOptions));
             Facility* newFacility= new Facility(addFacility,settlement->getName());
             this->addFacility(newFacility);
         }
    }
    //stage-3
    
        int i=0;
        for (Facility* f:underConstruction)
        {
            
            // f->step();
            if(f->step()==FacilityStatus::OPERATIONAL){
                this->addFacility(f);
                underConstruction.erase(underConstruction.begin()+i);
                i--;
            }
            i++;
        }
        

    //stage-4
    if(underConstruction.size()==consLimit)
    {
        this->setPlanStatus(PlanStatus::BUSY);
    }
    else this->setPlanStatus(PlanStatus::AVALIABLE);
}



const SelectionPolicy* Plan::getSelectionPolicy() const {
    return selectionPolicy;
}



