#pragma once
#include "DynamicObject.h"
class Bird : DynamicObject {

	Bird(BirdType type, float size) : DynamicObject(new sf::CircleShape(size)) {
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

enum BirdType {
	Red,
	Blue,
	Yellow,
	Black,
	White
};