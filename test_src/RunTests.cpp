#include <gtest/gtest.h>
#include "SmallPig.h"
#include "MediumPig.h"
#include "LargePig.h"
#include "Wall.h"

/// <summary>
///Taken from the GoogleTest primer. 
/// </summary>

class WorldTest : public testing::Test {
public:
    b2World world = b2World(b2Vec2(0.0f, 9.8f)); // Earth-like gravity;
};

class SinglePigTest : public WorldTest {
public:
    std::unique_ptr<SmallPig> enemy;
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    SinglePigTest() {
        // You can do set-up work for each test here.
    }

    ~SinglePigTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).

        sf::Texture pigTexture;
		enemy = std::make_unique<SmallPig>(SmallPig(world, 10.0f, 5.0f, pigTexture)); // All enemnies in this test suite start with 50 HP.
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(SinglePigTest, LethalDamagePopsPig) {
    enemy->takeDamage(60);
    EXPECT_TRUE(enemy->checkIfPopped());
}

TEST_F(SinglePigTest, SpawnPositionIsCorrect) {
    ASSERT_NE(enemy->getBody(), nullptr);

    b2Vec2 pos = enemy->getPosition();
    EXPECT_FLOAT_EQ(pos.x, 10.0f / Constants::SCALE);
	EXPECT_FLOAT_EQ(pos.y, 5.0f / Constants::SCALE);
}

TEST_F(SinglePigTest, SpriteLoaded) {
	EXPECT_FALSE(enemy->getSprite().getTexture() == nullptr);
}

TEST_F(WorldTest, PigSpriteLoads) {
    // Check that the texture loads
    sf::Texture texture;
    ASSERT_TRUE(texture.loadFromFile("assets/Ang_Birds/angry-birds-png-46187.png"));

    SmallPig pig(world, 100.0f, 100.0f, texture);

    // Check that the pig actually has the sprite
    EXPECT_NE(pig.getSprite().getTexture(), nullptr);
}

TEST_F(WorldTest, PigHealthIncreasesWithSize) {
    sf::Texture texture;

    SmallPig small(world, 100.0f, 100.0f, texture);
    MediumPig medium(world, 100.0f, 100.0f, texture);
    LargePig big(world, 100.0f, 100.0f, texture);

    // Medium must have more health than small and big must have more health than medium
    EXPECT_GT(medium.getHealth(), small.getHealth());
    EXPECT_GT(big.getHealth(), medium.getHealth());
}

TEST_F(WorldTest, RelativePositionToThreeObjects) {
    sf::Texture texture;
    SmallPig pig(world, 400.0f, 400.0f, texture);
    b2Vec2 pigPosition = pig.getPosition();

    Wall left(world, 100.0f, 300.0f, 20.0f, 200.0f);
    Wall right(world, 700.0f, 300.0f, 20.0f, 200.0f);
    Wall floor(world, 400.0f, 550.0f, 600.0f, 20.0f);

    EXPECT_GT(pigPosition.x, left.getBody()->GetPosition().x);
    EXPECT_LT(pigPosition.x, right.getBody()->GetPosition().x);
    EXPECT_LT(pigPosition.y, floor.getBody()->GetPosition().y);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}