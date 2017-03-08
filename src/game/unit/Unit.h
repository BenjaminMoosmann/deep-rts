//
// Created by Per-Arne on 24.02.2017.
//

#ifndef WARC2SIM_UNIT_H
#define WARC2SIM_UNIT_H

#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <map>
#include <SFML/Graphics/Texture.hpp>

#include "../environment/Tile.h"
#include "../state/StateManager.h"
#include "../Config.h"

#include "../../flatbuffers/Game_generated.h"
#include "../../flatbuffers/Unit_generated.h"
#include "../../flatbuffers/Player_generated.h"


class Player;
class BaseState;



class Unit{

public:

    // Graphics
    double animationInterval = .2 * 10;
    int animationTimer = 0;
    int animationIterator = 0;

    static bool build(State::Unit *uState, uint16_t idx);
    static void spawn(State::Unit *uState, uint16_t spawnTile, bool spawnInstantly);
    static void despawn(State::Unit *uState);
    static void update(State::Unit *uState);
	static uint16_t centerTile(State::Unit *uState);
    
	static void enqueueState(State::Unit *uState, Constants::State stateID);
    static void transitionState(State::Unit *uState);
    static void transitionState(State::Unit *uState, Constants::State stateID);
    static void setPosition(State::Unit *uState, Tile *tile);
    static void rightClick(State::Unit *uState, Tile *tile);
    static void move(State::Unit *uState, Tile *tile);
    static void attack(State::Unit *uState, Tile *tile);
    static void harvest(State::Unit *uState, Tile *tile);
	static void afflictDamage(State::Unit *uState, uint16_t dmg_);
	static uint16_t getDamage(State::Unit *uState, State::Unit *uStateTarget);
	static void setDirection(State::Unit *uState, uint16_t newX, uint16_t newY);
	static void setDirection(State::Unit *uState, sf::Vector2f &dir);
	static void moveRelative(State::Unit *uState, uint16_t x, uint16_t y);
	static void rightClickRelative(State::Unit *uState, uint16_t x, uint16_t y);
	static bool isDead(State::Unit *uState);

    static uint16_t distance(State::Unit *uState, uint16_t tileID);
	static uint16_t distance(State::Unit *uStateSource, State::Unit *uStateTarget);
    static sf::Vector2f distanceVector(State::Unit *uState, uint16_t tileID);
    static void clearTiles(State::Unit *uState);
	static uint16_t closestRecallBuilding(State::Unit *uState);


};

#endif //WARC2SIM_UNIT_H
