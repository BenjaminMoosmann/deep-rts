//
// Created by Per-Arne on 24.02.2017.
//

#include "Peasant.h"
#include "../player/Player.h"

void Peasant::construct(State::Unit * state)
{
	state->mutate_typeID(Constants::Unit_Peasant);
	state->mutate_health(30);
	state->mutate_maxHealth(30);
	state->mutate_direction(0);
	state->mutate_goundUnit(true);
	state->mutate_waterUnit(false);
	state->mutate_damageMin(2);
	state->mutate_damageMax(9);
	state->mutate_range(1);
	state->mutate_damagePiercing(2);
	state->mutate_armor(0);
	state->mutate_goldCarry(0);
	state->mutate_lumberCarry(0);
	state->mutate_oilCarry(0);
	state->mutate_carryCapacity(10);
	state->mutate_speed(10);
	state->mutate_sight(4);
	state->mutate_canHarvest(true);
	state->mutate_canAttack(true);
	state->mutate_canMove(true);
	state->mutate_isMilitary(false);
	state->mutate_isStructure(false);
	state->mutate_lumberCost(0);
	state->mutate_goldCost(400);
	state->mutate_oilCost(0);
	state->mutate_spawnDuration(45 * Config::getInstance().getTickModifier());
	state->mutate_foodProduction(0);
	state->mutate_foodConsumption(1);
	state->mutate_width(1);
	state->mutate_height(1);
	state->mutable_name = "Peasant";



}
