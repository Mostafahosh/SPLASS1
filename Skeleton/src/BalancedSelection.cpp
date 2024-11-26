#include <SelectionPolicy.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int maxOfThree(int a, int b, int c)
{
    return std::max(a, std::max(b, c));
}

int minOfThree(int a, int b, int c)
{
    return std::min(a, std::min(b, c));
}

BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
    : LifeQualityScore(LifeQualityScore),
      EconomyScore(EconomyScore),
      EnvironmentScore(EnvironmentScore) {}

const FacilityType &BalancedSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    int fSize = facilitiesOptions.size();
    int result_indx = -1;
    int min_dif = std::numeric_limits<int>::max(); // Maximum value for int

    int tmpQuality = 0;
    int tmpEco = 0;
    int tmpEnv = 0;

    for (int j = 0; j < fSize; j += 1)
    {
        FacilityType curr_facility = facilitiesOptions[j];
        int facilityQ = curr_facility.getLifeQualityScore();
        int facilityEco = curr_facility.getEconomyScore();
        int facilityEnv = curr_facility.getEnvironmentScore();

        tmpQuality = LifeQualityScore + facilityQ;
        tmpEco = EconomyScore + facilityEco;
        tmpEnv = EnvironmentScore + facilityEnv;

        int dif = maxOfThree(tmpQuality, tmpEco, tmpEnv) - minOfThree(tmpQuality, tmpEco, tmpEnv);

        if (dif < min_dif)
        {
            min_dif = dif;
            result_indx = j;
        }
    }

    return facilitiesOptions[result_indx];
}



const string BalancedSelection::toString() const{return "BalancedSelection";}

BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this); 
}
