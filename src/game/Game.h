//
// Created by Per-Arne on 23.02.2017.
//

#ifndef WARC2SIM_GAME_H
#define WARC2SIM_GAME_H

#include <time.h>
#include <memory>
#include <map>
#include <unordered_map>

#include "player/Player.h"
#include "environment/Tilemap.h"
#include "action/BaseAction.h"
#include <flatbuffers.h>
#include "../flatbuffers/Game_generated.h"
#include "../flatbuffers/Unit_generated.h"
#include "../flatbuffers/Player_generated.h"
class GameMessage;
class GUI;
class Game {
	State::Game *state;


    // Gameclock variables
    clock_t update_next_;
    clock_t render_next_;
    clock_t stats_next_;

    int update_delta_ = 0;
    int render_delta_ = 0;



public:
	


    Tilemap map;

	uint16_t getID();
    int getSeconds();
    long getFrames();

    StateManager stateManager;

	static std::unordered_map<int, Game *> games;
	std::unordered_map<uint16_t, State::Player * > players;
	std::unordered_map<uint16_t, State::Unit *> units;

    
	std::vector<std::shared_ptr<BaseAction>> executedActions; // TODO
    void addAction(std::shared_ptr<BaseAction> action); // TODO

    void loop();
    void update(int ticks);
    void render(int ticks);
    void createPlayers();
    void load_players();


    void start();

    void stop();

    Game(int n_players, bool setup);

    GUI *gui;

    void initGUI();

    void setFPS(int fps_);

    void setUPS(int ups_);

    uint32_t currentFPS = 0;
	uint32_t currentUPS = 0;

    bool checkTerminal();

    bool terminal;




	void deactivateGUI();
	GameMessage serialize();

	static Game *getGame(uint16_t gameID);
	State::Player *getPlayer(uint16_t idx);
	State::Unit *getUnit(uint16_t idx);


	uint16_t createPlayer();
	State::Unit *createUnit(uint16_t unitType);

	uint16_t addPlayer();
	uint16_t addUnit(State::Unit *uState);

	bool removeUnit(uint16_t unitID);

	std::string serialize_json();
	void load(GameMessage& gameMessage);


};


#endif //WARC2SIM_GAME_H
