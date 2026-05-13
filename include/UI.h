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

    void Render(sf::RenderWindow& window) override;

    void UpdatePhysics() override;
};