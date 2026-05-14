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
#include "Bird.h"
#include "SFML/Audio/Music.hpp"

int main() {
    // --- 1. WINDOW SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Annoyed_Flocks");
    window.setFramerateLimit(60);

    sf::Music music;
    music.openFromFile("assets/sounds/Theme.flac");
    music.setLoop(true);
    music.play();

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

    Wall rightWall(world, 785.0f, 480.0f, 20.0f, 200.0f);
    rightWall.spawn(&gameObjects);

	std::shared_ptr<sf::Texture> redTex = std::make_shared<sf::Texture>();
	if (!redTex->loadFromFile("assets/Ang_Birds/birds-png-3514.png")) {
		std::cout << "Failed to load red bird texture" << std::endl;
		return -1;
	}

	std::shared_ptr<sf::Texture> blueTex = std::make_shared<sf::Texture>();
	if (!blueTex->loadFromFile("assets/Ang_Birds/angry-birds-png-46169.png")) {
		std::cout << "Failed to load blue bird texture" << std::endl;
		return -1;
	}

	std::shared_ptr<sf::Texture> yellowTex = std::make_shared<sf::Texture>();
	if (!yellowTex->loadFromFile("assets/Ang_Birds/angry-birds-png-46179.png")) {
		std::cout << "Failed to load yellow bird texture" << std::endl;
		return -1;
	}

	std::map<BirdType, std::shared_ptr<sf::Texture>> birdTextures = {
		{BirdType::Red, redTex},
		{BirdType::Blue, blueTex},
		{BirdType::Yellow, yellowTex},
		{BirdType::Black, redTex},
		{BirdType::White, redTex},
	};

	Catapult catapult(world, 100.0f, 500.0f, &gameObjects, birdTextures);
	catapult.spawn(&gameObjects);

	sf::Texture pigTexture;
	if (!pigTexture.loadFromFile("assets/Ang_Birds/angry-birds-png-46187.png")) {
	    std::cout << "Failed to load texture" << std::endl;
	    return -1;
	}

	// Structure 1
	Plank s1LeftPost(world, 380.0f, 530.0f, 20.0f, 100.0f);
	s1LeftPost.spawn(&gameObjects);
	Plank s1RightPost(world, 440.0f, 530.0f, 20.0f, 100.0f);
	s1RightPost.spawn(&gameObjects);
	Plank s1Roof(world, 410.0f, 472.0f, 80.0f, 15.0f);
	s1Roof.spawn(&gameObjects);
	SmallPig s1Pig(world, 410.0f, 447.0f, pigTexture);
	s1Pig.spawn(&gameObjects);

	// Structure 2
	Plank s2Wall(world, 540.0f, 510.0f, 20.0f, 140.0f);
	s2Wall.spawn(&gameObjects);
	MediumPig s2Pig(world, 580.0f, 554.0f, pigTexture);
	s2Pig.spawn(&gameObjects);

	// Structure 3
	Plank s3LeftWall(world, 650.0f, 520.0f, 20.0f, 120.0f);
	s3LeftWall.spawn(&gameObjects);
	Plank s3RightWall(world, 710.0f, 520.0f, 20.0f, 120.0f);
	s3RightWall.spawn(&gameObjects);
	Plank s3Roof(world, 680.0f, 452.0f, 80.0f, 15.0f);
	s3Roof.spawn(&gameObjects);
	LargePig s3Pig(world, 680.0f, 544.0f, pigTexture);
	s3Pig.spawn(&gameObjects);

	Plank s3TopBlock(world, 680.0f, 437.0f, 30.0f, 15.0f);
	s3TopBlock.spawn(&gameObjects);
	SmallPig s3TopPig(world, 680.0f, 411.0f, pigTexture);
	s3TopPig.spawn(&gameObjects);

    // --- 7. MAIN LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                catapult.onMousePress(event.mouseButton.x, event.mouseButton.y);

                // Trigger special ability on any in-flight bird
                int size = gameObjects.size();
                for (int i = 0; i < size; ++i) {
                    Bird* bird = dynamic_cast<Bird*>(gameObjects[i]);
                    if (bird && bird->getBody() && bird->getBody()->IsEnabled() && !bird->hasUsedAbility()) {
                        bird->activateSpecialAbility();
                    }
                }
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

        // Search for game objects that have been marked for removal
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
            DynamicObject* object = dynamic_cast<DynamicObject*>(*it);
            if (object && object->isRemoved()) {
                if (object->getBody()) {
                    // Remove from box2d
                    world.DestroyBody(object->getBody());
                }

                // Remove from gameObjects
                it = gameObjects.erase(it);
            } else {
                ++it;
            }
        }

        // Since we removed objects marked for removal we need to reset their pointers to what index they are now in the list
        for (int i = 0; i < gameObjects.size(); ++i) {
            DynamicObject* dynObject = dynamic_cast<DynamicObject*>(gameObjects[i]);
            if (dynObject && dynObject->getBody()) {
                dynObject->getBody()->GetUserData().pointer = i;
            }

            StaticObject* staticObject = dynamic_cast<StaticObject*>(gameObjects[i]);
            if (staticObject && staticObject->getBody()) {
                staticObject->getBody()->GetUserData().pointer = i;
            }
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
