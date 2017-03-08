//
// Created by Per-Arne on 26.02.2017.
//

#ifndef WARC2SIM_HARVESTING_H
#define WARC2SIM_HARVESTING_H


#include "BaseState.h"

class Unit;

class Harvesting: public BaseState {
public:
    Harvesting():BaseState(Constants::State::Harvesting){
        name = "Harvesting";
    }

    virtual void update(State::Unit *uState)const;;
    virtual void init(State::Unit *uState)const;;
    virtual void end(State::Unit *uState)const;;
};

#endif //WARC2SIM_HARVESTING_H
