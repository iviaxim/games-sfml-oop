#include "rectangle_board.h"

namespace snake_game
{

	RectangleBoard::RectangleBoard(const sf::Vector2u& size)
		: boardSize(size)
	{
	}

	bool RectangleBoard::contains(const sf::Vector2u& cellIndex) const
	{
		return (cellIndex.x < boardSize.x)
			&& (cellIndex.y < boardSize.y);
	}

	sf::Vector2u RectangleBoard::size() const
	{
		return boardSize;
	}

	sf::Vector2u RectangleBoard::randomCellIndex() const
	{
		return { rand() % boardSize.x, rand() % boardSize.y };
	}

}
