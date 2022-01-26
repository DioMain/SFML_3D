#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalVars.h"
#include "Player.h"

namespace render {
	void update(sf::RenderWindow* app) {
		(*app).clear();

		for (int i = 0; i < gv::CastRects.size(); i++) (*app).draw(*gv::CastRects[i]);

		for (int i = 0; i < player::CAM.RAYS_NUM; i++) (*app).draw(player::CAM.getRay(i).vertex);

		(*app).draw(player::Toward);

		(*app).display();
	}
}