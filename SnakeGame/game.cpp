#include "game.h"

namespace snake_game
{

	Game::Game(const GameSettings& gameSettings)
		: theSnakePart((gameSettings.board.cellSize.x - 2) / 2.f)
		, theFoodPart((gameSettings.board.cellSize.x - 2) / 2.f)
		, theBoard(gameSettings.board.size)
		, boardView(&theBoard, gameSettings.board)
		, theSnake(gameSettings.snake.maximumLength)
		, snakeController(&theSnake)
		, settings(gameSettings)
	{
		theSnakePart.setOrigin(settings.board.cellSize.x / 2.f, settings.board.cellSize.y / 2.f);
		theSnakePart.setFillColor(sf::Color::Green);

		theFoodPart.setOrigin(settings.board.cellSize.x / 2.f, settings.board.cellSize.y / 2.f);
		theFoodPart.setFillColor(sf::Color::Yellow);

		reset();
	}

	void Game::reset()
	{
		moveTimer.reset();

		theSnake.init(settings.board.size / 2u, settings.snake.baseSize);
		snakeController.lookDown();

		generateFood();
	}

	void Game::generateFood()
	{
		sf::Vector2u pos;
		pos.x = (rand() % settings.board.size.x);
		pos.y = (rand() % settings.board.size.y);

		foodPosition = pos;
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
			if (!theBoard.contains(snakeController.headNextPosition()))
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

		if (snakeController.canEat(foodPosition))
		{
			snakeController.eat(foodPosition);
			generateFood();
		}
	}

	void Game::draw(sf::RenderWindow& window)
	{
		boardView.draw(window);
		drawFood(window);
		drawSnake(window);
	}

	void Game::drawFood(sf::RenderWindow& window)
	{
		auto cellPosition = boardView.getCellPosition(foodPosition);
		theFoodPart.setPosition(cellPosition);
		window.draw(theFoodPart);
	}

	void Game::drawSnake(sf::RenderWindow& window)
	{
		auto cellPosition = boardView.getCellPosition(theSnake.point(0));
		theSnakePart.setPosition(cellPosition);
		theSnakePart.setScale(1, 1);
		window.draw(theSnakePart);

		theSnakePart.setScale(0.8f, 0.8f);
		for (int i = 0; i < theSnake.size() - 1; ++i)
		{
			cellPosition = boardView.getCellPosition(theSnake.point(i));
			theSnakePart.setPosition(cellPosition);
			window.draw(theSnakePart);
		}

		cellPosition = boardView.getCellPosition(theSnake.point(theSnake.size() - 1));
		theSnakePart.setScale(0.4f, 0.4f);
		theSnakePart.setPosition(cellPosition);
		window.draw(theSnakePart);
	}

}
