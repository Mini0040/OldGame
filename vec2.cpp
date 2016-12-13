#include "vec2.h"

vec2 vec2::operator= (vec2 objPosition)
{
	vec2 Temp;
	Temp.xPos = objPosition.xPos;
	Temp.yPos = objPosition.yPos;
	Temp.boxRadius = objPosition.boxRadius;
	return Temp;
}

vec2 vec2::operator= (int objPosition)
{
	vec2 Temp;
	Temp.xPos = objPosition;
	Temp.yPos = objPosition;
	Temp.boxRadius = objPosition;
	return Temp;
}