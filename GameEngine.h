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
	sf::RenderWindow m_window;
	sf::View m_view;
	PlanetSystem m_planetarySystem;	
	FrameData m_frameData;
	void updateAndAnalyzeFrameData();
	bool handleEventLoop();
	void draw();
	void handleTemporaryViewMovement(const float dt);
	void updateFrame();
	void initialize();
	void initializePlanetarySystem();
	void initializeWindowAndView();
public:
	static GameEngine& getInstance();
	void gameLoop();
};

