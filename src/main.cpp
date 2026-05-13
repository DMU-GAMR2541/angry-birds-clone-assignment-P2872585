#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "RedBird.h"
#include "Constants.h"
#include "ContactListener.h"
#include "Ground.h"
#include "Wall.h"
#include "Plank.h"
#include "SmallPig.h"
#include "MediumPig.h"
#include "LargePig.h"

int main() {
    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    const float scale = Constants::SCALE;
    const float pi = Constants::PI;
    
    //setup world.
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);
    
    std::vector<GameObject*> gameObjects;

	ContactListener contactListener = ContactListener(&gameObjects);
	world.SetContactListener(&contactListener);

    Ground ground(world, 400.0f, 590.0f, 800.0f, 20.0f);
    gameObjects.push_back(&ground);

    Wall wall(world, 750.0f, 500.0f, 20.0f, 160.0f);
    gameObjects.push_back(&wall);

    Plank plank(world, 550.0f, 450.0f, 20.0f, 120.0f);
    gameObjects.push_back(&plank);

    //Create a ball that is fired when space is pressed. We need to first have a dynamic ball to do it.
    b2BodyDef b2_ballDef;
    b2_ballDef.type = b2_dynamicBody;
    b2_ballDef.position.Set(100.0f / scale, 500.0f / scale);
    b2Body* b2_ballBody = world.CreateBody(&b2_ballDef);

    b2CircleShape b2_circleShape;
    b2_circleShape.m_radius = 15.0f / scale;

    b2FixtureDef b2_ballFixture;
    b2_ballFixture.shape = &b2_circleShape;
    b2_ballFixture.density = 1.0f;
    b2_ballFixture.restitution = 0.5f; // Bounciness
    b2_ballBody->CreateFixture(&b2_ballFixture);

    sf::CircleShape sf_ballVisual(15.0f);
    sf_ballVisual.setOrigin(15.0f, 15.0f);
    sf_ballVisual.setFillColor(sf::Color::Yellow);

	sf::Texture birdTexture;
	if (!birdTexture.loadFromFile("assets/Ang_Birds/birds-png-3514.png")) {
	    std::cout << "Failed to load texture" << std::endl;
	    return -1;
	}

	RedBird bird(world, gameObjects.size() + 1, 10.0f * scale, 0.0f, birdTexture);
	bird.addEntity(&gameObjects);

	sf::Texture pigTexture;
	if (!pigTexture.loadFromFile("assets/Ang_Birds/angry-birds-png-46187.png")) {
	    std::cout << "Failed to load texture" << std::endl;
	    return -1;
	}

	SmallPig smallPig(gameObjects.size() + 1, world, 600.0f, 540.0f, pigTexture);
	smallPig.addEntity(&gameObjects);

	MediumPig mediumPig(gameObjects.size() + 1, world, 660.0f, 530.0f, pigTexture);
	mediumPig.addEntity(&gameObjects);

	LargePig largePig(gameObjects.size() + 1, world, 720.0f, 520.0f, pigTexture);
	largePig.addEntity(&gameObjects);

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    // Reset position of the ball so that it can be fired again from its original poisition.
                    b2_ballBody->SetTransform(b2Vec2(100.0f / scale, 500.0f / scale), 0);
                    b2_ballBody->SetLinearVelocity(b2Vec2(0, 0));
                    b2_ballBody->SetAngularVelocity(0);

                    // Apply impulse (X-axis, Y-axis) Negative Y is UP in Box2D because gravity is positive.
                    b2_ballBody->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), b2_ballBody->GetWorldCenter(), true);

                    std::cout << "Firing!!!!" << std::endl;
                }
            }
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

        for (GameObject* obj : gameObjects) {
            obj->UpdatePhysics();
        }

        //All of the visuals needs to be synced with the physics.

        sf_ballVisual.setPosition(b2_ballBody->GetPosition().x * scale, b2_ballBody->GetPosition().y * scale);
        sf_ballVisual.setRotation(b2_ballBody->GetAngle() * (180.0f / pi));

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        window.draw(sf_ballVisual);

        for (GameObject* obj : gameObjects) {
            obj->Render(window);
		}

        window.display();
    }

    return 0;
}
