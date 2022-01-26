#pragma once

#include <SFML/Graphics.hpp>

namespace mathf {
	float lerp() {

	}

	float vecLen(sf::Vector2f a) {
		return sqrt(a.x * a.x + a.y * a.y);
	}

	//sf::Vector2f normalize()
	//{
	//	float inv_length = 1.0f / sqrt(x * x + y * y + z * z);
	//	return (*this * inv_length);
	//}
}