//
// Created by Per-Arne on 24.02.2017.
//

#ifndef WARC2SIM_BASESTATE_H
#define WARC2SIM_BASESTATE_H



#include <string>
#include <iostream>
#include <memory>
#include "../Constants.h"
#include "../../flatbuffers/Game_generated.h"
#include "../../flatbuffers/Unit_generated.h"
#include "../../flatbuffers/Player_generated.h"


class Unit;
class BaseState {


public:
    int id = 1337;
    std::string name = "**ERR**";
    BaseState(Constants::State id): id(id){
        std::cout << "setting id to " << id << std::endl;

    };
    virtual void update(State::Unit *uState)const;
    virtual void init(State::Unit *uState)const;
    virtual void end(State::Unit *uState)const;
};


#endif //WARC2SIM_BASESTATE_H
