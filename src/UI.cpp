#include "UI.h"
#include <iostream>
#include "Pig.h"

UI::UI(sf::Font& font, std::vector<GameObject*>* gameObjects, float x, float y) : font(font), gameObjects(gameObjects), x(x), y(y) {

}

void UI::Render(sf::RenderWindow &window) {
    int pigs = 0;
    for (GameObject* gameObject : *gameObjects) {
        Pig* pig = dynamic_cast<Pig*>(gameObject);
        if (pig && !pig->isRemoved()) {
            pigs++;
        }
    }

    if (pigs == 0) {
        sf::Vector2 windowSize = window.getSize();
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));
        text.setString("You win!");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Green);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2.0f);
    } else {
        text.setString("Pigs: " + std::to_string(pigs));
        text.setPosition(x, y);
        text.setCharacterSize(24);
    }

    text.setFont(font);
    window.draw(text);
}

void UI::UpdatePhysics() {

}
