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

		static FoodViewSettings fromRect(const sf::Vector2f& size, float padding, const sf::Color& color);
	};

	class FoodView
	{
	public:
		FoodView(RectangleBoardView* board);

		void setupView(const FoodViewSettings &settings);

		void draw(sf::RenderWindow& window, const Food& food);

	private:
		RectangleBoardView* board;
		sf::CircleShape circleView;
	};

}
