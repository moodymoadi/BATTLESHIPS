#pragma once
#include "Player.h";

using namespace std;
const int BSIZE = 10;
class Board {

private:
	char myBoard[1][BSIZE][BSIZE];
	Player p;
public:
	Board();
	void addToBoard(int _position, int _size, int _fromRow, int _fromCol);
	void printBoard();
	void setPlayer(Player _p);
	Player & getPlayer();

};
