#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>

class Wall : public StaticObject {
private:
    sf::RectangleShape shape;
public:
	Wall() = default;
	~Wall() override = default;
    Wall(b2World& world, float x, float y, float width, float height);

    void Render(sf::RenderWindow& window) override {
        window.draw(shape);
    }

    void UpdatePhysics() override {
        //Static objects usually don't move, but we set the position once.
        shape.setPosition(body->GetPosition().x * Constants::SCALE, body->GetPosition().y * Constants::SCALE);
    }
};