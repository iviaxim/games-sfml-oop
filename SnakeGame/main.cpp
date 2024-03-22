#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ciclic_buffer.h"

namespace snake_game
{

	class Snake
	{
	public:
		Snake(int maximumSize)
			: snakePoints(maximumSize)
		{
		}

		void Init(const sf::Vector2u& position, int size)
		{
			snakePoints.clear();
			for (int i = 0; i < size; ++i)
			{
				snakePoints.push(position);
			}
		}

		void Eat(const sf::Vector2u& position)
		{
			snakePoints.push(position);
		}

		void Move()
		{
			MoveTo(HeadPosition() + moveDirection);
		}

		void LookLeft()
		{
			TryChangeDirection(sf::Vector2u(-1, 0));
		}

		void LookRight()
		{
			TryChangeDirection(sf::Vector2u(1, 0));
		}

		void LookUp()
		{
			TryChangeDirection(sf::Vector2u(0, -1));
		}

		void LookDown()
		{
			TryChangeDirection(sf::Vector2u(0, 1));
		}

		int Size() const
		{
			return snakePoints.size();
		}

		sf::Vector2u Point(int index) const
		{
			return snakePoints[snakePoints.size() - 1 - index];
		}

		sf::Vector2u HeadPosition() const
		{
			return Point(0);
		}

		sf::Vector2u HeadDirection() const
		{
			return Point(0) - Point(1);
		}

		bool SelfEat() const
		{
			auto headPos = HeadPosition();
			for (int i = 1; i < Size(); ++i)
			{
				if (headPos == Point(i))
				{
					return true;
				}
			}
			return false;
		}

	protected:
		void TryChangeDirection(const sf::Vector2u& value)
		{
			if (value + HeadDirection() != sf::Vector2u(0, 0))
			{
				moveDirection = value;
			}
		}

		void MoveTo(const sf::Vector2u& position)
		{
			snakePoints.pop();
			snakePoints.push(position);
		}

	private:
		sf::Vector2u moveDirection;
		utils::CiclicBuffer<sf::Vector2u> snakePoints;
	};

	struct BoardSettings
	{
		sf::Vector2f center;
		sf::Vector2u size;
		sf::Vector2f cellSize;
	};

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

	sf::Color CellBackColor = sf::Color(100, 100, 100);

	class RectangleBoard
	{
	public:
		RectangleBoard(const BoardSettings& settings)
			: boardSettings(settings)
		{
			theCell.setFillColor(CellBackColor);
			theCell.setSize(boardSettings.cellSize - sf::Vector2f(2, 2));
			theCell.setOrigin(boardSettings.cellSize / 2.f);
		}

		void draw(sf::RenderWindow& window)
		{
			sf::Vector2f leftTopCorner = LeftTopCorner();
			for (unsigned int x = 0; x < boardSettings.size.x; ++x)
			{
				for (unsigned int y = 0; y < boardSettings.size.y; ++y)
				{
					sf::Vector2f cellPos = leftTopCorner;
					cellPos.x += boardSettings.cellSize.x * x;
					cellPos.y += boardSettings.cellSize.y * y;
					theCell.setPosition(cellPos);
					window.draw(theCell);
				}
			}
		}

		sf::Vector2f GetCellPosition(const sf::Vector2u& cellIndex) const
		{
			sf::Vector2f cellPos = LeftTopCorner();
			cellPos.x += boardSettings.cellSize.x * cellIndex.x;
			cellPos.y += boardSettings.cellSize.y * cellIndex.y;
			return cellPos;
		}

		bool OutOfBoard(const sf::Vector2u& cellIndex) const
		{
			return (cellIndex.x >= boardSettings.size.x)
				|| (cellIndex.y >= boardSettings.size.y);
		}

		BoardSettings settings() const
		{
			return boardSettings;
		}

	private:
		sf::Vector2f LeftTopCorner() const
		{
			return sf::Vector2f{
				boardSettings.center.x - boardSettings.cellSize.x * float(boardSettings.size.x) / 2.f,
				boardSettings.center.y - boardSettings.cellSize.y * float(boardSettings.size.y) / 2.f
			} + boardSettings.cellSize / 2.f;
		}

	private:
		BoardSettings boardSettings;
		sf::RectangleShape theCell;
	};

	class Game
	{
	public:
		Game(const GameSettings& gameSettings)
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

		void reset()
		{
			clock.restart();
			lastElapsedTime = clock.getElapsedTime();

			theSnake.Init(theBoard.settings().size / 2u, settings.snake.baseSize);
			theSnake.LookDown();

			generateFood();
		}

		void generateFood()
		{
			sf::Vector2u pos;
			pos.x = (rand() % theBoard.settings().size.x);
			pos.y = (rand() % theBoard.settings().size.y);

			foodPosition = pos;
		}

		void handleEvent(const sf::Event& event)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					theSnake.LookLeft();
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					theSnake.LookRight();
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					theSnake.LookUp();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					theSnake.LookDown();
				}
			}
		}

		void update()
		{
			auto elapsedTime = clock.getElapsedTime();
			float secondsToMove = 1.0f / settings.snake.movesPerSecond;
			bool moveIsReady = (elapsedTime.asSeconds() - lastElapsedTime.asSeconds()) > secondsToMove;
			if (moveIsReady)
			{
				theSnake.Move();
				lastElapsedTime = elapsedTime;

				if (theBoard.OutOfBoard(theSnake.HeadPosition())
					|| theSnake.SelfEat())
				{
					reset();
				}
			}

			if (theSnake.HeadPosition() == foodPosition)
			{
				theSnake.Eat(foodPosition);
				generateFood();
			}
		}

		void draw(sf::RenderWindow& window)
		{
			theBoard.draw(window);

			auto cellPosition = theBoard.GetCellPosition(foodPosition);
			theFoodPart.setPosition(cellPosition);
			window.draw(theFoodPart);

			cellPosition = theBoard.GetCellPosition(theSnake.Point(0));
			theSnakePart.setPosition(cellPosition);
			theSnakePart.setScale(1, 1);
			window.draw(theSnakePart);

			theSnakePart.setScale(0.8f, 0.8f);
			for (int i = 0; i < theSnake.Size() - 1; ++i)
			{
				cellPosition = theBoard.GetCellPosition(theSnake.Point(i));
				theSnakePart.setPosition(cellPosition);
				window.draw(theSnakePart);
			}

			cellPosition = theBoard.GetCellPosition(theSnake.Point(theSnake.Size() - 1));
			theSnakePart.setScale(0.4f, 0.4f);
			theSnakePart.setPosition(cellPosition);
			window.draw(theSnakePart);
		}

	private:
		sf::CircleShape theSnakePart;
		sf::CircleShape theFoodPart;
		RectangleBoard theBoard;
		Snake theSnake;
		sf::Vector2u foodPosition;
		sf::Clock clock;
		sf::Time lastElapsedTime;
		GameSettings settings;
	};
}

int main()
{
	srand(456);

	snake_game::GameSettings gameSettings;
	gameSettings.screen.width = 800;
	gameSettings.screen.height = 600;
	gameSettings.board.size.x = 35;
	gameSettings.board.size.y = 25;
	gameSettings.board.cellSize.x = 20;
	gameSettings.board.cellSize.y = 20;
	gameSettings.board.center.x = gameSettings.screen.width / 2.f;
	gameSettings.board.center.y = gameSettings.screen.height / 2.f;
	gameSettings.snake.baseSize = 3;
	gameSettings.snake.maximumLength = 30;
	gameSettings.snake.movesPerSecond = 10;

	auto videoMode = sf::VideoMode(gameSettings.screen.width, gameSettings.screen.height);
	sf::RenderWindow window(videoMode, "Simple snake");

	snake_game::Game theGame(gameSettings);
	// https://musiclab.chromeexperiments.com/Song-Maker/song/5087407958523904
	//"c:/Maxim/Projects/SFML/projects/snake_game/SnakeGame/resources/theme.wav"

	//sf::Music music;
	//if (!music.openFromFile("c:/Maxim/Projects/SFML/projects/snake_game/SnakeGame/resources/theme.wav"))
	//	return EXIT_FAILURE;
	//music.setLoop(true);
	//music.play();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else
			{
				theGame.handleEvent(event);
			}
		}

		window.clear();

		theGame.update();
		theGame.draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}
