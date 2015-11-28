#include "Animation.h"

void blockConstuction::firstStep(float &deltaTime)
{
	rotateRelativeBlock(idOriginBlock);

	if (int(block[0].getRotation()) % 180 == 0) {
		idOriginBlock++;
		if (idOriginBlock >= AMOUNT_BLOCKS) {
			idOriginBlock = 0;
		}
	}

	updateColors(deltaTime);
}

void blockConstuction::secondStep(float& deltaTime)
{
	timeMove += deltaTime;
	if(timeMove < timeUpdateDirection)
	{
		block[0].move(direction);
		if(zoomPlus)
		{
			currentScale += SCALE;		}
		else {
			currentScale -= SCALE;
		}
		block[0].setScale(currentScale, currentScale);

	}
	else
	{
		timeMove = 0.f;
		
		
		if(idDirection > directions.size() - 1)
		{
			countCircle = 0;
			conditionFirstStep = true;
		}
		else
		{
			direction = directions[idDirection];
			zoomPlus = !zoomPlus;
		}
		idDirection++;

	}
}