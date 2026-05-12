#pragma once
#include "Bird.h"

class RedBird : public Bird {

public:
	RedBird() = default;
	~RedBird() override = default;
	RedBird(b2World& world, int entityId, float x, float y, sf::Texture& texture);

	bool activateSpecialAbility() override;
};