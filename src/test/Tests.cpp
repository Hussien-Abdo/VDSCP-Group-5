//
// Created by tobias on 21.11.16.
//

#include "Tests.h"
#include "iostream"

namespace {
    TEST(ConstructorTest,BDD_IDD){
        std::cout<<"testing";
        BDD_Id bddId1(1,"1",NULL);
        BDD_Id bddId0(0,"0",NULL);
        BDD_Id bddIda(3,"a",&bddId1,&bddId0,NULL);
        EXPECT_EQ(1, bddIda.getHigh()->getId());
        EXPECT_EQ(0, bddIda.getLow()->getId());
    }
}