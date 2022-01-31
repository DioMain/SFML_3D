#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "GlobalVars.h"
#include "Mathf.h"

namespace gc {

	class Line
	{
	public:
		sf::Vector2f a;
		sf::Vector2f b;

		Line() : a(sf::Vector2f()), b(sf::Vector2f()) { }

		Line(sf::Vector2f a, sf::Vector2f b) {
			this->a = a;
			this->b = b;
		}

		static sf::Vector2f lap(Line a, Line b) {
			sf::Vector2f vec0 = mathf::vector::create(a.a, a.b);
			sf::Vector2f vec1 = mathf::vector::create(b.a, b.b);
			sf::Vector2f vec2 = mathf::vector::create(a.a, b.a);
			sf::Vector2f vec3 = mathf::vector::create(a.a, b.b);
			sf::Vector2f vec4 = mathf::vector::create(b.a, a.a);
			sf::Vector2f vec5 = mathf::vector::create(b.a, a.b);

			sf::Vector3f prod0, prod1;

			prod0 = mathf::vector::prod(mathf::vector::to3d(vec0), mathf::vector::to3d(vec2));
			prod1 = mathf::vector::prod(mathf::vector::to3d(vec0), mathf::vector::to3d(vec3));

			if ((mathf::Sing(prod0.z) == mathf::Sing(prod1.z)) || (prod0.z == 0) || (prod1.z == 0)) return sf::Vector2f();

			prod0 = mathf::vector::prod(mathf::vector::to3d(vec1), mathf::vector::to3d(vec4));
			prod1 = mathf::vector::prod(mathf::vector::to3d(vec1), mathf::vector::to3d(vec5));

			if ((mathf::Sing(prod0.z) == mathf::Sing(prod1.z)) || (prod0.z == 0) || (prod1.z == 0)) return sf::Vector2f();

			return sf::Vector2f
			(a.a.x + vec0.x * std::fabs(prod0.z) / std::fabs(prod1.z - prod0.z),
				a.a.y + vec0.y * std::fabs(prod0.z) / std::fabs(prod1.z - prod0.z));
		}

	private:

	};

	class Ray
	{
	public:

		sf::VertexArray vertex;

		sf::Vector2f pos;
		sf::Vector2f lapPos;

		float angle;
		float len;
		float lapLen;

		Ray() : angle(0), len(0), lapLen(len), vertex(sf::VertexArray()), pos(sf::Vector2f()), lapPos(sf::Vector2f()) { }

		Ray(sf::Vector2f pos, float angle, float rayLen = 10) : lapLen(0), lapPos(sf::Vector2f()) {
			vertex = sf::VertexArray(sf::Lines, 2);

			this->pos = pos;
			this->angle = angle;
			len = rayLen;
		}

		void update() {
			vertex[0].position = pos;
			CAST();
		}

	private:

		void ADDLEN(sf::Vector2f* LAPPOS, std::vector<float>* LENS) {
			if (LAPPOS->x != 0 && LAPPOS->y != 0) {
				LENS->push_back(mathf::vector::len(mathf::vector::create(pos, *LAPPOS)));
			}
		}

		void CAST() {
			sf::Vector2f posLen;

			posLen.x = pos.x + len * cos(angle);
			posLen.y = pos.y + len * sin(angle);

			sf::Vector2f rayVec = mathf::vector::create(pos, posLen);

			std::vector<float> lens;

			for (int r = 0; r < gv::CastRects.size(); r++)
			{
				Line l0(pos, posLen);
				Line l1;

				// up

				l1 = Line
				(sf::Vector2f(gv::CastRects[r]->getPosition()),
					sf::Vector2f(gv::CastRects[r]->getPosition().x + gv::CastRects[r]->getSize().x, gv::CastRects[r]->getPosition().y));

				lapPos = Line::lap(l0, l1);

				ADDLEN(&lapPos, &lens);

				// right

				l1 = Line
				(sf::Vector2f(gv::CastRects[r]->getPosition().x + gv::CastRects[r]->getSize().x, gv::CastRects[r]->getPosition().y), sf::Vector2f(gv::CastRects[r]->getPosition().x + gv::CastRects[r]->getSize().x, gv::CastRects[r]->getPosition().y + gv::CastRects[r]->getSize().y));

				lapPos = Line::lap(l0, l1);

				ADDLEN(&lapPos, &lens);

				// Down

				l1 = Line
				(sf::Vector2f(gv::CastRects[r]->getPosition().x, gv::CastRects[r]->getPosition().y + gv::CastRects[r]->getSize().y), sf::Vector2f(gv::CastRects[r]->getPosition().x + gv::CastRects[r]->getSize().x, gv::CastRects[r]->getPosition().y + gv::CastRects[r]->getSize().y));

				lapPos = Line::lap(l0, l1);

				ADDLEN(&lapPos, &lens);

				// Left

				l1 = Line
				(sf::Vector2f(gv::CastRects[r]->getPosition()),
					sf::Vector2f(gv::CastRects[r]->getPosition().x, gv::CastRects[r]->getPosition().y + gv::CastRects[r]->getSize().y));

				lapPos = Line::lap(l0, l1);

				ADDLEN(&lapPos, &lens);
			}

			if (lens.size() > 0) {
				float maxLen = len;
				for (int i = 0; i < lens.size(); i++)
				{
					if (lens[i] < maxLen) maxLen = lens[i];
				}

				lapLen = maxLen;
				
				if (gv::DEBAG_MODE) {
					vertex[1].position.x = pos.x + lapLen * cos(angle);
					vertex[1].position.y = pos.y + lapLen * sin(angle);
				}
			}
			else {
				vertex[1].position = posLen;
				lapLen = len;
			}
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

		Camera() : FOV(0), DIRECTION(0), RAYS_NUM(0), POSITION(sf::Vector2f()) {
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

			for (int i = 0; i < RAYS_NUM; i++) {
				rays[i].pos = POSITION;

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
