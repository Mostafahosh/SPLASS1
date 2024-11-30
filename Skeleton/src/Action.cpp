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
