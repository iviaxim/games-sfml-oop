#pragma once

#include <SFML/System.hpp>

namespace snake_game
{

	class MoveTimer
	{
	public:
		void reset();

		bool isReadyToMove(float secondsToMove) const;

	private:
		sf::Clock clock;
	};

}
