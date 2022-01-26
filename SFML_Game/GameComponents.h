#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GlobalVars.h"

namespace gc {
	class Ray
	{
	public:

		sf::VertexArray vertex;

		sf::Vector2f pos;

		float angle;
		float len;
		float endLen;

		Ray() {
			vertex = sf::VertexArray();
			pos = sf::Vector2f();

			angle = 0;
			len = 0;
			endLen = len;
		}

		Ray(sf::Vector2f pos, float angle, float rayLen = 10) {
			vertex = sf::VertexArray(sf::Lines, 2);

			//vertex[0].position = pos;
			//vertex[1].position.x = pos.x + rayLen * cos(angle);
			//vertex[1].position.y = pos.y + rayLen * sin(angle);

			this->pos = pos;
			this->angle = angle;
			len = rayLen;
		}

		void update() {
			vertex[0].position = pos;
			CAST();
		}

	private:

		void CAST() {
			for (int i = 0; i < len; i++)
			{
				vertex[1].position.x = pos.x + i * cos(angle);
				vertex[1].position.y = pos.y + i * sin(angle);

				for (int r = 0; r < gv::CastRects.size(); r++)
				{
					if (vertex[1].position.x > (*gv::CastRects[r]).getPosition().x && vertex[1].position.x <= (*gv::CastRects[r]).getPosition().x + (*gv::CastRects[r]).getSize().x
						&& vertex[1].position.y > (*gv::CastRects[r]).getPosition().y && vertex[1].position.y <= (*gv::CastRects[r]).getPosition().y + (*gv::CastRects[r]).getSize().y) {
						endLen = i;
						return;
					}
				}
			}

			endLen = len;
		}
	};

	class Camera
	{
	public:

		sf::Vector2f POSITION;

		float FOV;
		float DEPTH;
		float DIRECTION;

		int RAYS_NUM;

		Camera() {
			FOV = 0;
			DEPTH = 0;
			DIRECTION = 0;

			POSITION = sf::Vector2f();

			RAYS_NUM = 0;

			RAYS_INIT();
		}

		Camera(sf::Vector2f POSITION, float FOV, float DEPTH, float DIRECTION, int RAYS_NUM) {
			this->FOV = FOV;
			this->DIRECTION = DIRECTION;
			this->DEPTH = DEPTH;

			this->POSITION = POSITION;

			this->RAYS_NUM = RAYS_NUM;

			RAYS_INIT();
		}

		void update() {
			RAYS_UPDATE();
		}

		Ray getRay(int index) {
			return rays[index];
		}

	private:

		Ray* rays = new Ray[0];

		void RAYS_INIT() {
			delete[] rays;

			rays = new Ray[RAYS_NUM];

			for (int i = 0; i < RAYS_NUM; i++) rays[i] = Ray(POSITION, 0, 0);

			RAYS_UPDATE();
		}

		void RAYS_UPDATE() {
			float DELTA_ANGLE = FOV / RAYS_NUM;

			for (int i = 0; i < RAYS_NUM; i++)
			{
				rays[i].pos = POSITION;

				rays[i].angle = (DIRECTION - (FOV / 2)) + (DELTA_ANGLE * i);

				rays[i].len = DEPTH;

				rays[i].update();
			}
		}
	};
}
