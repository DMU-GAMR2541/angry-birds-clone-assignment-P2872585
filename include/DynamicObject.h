#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>

class DynamicObject : virtual public GameObject {

protected:
	b2Body* body = nullptr;
	bool markRemoved = false;

public:
	DynamicObject() = default;
	~DynamicObject() override = default;

	void spawn(std::vector<GameObject*>* gameObjects) override {
		if (body) {
			body->GetUserData().pointer = gameObjects->size();
		}

		GameObject::spawn(gameObjects);
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