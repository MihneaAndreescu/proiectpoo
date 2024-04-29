#include "GameEngine.h"

GameEngine& GameEngine::getInstance() {
	static GameEngine instance;
	return instance;
}

void GameEngine::updateAndAnalyzeFrameData() {
	if (m_frameData.secondClock.getElapsedTime().asSeconds() >= 1) {
		std::cout << "fps = " << m_frameData.fps << " " << m_planetarySystem << std::endl;
		m_frameData.secondClock.restart();
		m_frameData.fps = 0;
	}
	m_frameData.fpsClock.restart();
	m_frameData.fps++;
}

bool GameEngine::handleEventLoop() {
	bool shouldExit = false;
	sf::Event e{};
	while (m_window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			m_window.close();
		}
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
			shouldExit = true;
		}
	}
	return shouldExit;
}

void GameEngine::draw() {
	m_window.clear();
	m_planetarySystem.prepDraw();
	m_window.draw(m_planetarySystem);
	m_window.display();
}

void GameEngine::handleTemporaryViewMovement(const float dt) {
	sf::Vector2f movement = sf::Vector2f(0, 0);
	movement += sf::Vector2f(1, 0) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));
	movement += sf::Vector2f(-1, 0) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
	movement += sf::Vector2f(0, 1) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
	movement += sf::Vector2f(0, -1) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
	m_view.move(movement);
	m_window.setView(m_view);
}

void GameEngine::updateFrame() {
	if (handleEventLoop()) {
		return;
	}
	const float dt = m_frameData.fpsClock.getElapsedTime().asSeconds();
	handleTemporaryViewMovement(dt);
	sf::Vector2f mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	ObjectUpdateInfo m_drawInfo({ dt, mousePosition });
	m_planetarySystem.update(m_drawInfo);
	updateAndAnalyzeFrameData();
	draw();
}

void GameEngine::initializeWindowAndView() {
	m_window.create(sf::VideoMode({ 900, 900 }), "Muad'dib", sf::Style::Default);
	m_window.setVerticalSyncEnabled(true);
	m_view.setSize(sf::Vector2f(2, -2));
	m_view.setCenter(sf::Vector2f(1, 1));
	m_window.setView(m_view);
}

void GameEngine::initializePlanetarySystem() {
	m_planetarySystem.setName("Sistemul lu' Mihnea");
	m_planetarySystem.addObject(new SpaceShip{ "Dune", sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.2f, 0.4f), 1.0f });
	m_planetarySystem.addObject(new Planet{ "Dune", sf::Vector2f(0.5f, 0.5f), 0.1f, sf::Vector2f(0.0f, 0.3f), 2.0f, sf::Color::Red });
	m_planetarySystem.addObject(new Planet{ "Caladan", sf::Vector2f(0.2f, 0.1f), 0.05f, sf::Vector2f(0.0f, 0.1f), 4.0f, sf::Color::Blue });
}

void GameEngine::initialize() {
	initializeWindowAndView();
	initializePlanetarySystem();
}

void GameEngine::gameLoop() {
	initialize();
	while (m_window.isOpen()) {
		updateFrame();
	}
}
