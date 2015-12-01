#include "Animation.h"

using namespace sf;
using namespace std;

void blockConstuction::firstStep(float deltaTime)
{
	anisochronousRotate();
	updateColors(deltaTime);
}

void blockConstuction::secondStep(float deltaTime)
{
	float &timeMove = variablesSecond.timeMove;
	float timeUpdateDirection = variablesSecond.timeUpdateDirection;
	Vector2f &direction = variablesSecond.direction;
	vector<Vector2f> &directions = variablesSecond.directions;
	bool &zoomPlus = variablesSecond.zoomPlus;
	int &idDirection = variablesSecond.idDirection;

	timeMove += deltaTime;
	if(timeMove < timeUpdateDirection)
	{
		scaleConstruction();
		block[0].move(direction);
	}
	else
	{
		timeMove = 0.f;
		idDirection++;
		
		if(idDirection >= directions.size())
		{
			doFirstStep = false;
			doSecondStep = false;

			variablesSecond.reset();

		}
		else {
			direction = directions[idDirection];
			zoomPlus = !zoomPlus;
		}

	}
}

void blockConstuction::thirdStep()
{
	resetColorBlocks();
}