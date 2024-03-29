#include "game.h"

namespace snake_game
{

	Game::Game(const GameSettings& gameSettings)
		: board(gameSettings.board.size)
		, boardView(gameSettings.board)
		, snake(gameSettings.snake.maximumLength)
		, snakeView(&boardView)
		, snakeController(&snake)
		, food(sf::Vector2u(0, 0))
		, foodView(&boardView)
		, settings(gameSettings)
	{
		reset();
	}

	void Game::reset()
	{
		moveTimer.reset();

		snake.init(settings.board.size / 2u, settings.snake.baseSize);
		snakeController.lookDown();

		generateFood();
	}

	void Game::generateFood()
	{
		sf::Vector2u pos;
		pos.x = (rand() % settings.board.size.x);
		pos.y = (rand() % settings.board.size.y);

		food = Food(pos);
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
		if (moveTimer.isReadyToMove(settings.snake.secondsToMove()))
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
			generateFood();
		}
	}

	void Game::draw(sf::RenderWindow& window)
	{
		boardView.draw(window);
		foodView.draw(window, food);
		snakeView.draw(window, snake);
	}

}
