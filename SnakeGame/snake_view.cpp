#include "snake_view.h"

namespace snake_game
{

	constexpr float CellPadding = 2.0f;

	SnakeView::SnakeView(Snake* snake_, RectangleBoardView* board_)
		: snake(snake_)
		, board(board_)
		, theSnakePart((board->cellSize().x - CellPadding) / 2.f)
	{
		theSnakePart.setOrigin(board->cellSize().x / 2.f, board->cellSize().y / 2.f);
		theSnakePart.setFillColor(sf::Color::Green);
	}

	void SnakeView::draw(sf::RenderWindow& window)
	{
		auto cellPosition = board->getCellPosition(snake->point(0));
		theSnakePart.setPosition(cellPosition);
		theSnakePart.setScale(1, 1);
		window.draw(theSnakePart);

		theSnakePart.setScale(0.8f, 0.8f);
		for (int i = 0; i < snake->size() - 1; ++i)
		{
			cellPosition = board->getCellPosition(snake->point(i));
			theSnakePart.setPosition(cellPosition);
			window.draw(theSnakePart);
		}

		cellPosition = board->getCellPosition(snake->point(snake->size() - 1));
		theSnakePart.setScale(0.4f, 0.4f);
		theSnakePart.setPosition(cellPosition);
		window.draw(theSnakePart);
	}

}
