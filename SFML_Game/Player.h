#pragma once

#include <SFML/Graphics.hpp>

#include "GameComponets.h"
#include "GlobalVars.h"
#include "Mathf.h"

namespace player {

	static gc::Ray ViewRay;
	static float VievAngle;

	static float Speed = 2;

	static sf::CircleShape Toward;

	static sf::Vector2f position;

	void init(sf::RenderWindow* app, sf::Vector2f startPos, float startVievAngle = 0, float startSpeed = 2) {
		position = startPos;
		VievAngle = startVievAngle;
		Speed = startSpeed;

		ViewRay = gc::Ray(position, VievAngle, (*app).getSize().x);
		ViewRay.vertex[0].color = sf::Color::Red;

		Toward = sf::CircleShape(25, 50);
		Toward.setPosition(sf::Vector2f(position.x - Toward.getRadius(), position.y - Toward.getRadius()));
		Toward.setFillColor(sf::Color::Green);
	}

	void update() {
		ViewRay.pos = position;
		ViewRay.angle = VievAngle;

		ViewRay.update();

		Toward.setPosition(sf::Vector2f(position.x - Toward.getRadius(), position.y - Toward.getRadius()));
	}

	void input() {
		sf::Keyboard key;

		if (key.isKeyPressed(sf::Keyboard::W)) position.y -= 1 * Speed;
		if (key.isKeyPressed(sf::Keyboard::S)) position.y += 1 * Speed;
		if (key.isKeyPressed(sf::Keyboard::D)) position.x += 1 * Speed;
		if (key.isKeyPressed(sf::Keyboard::A)) position.x -= 1 * Speed;

		VievAngle = -atan2(gv::MouseWorldPos.x - position.x, gv::MouseWorldPos.y - position.y) + (90 / mathf::RadToDeg);
	}
}