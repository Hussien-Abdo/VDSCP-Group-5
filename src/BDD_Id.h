//
// Created by Mohamed Moursi on 01.12.20.
//
#ifndef VDSPROJECT_BDD_ID_H
#define VDSPROJECT_BDD_ID_H


#include <string>

class BDD_Id {
public:
    BDD_Id(int id, const std::string &label, BDD_Id *high, BDD_Id *low, BDD_Id *topVar);

    BDD_Id(int id, const std::string &label, BDD_Id *topVar);

    int getId() const;

    void setId(int id);

    const std::string &getLabel() const;

    void setLabel(const std::string &label);

    BDD_Id *getHigh() const;

    void setHigh(BDD_Id *high);

    BDD_Id *getLow() const;

    void setLow(BDD_Id *low);

    BDD_Id *getTopVar() const;

    void setTopVar(BDD_Id *topVar);

private:
    int ID;
    std::string Label;
    BDD_Id *High;
    BDD_Id *Low;
    BDD_Id *Top_Var;
};


#endif //VDSPROJECT_BDD_ID_H
