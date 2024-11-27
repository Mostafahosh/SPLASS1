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

Simulation::Simulation(const string &configFilePath):isRunning(true),planCounter(0){
    ifstream inputFile(configFilePath);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        
    }
    string line;
    while (getline(inputFile, line)) {
        vector<string> v = Auxiliary::parseArguments(line);  // Split the line into tokens

        if (v.empty()) {
            continue;  // Skip empty lines
        }

        if (v[0] == "settlement") {
            // Create a new Settlement object and add it to the settlements vector
            settlements.push_back(new Settlement(v[1], stoi(v[2])));
        }
        else if(v[0]=="facility"){
            facilitiesOptions.push_back(new FacilityType(v[1],stoi(v[2]),stoi(v[3]),stoi(v[4]),stoi(v[5]),stoi(v[6])));
        }
        else if(v[0] == "plan")
        {
            for (Settlement* s : settlements) {
                if (s->getName() == v[1]) {
                    SelectionPolicy* p = nullptr;

                    if (v[2] == "eco") {
                        p = new EconomySelection();
                    } else if (v[2] == "bal") {
                        p = new BalancedSelection(0, 0, 0);
                    } else if (v[2] == "env") {
                        p = new SustainabilitySelection();
                    } else {
                        p = new NaiveSelection();
                    }

                    // Create a new Plan and add it to the plans vector
                    plans.push_back(new Plan(planCounter, *s, p, facilitiesOptions));
                }
            }
        }



   


    }

    
}
