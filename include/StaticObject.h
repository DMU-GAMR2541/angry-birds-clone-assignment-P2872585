#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>

class StaticObject : virtual public GameObject {
protected:
    b2Body* b2_body;

public:
    StaticObject() = default;
    ~StaticObject() override = default;

    b2Body* getBody() const { return b2_body; }
};