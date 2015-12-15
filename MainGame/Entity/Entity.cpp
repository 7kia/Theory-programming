
#include <list>

#include "Entity.h"

using namespace sf;
using namespace std;


void entityProtection::init(float cut, float crash, float unlife)
{
	protectionCut = cut;
	protectionCrash = crash;
	protectionUnlife = unlife;
}

void foundObjects::init(Item *item, UnlifeObject *object, Entity *enemy)
{
	emptyItem = item;
	emptyObject = object;
	emptyEntity = enemy;
	findItem = emptyItem;
	findObject = emptyObject;
	findEntity = emptyEntity;
}

void currentCollision::initPos(int xPos, int yPos, int zPos)
{
	x = xPos;
	y = yPos;
	level = zPos;
}

void currentCollision::clear()
{
	initPos(0, 0, 0);
	block = 0;
	idObject = 0;
}


void entityMana::update(const float deltaTime)
{
	timeForMana += deltaTime;

	if (timeForMana > timeUpdateMana) {
		timeForMana = 0;

		if (needMinusMana) {
			currentMana -= delMana;
		} else {
			currentMana += addMana;
		}
	}

	if (currentMana < 1) {
		currentMana = 0;
	} else if (currentMana > maxMana) {
		currentMana = maxMana;
	}
}

void Step::init(float first)
{
	stepFirst = first;
	stepCurrent = stepFirst;
}

void DamageInputAndOutput::init(int cut, int crush, float time, float mult)
{
	cuttingDamage = cut;
	crushingDamage = crush;
	timeOutputDamage = time;
	damageMultiplirer = mult;

	timeInputDamage = 0.f;
}

void entityAnimation::init(float input, float output)
{
	timeAnimation = 0.f;
	timeFightAnimation = output;

	timeOutputDamage = input;
	currentTimeFightAnimation = 0.f;
}

void entityAnimation::updateFight(const float deltaTime, bool &giveDamage, idEntityMode &idMode)
{

		currentTimeFightAnimation += deltaTime;

		if (currentTimeFightAnimation > timeFightAnimation) {
			giveDamage = true;
			idMode = idEntityMode::walk;
			currentTimeFightAnimation = 0;
		}

};

void DamageInputAndOutput::updateInputDamage(const float deltaTime)
{
	if (inputDamage) {
		timeInputDamage += deltaTime;

		if (timeInputDamage > TIME_ATTENTION_SHOW_DAMAGE) {
			timeInputDamage = 0;
			inputDamage = 0;
		}

	}
};

void entityStamina::update(const float deltaTime, Direction directionWalk, Step &step)
{
	timeForStamina += deltaTime;

	if (timeForStamina > timeUpdateStamina) {
		timeForStamina = 0;

		if (needMinusStamina && directionWalk != NONE_DIRECTION) {
			currentStamina -= delStamina;
		} else {
			currentStamina += addStamina;
		}
	}

	if (currentStamina < 1) {
		currentStamina = 0;
		needMinusStamina = false;
		step.stepCurrent = step.stepFirst;// �������� �� ����� ������
	} else if (currentStamina > maxStamina) {
		currentStamina = maxStamina;
	}

};

void entityHealth::update(const float deltaTime, bool &isDeath)
{
	timeForHealth += deltaTime;

	if (timeForHealth > timeUpdateHealth) {
		timeForHealth = 0;

		if (needMinusHealth) {
			currentHealth -= delHealth;
		} else {
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

void entityHungry::update(const float deltaTime, bool &needMinusHealth)
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
	} else {
		needMinusHealth = true;
	}
};

void entityThirst::update(const float deltaTime, bool &needMinusHealth)
{
	timeForThirst += deltaTime;

	if (timeForThirst > timeUpdateThirst) {
		timeForThirst = 0;
		currentThirst--;
	}

	if (currentThirst > maxThirst) {
		currentThirst = maxThirst;
	}

	if (currentThirst > 0) {
		needMinusHealth = false;
	} else {
		needMinusHealth = true;
	}
}

////////////////////////////////////////////////////////////////////
// ������������. ��� �������� � �������
void Entity::update(const float deltaTime)
{

	soundEntity.setPosition(getXPos(), getYPos(), 1.f);

	damage.updateInputDamage(deltaTime);
	mana.update(deltaTime);
	stamina.update(deltaTime, directions.directionWalk, step);
	health.update(deltaTime, isDeath);
	hungry.update(deltaTime, health.needMinusHealth);
	thirst.update(deltaTime, health.needMinusHealth);

	///////////////////////////////////////
	if (currenMode == idEntityMode::walk
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

		if (directions.directionWalk) {
			playAnimationWalk(deltaTime);
		}

	}

	//animation.currentTimeFightAnimation > 0
	if (currenMode == idEntityMode::atack) {
		animation.updateFight(deltaTime, giveDamage, currenMode);

		playAnimationAtack(deltaTime);

	}
}

void Entity::resetAtack()
{
	animation.currentTimeFightAnimation = 0.f;
	currenMode = idEntityMode::walk;
	directions.directionWalk = NONE_DIRECTION;
	giveDamage = false;
}

void Entity::playAnimationWalk(const float deltaTime)
{
	animation.timeAnimation += deltaTime * MULTIPLY_STEP_ANIMATION;
	resetTimeAnimation(animation.timeAnimation, RESET_WALK_ANIMATION);

	int id = idSoundPaths::stepGrass1Sound;
	playSoundAfterTime(animation.timeAnimation, id);

	int shiftWidth = directions.directionLook / NUMBER_FOR_COMPUTE_SHIFT_WALK_ANIMATION;// TODO

	int currentWidth = size.width;
	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);//

	if (shiftWidth) {
		currentWidth *= -1;
	}

	int currentHeight = size.height * int(animation.timeAnimation);
	spriteEntity->setTextureRect(IntRect(xPos, currentHeight, currentWidth, size.height));
}

void Entity::playAnimationAtack(const float deltaTime)
{
	float &timeAnimation = animation.currentTimeFightAnimation;
	int width = size.width;
	int height = size.height;

	timeAnimation += deltaTime;
	resetTimeAnimation(timeAnimation, animation.timeFightAnimation);


	int shiftWidth = directions.directionLook / NUMBER_FOR_COMPUTE_SHIFT_WALK_ANIMATION;// TODO

	int currentWidth = width;

	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);//

	if (shiftWidth) {
		currentWidth *= -1;
	}

	int currentHeight = height * (int(timeAnimation * RESET_ATACK_ANIMATION) + SHIFT_ANIMATION_ATACK);
	spriteEntity->setTextureRect(IntRect(xPos, currentHeight, currentWidth, height));
}

void Entity::playSoundAfterTime(float time, const int idSound)
{
	if (time == soundBase->startSounds[idSound]) {
		Vector2f posPerson = { getXPos(), getYPos() };
		::playSound(idSound, *soundBase, soundEntity, posPerson);
	}
}

void Entity::resetTimeAnimation(float &time, float reset)
{
	if (time > reset) {
		time = 0;
	}
}

void Entity::playAtackSound(Item &currentItem)
{
	Vector2f posPerson = { getXPos(), getYPos() };
	int idSound;
	if (currentItem.typeItem->features.isCutting) {
		idSound = idSoundPaths::metalPunchBody1Sound;
		::playSound(idSound, *soundBase, soundEntity, posPerson);
	}
	else {
		idSound = idSoundPaths::punchBody1Sound;
		::playSound(idSound, *soundBase, soundEntity, posPerson);
	}

}

void Entity::playObjectBreakSound(int idNature)
{
	Vector2f posUse = getPosition();
	switch (idNature) {
	case idNatureObject::woodNature:
		playSound(chopp1Sound, *soundBase, soundEntity, posUse);
		break;
	case idNatureObject::stoneNature:
		playSound(hitStoneSound, *soundBase, soundEntity, posUse);
		break;
	case idNatureObject::sandNature:
		playSound(hitSandSound, *soundBase, soundEntity, posUse);
		break;
	case idNatureObject::groundNature:
		playSound(hitGroundSound, *soundBase, soundEntity, posUse);
		break;
	default:
		break;
	}
}

void Entity::playObjectDropSound(sf::Vector2f pos)
{
	int idSound = idSoundPaths::drop1Sound;
	playSound(idSound, *soundBase, soundEntity, pos);
}



////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// ��������������� �������
float Entity::getXPos()
{
	return spriteEntity->getPosition().x;
}

float Entity::getYPos()
{
	return spriteEntity->getPosition().y;
}

sf::Vector2f Entity::getPosition()
{
	return { getXPos(), getYPos() };
}

void Entity::choiceDirectionLook(int& xShift, int& yShift)
{
	switch (directions.directionLook) {
	case DOWN_LEFT:
		xShift = -1;
		yShift = 1;
		break;
	case DOWN_RIGHT:
		xShift = 1;
		yShift = 1;
		break;
	case UP_LEFT:
		xShift = -1;
		yShift = -1;
		break;
	case UP_RIGHT:
		xShift = 1;
		yShift = -1;
		break;
	case LEFT:
		xShift = -1;
		yShift = 0;
		break;
	case RIGHT:
		xShift = 1;
		yShift = 0;
		break;
	case UP:
		xShift = 0;
		yShift = -1;
		break;
	case DOWN:
		xShift = 0;
		yShift = 1;
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// �������������� � �����
void Entity::interactionWithMap(Field &field, listDestroyObjectsAndBlocks& listDestroy, const float deltaTime)
{

	float &dx(movement.x);
	float &dy(movement.y);

	float x = getXPos();
	float y = getYPos();

	//wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;


	// �������� �� ����� �� �����
	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0))
			&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0))) {
	

		bool isSlowingBlock = false;
		/////////////////////////////////////////////
		// ��������� ���������� �������
		for (int i = y / SIZE_BLOCK; i < (y + size.height) / SIZE_BLOCK; i++) {
			for (int j = x / SIZE_BLOCK; j < (x + size.width) / SIZE_BLOCK; j++) {
				// ����������� �����
				if (isInListBlocks(map[currentLevelFloor + 1][i][j], *listDestroy.slowingBlocks)) {// �������
					step.stepCurrent = step.stepFirst / slowingStep;
					isSlowingBlock = true;
					stamina.needMinusStamina = false;
					break;
				} else if (step.stepCurrent == step.stepFirst / slowingStep) {
					step.stepCurrent = step.stepFirst;
				}



				// ��������� �� ������ ���������� ������
				if (isInListBlocks(map[currentLevelFloor + 1][i][j], *listDestroy.passableBlocks) == false) {
					wasCollision = true;
					collision.initPos(j, i, currentLevelFloor + 1);
					collision.block = map[currentLevelFloor + 1][i][j];

					directions.directionWalk = NONE_DIRECTION;
					break;
				}

			}
		}
		/////////////////////////////////////////////

		/////////////////////////////////////////////
		// ��������� ���

		for (int i = int(y / SIZE_BLOCK); i < int((y + size.height) / SIZE_BLOCK); i++) {
			for (int j = int(x / SIZE_BLOCK); j < int((x + size.width) / SIZE_BLOCK); j++) {


				// ����������� �����
				if (isInListBlocks(map[currentLevelFloor][i][j], *listDestroy.slowingBlocks)) {// �������
					step.stepCurrent = step.stepFirst / slowingStep;
					stamina.needMinusStamina = false;
					break;
				} else if (step.stepCurrent == step.stepFirst / slowingStep && !isSlowingBlock) {
					step.stepCurrent = step.stepFirst;
				}

				// �������� ������������
				if (isInListBlocks(map[currentLevelFloor][i][j], *listDestroy.notPassableFloor)) {

					wasCollision = true;
					collision.initPos(j, i, currentLevelFloor);
					collision.block = map[currentLevelFloor][i][j];

					break;
				}

			}
		}

		/////////////////////////////////////////////
	} else {
<<<<<<< HEAD
		wasCollision = true;
=======
		
		wasCollision = true;
		dx = dy = 0;
		directions.directionWalk = NONE_DIRECTION;
>>>>>>> master
	}


	if (wasCollision) {
		if (map[currentLevelFloor][collision.y][collision.x] == field.charBlocks[idBlocks::air]) {
			currentLevelFloor -= 1;
			x = float(collision.x * SIZE_BLOCK);
			y = float(collision.y * SIZE_BLOCK);
		}

	}

<<<<<<< HEAD
	if(map[currentLevelFloor][collision.y][collision.x] == field.charBlocks[idBlocks::air])
	{
		currentLevelFloor -= 1;
		x = float(collision.x * SIZE_BLOCK);
		y = float(collision.y * SIZE_BLOCK);
	}

	spriteEntity->setPosition(x, y);
	movement = { 0.f, 0.f };
=======
	//spriteEntity->setPosition(x, y);
>>>>>>> master
}


void Entity::interactionWitnUnlifeObject(vector<UnlifeObject> *unlifeObjects, const float deltaTime)// ������� for enity and mainPerson
{
<<<<<<< HEAD
		float dx(movement.x);
		float dy(movement.y);
=======
	if (wasCollision == false) {
		float &dx(movement.x);
		float &dy(movement.y);
>>>>>>> master

		float x;
		float y;
		x = getXPos();
		y = getYPos();
		wasCollision = false;


		Sprite *spriteObject;
		FloatRect objectBound;

		int levelUnlifeObject;
		Sprite *transparentSpiteObject;
		FloatRect objectAltBound;
		FloatRect entityBound;

		vector<UnlifeObject> &objects = *unlifeObjects;
		for (int i = 0; i < objects.size(); i++) {
			levelUnlifeObject = objects[i].currentLevel;

			spriteObject = objects[i].spriteObject;
			objectBound = spriteObject->getGlobalBounds();

			transparentSpiteObject = objects[i].transparentSpiteObject;
			objectAltBound = transparentSpiteObject->getGlobalBounds();
			entityBound = spriteEntity->getGlobalBounds();

			if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				wasCollision = true;

<<<<<<< HEAD
				//founds.init(pos)
=======

>>>>>>> master
				founds.findObject = &objects[i];
				founds.findObjectFromList = i;

				// �������
				TypeUnlifeObject *typeObject = objects[i].typeObject;//typeObject->id != idUnlifeObject::destroyBlockEffect
				if (true) {
					Vector2f posObject = spriteObject->getPosition();

					int heightMain = typeObject->mainSize.size.height;
					int height = typeObject->transparentSize.size.height;

					int xPos = int((posObject.x + SIZE_BLOCK / 2) / SIZE_BLOCK);
					int yPos = int((posObject.y + SIZE_BLOCK / 2) / SIZE_BLOCK);

					founds.currentTarget = { xPos, yPos, objects[i].currentLevel };

				}

				directions.directionWalk = NONE_DIRECTION;
				break;
			}
			else if (entityBound.intersects(objectAltBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				transparentSpiteObject->setColor(TRANSPARENT_COLOR);
			}
			else {
				transparentSpiteObject->setColor(NORMAL_COLOR);
			}

		}
<<<<<<< HEAD
=======

	}

	if (wasCollision == false) {

		if (directions.directionWalk >= Direction::UP_LEFT) {
			movement.x = DIAGONAL_SCALE_SPEED * movement.x * deltaTime;
			movement.y = DIAGONAL_SCALE_SPEED * movement.y * deltaTime;
		}
		else
		{
			movement.x *= deltaTime;
			movement.y *= deltaTime;
		}
		collision.clear();

	}
	else
	{
		movement.x *= -deltaTime;
		movement.y *= -deltaTime;
	}
		
	spriteEntity->move(movement);
	movement = { 0.f, 0.f };
	
>>>>>>> master
}



bool Entity::isEmptySlot()
{
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		if (itemFromPanelQuickAccess[i].typeItem == founds.emptyItem->typeItem) {
			emptySlot = i;
			return true;
		}
	}
	return false;
}


//////////////////////////////////////////////////////
// ����� �������� �������
bool isObject(float x, float y, std::vector<UnlifeObject> &unlifeObjects, UnlifeObject &findObject,
							int &findObjectFromList, int &current, int currentLevel)
{
	int levelObject = unlifeObjects[current].currentLevel;

	Sprite *spriteObject = unlifeObjects[current].spriteObject;
	FloatRect objectBound = spriteObject->getGlobalBounds();

	if (objectBound.contains(x, y) && levelObject == currentLevel) {
		findObject = unlifeObjects[current];
		findObjectFromList = current;
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////
// ����� ��������
bool isItem(float x, float y, vector<Item> &items, Item &findItem, int &findItemFromList, int currentLevel)
{
	int levelItem = items[findItemFromList].currentLevel;

	Sprite *spriteItem = items[findItemFromList].mainSprite;
	FloatRect objectItem = spriteItem->getGlobalBounds();

	if (objectItem.contains(x, y) && levelItem == currentLevel) {
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////

bool Entity::isInUseField(float x, float y, bool under)
{
	int xPosBlock = int(x / SIZE_BLOCK);
	int yPosBlock = int(y / SIZE_BLOCK);

	bool checkX = (((getXPos() + size.width / 2) / SIZE_BLOCK) + radiusUse > xPosBlock)
								&& (((getXPos() + size.width / 2) / SIZE_BLOCK) - (radiusUse + 1) <= xPosBlock);

	bool checkY = (((getYPos() + size.height / 2) / SIZE_BLOCK) + radiusUse > yPosBlock)
								&& (((getYPos() + size.height / 2) / SIZE_BLOCK) - (radiusUse + 1) <= yPosBlock);

	bool checkUnderPerson = xPosBlock == ((int(getXPos()) + SIZE_BLOCK / 2) / SIZE_BLOCK)
													&& yPosBlock == ((int(getYPos()) + SIZE_BLOCK / 2) / SIZE_BLOCK);

	if (checkX && checkY) {
		{
			if (checkUnderPerson && !under) return false;
			return true;
		}
	}

	return false;
}

Vector2i  Entity::isEmptyFloor(Field &field, int Level)
{
	int x = int(getXPos() / SIZE_BLOCK);
	int y = int(getYPos() / SIZE_BLOCK);

	wchar_t *charBlocks = field.charBlocks;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			// ���� ��� ��������� ����� �� ���������
			if (i == 0 && j == 0) {// ���� ���������� ���� �������� �� ���������
				if (isExitFromBorder(x, y) == false && Level != currentLevelFloor) {
					if (map[Level][y][x] != charBlocks[idBlocks::air]) {
						return{ -1, -1 };
					}
				}
			} else {
				if (isExitFromBorder(x + i, y + j) == false) {
					// �������� �����
					if (Level != currentLevelFloor) {
						// ��������� ��� � ����� ��� ���
						if (map[Level][y + j][x + i] != charBlocks[idBlocks::air]
								&& (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::air]
								|| map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder]))// �������
						{
							return{ x + i, y + j };
						}
					} else {// ��������� ���
						if (map[Level][y + j][x + i] == charBlocks[idBlocks::air]
								|| map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder])// �������
						{
							return{ x + i, y + j };
						}
					}
				}
			}
		}

	}
	return{ -1, -1 };
}

bool Entity::isExitFromBorder(int x, int y)
{

	if (((x < WIDTH_MAP) && (x > 0))
			&& (y < (LONG_MAP - 1) && (y > 0))) {
		return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////
void Entity::throwItem(Field &field, vector<Item> &items)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
	if (currentItem.typeItem != founds.emptyItem->typeItem) {
		// ���������� �������


		Item* addItem = new Item;
		*addItem = itemFromPanelQuickAccess[idSelectItem];
		// ����� ������� ������������
		addItem->setPosition(int(getXPos() / SIZE_BLOCK),
												 int(getYPos() / SIZE_BLOCK),
												 currentLevelFloor + 1);
		Vector2f posHero = { getXPos() + size.width / 2, getYPos() + size.height / 2 };// ������ ������� �� � ������ �������
		addItem->mainSprite->setPosition(posHero);
		addItem->mainSprite->scale(scaleOutItems);
		items.push_back(*addItem);
		delete addItem;

		playObjectDropSound(posHero);

		itemFromPanelQuickAccess[idSelectItem] = *founds.emptyItem;
	}
}

void Entity::run()
{
	if (step.stepCurrent > step.stepFirst) {
		step.stepCurrent = step.stepFirst;
		stamina.needMinusStamina = false;
	}
	else {
		step.stepCurrent = step.stepFirst * 3;
		stamina.needMinusStamina = true;
	}
}

////////////////////////////////////////////////////////////////////////////////////
// ����������� ���� ��� ���
bool Entity::isInListBlocks(wchar_t block, vector<wchar_t> &listObjects) {
	if (&listObjects != nullptr) {

		size_t size = listObjects.size();
		if (size) {
			for (size_t i = 0; i < size; i++) {
				if (block == listObjects[i]) {
					return true;
				}
			}
		}

	}
	
	return false;
}

bool Entity::isInListIds(int id, vector<wchar_t> &listIds) {
	if (&listIds != nullptr) {

		size_t size = listIds.size();
		if (size) {
			for (size_t i = 0; i < size; i++) {
				if (id == listIds[i]) {
					return true;
				}
			}
		}

	}

	return false;
}

bool Entity::isInListObjects(vector<int> &listObjects, int id) {
	if(&listObjects != nullptr)
	{
		size_t size = listObjects.size();
		if (size) {
			for (size_t i = 0; i < size; i++) {
				if (id == listObjects[i]) {
					return true;
				}
			}
		}

	}


	return false;
}
////////////////////////////////////////////////////////////////////////////////////

void Entity::choceShiftUseItem(int& shiftX, int& shiftY, bool prickBlow)
{
	float percentTime = 1.f - 2.f * animation.currentTimeFightAnimation / animation.timeFightAnimation;
	shiftX = int(-spriteEntity->getOrigin().x);
	shiftY = int(-spriteEntity->getOrigin().y);


	switch (directions.directionLook) {
	case UP:
		shiftX -= size.width / 4;
		shiftY -= size.width / 3;
		shiftY -= int(size.width / 4 * percentTime);
		break;
	case DOWN:
		shiftX += size.width / 4;
		shiftY += size.width / 3;
		shiftY += int(size.width / 4 * percentTime);
		break;
	case RIGHT:
		shiftX += size.width / 3;
		shiftY -= size.width / 4;
		shiftX -= int(size.width / 4 * percentTime);
		break;
	case LEFT:
		shiftX -= size.width / 3;
		shiftY += size.width / 4;
		shiftX += int(size.width / 4 * percentTime);
		break;
	case UP_RIGHT:
		shiftX = 0;
		shiftY -= size.width / 4;

		shiftX += int(size.width / 4 * percentTime);
		shiftY -= int(size.width / 4 * percentTime);
		break;
	case UP_LEFT:
		shiftX -= size.width / 4;
		shiftY = 0;

		shiftX -= int(size.width / 4 * percentTime);
		shiftY -= int(size.width / 4 * percentTime);
		break;
	case DOWN_RIGHT:
		shiftX += size.width / 4;
		shiftY = 0;

		shiftX += int(size.width / 4 * percentTime);
		shiftY += int(size.width / 4 * percentTime);
		break;
	case DOWN_LEFT:
		shiftX = 0;
		shiftY += size.width / 3;

		shiftX -= int(size.width / 4 * percentTime);
		shiftY += int(size.width / 4 * percentTime);
		break;
	default:
		break;

	}
}

void Entity::renderCurrentItem(sf::RenderWindow& window)
{

	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
	bool isEmptyItem = currentItem.typeItem->features.name == founds.emptyItem->typeItem->features.name;
	if (!isEmptyItem) {
		Sprite& spriteItem = *currentItem.mainSprite;


		bool condition = directions.directionLook < DOWN_LEFT;
		bool condition2 = directions.directionLook != UP_LEFT;
		int shiftAngle = shiftAngleUseItem * (condition && condition2) + !condition * 4;

		int shiftX;
		int shiftY;

		// TODO ANIMATION
		bool prickBlow = rand() % 2 == 1;
		choceShiftUseItem(shiftX, shiftY, prickBlow);



		Vector2f pos = { getXPos() + size.width / 2 + shiftX,
			getYPos() + size.width / 2 + shiftY };
		spriteItem.setOrigin(0, 0);
		spriteItem.setRotation(45.f * (directions.directionLook - shiftAngle));
		spriteItem.setScale(scaleUseItems);

		spriteItem.setPosition(pos);
		window.draw(spriteItem);


		spriteItem.setRotation(0);
		spriteItem.setScale(normalSize);
		spriteItem.setOrigin(SIZE_ITEM / 2, SIZE_ITEM / 2);
	}
}
