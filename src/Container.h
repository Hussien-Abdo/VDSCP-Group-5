//
// Created by Mohamed Moursi on 18.01.21.
//

#ifndef VDSPROJECT_CONTAINER_H
#define VDSPROJECT_CONTAINER_H

#include <cstddef>

/**
 * This class is used as a container for 3 BDD_IDs used to store data in unordered_map,
 * In the computed_table (i,t,e) => (e1,e2,e3)
 * In the u_table (high,low,top_var) => (e1,e2,e3)
 */
typedef size_t BDD_ID;

class Container {
public:

    Container(BDD_ID e1, BDD_ID e2, BDD_ID e3);

    BDD_ID getE1() const;

    BDD_ID getE2() const;

    BDD_ID getE3() const;

    bool operator==(const Container &rhs) const;

    bool operator!=(const Container &rhs) const;

private:
    BDD_ID e1;
    BDD_ID e2;
    BDD_ID e3;

};


#endif //VDSPROJECT_CONTAINER_H
