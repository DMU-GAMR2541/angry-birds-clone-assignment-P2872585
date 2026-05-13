#pragma once
#include "DynamicObject.h"
class Enemy : public DynamicObject {
/// <summary>
/// Varaibles that define an enemy.
/// </summary>
private:
    int health = 0;

public:
    //Default constructor for an enemy. 
    Enemy() = default;
    Enemy(int health) : health(health) {}

    //Class functions to be tested.
    void takeDamage(int damage) {
        if (damage < 0) return;
        
        health -= damage;
        if (health <= 0) {
            health = 0;
            markRemoved = true;
        }
    }

    int getHealth() const {
        return health;
    }
};