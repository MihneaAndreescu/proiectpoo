#include "GameEngine2D.h"
#include "Heart.h"
#include "Shroom.h"
#include "PsychedelicDrug.h"
#include "Star.h"
#include "StarObject.h"
#include "DuneColor.h"

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

	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(100, 100));
	shape.setPosition(sf::Vector2f(-50, -50));
	shape.setFillColor(DuneColor<unsigned char>(35, 100, 44));
	m_window.draw(shape);
	
	m_planetarySystem.prepDraw();
	m_window.draw(m_planetarySystem);
	int hearts = m_planetarySystem.countHearts();
	float x = -2.9f, y = 2.9f;
	std::vector<sf::Vector2f> points;
	for (int i = 0; i < hearts; i++) {
		Heart heart(x, y, 0.2f);
		points.push_back({ x - 0.05f, y - 0.15f });
		points.push_back({ x + 0.05f, y + 0.15f });
		x += 0.25f;
		m_window.draw(heart);
	}

	int shrooms = m_planetarySystem.countShrooms();
	x = -2.9f, y = 2.6f;
	for (int i = 0; i < shrooms; i++) {
		Shroom shroom(0.1f, true);
		shroom.setPosition(sf::Vector2f(x, y));
		points.push_back({ x - 0.05f, y - 0.15f });
		points.push_back({ x + 0.05f, y + 0.15f });
		x += 0.25f;
		m_window.draw(shroom);
	}
	if (!points.empty()) {
		float minx = points[0].x;
		float miny = points[0].y;
		float maxx = points[0].x;
		float maxy = points[0].y;
		for (auto& it : points) {
			minx = std::min(minx, it.x);
			miny = std::min(miny, it.y);

			maxx = std::max(maxx, it.x);
			maxy = std::max(maxy, it.y);
		}
		sf::RectangleShape shp;
		float midx = (minx + maxx) * 0.5f;
		float midy = (miny + maxy) * 0.5f;
		float dimx = (maxx - minx) * 1.2f;
		float dimy = (maxy - miny) * 1.2f;
		sf::Vector2f dim = sf::Vector2f(dimx, dimy);
		sf::Vector2f mid = sf::Vector2f(midx, midy);
		shp.setPosition(mid - dim * 0.5f);
		shp.setSize(dim);
		shp.setFillColor(DuneColor<unsigned char>(0, 0, 230, 100));
		m_window.draw(shp);
	}
	m_window.display();
}

int GameEngine2D::updateFrame() {
	if (handleEventLoop()) {
		return 1;
	}
	const float dt = m_frameData.fpsClock.getElapsedTime().asSeconds();
	sf::Vector2f mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	ObjectUpdateInfo m_drawInfo({ dt, mousePosition });
	m_planetarySystem.update(m_drawInfo);
	updateAndAnalyzeFrameData();
	draw();
	return 0;
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
	m_planetarySystem.addObject(std::make_shared<SpaceShip>("Player", sf::Vector2f(-0.5f, -0.5f), sf::Vector2f(0.2f, 0.4f), 1.0f));
	//m_planetarySystem.addObject(std::make_shared<StarObject>("Star 1"));
	//m_planetarySystem.addObject(std::make_shared<StarObject>("Star 2"));
	//m_planetarySystem.addObject(std::make_shared<StarObject>("Star 3"));
	//m_planetarySystem.addObject(std::make_shared<StarObject>("Star 4"));
	//m_planetarySystem.addObject(std::make_shared<StarObject>("Star 5"));
	m_planetarySystem.addObject(std::make_shared<Planet>("Dune", sf::Vector2f(0.0f, 0.0f), 0.1f, sf::Vector2f(0.0f, 0.3f), 2.0f, DuneColor<unsigned char>(255, 0, 100)));
	m_planetarySystem.addObject(std::make_shared<Planet>("Caladan", sf::Vector2f(-2.5f, -2.5f), 0.05f, sf::Vector2f(0.0f, 0.1f), 4.0f, DuneColor<unsigned char>(0, 0, 255))); 
	m_planetarySystem.addObject(std::make_shared<Planet>("Arrakis", sf::Vector2f(1.5f, 2.0f), 0.08f, sf::Vector2f(0.05f, 0.02f), 3.0f, DuneColor<unsigned char>(255, 255, 0))); 
	m_planetarySystem.addObject(std::make_shared<Planet>("Giedi Prime", sf::Vector2f(2.5f, -1.0f), 0.12f, sf::Vector2f(-0.04f, 0.01f), 5.0f, DuneColor<unsigned char>(0, 128, 0)));
	m_planetarySystem.addObject(std::make_shared<Planet>("Kaitain", sf::Vector2f(-2.0f, 2.5f), 0.09f, sf::Vector2f(0.06f, -0.03f), 2.5f, DuneColor<unsigned char>(0, 255, 255))); 
}

void GameEngine2D::initialize() {
	initializeWindowAndView();
	initializePlanetarySystem();
}

void GameEngine2D::gameLoop() {
	initialize();
	while (m_window.isOpen()) {
		if (updateFrame()) {
			return;
		}
	}
}
