#pragma once

#include "snake.h"
#include "rectangle_board_view.h"

namespace snake_game
{

	class SnakeView
	{
	public:
		SnakeView(Snake* snake, RectangleBoardView* board);

		void draw(sf::RenderWindow& window);

	private:
		Snake* snake;
		RectangleBoardView* board;
		sf::CircleShape theSnakePart;
	};

}
