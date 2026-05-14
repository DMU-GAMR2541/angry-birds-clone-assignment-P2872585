#pragma once
#include "Pig.h"

class LargePig : public Pig {
public:
	LargePig() = default;
	~LargePig() override = default;

	LargePig(b2World& world, float x, float y, sf::Texture& texture) : Pig(world, x, y, 28.0f, 240, texture) {}
};