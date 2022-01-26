#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameComponets.h"
#include "Player.h"
#include "GlobalVars.h"
#include "GameMap.h"
#include "Render.h"

int main() {
	sf::RenderWindow app(sf::VideoMode(640, 480), "Game");
	app.setVerticalSyncEnabled(true);

	sf::Image icon;
	icon.loadFromFile("Resource/icon.png");

	sf::Music chase;
	chase.openFromFile("Resource/CHASE.ogg");
	chase.setVolume(15);

	gc::Camera cam = gc::Camera(sf::Vector2f(), 1, 250, 0, 25);

	map::init();

	player::init(&app, cam, sf::Vector2f(320, 240), 0, 4);

	chase.play();
	while (app.isOpen())
	{
		gv::update(&app);

		player::update();

		player::input();

		sf::Event appEvent;
		while (app.pollEvent(appEvent))
		{
			if (appEvent.type == sf::Event::Closed) app.close();
		}

		render::update(&app);
	}

	return EXIT_SUCCESS;
}