#include "food_view.h"

namespace snake_game
{

	FoodView::FoodView(Food* food_, RectangleBoardView* board_)
		: food(food_)
		, board(board_)
		, theFoodPart((board->cellSize().x - 2) / 2.f)
	{
		theFoodPart.setOrigin(board->cellSize().x / 2.f, board->cellSize().y / 2.f);
		theFoodPart.setFillColor(sf::Color::Yellow);
	}

	void FoodView::draw(sf::RenderWindow& window)
	{
		auto cellPosition = board->getCellPosition(food->position());
		theFoodPart.setPosition(cellPosition);
		window.draw(theFoodPart);
	}

}
