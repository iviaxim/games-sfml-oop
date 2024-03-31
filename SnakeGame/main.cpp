#include "game.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	snake_game::GameSettings gameSettings;
	gameSettings.screen.width = 800;
	gameSettings.screen.height = 600;
	gameSettings.board.size.x = 35;
	gameSettings.board.size.y = 25;
	gameSettings.board.cellSize.x = 20;
	gameSettings.board.cellSize.y = 20;
	gameSettings.board.cellPadding = 1.f;
	gameSettings.board.center.x = gameSettings.screen.width / 2.f;
	gameSettings.board.center.y = gameSettings.screen.height / 2.f;
	gameSettings.board.cellBackColor = sf::Color(100, 100, 100);
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
