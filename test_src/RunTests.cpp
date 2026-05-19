#include <gtest/gtest.h>
#include "SmallPig.h"
#include <iostream>

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

// The fixture for testing class Foo.
class EnemyTest : public testing::Test {
public:
    // TODO shared ptr?
    b2World world = b2World(b2Vec2(0.0f, 9.8f)); // Earth-like gravity;
    std::unique_ptr<SmallPig> enemy;
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    EnemyTest() {
        // You can do set-up work for each test here.

    }

    ~EnemyTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
        
        sf::Texture pigTexture;
        if (!pigTexture.loadFromFile("assets/Ang_Birds/angry-birds-png-46187.png")) {
            std::cout << "Failed to load texture" << std::endl;
        }

		enemy = std::make_unique<SmallPig>(SmallPig(world, 10.0f, 5.0f, pigTexture)); // All enemnies in this test suite start with 50 HP.
		std::cout << "Pig position at setup: (" << enemy->getPosition().x << ", " << enemy->getPosition().y << ")" << std::endl;
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }


};

//A single test, not a fixture. No setup is called.
//TEST(Pig, First_test) {
//    SmallPig e(100);
//    EXPECT_GT(e.getHealth(), 100);
//    SUCCEED() << "Test test passed";
//    FAIL() << "Test didn't pass";
//}

TEST_F(EnemyTest, LethalDamagePopsPig) {
    enemy->takeDamage(60);
    EXPECT_TRUE(enemy->checkIfPopped());
}

TEST_F(EnemyTest, SpawnPositionIsCorrect) {
    b2Vec2 pos = enemy->getPosition();
	std::cout << "Pig position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    EXPECT_FLOAT_EQ(pos.x, 10.0f / Constants::SCALE);
	EXPECT_FLOAT_EQ(pos.y, 5.0f / Constants::SCALE);
}

TEST_F(EnemyTest, SpriteLoaded) {
	EXPECT_FALSE(enemy->getSprite().getTexture() == nullptr);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}