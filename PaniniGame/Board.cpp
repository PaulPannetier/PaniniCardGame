
#include "Board.hpp"

using namespace std;

Board::Board()
{
	playerBoard1 = PlayerBoard(0);
	playerBoard2 = PlayerBoard(1);
	//PlayerBoard pb = PlayerBoard(0);
	//PlayerBoard pb2 = PlayerBoard(1);

	cout << playerBoard1.playerID() << endl;
	cout << playerBoard2.playerID() << endl;
	/*
	cout << pb.playerID() << endl;
	cout << pb2.playerID() << endl;
	*/
}