#include "food_view.h"

namespace snake_game
{

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
