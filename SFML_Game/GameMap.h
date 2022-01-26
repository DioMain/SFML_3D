#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

#include "GameComponents.h"
#include "GlobalVars.h"
#include "Player.h"

namespace map {
	const int MAP_SIZE_X = 10;
	const int MAP_SIZE_Y = 8;

	static float TILE = 500;

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

		for (int i = 0; i < player::CAM.RAYS_NUM; i++)
		{
			sf::RectangleShape* r = new sf::RectangleShape(sf::Vector2f(640 / player::CAM.RAYS_NUM, 10));
			(*r).setPosition(sf::Vector2f((640 / player::CAM.RAYS_NUM) * i, 240 - ((*r).getSize().y / 2)));
			(*r).setFillColor(sf::Color(255, 140, 0));

			gv::RenderScreen.push_back(r);
		}
	}

	void update() {
		float d = player::CAM.RAYS_NUM / (2 * tan(player::CAM.FOV / 2));

		for (int i = 0; i < player::CAM.RAYS_NUM; i++)
		{
			if (player::CAM.getRay(i).len - player::CAM.getRay(i).endLen > 0) 
				(*gv::RenderScreen[i]).setSize(sf::Vector2f((*gv::RenderScreen[i]).getSize().x, (d * TILE) / player::CAM.getRay(i).endLen));
			else 
				(*gv::RenderScreen[i]).setSize(sf::Vector2f((*gv::RenderScreen[i]).getSize().x, 0));
			
			(*gv::RenderScreen[i]).setPosition(sf::Vector2f((640 / player::CAM.RAYS_NUM) * i, 240 - ((*gv::RenderScreen[i]).getSize().y / 2)));
		}
	}
}