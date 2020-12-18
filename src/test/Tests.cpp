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

    TEST_F(ManagerTest, getTopVarId) {
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

////Testing ite Terminal Cases
    TEST_F(ManagerTest, iteTerminal) {
        SetUp(2);
        EXPECT_EQ(m.ite(1, var1, var2), var1);
        EXPECT_EQ(m.ite(0, var2, var1), var1);
        EXPECT_EQ(m.ite(var1, 1, 0), var1);
        EXPECT_EQ(m.ite(var2, var1, var1), var1);
        EXPECT_EQ(m.ite(var1,0,1), m.neg(var1));
    }

////Testing ite with the function f = neg(and(or(a,b),and(c,d)))
    TEST_F(ManagerTest, ITE_Function) {
        SetUp(4);
        BDD_ID or2 = m.or2(var1, var2);
        EXPECT_EQ(or2, 6);
        EXPECT_EQ(m.getHashCode(or2).getHigh(), 1);
        EXPECT_EQ(m.getHashCode(or2).getLow(), 3);
        EXPECT_EQ(m.getHashCode(or2).getTopVar(), 2);
        BDD_ID and2 = m.and2(var3, var4);
        EXPECT_EQ(and2, 7);
        EXPECT_EQ(m.getHashCode(and2).getHigh(), 5);
        EXPECT_EQ(m.getHashCode(and2).getLow(), 0);
        EXPECT_EQ(m.getHashCode(and2).getTopVar(), 4);
        BDD_ID f = m.and2(or2, and2);
        EXPECT_EQ(m.getHashCode(8).getHigh(), 7);
        EXPECT_EQ(m.getHashCode(8).getLow(), 0);
        EXPECT_EQ(m.getHashCode(8).getTopVar(), 3);
        EXPECT_EQ(f, 9);
        EXPECT_EQ(m.getHashCode(f).getHigh(), 7);
        EXPECT_EQ(m.getHashCode(f).getLow(), 8);
        EXPECT_EQ(m.getHashCode(f).getTopVar(), 2);
        BDD_ID neg_f = m.neg(m.and2(or2, and2));
        EXPECT_EQ(neg_f, 10);
        EXPECT_EQ(m.getHashCode(neg_f).getHigh(), 8);
        EXPECT_EQ(m.getHashCode(neg_f).getLow(), 7);
        EXPECT_EQ(m.getHashCode(neg_f).getTopVar(), 2);
        std::cout << "              *************************** f = neg(and(or(a,b),and(c,d))) ****************************\n";
        m.printUniqueTable();
    }

////Test for getting cofactors of the function defined by node f = or(a,and(b,c))
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

////Test for getting cofactors of the function defined by node f = or(a,and(b,c))
/// with respect to function x = c
    TEST_F(ManagerTest, coFactorTrueX) {
        SetUp(3);
        BDD_ID and2 = m.and2(var2, var3);
        BDD_ID f = m.or2(var1, and2);
        EXPECT_EQ(m.coFactorTrue(f,var3), m.or2(var1,var2));
    }

    TEST_F(ManagerTest, coFactorFalseX) {
        SetUp(3);
        BDD_ID f = m.or2(var1, m.and2(var2, var3));
        EXPECT_EQ(m.coFactorFalse(f, var3), var1);
    }

////Basic gates, tests for True & False inputs
    TEST_F(ManagerTest, ITE_Basic_neg){
        EXPECT_FALSE(m.neg(m.True()));
        EXPECT_TRUE(m.neg(m.False()));
    }

    TEST_F(ManagerTest, ITE_Basic_And2) {
        EXPECT_EQ(m.and2(m.True(), m.False()), m.False());
        EXPECT_EQ(m.and2(m.True(), m.True()), m.True());
        EXPECT_EQ(m.and2(m.False(), m.False()), m.False());
        EXPECT_EQ(m.and2(m.False(), m.True()), m.False());
    }

    TEST_F(ManagerTest, ITE_Basic_Or2) {
        EXPECT_EQ(m.or2(m.True(), m.False()), m.True());
        EXPECT_EQ(m.or2(m.True(), m.True()), m.True());
        EXPECT_EQ(m.or2(m.False(), m.False()), m.False());
        EXPECT_EQ(m.or2(m.False(), m.True()), m.True());

    }

    TEST_F(ManagerTest, ITE_Basic_xor2){
        EXPECT_EQ(m.xor2(m.False(),m.False()),m.False());
        EXPECT_EQ(m.xor2(m.False(),m.True()),m.True());
        EXPECT_EQ(m.xor2(m.True(),m.False()),m.True());
        EXPECT_EQ(m.xor2(m.True(),m.True()),m.False());
    }

    TEST_F(ManagerTest, ITE_Basic_nand2){
        EXPECT_EQ(m.nand2(m.False(),m.False()),m.True());
        EXPECT_EQ(m.nand2(m.False(),m.True()),m.True());
        EXPECT_EQ(m.nand2(m.True(),m.False()),m.True());
        EXPECT_EQ(m.nand2(m.True(),m.True()),m.False());
    }

    TEST_F(ManagerTest, ITE_Basic_nor2){
        EXPECT_EQ(m.nor2(m.False(),m.False()),m.True());
        EXPECT_EQ(m.nor2(m.False(),m.True()),m.False());
        EXPECT_EQ(m.nor2(m.True(),m.False()),m.False());
        EXPECT_EQ(m.nor2(m.True(),m.True()),m.False());
    }

////Basic gates, tests for variable inputs
    TEST_F(ManagerTest, ITE_Var_neg){
        SetUp(1);
        BDD_ID negVar1 = m.neg(var1);
        EXPECT_EQ(negVar1, 3);
        EXPECT_EQ(m.getHashCode(negVar1).getHigh(), m.getHashCode(var1).getLow());
        EXPECT_EQ(m.getHashCode(negVar1).getLow(), m.getHashCode(var1).getHigh());
    }

    TEST_F(ManagerTest, ITE_Var_And2) {
        SetUp(2);
        BDD_ID and2 = m.and2(var1, var2);
        EXPECT_EQ(and2, 4);
        EXPECT_EQ(m.getHashCode(and2).getHigh(), 3);
        EXPECT_EQ(m.getHashCode(and2).getLow(), 0);
        EXPECT_EQ(m.getHashCode(and2).getTopVar(), 2);
    }

    TEST_F(ManagerTest, ITE_Var_Or2) {
        SetUp(2);
        BDD_ID or2 = m.or2(var1, var2);
        EXPECT_EQ(or2, 4);
        EXPECT_EQ(m.getHashCode(or2).getHigh(), 1);
        EXPECT_EQ(m.getHashCode(or2).getLow(), 3);
        EXPECT_EQ(m.getHashCode(or2).getTopVar(), 2);

    }

    TEST_F(ManagerTest, ITE_Var_xor2){
        SetUp(2);
        BDD_ID xor2 = m.xor2(var1, var2);
        EXPECT_EQ(xor2, 5);
        EXPECT_EQ(m.getHashCode(xor2).getHigh(), 4);
        EXPECT_EQ(m.getHashCode(xor2).getLow(), 3);
        EXPECT_EQ(m.getHashCode(xor2).getTopVar(), 2);
    }
    TEST_F(ManagerTest, ITE_Var_nand2){
        SetUp(2);
        BDD_ID nand2 = m.nand2(var1, var2);
        EXPECT_EQ(nand2, 5);
        EXPECT_EQ(m.getHashCode(nand2).getHigh(), 4);
        EXPECT_EQ(m.getHashCode(nand2).getLow(), 1);
        EXPECT_EQ(m.getHashCode(nand2).getTopVar(), 2);
    }

    TEST_F(ManagerTest, ITE_Var_nor2){
        SetUp(2);
        BDD_ID nor2 = m.nor2(var1, var2);
        EXPECT_EQ(nor2, 5);
        EXPECT_EQ(m.getHashCode(nor2).getHigh(), 0);
        EXPECT_EQ(m.getHashCode(nor2).getLow(), 4);
        EXPECT_EQ(m.getHashCode(nor2).getTopVar(), 2);
    }

////findNodes & findVars tests
    TEST_F(ManagerTest, findNodesTest){
        SetUp(4);
        std::set<BDD_ID> nodes_of_root;
        BDD_ID or2 = m.or2(var1, var2);
        BDD_ID and2 = m.and2(var3, var4);
        BDD_ID f = m.and2(or2, and2);
        m.findNodes(f,nodes_of_root);
        std::set<BDD_ID> nodes_of_root_expected{0,1,9,7,8,5};
        EXPECT_EQ(nodes_of_root.size(),nodes_of_root_expected.size());
        EXPECT_EQ(nodes_of_root,nodes_of_root_expected);
    }

    TEST_F(ManagerTest, findVarsTest){
        SetUp(4);
        std::set<BDD_ID> vars_of_root;
        BDD_ID or2 = m.or2(var1, var2);
        BDD_ID and2 = m.and2(var3, var4);
        BDD_ID f = m.and2(or2, and2);
        m.findVars(f,vars_of_root);
        std::set<BDD_ID> vars_of_root_expected{2,3,4,5};
        EXPECT_EQ(vars_of_root.size(),vars_of_root_expected.size());
        EXPECT_EQ(vars_of_root,vars_of_root_expected);
    }

////Tests for getting the size  of the unique table
    TEST_F(ManagerTest, uniqueTableSize) {
        SetUp(4);
        EXPECT_EQ(m.uniqueTableSize(), 6);
        BDD_ID or2 = m.or2(var1, var2);
        BDD_ID and2 = m.and2(var3, var4);
        m.and2(or2, and2);
        EXPECT_EQ(m.uniqueTableSize(), 10);
    }
}