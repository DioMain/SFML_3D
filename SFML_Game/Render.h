#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalVars.h"
#include "Player.h"
#include "GameMap.h"

namespace render {
	void update(sf::RenderWindow* app) {
		(*app).clear();

		sf::RectangleShape floorShape(sf::Vector2f(1280, 310));
		floorShape.setPosition(sf::Vector2f(0, 720 - 310));
		floorShape.setFillColor(sf::Color(30, 30, 30));

		(*app).draw(floorShape);

		for (int i = 0; i < gv::RenderScreen.size(); i++) (*app).draw(*gv::RenderScreen[i]);

		if (gv::DEBAG_MODE) {
			for (int i = 0; i < gv::CastRects.size(); i++) (*app).draw(*gv::CastRects[i]);
			(*app).draw(player::Toward);

			for (int i = 0; i < player::CAM.RAYS_NUM; i++) (*app).draw(player::CAM.getRay(i).vertex);
		}

		sf::Font font0;
		font0.loadFromFile("Resource/font.ttf");

		sf::Text FramerateTxt("FPS: " + mathf::toString(player::Framerate.getFPS()), font0, 20);
		FramerateTxt.setFillColor(sf::Color::Red);

		(*app).draw(FramerateTxt);

		(*app).display();
	}
}