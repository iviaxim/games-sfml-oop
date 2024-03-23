#pragma once

#include "ciclic_buffer.h"

#include <SFML/Graphics.hpp>

namespace snake_game
{

	class Snake
	{
	public:
		Snake(int maximumSize);

		void init(const sf::Vector2u& position, int size);

		void eat(const sf::Vector2u& position);

		void move();

		void lookLeft();

		void lookRight();

		void lookUp();

		void lookDown();

		int size() const;

		sf::Vector2u point(int index) const;

		sf::Vector2u headPosition() const;

		sf::Vector2u headDirection() const;

		bool selfEat() const;

	protected:
		void tryChangeDirection(const sf::Vector2u& value);

		void moveTo(const sf::Vector2u& position);

	private:
		sf::Vector2u moveDirection;
		utils::CiclicBuffer<sf::Vector2u> snakePoints;
	};

}
