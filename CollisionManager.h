#pragma once

#include <math.h>

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	bool squareCollision(double x1, double x2, double y1, double y2, double box1, double box2);
	double distanceBetweenPoints(double x1, double x2, double y1, double y2);
	bool insideAnotherObject(double placeX, double placeY, double objX, double objY, double objBox);
	bool totalCollision(double x1, double x2, double y1, double y2, double box1, double box2);
};