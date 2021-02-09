//
// Created by ludwig on 27.11.18.
//

#include "Reachable.h"

namespace ClassProject {


    Reachable::Reachable(unsigned int stateSize) : ReachableInterface(stateSize) {
        this->stateSize = stateSize;
        for(auto i =0; i<stateSize; i++){
            states.push_back(createVar("s"+std::to_string(i)));
        }
        for(auto i =0; i<stateSize; i++){
            next_states.push_back(createVar("s`"+std::to_string(i)));
        }
    }

    BDD_ID Reachable::xnor2(BDD_ID a, BDD_ID b) {
        return ite(a, b, neg(b));
    }

    const std::vector<BDD_ID> &Reachable::getStates() const {
        return states;
    }

    void Reachable::setDelta(const std::vector<BDD_ID> &transitionFunctions) {
        std::vector<BDD_ID> taus;
         for(auto i=0;i<stateSize;i++){
           taus.push_back(xnor2(next_states.at(i),transitionFunctions.at(i)));
        }
        tau=taus.at(0);
        for(int i=1;i<stateSize;i++){
           tau=and2(tau, taus.at(i));
        }
    }

    void Reachable::setInitState(const std::vector<bool> &stateVector) {
        std::vector<BDD_ID> temp_BDD_ID;
        for(auto i=0;i<stateSize;i++){
            temp_BDD_ID.push_back(xnor2(states.at(i), stateVector.at(i)));
        }
        C_S0=temp_BDD_ID.at(0);
        for(int i=1;i<stateSize;i++){
            C_S0=and2(C_S0, temp_BDD_ID.at(i));
        }
    }

    BDD_ID Reachable::compute_reachable_states() {
        BDD_ID C_R;
        BDD_ID C_R_it=C_S0;
        BDD_ID temp_BDD_ID;
        BDD_ID img_next;
        BDD_ID img_current;
        do{
            C_R=C_R_it;
            temp_BDD_ID=and2(C_R,tau);
            //STEP 8
            for(signed int i=stateSize-1;i>=0;i--){
                temp_BDD_ID=or2(coFactorTrue(temp_BDD_ID,states.at(i)),coFactorFalse(temp_BDD_ID,states.at(i)));
            }
            img_next = temp_BDD_ID;
            //STEP9
            std::vector<BDD_ID> temp_vector;
            for(auto i=0;i<stateSize;i++){
                temp_vector.push_back(xnor2(states.at(i),next_states.at(i)));
            }
            temp_BDD_ID=temp_vector.at(0);
            for(auto i=1;i<stateSize;i++){
                temp_BDD_ID=and2(temp_BDD_ID, temp_vector.at(i));
            }

            temp_BDD_ID=and2(temp_BDD_ID, img_next);
            for(signed int i=stateSize-1;i>=0;i--){
                temp_BDD_ID=or2(coFactorTrue(temp_BDD_ID,next_states.at(i)),coFactorFalse(temp_BDD_ID,next_states.at(i)));
            }
            img_current = temp_BDD_ID;
            //STEP10
            C_R_it=or2(C_R,img_current);

        } while (C_R!=C_R_it);
        return C_R;
    }

    bool Reachable::is_reachable(const std::vector<bool>& stateVector){
        BDD_ID C_R = compute_reachable_states();
        for(int i = 0; i < stateSize; i++) {
            if(stateVector.at(i)) {
                C_R = coFactorTrue(C_R,  states.at(i));
            } else {
                C_R = coFactorFalse(C_R,  states.at(i));
            }
        }
        if(C_R == 1)
            return true;
        else
            return false;
    }
}