#include "Bird.h"

Bird::Bird(b2World& world, int entityId, float x, float y, float radius, BirdType type, sf::Texture& texture, float density, float gravityScale) : birdType(type) {
    b2BodyDef bodyDefinition;
    bodyDefinition.type = b2_dynamicBody;
    bodyDefinition.position.Set(x / Constants::SCALE, y / Constants::SCALE);
    bodyDefinition.gravityScale = gravityScale;
    bodyDefinition.userData.pointer = entityId;
    body = world.CreateBody(&bodyDefinition);

    b2CircleShape circle;
    circle.m_radius = radius / Constants::SCALE;

    b2FixtureDef physicsDefinition;
    physicsDefinition.shape = &circle;
    physicsDefinition.density = density;
    physicsDefinition.friction = 0.3f;
    physicsDefinition.restitution = 0.4f;
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

void Bird::Render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Bird::UpdatePhysics() {
    sprite.setPosition(body->GetPosition().x * Constants::SCALE, body->GetPosition().y * Constants::SCALE);
}