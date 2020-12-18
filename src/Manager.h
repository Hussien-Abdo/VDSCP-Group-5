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
#include <set>
#include <string>
#include "ManagerInterface.h"
#include "HashCode.h"
/**
 * Main namespace, contains Manager.cpp class
 */
namespace ClassProject {
/**
 * The Manager class is the main class in this package. It implements ManagerInterface.
 * It contains all BDD package functions. In addition it implements the ROBDD as an unordered_map.
 * The order of the variables -priority- is the insertion order.
 */
    class Manager : public ManagerInterface {

    private:
        BDD_ID node_id; /**< BDD_ID counter, keeps track of last used BDD_ID */
        std::string node_label; /**<  Internal string used to create label for nodes that represent a function */
        BDD_ID search_result; /**< Used to store the return values for some functions, to return by reference */
        std::unordered_map<BDD_ID, HashCode> unique_table; /**< unordered_map that represents the ROBDD */
        std::vector<std::array<BDD_ID, 4>> computed_table; /**< Table to store the result of each ite(i,t,e) call */

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
        /**
         * Returns positive cofactor of function f with respect to x
         *
         * Returns the result of substituting x equal to 1 in f as a BDD_ID
         * f = a + (b ∗ c)
         * coFactorTrue(f, c) = a + b
         * @param f Function to coFactor
         * @param x Variable or function to coFactor with respect to
         * @return BDD_ID representing the result of the coFactoring
         */
        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x);
        /**
         * Returns negative cofactor of function f with respect to x
         *
         * Returns the result of substituting x equal to 0 in f as a BDD_ID
         * f = a + (b ∗ c)
         * coFactorFalse(f, c) = a
         * @param f Function to coFactor
         * @param x Variable or function to coFactor with respect to
         * @return BDD_ID representing the result of the coFactoring
         */
        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x);
        /**
         * Returns the positive cofactor of function f with respect to the highest variable
         *
         * Returns the positive cofactor of function f with respect to the highest order variable in function f
         * @param f Function to coFactor
         * @return BDD_ID representing the result of the coFactoring
         */
        BDD_ID coFactorTrue(const BDD_ID f);
        /**
         * Returns the negative cofactor of function f with respect to the highest variable
         *
         * Returns the negative cofactor of function f with respect to the highest order variable in function f
         * @param f Function to coFactor
         * @return BDD_ID representing the result of the coFactoring
         */
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
         * @param root Node to get its topVar
         * @return name of topVar as string
         */
        std::string getTopVarName(const BDD_ID &root);
        /**
         *
         * @param root
         * @param nodes_of_root
         */
        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);
        /**
         * Returns the set of nodes reachable from the given BDD_ID -root- including the node itself
         *
         * @param root Node to get its successors
         * @param vars_of_root set of BDD_ID to store the result into
         */
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
        /**
         *  Returns the HashCode-unique tuple- associated with the given BDD_ID
         * @param id BDD_ID to get its HashCode-unique tuple-
         * @return HashCode associated with the given BDD_ID
         */
        HashCode getHashCode(BDD_ID id);
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
        BDD_ID searchComputedTable(BDD_ID i, BDD_ID t, BDD_ID e);

        /** Takes set of vars and returns the highest priority
         *
         * The priority is defined by the order of insertion in the unique_table
         * @param varsSet Set of variables
         * @return The variable with the highest priority
         */
        BDD_ID getHighestVar(std::set<BDD_ID> varsSet);
        /**
         *Prints the Uniqetable
         */
        void printUniqueTable();
        /**
         * Adds a HashCode to the UniqueTable or returns its ID if it already exists
         * @param hashCode to add or return its BDD_ID
         * @return The BDD_ID associated with the HashCode
         */
        BDD_ID &FindOrAddToUniqueTable(HashCode &hashCode);
    };

}
#endif