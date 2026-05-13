#include "Catapult.h"
#include <cmath>
#include <random>
#include "RedBird.h"
#include "YellowBird.h"

Catapult::Catapult(b2World& world, float x, float y, std::vector<GameObject*>* gameObjects, std::map<BirdType, std::shared_ptr<sf::Texture>>& birdTextures)
	: world(&world), gameObjects(gameObjects), birdTextures(&birdTextures) {
	shape.setSize(sf::Vector2f(20.0f, 80.0f));
	shape.setOrigin(10.0f, 0.0f);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color(101, 67, 33)); // Dark Brown

	loadedBird = createRandomBird();
}

void Catapult::onMousePress(float x, float y) {
	if (!loadedBird) return;
	float dx = x - shape.getPosition().x;
	float dy = y - shape.getPosition().y;
	// Maximum pull distance
	if (std::sqrt(dx * dx + dy * dy) <= 100) {
		dragging = true;
		pullPosition = sf::Vector2f(x, y);
	}
}

void Catapult::onMouseDrag(float x, float y) {
	if (!dragging || !loadedBird) return;

	float dx = x - shape.getPosition().x;
	float dy = y - shape.getPosition().y;
	// Maximum pull distance
	float distance = std::sqrt(dx * dx + dy * dy);
	if (distance > 100) {
		// Clamp drag position
		x = shape.getPosition().x + dx * 100 / distance;
		y = shape.getPosition().y + dy * 100 / distance;
	}

	pullPosition = sf::Vector2f(x, y);
	loadedBird->setPosition(pullPosition.x / Constants::SCALE, pullPosition.y / Constants::SCALE);
}

Bird* Catapult::onMouseRelease() {
	if (!dragging || !loadedBird) return nullptr;
	dragging = false;

	float pullX = shape.getPosition().x - pullPosition.x;
	float pullY = shape.getPosition().y - pullPosition.y;

	Bird* fired = loadedBird.release();
	// Enable physics now that it's fired
	fired->getBody()->SetEnabled(true);
	fired->getBody()->ApplyLinearImpulse(b2Vec2(pullX * 0.22f, pullY * 0.22f), fired->getBody()->GetWorldCenter(), true);

	// Put a new bird in the catapult
	loadedBird = createRandomBird();
	return fired;
}

std::unique_ptr<Bird> Catapult::createRandomBird() {
	// Generate a random bird from the BirdType enum
	BirdType type = static_cast<BirdType>(rand() % 4);
	sf::Texture& birdTexture = *birdTextures->at(type);

	float spawnX = shape.getPosition().x;
	float spawnY = shape.getPosition().y;
	std::unique_ptr<Bird> bird;
	switch (type) {
		case BirdType::Red:
			bird = std::make_unique<RedBird>(*world, spawnX, spawnY, birdTexture);
			break;
		case BirdType::Blue:
			bird = std::make_unique<RedBird>(*world, spawnX, spawnY, birdTexture);
			break;
		case BirdType::Yellow:
			bird = std::make_unique<YellowBird>(*world, spawnX, spawnY, birdTexture);
			break;
		case BirdType::Black:
			bird = std::make_unique<RedBird>(*world, spawnX, spawnY, birdTexture);
			break;
		case BirdType::White:
			bird = std::make_unique<RedBird>(*world, spawnX, spawnY, birdTexture);
			break;
	}

	// Ensure that until the bird is fired it doesn't have any physics
	bird->getBody()->SetEnabled(false);
	bird->spawn(gameObjects);
	return bird;
}

void Catapult::Render(sf::RenderWindow& window) {
	window.draw(shape);

	if (dragging) {
		sf::Vertex line[] = {
			sf::Vertex(shape.getPosition(), sf::Color::Black),
			sf::Vertex(pullPosition, sf::Color::Black)
		};
		window.draw(line, 2, sf::Lines);
	}
}

void Catapult::UpdatePhysics() {

}