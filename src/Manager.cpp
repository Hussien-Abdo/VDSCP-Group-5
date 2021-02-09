/** \file Manager.cpp
 * Manager class.
 */
#include "Manager.h"
#include "iostream"
/**
 * Main namespace, contains Manager.cpp class
 */
namespace ClassProject {
    /**
     * A no argument constructor for class manager
     */
    Manager::Manager() {
        node_id = 0;
        unique_table.emplace(std::pair<BDD_ID, HashCode>(0, HashCode("0", 0, 0, 0)));
        reversed_u_table.emplace(std::pair<Container, BDD_ID>(Container(0, 0, 0), 0));
        unique_table.emplace(std::pair<BDD_ID, HashCode>(1, HashCode("1", 1, 1, 1)));
        reversed_u_table.emplace(std::pair<Container, BDD_ID>(Container(1, 1, 1), 1));
//      std::pair<std::tuple<BDD_ID ,BDD_ID ,BDD_ID>, BDD_ID> true_node_r_pair(std::tuple<BDD_ID, BDD_ID, BDD_ID>(1,1,1), 1);
        node_id += 1;

    }

    /**
     * Creates a variable with the specified label
     *
     * @param label to create var for it
     * @return
     */
    BDD_ID Manager::createVar(const std::string &label) {
        node_id++;
//        std::cout << "node_id: " << node_id << "\n";
        HashCode hashCode=HashCode(label, True(), False(), node_id);
        unique_table.emplace(std::pair<BDD_ID, HashCode>(node_id, hashCode));
        reversed_u_table.emplace(std::pair<Container, BDD_ID>(Container(hashCode.getHigh(), hashCode.getLow(), hashCode.getTopVar()), node_id));
        return node_id;
    }

    /**
     * Returns the BDD_ID of the True node i.e 1
     * @return BDD_ID of the True node
     */
    const BDD_ID &Manager::True() {
        return trueNode;
    }

    /**
     * Returns the BDD_ID of the False node i.e 0
     * @return BDD_ID of the False node
     */
    const BDD_ID &Manager::False() {
        return falseNode;
    }

    /**
     * Returns True if f is constant
     *
     * @param f node to check if it's constant or not
     * @return True if f is constant
     */
    bool Manager::isConstant(const BDD_ID f) {
        HashCode hashcode = unique_table[f];
        return (hashcode.getTopVar() == 1 || hashcode.getTopVar() == 0);
    }

    /**
     * Returns True if x is variable
     *
     * @param x node to check if it's a variable or not
     * @return True if x is variable
     */
    bool Manager::isVariable(const BDD_ID x) {
        HashCode hashcode = unique_table[x];
        return (hashcode.getTopVar() == x) && (hashcode.getTopVar() != 1 && hashcode.getTopVar() != 0);
    }

    /**
     * Returns the top variable of node f
     *
     * @param f node to return the top variable for
     * @return the top variable of node f
     */
    BDD_ID Manager::topVar(const BDD_ID f) {
        return unique_table[f].getTopVar();
    }

    /**
     * Performs the ite(i,t,e,) operation on nodes (i,t,e)
     *
     * ite() is the "if then else" operation that can modeled as ite(i, t, e) = i⋅t + !i⋅e it's used here to implement
     * logic operations { and2, or2, xor2, nand2, nor2, neg} and to perform shannon decomposition
     * The implementation is recursion based, the terminal cases are:
     * ite(1, t, e) = t
     * ite(0, t, e) = e
     * ite(i, 1, 0) = i
     * ite(i, f, f) = f
     * ite(i, 0, 1) = !i
     * At the beginning the code checks for the terminal cases if the input is not a terminal case, it then checks if it
     * has already been calculated and stored in computed_table, if it's already calculated the associated BDD_ID is
     * returned. Otherwise it proceeds with getting the highest var for the input functions (i,t, e) and then uses it to
     * coFactorTrue & coFactorFalse each input node. Then ite(i, t, e) is run twice, ite(i.high, t.high, e.high) then
     * ite(i.low, t.low, e.low) if the result of both is equal, the first one is returned, otherwise the result is stored
     * in a HashCode
     * @param i First variable -condition variable-
     * @param t The expected result if i is True
     * @param e The expected result if i is False
     * @return
     */
    BDD_ID Manager::ite(const BDD_ID i, const BDD_ID t, const BDD_ID e) {
        BDD_ID id;
        //Terminal cases
        if (t == 1 && e == 0) {
            return i;
        } else if (i == 1 || t == e) {
            return t;
        } else if (i == 0) {
            return e;
        } else {
            auto it = computed_table.find(Container(i, t, e));
            if (it != computed_table.end()) {
                return it->second;
            }
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
        id = FindOrAddToUniqueTable(node);
        computed_table.emplace(std::pair<Container,BDD_ID>(Container(i, t, e), id));
        return id;
    }

    /**
     * Returns positive cofactor of function f with respect to x
     *
     * Returns the result of substituting x equal to 1 in f as a BDD_ID
     * f = a + (b ∗ c)
     * coFactorTrue(f, c) = a + b
     * Terminal cases:
     *  f or x are constants
     *  topVar(f) > x
     * @param f Function to coFactor
     * @param x Variable or function to coFactor with respect to
     * @return BDD_ID representing the result of the coFactoring
     */
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

    /**
     * Returns negative cofactor of function f with respect to x
     *
     * Returns the result of substituting x equal to 0 in f as a BDD_ID
     * f = a + (b ∗ c)
     * coFactorFalse(f, c) = a
     * Terminal cases:
     *  f or x are constants
     *  topVar(f) > x
     * @param f Function to coFactor
     * @param x Variable or function to coFactor with respect to
     * @return BDD_ID representing the result of the coFactoring
     */
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

    /**
     * Returns the positive cofactor of function f with respect to the highest variable
     *
     * Returns the positive cofactor of function f with respect to the highest order variable in function f
     * @param f Function to coFactor
     * @return BDD_ID representing the result of the coFactoring
     */
    BDD_ID Manager::coFactorTrue(const BDD_ID f) {
        return coFactorTrue(f, topVar(f));
    }

    /**
     * Returns the negative cofactor of function f with respect to the highest variable
     *
     * Returns the negative cofactor of function f with respect to the highest order variable in function f
     * @param f Function to coFactor
     * @return BDD_ID representing the result of the coFactoring
     */
    BDD_ID Manager::coFactorFalse(const BDD_ID f) {
        return coFactorFalse(f, topVar(f));
    }

    /**
     * Performs logical AND operation on a & b
     *
     * Performs logical AND using ite(a, b, 0) and returns BDD_ID of the node representing the result of the operation
     * @param a First node
     * @param b Second node
     * @return BDD_ID of the result
     */
    BDD_ID Manager::and2(const BDD_ID a, const BDD_ID b) {
//        if (isVariable(a) && isVariable(b))
//            node_label += "and(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, b, 0);
    }

    /**
     * Performs logical OR operation on a & b
     *
     * Performs logical OR using ite(a, 1, b) and returns BDD_ID of the node representing the result of the operation
     * @param a First node
     * @param b Second node
     * @return BDD_ID of the result
     */
    BDD_ID Manager::or2(const BDD_ID a, const BDD_ID b) {
//        if (isVariable(a) && isVariable(b))
//            node_label += "or(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, 1, b);
    }

    /**
     * Performs logical XOR operation on a & b
     *
     * Performs logical XOR using ite(a, neg(b), b) and returns BDD_ID of the node representing the result of the operation
     * @param a First node
     * @param b Second node
     * @return BDD_ID of the result
     */
    BDD_ID Manager::xor2(const BDD_ID a, const BDD_ID b) {
//        if (isVariable(a) && isVariable(b))
//            node_label += "xor(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, neg(b), b);
    }

    /**
     * Performs a logical NOT operation on a
     * Performs logical NOT using ite(a, 0, 1) and returns BDD_ID of the node representing the result of the operation
     * @param a Node to negate
     * @return BDD_ID of the result
     */
    BDD_ID Manager::neg(const BDD_ID a) {
        return ite(a, 0, 1);
    }

    /**
     * Performs logical NAND operation on a & b
     *
     * Performs logical NAND using ite(ite(a, b, 0), 0, 1) and returns BDD_ID of the node representing the result of the operation
     * @param a First node
     * @param b Second node
     * @return BDD_ID of the result
     */
    BDD_ID Manager::nand2(const BDD_ID a, const BDD_ID b) {
//        if (isVariable(a) && isVariable(b))
//            node_label += "nand(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, neg(b), 1);
    }

    /**
     * Performs logical NOR operation on a & b
     *
     * Performs logical NOR using ite(ite(a, 1, b), 0, 1) and returns BDD_ID of the node representing the result of the operation
     * @param a First node
     * @param b Second node
     * @return BDD_ID of the result
     */
    BDD_ID Manager::nor2(const BDD_ID a, const BDD_ID b) {
//        if (isVariable(a) && isVariable(b))
//            node_label += "nor(" + unique_table[a].getLabel() + "," + unique_table[b].getLabel() + ")";
        return ite(a, 0, neg(b));
    }

    /**
     * Returns the name -label- of the topVar of node root
     *
     * @param root Node to get its topVar
     * @return name of topVar as string
     */
    std::string Manager::getTopVarName(const BDD_ID &root) {
        BDD_ID topVarId = unique_table[root].getTopVar();
        return unique_table[topVarId].getLabel();
    }

    /**
     * Returns the set of nodes reachable from the given BDD_ID -root- including the node itself
     * @param root Node to get its successors
     * @param nodes_of_root set of BDD_ID to store the result into
     */
    void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {
        nodes_of_root.emplace(root);
        if (!isConstant(root)) {
            findNodes(unique_table[root].getHigh(), nodes_of_root);
            findNodes(unique_table[root].getLow(), nodes_of_root);
        }
    }

    /**
     *  Returns the top var of the given node and the nodes reachable from it
     *
     *  Returns the top var of the given node -root- or the top var of the nodes reachable from node root.
     * @param root Node to get its successors
     * @param vars_of_root set of BDD_ID to store the result into
     */
    void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) {
        if (!isConstant(root)) {
            vars_of_root.emplace(topVar(root));
            findVars(unique_table[root].getHigh(), vars_of_root);
            findVars(unique_table[root].getLow(), vars_of_root);
        }
    }

    /**
     * Returns the size of the unique table
     * @return size of the unique table
     */
    size_t Manager::uniqueTableSize() {
        return unique_table.size();
    }

    /**
     * deprecated
     * Returns the BDD_ID associated with the given HashCode
     *
     * Iterates the unique table looking for a HashCode that matches the given one and returns the BDD_ID associated with it, returns -1 if it's not found.
     * @param hashCode to get its BDD_ID
     * @return BDD_ID if it's found, -1 otherwise.
     */
    BDD_ID Manager::searchUniqueTable(const HashCode &hashCode) {
        auto it = reversed_u_table.find(Container(hashCode.getHigh(), hashCode.getLow(), hashCode.getTopVar()));
        if (it != reversed_u_table.end()) {
            return it->second;
        }
        return -1;
    }

    /**
     *  Returns the HashCode-unique tuple- associated with the given BDD_ID
     * @param id BDD_ID to get its HashCode-unique tuple-
     * @return HashCode associated with the given BDD_ID
     */
    HashCode Manager::getHashCode(BDD_ID id) {
        return unique_table[id];
    }

    /**
     * Adds a HashCode to the UniqueTable or returns its ID if it already exists
     * @param hashCode to add or return its BDD_ID
     * @return The BDD_ID associated with the HashCode
     */
    BDD_ID Manager::FindOrAddToUniqueTable(HashCode &hashCode) {
        auto it = reversed_u_table.find(Container(hashCode.getHigh(), hashCode.getLow(), hashCode.getTopVar()));
        if (it != reversed_u_table.end()) {
            return it->second;
        }
        node_id++;
        unique_table.emplace(std::pair<BDD_ID, HashCode>(node_id,hashCode));
        reversed_u_table.emplace(std::pair<Container, BDD_ID>(Container(hashCode.getHigh(), hashCode.getLow(), hashCode.getTopVar()), node_id));
        return node_id;
    }

    /**
     *  Searches the computedTable for a result of a previously computed ite(i,t,e) operation, Returns -1 if it's not found
     *
     *  Takes as input the parameters of the ite(i,t,e) function, and iterates the computed table looking
     *  for the result of the given parameters -HashCode "Unique tuple"-.
     *  If found returns the BDD_ID of the result of the operation from the UniqueTable, returns -1 otherwise.
     * @param i First parameter of ite(i,t,e)
     * @param t Second parameter of ite(i,t,e)
     * @param e Third parameter of ite(i,t,e)
     * @return BDD_ID of the result in the UniqueTable
     */
    BDD_ID Manager::searchComputedTable(const BDD_ID &i,const BDD_ID &t,const BDD_ID &e) {
        auto it = computed_table.find(Container(i, t, e));
        if (it != computed_table.end()) {
            return it->second;
        }
        return -1;
    }

    /** Takes set of vars and returns the highest priority
     *
     * The priority is defined by the order of insertion in the unique_table
     * @param varsSet Set of variables
     * @return The variable with the highest priority
     */
    BDD_ID Manager::getHighestVar(const std::set<BDD_ID> &varSet) {
        std::set<BDD_ID> setTmp;
        for (auto &element : varSet) {
            if (!isConstant(element))
                setTmp.emplace(element);
        }
        if (setTmp.empty()) {
            throw std::invalid_argument("getHighestVar called with Three constants!!!");
        } else {
            BDD_ID value = *(setTmp.begin());
            for (auto &element : setTmp) {
                if (topVar(element) < topVar(value))
                    value = element;
            }
            return topVar(value);
        }
    }

    /**
     *Prints the Uniqetable
     */
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