//
// Created by Per-Arne on 01.03.2017.
//

#ifndef WARC2SIM_BASEACTION_H
#define WARC2SIM_BASEACTION_H


#include "../unit/Unit.h"
#include "../../flatbuffers/Game_generated.h"
#include "../../flatbuffers/Unit_generated.h"
#include "../../flatbuffers/Player_generated.h"

class BaseAction {
protected:
    State::Unit * unit;
public:

    BaseAction(State::Unit * unit): unit(unit){};

    long tick;                      // At which tick this move was executed;
    virtual void doAction() = 0;         // This function
    virtual void reverseAction() = 0;    // Reverse operation of this action.
};


#endif //WARC2SIM_BASEACTION_H
