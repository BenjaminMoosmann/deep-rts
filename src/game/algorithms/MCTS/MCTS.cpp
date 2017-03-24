//
// Created by Per-Arne on 04.03.2017.
//

#include "MCTS.h"
#include "../../player/Player.h"
#include "MCTSNode.h"
#include "../../Game.h"
#include <SFML/System/Clock.hpp>

MCTS::MCTS(Player *player) : Algorithm(player) {


    int _apm_interval = 1000000 / ( Config::getInstance().getAPM() / 60.0);

    timeBudget = _apm_interval; // 1 second
    depthBudget = 10; // Depth budget (Tree depth)
	epsilon = 0.9;	// Start of epsilon
	epsilonModifier = 1000000; // Number of iterations to reach epsilon 0.1
	epsilonDecent = epsilon / epsilonModifier; // How much epsilon decrease with per iteration
	playerID = player->id_;  // Index of selected player


    sim = new Game(4, false);
    sim->addPlayer();
    sim->addPlayer();
    sim->addPlayer();
    sim->addPlayer();

    sim->deactivateGUI();
    /*sim->doDisplay = true;
    sim->initGUI();
    sim->stop(); // Set Running to false. This allows loop() to only run once (Iterate)
    sim->setFPS(INT32_MAX);
    sim->setUPS(INT32_MAX);*/

}

void MCTS::calculate(MCTSNode root){
    sf::Clock clock;
    sf::Time now = clock.getElapsedTime();
    auto nowMicroSec = now.asMicroseconds();
	auto timeout = nowMicroSec + timeBudget;

	MCTSNode &current = root;
	// Load up game state
	long counter = 0;
    std::uniform_real_distribution<> dist(0, 1);
    std::uniform_int_distribution<> actionDist(0, actionSpace.size());

	while (nowMicroSec < timeout) {
        now = clock.getElapsedTime();		// Update clock
        nowMicroSec = now.asMicroseconds();

		if (current.children.size() == 0) {
			// Has no children, Select random action


		}
		else if (dist(random_engine) < epsilon) {
			// Explore (Random Action)
            auto action = actionSpace[actionDist(random_engine)];



			epsilon -= epsilonDecent;
		}
		else {
			// Exploit (Use domain experience)


		}


        sim->loop();
		counter++;
	}

    player->queueAction(static_cast<Constants::Action >(1));
	std::cout << "Iterations: " << std::to_string(counter) << " | " << timeout / 1000 << "ms" <<std::endl;
	

}

int MCTS::findAction() {

}

void MCTS::train() {

}

void MCTS::reset() {

}

void MCTS::update() {
    // Tick happended

    /*sim->load(&player->game_);

    root = MCTSNode(NULL, 0, 0);
    calculate(root);*/
}

bool MCTS::terminal() {
	return false;
}

