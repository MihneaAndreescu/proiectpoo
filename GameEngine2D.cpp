#include "GameEngine2D.h"
#include "Heart.h"
#include "Shroom.h"
#include "PsychedelicDrug.h"

GameEngine2D& GameEngine2D::getInstance() {
	static GameEngine2D instance;
	return instance;
}

void GameEngine2D::updateAndAnalyzeFrameData() {
	if (m_frameData.secondClock.getElapsedTime().asSeconds() >= 1) {
		std::cout << "fps = " << m_frameData.fps << " " << m_planetarySystem << std::endl;
		m_frameData.secondClock.restart();
		m_frameData.fps = 0;
	}
	m_frameData.fpsClock.restart();
	m_frameData.fps++;
}

bool GameEngine2D::handleEventLoop() {
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

void GameEngine2D::draw() {
	m_window.clear();
	m_planetarySystem.prepDraw();
	m_window.draw(m_planetarySystem);
	int hearts = m_planetarySystem.countHearts();
	float x = -2.9f, y = 2.9f;
	for (int i = 0; i < hearts; i++) {
		Heart heart(x, y, 0.2f);
		x += 0.25f;
		m_window.draw(heart);
	}

	//Shroom mushroom(0.1f); 
	//mushroom.setPosition(0, 0);
	//m_window.draw(mushroom);

	m_window.display();
}

void GameEngine2D::handleTemporaryViewMovement(const float dt) {
	sf::Vector2f movement = sf::Vector2f(0, 0);
	movement += sf::Vector2f(1, 0) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D));
	movement += sf::Vector2f(-1, 0) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A));
	movement += sf::Vector2f(0, 1) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
	movement += sf::Vector2f(0, -1) * dt * (float)(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S));
	m_view.move(movement);
	m_window.setView(m_view);
}


void GameEngine2D::updateFrame() {
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

void GameEngine2D::initializeWindowAndView() {
	m_window.create(sf::VideoMode({ 900, 900 }), "Muad'dib", sf::Style::Default);
	m_window.setVerticalSyncEnabled(true);
	m_view.setSize(sf::Vector2f(6, -6));
	m_view.setCenter(sf::Vector2f(0, 0));
	m_window.setView(m_view);
}

void GameEngine2D::initializePlanetarySystem() {
	m_planetarySystem.setName("Sistemul lu' Mihnea");
	m_planetarySystem.addObject(std::make_shared<SpaceShip>("Dune", sf::Vector2f(-0.5f, -0.5f), sf::Vector2f(0.2f, 0.4f), 1.0f));
	m_planetarySystem.addObject(std::make_shared<Planet>("Dune", sf::Vector2f(0.0f, 0.0f), 0.1f, sf::Vector2f(0.0f, 0.3f), 2.0f, sf::Color(255, 0, 100)));
	m_planetarySystem.addObject(std::make_shared<Planet>("Caladan", sf::Vector2f(-2.5f, -2.5f), 0.05f, sf::Vector2f(0.0f, 0.1f), 4.0f, sf::Color::Blue));
	m_planetarySystem.addObject(std::make_shared<Planet>("Arrakis", sf::Vector2f(1.5f, 2.0f), 0.08f, sf::Vector2f(0.05f, 0.02f), 3.0f, sf::Color::Yellow));
	m_planetarySystem.addObject(std::make_shared<Planet>("Giedi Prime", sf::Vector2f(2.5f, -1.0f), 0.12f, sf::Vector2f(-0.04f, 0.01f), 5.0f, sf::Color::Green));
	m_planetarySystem.addObject(std::make_shared<Planet>("Kaitain", sf::Vector2f(-2.0f, 2.5f), 0.09f, sf::Vector2f(0.06f, -0.03f), 2.5f, sf::Color::Cyan));
	m_planetarySystem.addObject(std::make_shared<PsychedelicDrug>("PsychedelicDrugDrug"));
}

void GameEngine2D::initialize() {
	initializeWindowAndView();
	initializePlanetarySystem();
}

void GameEngine2D::gameLoop() {
	initialize();
	while (m_window.isOpen()) {
		updateFrame();
	}
}
