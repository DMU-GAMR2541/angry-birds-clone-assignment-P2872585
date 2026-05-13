#pragma once
#include "DynamicObject.h"
#include <SFML/Graphics.hpp>

class Plank : public DynamicObject {
private:
    sf::RectangleShape shape;
public:
	Plank() = default;
	~Plank() override = default;
    Plank(b2World& world, float x, float y, float width, float height);

    void Render(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    void UpdatePhysics() override {
        shape.setPosition(body->GetPosition().x * Constants::SCALE, body->GetPosition().y * Constants::SCALE);
        shape.setRotation(body->GetAngle() * (180.0f / Constants::PI));
    }
};