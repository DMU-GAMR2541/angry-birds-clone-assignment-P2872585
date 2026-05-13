#include "RedBird.h"

RedBird::RedBird(b2World& world, int entityId, float x, float y, sf::Texture& texture) : Bird(world, entityId, x, y, 22.0f, BirdType::Red, texture, 1.0f, 1.0f) {

}

bool RedBird::activateSpecialAbility() {
	// TODO
	return false;
}