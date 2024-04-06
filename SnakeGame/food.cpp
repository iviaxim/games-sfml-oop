#include "food.h"

namespace snake_game
{

	Food::Food(const sf::Vector2u& position)
		: foodPosition(position)
	{
	}

	sf::Vector2u Food::position() const
	{ 
		return foodPosition;
	}

}
