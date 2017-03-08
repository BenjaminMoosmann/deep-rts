//
// Created by Per-Arne on 24.02.2017.
//

#include "Unit.h"
#include "../player/Player.h"
#include "../Game.h"
#include "../util/Pathfinder.h"
#include "../graphics/GUI.h"
#include "../action/RightClickAction.h"
#include <random>


void Unit::spawn(State::Unit *uState, uint16_t spawnTile, bool spawnInstantly) {
	
	if (spawnInstantly) {
		uState->mutate_spawnTimer(uState->spawnDuration());
	}
	uState->mutate_spawnTile(spawnTile);
	
    Unit::transitionState(uState, Constants::State::Spawning);
	Unit::enqueueState(uState, Constants::State::Idle);
}

void Unit::moveRelative(State::Unit *uState, uint16_t x, uint16_t y) {
	Game *game = Game::getGame(uState->gameID());
	const Tile *tile = game->map.getTile(x, y);

	uint16_t newX = tile->x + x;
	uint16_t newY = tile->y + y;

	Tile *moveTile = game->map.getTile(newX, newY);

    Unit::move(uState, moveTile);
}

void Unit::rightClickRelative(State::Unit *uState, uint16_t x, uint16_t y) {
	Game *game = Game::getGame(uState->gameID());
	const Tile *tile = game->map.getTile(x, y);

	uint16_t newX = tile->x + x;
	uint16_t newY = tile->y + y;

	Tile *clickTile = game->map.getTile(newX, newY);

	Unit::rightClick(uState, clickTile);
}

void Unit::move(State::Unit *uState, Tile *targetTile){
    if (!uState->canMove())
        return;
	uState->mutate_walkGoal(targetTile->id_);

    Unit::transitionState(uState, Constants::State::Walking);
}


void Unit::setPosition(State::Unit *uState, Tile *tile) {
	Game *game = Game::getGame(uState->gameID());

    if(tile){                       // If unit already stands on a tile
        Unit::clearTiles(uState);
    }

    for(auto &t : game->map.getTiles(tile, uState->width(), uState->height())) {
        t->setOccupant(uState->id());
    }


	tile->setOccupant(uState->id());         // Set occupant of new tile to this
	uState->mutate_tile(tile->id_);                    // Set this units tile to new tile
    
	sf::Vector2f newPos = tile->getPixelPosition();
    
	Unit::setDirection(uState, newPos.x, newPos.y);
	uState->mutate_worldPositionX(newPos.x);
	uState->mutate_worldPositionY(newPos.y);
}

void Unit::update(State::Unit *uState) {
	StateManager::getInstance().getState(uState->currentState)->update();
}

uint16_t Unit::centerTile(State::Unit *uState) {
	Game *game = Game::getGame(uState->gameID());

	uint16_t addX = floor(uState->width() / 2);
	uint16_t addY = floor(uState->height() / 2);

	if (addX == 0 && addY == 0) {
		return uState->tile();
	}

	uint16_t tileID = game->map.getTileIdx(addX, addY);
	return tileID;
}

bool Unit::build(State::Unit *uState, uint16_t idx) {


    if(uState->currentState() != Constants::State::Idle)
        return false;

    if(idx < 0 or idx >= uState->buildInventory()->size())
        return false;

	Game *game = Game::getGame(uState->gameID());
	State::Player *pState = game->getPlayer(uState->playerID());


    uint16_t unitTypeID = uState->buildInventory()->Get(idx);
	State::Unit *newUnit = game->createUnit(unitTypeID);


    // PlacementTile is based on dimension of the new unit. For example; town hall has
    // 3x Width and 3x Height. We then want to place  the building by the middle tile;
	Tile * uTile = game->map.getTile(uState->tile());
	Tile * placementTile = game->map.getTile(
		uTile->x - floor(newUnit->width() / 2),
		uTile->y - floor(newUnit->height() / 2)
	);


    if(!Player::canAfford(pState, newUnit)) {
        std::cout << "Cannot afford " << newUnit->name() << std::endl;
        return false;
    }

    if(Player::canPlace(pState, uState, newUnit, placementTile)) {

		pState->units.push_back(newUnit->id());
		game->addUnit(newUnit);

        if(!uState->isStructure() and newUnit->isStructure()) {
			// *this is a unit (peasant), which builds a building
            Tile *spawnTile = placementTile;
            assert(spawnTile);
            Unit::despawn(uState);

            uState->mutate_buildEntity(newUnit->id());
            Unit::transitionState(uState, Constants::State::Building);
			Unit::spawn(newUnit, spawnTile->id_, false);
			Unit::setPosition(newUnit, spawnTile);


        }else if(uState->isStructure() and !newUnit->isStructure()){
            // Structure builds unit (Ie: TownHall builds Peasant)
			uState->mutate_buildEntity(newUnit->id());
            // build entity has no tile, spawn on nearest walkable
			Tile *uCenterTile = game->map.getTile(Unit::centerTile(uState));
            Tile *firstWalkable = Pathfinder::find_first_walkable_tile(uCenterTile);
            assert(firstWalkable);
			Unit::spawn(newUnit, firstWalkable->id_, false);

            Unit::transitionState(uState, Constants::State::Building);
        }

		pState->mutate_gold(pState->gold() - newUnit->goldCost());
		pState->mutate_lumber(pState->lumber() - newUnit->lumberCost());
		pState->mutate_oil(pState->oil() - newUnit->oilCost());
		pState->mutate_statUnitBuilt(pState->statUnitBuilt() + 1);
 
    } else {
        std::cout << "Cannot build here" << std::endl;
    }






}

void Unit::despawn(State::Unit *uState) {

	// TODO
    /*for(auto p: player_.game_.players) {
        p->targetedUnit = NULL;
    }*/

    Unit::clearTiles(uState);
    Unit::transitionState(uState, Constants::State::Despawned);
}

void Unit::clearTiles(State::Unit *uState){
	Game *game = Game::getGame(uState->gameID());
	Tile *uTile = game->map.getTile(uState->tile());

    for(auto &t : game->map.getTiles(uTile, uState->width(), uState->height())) {
        t->occupant = NULL;
    }

	uTile->occupant = NULL;
	uState->mutate_tile(NULL);
}


void Unit::rightClick(State::Unit *uState, Tile *tile) {
	
	// Clear unit state quueu
	uState->stateList.clear();
	//Unit::transitionState(uState);



    if(tile->isHarvestable()){
        //  Harvest
        harvest(uState, tile);
    }
    else if(tile->isAttackable(uState)){
        // Attack
        attack(uState, tile);
    }
    else if(tile->isWalkable()){
        // Walk
        move(uState, tile);
    }
}

void Unit::attack(State::Unit *uState, Tile *tile) {

    if(!uState->canAttack())
        return;

    uint16_t uTargetID = tile->occupant;
	uState->mutate_combatTarget(uTargetID);


    if(Unit::distance(uState, tile->id_) > 1){
        Unit::enqueueState(uState, Constants::State::Combat);
        Unit::move(uState, tile);


    }
    else {
        Unit::transitionState(uState, Constants::State::Combat);

    }



}

void Unit::harvest(State::Unit *uState, Tile *tile) {
    if(!uState->canHarvest())
        return;

    uState->mutate_harvestTile(tile->id_);
    Unit::transitionState(uState, Constants::State::Harvesting);

}

void Unit::enqueueState(State::Unit *uState, Constants::State stateID) {
	uState->stateList()->push_back(stateID);
}

void Unit::transitionState(State::Unit *uState) {
    if(uState->stateList.empty()) {
        // No states to transition to, enter idle state
		uint16_t nextState = Constants::State::Idle;
        //std::cout << "State Transition: " << state->name << " ==> " << nextState->name << "|" << std::endl;
		//std::cout << "State Transition: " << state->id << " ==> " << nextState->id << "|" << std::endl;
        uState->mutate_currentState(nextState);
		StateManager::getInstance().getState(uState->currentState)->init(uState);
        return;
    }

	uint16_t nextState = uState->mutable_stateList());
    //std::cout << "State Transition: " << state->name << " ==> " << nextState->name << "|y" << std::endl;
	//std::cout << "State Transition: " << state->id << " ==> " << nextState->id << "|y"  << std::endl;
	uState->mutate_currentState(nextState);
	uState->stateList.pop_back();
    //state->init(*this);


}

void Unit::transitionState(State::Unit *uState, Constants::State stateID) {
    //std::cout << "State Transition: " << state->name << " ==> " << nextState->name << "|x" << std::endl;
	//std::cout << "State Transition: " << state->id << " ==> " << nextState->id << "|x" << std::endl;
	uState->mutate_currentState(stateID);
	StateManager::getInstance().getState(uState->currentState())->init(uState);
    return;
}

uint16_t Unit::distance(State::Unit *uState, uint16_t tileID) {
	Game *game = Game::getGame(uState->gameID());
	const Tile *sourceTile = game->map.getTile(uState->tile());
	const Tile *targetTile = game->map.getTile(tileID);

    int dim = 0; // TODO
    double d = hypot(sourceTile->x - (targetTile->x + dim), sourceTile->y - (targetTile->y + dim));
    return (int)d - dim;

}


uint16_t Unit::distance(State::Unit *uStateSource, State::Unit *uStateTarget) {
	Game *game = Game::getGame(uStateSource->gameID());
	const State::Player *pState = game->getPlayer(uStateSource->playerID());
	const Tile *sourceTile = game->map.getTile(uStateSource->tile());
	const Tile *targetTile = game->map.getTile(uStateTarget->tile());

	uint16_t targetX = sourceTile->x;
	uint16_t targetY = sourceTile->y;
	uint16_t dimX = floor(targetTile->width / 2);
	uint16_t dimY = floor(targetTile->height / 2);

	double d = hypot(sourceTile->x - (targetX + dimX), sourceTile->y - (targetY + dimY));

	return (int)d - dimX;

}

sf::Vector2f Unit::distanceVector(State::Unit *uState, uint16_t tileID){
	Game *game = Game::getGame(uState->gameID());
	const State::Player *pState = game->getPlayer(uState->playerID());
	const Tile *uTile = game->map.getTile(uState->tile());
	const Tile *targetTile = game->map.getTile(tileID);

	uint16_t dx = uTile->x - targetTile->x;
	uint16_t dy = uTile->y - targetTile->y;

    return sf::Vector2f(dx, dy);
}

uint16_t Unit::closestRecallBuilding(State::Unit *uState) {
	Game *game = Game::getGame(uState->gameID());
	State::Player *pState = game->getPlayer(uState->playerID());

	uint16_t closest;


    int bestDistance = INT_MAX;

    for(uint16_t &uID : pState->units) {
		State::Unit *uTargetState = game->getUnit(uID);

        if(uState->isRecallable()) {

            uint16_t d = Unit::distance(uState, uTargetState);

            if(d < bestDistance) {
				bestDistance = d;
                closest = uID;
            }
        }
    }
    return closest;
}

void Unit::afflictDamage(State::Unit *uState, uint16_t dmg_) {
	Game *game = Game::getGame(uState->gameID());
	State::Player *pState = game->getPlayer(uState->playerID());

	uint16_t maxDamage = uState->health() - dmg_;
	uState->mutate_health(std::max(static_cast<uint16_t>(0), maxDamage));

    if (uState->health() <= 0) {
        Unit::transitionState(uState, Constants::State::Dead);

		Player::checkDefeat(pState);
		game->checkTerminal();
    }

}

bool Unit::isDead(State::Unit *uState) {
    return uState->currentState() == Constants::State::Dead;
}

uint16_t Unit::getDamage(State::Unit *uState, State::Unit *uStateTarget) {

    // TODO better random
    double_t output = uState->damageMin() + (rand() % (uState->damageMax() - uState->damageMin() + 1));
	double_t myDamage = output - uStateTarget->armor() + uState->damagePiercing();

	double_t mini = myDamage * .50;
	double_t output2 = mini + (rand() % (uint16_t)(myDamage - mini + 1));

    return floor(output2);

}

void Unit::setDirection(State::Unit *uState, sf::Vector2f &dir){
    Unit::setDirection(uState, dir.x, dir.y);
}

void Unit::setDirection(State::Unit *uState, uint16_t newX, uint16_t newY){
	uint16_t oldX = uState->worldPositionX();
	uint16_t oldY = uState->worldPositionY();

	uint16_t dx = (newX - oldX);
	uint16_t dy = (newY - oldY);

    if (dx > 0 and dy > 0) {
        // Down Right
		uState->mutate_direction(Constants::D_DownRight);
        //std::cout << "Down Right" << std::endl;
    } else if (dx < 0 and dy > 0) {
        // Down Left
		uState->mutate_direction(Constants::D_DownLeft);
        //std::cout << "Down Left" << std::endl;
    } else if (dx > 0 and dy < 0) {
        // Up Right
		uState->mutate_direction(Constants::D_UpRight);
        //std::cout << "Up Right" << std::endl;
    } else if (dx < 0 and dy < 0) {
        // Up Left
		uState->mutate_direction(Constants::D_UpLeft);
        //std::cout << "Up Left" << std::endl;
    } else if (dx > 0 and dy == 0) {
        // Right
		uState->mutate_direction(Constants::D_Right);
        //std::cout << "Right" << std::endl;
    } else if (dx < 0 and dy == 0) {
        // Left
		uState->mutate_direction(Constants::D_Left);
        //std::cout << "Left" << std::endl;
    } else if (dx == 0 and dy < 0) {
        // Up
		uState->mutate_direction(Constants::D_Up);
        //std::cout << "Up" << std::endl;
    } else if (dx == 0 and dy > 0) {
        // Down
		uState->mutate_direction(Constants::D_Down);
        //std::cout << "Down" << std::endl;
    }



}