//
// Created by Per-Arne on 25.02.2017.
//

#pragma once

#include "../Constants.h"
#include "BaseState.h"
class Unit;

class Building: public BaseState {
public:
    Building():BaseState(Constants::State::Building){
        name = "Building";
    }

    virtual void update(State::Unit *uState)const;;
    virtual void init(State::Unit *uState)const;;
    virtual void end(State::Unit *uState)const;;
};

