#include "rectangle_board_view.h"

namespace snake_game
{

	sf::Vector2f multiply(const sf::Vector2f& left, const sf::Vector2u& right)
	{
		return { left.x * right.x, left.y * right.y };
	}

	sf::Vector2f RectangleBoardViewSettings::cellCenter() const
	{
		return cellSize / 2.f;
	}

	RectangleBoardView::RectangleBoardView(const RectangleBoardViewSettings& settings)
		: boardSettings(settings)
	{
		cell.setFillColor(boardSettings.cellBackColor);
		cell.setSize(boardSettings.cellSize - sf::Vector2f(boardSettings.cellPadding, boardSettings.cellPadding) * 2.f);
		cell.setOrigin(boardSettings.cellCenter());
	}

	sf::Vector2f RectangleBoardView::leftTopCellCenter() const
	{
		return boardSettings.center
			- multiply(boardSettings.cellSize, boardSettings.size) / 2.f
			+ boardSettings.cellCenter();
	}

	void RectangleBoardView::draw(sf::RenderWindow& window)
	{
		sf::Vector2f ltCorner = leftTopCellCenter();
		for (unsigned int x = 0; x < boardSettings.size.x; ++x)
		{
			for (unsigned int y = 0; y < boardSettings.size.y; ++y)
			{
				sf::Vector2u cellIndex(x, y);
				cell.setPosition(
					ltCorner + multiply(boardSettings.cellSize, cellIndex)
				);
				window.draw(cell);
			}
		}
	}

	sf::Vector2f RectangleBoardView::cellCenter(const sf::Vector2u& cellIndex) const
	{
		return leftTopCellCenter() + multiply(boardSettings.cellSize, cellIndex);
	}

}
