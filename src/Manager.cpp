#include "Manager.h"
#include "iostream"

namespace ClassProject {

    Manager::Manager() {
        std::string node_label = "";
        node_id = 0;
        unique_table[0] = HashCode("0", 0, 0, 0);
        unique_table[1] = HashCode("1", 1, 1, 1);
        node_id += 1;

    }

    BDD_ID Manager::createVar(const std::string &label) {
        node_id++;
        unique_table[node_id] = HashCode(label, True(), False(), node_id);
        return node_id;
    }

    const BDD_ID &Manager::True() {
        search_result = 1;
        return search_result;
    }

    const BDD_ID &Manager::False() {
        search_result = 0;
        return search_result;
    }

    bool Manager::isConstant(const BDD_ID f) {
        HashCode hashcode = unique_table[f];
        return (hashcode.getTopVar() == 1 || hashcode.getTopVar() == 0);
    }

    bool Manager::isVariable(const BDD_ID x) {
        HashCode hashcode = unique_table[x];
        return (hashcode.getTopVar() == x) && (hashcode.getTopVar() != 1 && hashcode.getTopVar() != 0);
    }

    BDD_ID Manager::topVar(const BDD_ID f) {
        return unique_table[f].getTopVar();
    }

    BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
        //Terminal cases
        if (t == 1 && e == 0) {
            return i;
        } else if (i == 1 || t == e) {
            return t;
        } else if (i == 0) {
            return e;
        } else if (!isConstant(i) && t == 0 && e == 1) {                    //negate case
            node_label = unique_table[i].getLabel();
            if (node_label[0] == '!') node_label.erase(node_label.begin()); else node_label = "!" + node_label;
            HashCode not_i = HashCode("", unique_table[i].getLow(), unique_table[i].getHigh(), topVar(i));
            node_id = FindOrAddToUniqueTable(not_i);
            return node_id;
        } else {
            BDD_ID result = searchComputedTable(i, t, e);
            if (result != -1)
                return result;
        }
        BDD_ID ite_top_var = getHighestVar(std::set<BDD_ID>{i, t, e});
        BDD_ID i_topVarTrue = coFactorTrue(i, ite_top_var);
        BDD_ID i_topVarFalse = coFactorFalse(i, ite_top_var);
        BDD_ID t_topVarTrue = coFactorTrue(t, ite_top_var);
        BDD_ID t_topVarFalse = coFactorFalse(t, ite_top_var);
        BDD_ID e_topVarTrue = coFactorTrue(e, ite_top_var);
        BDD_ID e_topVarFalse = coFactorFalse(e, ite_top_var);
        BDD_ID r_high = ite(i_topVarTrue, t_topVarTrue, e_topVarTrue);
        BDD_ID r_low = ite(i_topVarFalse, t_topVarFalse, e_topVarFalse);
        if (r_high == r_low) {
            return r_high;
        }
        HashCode node = HashCode("", r_high, r_low, ite_top_var);
        node_id = FindOrAddToUniqueTable(node);
        std::array<BDD_ID, 4> ite_result = {i, t, e, node_id};
        computed_table.push_back(ite_result);
        return node_id;
    }


    BDD_ID Manager::coFactorTrue(const BDD_ID f, BDD_ID x) {
        if (isConstant(f) || isConstant(x) || topVar(f) > x) {
            return f;
        }
        if (topVar(f) == x) {
            return unique_table[f].getHigh();
        } else {
            BDD_ID T = coFactorTrue(unique_table[f].getHigh(), x);
            BDD_ID F = coFactorTrue(unique_table[f].getLow(), x);
            return ite(topVar(f), T, F);
        }
    }

    BDD_ID Manager::coFactorFalse(const BDD_ID f, BDD_ID x) {
        if (isConstant(f) || isConstant(x) || topVar(f) > x) {
            return f;
        }
        if (topVar(f) == x) {
            return unique_table[f].getLow();
        } else {
            BDD_ID T = coFactorFalse(unique_table[f].getHigh(), x);
            BDD_ID F = coFactorFalse(unique_table[f].getLow(), x);
            return ite(topVar(f), T, F);
        }
    }

    BDD_ID Manager::coFactorTrue(const BDD_ID f) {
        return coFactorTrue(f, topVar(f));
    }

    BDD_ID Manager::coFactorFalse(const BDD_ID f) {
        return coFactorFalse(f, topVar(f));
    }

    BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b) {
        if (isVariable(a) && isVariable(b))
            node_label += "and(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, b, 0);
    }

    BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b) {
        if (isVariable(a) && isVariable(b))
            node_label += "or(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, 1, b);
    }

    BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b) {
        if (isVariable(a) && isVariable(b))
            node_label += "xor(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, neg(b), b);
    }

    BDD_ID Manager::neg(const BDD_ID a) {
        return ite(a, 0, 1);
    }

    BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b) {
        if (isVariable(a) && isVariable(b))
            node_label += "nand(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, neg(b), 1);
    }

    BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b) {
        if (isVariable(a) && isVariable(b))
            node_label += "nor(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a,0, neg(b));
    }

    std::string Manager::getTopVarName(const BDD_ID &root) {
        BDD_ID topVarId = unique_table[root].getTopVar();
        return unique_table[topVarId].getLabel();
    }

    void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
        if (!isConstant(root)) {
            nodes_of_root.insert(root);
            findNodes(unique_table[root].getHigh(), nodes_of_root);
            findNodes(unique_table[root].getLow(), nodes_of_root);
        }
    }

    void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
        if (!isConstant(root)) {
            vars_of_root.insert(topVar(root));
            findVars(unique_table[root].getHigh(), vars_of_root);
            findVars(unique_table[root].getLow(), vars_of_root);
        }
    }

    size_t Manager::uniqueTableSize() {
        return unique_table.size();
    }

    BDD_ID &Manager::searchUniqueTable(const HashCode &hashCode) {
        for (std::pair<BDD_ID, HashCode> element : unique_table) {
            if (element.second == hashCode) {
                search_result = element.first;
                return search_result;
            }
        }
        search_result = -1;
        return search_result;
    }

    HashCode Manager::getHashCode(BDD_ID id) {
        return unique_table[id];
    }

    BDD_ID &Manager::FindOrAddToUniqueTable(HashCode &hashCode) {
        search_result = searchUniqueTable(hashCode);
        if (search_result != -1) {
            return search_result;
        }
        if (unique_table[node_id].getLabel() == "f" && node_label[0] != '!') unique_table[node_id].setLabel("");
        node_id++;
        if (node_label == "") node_label += "f";
        unique_table[node_id] = HashCode(hashCode);
        unique_table[node_id].setLabel(node_label);
        node_label = "";
        return node_id;
    }

    BDD_ID Manager::searchComputedTable(BDD_ID i, BDD_ID t, BDD_ID e) {
        for (std::array<BDD_ID, 4> element: computed_table) {
            if (element[0] == i && element[1] == t && element[2] == e)
                return element[3];
        }
        return -1;
    }

    BDD_ID Manager::getHighestVar(std::set<BDD_ID> varsSet) {
        BDD_ID result;
        for (std::set<BDD_ID>::iterator it = varsSet.begin(); it != varsSet.end();) {
            if (isConstant(*it)) {
                it = varsSet.erase(it);
            } else
                it++;
        }
        result = *varsSet.begin();
        for (BDD_ID element:varsSet) {
            if (topVar(element) < topVar(result))
                result = element;
        }
        return topVar(result);
    }

    void Manager::printUniqueTable() {
        printf("%*s %*s %*s %*s %*s %*s\n", 16, "ID", 16, "Label", 16, "High", 16,
               "Low", 16, "TopVar", 16, "TopVarName");
        for (std::pair<BDD_ID, HashCode> element : unique_table) {
            printf("%*ld %*s %*ld %*ld %*ld %*s\n", 16, element.first, 16, element.second.getLabel().c_str(), 16,
                   element.second.getHigh(), 16,
                   element.second.getLow(), 16, element.second.getTopVar(), 16,
                   getTopVarName(element.second.getTopVar()).c_str());
        }
    }

}