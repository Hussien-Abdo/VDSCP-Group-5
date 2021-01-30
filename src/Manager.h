// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014
/** \file Manager.h
 * Header file for Manager class.
 */
#ifndef mwBDD_H
#define mwBDD_H

#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
#include "ManagerInterface.h"
#include "Container.h"
#include "HashCode.h"
#include <boost/functional/hash.hpp>

namespace ClassProject {
/**
 * The Manager class is the main class in this package. It implements ManagerInterface.
 * It contains all BDD package functions. In addition it implements the ROBDD as an unordered_map.
 * The order of the variables -priority- is the insertion order.
 */
    class Manager : public ManagerInterface {

    private:
        struct Container_Hash{
            std::size_t operator()(Container const& container3BddId) const noexcept{
                std::size_t seed=0;
                boost::hash_combine(seed, container3BddId.getE1());
                boost::hash_combine(seed, container3BddId.getE2());
                boost::hash_combine(seed, container3BddId.getE3());
                return seed;
            }
        };
        BDD_ID node_id; /**< BDD_ID counter, keeps track of last used BDD_ID */
        std::unordered_map<BDD_ID, HashCode> unique_table; /**< unordered_map that represents the ROBDD */
        std::unordered_map<Container, BDD_ID,Container_Hash> computed_table; /**< Table to store the result of each ite(i,t,e) call */
        std::unordered_map<Container, BDD_ID,Container_Hash> reversed_u_table; /**< Table to store the result of each ite(i,t,e) call */
        BDD_ID trueNode = 1;
        BDD_ID falseNode = 0;

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


        BDD_ID searchUniqueTable(const HashCode &hashCode);

        HashCode getHashCode(BDD_ID id);

        BDD_ID searchComputedTable(const BDD_ID &i,const BDD_ID &t,const BDD_ID &e);

        BDD_ID getHighestVar(const std::set<BDD_ID> &varsSet);

        void printUniqueTable();

        BDD_ID FindOrAddToUniqueTable(HashCode &hashCode);
    };

}
#endif