#include "move_timer.h"

namespace snake_game
{

	void MoveTimer::reset()
	{
		clock.restart();
	}

	bool MoveTimer::isReadyToMove(float secondsToMove) const
	{
		return secondsToMove < clock.getElapsedTime().asSeconds();
	}

}
