#pragma once
#include "Ship.h"
#include <iostream>

using namespace std;

const int SIZE = 5;

class Player {
private:
	Ship ships[SIZE];

public:
	Player();
	void setShip(int i, int _id, int _size, bool _Position, int _fromRow, int _fromCol, int _toRow, int _toCol, bool _living);
	void setShips();
	Ship & getShip(int i);
	Ship* getShips();
	void printShips();
	int getShipSize(int pickedShip);
};
