#include "rectangle_board.h"

namespace snake_game
{

	RectangleBoard::RectangleBoard(const BoardSettings& settings)
		: boardSettings(settings)
	{
		theCell.setFillColor(settings.cellBackColor);
		theCell.setSize(boardSettings.cellSize - sf::Vector2f(2, 2));
		theCell.setOrigin(boardSettings.cellSize / 2.f);
	}

	void RectangleBoard::draw(sf::RenderWindow& window)
	{
		sf::Vector2f ltCorner = leftTopCorner();
		for (unsigned int x = 0; x < boardSettings.size.x; ++x)
		{
			for (unsigned int y = 0; y < boardSettings.size.y; ++y)
			{
				sf::Vector2f cellPos = ltCorner;
				cellPos.x += boardSettings.cellSize.x * x;
				cellPos.y += boardSettings.cellSize.y * y;
				theCell.setPosition(cellPos);
				window.draw(theCell);
			}
		}
	}

	sf::Vector2f RectangleBoard::getCellPosition(const sf::Vector2u& cellIndex) const
	{
		sf::Vector2f cellPos = leftTopCorner();
		cellPos.x += boardSettings.cellSize.x * cellIndex.x;
		cellPos.y += boardSettings.cellSize.y * cellIndex.y;
		return cellPos;
	}

	bool RectangleBoard::outOfBoard(const sf::Vector2u& cellIndex) const
	{
		return (cellIndex.x >= boardSettings.size.x)
			|| (cellIndex.y >= boardSettings.size.y);
	}

	BoardSettings RectangleBoard::settings() const
	{
		return boardSettings;
	}

	sf::Vector2f RectangleBoard::leftTopCorner() const
	{
		return sf::Vector2f{
			boardSettings.center.x - boardSettings.cellSize.x * float(boardSettings.size.x) / 2.f,
			boardSettings.center.y - boardSettings.cellSize.y * float(boardSettings.size.y) / 2.f
		} + boardSettings.cellSize / 2.f;
	}

}
