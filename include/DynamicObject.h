#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>

class DynamicObject : virtual public GameObject {

protected:
	b2Body* body;
	bool markRemoved = false;

public:
	DynamicObject() = default;
	~DynamicObject() override = default;

	// TODO: Move into a world manager class
	void addEntity(std::vector<GameObject*>* gameObjects) {
		// TODO: Check for entity ID conflicts before adding to the list. Add a test.
		gameObjects->push_back(this);
	}

	b2Vec2 getPosition() const {
		return body->GetPosition();
	}

	void setPosition(float x, float y) {
		body->SetTransform(b2Vec2(x, y), body->GetAngle());
	}

	void remove() {
		this->markRemoved = true;
	}

	bool isRemoved() const {
		return markRemoved;
	}
};