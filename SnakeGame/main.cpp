#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ciclic_buffer.h"

namespace snake_game
{

	constexpr int SnakeMaximumLength = 30;
	constexpr int SnakeBaseSize = 3;

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
			auto headPos = HeadPosition();
			headPos.x += snakeDirection.x;
			headPos.y += snakeDirection.y;
			Move(headPos);
		}

		void LookLeft()
		{
			if (snakeDirection.x != 1)
			{
				snakeDirection = sf::Vector2u(-1, 0);
			}
		}

		void LookRight()
		{
			if (snakeDirection.x != -1)
			{
				snakeDirection = sf::Vector2u(1, 0);
			}
		}

		void LookUp()
		{
			if (snakeDirection.y != 1)
			{
				snakeDirection = sf::Vector2u(0, -1);
			}
		}

		void LookDown()
		{
			if (snakeDirection.y != -1)
			{
				snakeDirection = sf::Vector2u(0, 1);
			}
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
		void Move(const sf::Vector2u& position)
		{
			snakePoints.pop();
			snakePoints.push(position);
		}

	private:
		sf::Vector2u snakeDirection;
		utils::CiclicBuffer<sf::Vector2u> snakePoints;
	};

	struct BoardSettings
	{
		sf::Vector2f center;
		int sizeX;
		int sizeY;
		sf::Vector2f cellSize;
	};

	sf::Color CellBackColor = sf::Color(100, 100, 100);

	class RectangleBoard
	{
	public:
		RectangleBoard(const BoardSettings& settings)
			: boardSettings(settings)
		{
			theCell.setFillColor(CellBackColor);
			theCell.setSize(sf::Vector2f(boardSettings.cellSize.x - 2, boardSettings.cellSize.y - 2));
			theCell.setOrigin(boardSettings.cellSize.x / 2, boardSettings.cellSize.y / 2);
		}

		void draw(sf::RenderWindow& window)
		{
			sf::Vector2f leftTopCorner(
				boardSettings.center.x - (boardSettings.sizeX / 2) * boardSettings.cellSize.x,
				boardSettings.center.y - (boardSettings.sizeY / 2) * boardSettings.cellSize.y
			);
			for (int x = 0; x < boardSettings.sizeX; ++x)
			{
				for (int y = 0; y < boardSettings.sizeY; ++y)
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
			sf::Vector2f leftTopCorner(
				boardSettings.center.x - (boardSettings.sizeX / 2) * boardSettings.cellSize.x,
				boardSettings.center.y - (boardSettings.sizeY / 2) * boardSettings.cellSize.y
			);
			sf::Vector2f cellPos = leftTopCorner;
			cellPos.x += boardSettings.cellSize.x * cellIndex.x;
			cellPos.y += boardSettings.cellSize.y * cellIndex.y;
			return cellPos;
		}

		bool OutOfBoard(const sf::Vector2u& cellIndex) const
		{
			return (cellIndex.x >= boardSettings.sizeX)
				|| (cellIndex.y >= boardSettings.sizeY);
		}

		BoardSettings settings() const
		{
			return boardSettings;
		}

	private:
		BoardSettings boardSettings;
		sf::RectangleShape theCell;
	};


	class Game
	{
	public:
		Game(const BoardSettings& boardSettings)
			: theSnakePart((boardSettings.cellSize.x - 2) / 2.f)
			, theFoodPart((boardSettings.cellSize.x - 2) / 2.f)
			, theBoard(boardSettings)
			, theSnake(SnakeMaximumLength)
		{
			theSnakePart.setOrigin(boardSettings.cellSize.x / 2.f, boardSettings.cellSize.y / 2.f);
			theSnakePart.setFillColor(sf::Color::Green);

			theFoodPart.setOrigin(boardSettings.cellSize.x / 2.f, boardSettings.cellSize.y / 2.f);
			theFoodPart.setFillColor(sf::Color::Yellow);

			reset();
		}

		void reset()
		{
			clock.restart();
			lastElapsedTime = clock.getElapsedTime();

			theSnake.Init(sf::Vector2u(theBoard.settings().sizeX / 2, theBoard.settings().sizeY / 2), 3);
			theSnake.LookDown();

			generateFood();
		}

		void generateFood()
		{
			sf::Vector2u pos;
			pos.x = (rand() % theBoard.settings().sizeX);
			pos.y = (rand() % theBoard.settings().sizeY);

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
			float speedDelta = 0.1f;
			if ((elapsedTime.asSeconds() - lastElapsedTime.asSeconds()) > speedDelta)
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

			for (int i = 0; i < theSnake.Size(); ++i)
			{
				cellPosition = theBoard.GetCellPosition(theSnake.Point(i));

				theSnakePart.setPosition(cellPosition);
				window.draw(theSnakePart);
			}
		}

	private:
		sf::CircleShape theSnakePart;
		sf::CircleShape theFoodPart;
		RectangleBoard theBoard;
		Snake theSnake;
		sf::Vector2u foodPosition;
		sf::Clock clock;
		sf::Time lastElapsedTime;
	};
}

int main()
{
	srand(456);
	auto videoMode = sf::VideoMode(800, 600);
	sf::RenderWindow window(videoMode, "SFML window");

	snake_game::BoardSettings boardSettings;
	boardSettings.sizeX = 30;
	boardSettings.sizeY = 20;
	boardSettings.cellSize.x = 20;
	boardSettings.cellSize.y = 20;
	boardSettings.center.x = videoMode.width / 2.f;
	boardSettings.center.y = videoMode.height / 2.f;

	snake_game::Game theGame(boardSettings);
	// https://musiclab.chromeexperiments.com/Song-Maker/song/5087407958523904
	//"c:/Maxim/Projects/SFML/projects/snake_game/SnakeGame/resources/theme.wav"

	sf::Music music;
	if (!music.openFromFile("c:/Maxim/Projects/SFML/projects/snake_game/SnakeGame/resources/theme.wav"))
		return EXIT_FAILURE;
	music.setLoop(true);
	music.play();

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
