#include<iostream>
#include "Board.h"
using namespace std;

void checkIfCorrectShipChoosed(Player _p, int* _pickedShip);
void checkIfCorrectPositionChoosed(Player _p, int* _pickedShip, int* _fromPos,
	int* _toPos, int* _fromRow,
	int* _fromCol, int* _toRow,
	int* _toCol, int* _size,
	int* _position);

int main() {
	int pickedShip, size, fromPos, toPos;
	int fromRow, fromCol, toRow, toCol;
	int position;
	bool isChooseCorrect = false;

	Board b1, b2;
	Player p1, p2;
	Ship sh;

	p1 = b1.getPlayer();

	for (int i = 0; i < 5; i++)
	{
		//system("cls");
		b1.printBoard();
		cout << "Please choose a ship and place it in the above board: " << endl;
		p1.printShips();
		cin >> pickedShip;

		checkIfCorrectShipChoosed(p1, &pickedShip);

		size = p1.getShipSize(pickedShip-1);

		do
		{
			isChooseCorrect = false;
			cout << "please choose " << size << " adjacent squares horizontaly or verticaly on the board:" << endl;
			cout << "from: "; cin >> fromPos;
			while (fromPos < 0 || fromPos > 99) {
				cout << "please choose between 00 to 99";
				cout << "from: "; cin >> fromPos;
			}
			cout << "to: "; cin >> toPos;
			while (toPos < 0 || toPos > 99) {
				cout << "please choose between 00 to 99";
				cout << "to: "; cin >> toPos;
			}
			fromRow = fromPos / 10;
			fromCol = fromPos % 10;
			toRow = toPos / 10;
			toCol = toPos % 10;

			cout << "from row: " << fromRow << ", from col: " << fromCol
				<< ", to row: " << toRow << ", toCol: " << toCol << endl;

			if (fromRow == toRow)
			{
				p1.getShip(pickedShip - 1).setPosition(HORIZONTAL);
			}
			else if (fromCol == toCol) {
				p1.getShip(pickedShip - 1).setPosition(VERTICAL);
			}
			else {
				p1.getShip(pickedShip - 1).setPosition(NO_POSITION);
			}

			position = p1.getShip(pickedShip - 1).getPosition();
			cout << "position: " << position << endl;

			while (position == NO_POSITION && !isChooseCorrect)
			{
				isChooseCorrect = false;
				cout << "please choose " << size << " adjacent squares horizontaly or verticaly on the board:" << endl;
				cout << "from: "; cin >> fromPos;
				while (fromPos < 0 || fromPos > 99) {
					cout << "please choose between 00 to 99";
					cout << "from: "; cin >> fromPos;
				}
				cout << "to: "; cin >> toPos;
				while (toPos < 0 || toPos > 99) {
					cout << "please choose between 00 to 99";
					cout << "to: "; cin >> toPos;
				}
				fromRow = fromPos / 10;
				fromCol = fromPos % 10;
				toRow = toPos / 10;
				toCol = toPos % 10;

				cout << "from row: " << fromRow << ", from col: " << fromCol
					<< ", to row: " << toRow << ", toCol: " << toCol << endl;

				if (fromRow == toRow)
				{
					p1.getShip(pickedShip - 1).setPosition(HORIZONTAL);
				}
				else if (fromCol == toCol) {
					p1.getShip(pickedShip - 1).setPosition(VERTICAL);
				}
				else {
					p1.getShip(pickedShip - 1).setPosition(NO_POSITION);
				}

				position = p1.getShip(pickedShip - 1).getPosition();
				cout << "position: " << position << endl;
			}

			while (position == HORIZONTAL && !isChooseCorrect) {
				if (toCol > fromCol && (toCol - fromCol != size-1) || 
					fromCol > toCol && (fromCol - toCol != size-1))
				{
					isChooseCorrect = false;
					cout << "The horizontal position you chose does not match the size of your ship, please choose " << size << " adjacent squares verticaly or horizontaly on the board:" << endl;
					cout << "from: "; cin >> fromPos;
					while (fromPos < 0 || fromPos > 99) {
						cout << "please choose between 00 to 99";
						cout << "from: "; cin >> fromPos;
					}
					cout << "to: "; cin >> toPos;
					while (toPos < 0 || toPos > 99) {
						cout << "please choose between 00 to 99";
						cout << "to: "; cin >> toPos;
					}
					fromRow = fromPos / 10;
					fromCol = fromPos % 10;
					toRow = toPos / 10;
					toCol = toPos % 10;

					cout << "from row: " << fromRow << ", from col: " << fromCol
						<< ", to row: " << toRow << ", toCol: " << toCol << endl;

					if (fromRow == toRow)
					{
						p1.getShip(pickedShip - 1).setPosition(HORIZONTAL);
					}
					else if (fromCol == toCol) {
						p1.getShip(pickedShip - 1).setPosition(VERTICAL);
					}
					else {
						p1.getShip(pickedShip - 1).setPosition(NO_POSITION);
					}

					position = p1.getShip(pickedShip - 1).getPosition();
					cout << "position: " << position << endl;
				}
				else {
					isChooseCorrect = true;
				}
			}

			while (position == VERTICAL && !isChooseCorrect)
			{
				if (toRow > fromRow && (toRow - fromRow != size-1)||
					fromRow > toRow && (fromRow - toRow != size-1))
				{
					isChooseCorrect = false;
					cout << "The vertical position you chose does not match the size of your ship, please choose " << size << " adjacent squares verticaly or horizontaly on the board: " << endl;
					cout << "from: "; cin >> fromPos;
					while (fromPos < 0 || fromPos > 99) {
						cout << "please choose between 00 to 99";
						cout << "from: "; cin >> fromPos;
					}
					cout << "to: "; cin >> toPos;
					while (toPos < 0 || toPos > 99) {
						cout << "please choose between 00 to 99";
						cout << "to: "; cin >> toPos;
					}
					fromRow = fromPos / 10;
					fromCol = fromPos % 10;
					toRow = toPos / 10;
					toCol = toPos % 10;

					cout << "from row: " << fromRow << ", from col: " << fromCol
						<< ", to row: " << toRow << ", toCol: " << toCol << endl;

					if (fromRow == toRow)
					{
						p1.getShip(pickedShip - 1).setPosition(HORIZONTAL);
					}
					else if (fromCol == toCol) {
						p1.getShip(pickedShip - 1).setPosition(VERTICAL);
					}
					else {
						p1.getShip(pickedShip - 1).setPosition(NO_POSITION);
					}

					position = p1.getShip(pickedShip - 1).getPosition();
					cout << "position: " << position << endl;
				}
				else {
					isChooseCorrect = true;
				}
			}
		} while (!isChooseCorrect);
		
		p1.getShip(pickedShip-1).setPlace(size, position, fromRow, fromCol);
		b1.addToBoard(position, size, fromRow, fromCol);

		for (int i = 0; i < 5; i++)
		{
			cout << "is ship choosed: " << p1.getShip(i).isChoosed() << endl;
			cout << "is ship living: " << p1.getShip(i).isLiving() << endl;
			cout << "ship from row: " << p1.getShip(i).getFromRow() << endl;
			cout << "ship to row: " << p1.getShip(i).getToRow() << endl;
			cout << "ship from col: " << p1.getShip(i).getFromCol() << endl;
			cout << "ship to col: " << p1.getShip(i).getToCol() << endl;
		}
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

void checkIfCorrectShipChoosed(Player _p, int* _pickedShip) {
	while (*_pickedShip < 1
		|| *_pickedShip > 5
		|| _p.getShip(*_pickedShip - 1).isChoosed()) {
		if (*_pickedShip < 1 || *_pickedShip > 5) {
			cout << "please choose a number between 1 to 5." << endl;
		}
		else if (_p.getShip(*_pickedShip - 1).isChoosed()) {
			cout << "ship already choosed! please choose other ship." << endl;
		}

		cin >> *_pickedShip;
	}
}

//void checkIfCorrectPositionChoosed(Player _p, int* _pickedShip,
//	int* _fromPos, int* _toPos,
//	int* _fromRow, int* _fromCol,
//	int* _toRow, int* _toCol,
//	int* _size, int* _position){
//	_fromRow = _fromPos / 10;
//	_fromCol = _fromPos % 10;
//	_toRow = _toPos / 10;
//	_toCol = _toPos % 10;
//
//	cout << "from row: " << _fromRow << ", from col: " << _fromCol
//		<< ", to row: " << _toRow << ", toCol: " << _toCol << endl;
//
//	if (_fromRow == _toRow)
//	{
//		_p.getShip((int)_pickedShip - 1).setPosition(HORIZONTAL);
//	}
//	else if (_fromCol == _toCol) {
//		_p.getShip((int)_pickedShip - 1).setPosition(VERTICAL);
//	}
//	else {
//		_p.getShip((int)_pickedShip - 1).setPosition(NO_POSITION);
//	}
//
//	_position = _p.getShip((int)_pickedShip - 1).getPosition();
//	cout << "position: " << _position << endl;
//}
