#pragma once
#include "DynamicObject.h"
class Bird : DynamicObject {

	Bird(BirdType type, float size) : DynamicObject(new sf::CircleShape(size)) {
		switch (type) {
			case BirdType::Red:
				shape->setFillColor(sf::Color(255, 0, 0));
				break;
			case BirdType::Blue:
				shape->setFillColor(sf::Color(0, 0, 255));
				break;
			case BirdType::Yellow:
				shape->setFillColor(sf::Color(255, 255, 0));
				break;
			case BirdType::Black:
				shape->setFillColor(sf::Color(0, 0, 0));
				break;
			case BirdType::White:
				shape->setFillColor(sf::Color(255, 255, 255));
				break;
			default:
				shape->setFillColor(sf::Color(128, 128, 128));
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