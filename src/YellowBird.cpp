#include "YellowBird.h"

YellowBird::YellowBird(b2World& world, float x, float y, sf::Texture& texture) : Bird(world, x, y, 22.0f, BirdType::Yellow, texture, 1.0f, 1.0f) {

}

bool YellowBird::activateSpecialAbility() {
    // TODO
    return false;
}