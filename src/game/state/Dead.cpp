//
// Created by Per-Arne on 27.02.2017.
//

#include "Dead.h"
#include "../unit/Unit.h"
#include "../player/Player.h"
void Dead::update(State::Unit * unit)const{

    unit->despawn();
    unit->player_.removeUnit(unit);
}

void Dead::end(State::Unit * unit)const{

}

void Dead::init(State::Unit * unit)const{

}

