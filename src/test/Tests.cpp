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

    TEST(ManagerClass, TopVarId) {
        Manager m = Manager();
        const BDD_ID varId1 = m.createVar("TestVar1");
        const BDD_ID varId2 = m.createVar("TestVar2");
        EXPECT_EQ(m.topVar(varId1), varId1);
        EXPECT_EQ(m.topVar(varId2), varId2);
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

    TEST(ManagerClass,iteTerminal){
        Manager m = Manager();
        const BDD_ID f = m.createVar("TestVar1");
        const BDD_ID g = m.createVar("TestVar2");
        EXPECT_EQ(m.ite(1, f, g), f);
        EXPECT_EQ(m.ite(0, g, f), f);
        EXPECT_EQ(m.ite(f, 1, 0), f);
        EXPECT_EQ(m.ite(g,f,f), f);
        m.printUniqueTable();
        //EXPECT_EQ(m.ite(f,0,1), neg(f));
    }
    TEST(ManagerClass,ITE_Basic_And2){
        Manager m = Manager();
        EXPECT_EQ(m.and2(m.True(),m.False()),0);
        EXPECT_EQ(m.and2(m.True(),m.True()),1);
        EXPECT_EQ(m.and2(m.False(),m.False()),0);
        EXPECT_EQ(m.and2(m.False(),m.True()),0);

    }

    TEST(ManagerClass,ITE_Basic_Or2){
        Manager m = Manager();
        EXPECT_EQ(m.or2(m.True(),m.False()),1);
        EXPECT_EQ(m.or2(m.True(),m.True()),1);
        EXPECT_EQ(m.or2(m.False(),m.False()),0);
        EXPECT_EQ(m.or2(m.False(),m.True()),1);

    }
    TEST(ManagerClass,ITE_Function){
        Manager m=Manager();
        BDD_ID a=m.createVar("a");
        BDD_ID b=m.createVar("b");
        BDD_ID c=m.createVar("c");
        BDD_ID d=m.createVar("d");
        BDD_ID or2=m.or2(a,b);
        BDD_ID and2=m.and2(c,d);
        m.and2(or2,and2);
        m.printUniqueTable();
    }
    TEST(ManagerClass,coFactorTrue){
        Manager m=Manager();
        BDD_ID a=m.createVar("a");
        BDD_ID b=m.createVar("b");
        BDD_ID c=m.createVar("c");
        BDD_ID f=m.or2(a,m.and2(b,c));
        EXPECT_EQ(m.coFactorTrue(f),m.True());
    }
    TEST(ManagerClass,coFactorFalse){
        Manager m=Manager();
        BDD_ID a=m.createVar("a");
        BDD_ID b=m.createVar("b");
        BDD_ID c=m.createVar("c");
        BDD_ID f=m.or2(a,m.and2(b,c));
        EXPECT_EQ(m.coFactorFalse(f),5);
    }
    TEST(ManagerClass,uniqueTableSize){
        Manager m=Manager();
        EXPECT_EQ(m.uniqueTableSize(),2);
    }

}