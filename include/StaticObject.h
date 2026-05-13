#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>

class StaticObject : virtual public GameObject {
protected:
    b2Body* body = nullptr;

public:
    StaticObject() = default;
    ~StaticObject() override = default;

    void spawn(std::vector<GameObject*>* gameObjects) override {
        if (body) {
            body->GetUserData().pointer = gameObjects->size();
        }

        gameObjects->push_back(this);
    }

    b2Body* getBody() const { return body; }
};