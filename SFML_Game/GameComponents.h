#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "GlobalVars.h"
#include "Mathf.h"

namespace gc {
	class Ray
	{
	public:

		sf::VertexArray vertex;

		sf::Vector2f pos;

		float angle;
		float len;
		float endLen;

		int step;

		Ray() : angle(0), len(0), step(1), endLen(len), vertex(sf::VertexArray()), pos(sf::Vector2f()) { }

		Ray(sf::Vector2f pos, float angle, float rayLen = 10, int step = 1) {
			vertex = sf::VertexArray(sf::Lines, 2);

			this->pos = pos;
			this->angle = angle;
			this->step = step;
			len = rayLen;
		}

		void update() {
			vertex[0].position = pos;
			CAST();
		}

	private:

		void CAST() {
			for (int i = 0; i < len; i += step)
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
		int RAY_STEP;

		Camera() : FOV(0), DIRECTION(0), RAYS_NUM(0), RAY_STEP(1), POSITION(sf::Vector2f()) {
			RAYS_INIT();
		}

		Camera(sf::Vector2f POSITION, float FOV, float DEPTH, float DIRECTION, int RAYS_NUM , int RAY_STEP) {
			this->FOV = FOV;
			this->DIRECTION = DIRECTION;
			this->DEPTH = DEPTH;

			this->POSITION = POSITION;

			this->RAYS_NUM = RAYS_NUM;
			this->RAY_STEP = RAY_STEP;

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

			for (int i = 0; i < RAYS_NUM; i++) {
				rays[i].pos = POSITION;

				rays[i].step = RAY_STEP;

				rays[i].angle = (DIRECTION - (FOV / 2)) + (DELTA_ANGLE * i);

				rays[i].len = DEPTH;

				rays[i].update();
			}
		}
	};

	//https://gist.github.com/kenpower/7233967
	class FPS
	{
	public:
		/// @brief Constructor with initialization.
		///
		FPS() : mFrame(0), mFps(0) {}

		/// @brief Update the frame count.
		/// 


		/// @brief Get the current FPS count.
		/// @return FPS count.
		const unsigned int getFPS() const { return mFps; }

	private:
		unsigned int mFrame;
		unsigned int mFps;
		sf::Clock mClock;

	public:
		void update()
		{
			if (mClock.getElapsedTime().asSeconds() >= 1.f)
			{
				mFps = mFrame;
				mFrame = 0;
				mClock.restart();
			}

			++mFrame;
		}
	};
}
