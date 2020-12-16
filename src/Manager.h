// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Written by Markus Wedler 2014

#ifndef mwBDD_H
#define mwBDD_H

#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include "ManagerInterface.h"
#include "HashCode.h"

namespace ClassProject {
    class Manager : public ManagerInterface {

    private:
        BDD_ID node_id;
        std::string node_label;
        BDD_ID search_result;
        std::unordered_map<BDD_ID, HashCode> unique_table;
        std::vector<std::array<BDD_ID, 4>> computed_table;

    public:
        /**
         * A no argument constructor for class manager
         */
        Manager();

        /**
         * Creates a variable with the specified label
         *
         * @param label to create var for it
         * @return
         */
        BDD_ID createVar(const std::string &label);

        /**
         * Returns the BDD_ID of the True node i.e 1
         * @return BDD_ID of the True node
         */
        const BDD_ID &True();

        /**
         * Returns the BDD_ID of the False node i.e 0
         * @return BDD_ID of the False node
         */
        const BDD_ID &False();

        /**
         * Returns True if f is constant
         *
         * @param f node to check if it's constant or not
         * @return True if f is constant
         */
        bool isConstant(const BDD_ID f);

        /**
         * Returns True if x is variable
         *
         * @param x node to check if it's a variable or not
         * @return True if x is variable
         */
        bool isVariable(const BDD_ID x);

        /**
         * Returns the top variable of node f
         *
         * @param f node to return the top variable for
         * @return the top variable of node f
         */
        BDD_ID topVar(const BDD_ID f);

        /**
         * Performs the ite(i,t,e,) operation on nodes (i,t,e)
         *
         * ite() is the "if then else" operation that can modeled as ite(i, t, e) = i⋅t + !i⋅e
         * @param i First variable -condition variable-
         * @param t The expected result if i is True
         * @param e The expected result if i is False
         * @return
         */
        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e);

        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x);

        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x);

        BDD_ID coFactorTrue(const BDD_ID f);

        BDD_ID coFactorFalse(const BDD_ID f);

        /**
         * Performs logical AND operation on a & b
         *
         * Performs logical AND using ite(a, b, 0) and returns BDD_ID of the node representing the result of the operation
         * @param a First node
         * @param b Second node
         * @return BDD_ID of the result
         */
        BDD_ID and2(const BDD_ID a, const BDD_ID b);

        /**
         * Performs logical OR operation on a & b
         *
         * Performs logical OR using ite(a, 1, b) and returns BDD_ID of the node representing the result of the operation
         * @param a First node
         * @param b Second node
         * @return BDD_ID of the result
         */
        BDD_ID or2(const BDD_ID a, const BDD_ID b);   //a = 2; b=3; or(a,b) => or(2,3)
        /**
         * Performs logical XOR operation on a & b
         *
         * Performs logical XOR using ite(a, neg(b), b) and returns BDD_ID of the node representing the result of the operation
         * @param a First node
         * @param b Second node
         * @return BDD_ID of the result
         */
        BDD_ID xor2(const BDD_ID a, const BDD_ID b);

        /**
         * Performs a logical NOT operation on a
         * Performs logical NOT using ite(a, 0, 1) and returns BDD_ID of the node representing the result of the operation
         * @param a Node to negate
         * @return BDD_ID of the result
         */
        BDD_ID neg(const BDD_ID a);

        /**
         * Performs logical NAND operation on a & b
         *
         * Performs logical NAND using ite(ite(a, b, 0), 0, 1) and returns BDD_ID of the node representing the result of the operation
         * @param a First node
         * @param b Second node
         * @return BDD_ID of the result
         */
        BDD_ID nand2(const BDD_ID a, const BDD_ID b);

        /**
         * Performs logical NOR operation on a & b
         *
         * Performs logical NOR using ite(ite(a, 1, b), 0, 1) and returns BDD_ID of the node representing the result of the operation
         * @param a First node
         * @param b Second node
         * @return BDD_ID of the result
         */
        BDD_ID nor2(const BDD_ID a, const BDD_ID b);

        /**
         * Returns the name -label- of the topVar of node root
         *
         * @param root
         * @return name of topVar as string
         */
        std::string getTopVarName(const BDD_ID &root);

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

        /**
         * Returns the size of the unique table
         * @return size of the unique table
         */
        size_t uniqueTableSize();

        /**
         * Returns the BDD_ID associated with the given HashCode
         *
         * Iterates the unique table looking for a HashCode that matches the given one and returns the BDD_ID associated with it, returns -1 if it's not found.
         * @param hashCode to get its BDD_ID
         * @return BDD_ID if it's found, -1 otherwise.
         */
        BDD_ID &searchUniqueTable(const HashCode &hashCode);

        HashCode getHashCode(BDD_ID id);

        BDD_ID searchComputedTable(BDD_ID i, BDD_ID t, BDD_ID e);

        /** Takes set of vars and returns the highest priority
         *
         * The priority is defined by the order of insertion in the unique_table
         * @param varsSet Set of variables
         * @return The variable with the highest priority
         */
        BDD_ID getHighestVar(std::set<BDD_ID> varsSet);

        void printUniqueTable();

        BDD_ID &FindOrAddToUniqueTable(HashCode &hashCode);
    };

}
#endif