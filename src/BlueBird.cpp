#include "BlueBird.h"
#include <cmath>

BlueBird::BlueBird(b2World& world, float x, float y, sf::Texture& birdTexture, std::vector<GameObject*>* gameObjects)
	: Bird(world, x, y, 18.0f, BirdType::Blue, birdTexture, 1.0f, 1.0f), gameObjects(gameObjects), birdTexture(&birdTexture) {

}

bool BlueBird::activateSpecialAbility() {
	if (usedAbility || !body) return false;

	b2Vec2 velocity = body->GetLinearVelocity();
	b2Vec2 position = body->GetPosition();
	b2World* world = body->GetWorld();

	const float spreadAngle = 0.35f;
	float cos = std::cos(spreadAngle);
	float sin = std::sin(spreadAngle);

	float topVx = velocity.x * cos + velocity.y * sin;
	float topVy = -velocity.x * sin + velocity.y * cos;

	float botVx = velocity.x * cos - velocity.y * sin;
	float botVy = velocity.x * sin + velocity.y * cos;

	float spawnX = position.x * Constants::SCALE;
	float spawnY = position.y * Constants::SCALE;

	// Use unique ptr so they stay in memory as gameObjects points to them
	auto topBird = std::make_unique<BlueBird>(*world, spawnX, spawnY - 25.0f, *birdTexture, gameObjects);
	topBird->body->SetLinearVelocity(b2Vec2(topVx, topVy));
	topBird->usedAbility = true;
	topBird->spawn(gameObjects);
	topBird.release();

	auto bottomBird = std::make_unique<BlueBird>(*world, spawnX, spawnY + 25.0f, *birdTexture, gameObjects);
	bottomBird->body->SetLinearVelocity(b2Vec2(botVx, botVy));
	bottomBird->usedAbility = true;
	bottomBird->spawn(gameObjects);
	bottomBird.release();

	usedAbility = true;
	return true;
}
