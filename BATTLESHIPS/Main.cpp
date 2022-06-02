#include<iostream>
#include "Board.h"
#include "Utils.cpp"
#include <string>
using namespace std;

//const int PLAYER_1 = 1;
//const int PLAYER_2 = 2;

int checkIfCorrectPositionChoosed(Board _b, int* _pickedShip,
	bool* _isChooseCorrect, int* _size,
	int* _fromPos, int* _toPos,
	int* _fromRow, int* _fromCol,
	int* _toRow, int* _toCol);
void printShipsForOnePlayer(Board _b);
void printShipsForTwoPlayers(Board _b1, Board _b2);

int main() {
	Utils u;

	bool gameStatus = GAME_ON;
	int currentTurn = MY_PLAYER;

	int option, position, pickedShip, size, fromPos, toPos;
	int fromRow, fromCol, toRow, toCol;
	
	bool isAdjacent;
	bool isChooseCorrect = false;

	Board b1, b2;
	b1.getPlayer().setNum(MY_PLAYER);
	b2.getPlayer().setNum(OPPONENT);

	b1.printBoard();
	
	cout << "Choose how to add ships to board: " << endl;
	cout << "1: Add ships randomly" << endl;
	cout << "2: Add ships manualy" << endl;
	cin >> option;
	getchar();
	while (option != 1 && option != 2) {
		cout << "Please choose an option 1 or 2." << endl;
		cin >> option;
	}
	system("cls");
	if (option == 1)
	{
		b1.addShipsRandomly();
	}
	else if (option == 2) {
		for (int i = 0; i < 5; i++)
		{
			system("cls");
			b1.printBoard();
			cout << "Please choose a ship and place it in the above board: " << endl;
			b1.printShips();
			cin >> pickedShip;

			u.checkIfCorrectShipChoosed(b1, &pickedShip);

			size = b1.getShipSize(pickedShip - 1);

			do
			{
				if (!isChooseCorrect)
					cout << "Please choose " << size << " adjacent squares horizontaly or verticaly on the board:" << endl;
				else if (isAdjacent) {
					cout << "Can not put two ships near to each other." << endl;
					cout << "Please choose different spot." << endl;
				}

				position = checkIfCorrectPositionChoosed(b1, &pickedShip,
					&isChooseCorrect, &size,
					&fromPos, &toPos,
					&fromRow, &fromCol,
					&toRow, &toCol);

				while (position == NO_POSITION && !isChooseCorrect)
				{
					cout << "Please choose " << size << " adjacent squares horizontaly or verticaly on the board:" << endl;
					position = checkIfCorrectPositionChoosed(b1, &pickedShip,
						&isChooseCorrect, &size,
						&fromPos, &toPos,
						&fromRow, &fromCol,
						&toRow, &toCol);
				}

				while (position == HORIZONTAL && !isChooseCorrect) {
					if (toCol > fromCol && (toCol - fromCol != size - 1) ||
						fromCol > toCol && (fromCol - toCol != size - 1))
					{
						cout << "The horizontal position you chose does not match the size of your ship." << endl
							<< "Please choose " << size << " adjacent squares verticaly or horizontaly on the board : " << endl;
						position = checkIfCorrectPositionChoosed(b1, &pickedShip,
							&isChooseCorrect, &size,
							&fromPos, &toPos,
							&fromRow, &fromCol,
							&toRow, &toCol);
					}
					else {
						isChooseCorrect = true;
					}
				}

				while (position == VERTICAL && !isChooseCorrect)
				{
					if (toRow > fromRow && (toRow - fromRow != size - 1) ||
						fromRow > toRow && (fromRow - toRow != size - 1))
					{
						cout << "The vertical position you chose does not match the size of your ship." << endl
							<< "Please choose " << size << " adjacent squares verticaly or horizontaly on the board : " << endl;
						position = checkIfCorrectPositionChoosed(b1, &pickedShip,
							&isChooseCorrect, &size,
							&fromPos, &toPos,
							&fromRow, &fromCol,
							&toRow, &toCol);
					}
					else {
						isChooseCorrect = true;
					}
				}
				isAdjacent = b1.checkIfAdjacent(position, size, fromRow, fromCol, toRow, toCol);
			} while (!isChooseCorrect || isAdjacent);

			b1.addToBoard(position, size, fromRow, fromCol, toRow, toCol);
			b1.getShip(pickedShip - 1).setPlace(size, position, fromRow, fromCol, toRow, toCol);
		}
	}

	b2.addShipsRandomly();

	while (gameStatus == GAME_ON) // while gameStatus is equal to gameOn=1 keep playing
	{
		//system("cls");
		cout << endl << "Opponent's board: " << endl;
		b2.printBoard();

		cout << endl << "My board: " << endl;
		b1.printBoard();
		if (currentTurn == MY_PLAYER)
		{
			b2.play(); // you play and update player2's board
			gameStatus = b2.checkGameStatus(); // check sataus of player 2 ships
			currentTurn = OPPONENT; // switch turn
		}
		else {
			b1.play(); // player 2 plays and update your board
			gameStatus = b1.checkGameStatus(); //check status of your ships
			currentTurn = MY_PLAYER; // switch turn
		}
		printShipsForTwoPlayers(b1, b2);
	}
	
	

	/*cout << "ship number 5 is: " << (sh1.checkIfLiving(sh1.isDestruction())? "living": "distroyed") << endl;
	sh1.updateDestruction(1);
	cout << "ship number 5 is: " << (sh1.checkIfLiving(sh1.isDestruction()) ? "living" : "distroyed") << endl;
	sh1.updateDestruction(0);
	sh1.checkIfLiving(sh1.isDestruction());
	cout << "ship number 5 is: " << (sh1.isLiving() ? "living" : "distroyed") << endl;*/
	

	
	/*cout << endl << endl;
	cout << "computer's board: " << endl;
	b2.printBoard();*/

	return 0;
}

// the user chooses two elements on the board
// 1_from element, 2_to element. the funcion checks if the user
// choosed horizotaly or vertacly or non of them by the two choosed elements
int checkIfCorrectPositionChoosed(Board _b, int* _pickedShip,
	bool* _isChooseCorrect, int* _size,
	int* _fromPos, int* _toPos,
	int* _fromRow, int* _fromCol,
	int* _toRow, int* _toCol){

	*_isChooseCorrect = false;
	cout << "from: "; cin >> *_fromPos;
	while (*_fromPos < 0 || *_fromPos > 99) {
		cout << "please choose between 00 to 99" << endl;
		cout << "from: "; cin >> *_fromPos;
	}
	cout << "to: "; cin >> *_toPos;
	while (*_toPos < 0 || *_toPos > 99) {
		cout << "please choose between 00 to 99" << endl;
		cout << "to: "; cin >> *_toPos;
	}
	*_fromRow = *_fromPos / 10;//takes the row(fromRow) from the first choosen element
	*_fromCol = *_fromPos % 10;//takes the column(fromCol) from the first choosen element
	*_toRow = *_toPos / 10;//takes the row(toRow) from the second choosen element
	*_toCol = *_toPos % 10;//takes the column(toCol) from the second choosen element

	if (*_fromPos == *_toPos)
	{
		_b.getShip(*_pickedShip - 1).setPosition(NO_POSITION);
	}
	else if (*_fromRow == *_toRow)
	{
		_b.getShip(*_pickedShip - 1).setPosition(HORIZONTAL);
	}
	else if (*_fromCol == *_toCol) {
		_b.getShip(*_pickedShip - 1).setPosition(VERTICAL);
	}
	else {
		_b.getShip(*_pickedShip - 1).setPosition(NO_POSITION);
	}
	return _b.getShip(*_pickedShip - 1).getPosition();
}

void printShipsForOnePlayer(Board _b) {
	for (int i = 0; i < 5; i++)
	{
		cout << endl;
		cout << "player 1 ship " << i + 1 << ":" << endl;
		cout << "is ship choosed: " << _b.getShip(i).isChoosed() << endl;
		cout << "is ship living: " << _b.getShip(i).isLiving() << endl;
		cout << "ship from row: " << _b.getShip(i).getFromRow() << endl;
		cout << "ship from col: " << _b.getShip(i).getFromCol() << endl;
		cout << "ship to row: " << _b.getShip(i).getToRow() << endl;
		cout << "ship to col: " << _b.getShip(i).getToCol() << endl;
	}
}

void printShipsForTwoPlayers(Board _b1, Board _b2) {
	for (int i = 0; i < 5; i++)
	{
		cout << endl;
		cout << "player 1 ship " << i + 1 << ":" << endl;
		cout << "is ship choosed: " << _b1.getShip(i).isChoosed() << endl;
		cout << "is ship living: " << _b1.getShip(i).isLiving() << endl;
		cout << "ship from row: " << _b1.getShip(i).getFromRow() << endl;
		cout << "ship from col: " << _b1.getShip(i).getFromCol() << endl;
		cout << "ship to row: " << _b1.getShip(i).getToRow() << endl;
		cout << "ship to col: " << _b1.getShip(i).getToCol() << endl;
	}

	for (int i = 0; i < 5; i++)
	{
		cout << endl;
		cout << "player 2 ship " << i + 1 << ":" << endl;
		cout << "is ship choosed: " << _b2.getShip(i).isChoosed() << endl;
		cout << "is ship living: " << _b2.getShip(i).isLiving() << endl;
		cout << "ship from row: " << _b2.getShip(i).getFromRow() << endl;
		cout << "ship from col: " << _b2.getShip(i).getFromCol() << endl;
		cout << "ship to row: " << _b2.getShip(i).getToRow() << endl;
		cout << "ship to col: " << _b2.getShip(i).getToCol() << endl;
	}
}
