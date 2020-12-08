#include <cassert>

#include "Manager.h"


// Local Variables:
// mode: c++
// End:

ClassProject::Manager::Manager() {
    BDD_ID nodes_id=0;
    std::unordered_map<BDD_ID,HashCode> unique_table;
    unique_table[0]=HashCode("0",NULL,NULL,NULL);
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