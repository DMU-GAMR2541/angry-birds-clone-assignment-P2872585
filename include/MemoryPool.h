#pragma once
#include "GameObject.h"
#include "LargePig.h"
#include "MediumPig.h"
#include "Pig.h"
#include "SmallPig.h"

class MemoryPool {
private:
    static constexpr int POOL_SIZE = 10;

    // Make array pool of fixed size (10 objects)
    // Now when we need a new pig we don't need any vector resizing
    std::unique_ptr<Pig> pool[POOL_SIZE];

    // Using generics to return the same type easily
    template <typename T> T* addPig(T pig) {
        for (int i = 0; i < POOL_SIZE; i++) {
            // Is this slot free?
            if (!pool[i]) {
                pool[i] = std::make_unique<T>(pig);
                return static_cast<T*>(pool[i].get());
            }
        }
        // No slot is free, panic!!
        return nullptr;
    }

public:
    SmallPig* getSmall(b2World& world, float x, float y, sf::Texture& texture) {
        return addPig(SmallPig(world, x, y, texture));
    }

    MediumPig* getMedium(b2World& world, float x, float y, sf::Texture& texture) {
        return addPig(MediumPig(world, x, y, texture));
    }

    LargePig* getLarge(b2World& world, float x, float y, sf::Texture& texture) {
        return addPig(LargePig(world, x, y, texture));
    }

    void release(Pig* pig) {
        for (int i = 0; i < POOL_SIZE; i++) {
            if (pool[i].get() == pig) {
                pool[i].reset();
                return;
            }
        }
    }
};
