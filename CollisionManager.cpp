#include "CollisionManager.h"
#include <iostream>

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::squareCollision(double x1, double x2, double y1, double y2, double box1, double box2)
{
	if(x1 - box1 >= x2 - box2 && x1 + box1 <= x2 + box2 && y1 - box1 >= y2 - box2 && y1 + box1 <= y2 + box2)
	{
		return true;
	}
	else if(x2 - box2 >= x1 - box1 && x2 + box2 <= x1 + box1 && y2 - box2 >= y1 - box1 && y2 + box2 <= y1 + box1)
	{
		return true;
	}
	return false;
}

double CollisionManager::distanceBetweenPoints(double x1, double x2, double y1, double y2)
{
	double square = pow(x2 - x1, 2) + pow(y2 - y1, 2);
	square = sqrt(square);
	return square;
}

bool CollisionManager::insideAnotherObject(double placeX, double placeY, double objX, double objY, double objBox)
{
	if(placeX >= objX - objBox && placeX <= objX + objY && placeY >= objY - objBox && placeY <= objY + objBox)
	{
		return true;
	}
	return false;
}

bool CollisionManager::totalCollision(double x1, double x2, double y1, double y2, double box1, double box2)
{
	double total = pow((x2 - x2), 2) + pow((y2 - y1), 2);
	if(sqrt(total) <= box1 + box2)
	{
		return true;
	}
	return false;
}