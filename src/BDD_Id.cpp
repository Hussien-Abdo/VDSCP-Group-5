//
// Created by Mohamed Moursi on 01.12.20.
//

#include "BDD_Id.h"

BDD_Id::BDD_Id(int id, const std::string &label, BDD_Id *high, BDD_Id *low, BDD_Id *topVar) {
    ID=id;
    Label=label;
    Top_Var = topVar;
    High=high;
    Low=low;
    Top_Var = topVar;
}

BDD_Id::BDD_Id(int id, const std::string &label, BDD_Id *topVar) {
    ID=id;
    Label=label;
    Top_Var = topVar;
    High=NULL;
    Low=NULL;
}

int BDD_Id::getId() const {
    return ID;
}

void BDD_Id::setId(int id) {
    ID = id;
}

const std::string &BDD_Id::getLabel() const {
    return Label;
}

void BDD_Id::setLabel(const std::string &label) {
    Label = label;
}

BDD_Id *BDD_Id::getHigh() const {
    return High;
}

void BDD_Id::setHigh(BDD_Id *high) {
    High = high;
}

BDD_Id *BDD_Id::getLow() const {
    return Low;
}

void BDD_Id::setLow(BDD_Id *low) {
    Low = low;
}

BDD_Id *BDD_Id::getTopVar() const {
    return Top_Var;
}

void BDD_Id::setTopVar(BDD_Id *topVar) {
    Top_Var = topVar;
}
