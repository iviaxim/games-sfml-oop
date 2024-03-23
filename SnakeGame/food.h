#pragma once

#include <SFML/System.hpp>

namespace snake_game
{

	class Food
	{
	public:
		Food(const sf::Vector2u& position);

		sf::Vector2u position() const;

	private:
		sf::Vector2u foodPosition;
	};

}
