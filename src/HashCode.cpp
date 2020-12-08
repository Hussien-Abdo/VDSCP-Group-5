//
// Created by Mohamed Moursi on 01.12.20.
//

#include "HashCode.h"

HashCode::HashCode(const std::string label, HashCode *high, HashCode *low, HashCode *topVar) {
    Label=label;
    Top_Var = topVar;
    High=high;
    Low=low;
    Top_Var = topVar;
}

const std::string HashCode::getLabel() const {
    return Label;
}

void HashCode::setLabel(const std::string label) {
    Label = label;
}

HashCode *HashCode::getHigh() const {
    return High;
}

void HashCode::setHigh(HashCode *high) {
    High = high;
}

HashCode *HashCode::getLow() const {
    return Low;
}

void HashCode::setLow(HashCode *low) {
    Low = low;
}

HashCode *HashCode::getTopVar() const {
    return Top_Var;
}

void HashCode::setTopVar(HashCode *topVar) {
    Top_Var = topVar;
}
