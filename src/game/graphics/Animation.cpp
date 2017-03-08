//
// Created by Per-Arne on 25.02.2017.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "Animation.h"
#include "../Constants.h"


void Animation::add(const int unit, const int state, const int direction, int x, int y, int w, int h, int wrs, int hrs, sf::Texture* texture, bool flip) {

    std::shared_ptr<sf::Sprite> sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
    sprite->setTexture(*texture);
    if(flip)
        w * -1;
    sprite->setTextureRect(sf::IntRect(x, y, w, h));
    sprite->setScale((double)wrs/w,(double)hrs/h);
    Animation::sprites[unit][state][direction].push_back(sprite);



}

void Animation::setup() {
    peasant = std::shared_ptr<sf::Texture>(new sf::Texture());
    peasant->loadFromFile("data/textures/human/peasant.png");

    buildings = std::shared_ptr<sf::Texture>(new sf::Texture());
    buildings->loadFromFile("data/textures/human/buildings.png");


    setupPeasant();
    setupTownHall();


}

void Animation::setupPeasant(){
    int P = Constants::Unit_Peasant;


    ///
    /// Walking
    ///
    Animation::add(P, Constants::State_Walking, Constants::D_Up, 18, 8,  25, 23, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Up, 18, 46,  23, 28, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Up, 18, 86,  23, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Up, 18, 122,  23, 30, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Up, 18, 159,  24, 27, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Walking, Constants::D_Down, 166, 7,  24, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Down, 169, 45,  22, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Down, 167, 85,  26, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Down, 168, 121,  23, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Down, 167, 158,  24, 27, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Walking, Constants::D_Left, 97, 4,  14, 31, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_Left, 91, 42,  24, 30, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_Left, 96, 82,  16, 31, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_Left, 91, 118,  23, 30, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_Left, 95, 155,  20, 30, 32, 32, &*peasant, true);

    Animation::add(P, Constants::State_Walking, Constants::D_Right, 97, 4,  14, 31, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Right, 91, 42,  24, 30, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Right, 96, 82,  16, 31, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Right, 91, 118,  23, 30, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_Right, 95, 155,  20, 30, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Walking, Constants::D_UpRight, 56, 6,  22, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_UpRight, 55, 44,  26, 30, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_UpRight, 56, 84,  24, 29, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_UpRight, 56, 119,  23, 29, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_UpRight, 57, 156,  21, 28, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Walking, Constants::D_UpLeft, 56, 6,  22, 26, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_UpLeft, 55, 44,  26, 30, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_UpLeft, 56, 84,  24, 29, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_UpLeft, 56, 119,  23, 29, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_UpLeft, 57, 156,  21, 28, 32, 32, &*peasant, true);

    Animation::add(P, Constants::State_Walking, Constants::D_DownRight, 128, 3,  21, 31, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_DownRight, 128, 41,  20, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_DownRight, 130, 82,  19, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_DownRight, 126, 119,  26, 29, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Walking, Constants::D_DownRight, 126, 156,  26, 28, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Walking, Constants::D_DownLeft, 128, 3,  21, 31, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_DownLeft, 128, 41,  20, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_DownLeft, 130, 82,  19, 26, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_DownLeft, 126, 119,  26, 29, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Walking, Constants::D_DownLeft, 126, 156,  26, 28, 32, 32, &*peasant, true);

    ///
    /// Harvesting
    ///
    Animation::add(P, Constants::State_Harvesting,Constants::D_Down,168, 196,  24, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Down,160, 228,  28, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Down,168, 274,  23, 24, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Down,174, 317,  22, 37, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Down,173, 367,  22, 24, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Harvesting,Constants::D_Up,19, 190,  31, 32, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Up,19, 230,  30, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Up,19, 260,  23, 41, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Up,19, 304,  21, 41, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Up,18, 356,  24, 36, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Harvesting,Constants::D_DownRight,129, 196,  21, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownRight,122, 231,  25, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownRight,129, 273,  19, 29, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownRight,133, 319,  37, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownRight,134, 366,  32, 28, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Harvesting,Constants::D_DownLeft,129, 196,  21, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownLeft,122, 231,  25, 26, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownLeft,129, 273,  19, 29, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownLeft,133, 319,  37, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_DownLeft,134, 366,  32, 28, 32, 32, &*peasant, true);

    Animation::add(P, Constants::State_Harvesting,Constants::D_UpRight,56, 196,  27, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpRight,56, 231,  21, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpRight,56, 270,  30, 30, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpRight,56, 309,  31, 35, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpRight,56, 362,  32, 30, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Harvesting,Constants::D_UpLeft,56, 196,  27, 25, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpLeft,56, 231,  21, 25, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpLeft,56, 270,  30, 30, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpLeft,56, 309,  31, 35, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_UpLeft,56, 362,  32, 30, 32, 32, &*peasant, true);

    Animation::add(P, Constants::State_Harvesting,Constants::D_Right,96, 194,  19, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Right,94, 228,  18, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Right,93, 268,  27, 32, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Right,94, 314,  36, 29, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Right,94, 364,  35, 27, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Harvesting,Constants::D_Left,96, 194,  19, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Left,94, 228,  18, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Left,93, 268,  27, 32, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Left,94, 314,  36, 29, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Left,94, 364,  35, 27, 32, 32, &*peasant, true);

    
    ///
    /// Combat
    ///
    Animation::add(P, Constants::State_Combat,Constants::D_Down,168, 196,  24, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Down,160, 228,  28, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Down,168, 274,  23, 24, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Down,174, 317,  22, 37, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Down,173, 367,  22, 24, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Combat,Constants::D_Up,19, 190,  31, 32, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Up,19, 230,  30, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Up,19, 260,  23, 41, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Up,19, 304,  21, 41, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Up,18, 356,  24, 36, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Combat,Constants::D_DownRight,129, 196,  21, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_DownRight,122, 231,  25, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_DownRight,129, 273,  19, 29, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_DownRight,133, 319,  37, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_DownRight,134, 366,  32, 28, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Combat,Constants::D_DownLeft,129, 196,  21, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_DownLeft,122, 231,  25, 26, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_DownLeft,129, 273,  19, 29, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_DownLeft,133, 319,  37, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_DownLeft,134, 366,  32, 28, 32, 32, &*peasant, true);

    Animation::add(P, Constants::State_Combat,Constants::D_UpRight,56, 196,  27, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_UpRight,56, 231,  21, 25, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_UpRight,56, 270,  30, 30, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_UpRight,56, 309,  31, 35, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_UpRight,56, 362,  32, 30, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Combat,Constants::D_UpLeft,56, 196,  27, 25, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_UpLeft,56, 231,  21, 25, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_UpLeft,56, 270,  30, 30, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_UpLeft,56, 309,  31, 35, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_UpLeft,56, 362,  32, 30, 32, 32, &*peasant, true);

    Animation::add(P, Constants::State_Combat,Constants::D_Right,96, 194,  19, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Right,94, 228,  18, 27, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Right,93, 268,  27, 32, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Right,94, 314,  36, 29, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat,Constants::D_Right,94, 364,  35, 27, 32, 32, &*peasant, false);

    Animation::add(P, Constants::State_Combat,Constants::D_Left,96, 194,  19, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_Left,94, 228,  18, 27, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_Left,93, 268,  27, 32, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_Left,94, 314,  36, 29, 32, 32, &*peasant, true);
    Animation::add(P, Constants::State_Combat,Constants::D_Left,94, 364,  35, 27, 32, 32, &*peasant, true);

    Animation::add(P, Constants::State_Idle, Constants::D_Down,166, 7,  24, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Dead, Constants::D_Down,166, 7,  24, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Spawning, Constants::D_Down,166, 7,  24, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Despawned, Constants::D_Down,166, 7,  24, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat, Constants::D_Down,166, 7,  24, 26, 32, 32, &*peasant, false);
    Animation::add(P, Constants::State_Combat, Constants::D_Down,0, 0,  40, 40, 32, 32, &*peasant, false);

}

void Animation::setupTownHall(){
    int P = Constants::Unit_TownHall;

    Animation::add(P, Constants::State_Idle, Constants::D_Down,270, 150,  110, 100, 96, 96, &*buildings, false);
    Animation::add(P, Constants::State_Idle, Constants::D_Down,270, 150,  110, 100, 96, 96, &*buildings, false);
    Animation::add(P, Constants::State_Dead, Constants::D_Down,270, 150,  110, 100, 96, 96, &*buildings, false);
    Animation::add(P, Constants::State_Spawning, Constants::D_Down,270, 150,  110, 100, 96, 96, &*buildings, false);
    Animation::add(P, Constants::State_Despawned,Constants::D_Down,270, 150,  110, 100, 96, 96, &*buildings, false);
    Animation::add(P, Constants::State_Combat, Constants::D_Down,270, 150,  110, 100, 96, 96, &*buildings, false);
    Animation::add(P, Constants::State_Harvesting,Constants::D_Down,270, 150,  110, 100, 96, 96, &*buildings, false);





}

sf::Sprite &Animation::getNext(State::Unit * unit) {
    int state = unit->current_state;
    int iteration = unit->animationIterator;
    int unitId = unit->typeId;
    int direction = unit->direction;

    std::vector<std::shared_ptr<sf::Sprite>> &items = Animation::sprites[unitId][state][direction];

    if(items.size() == 0) {
        std::vector<std::shared_ptr<sf::Sprite>> &items = Animation::sprites[unitId][Constants::State_Idle][Constants::D_Down];
        assert(items.size() > 0);
        std::shared_ptr<sf::Sprite> &sprite = items[iteration % items.size()];
        return *sprite;
    }
    std::shared_ptr<sf::Sprite> &sprite = items[iteration % items.size()];


    return *sprite;


}