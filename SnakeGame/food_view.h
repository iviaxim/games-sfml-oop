#pragma once

#include "food.h"
#include "rectangle_board_view.h"

namespace snake_game
{

	struct FoodViewSettings
	{
		float radius = 0.0f;
		sf::Vector2f origin;
		sf::Color color;
	};

	class FoodView
	{
	public:
		FoodView() = default;

		void setupView(const FoodViewSettings &settings);

		void draw(sf::RenderWindow& window, const Food& food, const RectangleBoardView& board);

	private:
		sf::CircleShape circleView;
	};

}
