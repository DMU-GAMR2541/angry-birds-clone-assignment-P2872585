#pragma once
#include "Enemy.h"
class Pig : public Enemy {

public:
	Pig() = default;

	Pig(int health, float size) : Enemy(health, new sf::CircleShape(size)) {
		// Set green fill colour
		shape->setFillColor(sf::Color(0, 255, 0));
	}

};