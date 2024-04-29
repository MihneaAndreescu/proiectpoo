#include "GameEngine.h"

GameEngine& GameEngine::getInstance() {
	static GameEngine instance;
	return instance;
}

void GameEngine::updateAndAnalyzeFrameData() {
	if (frameData.secondClock.getElapsedTime().asSeconds() >= 1) {
		std::cout << "fps = " << frameData.fps << " " << planetarySystem << std::endl;
		frameData.secondClock.restart();
		frameData.fps = 0;
	}
	frameData.fpsClock.restart();
	frameData.fps++;
}

bool GameEngine::handleEventLoop() {
	bool shouldExit = false;
	sf::Event e{};
	while (window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window.close();
		}
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
			shouldExit = true;
		}
	}
	return shouldExit;
}

void GameEngine::drawWindow() {
	window.clear();
	window.draw(planetarySystem);
	window.display();
}

void GameEngine::handleTemporaryViewMovement(const float dt) {
	sf::Vector2f movement = sf::Vector2f(0, 0);
	movement += sf::Vector2f(1, 0) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));
	movement += sf::Vector2f(-1, 0) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
	movement += sf::Vector2f(0, 1) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
	movement += sf::Vector2f(0, -1) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
	view.move(movement);
	window.setView(view);
}

void GameEngine::updateFrame() {
	if (handleEventLoop()) {
		return;
	}
	const float dt = frameData.fpsClock.getElapsedTime().asSeconds();
	handleTemporaryViewMovement(dt);
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	ObjectUpdateInfo info({ dt, mousePosition });
	planetarySystem.update(info);
	updateAndAnalyzeFrameData();
	drawWindow();
}

void GameEngine::initializeWindowAndView() {
	window.create(sf::VideoMode({ 900, 900 }), "Muad'dib", sf::Style::Default);
	window.setVerticalSyncEnabled(true);
	view.setSize(sf::Vector2f(2, -2));
	view.setCenter(sf::Vector2f(1, 1));
	window.setView(view);
}

void GameEngine::initializePlanetarySystem() {
	planetarySystem.setName("Sistemul lu' Mihnea");
	planetarySystem.addObject(new SpaceShip{ "Dune", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.2f, 0.4f), 1.0f });
	planetarySystem.addObject(new Planet{ "Dune", sf::Vector2f(0.5f, 0.5f), 0.1f, sf::Vector2f(0.0f, 0.3f), 2.0f, sf::Color::Red });
	planetarySystem.addObject(new Planet{ "Caladan", sf::Vector2f(0.2f, 0.1f), 0.05f, sf::Vector2f(0.0f, 0.1f), 4.0f, sf::Color::Blue });
}

void GameEngine::initialize() {
	initializeWindowAndView();
	initializePlanetarySystem();
}

void GameEngine::gameLoop() {
	initialize();
	while (window.isOpen()) {
		updateFrame();
	}
}
