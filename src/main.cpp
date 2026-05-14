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

    Wall leftWall(world, -10.0f, 480.0f, 20.0f, 200.0f);
    leftWall.spawn(&gameObjects);

    Wall rightWall(world, 810.0f, 480.0f, 20.0f, 200.0f);
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

	// Structure 1 - Watchtower
	Plank s1LeftPost(world, 240.0f, 545.0f, 15.0f, 70.0f);
	s1LeftPost.spawn(&gameObjects);
	Plank s1RightPost(world, 280.0f, 545.0f, 15.0f, 70.0f);
	s1RightPost.spawn(&gameObjects);
	Plank s1Roof(world, 260.0f, 502.0f, 55.0f, 10.0f);
	s1Roof.spawn(&gameObjects);
	SmallPig s1Pig(world, 260.0f, 483.0f, pigTexture);
	s1Pig.spawn(&gameObjects);

	// Structure 2 - Wall blockade
	Plank s2Wall(world, 460.0f, 525.0f, 15.0f, 110.0f);
	s2Wall.spawn(&gameObjects);
	MediumPig s2Pig(world, 495.0f, 560.0f, pigTexture);
	s2Pig.spawn(&gameObjects);

	// Structure 3 - Fortress
	Plank s3LeftWall(world, 620.0f, 530.0f, 15.0f, 100.0f);
	s3LeftWall.spawn(&gameObjects);
	Plank s3RightWall(world, 680.0f, 530.0f, 15.0f, 100.0f);
	s3RightWall.spawn(&gameObjects);
	Plank s3Roof(world, 650.0f, 475.0f, 75.0f, 10.0f);
	s3Roof.spawn(&gameObjects);
	LargePig s3Pig(world, 650.0f, 552.0f, pigTexture);
	s3Pig.spawn(&gameObjects);

	Plank s3TopBlock(world, 650.0f, 460.0f, 25.0f, 10.0f);
	s3TopBlock.spawn(&gameObjects);
	SmallPig s3TopPig(world, 650.0f, 441.0f, pigTexture);
	s3TopPig.spawn(&gameObjects);

	// Island 1 - Mid-height with small fort
	Ground island1(world, 360.0f, 415.0f, 70.0f, 8.0f);
	island1.spawn(&gameObjects);
	Plank i1LeftPost(world, 340.0f, 388.0f, 8.0f, 40.0f);
	i1LeftPost.spawn(&gameObjects);
	Plank i1RightPost(world, 380.0f, 388.0f, 8.0f, 40.0f);
	i1RightPost.spawn(&gameObjects);
	Plank i1Roof(world, 360.0f, 360.0f, 48.0f, 8.0f);
	i1Roof.spawn(&gameObjects);
	SmallPig i1Pig(world, 360.0f, 397.0f, pigTexture);
	i1Pig.spawn(&gameObjects);

	// Island 2 - High floating platform
	Ground island2(world, 540.0f, 315.0f, 60.0f, 8.0f);
	island2.spawn(&gameObjects);
	SmallPig i2Pig(world, 540.0f, 297.0f, pigTexture);
	i2Pig.spawn(&gameObjects);

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
