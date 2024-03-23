#pragma once

#include "ciclic_buffer.h"

#include <SFML/Graphics.hpp>

namespace snake_game
{

	class Snake
	{
	public:
		Snake(int maximumSize);

		void init(const sf::Vector2u& position, int size);

		void pushHead(const sf::Vector2u& position);

		void moveTo(const sf::Vector2u& position);

		int size() const;

		sf::Vector2u point(int index) const;

		sf::Vector2u headPosition() const;

		sf::Vector2u headDirection() const;

		bool contains(const sf::Vector2u& position) const;

	private:
		utils::CiclicBuffer<sf::Vector2u> snakePoints;
	};

}
