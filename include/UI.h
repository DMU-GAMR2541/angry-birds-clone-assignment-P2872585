#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"
#include <SFML/Graphics.hpp>

class UI : virtual public StaticObject, virtual public DynamicObject {
private:
    sf::Text text;
    sf::Font& font;
    std::vector<GameObject*>* gameObjects;
    float x, y;

public:
    UI(sf::Font& font, std::vector<GameObject*>* gameObjects, float x, float y);

    void spawn(std::vector<GameObject*>* objects) override {
        objects->push_back(this);
    }

    void Render(sf::RenderWindow& window) override;

    void UpdatePhysics() override;
};