#pragma once
#include "Pig.h"

class SmallPig : public Pig {
public:
	SmallPig() = default;
	~SmallPig() override = default;

	SmallPig(b2World& world, float x, float y, sf::Texture& texture) : Pig(world, x, y, 18.0f, 20, texture) {}
};