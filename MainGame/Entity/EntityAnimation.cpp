#include "Entity.h"


void entityAnimation::init(float input , float output)
{
	timeAnimation = 0.f;
	timeFightAnimation = output;

	timeOutputDamage = input;
	currentTimeFightAnimation = 0.f;
}

void entityAnimation::updateFight(const float deltaTime , bool &giveDamage , idEntityMode &idMode)
{
	currentTimeFightAnimation += deltaTime;

	if (currentTimeFightAnimation > timeFightAnimation) {
		giveDamage = true;
		idMode = idEntityMode::walk;
		currentTimeFightAnimation = 0;
	}
};

void Entity::playAnimationWalk(const float deltaTime)
{
	if (directions.directionWalk) {
		directions.directionLook = directions.directionWalk;
		animation.timeAnimation += deltaTime * MULTIPLY_STEP_ANIMATION;
		resetTimeAnimation(animation.timeAnimation , float(RESET_WALK_ANIMATION));

		int id = idSoundPaths::stepGrass1Sound;
		playSoundAfterTime(animation.timeAnimation , id);
	}
	int shiftWidth = directions.directionLook / NUMBER_FOR_COMPUTE_SHIFT_WALK_ANIMATION;// TODO

	sizeSprite &size = type->featuresSprite.size;
	int currentWidth = size.width;
	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);

	if (shiftWidth) {
		currentWidth *= -1;
	}

	int height = size.height;
	int currentHeight = height * int(animation.timeAnimation);
	spriteEntity->setTextureRect(IntRect(xPos , currentHeight , currentWidth , height));
}

void Entity::playAnimationAtack(const float deltaTime)
{
	float &timeAnimation = animation.currentTimeFightAnimation;
	sizeSprite &size = type->featuresSprite.size;
	int width = size.width;
	int height = size.height;

	timeAnimation += deltaTime;
	resetTimeAnimation(timeAnimation , animation.timeFightAnimation);
	if (timeAnimation == 0.f) {
		giveDamage = true;
	}

	int shiftWidth = directions.directionLook / NUMBER_FOR_COMPUTE_SHIFT_WALK_ANIMATION;// TODO

	int currentWidth = width;

	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);

	if (shiftWidth) {
		currentWidth *= -1;
	}

	int currentHeight = height * (int(timeAnimation * RESET_ATACK_ANIMATION) + SHIFT_ANIMATION_ATACK);
	spriteEntity->setTextureRect(IntRect(xPos , currentHeight , currentWidth , height));
}

void Entity::playSoundAfterTime(float time , const int idSound)
{
	if (time == soundBase->startSounds[idSound]) {
		Vector2f posPerson = { getXPos(), getYPos() };
		::playSound(idSound , *soundBase , soundEntity , posPerson);
	}
}

void Entity::resetTimeAnimation(float &time , float reset)
{
	if (time > reset) {
		time = 0;
	}
}
