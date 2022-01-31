#pragma once

#include <SFML/Graphics.hpp>
#include <string> 
#include <sstream>

namespace mathf {
	const float pi = 3.14f;
	const float pi2 = 2 * 3.14f;

	const float RadToDeg = 180 / pi;

	float lerp(float a, float b, float c) {
		return a * (1 - c) + b * c;
		return a * (1 - c) + b * c;
	}

	float Sing(float a) {
		if (a > 0) return 1;
		else if (a < 0) return -1;
		else return 0;
	}

	template <typename T>
	std::string toString(T val)
	{
		std::ostringstream oss;
		oss << val;
		return oss.str();
	}

	template<typename T>
	T fromString(const std::string& s)
	{
		std::istringstream iss(s);
		T res;
		iss >> res;
		return res;
	}

	namespace vector {
		float len(sf::Vector2f a) {
			return sqrt(a.x * a.x + a.y * a.y);
		}

		float dot(sf::Vector2f a, sf::Vector2f b) {
			return sqrt(a.x * b.x + a.y * b.y);
		}

		double det(sf::Vector2f a, sf::Vector2f b) {
			return a.x * b.y - a.y * b.x;
		}

		float angle(sf::Vector2f a, sf::Vector2f b) {
			return dot(a, b) / (len(a) * len(b));
		}

		sf::Vector2f create(sf::Vector2f a, sf::Vector2f b) {
			return sf::Vector2f(b.x - a.x, b.y - a.y);
		}

		sf::Vector2f mapping(sf::Vector2f a, float tile) {
			return sf::Vector2f(floor(a.x / tile) * tile, floor(a.y / tile) * tile);
		}

		sf::Vector3f to3d(sf::Vector2f a) {
			return sf::Vector3f(a.x, a.y, 0);
		}

		sf::Vector3f prod(sf::Vector3f a, sf::Vector3f b) {

			return sf::Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
		}
	}
}