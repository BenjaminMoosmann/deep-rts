//
// Created by Per-Arne on 24.02.2017.
//

#include "Walking.h"
#include "../player/Player.h"
#include "../Game.h"
#include "../util/Pathfinder.h"

void Walking::update(State::Unit *uState)const{


    if(!uState->walkGoal()){
        assert(false); //No goal were set!
    }


    if (!uState->walkPath.empty()) {
		uState->mutate_walkTimer(uState->walkTimer + 1) ;

        if (uState->walkTimer() > uState->walkInterval()) {

            // Pop next

            Tile * nextTile = unit->walking_path.back();
            unit->walking_path.pop_back();

			// Check if someone is standing on goal
			if (!nextTile->canWalkTo()) {
				unit->transitionState();
				return;
			}


            unit->setPosition(*nextTile);
            unit->walking_timer = 0;


        }
    } else {
        unit->transitionState();
        return;
    }




}

void Walking::end(State::Unit *uState)const{
    unit->walking_path.clear();
}

void Walking::init(State::Unit *uState)const{
    unit->walking_timer = 0;

	Tile *goal = NULL;
	if (unit->walkingGoal->occupant) {
		State::Unit * occupant = unit->walkingGoal->occupant;
		Tile *closest  = Pathfinder::find_closest_walkable_tile(unit->tile, occupant->tile, occupant->width);
		goal = closest;
	}
	else if (!unit->walkingGoal->canWalkTo()) {
		goal = Pathfinder::find_first_walkable_tile(unit->walkingGoal);
	}
	else {
		goal = unit->walkingGoal;
	}


	if (!goal) {

		return;
	}

	unit->walkingGoal = goal;
	Pathfinder::aStar(unit->walking_path, unit->tile, goal);
}

