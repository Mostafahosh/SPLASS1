#include <SelectionPolicy.h>
#include <iostream>
#include <vector>
#include <string>


NaiveSelection::NaiveSelection() : lastSelectedIndex (0){}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    int fSize = facilitiesOptions.size();
    if (fSize == 0){throw std::runtime_error("No facilities available for selection.");}


    //make sure to build more facilites than the provided number if needed
    if(lastSelectedIndex + 1 == fSize){lastSelectedIndex = 0;}
    for(int j = lastSelectedIndex ; j < fSize ; j +=1 ){
        lastSelectedIndex += j;
        return facilitiesOptions[lastSelectedIndex - 1];
    }
}

const string NaiveSelection::toString() const{return "NaiveSelection";}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this); 
}
