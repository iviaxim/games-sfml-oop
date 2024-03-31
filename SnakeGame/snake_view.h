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
	};

	class SnakeView
	{
	public:
		SnakeView() = default;

		void setupView(const SnakeViewSettings& settings);

		void draw(sf::RenderWindow& window, const Snake &snake, const RectangleBoardView& board);

	private:
		sf::CircleShape circleView;
		SnakeViewSettings settings;
	};

}
