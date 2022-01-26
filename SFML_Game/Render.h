#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalVars.h"
#include "Player.h"
#include "GameMap.h"

namespace render {
	void update(sf::RenderWindow* app) {
		(*app).clear();

		for (int i = 0; i < gv::RenderScreen.size(); i++) (*app).draw(*gv::RenderScreen[i]);

		for (int i = 0; i < gv::CastRects.size(); i++) (*app).draw(*gv::CastRects[i]);
		(*app).draw(player::Toward);

		for (int i = 0; i < player::CAM.RAYS_NUM; i++) (*app).draw(player::CAM.getRay(i).vertex);

		(*app).display();
	}
}