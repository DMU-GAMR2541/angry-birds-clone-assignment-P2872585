#pragma once
#include "DynamicObject.h"
#include <SFML/Graphics.hpp>

class Stone : public DynamicObject {
private:
    sf::RectangleShape shape;
public:
	Stone() = default;
	~Stone() override = default;
    Stone(b2World& world, float x, float y, float width, float height, sf::Texture& texture);

    void Render(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    void UpdatePhysics() override {
        shape.setPosition(body->GetPosition().x * Constants::SCALE, body->GetPosition().y * Constants::SCALE);
        shape.setRotation(body->GetAngle() * (180.0f / Constants::PI));
    }
};
