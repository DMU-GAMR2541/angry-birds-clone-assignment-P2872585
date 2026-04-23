#pragma once
#include <SFML/Graphics.hpp>
class GameObject {

private:
	
public:
	GameObject() = default;
	~GameObject() = default;

	virtual void Render(sf::RenderWindow& window) = 0;
};