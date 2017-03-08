//
// Created by Per-Arne on 24.02.2017.
//


#include "Player.h"
#include "../unit/Peasant.h"
#include "../Game.h"
#include "../util/ColorConverter.hpp"
#include "../algorithms/RANDOM/AlgoRandom.h"
#include "../unit/TownHall.h"


void Player::construct(State::Player *playerState)
{
	
	playerState->name = "Player: " + std::to_string(playerState->id);
	playerState->faction = State::Faction::Faction_Human;
	playerState->gold = 1500;
	playerState->lumber = 750;
	playerState->oil = 0;
	playerState->foodConsumption = 0;
	playerState->food = 1;
	playerState->statGoldGather = 0;
	playerState->statLumberGather = 0;
	playerState->statOilGather = 0;
	playerState->statUnitDamageDone = 0;
	playerState->statUnitDamageTaken = 0;
	playerState->statUnitBuilt = 0;
	playerState->statUnitMilitary = 0;

}

void Player::update(State::Player *state) {

	Game* game = Game::getGame(state->gameID);

	for (auto &uID : state->units) {
		State::Unit *uState = game->units[uID];
		Unit::update(uState);
	}


	/*

    std::vector<State::Unit *>::iterator it;
    for(it = units.begin(); it != units.end();) {
        (*it)->update();

        if((*it)->removedFromGame) {
            it = units.erase(it);
        }else {
            it++;
        }
    }

    if(algorithm_) {
        algorithm_->update();
    }
	*/
}

void Player::click(State::Game *game, std::string direction, uint16_t tileIdx) {
	/*Tile &tile = game_.map.tiles.at(tileIdx);
	assert(&tile);

	if (direction == "left") {


		if (tile.occupant) {
			targetedUnit = tile.occupant;
		}
		else {
			targetedUnit = NULL;
		}


	}
	else if (direction == "right") {
		if (targetedUnit) {
			targetedUnit->rightClick(tile);
		}
	}
	else {
		throw std::invalid_argument("Must be right or left!");
	}*/

}

uint16_t Player::getScore(State::Player *pState) {
	uint16_t GOLD_VALUE = 2;
	uint16_t LUMBER_VALUE = 1;
	uint16_t OIL_VALUE = 3;

	


	double_t dmg = pState->statUnitDamageDone - (pState->statUnitDamageTaken * .5);
	uint16_t gatherScore =pState->statGoldGather * GOLD_VALUE + (pState->statLumberGather * LUMBER_VALUE) * .5;
	uint16_t builtScore = pState->statUnitBuilt * 10;
	uint16_t damageScore = std::max(0.0, dmg);
	uint16_t unitScore = pState->units.size() * 5;


	uint16_t militaryScore = 0;
	uint16_t defenceScore = 0;


    return gatherScore + builtScore + unitScore + militaryScore + defenceScore + damageScore;

}


bool Player::checkDefeat(State::Player *state){

    bool isDefeated = (state->units.size() > 0);
    state->defeated = isDefeated;
    return isDefeated;
}

bool Player::canPlace(State::Player *pState, State::Unit *builder, State::Unit *target, Tile *tileTarget) {
	Game *game = Game::getGame(pState->gameID);
	State::Unit *builder = builder;
	State::Unit *target =target;

    for (auto &tile : game->map.getTiles(tileTarget, target->width, target->height)) {
        if(tile == builder->tile) // Ignore tile of the builder, this is handled in Unit::Build when builder despawns
            continue;

        if(!tile->isBuildable()) {
            return false;
        }

    }

    return true;
}

bool Player::canAfford(State::Player *pState, State::Unit *uStates) {
    return pState->gold >= uStates->goldCost and pState->lumber >= uStates->lumberCost and pState->oil >= uStates->oilCost;

}


uint16_t Player::spawn(State::Player * pState, uint16_t tileID)
{
	Game *game = Game::getGame(pState->gameID);
	assert(game);

	State::Unit *sUnit;
	if (pState->faction == State::Faction::Faction_Human) // Human
	{
		sUnit = game->createUnit(Constants::Unit_Peasant);
	}
	else if (pState->faction == State::Faction::Faction_Orc) // Orc
	{
		sUnit = game->createUnit(Constants::Unit_Peasant);
	}
	else {
		assert(false);
	}

	Unit::spawn(sUnit, tileID, true);

	return sUnit->id;
}
