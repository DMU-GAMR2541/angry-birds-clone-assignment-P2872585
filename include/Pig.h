#pragma once
#include "Enemy.h"
class Pig : public Enemy {

protected:
	sf::Sprite sprite;
	float radius;

public:
	Pig() = default;
	~Pig() override = default;

	Pig(b2World& world, float x, float y, float size, int health, sf::Texture& texture);

	void Render(sf::RenderWindow& window) override;

	void UpdatePhysics() override;

	bool checkIfPopped() const {
		return markRemoved;
	}

	sf::Sprite getSprite() const {
		return sprite;
	}
};