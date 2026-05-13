#include "Plank.h"
#include <box2d/box2d.h>

Plank::Plank(b2World& world, float x, float y, float width, float height) {
    //Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / Constants::SCALE, y / Constants::SCALE);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(width * 0.5f / Constants::SCALE, height * 0.5f / Constants::SCALE);

    b2FixtureDef fixture;
    fixture.shape = &box;
    fixture.density = 1.5f;   // Light wood
    fixture.friction = 0.3f;
    body->CreateFixture(&fixture);

    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width * 0.5f, height * 0.5f);
    shape.setFillColor(sf::Color(139, 69, 19)); // Brown
}
