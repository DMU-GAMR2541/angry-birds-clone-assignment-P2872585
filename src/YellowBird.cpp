#include "YellowBird.h"

YellowBird::YellowBird(b2World& world, float x, float y, sf::Texture& texture) : Bird(world, x, y, 22.0f, BirdType::Yellow, texture, 1.0f, 1.0f) {

}

bool YellowBird::activateSpecialAbility() {
    b2Vec2 velocity = body->GetLinearVelocity();
    float speed = velocity.Length();
    float boostMagnitude = 15.0f * body->GetMass();
    body->ApplyLinearImpulse(b2Vec2((velocity.x / speed) * boostMagnitude, (velocity.y / speed) * boostMagnitude), body->GetWorldCenter(), true);
    usedAbility = true;
    return true;
}