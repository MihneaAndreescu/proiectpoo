#pragma once

#include <SFML/Graphics.hpp>
#include "PlanetSystem.h"

class GameEngine {
private:
	struct FrameData {
		sf::Clock fpsClock;
		sf::Clock secondClock;
		int fps;
		FrameData() : fps(0) {
		}
	};
	GameEngine() {}
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator = (const GameEngine&) = delete;
	sf::RenderWindow window;
	sf::View view;
	PlanetSystem planetarySystem;	
	FrameData frameData;
	void updateAndAnalyzeFrameData();
	bool handleEventLoop();
	void drawWindow();
	void handleTemporaryViewMovement(const float dt);
	void updateFrame();
	void initialize();
	void initializePlanetarySystem();
	void initializeWindowAndView();
public:
	static GameEngine& getInstance();
	void gameLoop();
};

