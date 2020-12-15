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
        std::vector<std::array<BDD_ID,4>> computed_table;

    public:
        Manager();

        BDD_ID createVar(const std::string &label);

        const BDD_ID &True();

        const BDD_ID &False();    //EXPECT(0, manager.False())

        bool isConstant(const BDD_ID f);

        bool isVariable(const BDD_ID x);

        BDD_ID topVar(const BDD_ID f);

        BDD_ID ite(const BDD_ID i, const BDD_ID t, const BDD_ID e);

        BDD_ID coFactorTrue(const BDD_ID f, BDD_ID x);

        BDD_ID coFactorFalse(const BDD_ID f, BDD_ID x);

        BDD_ID coFactorTrue(const BDD_ID f);

        BDD_ID coFactorFalse(const BDD_ID f);

        BDD_ID and2(const BDD_ID a, const BDD_ID b);

        BDD_ID or2(const BDD_ID a, const BDD_ID b);   //a = 2; b=3; or(a,b) => or(2,3)

        BDD_ID xor2(const BDD_ID a, const BDD_ID b);

        BDD_ID neg(const BDD_ID a);

        BDD_ID nand2(const BDD_ID a, const BDD_ID b);

        BDD_ID nor2(const BDD_ID a, const BDD_ID b);

        std::string getTopVarName(const BDD_ID &root);

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

        size_t uniqueTableSize();

        BDD_ID &searchUniqueTable(const HashCode& hashCode);

        HashCode getHashCode(BDD_ID id);

        BDD_ID searchComputedTable(BDD_ID i, BDD_ID t, BDD_ID e);

        BDD_ID getHighestVar(std::set<BDD_ID> varsSet);

        void printUniqueTable();

        BDD_ID &FindOrAddToUniqueTable(HashCode &hashCode);
    };

}
#endif

// Local Variables:
// mode: c++
// End:
