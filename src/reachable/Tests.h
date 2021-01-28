//
// Created by tobias on 29.11.18.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "Reachable.h"
#include "gtest/gtest.h"
using namespace ClassProject;

TEST(managerTest, HowTo_Example) {

    ClassProject::Reachable comp(2);

    auto states = comp.getStates();
    std::vector<BDD_ID> functions;

    auto s0 = states.at(0);
    auto s1 = states.at(1);
    //s0' = not(s0)
    functions.push_back(comp.neg(s0));
    //s1' = not(s1)
    functions.push_back(comp.neg(s1));
    //Add transition functions
    comp.setDelta(functions);
    //Add init state
    comp.setInitState({false,false});

    ASSERT_TRUE(comp.is_reachable({true,true}));
    ASSERT_TRUE(comp.is_reachable({false,false}));
    ASSERT_FALSE(comp.is_reachable({true,false}));
    ASSERT_FALSE(comp.is_reachable({false,true}));

}

TEST(managerTest, lecture_Example) {

    ClassProject::Reachable comp(2);
    BDD_ID x1 = comp.createVar("x1");
    BDD_ID x2 =  comp.createVar("x2");
    auto states = comp.getStates();
    std::vector<BDD_ID> functions;

    auto s0 = states.at(0);
    auto s1 = states.at(1);
    functions.push_back(comp.and2(comp.neg(x1),comp.or2(s0, s1)));
    functions.push_back(comp.and2(comp.neg(x2),comp.or2(x1,comp.or2(s0, s1))));
    //Add transition functions
    comp.setDelta(functions);
    //Add init state
    comp.setInitState({false,false});

    ASSERT_FALSE(comp.is_reachable({true,true}));
    ASSERT_TRUE(comp.is_reachable({false,false}));
    ASSERT_FALSE(comp.is_reachable({true,false}));
    ASSERT_TRUE(comp.is_reachable({false,true}));

}


#endif //VDSPROJECT_TESTS_H
