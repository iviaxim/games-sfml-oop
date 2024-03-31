#pragma once

#include <SFML/System.hpp>

namespace snake_game
{

	class MoveTimer
	{
	public:
		MoveTimer(float secondsToMove);

		void reset();

		bool isReadyToMove() const;

	private:
		sf::Clock clock;
		float secondsToMove;
	};

}
