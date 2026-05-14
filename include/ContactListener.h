#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>
#include <iostream>
#include "Pig.h"
#include "Plank.h"
#include "Bird.h"

class ContactListener : public b2ContactListener {
private:
    std::vector<GameObject*>* gameObjects;
public:
    ContactListener() = default;

    ContactListener(std::vector<GameObject*>* gameObjects) {
        this->gameObjects = gameObjects;
    }

    // PostSolve gives us impulse so we can see how hard the pig got hit
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {
        float totalImpulse = 0.0f;
        for (int i = 0; i < impulse->count; ++i) {
            totalImpulse += impulse->normalImpulses[i];
        }

        if (totalImpulse < 0.75) return;

        int damage = totalImpulse * 2.3f;

        try {
            GameObject* obj1 = gameObjects->at(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
            GameObject* obj2 = gameObjects->at(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

            // Only birds and planks can hurt a pig
            if (Pig* pig = dynamic_cast<Pig*>(obj1)) {
                if (dynamic_cast<Bird*>(obj2) || dynamic_cast<Plank*>(obj2)) {
                    pig->takeDamage(damage);
                }
            }

            if (Pig* pig = dynamic_cast<Pig*>(obj2)) {
                if (dynamic_cast<Bird*>(obj1) || dynamic_cast<Plank*>(obj1)) {
                    pig->takeDamage(damage);
                }
            }
        }
        catch (const std::out_of_range& e) {
            std::cout << "Collision between unknown game objects" << std::endl;
        }
    }

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) override {
        std::cout << "Collision Ended" << std::endl;
    }
};
