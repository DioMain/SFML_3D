#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameComponets.h"
#include "Player.h"
#include "GlobalVars.h"

int main() {
	sf::RenderWindow app(sf::VideoMode(640, 480), "Game");
	app.setVerticalSyncEnabled(true);

	sf::Image icon;
	icon.loadFromFile("Resource/icon.png");
	
	app.setIcon(128, 128, icon.getPixelsPtr());

	player::init(&app, sf::Vector2f(320, 240), 0, 4);

	sf::Music chase;
	chase.openFromFile("Resource/CHASE.ogg");
	chase.setVolume(15);

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

		app.clear();

		app.draw(player::ViewRay.vertex);
		app.draw(player::Toward);

		app.display();
	}

	return EXIT_SUCCESS;
}