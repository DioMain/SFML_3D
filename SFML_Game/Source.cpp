#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
	sf::RenderWindow app(sf::VideoMode(640, 480), "test");

	sf::CircleShape shape(100, 50);
	shape.setFillColor(sf::Color::Green);

	sf::Texture test_texture;
	test_texture.loadFromFile("Resource/GameNote.png");

	sf::Sprite test(test_texture);
	test.setScale(sf::Vector2f(.5f, .5f));

	sf::Music chase;
	chase.openFromFile("Resource/CHASE.ogg");

	chase.play();
	while (app.isOpen())
	{
		sf::Event appEvent;

		while (app.pollEvent(appEvent))
		{
			if (appEvent.type == sf::Event::Closed) app.close();
		}

		app.clear();

		app.draw(test);

		app.display();
	}

	return EXIT_SUCCESS;
}