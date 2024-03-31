#include "snake_view.h"

namespace snake_game
{

	constexpr float CellPadding = 1.0f;

	SnakeViewSettings SnakeViewSettings::fromRect(const sf::Vector2f& size, float padding, const sf::Color& color)
	{
		SnakeViewSettings result;
		result.radius = size.x / 2.0f - padding;
		result.origin = size / 2.0f;
		result.color = color;
		return result;
	}

	SnakeView::SnakeView(RectangleBoardView* board_)
		: board(board_)
	{
		auto viewSettings = SnakeViewSettings::fromRect(board->cellSize(), CellPadding, sf::Color::Green);
		viewSettings.scaleHead = 1.0f;
		viewSettings.scaleBody = 0.8f;
		viewSettings.scaleTail = 0.4f;
		setupView(viewSettings);
	}

	void SnakeView::setupView(const SnakeViewSettings& settings_)
	{
		settings = settings_;
		circleView.setRadius(settings.radius);
		circleView.setOrigin(settings.origin);
		circleView.setFillColor(settings.color);
	}

	void SnakeView::draw(sf::RenderWindow& window, const Snake& snake, const RectangleBoardView& board)
	{
		auto cellPosition = board.cellCenter(snake.point(0));
		circleView.setPosition(cellPosition);
		circleView.setScale(settings.scaleHead, settings.scaleHead);
		window.draw(circleView);

		circleView.setScale(settings.scaleBody, settings.scaleBody);
		for (int i = 0; i < snake.size() - 1; ++i)
		{
			cellPosition = board.cellCenter(snake.point(i));
			circleView.setPosition(cellPosition);
			window.draw(circleView);
		}

		cellPosition = board.cellCenter(snake.point(snake.size() - 1));
		circleView.setScale(settings.scaleTail, settings.scaleTail);
		circleView.setPosition(cellPosition);
		window.draw(circleView);
	}

}
