#pragma once
#include <iostream>
#include "Ship.h"
#include <time.h>

using namespace std;

const int NUM_OF_SHIPS = 5;

const int MY_PLAYER = 1;
const int OPPONENT = 2;

class Player {
private:
	int num;
	Ship ships[NUM_OF_SHIPS];

public:
	Player();
	void setShip(int i, int _id, int _size, bool _Position, int _fromRow, int _fromCol, int _toRow, int _toCol, bool _living);
	void setShips();
	void setNum(int _num);

	Ship & getShip(int i);
	Ship* getShips();
	Ship& getShipByElement(int row, int col);
	void UpdateShipDestructionByElement(int row, int col);
	int getNum();
	void printShips();
	int getShipSize(int pickedShip);

};
