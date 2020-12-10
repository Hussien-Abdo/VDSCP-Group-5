//
// Created by Mohamed Moursi on 10.12.20.
//
#include "../Manager.h"
#include "../Manager.cpp"
#include "Tests.h"

class ManagerTest : public ::testing::Test {
protected:
    void SetUp(int i) {
        switch (i) {
            case 0:{
                break;
            }
            case 1: {
                var1 = m.createVar("a");
                break;
            }
            case 2: {
                var1 = m.createVar("a");
                var2 = m.createVar("b");
                break;
            }
            case 3: {
                var1 = m.createVar("a");
                var2 = m.createVar("b");
                var3 = m.createVar("c");
                break;
            }
            case 4: {
                var1 = m.createVar("a");
                var2 = m.createVar("b");
                var3 = m.createVar("c");
                var4 = m.createVar("d");
                break;
            }
        }
    }
    ClassProject::Manager m = ClassProject::Manager();
    BDD_ID var1, var2, var3, var4;
};
