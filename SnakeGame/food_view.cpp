#include "food_view.h"

namespace snake_game
{

	FoodViewSettings FoodViewSettings::fromRect(const sf::Vector2f& size, float padding, const sf::Color& color)
	{
		FoodViewSettings result;
		result.radius = size.x / 2.0f - padding;
		result.origin = size / 2.0f;
		result.color = color;
		return result;
	}

	FoodView::FoodView(RectangleBoardView* board_)
		: board(board_)
	{
		setupView(FoodViewSettings::fromRect(board->cellSize(), 1.f, sf::Color::Yellow));
	}

	void FoodView::setupView(const FoodViewSettings& settings)
	{
		circleView.setRadius(settings.radius);
		circleView.setOrigin(settings.origin);
		circleView.setFillColor(settings.color);
	}

	void FoodView::draw(sf::RenderWindow& window, const Food& food, const RectangleBoardView& board)
	{
		auto cellPosition = board.cellCenter(food.position());
		circleView.setPosition(cellPosition);
		window.draw(circleView);
	}

}
