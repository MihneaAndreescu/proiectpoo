#include "Math.h"
#include <cmath>
#include <iostream>
#include "DuneException.h"

namespace Math {
	sf::Vector2f rotateAroundOrigin(sf::Vector2f point, float angle) {
		float Cos = cos(angle);
		float Sin = sin(angle);
		return sf::Vector2f(point.x * Cos - point.y * Sin, point.x * Sin + point.y * Cos);
	}

	sf::Vector2f rotateAroundPoint(sf::Vector2f origin, sf::Vector2f point, float angle) {
		return origin + rotateAroundOrigin(point - origin, angle);
	}

	float dot(sf::Vector2f a, sf::Vector2f b) {
		return a.x * b.x + a.y * b.y;
	}

	float normUnsafe(sf::Vector2f a) {
		float solu = dot(a, a);
		if (solu < 0) {
			throw MathException("radical din negative boss?", dot(a, a));
		}
		return sqrt(solu);
	}

	float norm(sf::Vector2f a) {
		float sol;
		try {
			sol = normUnsafe(a);
		}
		catch (const MathException& e) {
			std::cout << "Exception caught in normSafe: " << e.what() << std::endl;
			sol = 0.0f;
		}
		return sol;
	}
	sf::Vector2f normalize(sf::Vector2f a) {
		float n = norm(a);
		if (n == 0.0f) {
			return a;
		}
		return a / n;
	}

	sf::Vector2f perp(sf::Vector2f a) {
		return sf::Vector2f(a.y, -a.x);
	}

	float cross(sf::Vector2f a, sf::Vector2f b) {
		return a.x * b.y - b.x * a.y;
	}

	bool intersects(const sf::CircleShape& a, const sf::CircleShape& b) {
		sf::Vector2f positionA = a.getPosition();
		sf::Vector2f positionB = b.getPosition();
		float deltaX = positionA.x - positionB.x;
		float deltaY = positionA.y - positionB.y;
		float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
		float radiusA = a.getRadius();
		float radiusB = b.getRadius();
		return distance <= (radiusA + radiusB);
	}
}