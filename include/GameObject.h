#pragma once
#include <SFML/Graphics.hpp>
class GameObject {

protected:
	//Box2D works in meters. SFML works in pixels.
	const float SCALE = 30.0f;

	//Can set a definition for PI.
	const float PI = 3.1415927;
	
private:
	
public:
	GameObject() = default;
	~GameObject() = default;

	virtual void Render(sf::RenderWindow& window) = 0;
};