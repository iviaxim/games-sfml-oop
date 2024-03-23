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

	void Snake::pushHead(const sf::Vector2u& position)
	{
		snakePoints.push(position);
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

	bool Snake::contains(const sf::Vector2u& position) const
	{
		for (int i = 0; i < size(); ++i)
		{
			if (position == point(i))
			{
				return true;
			}
		}
		return false;
	}

	void Snake::moveTo(const sf::Vector2u& position)
	{
		snakePoints.pop();
		snakePoints.push(position);
	}

}
