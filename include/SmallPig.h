#pragma once
#include "Pig.h"

class SmallPig : public Pig {
public:
	SmallPig() = default;
	~SmallPig() override = default;

	SmallPig(int entityId, b2World& world, float x, float y, sf::Texture& texture)
		: Pig(entityId, world, x, y, 18.0f, 20, texture) {}
};