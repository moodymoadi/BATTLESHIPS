#include "Player.h"

Player::Player(){
    /*default constructor*/
}

void Player::setShip(int i, int _id,
    int _size, bool _position,
    int _fromRow, int _fromCol,
    int _toRow, int _toCol, bool _living){
    ships[i].setId(_id);
    ships[i].setSize(_size);
    ships[i].setPosition(_position);
    ships[i].setPlace(_fromRow, _fromCol, _toRow, _toCol);
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

Ship & Player::getShip(int i){
    return ships[i];
}

Ship* Player::getShips() {
    return ships;
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


