#include "snake_controller.h"

namespace snake_game
{

	SnakeController::SnakeController(Snake* snake_)
		: snake(snake_)
	{
	}

	void SnakeController::eat(const sf::Vector2u& position)
	{
		snake->pushHead(position);
	}

	bool SnakeController::canEat(const sf::Vector2u& position) const
	{
		return snake->headPosition() == position;
	}

	bool SnakeController::snakeContains(const sf::Vector2u& position) const
	{
		return snake->contains(position);
	}

	void SnakeController::lookLeft()
	{
		tryChangeDirection(sf::Vector2u(-1, 0));
	}

	void SnakeController::lookRight()
	{
		tryChangeDirection(sf::Vector2u(1, 0));
	}

	void SnakeController::lookUp()
	{
		tryChangeDirection(sf::Vector2u(0, -1));
	}

	void SnakeController::lookDown()
	{
		tryChangeDirection(sf::Vector2u(0, 1));
	}

	void SnakeController::move()
	{
		snake->moveTo(headNextPosition());
	}

	sf::Vector2u SnakeController::headNextPosition() const
	{
		return snake->headPosition() + moveDirection;
	}

	void SnakeController::tryChangeDirection(const sf::Vector2u& value)
	{
		if (value + snake->headDirection() != sf::Vector2u(0, 0))
		{
			moveDirection = value;
		}
	}

}
