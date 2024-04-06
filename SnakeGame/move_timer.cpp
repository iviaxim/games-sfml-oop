#include "move_timer.h"

namespace snake_game
{

	MoveTimer::MoveTimer(float secondsToMove_)
		: secondsToMove(secondsToMove_)
	{
	}

	void MoveTimer::reset()
	{
		clock.restart();
	}

	bool MoveTimer::isReadyToMove() const
	{
		return secondsToMove < clock.getElapsedTime().asSeconds();
	}

}
