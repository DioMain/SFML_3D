#pragma once

#include <SFML/Graphics.hpp>

namespace gv {
	static sf::Vector2f MouseWorldPos;

	void update(sf::RenderWindow* app) {
		sf::Mouse mouse;

		MouseWorldPos = sf::Vector2f(
			(float)mouse.getPosition().x - (*app).getPosition().x - 8, 
			(float)mouse.getPosition().y - (*app).getPosition().y - 30);
	}
}