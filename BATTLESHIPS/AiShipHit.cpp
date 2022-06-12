#include "AiShipHit.h"

void AiShipHit::setShipHit(bool _shipHit)
{
    shipHit = _shipHit;
}

void AiShipHit::setFirstHit(bool _firstHit)
{
    firstHit = _firstHit;
}

void AiShipHit::setHitRow(int _hitRow)
{
    hitRow = _hitRow;
}

void AiShipHit::setHitCol(int _hitCol)
{
    hitCol = _hitCol;
}

void AiShipHit::setPosition(int _position)
{
    position = _position;
}

void AiShipHit::setHitDirection(int _direction)
{
    hitDirection = _direction;
}

void AiShipHit::setHitCount(int _hitCount)
{
    hitCount = _hitCount;
}

bool AiShipHit::isShipHit()
{
    return shipHit;
}

bool AiShipHit::isFirstHit()
{
    return firstHit;
}

int AiShipHit::getHitRow()
{
    return hitRow;
}

int AiShipHit::getHitCol()
{
    return hitCol;
}

int AiShipHit::getPosition()
{
    return position;
}

int AiShipHit::getHitDirection()
{
    return hitDirection;
}

int AiShipHit::getHitCount()
{
    return hitCount;
}
