#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "ContactListener.h"
#include "Ground.h"
#include "Wall.h"
#include "Plank.h"
#include "SmallPig.h"
#include "MediumPig.h"
#include "LargePig.h"
#include "UI.h"
#include "Catapult.h"

int main() {
    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);
    
    //setup world.
    b2Vec2 b2_gravity(0.0f, 9.8f); // Earth-like gravity
    b2World world(b2_gravity);
    
    std::vector<GameObject*> gameObjects;

	ContactListener contactListener = ContactListener(&gameObjects);
	world.SetContactListener(&contactListener);

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/angry-birds.ttf")) {
		std::cout << "Failed to load font" << std::endl;
		return -1;
	}

	UI pigsUI(font, &gameObjects, 10.0f, 10.0f);
	pigsUI.spawn(&gameObjects);

    Ground ground(world, 400.0f, 590.0f, 800.0f, 20.0f);
    ground.spawn(&gameObjects);

    Wall wall(world, 750.0f, 500.0f, 20.0f, 160.0f);
    wall.spawn(&gameObjects);

    Plank plank(world, 550.0f, 450.0f, 20.0f, 120.0f);
    plank.spawn(&gameObjects);

	Catapult catapult(world, 150.0f, 480.0f, &gameObjects);
	catapult.spawn(&gameObjects);

	sf::Texture pigTexture;
	if (!pigTexture.loadFromFile("assets/Ang_Birds/angry-birds-png-46187.png")) {
	    std::cout << "Failed to load texture" << std::endl;
	    return -1;
	}

	SmallPig smallPig(gameObjects.size() + 1, world, 600.0f, 540.0f, pigTexture);
	smallPig.spawn(&gameObjects);

	MediumPig mediumPig(gameObjects.size() + 1, world, 660.0f, 530.0f, pigTexture);
	mediumPig.spawn(&gameObjects);

	LargePig largePig(gameObjects.size() + 1, world, 720.0f, 520.0f, pigTexture);
	largePig.spawn(&gameObjects);

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // INPUT HANDLING: Press SPACE to launch
            // if (event.type == sf::Event::KeyPressed) {
            //     if (event.key.code == sf::Keyboard::Space) {
            //         // Reset position of the ball so that it can be fired again from its original poisition.
            //         b2_ballBody->SetTransform(b2Vec2(100.0f / scale, 500.0f / scale), 0);
            //         b2_ballBody->SetLinearVelocity(b2Vec2(0, 0));
            //         b2_ballBody->SetAngularVelocity(0);
            //
            //         // Apply impulse (X-axis, Y-axis) Negative Y is UP in Box2D because gravity is positive.
            //         b2_ballBody->ApplyLinearImpulse(b2Vec2(5.0f, -5.0f), b2_ballBody->GetWorldCenter(), true);
            //
            //         std::cout << "Firing!!!!" << std::endl;
            //     }
            // }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                catapult.onMousePress(event.mouseButton.x, event.mouseButton.y);
            }

            if (event.type == sf::Event::MouseMoved && catapult.isDragging()) {
                catapult.onMouseDrag(event.mouseMove.x, event.mouseMove.y);
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                catapult.onMouseRelease();
            }
        }

        // Update Physics
        world.Step(1.0f / 60.0f, 8, 3);

    	//All of the visuals needs to be synced with the physics.
        for (GameObject* obj : gameObjects) {
            obj->UpdatePhysics();
        }

        //Render all of the content at each frame. Remember you need to clear the screen each iteration or artefacts remain.
        window.clear(sf::Color(135, 206, 235)); // Sky Blue

        for (GameObject* obj : gameObjects) {
            obj->Render(window);
		}

        window.display();
    }

    return 0;
}
