//
// Created by Per-Arne on 24.02.2017.
//


#include "Spawning.h"
#include "../unit/Unit.h"
#include "../util/Pathfinder.h"
#include "../player/Player.h"

void Spawning::update(Unit& unit)const{
    unit.spawnTimer += 1;

   
    if(unit.spawnTimer >= unit.spawnDuration) {

		// Check if tile is occupied, if it is. We attempt to find a new one
		if (!unit.tile && unit.getSpawnTile().getOccupant()) {
			if (unit.builtByID != Constants::None) {
				Tile *newSpawnTile = Pathfinder::find_first_walkable_tile(unit.getBuiltBy().centerTile());
				unit.spawnTileID = newSpawnTile->id;
			}
			else {
				// Unit must simply wait for tile to be available
				return;
			}
		}

        // Unit can spawn
        unit.setPosition(unit.getSpawnTile());
        unit.transitionState();
		if (unit.structure) {
			unit.direction = Constants::Direction::Up;
		}

    }

}

void Spawning::init(Unit & unit)const{

}

void Spawning::end(Unit & unit)const{
	unit.builtByID = -1;
}
