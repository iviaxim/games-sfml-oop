#pragma once

#include "rectangle_board.h"

#include <SFML/Graphics.hpp>

namespace snake_game
{

	struct RectangleBoardViewSettings
	{
		sf::Vector2f center;
		sf::Vector2u size;
		sf::Vector2f cellSize;
		float cellPadding;
		sf::Color cellBackColor;

		sf::Vector2f cellCenter() const;
	};

	class RectangleBoardView
	{
	public:
		RectangleBoardView(const RectangleBoardViewSettings& settings);

		void draw(sf::RenderWindow& window);

		sf::Vector2f cellCenter(const sf::Vector2u& cellIndex) const;

	private:
		sf::Vector2f leftTopCellCenter() const;

	private:
		RectangleBoardViewSettings boardSettings;
		sf::RectangleShape cell;
	};

}
