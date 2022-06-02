#include<iostream>
#include "Board.h"
#include "Utils.cpp"



Board::Board(){
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			myBoard[i][j] = 0;
		}
	}
	p.setShips();
}

void Board::setPlayer(Player _p){
	p = _p;
}

void Board::setShip(int i, int _id, int _size, bool _Position, int _fromRow, int _fromCol, int _toRow, int _toCol, bool _living)
{
	p.setShip(i, _id, _size, _Position, _fromRow, _fromCol, _toRow, _toCol, _living);
}

Player& Board::getPlayer() {
	return p;
}

Ship& Board::getShip(int i)
{
	return p.getShip(i);
}

int Board::getShipSize(int pickedShip)
{
	return p.getShipSize(pickedShip);
}

void Board::addShipsRandomly()
{
	int fromRow, fromCol, toRow, toCol;
	bool isAdjacent;
	
	    setShip(0, 1, 5, HORIZONTAL, -1, -1, -1, -1, true);
	    setShip(1, 2, 4, HORIZONTAL, -1, -1, -1, -1, true);
	    setShip(2, 3, 3, HORIZONTAL, -1, -1, -1, -1, true);
	    setShip(3, 4, 3, HORIZONTAL, -1, -1, -1, -1, true);
	    setShip(4, 5, 2, HORIZONTAL, -1, -1, -1, -1, true);
	
	    srand(time(NULL)); //Randomize seed initialization
	    
	    for (int i = 0; i < 5; i++)
	    {
			isAdjacent = true;
			while (isAdjacent) {
				int size = getShip(i).getSize();
				int randPosition = rand() % 2;
				int r = rand() % 100;// Generate a random number between 0 and 99
				fromRow = r / 10;
				fromCol = r % 10;
				if (randPosition == VERTICAL)
				{
					if (fromRow - size >= 0)
					{
						toRow = fromRow - size + 1;
					}
					else if (fromRow + size <= 9)
					{
						toRow = fromRow + size - 1;
					}
					toCol = fromCol;
				}
				else if (randPosition == HORIZONTAL)
				{
					if (fromCol - size >= 0)
					{
						toCol = fromCol - size + 1;
					}
					else if (fromCol + size <= 9)
					{
						toCol = fromCol + size - 1;
					}
					toRow = fromRow;
				}
				isAdjacent = checkIfAdjacent(randPosition, size, fromRow, fromCol, toRow, toCol);
				if (!isAdjacent)
				{
					addToBoard(randPosition, size, fromRow, fromCol, toRow, toCol);
					setShip(i, i + 1, size, randPosition, fromRow, fromCol, toRow, toCol, true);
					getShip(i).setChoosed(true);
				}
			}
	    }
}

// check if two ships are adjacent to each other
//return true if adjacent
//return false if no adjacent
bool Board::checkIfAdjacent(int _position, int _size, int _fromRow,
	int _fromCol, int _toRow, int _toCol)
{
	for (int i = 0; i < _size; i++)
	{
		if (_position == HORIZONTAL && _toCol > _fromCol)//check horizintaly from left to right
		{
			if (myBoard[_fromRow][_fromCol + i] == SHIP_EDGES || myBoard[_fromRow][_fromCol + i] == SHIP_EXIST)
				return true;
		}
		else if (_position == HORIZONTAL && _fromCol > _toCol)//check horizontaly from right to left
		{
			if (myBoard[_fromRow][_fromCol - i] == SHIP_EDGES || myBoard[_fromRow][_fromCol - i] == SHIP_EXIST)
				return true;
		}
		else if (_position == VERTICAL && _toRow > _fromRow)//check verticaly from up to down
		{
			if (myBoard[_fromRow + i][_fromCol] == SHIP_EDGES || myBoard[_fromRow + i][_fromCol] == SHIP_EXIST)
				return true;
		}
		else if (_position == VERTICAL && _fromRow > _toRow)//check verticaly from down to up
		{
			if (myBoard[_fromRow - i][_fromCol] == SHIP_EDGES || myBoard[_fromRow - i][_fromCol] == SHIP_EXIST)
				return true;
		}
	}
	return false;
}

/*this function adds the ship to the board by initializing 1
to the elements that the ship is located in*/
void Board::addToBoard(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol){

	/* add ship to the board horizintaly from left to right*/
	if (_position == HORIZONTAL && _toCol > _fromCol) {
		addFromLeftToRight(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol);
	}

	/* add ship to the board horizintaly from right to left*/
	else if (_position == HORIZONTAL && _fromCol > _toCol)
	{
		addFromRightToLeft(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol);
	}

	/* add ship to the board verticaly from up to down*/
	else if (_position == VERTICAL && _toRow > _fromRow) {
		addFromUpToDown(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol);
	}

	/* add ship to the board verticaly from down to up*/
	else if (_position == VERTICAL && _fromRow > _toRow)
	{
		addFromDownToUp(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol);
	}
	
}

void Board::addFromLeftToRight(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol) {

	int temp = _fromCol;

	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		/*this makes the elements of the ship equal to 1*/
		myBoard[_fromRow][_fromCol++] = SHIP_EXIST;//the ship

		//todo -- put out side of the parent loop
		/* make all the adjacent elements
		from bellow and above the ship (row-1 and row+1) equal to -1 */
		for (int i = 0; i < _size; i++)
		{
			if (_fromRow != 9)
				myBoard[_fromRow + 1][temp + i] = SHIP_EDGES;
			if (_fromRow != 0)
				myBoard[_fromRow - 1][temp + i] = SHIP_EDGES;
		}

		/* make all the adjacent elements
		from left to the ship (col-1) equal to -1 */
		if (temp != 0 && _fromRow != 0)
			myBoard[_fromRow - 1][temp - 1] = SHIP_EDGES;//aboveLeft
		if (temp != 0)
			myBoard[_fromRow][temp - 1] = SHIP_EDGES;//left
		if (temp != 0 && _fromRow != 9)
			myBoard[_fromRow + 1][temp - 1] = SHIP_EDGES;//bellowLeft

		/* make all the adjacent elements
		from right to the ship (col+size) equal to -1 */
		if (temp + _size != 10 && _fromRow != 0)
			myBoard[_fromRow - 1][temp + _size] = SHIP_EDGES;//aboveRight
		if (temp + _size != 10)
			myBoard[_fromRow][temp + _size] = SHIP_EDGES;//right
		if (temp + _size != 10 && _fromRow != 9)
			myBoard[_fromRow + 1][temp + _size] = SHIP_EDGES;//bellowRight
	}
}

void Board::addFromRightToLeft(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol) {
	int temp = _fromCol;

	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		/*this makes the elements of the ship equal to 1*/
		myBoard[_fromRow][_fromCol--] = SHIP_EXIST;// the ship

		//todo -- put out side of the parent loop
		/* make all the adjacent elements
		from bellow and above the ship (row-1 and row+1) equal to -1 */
		for (int i = 0; i < _size; i++)
		{
			if (_fromRow != 9)
				myBoard[_fromRow + 1][temp - i] = SHIP_EDGES;
			if (_fromRow != 0)
				myBoard[_fromRow - 1][temp - i] = SHIP_EDGES;
		}

		/* make all the adjacent elements
		from left to the ship (col-size) equal to -1*/
		if (temp - _size != -1 && _fromRow != 0)
			myBoard[_fromRow - 1][temp - _size] = SHIP_EDGES;//aboveLeft
		if (temp - _size != -1)
			myBoard[_fromRow][temp - _size] = SHIP_EDGES;//left
		if (temp - _size != -1 && _fromRow != 9)
			myBoard[_fromRow + 1][temp - _size] = SHIP_EDGES;//bellowLeft

		/* make all the adjacent elements
		from right to the ship (col+1) equal to -1 */
		if (temp != 9 && _fromRow != 0)
			myBoard[_fromRow - 1][temp + 1] = SHIP_EDGES;//aboveRight
		if (temp != 9)
			myBoard[_fromRow][temp + 1] = SHIP_EDGES;//right
		if (temp != 9 && _fromRow != 9)
			myBoard[_fromRow + 1][temp + 1] = SHIP_EDGES;//bellowRight
	}
}

void Board::addFromUpToDown(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol) {
	int temp = _fromRow;

	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		myBoard[_fromRow++][_fromCol] = SHIP_EXIST;// the ship

		//todo -- put out side of the parent loop
		/* make all the adjacent elements
		from right and left the ship (col-1 and col+1) equal to -1 */
		for (int i = 0; i < _size; i++)
		{
			if (_fromCol != 9)
				myBoard[temp + i][_fromCol + 1] = SHIP_EDGES;
			if (_fromCol != 0)
				myBoard[temp + i][_fromCol - 1] = SHIP_EDGES;
		}

		/* make all the adjacent elements
		above to the ship (row-1) equal to -1 */
		if (temp != 0 && _fromCol != 0)
			myBoard[temp - 1][_fromCol - 1] = SHIP_EDGES;//leftAbove
		if (temp != 0)
			myBoard[temp - 1][_fromCol] = SHIP_EDGES;//above
		if (temp != 0 && _fromCol != 9)
			myBoard[temp - 1][_fromCol + 1] = SHIP_EDGES;//rightAbove

		/* make all the adjacent elements
		bellow the ship (row+size) equal to -1*/
		if (temp + _size != 10 && _fromCol != 0)
			myBoard[temp + _size][_fromCol - 1] = SHIP_EDGES;//leftBellow
		if (temp + _size != 10)
			myBoard[temp + _size][_fromCol] = SHIP_EDGES;//bellow
		if (temp + _size != 10 && _fromCol != 9)
			myBoard[temp + _size][_fromCol + 1] = SHIP_EDGES;//rightBellow
	}
}

void Board::addFromDownToUp(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol) {
	int temp = _fromRow;
	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		myBoard[_fromRow--][_fromCol] = SHIP_EXIST;// the ship
		for (int i = 0; i < _size; i++)
		{
			if (_fromCol != 9)
				myBoard[temp - i][_fromCol + 1] = SHIP_EDGES;
			if (_fromCol != 0)
				myBoard[temp - i][_fromCol - 1] = SHIP_EDGES;
		}

		//todo -- put outside
		/* make all the adjacent elements
		above to the ship (row-size) equal to -1 */
		if (temp - _size != -1 && _fromCol != 0)
			myBoard[temp - _size][_fromCol - 1] = SHIP_EDGES;//leftAbove
		if (temp - _size != -1)
			myBoard[temp - _size][_fromCol] = SHIP_EDGES;//above
		if (temp - _size != -1 && _fromCol != 9)
			myBoard[temp - _size][_fromCol + 1] = SHIP_EDGES;//rightAbove

		/* make all the adjacent elements
		bellow the ship (row+1) equal to -1*/
		if (temp != 9 && _fromCol != 0)
			myBoard[temp + 1][_fromCol - 1] = SHIP_EDGES;//leftBellow
		if (temp != 9)
			myBoard[temp + 1][_fromCol] = SHIP_EDGES;//bellow
		if (temp != 9 && _fromCol != 9)
			myBoard[temp + 1][_fromCol + 1] = SHIP_EDGES;//rightBellow
	}
}

void Board::printShips()
{
	p.printShips();
}

void Board::printBoard(){
	Utils u;
	WORD Attributes = 1;

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
			if (p.getNum() == MY_PLAYER)
			{
				if (myBoard[i][j] == EMPTY || myBoard[i][j] == SHIP_EDGES) cout << "  ";
				if (myBoard[i][j] == SHIP_EXIST) cout << "X ";
				if (myBoard[i][j] == MISS) {
					u.SetConsoleColour(&Attributes, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//white colour
					cout << "  ";
					u.ResetConsoleColour(Attributes);
				}
				if (myBoard[i][j] == HIT) {
					u.SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
					cout << "X ";
					u.ResetConsoleColour(Attributes);
				}
			}
			else {
				if (myBoard[i][j] == EMPTY || myBoard[i][j] == SHIP_EXIST || myBoard[i][j] == SHIP_EDGES) cout << "  ";
				if (myBoard[i][j] == MISS) {
					u.SetConsoleColour(&Attributes, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
					cout << "  ";
					u.ResetConsoleColour(Attributes);
				}
				if (myBoard[i][j] == HIT) {
					u.SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);
					cout << "X ";
					u.ResetConsoleColour(Attributes);
				}
			}
			
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

void Board::play()
{
	int element, row, col;
	bool choosenElement = false;
	if (p.getNum() == OPPONENT) //your turn, updates will be on opponents board
	{
		cout << "Your turn..." << endl 
			<< "Please choose a square to shoot on : ";
	}
	else { // opponent turn, updates will be on your board
		cout << "PC's turn, wait until PC finish his turn..." << endl;
	}

	do // do-while loop checks wether the element alreaady choosed
	{
		if (p.getNum() == OPPONENT)
		{
			if (choosenElement)
				cout << "element already choosed, Please choose other element: " << endl;
			
			cin >> element;
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			element = rand() % 100;// Generate a random number between 0 and 99
			cout << element << endl;
		}
		row = element / 10;
		col = element % 10;

		if (myBoard[row][col] == MISS || myBoard[row][col] == HIT)
		{
			choosenElement = true;
		}
		else {
			choosenElement = false;
		}
	} while (choosenElement);

	if (myBoard[row][col] == SHIP_EXIST)
	{
		myBoard[row][col] = HIT;
		p.UpdateShipDestructionByElement(row, col);
		cout << "HIT :)" << endl;
		
	}
	else if (myBoard[row][col] == SHIP_EDGES)
	{
		myBoard[row][col] = MISS;
		cout << "MISS :(" << endl;
	}
	else if (myBoard[row][col] == EMPTY)
	{
		myBoard[row][col] = MISS;
		cout << "MISS :(" << endl;
	}
}

bool Board::checkGameStatus()
{
	int counter=0;
	for (int i = 0; i < 5; i++)
	{
		if (!p.getShip(i).checkIfLiving(p.getShip(i).isDestruction()))
		{
			counter++;
		}
	}
	if (counter==5)
	{
		return GAME_OVER;
	}
	return GAME_ON;
}
