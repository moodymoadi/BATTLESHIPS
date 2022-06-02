#include<iostream>
#include "Board.h"
#include "Utils.cpp"
#include <string>
using namespace std;

//const int PLAYER_1 = 1;
//const int PLAYER_2 = 2;

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
		u.printShipsForTwoPlayers(b1, b2);
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
