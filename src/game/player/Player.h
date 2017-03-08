//
// Created by Per-Arne on 24.02.2017.
//

#ifndef WARC2SIM_PLAYER_H
#define WARC2SIM_PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "../unit/Unit.h"
#include "../environment/Tile.h"
#include "../unit/InventoryManager.h"
#include "../algorithms/base/Algorithm.h"

#include "../../flatbuffers/Game_generated.h"
#include "../../flatbuffers/Unit_generated.h"
#include "../../flatbuffers/Player_generated.h"

class AlgoRandom;


class Game;
class Player {
public:
	static void construct(State::Player *playerState);
    static void update(State::Player *state);
	static void click(State::Game *game, std::string direction, uint16_t tileIdx);
	static uint16_t Player::spawn(State::Player * pState, uint16_t tileID);
	static bool canPlace(State::Player *pState, State::Unit *builder, State::Unit *target, Tile *tileTarget);
	static bool canAfford(State::Player *pState, State::Unit *uStates);
	static bool checkDefeat(State::Player *state);

	static uint16_t getScore(State::Player *pState);
};


#endif //WARC2SIM_PLAYER_H
