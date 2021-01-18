//
// Created by Mohamed Moursi on 18.01.21.
//

#include "Container.h"

Container::Container(BDD_ID e1, BDD_ID e2, BDD_ID e3) {
    this->e1=e1;
    this->e2=e2;
    this->e3=e3;
}

BDD_ID Container::getE1() const {
    return e1;
}

BDD_ID Container::getE2() const {
    return e2;
}

BDD_ID Container::getE3() const {
    return e3;
}

bool Container::operator==(const Container &rhs) const {
    return e1 == rhs.e1 &&
           e2 == rhs.e2 &&
           e3 == rhs.e3;
}

bool Container::operator!=(const Container &rhs) const {
    return !(rhs == *this);
}
