#pragma once

#include "snake.h"
#include "rectangle_board_view.h"

namespace snake_game
{

	struct SnakeViewSettings
	{
		float radius = 0.0f;
		sf::Vector2f origin;
		sf::Color color;
		float scaleHead = 1.0f;
		float scaleBody = 1.0f;
		float scaleTail = 1.0f;

		static SnakeViewSettings fromRect(const sf::Vector2f& size, float padding, const sf::Color& color);
	};

	class SnakeView
	{
	public:
		SnakeView(RectangleBoardView* board);

		void setupView(const SnakeViewSettings& settings);

		void draw(sf::RenderWindow& window, const Snake &snake, const RectangleBoardView& board);

	private:
		RectangleBoardView* board;
		sf::CircleShape circleView;
		SnakeViewSettings settings;
	};

}
