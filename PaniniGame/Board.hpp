#ifndef BOARD_HPP
#define BOARD_HPP

#include "PlayerBoard.hpp"

class Board
{
private:

public:
	PlayerBoard playerBoard1, playerBoard2;

	Board();

	Board& operator =(Board value)
	{
		return value;
	}
};

#endif