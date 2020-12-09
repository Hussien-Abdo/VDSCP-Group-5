#include <cassert>

#include "Manager.h"

// Local Variables:
// mode: c++
// End:
namespace ClassProject {

    Manager::Manager() {
        nodes_id = 0;
        search_result = -1;
        unique_table[0] = HashCode("0", 0, 0, 0);
        unique_table[1] = HashCode("1", 1, 1, 1);
        nodes_id += 1;

    }

    HashCode Manager::getHashCode(BDD_ID id) {
        return unique_table[id];
    }

    BDD_ID Manager::createVar(const std::string &label) {
        nodes_id++;
        unique_table[nodes_id] = HashCode(label,True(),False(),nodes_id);
        return nodes_id;
    }

    const BDD_ID &Manager::True() {
        return searchHashCode(HashCode ("1", 1, 1, 1));
    }

    const BDD_ID &Manager::False() {
        return searchHashCode(HashCode ("0", 0, 0, 0));
    }

    bool Manager::isConstant(const BDD_ID f) {
        HashCode hashcode = unique_table[f];
        return (hashcode.getTopVar() == 1 || hashcode.getTopVar() == 0);
    }

    bool Manager::isVariable(const BDD_ID x) {
        HashCode hashcode = unique_table[x];
        return (hashcode.getTopVar() == x) && (hashcode.getTopVar() !=1 && hashcode.getTopVar() !=0);
    }

    BDD_ID Manager::topVar(const BDD_ID f) {
        return 0;
    }

    BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
        //Terminal cases
        if (i==1 || t==e){
            return t;
        } else if (i==0){
            return e;
        } else if (t==1 && e==01){
            return i;
        } else if (t==0 && e==1){
            return neg(i);
        }
        return 0;
    }

    BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {
        return 0;
    }

    BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {
        return 0;
    }

    BDD_ID Manager::coFactorTrue(const BDD_ID f) {
        return 0;
    }

    BDD_ID Manager::coFactorFalse(const BDD_ID f) {
        return 0;
    }

    BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b) {
        return 0;
    }

    BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b) {
        return 0;
    }

    BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b) {
        return 0;
    }

    BDD_ID Manager::neg(const BDD_ID a) {
        return 0;
    }

    BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b) {
        return 0;
    }

    BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b) {
        return 0;
    }

    std::string Manager::getTopVarName(const BDD_ID &root) {
        BDD_ID topVarId=unique_table[root].getTopVar();
        return unique_table[topVarId].getLabel();
    }

    void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {

    }

    void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {

    }

    size_t Manager::uniqueTableSize() {
        return 0;
    }

// Iterate over an unordered_map using range based for loop
BDD_ID& Manager::searchHashCode(HashCode hashCode){
        for (std::pair<BDD_ID, HashCode> element : unique_table)
        {
            if (element.second ==  hashCode){
                search_result = element.first;
                return search_result;
            }
        }
        return search_result;
    }
}