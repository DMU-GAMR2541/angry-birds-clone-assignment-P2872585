#pragma once
#include "Pig.h"

class MediumPig : public Pig {
public:
	MediumPig() = default;
	~MediumPig() override = default;

	MediumPig(b2World& world, float x, float y, sf::Texture& texture) : Pig(world, x, y, 26.0f, 60, texture) {}
};