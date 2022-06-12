#pragma once

class AiShipHit {
private:
	bool shipHit = false;
	bool firstHit = true;
	int hitRow;
	int	hitCol;
	int position;
	int hitDirection;
	int hitCount = 2; //this variable equals to 2 because we use it after the ship already hitten twice
public:

	void setShipHit(bool _shipHit);
	void setFirstHit(bool _firstHit);
	void setHitRow(int _hitRow);
	void setHitCol(int _hitCol);
	void setPosition(int _position);
	void setHitDirection(int _direction);
	void setHitCount(int _hitCount);

	bool isShipHit();
	bool isFirstHit();
	int getHitRow();
	int getHitCol();
	int getPosition();
	int getHitDirection();
	int getHitCount();
};