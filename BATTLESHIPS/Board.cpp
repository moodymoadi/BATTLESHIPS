
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
					addToBoard(randPosition, size, fromRow, fromCol, toRow, toCol,SHIP_EXIST, SHIP_EDGES);
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
to the elements that the ship is located in and -1 to all the adjacent elements*/
void Board::addToBoard(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol, int _shipElems,
	int _adjElems){

	/* add ship to the board horizintaly from left to right*/
	if (_position == HORIZONTAL && _toCol > _fromCol) {
		addFromLeftToRight(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol, _shipElems, _adjElems);
	}

	/* add ship to the board horizintaly from right to left*/
	else if (_position == HORIZONTAL && _fromCol > _toCol)
	{
		addFromRightToLeft(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol, _shipElems, _adjElems);
	}

	/* add ship to the board verticaly from up to down*/
	else if (_position == VERTICAL && _toRow > _fromRow) {
		addFromUpToDown(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol, _shipElems, _adjElems);
	}

	/* add ship to the board verticaly from down to up*/
	else if (_position == VERTICAL && _fromRow > _toRow)
	{
		addFromDownToUp(_position, _size,
			_fromRow, _fromCol,
			_toRow, _toCol, _shipElems, _adjElems);
	}
	
}

void Board::addFromLeftToRight(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol, int _shipElems, int adjElems) {
	int temp = _fromCol;

	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		/*this makes the elements of the ship equal to 1*/
		myBoard[_fromRow][_fromCol++] = _shipElems;//the ship

		//todo -- put out side of the parent loop
		/* make all the adjacent elements
		from bellow and above the ship (row-1 and row+1) equal to -1 */
		for (int i = 0; i < _size; i++)
		{
			if (_fromRow != 9)
				myBoard[_fromRow + 1][temp + i] = adjElems;
			if (_fromRow != 0)
				myBoard[_fromRow - 1][temp + i] = adjElems;
		}

		/* make all the adjacent elements
		from left to the ship (col-1) equal to -1 */
		if (temp != 0 && _fromRow != 0)
			myBoard[_fromRow - 1][temp - 1] = adjElems;//aboveLeft
		if (temp != 0)
			myBoard[_fromRow][temp - 1] = adjElems;//left
		if (temp != 0 && _fromRow != 9)
			myBoard[_fromRow + 1][temp - 1] = adjElems;//bellowLeft

		/* make all the adjacent elements
		from right to the ship (col+size) equal to -1 */
		if (temp + _size != 10 && _fromRow != 0)
			myBoard[_fromRow - 1][temp + _size] = adjElems;//aboveRight
		if (temp + _size != 10)
			myBoard[_fromRow][temp + _size] = adjElems;//right
		if (temp + _size != 10 && _fromRow != 9)
			myBoard[_fromRow + 1][temp + _size] = adjElems;//bellowRight
	}
}

void Board::addFromRightToLeft(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol, int _shipElems, int adjElems) {
	int temp = _fromCol;

	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		/*this makes the elements of the ship equal to 1*/
		myBoard[_fromRow][_fromCol--] = _shipElems;// the ship

		//todo -- put out side of the parent loop
		/* make all the adjacent elements
		from bellow and above the ship (row-1 and row+1) equal to -1 */
		for (int i = 0; i < _size; i++)
		{
			if (_fromRow != 9)
				myBoard[_fromRow + 1][temp - i] = adjElems;
			if (_fromRow != 0)
				myBoard[_fromRow - 1][temp - i] = adjElems;
		}

		/* make all the adjacent elements
		from left to the ship (col-size) equal to -1*/
		if (temp - _size != -1 && _fromRow != 0)
			myBoard[_fromRow - 1][temp - _size] = adjElems;//aboveLeft
		if (temp - _size != -1)
			myBoard[_fromRow][temp - _size] = adjElems;//left
		if (temp - _size != -1 && _fromRow != 9)
			myBoard[_fromRow + 1][temp - _size] = adjElems;//bellowLeft

		/* make all the adjacent elements
		from right to the ship (col+1) equal to -1 */
		if (temp != 9 && _fromRow != 0)
			myBoard[_fromRow - 1][temp + 1] = adjElems;//aboveRight
		if (temp != 9)
			myBoard[_fromRow][temp + 1] = adjElems;//right
		if (temp != 9 && _fromRow != 9)
			myBoard[_fromRow + 1][temp + 1] = adjElems;//bellowRight
	}
}

void Board::addFromUpToDown(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol, int _shipElems, int adjElems) {
	int temp = _fromRow;

	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		myBoard[_fromRow++][_fromCol] = _shipElems;// the ship

		//todo -- put out side of the parent loop
		/* make all the adjacent elements
		from right and left the ship (col-1 and col+1) equal to -1 */
		for (int i = 0; i < _size; i++)
		{
			if (_fromCol != 9)
				myBoard[temp + i][_fromCol + 1] = adjElems;
			if (_fromCol != 0)
				myBoard[temp + i][_fromCol - 1] = adjElems;
		}

		/* make all the adjacent elements
		above to the ship (row-1) equal to -1 */
		if (temp != 0 && _fromCol != 0)
			myBoard[temp - 1][_fromCol - 1] = adjElems;//leftAbove
		if (temp != 0)
			myBoard[temp - 1][_fromCol] = adjElems;//above
		if (temp != 0 && _fromCol != 9)
			myBoard[temp - 1][_fromCol + 1] = adjElems;//rightAbove

		/* make all the adjacent elements
		bellow the ship (row+size) equal to -1*/
		if (temp + _size != 10 && _fromCol != 0)
			myBoard[temp + _size][_fromCol - 1] = adjElems;//leftBellow
		if (temp + _size != 10)
			myBoard[temp + _size][_fromCol] = adjElems;//bellow
		if (temp + _size != 10 && _fromCol != 9)
			myBoard[temp + _size][_fromCol + 1] = adjElems;//rightBellow
	}
}

void Board::addFromDownToUp(int _position, int _size,
	int _fromRow, int _fromCol,
	int _toRow, int _toCol, int _shipElems, int adjElems) {
	int temp = _fromRow;
	/*make all the adjacent elements to the ship equal to -1*/
	for (int i = 0; i < _size; i++)
	{
		myBoard[_fromRow--][_fromCol] = _shipElems;// the ship
		for (int i = 0; i < _size; i++)
		{
			if (_fromCol != 9)
				myBoard[temp - i][_fromCol + 1] = adjElems;
			if (_fromCol != 0)
				myBoard[temp - i][_fromCol - 1] = adjElems;
		}

		//todo -- put outside
		/* make all the adjacent elements
		above to the ship (row-size) equal to -1 */
		if (temp - _size != -1 && _fromCol != 0)
			myBoard[temp - _size][_fromCol - 1] = adjElems;//leftAbove
		if (temp - _size != -1)
			myBoard[temp - _size][_fromCol] = adjElems;//above
		if (temp - _size != -1 && _fromCol != 9)
			myBoard[temp - _size][_fromCol + 1] = adjElems;//rightAbove

		/* make all the adjacent elements
		bellow the ship (row+1) equal to -1*/
		if (temp != 9 && _fromCol != 0)
			myBoard[temp + 1][_fromCol - 1] = adjElems;//leftBellow
		if (temp != 9)
			myBoard[temp + 1][_fromCol] = adjElems;//bellow
		if (temp != 9 && _fromCol != 9)
			myBoard[temp + 1][_fromCol + 1] = adjElems;//rightBellow
	}
}

void Board::printShips()
{
	p.printShips();
}

void Board::printBoard(){
	Utils u;
	WORD Attributes = 1;
	Ship sh;

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
					u.SetConsoleColour(&Attributes, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//set white background
					cout << "  ";
					u.ResetConsoleColour(Attributes);//reset color
				}
				if (myBoard[i][j] == HIT) {
					sh = p.getShipByElement(i, j);
					if (!sh.isLiving()) {
						u.SetConsoleColour(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_RED);//set red background
						cout << "X ";
						u.ResetConsoleColour(Attributes);//reset color 
					}
					else {
						u.SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);//set red forground
						cout << "X ";
						u.ResetConsoleColour(Attributes);//reset color 
					}
				}
				if (myBoard[i][j] == HIT_EDGES)
				{
					u.SetConsoleColour(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_RED);//set red color background
					cout << "  ";
					u.ResetConsoleColour(Attributes);//reset color 
				}
			}
			else {
				if (myBoard[i][j] == EMPTY || myBoard[i][j] == SHIP_EXIST || myBoard[i][j] == SHIP_EDGES) cout << "  ";
				if (myBoard[i][j] == MISS) {
					u.SetConsoleColour(&Attributes, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);//set white color background
					cout << "  ";
					u.ResetConsoleColour(Attributes);//reset color
				}
				if (myBoard[i][j] == HIT) {
					sh = p.getShipByElement(i, j);
					if (!sh.isLiving()) {
						u.SetConsoleColour(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_RED);//set red color background
						cout << "X ";
						u.ResetConsoleColour(Attributes);//reset color 
					}
					else {
						u.SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED);//set red color forground
						cout << "X ";
						u.ResetConsoleColour(Attributes);//reset color 
					}
				}if (myBoard[i][j] == HIT_EDGES)
				{
					u.SetConsoleColour(&Attributes, BACKGROUND_INTENSITY | BACKGROUND_RED);//set red color background
					cout << "  ";
					u.ResetConsoleColour(Attributes);//reset color 
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

// print board for development tests
void Board::printBoardTest() {
	Utils u;
	WORD Attributes = 1;
	Ship sh;

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
			cout << myBoard[i][j] << " ";
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
	try
	{
		int element, row, col;
		bool choosenElement = false;
		if (p.getNum() == OPPONENT) //your turn, updates will be on opponent's board
		{
			cout << "Your turn..." << endl
				<< "Please choose a square to shoot on : ";
		}
		else { // opponent's turn, updates will be on your board
			cout << "PC's turn, wait until PC finish his turn..." << endl;
		}

		do // do-while loop checks wether the board's element already choosed 
		{
			if (p.getNum() == OPPONENT)//your turn
			{
				if (choosenElement)
					cout << "Please choose other element: " << endl;

				cin >> element;
				while (element < 0 || element > 99) {
					cout << "please choose between 00 to 99" << endl;
					cin >> element;
				}
			}
			else {//opponent's turn
				if (p.getAiShipHit().isShipHit())
				{
					AiKeepHitUntilShipDestroyed(p.getAiShipHit().getHitRow(), p.getAiShipHit().getHitCol());
					return;
				}
				else {
					element = rand() % 100;// Generate a random number between 0 and 99
				}
			}
			row = element / 10;
			col = element % 10;

			if (myBoard[row][col] == MISS || myBoard[row][col] == HIT || myBoard[row][col] == HIT_EDGES)
			{
				choosenElement = true;
			}
			else {
				choosenElement = false;
				cout << element << endl;
			}
		} while (choosenElement);

		if (myBoard[row][col] == SHIP_EXIST)
		{
			myBoard[row][col] = HIT;
			Ship sh = p.UpdateShipDestructionByElement(row, col);
			if (!sh.isLiving())
				addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
					sh.getFromCol(), sh.getToRow(), sh.getToCol(), HIT, HIT_EDGES);
			if (p.getNum() == MY_PLAYER) {
				p.getAiShipHit().setHitRow(row);
				p.getAiShipHit().setHitCol(col);
				p.getAiShipHit().setShipHit(true);
			}
			cout << "HIT :)" << endl;
			PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
		}
		else if (myBoard[row][col] == SHIP_EDGES)
		{
			myBoard[row][col] = MISS;
			cout << "MISS :(" << endl;
			PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
		}
		else if (myBoard[row][col] == EMPTY)
		{
			myBoard[row][col] = MISS;
			cout << "MISS :(" << endl;
			PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	catch (const std::exception& e)
	{
		cout << "exception accourd: " << e.what();
	}
	
}

//this function keeps the computer shoot the hitten ship untill it destroyes
void Board::AiKeepHitUntilShipDestroyed(int _hitRow, int _hitCol)
{
	int ran;
	bool hitOtherElement = true;

	do// do-while to check if computer hit irelevant element, like ship-edges element or if something went wrong
	{
		if (p.getAiShipHit().isFirstHit()) {
			p.getAiShipHit().setHitCount(2);
			// Generate a random number between 0 and 3,
			//this random number decides where the computer continue shooting after first hit
			ran = rand() % 4;
			switch (ran) {
			case 0://right element
				if (_hitCol + 1 != 10)
				{
					if (myBoard[_hitRow][_hitCol + 1] == HIT_EDGES || 
						myBoard[_hitRow][_hitCol + 1] == MISS)
						hitOtherElement = true;
					else if (myBoard[_hitRow][_hitCol + 1] == SHIP_EXIST) {
						cout << ((_hitRow * 10) + (_hitCol + 1)) << endl;//prints the element number
						myBoard[_hitRow][_hitCol + 1] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow, _hitCol+1);
						if (sh.isLiving()) {
							p.getAiShipHit().setFirstHit(false);
							p.getAiShipHit().setPosition(HORIZONTAL);
							p.getAiShipHit().setHitDirection(RIGHT_DIRECTION);
							PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						}
						else {
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						hitOtherElement = false;
						cout << "hit :)" << endl;
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
					}
					else if (myBoard[_hitRow][_hitCol + 1] == EMPTY ||
						myBoard[_hitRow][_hitCol + 1] == SHIP_EDGES) {
						cout << ((_hitRow * 10) + (_hitCol + 1)) << endl;//prints the element number
						myBoard[_hitRow][_hitCol + 1] = MISS;
						hitOtherElement = false;
						cout << "miss :(" << endl;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
					}
				}
				break;
			case 1://left element
				if (_hitCol - 1 != -1)
				{
					if (myBoard[_hitRow][_hitCol - 1] == HIT_EDGES ||
						myBoard[_hitRow][_hitCol - 1] == MISS)
						hitOtherElement = true;
					else if (myBoard[_hitRow][_hitCol - 1] == SHIP_EXIST) {
						cout << ((_hitRow * 10) + (_hitCol - 1)) << endl;
						myBoard[_hitRow][_hitCol - 1] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow, _hitCol-1);
						if (sh.isLiving()) {
							p.getAiShipHit().setFirstHit(false);
							p.getAiShipHit().setPosition(HORIZONTAL);
							p.getAiShipHit().setHitDirection(LEFT_DIRECTION);
						}
						else {
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						cout << "hit :)" << endl;
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						hitOtherElement = false;
					}
					else if (myBoard[_hitRow][_hitCol - 1] == EMPTY ||
						myBoard[_hitRow][_hitCol - 1] == SHIP_EDGES) {
						cout << ((_hitRow * 10) + (_hitCol - 1)) << endl;
						myBoard[_hitRow][_hitCol - 1] = MISS;
						cout << "miss :(" << endl;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
						hitOtherElement = false;
					}
				}
				break;
			case 2:// above element
				if (_hitRow - 1 != -1)
				{
					if (myBoard[_hitRow - 1][_hitCol] == HIT_EDGES ||
						myBoard[_hitRow - 1][_hitCol] == MISS)
						hitOtherElement = true;
					else if (myBoard[_hitRow - 1][_hitCol] == SHIP_EXIST) {
						cout << (((_hitRow - 1) * 10) + _hitCol) << endl;
						myBoard[_hitRow - 1][_hitCol] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow - 1, _hitCol);
						if (sh.isLiving()) {
							p.getAiShipHit().setFirstHit(false);
							p.getAiShipHit().setPosition(VERTICAL);
							p.getAiShipHit().setHitDirection(ABOVE_DIRECTION);
						}
						else {
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						cout << "hit :)" << endl;
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						hitOtherElement = false;
					}
					else if (myBoard[_hitRow - 1][_hitCol] == EMPTY ||
						myBoard[_hitRow - 1][_hitCol] == SHIP_EDGES) {
						cout << (((_hitRow - 1) * 10) + _hitCol) << endl;
						myBoard[_hitRow - 1][_hitCol] = MISS;
						cout << "miss :(" << endl;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
						hitOtherElement = false;
					}
				}
				break;
			case 3://bellow element
				if (_hitRow + 1 != 10)
				{
					if (myBoard[_hitRow + 1][_hitCol] == HIT_EDGES ||
						myBoard[_hitRow + 1][_hitCol] == MISS)
						hitOtherElement = true;
					else if (myBoard[_hitRow + 1][_hitCol] == SHIP_EXIST) {
						cout << (((_hitRow + 1) * 10) + _hitCol) << endl;
						myBoard[_hitRow + 1][_hitCol] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow + 1, _hitCol);
						if (sh.isLiving()) {
							p.getAiShipHit().setFirstHit(false);
							p.getAiShipHit().setPosition(VERTICAL);
							p.getAiShipHit().setHitDirection(BELLOW_DIRECTION);
						}
						else {
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						cout << "hit :)" << endl;
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						hitOtherElement = false;
					}
					else if (myBoard[_hitRow + 1][_hitCol] == EMPTY || 
								myBoard[_hitRow + 1][_hitCol] == SHIP_EDGES) {
						cout << (((_hitRow + 1) * 10) + _hitCol) << endl;
						myBoard[_hitRow + 1][_hitCol] = MISS;
						cout << "miss :(" << endl;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
						hitOtherElement = false;
					}
				}
				break;
			default://none of the above cases
				hitOtherElement = true;
				break;
			}
		}else {
			int hitCount = p.getAiShipHit().getHitCount();
			switch (p.getAiShipHit().getHitDirection())
			{
			case LEFT_DIRECTION:
				cout << "left, hit count: " << hitCount << endl;
				if (_hitCol - hitCount != -1) {
					if (myBoard[_hitRow][_hitCol - hitCount] == HIT_EDGES ||
						myBoard[_hitRow][_hitCol - hitCount] == MISS) {
						p.getAiShipHit().setHitDirection(RIGHT_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = true;
					}
					else if (myBoard[_hitRow][_hitCol - hitCount] == SHIP_EXIST) {
						cout << ((_hitRow * 10) + (_hitCol - hitCount)) << endl;
						cout << "hit :)" << endl;
						myBoard[_hitRow][_hitCol - hitCount] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow, _hitCol - hitCount);
						p.getAiShipHit().setHitCount(hitCount + 1);
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						if (!sh.isLiving())
						{
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						hitOtherElement = false;
					}
					else if (myBoard[_hitRow][_hitCol - hitCount] == EMPTY ||
						myBoard[_hitRow][_hitCol - hitCount] == SHIP_EDGES) {
						cout << ((_hitRow * 10) + (_hitCol - hitCount)) << endl;
						cout << "miss :(" << endl;
						myBoard[_hitRow][_hitCol - hitCount] = MISS;
						p.getAiShipHit().setHitDirection(RIGHT_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = false;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
					}
				}
				else {
					p.getAiShipHit().setHitDirection(RIGHT_DIRECTION);
					p.getAiShipHit().setHitCount(1);
					hitOtherElement = true;
				}
				break;
			case RIGHT_DIRECTION:
				cout << "right, hit count: " << hitCount << endl;
				if (_hitCol + hitCount != 10) {
					if (myBoard[_hitRow][_hitCol + hitCount] == HIT_EDGES ||
						myBoard[_hitRow][_hitCol + hitCount] == MISS) {
						p.getAiShipHit().setHitDirection(LEFT_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = true;
					}
					else if (myBoard[_hitRow][_hitCol + hitCount] == SHIP_EXIST) {
						cout << ((_hitRow * 10) + (_hitCol + hitCount)) << endl;//prints the element number
						cout << "hit :)" << endl;
						myBoard[_hitRow][_hitCol + hitCount] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow, _hitCol + hitCount);
						p.getAiShipHit().setHitCount(hitCount + 1);
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						if (!sh.isLiving())
						{
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						hitOtherElement = false;
					}
					else if (myBoard[_hitRow][_hitCol + hitCount] == EMPTY ||
						myBoard[_hitRow][_hitCol + hitCount] == SHIP_EDGES) {
						cout << ((_hitRow * 10) + (_hitCol + hitCount)) << endl;
						cout << "miss :(" << endl;
						myBoard[_hitRow][_hitCol + hitCount] = MISS;
						p.getAiShipHit().setHitDirection(LEFT_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = false;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
					}
				}
				else {
					p.getAiShipHit().setHitDirection(LEFT_DIRECTION);
					p.getAiShipHit().setHitCount(1);
					hitOtherElement = true;
				}
				break;
			case ABOVE_DIRECTION:
				cout << "up, hit count: " << hitCount << endl;
				if (_hitRow - hitCount != -1) {
					if (myBoard[_hitRow - hitCount][_hitCol] == HIT_EDGES ||
						myBoard[_hitRow - hitCount][_hitCol] == MISS)
					{
						p.getAiShipHit().setHitDirection(BELLOW_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = true;
					}
					else if (myBoard[_hitRow - hitCount][_hitCol] == SHIP_EXIST) {
						cout << (((_hitRow - hitCount) * 10) + _hitCol) << endl;
						cout << "hit :)" << endl;
						myBoard[_hitRow - hitCount][_hitCol] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow - hitCount, _hitCol);
						p.getAiShipHit().setHitCount(hitCount + 1);
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						if (!sh.isLiving())
						{
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						hitOtherElement = false;
					}
					else if (myBoard[_hitRow - hitCount][_hitCol] == EMPTY ||
						myBoard[_hitRow - hitCount][_hitCol] == SHIP_EDGES) {
						cout << (((_hitRow - hitCount) * 10) + _hitCol) << endl;
						cout << "miss :(" << endl;
						myBoard[_hitRow - hitCount][_hitCol] = MISS;
						p.getAiShipHit().setHitDirection(BELLOW_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = false;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
					}
				}
				else {
					p.getAiShipHit().setHitDirection(BELLOW_DIRECTION);
					p.getAiShipHit().setHitCount(1);
					hitOtherElement = true;
				}
				break;
			case BELLOW_DIRECTION:
				cout << "down, hit count: " << hitCount << endl;
				if (_hitRow + hitCount != 10) {
					if (myBoard[_hitRow + hitCount][_hitCol] == HIT_EDGES ||
						myBoard[_hitRow + hitCount][_hitCol] == MISS)
					{
						p.getAiShipHit().setHitDirection(ABOVE_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = true;
					}
					else if (myBoard[_hitRow + hitCount][_hitCol] == SHIP_EXIST) {
						cout << (((_hitRow + hitCount) * 10) + _hitCol) << endl;
						cout << "hit :)" << endl;
						myBoard[_hitRow + hitCount][_hitCol] = HIT;
						Ship sh = p.UpdateShipDestructionByElement(_hitRow + hitCount, _hitCol);
						p.getAiShipHit().setHitCount(hitCount + 1);
						PlaySound(TEXT("bomb-02.wav"), NULL, SND_SYNC);
						if (!sh.isLiving())
						{
							p.getAiShipHit().setShipHit(false);
							p.getAiShipHit().setFirstHit(true);
							addToBoard(sh.getPosition(), sh.getSize(), sh.getFromRow(),
								sh.getFromCol(), sh.getToRow(), sh.getToCol(),
								HIT, HIT_EDGES);
						}
						hitOtherElement = false;
					}
					else if (myBoard[_hitRow + hitCount][_hitCol] == EMPTY ||
						myBoard[_hitRow + hitCount][_hitCol] == SHIP_EDGES) {
						cout << (((_hitRow + hitCount) * 10) + _hitCol) << endl;
						cout << "miss :(" << endl;
						myBoard[_hitRow + hitCount][_hitCol] = MISS;
						p.getAiShipHit().setHitDirection(ABOVE_DIRECTION);
						p.getAiShipHit().setHitCount(1);
						hitOtherElement = false;
						PlaySound(TEXT("splash.wav"), NULL, SND_SYNC);
					}
				}
				else {
					p.getAiShipHit().setHitDirection(ABOVE_DIRECTION);
					p.getAiShipHit().setHitCount(1);
					hitOtherElement = true;
				}
				break;
			default:
				hitOtherElement = true;
				cout << "something went wrong, no direction to hit" << endl;
				break;
			}
		}
	} while (hitOtherElement);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

// this function responsible for deciding wether the game ends or continues
// by checking ships destruction
// if there are ships alive game continue, if all ships destroyed then game-over
//game-over = false
//game-on = true
bool Board::checkGameStatus()
{
	int counter = 0;
	for (int i = 0; i < 5; i++)
	{
		if (!getShip(i).checkIfLiving(getShip(i).getDestruction()))
		{
			counter++;
		}
	}
	if (counter == 5)
	{
		system("cls");
		/*if (p.getNum() == MY_PLAYER)
		{
			cout << "pc win";
		}
		else {
			cout << "you win";
		}*/
		return GAME_OVER;
	}
	return GAME_ON;
}


