#include "Wall.h"
#include <box2d/box2d.h>

Wall::Wall(b2World& world, float x, float y, float width, float height) {
    //Setting up a wall for the ball to hit.
    b2BodyDef bodyDef;
    bodyDef.position.Set(x / Constants::SCALE, y / Constants::SCALE);
    b2_body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(width * 0.5f / Constants::SCALE, height * 0.5f / Constants::SCALE);
    b2_body->CreateFixture(&box, 0.0f);

    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width * 0.5f, height * 0.5f);
    shape.setFillColor(sf::Color::Red);
}
