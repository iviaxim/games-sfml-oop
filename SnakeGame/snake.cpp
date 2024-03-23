#include "snake.h"

namespace snake_game
{

	Snake::Snake(int maximumSize)
		: snakePoints(maximumSize)
	{
	}

	void Snake::init(const sf::Vector2u& position, int size)
	{
		snakePoints.clear();
		for (int i = 0; i < size; ++i)
		{
			snakePoints.push(position);
		}
	}

	void Snake::eat(const sf::Vector2u& position)
	{
		snakePoints.push(position);
	}

	void Snake::move()
	{
		moveTo(headPosition() + moveDirection);
	}

	void Snake::lookLeft()
	{
		tryChangeDirection(sf::Vector2u(-1, 0));
	}

	void Snake::lookRight()
	{
		tryChangeDirection(sf::Vector2u(1, 0));
	}

	void Snake::lookUp()
	{
		tryChangeDirection(sf::Vector2u(0, -1));
	}

	void Snake::lookDown()
	{
		tryChangeDirection(sf::Vector2u(0, 1));
	}

	int Snake::size() const
	{
		return snakePoints.size();
	}

	sf::Vector2u Snake::point(int index) const
	{
		return snakePoints[snakePoints.size() - 1 - index];
	}

	sf::Vector2u Snake::headPosition() const
	{
		return point(0);
	}

	sf::Vector2u Snake::headDirection() const
	{
		return point(0) - point(1);
	}

	bool Snake::selfEat() const
	{
		auto headPos = headPosition();
		for (int i = 1; i < size(); ++i)
		{
			if (headPos == point(i))
			{
				return true;
			}
		}
		return false;
	}

	void Snake::tryChangeDirection(const sf::Vector2u& value)
	{
		if (value + headDirection() != sf::Vector2u(0, 0))
		{
			moveDirection = value;
		}
	}

	void Snake::moveTo(const sf::Vector2u& position)
	{
		snakePoints.pop();
		snakePoints.push(position);
	}

}
