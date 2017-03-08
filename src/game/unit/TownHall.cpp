//
// Created by Per-Arne on 24.02.2017.
//

#include "TownHall.h"
#include "../player/Player.h"

void TownHall::construct(State::Unit * state)
{

	

	


	state->mutate_typeID(Constants::Unit_TownHall);
	state->mutate_health(1200);
	state->mutate_maxHealth(1200);
	state->mutate_direction(0);
	state->mutate_goundUnit(true);
	state->mutate_waterUnit(false);
	state->mutate_damageMin(0);
	state->mutate_damageMax(0);
	state->mutate_range(0);
	state->mutate_damagePiercing(0);
	state->mutate_armor(0);

	state->mutate_goldCarry(0);
	state->mutate_lumberCarry(0);
	state->mutate_oilCarry(0);
	state->mutate_carryCapacity(0);
	state->mutate_speed(0);
	state->mutate_sight(4);


	state->mutate_canHarvest(false);
	state->mutate_canAttack(false);
	state->mutate_canMove(false);
	state->mutate_isMilitary(false);
	state->mutate_isStructure(true);


	state->mutate_lumberCost(250);
	state->mutate_goldCost(500);
	state->mutate_oilCost(0);
	state->mutate_spawnDuration(1); //255 * Config::getInstance().getTickModifier();
	state->mutate_foodProduction(1);
	state->mutate_foodConsumption(0);
	state->mutate_width(3);
	state->mutate_height(3);
	state->mutable_name = "Town-Hall";
}
