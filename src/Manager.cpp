#include <cassert>

#include "Manager.h"


// Local Variables:
// mode: c++
// End:

ClassProject::Manager::Manager() {
    nodes_id=0;
    HashCode a=HashCode("0",NULL,NULL,NULL);
    unique_table[0]=a;
    unique_table[1]=HashCode("1",NULL,NULL,NULL);
    nodes_id+=2;
}

ClassProject::BDD_ID ClassProject::Manager::createVar(const std::string &label) {
    return 0;
}

const ClassProject::BDD_ID &ClassProject::Manager::True() {
    return 1;
}

const ClassProject::BDD_ID &ClassProject::Manager::False() {
    return 0;
}

bool ClassProject::Manager::isConstant(const ClassProject::BDD_ID f) {
    return false;
}

bool ClassProject::Manager::isVariable(const ClassProject::BDD_ID x) {
    return false;
}

ClassProject::BDD_ID ClassProject::Manager::topVar(const ClassProject::BDD_ID f) {
    return 0;
}

ClassProject::BDD_ID
ClassProject::Manager::ite(const ClassProject::BDD_ID i, const ClassProject::BDD_ID t, const ClassProject::BDD_ID e) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(const ClassProject::BDD_ID f, ClassProject::BDD_ID x) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(const ClassProject::BDD_ID f, ClassProject::BDD_ID x) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorTrue(const ClassProject::BDD_ID f) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::coFactorFalse(const ClassProject::BDD_ID f) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::and2(const ClassProject::BDD_ID a, const ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::or2(const ClassProject::BDD_ID a, const ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::xor2(const ClassProject::BDD_ID a, const ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::neg(const ClassProject::BDD_ID a) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::nand2(const ClassProject::BDD_ID a, const ClassProject::BDD_ID b) {
    return 0;
}

ClassProject::BDD_ID ClassProject::Manager::nor2(const ClassProject::BDD_ID a, const ClassProject::BDD_ID b) {
    return 0;
}

std::string ClassProject::Manager::getTopVarName(const ClassProject::BDD_ID &root) {
    return std::string();
}

void ClassProject::Manager::findNodes(const ClassProject::BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {

}

void ClassProject::Manager::findVars(const ClassProject::BDD_ID &root, std::set<BDD_ID> &vars_of_root) {

}

size_t ClassProject::Manager::uniqueTableSize() {
    return 0;
}
