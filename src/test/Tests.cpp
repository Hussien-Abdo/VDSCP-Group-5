//
// Created by tobias on 21.11.16.
//

#include "gtest/gtest.h"
#include "../Manager.h"
#include "../Manager.cpp"
#include "../HashCode.cpp"
#include "iostream"

using namespace ClassProject;
namespace {

    TEST(ManagerClass, Constructor) {
        Manager m = Manager();
        EXPECT_EQ(m.getHashCode(0).getLow(), 0);
        EXPECT_EQ(m.getHashCode(1).getLow(), 1);
        EXPECT_EQ(m.getHashCode(0).getHigh(), 0);
        EXPECT_EQ(m.getHashCode(1).getHigh(), 1);
    }

    TEST(ManagerClass, TrueFalse) {
        Manager m = Manager();
        EXPECT_EQ(m.True(), 1);
        EXPECT_EQ(m.False(), 0);
    }

    TEST(ManagerClass, IsConstant) {
        Manager m = Manager();
        EXPECT_TRUE(m.isConstant(1));
        EXPECT_TRUE(m.isConstant(0));
    }

    TEST(ManagerClass, IsVariable) {
        Manager m = Manager();
        EXPECT_FALSE(m.isVariable(1));
        EXPECT_FALSE(m.isVariable(0));
    }

    TEST(ManagerClass, CreateVar) {
        Manager m = Manager();
        const BDD_ID varID = m.createVar("TestVar");
        EXPECT_TRUE(m.isVariable(varID));
    }

    TEST(ManagerClass, getTopVarName) {
        Manager m = Manager();
        const BDD_ID varId1 = m.createVar("TestVar1");
        const BDD_ID varId2 = m.createVar("TestVar2");
        const char *TopVarName1 = m.getTopVarName(varId1).c_str();
        EXPECT_STREQ(TopVarName1, "TestVar1");
        const char *TopVarName2 = m.getTopVarName(varId2).c_str();
        EXPECT_STREQ(TopVarName2, "TestVar2");
    }
}