#include <Action.h>

using namespace std;
#include <iostream>
//BaseAction
BaseAction::BaseAction():errorMsg(""),status(ActionStatus::ERROR){}

ActionStatus BaseAction::getStatus() const
{
    return this->status;
}

void BaseAction::complete()
{
    this->status=ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg)
{
    this->status=ActionStatus::ERROR;
    this->errorMsg=errorMsg;
    cout<<"Error: "<<this->errorMsg<<endl;
}

const string &BaseAction::getErrorMsg() const
{
    return this->errorMsg;
}

//SimulationStep
SimulateStep::SimulateStep(const int numOfSteps):BaseAction(),numOfSteps(numOfSteps){}

void SimulateStep::act(Simulation &simulation) 
{
    for (int i = 0; i < this->numOfSteps; i++)
    {
        simulation.step();
    }
    //assume no errors will happen...
    this->complete();
}

const string SimulateStep::toString() const
{
    if(this->getStatus()==ActionStatus::COMPLETED)
    {
        return "step "+to_string(this->numOfSteps)+" COMPLETED";
    }
    else return "step "+to_string(this->numOfSteps)+" ERROR";
}

SimulateStep *SimulateStep::clone() const
{
    return new SimulateStep(*this); 
}

//AddPlan
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):BaseAction()
,settlementName(settlementName),selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation)
{
    if(simulation.isSettlementExists(settlementName)==false)
    {
        error("Cannot create this plan!");
    }
    else{
    if(this->selectionPolicy=="nve")
    {
        simulation.addPlan(simulation.getSettlement(this->settlementName),new NaiveSelection());
        complete();
    }
    else if(this->selectionPolicy=="bal")
    {
        simulation.addPlan(simulation.getSettlement(this->settlementName),new BalancedSelection(0,0,0));
        complete();
    }
    else if(this->selectionPolicy=="eco")
    {
        simulation.addPlan(simulation.getSettlement(this->settlementName),new EconomySelection());
        complete();
    }
    else if(this->selectionPolicy=="env")
    {
        simulation.addPlan(simulation.getSettlement(this->settlementName),new SustainabilitySelection());
        complete();
    }
    else {error("Cannot create this plan!");}
    }
}

const string AddPlan::toString() const
{
    return "plan "+settlementName;
}

AddPlan *AddPlan::clone() const
{
    return new AddPlan(*this);
}




//AddSettlement
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType) : BaseAction() 
,settlementName(settlementName)
,settlementType(settlementType){}

void AddSettlement::act(Simulation &simulation){
    if(simulation.isSettlementExists(settlementName)){error("settlement already exists!");}

    //create a new settlement and add it to settlements
    Settlement* settAddAction = new Settlement(settlementName,settlementType);
    simulation.addSettlement(settAddAction); 
}


AddSettlement *AddSettlement::clone() const {
    return new AddSettlement(*this);
}

const string AddSettlement::toString() const {
    return "AddSettlement: " + settlementName;
}







//AddFacility
 AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore) : BaseAction()
,facilityName(facilityName) 
,facilityCategory(facilityCategory) 
,price(price)
,lifeQualityScore(lifeQualityScore)
, economyScore(economyScore)
, environmentScore(environmentScore){}

void AddFacility::act(Simulation &simulation){
    //if the facility already exists
    if(simulation.isFacilityExists(facilityName)){return  error("Cannot create this facility!");}

    //if don't creat a new facility and add it to facilityOptions
    FacilityType* facilityAddAction = new FacilityType(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore);

    //the search for the facility will occur twise!?
    simulation.addFacility(*facilityAddAction);
}

AddFacility *AddFacility::clone() const {
    return new AddFacility(*this);
}
const string AddFacility::toString() const {
    return "AddFacility: " + facilityName;
}




//PrintPlanStatus
 PrintPlanStatus::PrintPlanStatus(int planID) : BaseAction()
,planId(planID){}

void PrintPlanStatus::act(Simulation &simulation){
    if(simulation.isPlanExists(planId)){
    Plan actionPlan = simulation.getPlan(planId);
    actionPlan.printStatus();
    complete();}
    else{error("plan does not exist");}

    // Settlement* settPlan = actionPlan.getSettlementOfPlan;
    // cout<<"planID: " <<planId << endl; 
    // cout<<"SettlementName: " <<  settPlan -> getName() << endl;
    // cout<<"PlanStatus: " << actionPlan.getStatus() << endl;
    // cout<<"SelectionPolicy: " << (actionPlan.getSelectionPolicy()) -> toString() <<endl;
    // cout<<"LifeQualityScore: " << actionPlan.getlifeQualityScore() << endl;
    // cout<<"EconomyScore: " << actionPlan.getEconomyScore() << endl;
    // cout<<"EnvironmentScore: " << actionPlan.getEnvironmentScore << endl;

    // vector<Facility*>& planUnderConst = actionPlan.getUnderConstructions();
    // vector<Facility*>& planOperational = actionPlan.getFacilities();

    // for(int i = 0; i < planUnderConst.size() ; i+=1){
    //     cout<<"FacilityName: " <<(planUnderConst[i]) -> getName() << endl;
    //     cout<<"FacilityName: " <<(planUnderConst[i]) -> getStatus() << endl;
    // }

    // for(int j = 0; j < planOperational.size() ; j +=1){
    //     cout<<"FacilityName: " <<(planOperational[j]) -> getName() << endl;
    //     cout<<"FacilityName: " <<(planOperational[j]) -> getStatus() << endl;
    // }

}

PrintPlanStatus *PrintPlanStatus::clone() const
{
    return new PrintPlanStatus(*this);
}

const string PrintPlanStatus::toString() const
{
    return "status has printed successfully";
}


//ChangePlanPolicy
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy) : BaseAction()
, planId(planId)
,newPolicy(newPolicy){}

void ChangePlanPolicy::act(Simulation &simulation){
        Plan actionPlan = simulation.getPlan(planId);
        const SelectionPolicy* oldPolicy = actionPlan.getSelectionPolicy();

//policy toString should return only 3 chars name of the policy - to match outputs
        if(!(simulation.isPlanExists(planId))) {return error ("plan do not exist");}


        const string oldPolicyName = oldPolicy ->toString();
        if(oldPolicyName == newPolicy){return error ("this is the same policy");}
        delete(oldPolicy); //is it right ?

        cout<<"planID: " <<planId << endl; 
        cout<<"PreviousPolicy: " << oldPolicy->toString() <<endl;

        if(newPolicy == "nve"){
            NaiveSelection* nPolicy = new NaiveSelection();
            actionPlan.setSelectionPolicy(nPolicy); //lastIndex should start from 0 and changed accordingly
        }

        else if(newPolicy == "bal"){
            BalancedSelection* bPolicy = new BalancedSelection(0,0,0); //should i pass 0 parametrs or calculate the existing facilites intrebution and add it accordingly ?
actionPlan.setSelectionPolicy(bPolicy);
}

else if(newPolicy == "eco"){
    EconomySelection* ecoPolicy = new EconomySelection();//lastIndex should start from 0 and changed accordingly
    actionPlan.setSelectionPolicy(ecoPolicy);
}

else if(newPolicy == "env"){
    SustainabilitySelection* envPolicy = new SustainabilitySelection();//lastIndex should start from 0 and changed accordingly
    actionPlan.setSelectionPolicy(envPolicy);
}

cout<<"newPolicy: " << newPolicy << endl;
}

ChangePlanPolicy *ChangePlanPolicy::clone() const
{
    return new ChangePlanPolicy(*this);
}

const string ChangePlanPolicy::toString() const
{
    return "SelectionPolicy changed successfully";
}










//PrintActionLogs
//need to add everyAction at the simulation to actionLog vector
PrintActionsLog::PrintActionsLog() : BaseAction() {}
void PrintActionsLog::act(Simulation &simulation){
    vector<BaseAction*> actionLogs = simulation.getActions() ;
    int numOfActions = actionLogs.size() ;
    for (int i = 0; i < numOfActions; i+=1) {
        std::cout << actionLogs[i] -> toString() <<std::endl ;
    }
}

PrintActionsLog *PrintActionsLog::clone() const {
    return new PrintActionsLog(*this);
}

const string PrintActionsLog::toString() const {
    return "PrintActionsLog COMPLETED" ;
}








//Close
Close::Close():BaseAction(){}

void Close::act(Simulation &simulation)
{
    this->complete();
    simulation.close();
}

Close *Close::clone() const
{
    return new Close(*this);
}

const string Close::toString() const
{
    return "Close!";
}





//BackupSimulation
BackupSimulation::BackupSimulation(){}

void BackupSimulation::act(Simulation &simulation)
{
    backup = &(simulation);
}

BackupSimulation *BackupSimulation::clone() const
{
        return new BackupSimulation(*this);

}

const string BackupSimulation::toString() const
{
    return "backup done";
}


RestoreSimulation::RestoreSimulation(){}

void RestoreSimulation::act(Simulation &simulation){
    simulation = *(backup);}


RestoreSimulation *RestoreSimulation::clone() const
{
        return new RestoreSimulation(*this);
}

const string RestoreSimulation::toString() const
{
    return "Restore done";
}


