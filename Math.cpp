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


	float pointToLineDistance(const sf::Vector2f& A, const sf::Vector2f& B, const sf::Vector2f& P) {
		sf::Vector2f AP = P - A;
		sf::Vector2f AB = B - A;
		float ab2 = AB.x * AB.x + AB.y * AB.y;
		float ap_ab = AP.x * AB.x + AP.y * AB.y;
		float t = ap_ab / ab2;
		if (t < 0.0f) {
			return std::sqrt(AP.x * AP.x + AP.y * AP.y);
		}
		else if (t > 1.0f) {
			sf::Vector2f BP = P - B;
			return std::sqrt(BP.x * BP.x + BP.y * BP.y);
		}
		else {
			sf::Vector2f Closest = A + t * AB;
			sf::Vector2f ClosestP = P - Closest;
			return std::sqrt(ClosestP.x * ClosestP.x + ClosestP.y * ClosestP.y);
		}
	}

	bool intersects(const sf::RectangleShape& rectangle, const sf::CircleShape& circle) {
		sf::Vector2f rectPos = rectangle.getPosition();
		sf::Vector2f circlePos = circle.getPosition();
		float radius = circle.getRadius();
		float rectWidth = rectangle.getSize().x;
		float rectHeight = rectangle.getSize().y;
		float rotation = rectangle.getRotation() * (Math::PI / 180.0);
		sf::Vector2f vertices[4];
		vertices[0] = rectPos;
		vertices[1] = sf::Vector2f(rectPos.x + rectWidth * cos(rotation), rectPos.y + rectWidth * sin(rotation));
		vertices[2] = sf::Vector2f(vertices[1].x - rectHeight * sin(rotation), vertices[1].y + rectHeight * cos(rotation));
		vertices[3] = sf::Vector2f(rectPos.x - rectHeight * sin(rotation), rectPos.y + rectHeight * cos(rotation));
		for (int i = 0; i < 4; i++) {
			int next = (i + 1) % 4;
			if (pointToLineDistance(vertices[i], vertices[next], circlePos) <= radius) {
				return true;
			}
		}
		for (int i = 0; i < 4; i++) {
			float dx = vertices[i].x - circlePos.x;
			float dy = vertices[i].y - circlePos.y;
			if (dx * dx + dy * dy <= radius * radius) {
				return true;
			}
		}
		return false;
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