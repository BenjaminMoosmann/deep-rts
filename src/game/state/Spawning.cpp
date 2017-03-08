//
// Created by Per-Arne on 24.02.2017.
//


#include "Spawning.h"
#include "../unit/unit.h"

void Spawning::update(State::Unit * unit)const{
    unit->spawnTimer += 1;

   
    if(unit->spawnTimer >= unit->spawnDuration) {
        // Unit can spawn
        unit->setPosition(*unit->spawnTile);
        unit->transitionState();
    }

}

void Spawning::init(State::Unit * unit)const{

}

void Spawning::end(State::Unit * unit)const{

}
