#pragma once
#include "DynamicObject.h"
class Enemy : public DynamicObject {
/// <summary>
/// Varaibles that define an enemy.
/// </summary>
private:
    int health = 0;
    bool b_isDestroyed = false;

public:
    //Default constructor for an enemy. 
    Enemy() = default;
    Enemy(int entityId, int health) : health(health) {}

    //Class functions to be tested.
    void takeDamage(int damage) {
        if (damage < 0) return;
        
        health -= damage;
        if (health <= 0) {
            health = 0;
            b_isDestroyed = true;
        }
    }

    int getHealth() const { return health; }
    bool checkIfPopped() const { return b_isDestroyed; }

};