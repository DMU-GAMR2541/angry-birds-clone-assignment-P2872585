#pragma once
#include "Pig.h"

class LargePig : public Pig {
public:
	LargePig() = default;
	~LargePig() override = default;

	LargePig(int entityId, b2World& world, float x, float y, sf::Texture& texture)
		: Pig(entityId, world, x, y, 36.0f, 120, texture) {}
};