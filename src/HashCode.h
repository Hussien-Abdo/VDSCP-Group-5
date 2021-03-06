//
// Created by Mohamed Moursi on 08.12.20.
//
/** \file HashCode.h
 * Header file for HashCode class.
 */
#ifndef VDSPROJECT_HASHCODE_H
#define VDSPROJECT_HASHCODE_H

typedef size_t BDD_ID;
/**
 * HashCode class is used to represent the Unique tuple which stores the data of each node in the ROBDD. Data include:
 * - Human readable label
 * - High successor of the node
 * - Low successor of the node
 * - Top_var of the node
 */
class HashCode {
public:

    HashCode();

    HashCode(const std::string &label, BDD_ID high, BDD_ID low, BDD_ID topVar);

    HashCode(const std::string &label);

    const std::string &getLabel() const;

    void setLabel(const std::string &label);

    BDD_ID getHigh() const;

    void setHigh(BDD_ID high);

    BDD_ID getLow() const;

    void setLow(BDD_ID low);

    BDD_ID getTopVar() const;

    void setTopVar(BDD_ID topVar);

    bool operator==(const HashCode &other) const;

private:
    std::string Label;
    BDD_ID High;
    BDD_ID Low;
    BDD_ID Top_Var;
};


#endif //VDSPROJECT_HASHCODE_H
