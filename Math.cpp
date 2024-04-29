#include "Math.h"
#include <cmath>

namespace Math
{
	sf::Vector2f rotateAroundOrigin(sf::Vector2f point, float angle)
	{
		float Cos = cos(angle);
		float Sin = sin(angle);
		return sf::Vector2f(point.x * Cos - point.y * Sin, point.x * Sin + point.y * Cos);
	}

	sf::Vector2f rotateArountPoint(sf::Vector2f origin, sf::Vector2f point, float angle)
	{
		return origin + rotateAroundOrigin(point - origin, angle);
	}

	float dot(sf::Vector2f a, sf::Vector2f b)
	{
		return a.x * b.x + a.y * b.y;
	}

	float norm(sf::Vector2f a)
	{
		return sqrt(dot(a, a));
	}

	sf::Vector2f normalize(sf::Vector2f a)
	{
		return a / norm(a);
	}

	sf::Vector2f perp(sf::Vector2f a)
	{
		return sf::Vector2f(a.y, -a.x);
	}
}