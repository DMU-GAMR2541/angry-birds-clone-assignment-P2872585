#pragma once
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>
#include "DynamicObject.h"
#include "Bird.h"

class Catapult : public DynamicObject {

private:
	std::unique_ptr<Bird> loadedBird;
	bool dragging = false;
	sf::Vector2f pullPosition;
	sf::RectangleShape shape;
	b2World* world;
	std::vector<GameObject*>* gameObjects;
	std::map<BirdType, std::shared_ptr<sf::Texture>>* birdTextures;

	std::unique_ptr<Bird> createRandomBird();

public:
	Catapult() = default;
	~Catapult() override = default;
	Catapult(b2World& world, float x, float y, std::vector<GameObject*>* gameObjects, std::map<BirdType, std::shared_ptr<sf::Texture>>& birdTextures);

	bool isDragging() {
		return dragging;
	}

	void onMousePress(float x, float y);
	void onMouseDrag(float x, float y);

	Bird* onMouseRelease();

	void Render(sf::RenderWindow& window) override;
	void UpdatePhysics() override;
};