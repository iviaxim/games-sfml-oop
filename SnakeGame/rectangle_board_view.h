#pragma once

#include "rectangle_board.h"

#include <SFML/Graphics.hpp>

namespace snake_game
{

	struct BoardSettings
	{
		sf::Vector2f center;
		sf::Vector2u size;
		sf::Vector2f cellSize;
		sf::Color cellBackColor;
	};

	class RectangleBoardView
	{
	public:
		RectangleBoardView(RectangleBoard* board, const BoardSettings& settings);

		void draw(sf::RenderWindow& window);

		sf::Vector2f getCellPosition(const sf::Vector2u& cellIndex) const;

		BoardSettings settings() const;

	private:
		sf::Vector2f leftTopCorner() const;

	private:
		BoardSettings boardSettings;
		RectangleBoard* board;
		sf::RectangleShape theCell;
	};

}
