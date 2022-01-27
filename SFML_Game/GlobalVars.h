#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace gv {
	static std::vector<sf::RectangleShape*> CastRects;
	static std::vector<sf::RectangleShape*> RenderScreen;

	static sf::Vector2f MOUSE_POS_IN_WORLD;
	static sf::Vector2f MOUSE_POS_IN_PREV_FRAME;
	static sf::Vector2f MOUSE_POS_DELTA;

	static bool DEBAG_MODE = false;

	void UPDATE_MOUSE_POS(sf::RenderWindow* app) {
		sf::Mouse mouse;

		MOUSE_POS_IN_WORLD = sf::Vector2f(
			(float)mouse.getPosition().x - (*app).getPosition().x - 8, 
			(float)mouse.getPosition().y - (*app).getPosition().y - 30);

		MOUSE_POS_DELTA = sf::Vector2f(MOUSE_POS_IN_WORLD.x - MOUSE_POS_IN_PREV_FRAME.x, MOUSE_POS_IN_WORLD.y - MOUSE_POS_IN_PREV_FRAME.y);
	}

	void APPLY_MOUSE_POS() {
		MOUSE_POS_IN_PREV_FRAME = MOUSE_POS_IN_WORLD;
	}
}