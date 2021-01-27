//
// Created by ludwig on 27.11.18.
//

#ifndef VDSPROJECT_IMGCOMP_H
#define VDSPROJECT_IMGCOMP_H


#include <map>
#include "ReachableInterface.h"

namespace ClassProject {

    class Reachable : public ReachableInterface {

    public:

        Reachable(unsigned int stateSize);

        BDD_ID xnor2(BDD_ID a, BDD_ID b);

        const std::vector<BDD_ID> &getStates() const;

        void setDelta(const std::vector<BDD_ID> &transitionFunctions);

        void setInitState(const std::vector<bool>& stateVector);

        BDD_ID compute_reachable_states();

        bool is_reachable(const std::vector<bool>& stateVector);

    private:
        unsigned int stateSize;
    };

}
#endif //VDSPROJECT_IMGCOMP_H
