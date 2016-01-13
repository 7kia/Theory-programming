#include "Entity.h"


void Entity::update(const float deltaTime)
{

	soundEntity.setPosition(getXPos() , getYPos() , 1.f);

	damage.updateInputDamage(deltaTime);
	mana.update(deltaTime);
	stamina.update(deltaTime , directions.directionWalk , step);
	health.update(deltaTime , isDeath);
	hungry.update(deltaTime , health.needMinusHealth);

	if (currenMode == idEntityMode::walk
			|| currenMode == idEntityMode::fight
			|| currenMode == idEntityMode::panic) {
		switch (directions.directionWalk) {
		case UP_LEFT:
			directions.directionLook = UP_LEFT;
			movement.y = -step.stepCurrent;
			movement.x = -step.stepCurrent;
			break;
		case UP_RIGHT:
			directions.directionLook = UP_RIGHT;
			movement.y = -step.stepCurrent;
			movement.x = step.stepCurrent;
			break;
		case UP:
			directions.directionLook = UP;
			movement.y = -step.stepCurrent;
			break;
		case DOWN_LEFT:
			directions.directionLook = DOWN_LEFT;
			movement.y = step.stepCurrent;
			movement.x = -step.stepCurrent;
			break;
		case DOWN_RIGHT:
			directions.directionLook = DOWN_RIGHT;
			movement.y = step.stepCurrent;
			movement.x = step.stepCurrent;
			break;
		case DOWN:
			directions.directionLook = DOWN;
			movement.y = step.stepCurrent;
			break;
		case LEFT:
			directions.directionLook = LEFT;
			movement.x = -step.stepCurrent;
			break;
		case RIGHT:
			directions.directionLook = RIGHT;
			movement.x = step.stepCurrent;
			break;
		case NONE_DIRECTION:
			movement.x = 0;
			movement.y = 0;
			break;
		default:
			break;
		}

		if (directions.directionWalk >= Direction::UP_LEFT) {
			movement.x *= DIAGONAL_SCALE_SPEED * deltaTime;
			movement.y *= DIAGONAL_SCALE_SPEED * deltaTime;
		}
		else {
			movement.x *= deltaTime;
			movement.y *= deltaTime;
		}

		updateDirectionLook();
		playAnimationWalk(deltaTime);

	}

	if (currenMode == idEntityMode::atack) {
		animation.updateFight(deltaTime , giveDamage , currenMode);
		playAnimationAtack(deltaTime);
	}
}

void Entity::updateDirectionLook()
{
	if (rotation >= (NUMBER_DEGREES + SHIFT_CIRCLE_LOOK)
			|| rotation <= (EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = UP;
	}
	else if (rotation >= (1 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)
					 && rotation <= (2 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = UP_LEFT;
	}
	else if (rotation >= (2 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)
					 && rotation <= (3 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = LEFT;
	}
	else if (rotation >= (3 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)
					 && rotation <= (4 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = DOWN_LEFT;
	}
	else if (rotation >= (4 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)
					 && rotation <= (5 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = DOWN;
	}
	else if (rotation >= (5 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)
					 && rotation <= (6 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = DOWN_RIGHT;
	}
	else if (rotation >= (6 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)
					 && rotation <= (7 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = RIGHT;
	}
	else if (rotation >= (7 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)
					 && rotation <= (8 * EIGHTH_PART_CIRCLE + SHIFT_CIRCLE_LOOK)) {
		directions.directionLook = UP_RIGHT;
	}

}

void entityMana::update(const float deltaTime)
{
	timeForMana += deltaTime;

	if (timeForMana > timeUpdateMana) {
		timeForMana = 0;

		if (needMinusMana) {
			currentMana -= delMana;
		}
		else {
			currentMana += addMana;
		}
	}

	if (currentMana < 1) {
		currentMana = 0;
	}
	else if (currentMana > maxMana) {
		currentMana = maxMana;
	}
}

void entityStamina::update(const float deltaTime , Direction directionWalk , Step &step)
{
	timeForStamina += deltaTime;

	if (timeForStamina > timeUpdateStamina) {
		timeForStamina = 0;

		if (needMinusStamina && directionWalk != NONE_DIRECTION) {
			currentStamina -= delStamina;
		}
		else {
			currentStamina += addStamina;
		}
	}

	if (currentStamina < 1) {
		currentStamina = 0;
		needMinusStamina = false;
		step.stepCurrent = step.stepFirst;
	}
	else if (currentStamina > maxStamina) {
		currentStamina = maxStamina;
	}

};

void entityHealth::update(const float deltaTime , bool &isDeath)
{
	timeForHealth += deltaTime;

	if (timeForHealth > timeUpdateHealth) {
		timeForHealth = 0;

		if (needMinusHealth) {
			currentHealth -= delHealth;
		}
		else {
			currentHealth += addHealth;
		}
	}

	if (currentHealth < 1) {
		isDeath = true;
		currentHealth = 0;
	}
	else if (currentHealth > maxHealth) {
		currentHealth = maxHealth;
	}

};

void entityHungry::update(const float deltaTime , bool &needMinusHealth)
{
	timeForHungry += deltaTime;

	if (timeForHungry > timeUpdateHungry) {
		timeForHungry = 0;
		currentHungry--;
	}

	if (currentHungry > maxHungry) {
		currentHungry = maxHungry;
	}

	if (currentHungry > 0) {
		needMinusHealth = false;
	}
	else {
		needMinusHealth = true;
	}
};

void Entity::resetAtack()
{
	animation.currentTimeFightAnimation = 0.f;
	currenMode = idEntityMode::walk;
	directions.directionWalk = NONE_DIRECTION;
	giveDamage = false;
}

void Entity::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	sizeSprite &size = type->featuresSprite.size;
	float dX = pos.x - spriteEntity->getPosition().x - size.width / 2;
	float dY = pos.y - spriteEntity->getPosition().y - size.height / 2;
	rotation = (atan2(dX , dY)) * 180 / PI - 180;

	directions.directionToTarget = Math::getNormalVector(sf::Vector2f(dX, dY));
	if (rotation < 0) {
		rotation += 360;
	}
}

void Entity::getCoordinateForView(Vector2f position , View &view)
{
	view.setCenter(position);
}