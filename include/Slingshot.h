#pragma once
#include <string>
#include "Bird.h"

/// <summary>
/// A simple class that you can use to begin the testing process using Googletest.
/// </summary>
class Slingshot {
private:
    /// <summary>
    /// Variables that define the slingshot.
    /// </summary>
    int i_tension;
    BirdType birdType;
    const int MAX_TENSION = 100;

public:
    Slingshot() : i_tension(0), birdType(BirdType::Red) {}

    //Functions to test.
    void loadBird(BirdType birdType) { this->birdType = birdType; }

    bool pullBack(int amount) {
        if (amount < 0) return false;
        i_tension = (i_tension + amount > MAX_TENSION) ? MAX_TENSION : i_tension + amount;
        return true;
    }

    int getTension() const { return i_tension; }
    BirdType getBirdType() const { return birdType; }

    void release() { i_tension = 0; }
};