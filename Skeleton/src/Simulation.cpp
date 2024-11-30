#include <Simulation.h>
#include <Auxiliary.h>
#include <Plan.h>
#include <SelectionPolicy.h>
#include <Facility.h>
#include <Settlement.h>
#include <Action.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0)
{

    // the constructor open the config file located in configFilePath
    // it will read line by line into line variable
    std::ifstream configFile(configFilePath);

    if (!configFile.is_open())
    {
        std::cerr << "Error: Could not open configuration file: " << configFilePath << std::endl;
        return;
    }

    std::string line;
    cout<<line<<endl;

    // getline reads until newline character
    // istringstream  allowing extraction of words and data
    // the first word in the line (type) determines the kind of object to creat
    while (getline(configFile, line))
    {
         std::cout << "Reading line: " << line << std::endl;  // Debugging line to see the content of each line read

        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "settlement")
        {

            std::string settlementName;
            int settlementType;
            ss >> settlementName >> settlementType;
            SettlementType settlementTypeEnum = static_cast<SettlementType>(settlementType); // casting int to enum

            // Create a new Settlement object and add it to the settlements vector
            Settlement* settlementAdd = new Settlement(settlementName, settlementTypeEnum);
            Simulation::addSettlement(settlementAdd);
             //cout << "the new settlement name is: " << settlementName << endl;
             //cout << "the new settlement Type is: " << settlementType << endl;
        }

        else if (type == "facility")
        {
            std::string facilityName;
            int facilityCategory;
            int facilityPrice;
            int facilityQuality;
            int facilityEco;
            int facilityEnv;

            ss >> facilityName >> facilityCategory >> facilityPrice >> facilityQuality >> facilityEco >> facilityEnv;
            FacilityCategory facilityCategoryEnum = static_cast<FacilityCategory>(facilityCategory); // casting int to enum
            FacilityType *addFacility = new FacilityType(facilityName, facilityCategoryEnum, facilityPrice, facilityQuality, facilityEco, facilityEnv);
            Simulation::facilitiesOptions.push_back(*addFacility);
            //cout << "the new facility name is: " << facilityName << facilityCategory<<facilityPrice<<facilityQuality<<facilityEco<<facilityEnv<<endl;
        }

        else if (type == "plan")
        {
            std::string settName;
            std::string selectionP;
            ss >> settName >> selectionP;

            Settlement* settPlan;
            SelectionPolicy* policyPlan;

            // finding the settlement to mach it to the plan
            for (int i = 0; i < settlements.size(); i += 1)
            {
                if (settlements[i]->getName() == settName)
                {
                    settPlan = (settlements[i]);
                    break;
                }
            }

            //choose the right selection policiy
            if (selectionP == "nve")
            {
                policyPlan = new NaiveSelection();
            }
            else if (selectionP == "bal")
            {
                policyPlan = new BalancedSelection(0, 0, 0);
            }
            else if (selectionP == "eco")
            {
                policyPlan = new EconomySelection();
            }
            else
            {
                policyPlan = new SustainabilitySelection();
            }

            Simulation::addPlan(settPlan , policyPlan);
        }
    }
//tests//    
//     for(int i =0 ; i < settlements.size() ; i +=1){
//         cout<<settlements[i] -> toString() <<endl;
//         cout<<" "<<endl;}
//    for(int i =0 ; i < facilitiesOptions.size() ; i +=1){cout<<facilitiesOptions[i].getName() <<endl;
//    cout<<" "<<endl;}
//     for(int i =0 ; i < plans.size() ; i +=1){plans[i].printStatus();
//     cout<<" "<<endl;}
    configFile.close();
}



void Simulation::start()
{
    cout << "The simulation has started" << endl;
    std::cout << "Entering Simulation::start() method..." << std::endl;
    Simulation::open();
    while(isRunning){
        string commandLine;
        cout << "Enter a command: ";
        getline(std::cin, commandLine); // Reading a line of input
        cout << "You entered: \"" << commandLine <<"\""<< std::endl;
        processingInput(commandLine);
    }

} // maybe add another things to the start




void Simulation::addPlan(const Settlement *settlement, SelectionPolicy *selectionPolicy)
{
    Plan* newPlan = new Plan(planCounter,*(settlement),selectionPolicy,facilitiesOptions);
    plans.push_back(*newPlan);
    Simulation::planCounter += 1;
}

void Simulation::addAction(BaseAction *action) {}

bool Simulation::addSettlement(Settlement *settlement)
{
    //checking if there is other settlement with the same name
        for(int i = 0; i <settlements.size() ; i+=1){
            if(settlement -> getName() == (settlements[i] -> getName())){return false;}
           }

        settlements.push_back(settlement);
        return true;
}

bool Simulation::addFacility(FacilityType facility)
{
       //checking if there is other facility with the same name
        for(int i = 0; i <facilitiesOptions.size() ; i+=1){
            if(facility.getName() == facilitiesOptions[i].getName()){return false;}
             }
        facilitiesOptions.push_back(facility);
        return true;
}

bool Simulation::isSettlementExists(const string &settlementName)
{
        for(int i = 0; i <settlements.size() ; i+=1){
            if(settlementName == (settlements[i] -> getName())){return true;}
             }
             return false;
}

Settlement* Simulation::getSettlement(const string &settlementName)
{
        for(int i =0; i < settlements.size() ; i+=1){
            if(settlements[i] -> getName() == settlementName){return settlements[i];}
        }
}

Plan& Simulation::getPlan(const int planID)
{
        for(int i=0 ; i<plans.size(); i+=1){
            if(plans[i].getID() == planID){return plans[i];}
        }
}

void Simulation::step()
{
    for(Plan p:plans)
    {
        p.step();//implmention is in each plan step
    }
   
}

// to be continued
void Simulation::close()
{
        this->isRunning=false;
         for (int i =0;i < plans.size() ;i+=1){
             plans[i].printStatus();
         }
}

void Simulation::open() {isRunning = true;}


void Simulation::processingInput(std::string& userCommand){
        istringstream ss(userCommand);
        string input;
        ss >> input;
        //SimulateStep
        if(input == "step"){
            int numOfSteps;
            ss>>numOfSteps;
            SimulateStep *action=new SimulateStep(numOfSteps);
            action->act(*this);
            this->actionsLog.push_back(action);
        }
        //AddPlan
        if(input=="plan")
        {
            string settName,policy;
            ss>>settName;
            ss>>policy;
            AddPlan *action=new AddPlan(settName,policy);
            action->act(*this);
            this->actionsLog.push_back(action);
        }
        //Close
        if(input=="close")
        {
            Close* action=new Close();
            action->act(*this);
            this->actionsLog.push_back(action);
        }
}