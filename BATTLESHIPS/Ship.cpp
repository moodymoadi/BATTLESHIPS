#include "Ship.h"

Ship::Ship(){
	/*default constructor*/
}

Ship::Ship(int _id, int _size, int _pos, int _fromRow, int _fromCol, int _toRow, int _toCol, bool _choosed, bool _living){
	setId(_id);
	setSize(_size);
	setPosition(_pos);
	setPlace(_fromRow, _fromCol, _toRow, toCol);
	setChoosed(false);
	setLiving(_living);
	setDestruction(_size);
}

void Ship::setId(int _id){
	id = _id;
}

void Ship::setSize(int _size){
	size = _size;
}

void Ship::setPosition(int _pos){
	position = _pos;
}

void Ship::setFromRow(int _fromRow){
	fromRow = _fromRow;
}

void Ship::setFromCol(int _col){
	fromCol = _col;
}

void Ship::setToRow(int _toRow) {
	toRow = _toRow;
}

void Ship::setToCol(int _toCol) {
	toCol = _toCol;
}

void Ship::setPlace(int _size, int _position, int _fromRow, int _fromCol){
	if (_position == HORIZONTAL) {
		fromRow = _fromRow;
		fromCol = _fromCol;
		toRow = _fromRow;
		toCol = _fromCol + _size-1;
	}
	else if (_position == VERTICAL) {
		fromRow = _fromRow;
		fromCol = _fromCol;
		toRow = _fromRow + _size-1;
		toCol = _fromCol;
	}
	/*fromRow = _fromRow;
	fromCol = _fromCol;
	toRow = _toRow;
	toCol = _toCol;*/
	setChoosed(true);
}

void Ship::setLiving(bool _living){
	living = _living;
}

void Ship::setChoosed(bool _choosed) {
	choosed = _choosed;
}

void Ship::setDestruction(int _size){
	destruction.resize(_size, true);
}

int Ship::getId(){
	return id;
}

int Ship::getSize(){
	return size;
}

int Ship::getPosition(){
	return position;
}

int Ship::getFromRow(){
	return fromRow;
}

int Ship::getFromCol()
{
	return fromCol;
}

int Ship::getToRow() {
	return toRow;
}

int Ship::getToCol() {
	return toCol;
}

bool Ship::isLiving(){
	return living;
}

bool Ship::isChoosed() {
	return choosed;
}

vector<bool> Ship::isDestruction(){
	return destruction;
}

bool Ship::checkIfLiving(vector<bool> _dest)
{
	for (int i = 0; i < size; i++)
	{
		if (_dest.at(i))
		{
			setLiving(true);
			return true;
		}
	}
	setLiving(false);
	return false;
}

void Ship::updateDestruction(int i) {
	destruction.at(i) = false;
}


