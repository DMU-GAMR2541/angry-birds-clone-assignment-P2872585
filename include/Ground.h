#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>

class Ground : public StaticObject {
private:
    sf::RectangleShape shape;
public:
	Ground() = default;
	~Ground() override = default;
    Ground(b2World& world, float x, float y, float width, float height);

    void Render(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    void UpdatePhysics() override {
        //Static objects usually don't move, but we set the position once.
        shape.setPosition(b2_body->GetPosition().x * Constants::SCALE, b2_body->GetPosition().y * Constants::SCALE);
    }
};