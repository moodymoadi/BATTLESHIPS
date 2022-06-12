#include<iostream>
#include "Board.h"
#include "Utils.cpp"
#include <string>
using namespace std;

int main() {
	Board b1, b2;
	Utils u;
	b1.getPlayer().setNum(MY_PLAYER);
	b2.getPlayer().setNum(OPPONENT);

	int position, pickedShip, size, fromPos, toPos;
	int fromRow, fromCol, toRow, toCol;
	
	bool isAdjacent = false;
	bool isChooseCorrect = false;

	for (int i = 0; i < 5; i++)
	{
		system("cls");
		b1.printBoard();
		cout << "Please choose a ship and place it in the above board: " << endl;
		b1.printShips();
		cin >> pickedShip;

		u.checkIfCorrectShipChoosed(b1, &pickedShip);//checks if we choosed a ship from 1 to 5

		size = b1.getShipSize(pickedShip - 1);

		do
		{
			if (!isChooseCorrect)
				cout << "Please choose " << size << " adjacent squares horizontaly or verticaly on the board:" << endl;
			else if (isAdjacent) {
				cout << "Can not put two ships near to each other." << endl;
				cout << "Please choose different spot." << endl;
			}

			position = u.checkIfCorrectPositionChoosed(b1, &pickedShip,
				&isChooseCorrect, &size,
				&fromPos, &toPos,
				&fromRow, &fromCol,
				&toRow, &toCol);

			while (position == NO_POSITION && !isChooseCorrect)
			{
				cout << "Please choose " << size << " adjacent squares horizontaly or verticaly on the board:" << endl;
				position = u.checkIfCorrectPositionChoosed(b1, &pickedShip,
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
					position = u.checkIfCorrectPositionChoosed(b1, &pickedShip,
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
					position = u.checkIfCorrectPositionChoosed(b1, &pickedShip,
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

		b1.addToBoard(position, size, fromRow, fromCol, toRow, toCol, SHIP_EXIST, SHIP_EDGES);
		b1.setShip(pickedShip - 1, i + 1, size, position, fromRow, fromCol, toRow, toCol, true);
		b1.getShip(pickedShip - 1).setChoosed(true);
	}
	
	b2.addShipsRandomly();

	u.gamePlay(b1, b2);

	return 0;
}
