#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

#include "GlobalVars.h"
#include "Player.h"

namespace map {
	const int MAP_SIZE_X = 10;
	const int MAP_SIZE_Y = 8;

	static std::string CHAR_MAP[MAP_SIZE_Y]{
		{"#########."},
		{".........."},
		{"..#......."},
		{".........."},
		{".........."},
		{".........."},
		{".#......#."},
		{"##########"}
	};

	void init() {
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			for (int x = 0; x < MAP_SIZE_X; x++)
			{
				if (CHAR_MAP[y][x] == '.') continue;

				sf::RectangleShape* r = new sf::RectangleShape(sf::Vector2f(64, 60));
				(*r).setPosition(sf::Vector2f(64 * x, 60 * y));
				(*r).setFillColor(sf::Color(200, 200, 200));

				gv::CastRects.push_back(r);
			}
		}
	}
}