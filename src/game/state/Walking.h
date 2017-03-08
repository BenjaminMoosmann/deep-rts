//
// Created by Per-Arne on 24.02.2017.
//

#ifndef WARC2SIM_WALKING_H
#define WARC2SIM_WALKING_H


#include "BaseState.h"

class Walking: public BaseState {

public:
    Walking(): BaseState(Constants::State::Walking){
        name = "Walking";
    }
    virtual void update(State::Unit *uState)const;;
    virtual void init(State::Unit *uState)const;;
    virtual void end(State::Unit *uState)const;;
};


#endif //WARC2SIM_WALKING_H
