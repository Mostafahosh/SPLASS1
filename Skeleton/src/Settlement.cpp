#include "Settlement.h"

Settlement::Settlement(const string &name, SettlementType type):name(name),type(type){}
const std::string &Settlement::getName() const{return Settlement::name;}
SettlementType Settlement::getType() const{return Settlement::type;}
const std::string Settlement::toString() const {
        return "Name: " + name + ", Type: " + settlementTypeToString(type);
}

const std::string Settlement::settlementTypeToString(SettlementType type)const{
    if (type == SettlementType::VILLAGE){return "village";}
    else if (type == SettlementType:: CITY){return "CITY";}
    else {return "METROPOLI";}
}

