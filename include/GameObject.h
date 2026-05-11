#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class GameObject {

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void UpdatePhysics() = 0;
};