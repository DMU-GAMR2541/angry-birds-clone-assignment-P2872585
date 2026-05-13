#pragma once
#include "Bird.h"

class YellowBird : public Bird {

public:
    YellowBird() = default;
    ~YellowBird() override = default;
    YellowBird(b2World& world, float x, float y, sf::Texture& texture);

    bool activateSpecialAbility() override;
};