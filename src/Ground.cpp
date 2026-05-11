#include "Ground.h"
#include <box2d/box2d.h>

Ground::Ground(b2World* world, float x, float y, float width, float height) {
    //Setup ground for the circle to move / bounce on.
    //Needs to have a body definition and a body. We use a raw pointer for the b2Body as Box2d does the management itself.
    //A body can be defined as having a position, velocity, and mass.
    b2BodyDef bodyDef;
    bodyDef.position.Set(x / Constants::SCALE, y / Constants::SCALE);
    b2_body = world->CreateBody(&bodyDef);

    //Define a fixture shape that relates to the collision for the ground.
    b2PolygonShape box;
    box.SetAsBox(width * 0.5f / Constants::SCALE, height * 0.5f / Constants::SCALE);
    b2_body->CreateFixture(&box, 0.0f);

    //Set up the ground visualisation.
    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width * 0.5f, height * 0.5f);
    shape.setFillColor(sf::Color(34, 139, 34)); // Forest Green
}
