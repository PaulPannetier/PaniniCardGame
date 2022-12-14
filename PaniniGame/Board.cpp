
#include "Board.hpp"

using namespace std;
using namespace sf;

Board::Board()
{

}

//Affiche le plateau de jeu
void Board::Draw(RenderWindow& window)
{
	int i;
	//Le joueur du haut
	for (i = 0; i < NB_MAX_GOAL_KEEPER; i++)
	{
		if (this->goalKeepersUp[i].isInitialised)
		{
			this->goalKeepersUp[i].Draw(window, this->goalKeeperUpPos[i], this->cardSize);
		}
	}
}