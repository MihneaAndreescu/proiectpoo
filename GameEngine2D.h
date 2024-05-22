#pragma once

#include <SFML/Graphics.hpp>
#include "PlanetSystem.h"

class GameEngine2D {
private:
	struct FrameData {
		sf::Clock fpsClock;
		sf::Clock secondClock;
		int fps;
		FrameData() : fps(0) {
		}
	};
	GameEngine2D() {}
	GameEngine2D(const GameEngine2D&) = delete;
	GameEngine2D& operator = (const GameEngine2D&) = delete;
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
	static GameEngine2D& getInstance();
	void gameLoop();
};

