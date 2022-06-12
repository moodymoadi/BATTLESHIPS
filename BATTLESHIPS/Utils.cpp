#include <iostream>
#include "Board.h"
#include <windows.h>
using namespace std;

class Utils {
private:

public:
	void SetConsoleColour(WORD* Attributes, DWORD Colour)
	{
		CONSOLE_SCREEN_BUFFER_INFO Info;
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout, &Info);
		*Attributes = Info.wAttributes;
		SetConsoleTextAttribute(hStdout, Colour);
	}

	void ResetConsoleColour(WORD Attributes)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
	}

	void checkIfCorrectShipChoosed(Board _b, int* _pickedShip) {
		while (*_pickedShip < 1
			|| *_pickedShip > 5
			|| _b.getShip(*_pickedShip - 1).isChoosed()) {
			if (*_pickedShip < 1 || *_pickedShip > 5) {
				cout << "please choose a number between 1 to 5." << endl;
			}
			else if (_b.getShip(*_pickedShip - 1).isChoosed()) {
				cout << "ship already choosed! please choose other ship." << endl;
			}

			cin >> *_pickedShip;
		}
	}

	// the user chooses two elements on the board
	// 1_from element, 2_to element. the funcion checks if the user
	// choosed horizotaly or vertacly or non of them by the two choosed elements
	int checkIfCorrectPositionChoosed(Board _b, int* _pickedShip,
		bool* _isChooseCorrect, int* _size,
		int* _fromPos, int* _toPos,
		int* _fromRow, int* _fromCol,
		int* _toRow, int* _toCol) {

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
			cout << "ship size: " << _b1.getShip(i).getSize() << endl;
			cout << "is ship choosed: " << _b1.getShip(i).isChoosed() << endl;
			cout << "is ship living: " << _b1.getShip(i).isLiving() << endl;
			cout << "ship from row: " << _b1.getShip(i).getFromRow() << endl;
			cout << "ship from col: " << _b1.getShip(i).getFromCol() << endl;
			cout << "ship to row: " << _b1.getShip(i).getToRow() << endl;
			cout << "ship to col: " << _b1.getShip(i).getToCol() << endl;
			cout << "ship position: " << _b1.getShip(i).getPosition() << endl;
		}

		for (int i = 0; i < 5; i++)
		{
			cout << endl;
			cout << "player 2 ship " << i + 1 << ":" << endl;
			cout << "ship size: " << _b2.getShip(i).getSize() << endl;
			cout << "is ship choosed: " << _b2.getShip(i).isChoosed() << endl;
			cout << "is ship living: " << _b2.getShip(i).isLiving() << endl;
			cout << "ship from row: " << _b2.getShip(i).getFromRow() << endl;
			cout << "ship from col: " << _b2.getShip(i).getFromCol() << endl;
			cout << "ship to row: " << _b2.getShip(i).getToRow() << endl;
			cout << "ship to col: " << _b2.getShip(i).getToCol() << endl;
			cout << "ship position: " << _b2.getShip(i).getPosition() << endl;
		}
	}

	void printTwoBaords(Board b1, Board b2) {
		system("cls");
		cout << endl << "Opponent's board: " << endl;
		b2.printBoard();
		cout << endl << "My board: " << endl;
		b1.printBoard();
	}

	void gamePlay(Board b1, Board b2) {
		bool gameStatus = GAME_ON;
		int currentTurn = MY_PLAYER;
		while (gameStatus == GAME_ON) // while gameStatus is equal to gameOn=1 keep playing
		{
			printTwoBaords(b1, b2);
			if (currentTurn == MY_PLAYER)
			{
				b2.play(); // you play and update player2's board
				gameStatus = b2.checkGameStatus(); // check status of player 2 ships
				currentTurn = OPPONENT; // switch turn
			}
			else {
				b1.play(); // AI plays and update your board
				gameStatus = b1.checkGameStatus(); //check status of your ships, if false then game-over
				currentTurn = MY_PLAYER; // switch turn
			}
		}
		endOfGame(b1, b2);
	}

	void endOfGame(Board myBoard, Board AIBoard) {
		system("cls");
		cout << endl << "Opponent's board: " << endl;
		AIBoard.printBoard();
		cout << endl << "My board: " << endl;
		myBoard.printBoard();

		if (!myBoard.getPlayer().checkIfAllShipsAlive()) {
			cout << "pc win";
			PlaySound(TEXT("game-lose.wav"), NULL, SND_SYNC);
		}
		else if (!AIBoard.getPlayer().checkIfAllShipsAlive()) {
			cout << "you win";
			PlaySound(TEXT("victory.wav"), NULL, SND_SYNC);
		}
			
	}
};