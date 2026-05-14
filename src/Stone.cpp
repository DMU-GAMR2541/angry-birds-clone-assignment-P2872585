#include "Stone.h"
#include <box2d/box2d.h>

Stone::Stone(b2World& world, float x, float y, float width, float height, sf::Texture& texture) {
    //Rather than having an immovable wall, we can use the dynamic body type to create one that can have velocity etc.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / Constants::SCALE, y / Constants::SCALE);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape box;
    box.SetAsBox(width * 0.5f / Constants::SCALE, height * 0.5f / Constants::SCALE);

    b2FixtureDef fixture;
    fixture.shape = &box;
    fixture.density = 4.0f; // Stone
    fixture.friction = 0.6f;
    body->CreateFixture(&fixture);

    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width * 0.5f, height * 0.5f);
    shape.setTexture(&texture);
    shape.setTextureRect(sf::IntRect(721, 658, 199, 19));
}
