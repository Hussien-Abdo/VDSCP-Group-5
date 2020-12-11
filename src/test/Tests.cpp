//
// Created by tobias on 21.11.16.
//

#include "gtest/gtest.h"
#include "../HashCode.cpp"
#include "ManagerTest.cpp"

using namespace ClassProject;
namespace {

    TEST_F(ManagerTest, Constructor) {
        SetUp(0);
        EXPECT_EQ(m.getHashCode(0).getLow(), 0);
        EXPECT_EQ(m.getHashCode(1).getLow(), 1);
        EXPECT_EQ(m.getHashCode(0).getHigh(), 0);
        EXPECT_EQ(m.getHashCode(1).getHigh(), 1);
    }

    TEST_F(ManagerTest, TrueFalse) {
        SetUp(0);
        EXPECT_EQ(m.True(), 1);
        EXPECT_EQ(m.False(), 0);
    }

    TEST_F(ManagerTest, IsConstant) {
        SetUp(0);
        EXPECT_TRUE(m.isConstant(1));
        EXPECT_TRUE(m.isConstant(0));
    }

    TEST_F(ManagerTest, IsVariable) {
        SetUp(0);
        EXPECT_FALSE(m.isVariable(1));
        EXPECT_FALSE(m.isVariable(0));
    }

    TEST_F(ManagerTest, CreateVar) {
        SetUp(1);
        EXPECT_TRUE(m.isVariable(var1));
    }

    TEST_F(ManagerTest, TopVarId) {
        SetUp(2);
        EXPECT_EQ(m.topVar(var1), var1);
        EXPECT_EQ(m.topVar(var2), var2);
    }

    TEST_F(ManagerTest, getTopVarName) {
        SetUp(2);
        const char *TopVarName1 = m.getTopVarName(var1).c_str();
        EXPECT_STREQ(TopVarName1, "a");
        const char *TopVarName2 = m.getTopVarName(var2).c_str();
        EXPECT_STREQ(TopVarName2, "b");
    }

    TEST_F(ManagerTest, iteTerminal) {
        SetUp(2);
        EXPECT_EQ(m.ite(1, var1, var2), var1);
        EXPECT_EQ(m.ite(0, var2, var1), var1);
        EXPECT_EQ(m.ite(var1, 1, 0), var1);
        EXPECT_EQ(m.ite(var2, var1, var1), var1);
        EXPECT_EQ(m.ite(var1,0,1), m.neg(var1));
        m.printUniqueTable();
    }

    TEST_F(ManagerTest, ITE_Basic_And2) {
        EXPECT_EQ(m.and2(m.True(), m.False()), 0);
        EXPECT_EQ(m.and2(m.True(), m.True()), 1);
        EXPECT_EQ(m.and2(m.False(), m.False()), 0);
        EXPECT_EQ(m.and2(m.False(), m.True()), 0);
    }

    TEST_F(ManagerTest, ITE_Basic_Or2) {
        EXPECT_EQ(m.or2(m.True(), m.False()), 1);
        EXPECT_EQ(m.or2(m.True(), m.True()), 1);
        EXPECT_EQ(m.or2(m.False(), m.False()), 0);
        EXPECT_EQ(m.or2(m.False(), m.True()), 1);

    }

    TEST_F(ManagerTest, ITE_Function) {
        SetUp(4);
        BDD_ID or2 = m.or2(var1, var2);
        BDD_ID and2 = m.and2(var3, var4);
        m.and2(or2, and2);
        std::cout << "**************************** f = and(or(a,b),and(c,d)) ****************************\n";
        m.printUniqueTable();
        std::cout << "************************** f = neg(and(or(a,b),and(c,d))) **************************\n";
        m.neg(m.and2(or2, and2));
        m.printUniqueTable();
    }

    TEST_F(ManagerTest, coFactorTrue) {
        SetUp(3);
        BDD_ID f = m.or2(var1, m.and2(var2, var3));
        EXPECT_EQ(m.coFactorTrue(f), m.True());
    }

    TEST_F(ManagerTest, coFactorFalse) {
        SetUp(3);
        BDD_ID f = m.or2(var1, m.and2(var2, var3));
        EXPECT_EQ(m.coFactorFalse(f), 5);
    }

    TEST_F(ManagerTest, uniqueTableSize) {
        EXPECT_EQ(m.uniqueTableSize(), 2);
    }
    TEST_F(ManagerTest, negTest){
        SetUp(1);
        m.neg(m.neg(m.neg(var1)));
        m.printUniqueTable();
        EXPECT_FALSE(m.neg(m.True()));
        EXPECT_TRUE(m.neg(m.False()));
    }
    TEST_F(ManagerTest, nand2Test){
        EXPECT_TRUE(m.nand2(m.False(),m.False()));
        EXPECT_TRUE(m.nand2(m.False(),m.True()));
        EXPECT_TRUE(m.nand2(m.True(),m.False()));
        EXPECT_FALSE(m.nand2(m.True(),m.True()));
        m.printUniqueTable();
    }
    TEST_F(ManagerTest, nor2Test){
        EXPECT_TRUE(m.nor2(m.False(),m.False()));
        EXPECT_FALSE(m.nor2(m.False(),m.True()));
        EXPECT_FALSE(m.nor2(m.True(),m.False()));
        EXPECT_FALSE(m.nor2(m.True(),m.True()));
        m.printUniqueTable();
    }
    TEST_F(ManagerTest, xor2Test){
        EXPECT_FALSE(m.xor2(m.False(),m.False()));
        EXPECT_TRUE(m.xor2(m.False(),m.True()));
        EXPECT_TRUE(m.xor2(m.True(),m.False()));
        EXPECT_FALSE(m.xor2(m.True(),m.True()));
        m.printUniqueTable();
    }
    TEST_F(ManagerTest, findNodesTest){
        SetUp(4);
        std::set<BDD_ID> nodes_of_root;
        BDD_ID or2 = m.or2(var1, var2);
        BDD_ID and2 = m.and2(var3, var4);
        BDD_ID f = m.and2(or2, and2);
        m.findNodes(f,nodes_of_root);
        EXPECT_EQ(nodes_of_root.size(),4);
    }
    TEST_F(ManagerTest, findVarsTest){
        SetUp(4);
        std::set<BDD_ID> vars_of_root;
        BDD_ID or2 = m.or2(var1, var2);
        BDD_ID and2 = m.and2(var3, var4);
        BDD_ID f = m.and2(or2, and2);
        m.findVars(f,vars_of_root);
        EXPECT_EQ(vars_of_root.size(),4);
    }
}