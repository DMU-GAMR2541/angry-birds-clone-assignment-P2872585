#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>
class DynamicObject : public GameObject {

protected:
	std::unique_ptr<sf::Shape> shape;
	//b2Body body;
	//b2BodyDef b2_bodyDef;
	//b2PolygonShape b2_dynamicBox;
	//b2CircleShape b2_dynamicCircle;
	//sf::Sprite

public:
	DynamicObject() = default;
	~DynamicObject() = default;
	DynamicObject(sf::Shape* shape) {
		this->shape = std::unique_ptr<sf::Shape>(shape);
		//this->body = body;
	}

	void GameObject::Render(sf::RenderWindow& window) override {
		//shape->setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		window.draw(*shape);
	}

	/*b2Vec2 getPosition() const {
		return body.GetPosition();
	}*/

	void setPosition(float x, float y) {
		//body->SetTransform(b2Vec2(x, y), body->GetAngle());
	}
};