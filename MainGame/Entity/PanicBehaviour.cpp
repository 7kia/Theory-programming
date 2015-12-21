#include "Entity.h"

void Entity::entityStandPanic(Vector2f &movemoment)
{
	bool canPanic = type->converse.canPanic;
	currenMode = idEntityMode::panic;
	if (canPanic) {
		movemoment = { -movemoment.x, -movemoment.y };
		choiceDirections(movemoment);

		animation.currentTimeFightAnimation = 0.f;

		step.stepCurrent = step.stepFirst * 2;
		stamina.needMinusStamina = true;
	}
}
