#pragma once
#include "DynamicObject.h"
enum BirdType {
	Red,
	Blue,
	Yellow,
	Black,
	White
};

class Bird : public DynamicObject {

protected:
	BirdType birdType;
	sf::Sprite sprite;
	bool usedAbility = false;

	Bird(b2World& world, float x, float y, float radius, BirdType type, sf::Texture& texture, float density, float gravityScale);

public:
	Bird() = default;
	~Bird() override = default;

	BirdType getBirdType() const {
		return birdType;
	}

	bool hasUsedAbility() const {
		return usedAbility;
	}

	void Render(sf::RenderWindow& window) override;

	void UpdatePhysics() override;

	virtual bool activateSpecialAbility() = 0;
};
