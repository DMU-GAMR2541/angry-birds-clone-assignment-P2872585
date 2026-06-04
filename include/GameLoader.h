#pragma once
#include <future>
#include <mutex>
#include <thread>
class GameLoader {
private:
	struct LoadProgress {
		std::mutex mutex;
		float spriteLoadedPercent = 0.0f;
		float physicsLoadedPercent = 0.0f;

		float getTotalLoadedPercent() const {
			// Convert to 0-100%
			return ((spriteLoadedPercent + physicsLoadedPercent) / 2.0f) * 100.0f;
		}
	};

    static void loadPhysicsData(LoadProgress& progress) {
        for (int i = 0; i <= 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            // Guard when modifying progress
            std::lock_guard<std::mutex> guard(progress.mutex);
            float loadedPercent = i / 10.0f;
            progress.physicsLoadedPercent = loadedPercent;
        }
    }

    static void loadSpriteData(LoadProgress& progress) {
        for (int i = 0; i <= 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));

            // Guard when modifying progress
            std::lock_guard<std::mutex> guard(progress.mutex);
            float loadedPercent = i / 10.0f;
            progress.spriteLoadedPercent = loadedPercent;
        }
    }

public:
    void loadStartScreen(sf::RenderWindow& window, sf::Font& font) {
		sf::Text title("Annoyed Flocks", font, 60);
		title.setFillColor(sf::Color::White);
		title.setOutlineColor(sf::Color::Black);
		title.setOutlineThickness(3.0f);
		sf::FloatRect tb = title.getLocalBounds();
		title.setOrigin(tb.left + tb.width / 2.0f, tb.top + tb.height / 2.0f);
		title.setPosition(window.getSize().x / 2.0f, 80.0f);

		sf::Texture redBirdTexture;
		sf::Sprite redBirdSprite;
		if (redBirdTexture.loadFromFile("assets/Ang_Birds/birds-png-3514.png")) {
			redBirdSprite.setTexture(redBirdTexture);
			redBirdSprite.setScale(0.25f, 0.25f);
			sf::FloatRect redBirdBounds = redBirdSprite.getLocalBounds();
			redBirdSprite.setOrigin(redBirdBounds.width / 2.0f, redBirdBounds.height / 2.0f);
			redBirdSprite.setPosition(window.getSize().x / 4.0f, window.getSize().y / 2.0f);
		} else {
			std::cout << "Failed to load start screen image" << std::endl;
		}

		sf::Texture pigTexture;
		sf::Sprite pigSprite;
		if (pigTexture.loadFromFile("assets/Ang_Birds/angry-birds-png-46187.png")) {
			pigSprite.setTexture(pigTexture);
			pigSprite.setScale(0.5f, 0.5f);
			sf::FloatRect pigBounds = pigSprite.getLocalBounds();
			pigSprite.setOrigin(pigBounds.width / 2.0f, pigBounds.height / 2.0f);
			pigSprite.setPosition(window.getSize().x * 3.0f / 4.0f, window.getSize().y / 2.0f);
		} else {
			std::cout << "Failed to load start screen image" << std::endl;
		}

		float barWidth = window.getSize().x / 2.0f;
		float barHeight = 30.0f;
		float barX = barWidth / 2.0f;
		float barY = 500.0f;
		sf::RectangleShape barBackground(sf::Vector2f(barWidth, barHeight));
		barBackground.setPosition(barX, barY);
		barBackground.setFillColor(sf::Color(50, 50, 50));

		sf::RectangleShape barFill(sf::Vector2f(0.0f, barHeight));
		barFill.setPosition(barX, barY);
		barFill.setFillColor(sf::Color::Green);

		sf::Text percentText("", font, 24);
		sf::FloatRect pb = percentText.getLocalBounds();
		percentText.setOrigin(pb.left + pb.width / 2.0f, pb.top + pb.height / 2.0f);
		percentText.setPosition(window.getSize().x / 2.0f, 540.0f);

		LoadProgress progress;
		std::thread physicsThread(loadPhysicsData, std::ref(progress));
		std::future<void> spriteThread = std::async(std::launch::async, loadSpriteData, std::ref(progress));

		bool loading = true;
		while (loading && window.isOpen()) {
			sf::Event event;
			// Lets you close the game whilst it's loading
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			// Guard when reading progress
			std::lock_guard<std::mutex> lock(progress.mutex);
			float percent = progress.getTotalLoadedPercent();

			barFill.setSize(sf::Vector2f(barWidth * (percent / 100.0f), barHeight));
			percentText.setString(std::to_string(static_cast<int>(percent)) + "%");

			window.clear(sf::Color(135, 206, 235)); // Sky Blue
			window.draw(title);
			window.draw(barBackground);
			window.draw(barFill);
			window.draw(percentText);
			window.draw(redBirdSprite);
			window.draw(pigSprite);
			window.display();

			if (percent >= 100.0f) {
				loading = false;
			}
		}

		physicsThread.join();
		spriteThread.get();
	}
};