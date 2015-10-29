#include "MyMath.h"

using namespace sf;

float distansePoints(Vector2f firstPoint, Vector2f secondPoint)
{
	return sqrt( (firstPoint.x - secondPoint.x) * (firstPoint.x - secondPoint.x)// ÈÑÏÐÀÂÜ
							+ (firstPoint.y - secondPoint.y) * (firstPoint.y - secondPoint.y));
}

Vector2f vectorDirection(Vector2f firstPoint, Vector2f secondPoint)
{
	return { (secondPoint.x - firstPoint.x) ,/// distansePoints(firstPoint, secondPoint)
		(secondPoint.y - firstPoint.y) };
}
