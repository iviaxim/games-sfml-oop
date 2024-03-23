#pragma once

#include "food.h"
#include "rectangle_board_view.h"

namespace snake_game
{

	class FoodView
	{
	public:
		FoodView(Food* food, RectangleBoardView* board);

		void draw(sf::RenderWindow& window);

	private:
		Food* food;
		RectangleBoardView* board;
		sf::CircleShape theFoodPart;
	};

}
