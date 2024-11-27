#include <Plan.h>


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
void Plan::step(){;}
void Plan::printStatus(){;}
const vector<Facility*>& Plan::getFacilities() const {;}
void Plan::addFacility(Facility* Facility){}
const string Plan::toString() const{;}
