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

    std::cout << "Pigs: " << pigs << std::endl;
    text.setString("Pigs: " + std::to_string(pigs));
    text.setPosition(x, y);
    text.setFont(font);
    text.setCharacterSize(24);
    window.draw(text);
}

void UI::UpdatePhysics() {

}
