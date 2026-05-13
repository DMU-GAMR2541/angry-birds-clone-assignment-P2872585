#pragma once
#include "GameObject.h"
#include <box2d/box2d.h>
#include <iostream>
#include "Pig.h"

class ContactListener : public b2ContactListener {
public:
    std::vector<GameObject*>* gameObjects;

    ContactListener() = default;

    ContactListener(std::vector<GameObject*>* gameObjects) {
        // Store the pointer to the list of game objects
        this->gameObjects = gameObjects;
    }

    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact) override {
        // Get the two fixtures involved
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        try {
            GameObject* obj1 = gameObjects->at(fixtureA->GetBody()->GetUserData().pointer);
            GameObject* obj2 = gameObjects->at(fixtureB->GetBody()->GetUserData().pointer);
            std::cout << "Collision Detected between Object " << fixtureA->GetBody()->GetUserData().pointer
                << " and Object " << fixtureB->GetBody()->GetUserData().pointer << std::endl;

            if (dynamic_cast<Pig*>(obj1)) {
                std::cout << "Pig Collided Obj 1" << std::endl;
            } else if (dynamic_cast<Pig*>(obj2)) {
                std::cout << "Pig Collided Obj 2" << std::endl;
            }
        }
        catch (const std::out_of_range& e) {
            std::cout << "Collision between unknown game objects";
        }
    }

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact) override {
        std::cout << "Collision Ended" << std::endl;
    }
};
