#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;
        const int getID() const;
        const vector<Facility*> &getUnderConstructions() const;
        const SelectionPolicy* getSelectionPolicy() const; 

        void setPlanStatus(PlanStatus newStatus);
        

        const Settlement& getSettlementOfPlan() const;
        const PlanStatus getStatus() const;
        //Copy//Des
        Plan(const Plan& other);
        ~Plan();
        Plan& operator=(const Plan& other);

    private:
        int plan_id;
        const Settlement *settlement;
        SelectionPolicy* selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
        
        //Additional_Methods
        PlanStatus setPlanStatus();
};

