#pragma once

#include "rectangle_board.h"
#include "rectangle_board_view.h"
#include "snake.h"
#include "snake_view.h"
#include "snake_controller.h"
#include "food.h"
#include "food_view.h"
#include "move_timer.h"

namespace snake_game
{

	struct SnakeSettings
	{
		int baseSize = 3;
		int maximumLength = 30;
		float movesPerSecond = 2.f;

		float secondsToMove() const
		{
			return 1.0f / movesPerSecond;
		}
	};

	struct ScreenSettings
	{
		unsigned int width = 800;
		unsigned int height = 600;
	};

	struct GameSettings
	{
		RectangleBoardViewSettings board;
		SnakeSettings snake;
		ScreenSettings screen;
	};

	class Game
	{
	public:
		Game(const GameSettings& gameSettings);

		void reset();

		void generateFood();

		void handleEvent(const sf::Event& event);

		void update();

		void draw(sf::RenderWindow& window);

	private:
		RectangleBoard theBoard;
		RectangleBoardView boardView;

		Snake theSnake;
		SnakeView snakeView;
		SnakeController snakeController;

		Food food;
		FoodView foodView;

		GameSettings settings;
		MoveTimer moveTimer;
	};

}
