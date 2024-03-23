#include "game.h"

namespace snake_game
{

	Game::Game(const GameSettings& gameSettings)
		: theSnakePart((gameSettings.board.cellSize.x - 2) / 2.f)
		, theFoodPart((gameSettings.board.cellSize.x - 2) / 2.f)
		, theBoard(gameSettings.board)
		, theSnake(gameSettings.snake.maximumLength)
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
		clock.restart();
		lastElapsedTime = clock.getElapsedTime();

		theSnake.init(theBoard.settings().size / 2u, settings.snake.baseSize);
		theSnake.lookDown();

		generateFood();
	}

	void Game::generateFood()
	{
		sf::Vector2u pos;
		pos.x = (rand() % theBoard.settings().size.x);
		pos.y = (rand() % theBoard.settings().size.y);

		foodPosition = pos;
	}

	void Game::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
			{
				theSnake.lookLeft();
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				theSnake.lookRight();
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				theSnake.lookUp();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				theSnake.lookDown();
			}
		}
	}

	void Game::update()
	{
		auto elapsedTime = clock.getElapsedTime();
		float secondsToMove = 1.0f / settings.snake.movesPerSecond;
		bool moveIsReady = (elapsedTime.asSeconds() - lastElapsedTime.asSeconds()) > secondsToMove;
		if (moveIsReady)
		{
			theSnake.move();
			lastElapsedTime = elapsedTime;

			if (theBoard.outOfBoard(theSnake.headPosition())
				|| theSnake.selfEat())
			{
				reset();
			}
		}

		if (theSnake.headPosition() == foodPosition)
		{
			theSnake.eat(foodPosition);
			generateFood();
		}
	}

	void Game::draw(sf::RenderWindow& window)
	{
		theBoard.draw(window);

		auto cellPosition = theBoard.getCellPosition(foodPosition);
		theFoodPart.setPosition(cellPosition);
		window.draw(theFoodPart);

		cellPosition = theBoard.getCellPosition(theSnake.point(0));
		theSnakePart.setPosition(cellPosition);
		theSnakePart.setScale(1, 1);
		window.draw(theSnakePart);

		theSnakePart.setScale(0.8f, 0.8f);
		for (int i = 0; i < theSnake.size() - 1; ++i)
		{
			cellPosition = theBoard.getCellPosition(theSnake.point(i));
			theSnakePart.setPosition(cellPosition);
			window.draw(theSnakePart);
		}

		cellPosition = theBoard.getCellPosition(theSnake.point(theSnake.size() - 1));
		theSnakePart.setScale(0.4f, 0.4f);
		theSnakePart.setPosition(cellPosition);
		window.draw(theSnakePart);
	}

}
