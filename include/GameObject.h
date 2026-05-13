#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class GameObject {

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void spawn(std::vector<GameObject*>* gameObjects) {
		gameObjects->push_back(this);
	}

	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void UpdatePhysics() = 0;
};