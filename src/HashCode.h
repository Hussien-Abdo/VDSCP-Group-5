//
// Created by Mohamed Moursi on 01.12.20.
//
#ifndef VDSPROJECT_HASHCODE_H
#define VDSPROJECT_HASHCODE_H


#include <string>

class HashCode {
public:
    HashCode(const std::string label, HashCode *high, HashCode *low, HashCode *topVar);

    const std::string getLabel() const;

    void setLabel(const std::string label);

    HashCode *getHigh() const;

    void setHigh(HashCode *high);

    HashCode *getLow() const;

    void setLow(HashCode *low);

    HashCode *getTopVar() const;

    void setTopVar(HashCode *topVar);

private:
    std::string Label;
    HashCode *High;
    HashCode *Low;
    HashCode *Top_Var;
};


#endif //VDSPROJECT_HASHCODE_H
