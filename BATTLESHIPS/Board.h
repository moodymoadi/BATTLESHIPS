#pragma once
#include <chrono>
#include <thread>
#include "Player.h";


using namespace std;

const int EMPTY = 0;
const int SHIP_EXIST = 1;
const int SHIP_EDGES = -1;
const int HIT = 2;
const int MISS = 3;

const int GAME_ON = 1;
const int GAME_OVER = 0;

const int BSIZE = 10;
class Board {

private:
	int myBoard[BSIZE][BSIZE];
	Player p;
public:
	Board();
	void setShip(int i, int _id, int _size, bool _Position, int _fromRow, int _fromCol, int _toRow, int _toCol, bool _living);
	void setPlayer(Player _p);
	Ship& getShip(int i);
	Player & getPlayer();
	int getShipSize(int pickedShip);


	void printBoard();
	void printShips();
	void addShipsRandomly();
	bool checkIfAdjacent(int _position, int _size, int _fromRow, int _fromCol, int toRow, int toCol);
	void addToBoard(int _position, int _size, int _fromRow, int _fromCol, int _toRow, int _toCol);
	// -> functions inside the addToBoard() function  
	void addFromLeftToRight(int _position, int _size, int _fromRow, int _fromCol, int _toRow, int _toCol);
	void addFromRightToLeft(int _position, int _size, int _fromRow, int _fromCol, int _toRow, int _toCol);
	void addFromUpToDown(int _position, int _size, int _fromRow, int _fromCol, int _toRow, int _toCol);
	void addFromDownToUp(int _position, int _size, int _fromRow, int _fromCol, int _toRow, int _toCol);
	// to here <- 
	void play();
	bool checkGameStatus();
	void endGame();
};
