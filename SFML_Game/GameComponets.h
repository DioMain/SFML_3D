#pragma once

#include <SFML/Graphics.hpp>

namespace gc {
	class Ray
	{
	public:

		sf::VertexArray vertex;

		sf::Vector2f pos;

		float angle;
		float len;

		Ray() {

		}

		Ray(sf::Vector2f pos, float angle, float rayLen = 10) {
			vertex = sf::VertexArray(sf::Lines, 2);

			vertex[0].position = pos;
			vertex[1].position.x = pos.x + rayLen * cos(angle);
			vertex[1].position.y = pos.y + rayLen * sin(angle);

			this->pos = pos;
			this->angle = angle;
			len = rayLen;
		}

		void update() {
			vertex[0].position = pos;
			vertex[1].position.x = pos.x + len * cos(angle);
			vertex[1].position.y = pos.y + len * sin(angle);
		}

	private:

	};
}
