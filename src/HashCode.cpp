//
// Created by habi on 08.12.20.
//

#include <string>
#include "HashCode.h"
HashCode::HashCode(){};

HashCode::HashCode(const std::string &label) {
    Label=label;
}

HashCode::HashCode(const std::string &label, BDD_ID high, BDD_ID low, BDD_ID topVar) {
Label=label;
High=high;
Low=low;
Top_Var=topVar;
}

const std::string &HashCode::getLabel() const {
    return Label;
}

void HashCode::setLabel(const std::string &label) {
    Label = label;
}

BDD_ID HashCode::getHigh() const {
    return High;
}

void HashCode::setHigh(BDD_ID high) {
    High = high;
}

BDD_ID HashCode::getLow() const {
    return Low;
}

void HashCode::setLow(BDD_ID low) {
    Low = low;
}

BDD_ID HashCode::getTopVar() const {
    return Top_Var;
}

void HashCode::setTopVar(BDD_ID topVar) {
    Top_Var = topVar;
}

bool HashCode::operator==(const HashCode &other) const {
    return this->getTopVar()==other.getTopVar()&&this->getHigh()==other.getHigh()&&this->getLow()==other.getLow();
}
