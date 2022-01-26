#pragma once

#include <SFML/Graphics.hpp>

namespace mathf {
	const float pi = 3.14f;
	const float pi2 = 2 * 3.14f;

	const float RadToDeg = 180 / pi;

	float lerp(float a, float b, float c) {
		return a * (1 - c) + b * c;
	}

	namespace vector {
		float len(sf::Vector2f a) {
			return sqrt(a.x * a.x + a.y * a.y);
		}

		float dot(sf::Vector2f a, sf::Vector2f b) {
			return sqrt(a.x * b.x + a.y * b.y);
		}

		float angle(sf::Vector2f a, sf::Vector2f b) {
			return dot(a, b) / (len(a) * len(b));
		}

		sf::Vector2f create(sf::Vector2f a, sf::Vector2f b) {
			return sf::Vector2f(b.x - a.x, b.y - a.y);
		}
	}
}