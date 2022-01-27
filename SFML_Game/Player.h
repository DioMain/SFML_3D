#pragma once

#include <SFML/Graphics.hpp>

#include "GameComponents.h"
#include "GlobalVars.h"
#include "Mathf.h"

namespace player {

	static gc::Camera CAM;
	static float VievAngle;

	static float Speed = 2;
	static float AntiSensivity = 200;
	

	static sf::CircleShape Toward;

	static sf::Vector2f position;

	void init(sf::RenderWindow* app, gc::Camera startCAM, sf::Vector2f startPos, float startVievAngle = 0, float startSpeed = 2, float startAntiSensivity = 200) {
		position = startPos;
		VievAngle = startVievAngle;
		Speed = startSpeed;
		AntiSensivity = startAntiSensivity;

		CAM = startCAM;

		Toward = sf::CircleShape(10, 50);
		Toward.setPosition(sf::Vector2f(position.x - Toward.getRadius(), position.y - Toward.getRadius()));
		Toward.setFillColor(sf::Color::Green);
	}

	void update() {
		CAM.DIRECTION = VievAngle;
		CAM.POSITION = position;

		CAM.update();

		Toward.setPosition(sf::Vector2f(position.x - Toward.getRadius(), position.y - Toward.getRadius()));
	}

	void input() {
		sf::Keyboard key;
		sf::Mouse mouse;

		if (key.isKeyPressed(sf::Keyboard::W)) {
			position.x = position.x + Speed * cos(VievAngle);
			position.y = position.y + Speed * sin(VievAngle);
		}
		if (key.isKeyPressed(sf::Keyboard::S)) {
			position.x = position.x - Speed * cos(CAM.DIRECTION);
			position.y = position.y - Speed * sin(CAM.DIRECTION);
		}
		if (key.isKeyPressed(sf::Keyboard::D)) {
			position.x = position.x - Speed * sin(CAM.DIRECTION);
			position.y = position.y + Speed * cos(CAM.DIRECTION);
		}
		if (key.isKeyPressed(sf::Keyboard::A)) {
			position.x = position.x + Speed * sin(CAM.DIRECTION);
			position.y = position.y - Speed * cos(CAM.DIRECTION);
		}

		if (key.isKeyPressed(sf::Keyboard::F1)) gv::DEBAG_MODE = (gv::DEBAG_MODE) ? false : true;

		VievAngle += gv::MOUSE_POS_DELTA.x / 100;
	}
}