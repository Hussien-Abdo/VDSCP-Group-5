// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014
/** \file Manager.h
 * Header file for Manager class.
 */
#ifndef mwBDD_H
#define mwBDD_H

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <string>
#include "ManagerInterface.h"
#include "HashCode.h"
#include <tuple>

namespace ClassProject {
/**
 * The Manager class is the main class in this package. It implements ManagerInterface.
 * It contains all BDD package functions. In addition it implements the ROBDD as an unordered_map.
 * The order of the variables -priority- is the insertion order.
 */
    class Manager : public ManagerInterface {

    private:
        BDD_ID node_id; /**< BDD_ID counter, keeps track of last used BDD_ID */
        //std::string node_label; /**<  Internal string used to create label for nodes that represent a function */
        BDD_ID search_result; /**< Used to store the return values for some functions, to return by reference */
        std::unordered_map<BDD_ID, HashCode> unique_table; /**< unordered_map that represents the ROBDD */
        std::map<std::tuple<BDD_ID , BDD_ID, BDD_ID>, BDD_ID> computed_table; /**< Table to store the result of each ite(i,t,e) call */
        BDD_ID trueNode=1;
        BDD_ID falseNode=0;

    public:

        Manager();

        BDD_ID createVar(const std::string &label);

        const BDD_ID &True();

        const BDD_ID &False();

        bool isConstant(const BDD_ID f);

        bool isVariable(const BDD_ID x);

        BDD_ID topVar(const BDD_ID f);

        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e);

        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x);

        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x);

        BDD_ID coFactorTrue(const BDD_ID f);

        BDD_ID coFactorFalse(const BDD_ID f);

        BDD_ID and2(const BDD_ID a, const BDD_ID b);

        BDD_ID or2(const BDD_ID a, const BDD_ID b);

        BDD_ID xor2(const BDD_ID a, const BDD_ID b);

        BDD_ID neg(const BDD_ID a);

        BDD_ID nand2(const BDD_ID a, const BDD_ID b);

        BDD_ID nor2(const BDD_ID a, const BDD_ID b);

        std::string getTopVarName(const BDD_ID &root);

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

        size_t uniqueTableSize();


        BDD_ID &searchUniqueTable(const HashCode &hashCode);

        HashCode getHashCode(BDD_ID id);

        BDD_ID searchComputedTable(BDD_ID i, BDD_ID t, BDD_ID e);

        BDD_ID getHighestVar(std::set<BDD_ID> varsSet);

        void printUniqueTable();

        BDD_ID &FindOrAddToUniqueTable(HashCode &hashCode);
    };

}
#endif