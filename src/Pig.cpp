#include "Pig.h"

Pig::Pig(b2World& world, float x, float y, float radius, int health, sf::Texture& texture) : Enemy(health), radius(radius) {
    b2BodyDef bodyDefinition;
    bodyDefinition.type = b2_dynamicBody;
    bodyDefinition.position.Set(x / Constants::SCALE, y / Constants::SCALE);
    body = world.CreateBody(&bodyDefinition);

    b2CircleShape circle;
    circle.m_radius = radius / Constants::SCALE;

    b2FixtureDef physicsDefinition;
    physicsDefinition.shape = &circle;
    physicsDefinition.density = 1.0f;
    physicsDefinition.friction = 0.4f;
    physicsDefinition.restitution = 0.2f;
    body->CreateFixture(&physicsDefinition);

    sprite.setTexture(texture);

    const sf::Vector2u size = texture.getSize();

    // Make sprite scale match physics radius
    const float scaleX = (radius * 2.0f) / size.x;
    const float scaleY = (radius * 2.0f) / size.y;
    sprite.setScale(scaleX, scaleY);

    // Set origin to center for proper rotation and positioning
    sprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
}

void Pig::Render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Pig::UpdatePhysics() {
    sprite.setPosition(body->GetPosition().x * Constants::SCALE, body->GetPosition().y * Constants::SCALE);
    sprite.setRotation(body->GetAngle() * 180.0f / Constants::PI);
}