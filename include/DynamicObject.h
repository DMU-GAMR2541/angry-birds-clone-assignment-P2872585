#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>
#include <list>
class DynamicObject : public GameObject {

protected:
	sf::Shape* sprite;
	b2Body* body;
	//b2Body body;
	//b2BodyDef b2_bodyDef;
	//b2PolygonShape b2_dynamicBox;
	//b2CircleShape b2_dynamicCircle;
	//sf::Sprite

public:
	DynamicObject() = default;
	~DynamicObject() = default;
	DynamicObject(int entityId, b2World* world, sf::Shape* sprite, b2BodyDef* bodyDef, b2FixtureDef* materialDef) {
		this->sprite = sprite;

		this->body = world->CreateBody(bodyDef);

		b2CircleShape b2_circleShape;
		b2_circleShape.m_radius = 15.0f / SCALE;

		//b2FixtureDef b2_ballFixture;
		//b2_ballFixture.shape = &b2_circleShape;
		//b2_ballFixture.density = 1.0f;
		//b2_ballFixture.restitution = 0.5f; // Bounciness
		this->body->CreateFixture(materialDef);
		//this->body = body;

		this->body->GetUserData().pointer = entityId;
	}

	// TODO: Move into a world manager class
	void addEntity(std::vector<GameObject*>* gameObjects) {
		// TODO: Check for entity ID conflicts before adding to the list. Add a test.
		gameObjects->push_back(this);
	}

	void GameObject::Render(sf::RenderWindow& window) override {
		sprite->setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		window.draw(*sprite);
	}

	b2Vec2 getPosition() const {
		return body->GetPosition();
	}

	void setPosition(float x, float y) {
		body->SetTransform(b2Vec2(x, y), body->GetAngle());
	}
};