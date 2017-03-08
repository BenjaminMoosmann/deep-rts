#include <zmq.h>
#include <zmq_utils.h>
#include "../../third_party/zmq.hpp"
#include "../../third_party/json.hpp"
#include "../../proto/GameMessage.pb.h"
#include "../../Game.h"

#include <thread>
#include <iostream>
#include "zmqAI.h"

zmqAI::zmqAI(int gameID, int playerID): gameID(gameID), playerID(playerID) {

}

zmqAI::zmqAI(){}



void zmqAI::start() {


	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	socket.bind("tcp://*:5000");

	clock_t now = clock();
	clock_t next = now + 1000;
	int counter = 0;

	while (true) {
		zmq::message_t request;
		socket.recv(&request);
	
		std::string request_str = std::string(static_cast<char*>(request.data()), request.size());
		json data = json::parse(request_str.data());
		
		if (data["type"] == "getState") {
			// This Means get state
			std::string json;
			GameMessage srs = Game::getGame(gameID)->serialize();
			srs.SerializeToString(&json);
			zmq::message_t reply(json.size());
			memcpy(reply.data(), json.data(), json.size());
			socket.send(reply);
		}
		else if (data["type"] == "doAction") {
			// This Means get state
			int tileIndex = data["data"][0];
			std::string mouseButton = data["data"][1];

			Game::getGame(gameID)->getPlayer(playerID)->click(mouseButton, tileIndex);

			json retData;
			retData["score"] = Game::getGame(gameID)->getPlayer(playerID)->getScore();
			retData["terminal"] = Game::getGame(gameID)->getPlayer(playerID)->defeated;
			std::string dump = retData.dump();
			zmq::message_t reply(dump.size());
			memcpy(reply.data(), dump.data(), dump.size());
			socket.send(reply);
		}
		counter += 1;

		now = clock();
		if (now > next) {
			next = now + 1000;
			std::cout << "zmqAI Iterations: " << counter << std::endl;
			counter = 0;
		}

	}



}


std::shared_ptr<zmqAI> zmqAI::createInstance(int gameID, int playerID) {

	std::shared_ptr<zmqAI> ai = std::shared_ptr<zmqAI>(new zmqAI(gameID, playerID));
	std::thread t = std::thread(&zmqAI::start, ai);
	t.detach();
	return ai;

}