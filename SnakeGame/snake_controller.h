#pragma once

#include "snake.h"

namespace snake_game
{

	class SnakeController
	{
	public:
		SnakeController(Snake* snake);

		void eat(const sf::Vector2u& position);

		bool canEat(const sf::Vector2u& position) const;

		bool snakeContains(const sf::Vector2u& position) const;

		void move();

		sf::Vector2u headNextPosition() const;

		void lookLeft();

		void lookRight();

		void lookUp();

		void lookDown();

	private:
		void tryChangeDirection(const sf::Vector2u& value);

	private:
		Snake* snake;
		sf::Vector2u moveDirection;
	};

}
