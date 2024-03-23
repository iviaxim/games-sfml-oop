#pragma once

#include "rectangle_board.h"
#include "snake.h"
#include "snake_controller.h"

namespace snake_game
{

	struct SnakeSettings
	{
		int baseSize = 3;
		int maximumLength = 30;
		float movesPerSecond = 2.f;
	};

	struct ScreenSettings
	{
		unsigned int width = 800;
		unsigned int height = 600;
	};

	struct GameSettings
	{
		BoardSettings board;
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
		sf::CircleShape theSnakePart;
		sf::CircleShape theFoodPart;
		RectangleBoard theBoard;
		Snake theSnake;
		SnakeController snakeController;
		sf::Vector2u foodPosition;
		sf::Clock clock;
		sf::Time lastElapsedTime;
		GameSettings settings;
	};

}