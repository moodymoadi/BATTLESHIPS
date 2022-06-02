#include <iostream>
#include "Board.h"
#include <windows.h> // WinApi header
using namespace std;

class Utils {
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
private:

};