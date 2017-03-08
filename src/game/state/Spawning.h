//
// Created by Per-Arne on 24.02.2017.
//

#ifndef WARC2SIM_SPAWNING_H
#define WARC2SIM_SPAWNING_H



#include "BaseState.h"

class Spawning: public BaseState{

public:
    Spawning():BaseState(Constants::State::Spawning){
        name = "Spawning";
    }
    virtual void update(State::Unit *uState)const;;
    virtual void init(State::Unit *uState)const;;
    virtual void end(State::Unit *uState)const;;
};


#endif //WARC2SIM_SPAWNING_H
