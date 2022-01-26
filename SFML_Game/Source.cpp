#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "GameComponets.h"

int main() {
	sf::RenderWindow app(sf::VideoMode(640, 480), "test");

	sf::VertexArray line(sf::PrimitiveType::LineStrip, 4);
	line[0].position = sf::Vector2f(20, 20);
	line[1].position = sf::Vector2f(320, 480);
	line[2].position = sf::Vector2f(500, 400);
	line[3].position = sf::Vector2f(500, 100);

	float angle = 0;

	while (app.isOpen())
	{
		sf::Event appEvent;

		gc::Ray ray = gc::Ray(sf::Vector2f(320, 240), angle, 100);

		while (app.pollEvent(appEvent))
		{
			if (appEvent.type == sf::Event::Closed) app.close();
		}

		app.clear();

		//app.draw(line);

		app.draw(ray.vertex);

		app.display();

		angle += 0.001f;
	}

	return EXIT_SUCCESS;
}