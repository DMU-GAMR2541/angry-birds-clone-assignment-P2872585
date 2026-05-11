#pragma once
#include <SFML/Graphics.hpp>
#include <Constants.h>

class GameObject {
	
private:
	
public:
	GameObject() = default;
	~GameObject() = default;

	virtual void Render(sf::RenderWindow& window) = 0;
};