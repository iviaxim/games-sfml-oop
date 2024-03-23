#pragma once

#include <SFML/System.hpp>

namespace snake_game
{

	class RectangleBoard
	{
	public:
		RectangleBoard(const sf::Vector2u& size);

		bool contains(const sf::Vector2u& cellIndex) const;

	private:
		sf::Vector2u boardSize;
	};

}
