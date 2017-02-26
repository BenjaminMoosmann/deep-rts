//
// Created by Per-Arne on 23.02.2017.
//

#ifndef WARC2SIM_GAME_H
#define WARC2SIM_GAME_H

#include <time.h>
#include <memory>
#include "player/Player.h"
#include "environment/Tilemap.h"


class GUI;
class Game {

    int n_players;

    // Gameclock variables
    clock_t _update_next;
    clock_t _render_next;
    clock_t _caption_next;
    clock_t _stats_next;

    int _update_interval = 0;
    int _render_interval = 0;
    int _caption_interval = 1000;

    int _update_delta = 0;
    int _render_delta = 0;


    bool running;
    long ticks = 0;

public:
    Tilemap map;
    int fps;
    int ups;

    int getSeconds();
    long getFrames();

    std::vector<Player*> players;


    void loop();
    void update(int ticks);
    void render(int ticks);
    void create_players();
    void load_players();


    void start();

    void stop();

    Game(int n_players);

    GUI *gui;
};


#endif //WARC2SIM_GAME_H
