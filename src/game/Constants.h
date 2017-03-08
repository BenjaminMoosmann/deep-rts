//
// Created by Per-Arne on 24.02.2017.
//

#ifndef WARC2SIM_CONSTANTS_H
#define WARC2SIM_CONSTANTS_H

namespace Constants{
    const int Unit_Peasant = 0;
    const int Unit_Peon = 1;
    const int Unit_TownHall = 2;

    const int Player_Race_Human = 0;
    const int Player_Race_Orc = 1;

    const int Tile_Spawn = 16;
    const int Tile_Grass = 271;


	enum State {
		Idle = 8,
		Spawning = 1,
		Walking = 2,
		Despawned = 3,
		Harvesting = 4,
		Building = 5,
		Combat = 6,
		Dead = 7,
	};

    const int Pathfinding_Walkable = 1;
    const int Pathfinding_All = 2;

    const int D_Down = 0;
    const int D_Up = 1;
    const int D_Left = 2;
    const int D_Right = 3;
    const int D_DownLeft = 4;
    const int D_DownRight = 5;
    const int D_UpLeft = 6;
    const int D_UpRight = 7;


    // Simple actions
    const int ACTION_NEXT_UNIT = 0;
    const int ACTION_PREVIOUS_UNIT = 1;
    const int ACTION_RC_LEFT = 2;
    const int ACTION_RC_RIGHT = 3;
    const int ACTION_RC_UP = 4;
    const int ACTION_RC_DOWN = 5;
    const int ACTION_RC_UPLEFT = 6;
    const int ACTION_RC_UPRIGHT = 7;
    const int ACTION_RC_DOWNLEFT = 8;
    const int ACTION_RC_DOWNRIGHT = 9;


}






#endif //WARC2SIM_CONSTANTS_H
