#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

#include "GameComponents.h"
#include "GlobalVars.h"
#include "Player.h"

namespace map {
	const int MAP_SIZE_X = 10;
	const int MAP_SIZE_Y = 9;

	static float TILE = 200;

	static std::string CHAR_MAP[MAP_SIZE_Y]{
		{"##########"},
		{"#........#"},
		{"#...#....#"},
		{"##.......#"},
		{"##....####"},
		{"##.......#"},
		{"##..#..#.#"},
		{"#......#.#"},
		{"##########"}
	};

	void init() {
		for (int y = 0; y < MAP_SIZE_Y; y++)
		{
			for (int x = 0; x < MAP_SIZE_X; x++)
			{
				if (CHAR_MAP[y][x] == '.') continue;

				sf::RectangleShape* r = new sf::RectangleShape(sf::Vector2f(64, 64));
				(*r).setPosition(sf::Vector2f(64 * x, 64 * y));
				(*r).setFillColor(sf::Color(200, 200, 200));

				gv::CastRects.push_back(r);
			}
		}

		for (int i = 0; i < player::CAM.RAYS_NUM; i++)
		{
			sf::RectangleShape* r = new sf::RectangleShape(sf::Vector2f(1280.f / player::CAM.RAYS_NUM, 10));
			(*r).setPosition(sf::Vector2f((1280.f / player::CAM.RAYS_NUM) * i, 360 - ((*r).getSize().y / 2)));
			(*r).setFillColor(sf::Color(255, 140, 0));

			gv::RenderScreen.push_back(r);
		}
	}

	void update() {
		float d = player::CAM.RAYS_NUM / (2.f * tan(player::CAM.FOV / 2));

		for (int i = 0; i < player::CAM.RAYS_NUM; i++)
		{
			float h = (d * TILE) / (player::CAM.getRay(i).lapLen * cos(player::VievAngle - player::CAM.getRay(i).angle));

			if (player::CAM.getRay(i).len - player::CAM.getRay(i).lapLen > 0) 
				(*gv::RenderScreen[i]).setSize(sf::Vector2f((*gv::RenderScreen[i]).getSize().x, h));
			else 
				(*gv::RenderScreen[i]).setSize(sf::Vector2f((*gv::RenderScreen[i]).getSize().x, 0));

			if (h >= 720) gv::RenderScreen[i]->setSize(sf::Vector2f(gv::RenderScreen[i]->getSize().x, 720));

			gv::RenderScreen[i]->setPosition(sf::Vector2f(gv::RenderScreen[i]->getPosition().x, 360 - (gv::RenderScreen[i]->getSize().y / 2)));

			gv::RenderScreen[i]->setFillColor(sf::Color(255, 162 + (93 / (h / 30)), 0 + (255 / (h / 50))));
		}
	}
}