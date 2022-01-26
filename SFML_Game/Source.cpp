#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameComponents.h"
#include "Player.h"
#include "GlobalVars.h"
#include "GameMap.h"
#include "Render.h"

int main() {
	sf::RenderWindow app(sf::VideoMode(640, 480), "Game");
	app.setVerticalSyncEnabled(true);

	sf::Image icon;
	icon.loadFromFile("Resource/icon.png");
	
	//sf::Music chase;
	//chase.openFromFile("Resource/CHASE.ogg");
	//chase.setVolume(15);

	gc::Camera cam = gc::Camera(sf::Vector2f(), 1, 250, 0, 60);

	player::init(&app, cam, sf::Vector2f(320, 240), 0, 4);

	map::init();

	//chase.play();
	while (app.isOpen())
	{
		gv::update(&app);

		player::update();

		player::input();

		map::update();

		sf::Event appEvent;
		while (app.pollEvent(appEvent))
		{
			if (appEvent.type == sf::Event::Closed) app.close();
		}

		render::update(&app);
	}

	return EXIT_SUCCESS;
}