#include "Player.h"


Player::Player(){
}

void Player::setShip(int i, int _id,
    int _size, bool _position,
    int _fromRow, int _fromCol,
    int _toRow, int _toCol, bool _living){
    ships[i].setId(_id);
    ships[i].setSize(_size);
    ships[i].setPosition(_position);
    ships[i].setPlace(_size, _position, _fromRow, _fromCol, _toRow, _toCol);
    ships[i].setLiving(_living);
    ships[i].setChoosed(false);
    ships[i].setDestruction(_size);
}

void Player::setShips(){
    setShip(0, 1, 5, HORIZONTAL, -1, -1, -1, -1, true);
    setShip(1, 2, 4, HORIZONTAL, -1, -1, -1, -1, true);
    setShip(2, 3, 3, HORIZONTAL, -1, -1, -1, -1, true);
    setShip(3, 4, 3, HORIZONTAL, -1, -1, -1, -1, true);
    setShip(4, 5, 2, HORIZONTAL, -1, -1, -1, -1, true);
}

void Player::setNum(int _num){
    num = _num;
}

Ship & Player::getShip(int i){
    return ships[i];
}

Ship* Player::getShips() {
    return ships;
}

Ship& Player::getShipByElement(int row, int col)
{
    int size, position, fromRow, toRow, fromCol, toCol;
    for (int i = 0; i < 5; i++)
    {
        size = getShip(i).getSize();
        position = getShip(i).getPosition();
        fromRow = getShip(i).getFromRow();
        toRow = getShip(i).getToRow();
        fromCol = getShip(i).getFromCol();
        toCol = getShip(i).getToCol();

        if (position == HORIZONTAL && toCol > fromCol) {/* check ship horizintaly from left to right*/
            for (int j = 0; j < size; j++)
            {
                if (fromRow == row && fromCol+j == col)
                {
                    return getShip(i);
                }
            }
        }
        else if (position == HORIZONTAL && fromCol > toCol)/* check ship horizintaly from right to left*/
        {
            for (int j = 0; j < size; j++)
            {
                if (fromRow == row && fromCol - j == col)
                {
                    return getShip(i);
                }
            }
        }
        else if (position == VERTICAL && toRow > fromRow) {/* check ship verticaly from up to down*/
            for (int j = 0; j < size; j++)
            {
                if (fromRow + j == row && fromCol == col)
                {
                    return getShip(i);
                }
            }
        }
        else if (position == VERTICAL && fromRow > toRow)/* check ship verticaly from down to up*/
        {
            for (int j = 0; j < size; j++)
            {
                if (fromRow - j == row && fromCol == col)
                {
                    return getShip(i);
                }
            }
        }
    }
}

void Player::UpdateShipDestructionByElement(int row, int col)
{
    int size, position, fromRow, toRow, fromCol, toCol;
    for (int i = 0; i < 5; i++)
    {
        size = getShip(i).getSize();
        position = getShip(i).getPosition();
        fromRow = getShip(i).getFromRow();
        toRow = getShip(i).getToRow();
        fromCol = getShip(i).getFromCol();
        toCol = getShip(i).getToCol();

        if (position == HORIZONTAL && toCol > fromCol) {/* check ship horizintaly from left to right*/
            for (int j = 0; j < size; j++)
            {
                if (fromRow == row && fromCol + j == col)
                {
                    getShip(i).updateDestruction(j);
                }
            }
        }
        else if (position == HORIZONTAL && fromCol > toCol)/* check ship horizintaly from right to left*/
        {
            for (int j = 0; j < size; j++)
            {
                if (fromRow == row && fromCol - j == col)
                {
                    getShip(i).updateDestruction(j);
                }
            }
        }
        else if (position == VERTICAL && toRow > fromRow) {/* check ship verticaly from up to down*/
            for (int j = 0; j < size; j++)
            {
                if (fromRow + j == row && fromCol == col)
                {
                    getShip(i).updateDestruction(j);
                }
            }
        }
        else if (position == VERTICAL && fromRow > toRow)/* check ship verticaly from down to up*/
        {
            for (int j = 0; j < size; j++)
            {
                if (fromRow - j == row && fromCol == col)
                {
                    getShip(i).updateDestruction(j);
                }
            }
        }
    }
}

int Player::getNum()
{
    return num;
}

void Player::printShips(){
    for (int i = 0; i < 5; i++)
    {
        ships[i] = getShip(i);
        cout << ships[i].getId() << ": ship size: " << ships[i].getSize() 
            << (ships[i].isChoosed() ? "(choosed)" : "") << endl;
    }
}

int Player::getShipSize(int pickedShip)
{
    return getShip(pickedShip).getSize();
}


