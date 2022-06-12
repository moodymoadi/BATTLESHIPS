#pragma once
#include<vector>

using namespace std;

const int HORIZONTAL = 1;
const int VERTICAL = 0;
const int NO_POSITION = 2;

class Ship {
private:
	int id;
	int size;
	int position;
	int fromRow;
	int fromCol;
	int toRow;
	int toCol;
	bool choosed;
	bool living;
	vector<bool> destruction;

public:
	Ship();
	Ship(int _id, int _size, int _Position, int _fromRow, int _fromCol, int _toRow, int _toCol, bool _choosed, bool _living);
	void setId(int _id);
	void setSize(int _size);
	void setPosition(int _pos);
	void setFromRow(int _fromRow);
	void setFromCol(int _fromCol);
	void setToRow(int _toRow);
	void setToCol(int _toCol);
	void setPlace(int _size, int _position, int _fromRow, int _fromCol, int _toRow, int _toCol);
	void setChoosed(bool _choosed);
	void setLiving(bool _living);
	void setDestruction(int _size);

	int getId();
	int getSize();
	int getPosition();
	int getFromRow();
	int getFromCol();
	int getToRow();
	int getToCol();
	bool isChoosed();
	bool isLiving();
	vector<bool> getDestruction();

	void updateDestruction(int i);
	bool checkIfLiving(vector<bool> _dest);
};
