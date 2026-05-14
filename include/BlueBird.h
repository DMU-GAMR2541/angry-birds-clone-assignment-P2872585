#pragma once
#include <vector>
#include "Bird.h"

class BlueBird : public Bird {

private:
	std::vector<GameObject*>* gameObjects;
	sf::Texture* birdTexture;

public:
	BlueBird() = default;
	~BlueBird() override = default;
	BlueBird(b2World& world, float x, float y, sf::Texture& birdTexture, std::vector<GameObject*>* gameObjects);

	bool activateSpecialAbility() override;
};
