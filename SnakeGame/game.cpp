#include "game.h"

namespace snake_game
{

	Game::Game(const GameSettings& gameSettings)
		: board(gameSettings.board.size)
		, boardView(gameSettings.board)
		, snake(gameSettings.snake.maximumLength)
		, snakeController(&snake)
		, food(sf::Vector2u(0, 0))
		, settings(gameSettings)
		, moveTimer(settings.snake.secondsToMove())
	{
		setupView(gameSettings);
		reset();
	}

	void Game::reset()
	{
		moveTimer.reset();

		snake.init(settings.board.size / 2u, settings.snake.baseSize);
		snakeController.lookDown();

		food = Food(board.randomCellIndex());
	}

	void Game::setupView(const GameSettings& gameSettings)
	{
		auto boardCellSize = gameSettings.board.cellSize;
		auto boardCellPadding = gameSettings.board.cellPadding;

		SnakeViewSettings snakeViewSettings;
		snakeViewSettings.radius = boardCellSize.x / 2.0f - boardCellPadding;
		snakeViewSettings.origin = boardCellSize / 2.0f;
		snakeViewSettings.color = sf::Color::Green;
		snakeViewSettings.scaleHead = 1.0f;
		snakeViewSettings.scaleBody = 0.8f;
		snakeViewSettings.scaleTail = 0.4f;
		snakeView.setupView(snakeViewSettings);

		FoodViewSettings foodViewSettings;
		foodViewSettings.radius = boardCellSize.x / 2.0f - boardCellPadding;
		foodViewSettings.origin = boardCellSize / 2.0f;
		foodViewSettings.color = sf::Color::Yellow;
		foodView.setupView(foodViewSettings);
	}

	void Game::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				snakeController.lookLeft();
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				snakeController.lookRight();
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				snakeController.lookUp();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				snakeController.lookDown();
			}
		}
	}

	void Game::update()
	{
		if (moveTimer.isReadyToMove())
		{
			if (!board.contains(snakeController.headNextPosition()))
			{
				reset();
			}
			else if (!snakeController.canMove())
			{
				reset();
			}
			else
			{
				snakeController.move();
				moveTimer.reset();
			}
		}

		if (snakeController.canEat(food.position()))
		{
			snakeController.eat(food.position());
			food = Food(board.randomCellIndex());
		}
	}

	void Game::draw(sf::RenderWindow& window)
	{
		boardView.draw(window);
		foodView.draw(window, food, boardView);
		snakeView.draw(window, snake, boardView);
	}

}
