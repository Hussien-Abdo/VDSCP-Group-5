#include <cassert>

#include "Manager.h"

// Local Variables:
// mode: c++
// End:
namespace ClassProject {

    Manager::Manager() {
        node_id = 0;
        search_result = -1;
        //computed_table[HashCode("", 0, 0, 0)] = 0;
        unique_table[0] = HashCode("0", 0, 0, 0);
        unique_table[1] = HashCode("1", 1, 1, 1);
        node_id += 1;

    }

    HashCode Manager::getHashCode(BDD_ID id) {
        return unique_table[id];
    }

    BDD_ID Manager::createVar(const std::string &label) {
        node_id++;
        unique_table[node_id] = HashCode(label,True(),False(),node_id);
        return node_id;
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
        return unique_table[f].getTopVar();
    }

    BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
        //Terminal cases
        if (t==1 && e==0) {
            return i;
        } else if (i==1 || t==e){
            return t;
        } else if (i==0){
            return e;
        } else if (t==0 && e==1){
            return 0;
        }else {
            try {
                //return computed_table.at(HashCode("",i,t,e));    // vector::at throws an out-of-range
            }
            catch (const std::out_of_range& oor) {
                  BDD_ID top_var = node_id;
//                BDD_ID new_top_var = 2;
//                if (isVariable(new_top_var)){
//                    if (current_top_var > topVar(new_top_var))
//                        current_top_var = new_top_var;
//                    }
//
                BDD_ID i_topVarTrue = coFactorTrue(i,top_var);
                BDD_ID i_topVarFalse= coFactorFalse(i,top_var);
                BDD_ID t_topVarTrue= coFactorTrue(t,top_var);
                BDD_ID t_topVarFalse = coFactorFalse(t,top_var);
                BDD_ID e_topVarTrue= coFactorTrue(e,top_var);
                BDD_ID e_topVarFalse = coFactorFalse(e,top_var);
                BDD_ID r_high = ite(i_topVarTrue, t_topVarTrue, e_topVarTrue);
                BDD_ID r_low = ite(i_topVarFalse,t_topVarFalse, e_topVarFalse);
                if (r_high==r_low ){
                    return r_high;
                }
                node_id++;
                node = std::to_string(node_id);
                unique_table[node_id] = HashCode(node,r_low,r_high, top_var);
                //computed_table[HashCode(node, i, t, e)] = node_id;
                return node_id;
            }
        }
    }

    BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {
        if (isConstant(f) || isConstant(x) || topVar(f)>x){
            return f;
        }
        if (topVar(f)==x){
            return unique_table[f].getHigh();
        } else {
            BDD_ID T = coFactorTrue(unique_table[f].getHigh(),x);
            BDD_ID F = coFactorTrue(unique_table[f].getLow(),x);
            return ite(topVar(f),T, F);
        }
    }

    BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {
        if (isConstant(f) || isConstant(x) || topVar(f)>x){
            return f;
        }
        if (topVar(f)==x){
            return unique_table[f].getLow();
        } else {
            BDD_ID T = coFactorFalse(unique_table[f].getHigh(),x);
            BDD_ID F = coFactorFalse(unique_table[f].getLow(),x);
            return ite(topVar(f),T, F);
        }
    }

    BDD_ID Manager::coFactorTrue(const BDD_ID f) {
        return 0;
    }

    BDD_ID Manager::coFactorFalse(const BDD_ID f) {
        return 0;
    }

    BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b) {
        return ite(a, b,0);
    }

    BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b) {
        return ite(a,1, b);
    }

    BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b) {
        return ite(a,neg(b), b);
    }

    BDD_ID Manager::neg(const BDD_ID a) {
        return ite(a,0,1);
    }

    BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b) {
        return ite(ite(a, b,0),0,1);
    }

    BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b) {
        return ite(ite(a,1, b),0,1);
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