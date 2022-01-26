#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

#include "GlobalVars.h"
#include "Player.h"

namespace map {
	const int MAP_SIZE_X = 10;
	const int MAP_SIZE_Y = 5;

	static std::string CHAR_MAP[MAP_SIZE_Y]{
		{"##########"},
		{".........."},
		{"..#......."},
		{".........."},
		{"##########"}
	};

	void init() {

	}
}