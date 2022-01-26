#pragma once

#include <SFML/Graphics.hpp>

namespace gc {
	class GameObject
	{
	public:

		GameObject(sf::Texture texture, sf::Vector2f) {
			this->texture = texture;
		}

		sf::Texture getTexture() {
			return texture;
		}

		sf::Sprite getSprite() {
			return sprite;
		}

		sf::Sprite* getSpritePointer() {
			return &sprite;
		}

		sf::Vector2f getPos(sf::Vector2f pos) {
			sprite.setPosition(pos);
		}

		void setPos(sf::Vector2f pos) {
			sprite.setPosition(pos);
		}

	private:		
		sf::Texture texture;
		sf::Sprite sprite;
	};

	class RectGameObject
	{
	public:

		sf::RectangleShape rect;

	private:

	};

	class CircleGameObject
	{
	public:

		sf::CircleShape circle;

	private:

	};

	class Ray
	{
	public:

		sf::VertexArray vertex;

		Ray(sf::Vector2f pos, float angle, float rayLen = 10) {
			vertex = sf::VertexArray(sf::Lines, 2);

			vertex[0].position = pos;
			vertex[1].position.x = pos.x + rayLen * cos(angle);
			vertex[1].position.y = pos.y + rayLen * sin(angle);
		}

	private:

	};
}
