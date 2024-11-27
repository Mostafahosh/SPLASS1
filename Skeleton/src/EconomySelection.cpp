#include <SelectionPolicy.h>
#include <iostream>
#include <vector>
#include <string>



EconomySelection::EconomySelection() : lastSelectedIndex(-1){}


const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    int fSize = facilitiesOptions.size();
    if (fSize == 0){throw std::runtime_error("No facilities available for selection.");}

    //make sure to build more facilites than the provided number if needed
    //if(lastSelectedIndex+1  == fSize){lastSelectedIndex = 0;}
    for(int j = 0 ; j < fSize ; j +=1 ){

        FacilityCategory checkCategory = facilitiesOptions[(lastSelectedIndex+1+j)%fSize].getCategory();

        if( checkCategory == FacilityCategory::ECONOMY){
            lastSelectedIndex = (lastSelectedIndex+1+j)%fSize;
            return facilitiesOptions[lastSelectedIndex];
        }

    }
    lastSelectedIndex++;
    return facilitiesOptions[(lastSelectedIndex)%fSize];
}

const string EconomySelection::toString() const{return "EconomySelection";}

EconomySelection* EconomySelection::clone() const {
    return new EconomySelection(*this); 
}

