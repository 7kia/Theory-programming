#include "Entity.h"

void Entity::entityStandPanic(Vector2f &movement)
{
	bool canPanic = type->converse.canPanic;
	currenMode = idEntityMode::panic;
	if (canPanic) {
		movement = { -movement.x, -movement.y };
		choiceDirections(movement);

		animation.currentTimeFightAnimation = 0.f;

		step.stepCurrent = step.stepFirst * 2;
		stamina.needMinusStamina = true;
	}
}
