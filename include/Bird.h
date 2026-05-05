#pragma once
#include "DynamicObject.h"
enum BirdType {
	Red,
	Blue,
	Yellow,
	Black,
	White
};

class Bird : public DynamicObject {

public:
	Bird() = default;

	Bird(b2World* world, b2BodyDef* bodyDef, BirdType type, float size) : DynamicObject(world, new sf::CircleShape(size), bodyDef) {
		sprite->setOrigin(size, size); // Set origin to center for proper rotation and positioning
		// TODO: Use sprites instead of colours
		switch (type) {
			case BirdType::Red:
				sprite->setFillColor(sf::Color(255, 0, 0));
				break;
			case BirdType::Blue:
				sprite->setFillColor(sf::Color(0, 0, 255));
				break;
			case BirdType::Yellow:
				sprite->setFillColor(sf::Color(255, 255, 0));
				break;
			case BirdType::Black:
				sprite->setFillColor(sf::Color(0, 0, 0));
				break;
			case BirdType::White:
				sprite->setFillColor(sf::Color(255, 255, 255));
				break;
			default:
				sprite->setFillColor(sf::Color(128, 128, 128));
				break;
		}
	}
};
