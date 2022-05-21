#include<iostream>
#include "Board.h"

Board::Board(){
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			myBoard[0][i][j] = ' ';
		}
	}
	p.setShips();
}

void Board::addToBoard(int _position, int _size, int _fromRow, int _fromCol){
	if (_position == HORIZONTAL){
		for (int i = 0; i < _size; i++)
		{
			myBoard[0][_fromRow][_fromCol++] = 'x';
		}
	}
	else if (_position == VERTICAL) {
		for (int i = 0; i < _size; i++)
		{
			myBoard[0][_fromRow++][_fromCol] = 'x';
		}
	}
	
}

void Board::printBoard(){
	cout << "  ";
	for (int k = 0; k < 10; k++)
	{
		cout << k << " ";
	}
	cout << endl;
	cout << "  ";
	for (int k = 0; k < 10; k++)
	{
		cout << "- ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << "|";
		for (int j = 0; j < 10; j++)
		{
			cout << myBoard[0][i][j] << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << "  ";
	for (int k = 0; k < 10; k++)
	{
		cout << "- ";
	}
	cout << endl;
}

void Board::setPlayer(Player _p){
	p = _p;
}

Player & Board::getPlayer(){
	return p;
}
