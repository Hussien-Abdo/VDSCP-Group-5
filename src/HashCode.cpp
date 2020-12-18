//
// Created by Mohamed Moursi on 08.12.20.
//
/** \file HashCode.cpp
 * HashCode class.
 */
#include <string>
#include "HashCode.h"

/**
 * zero argument constructor
 */
HashCode::HashCode() {};

/**
* Label only constructor
* @param label Human readable label
*/
HashCode::HashCode(const std::string &label) {
    Label = label;
}

/**
 * Full argument constructor
 * @param label Human readable label
 * @param high High successor of the node
 * @param low Low successor of the node
 * @param topVar Top_var of the node
 */
HashCode::HashCode(const std::string &label, BDD_ID high, BDD_ID low, BDD_ID topVar) {
    Label = label;
    High = high;
    Low = low;
    Top_Var = topVar;
}

/**
 * Returns the label of the node represented by the HashCode
 * @return label of the node
 */
const std::string &HashCode::getLabel() const {
    return Label;
}

/**
 * Sets the label of the node
 * @param label string to set as label
 */
void HashCode::setLabel(const std::string &label) {
    Label = label;
}

/**
 * Returns the BDD_ID of the high successor
 * @return BDD_ID of the high successor
 */
BDD_ID HashCode::getHigh() const {
    return High;
}

/**
 * Sets the high successor of the node
 * @param high BDD_ID to set as high successor
 */
void HashCode::setHigh(BDD_ID high) {
    High = high;
}

/**
 * Returns the BDD_ID of the low successor
 * @return BDD_ID of the low successor
 */
BDD_ID HashCode::getLow() const {
    return Low;
}

/**
 * Sets the low successor of the node
 * @param low BDD_ID to set as low successor
 */
void HashCode::setLow(BDD_ID low) {
    Low = low;
}

/**
 * Returns the topVar
 * @return BDD_ID of the topVar
 */
BDD_ID HashCode::getTopVar() const {
    return Top_Var;
}

/**
 * Sets the topVar
 * @param topVar BDD_ID to set as topVar
 */
void HashCode::setTopVar(BDD_ID topVar) {
    Top_Var = topVar;
}

/**
 * Overloading the == operator to compare HashCode objects
 * @param other
 * @return
 */
bool HashCode::operator==(const HashCode &other) const {
    return this->getTopVar() == other.getTopVar() && this->getHigh() == other.getHigh() &&
           this->getLow() == other.getLow();
}
