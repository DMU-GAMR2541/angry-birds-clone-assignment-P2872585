#pragma once
#include "Enemy.h"
class Pig : public Enemy {

public:
	Pig() = default;

	Pig(b2World* world, int health, float size, b2BodyDef* bodyDef) : Enemy(health, world, new sf::CircleShape(size), bodyDef) {
		// Set green fill colour
		sprite->setFillColor(sf::Color(0, 255, 0));
		sprite->setOrigin(size, size); // Set origin to center for proper rotation and positioning
	}

};