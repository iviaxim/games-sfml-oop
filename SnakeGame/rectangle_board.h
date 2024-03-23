#pragma once

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

	class RectangleBoard
	{
	public:
		RectangleBoard(const BoardSettings& settings);

		void draw(sf::RenderWindow& window);

		sf::Vector2f getCellPosition(const sf::Vector2u& cellIndex) const;

		bool outOfBoard(const sf::Vector2u& cellIndex) const;

		BoardSettings settings() const;

	private:
		sf::Vector2f leftTopCorner() const;

	private:
		BoardSettings boardSettings;
		sf::RectangleShape theCell;
	};

}
