
#include <list>

#include "Entity.h"
#include "Font.h"

using namespace sf;
using namespace std;


void entityProtection::init(float cut, float crash)
{
	protectionCut = cut;
	protectionCrash = crash;
}

void foundObjects::init(Item *item, UnlifeObject *object)
{
	emptyItem = item;
	emptyObject = object;
	findItem = emptyItem;
	findObject = emptyObject;
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

void entityAnimation::updateFight(const float deltaTime, bool &giveDamage)
{

		currentTimeFightAnimation += deltaTime;

		if (currentTimeFightAnimation > timeFightAnimation) {
			giveDamage = true;
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
		step.stepCurrent = step.stepFirst;// Персонаж не может бегать
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
};

////////////////////////////////////////////////////////////////////
// Передвижение. Его анимация и озвучка
void Entity::update(const float deltaTime, dataSound &databaseSound)
{

	/*
	if (outputDamage) {
	currentTimeFightAnimation += deltaTime;
	if (currentTimeFightAnimation > timeOutputDamage) {
	currentTimeFightAnimation = 0;

	outputDamage = 0;
	}
	}
	*/
	if (currenMode == idEntityMode::atack) {
		animation.updateFight(deltaTime, giveDamage);
	}
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
			playAnimationWalk(deltaTime, databaseSound);
		}

	}


	if (animation.currentTimeFightAnimation > 0) {
		playAnimationAtack(deltaTime, databaseSound);

	}
}

void Entity::playAnimationWalk(const float deltaTime, dataSound& databaseSound)
{
	float pauseStep = 5, resetAnimation = 4;

	//playSound(animation.timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

	animation.timeAnimation += deltaTime * pauseStep;
	resetTimeAnimation(animation.timeAnimation, resetAnimation);
	playSound(animation.timeAnimation, databaseSound.startSounds[idSoundEntity::stepGrass], idSoundEntity::stepGrass);

	int shiftWidth = directions.directionLook / 6;// TODO

	int currentWidth = size.width;
	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);//

	if (shiftWidth) {
		currentWidth *= -1;
	}

	spriteEntity->setTextureRect(IntRect(xPos, size.height * int(animation.timeAnimation), currentWidth, size.height));
}

void Entity::playAnimationAtack(const float deltaTime, dataSound& databaseSound)
{
	float pauseStep = 5, resetAnimation = 3;
	int shiftAnimation = 4;


	animation.timeAnimation += deltaTime * pauseStep;
	resetTimeAnimation(animation.timeAnimation, resetAnimation);

	int shiftWidth = directions.directionLook / 6;// TODO

	int currentWidth = size.width;
	int xPos = currentWidth * (directions.directionLook - 1 - shiftWidth * 3);//

	if (shiftWidth) {
		currentWidth *= -1;
	}

	spriteEntity->setTextureRect(IntRect(xPos, size.height * (int(animation.currentTimeFightAnimation * resetAnimation) + shiftAnimation),
															 currentWidth, size.height));
}

void Entity::playSound(float time, float &start, const int idSound)
{
	if (time == start) {
		soundsEntity[idSound]->play();
		soundsEntity[idSound]->setPosition(getXPos(), getYPos(), 0);
	}
}

void Entity::resetTimeAnimation(float &time, float &reset)
{
	if (time > reset) {
		time = 0;
	}
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Вспомагательные функции
float Entity::getXPos()
{
	return spriteEntity->getPosition().x;
}

float Entity::getYPos()
{
	return spriteEntity->getPosition().y;
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
// Взаимодейтсвие с миром
void Entity::interactionWithMap(Field &field, listDestroyObjectsAndBlocks& listDestroy, const float deltaTime)
{

	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;

	wasCollision = false;

	if (directions.directionWalk >= Direction::UP_LEFT) {
		// Чтобы скорость по диагонали была равной скорости по вертикали и горизонтали
		x = getXPos() + DIAGONAL_SCALE_SPEED * dx * deltaTime;
		y = getYPos() + DIAGONAL_SCALE_SPEED * dy * deltaTime;
	} else {
		x = getXPos() + dx * deltaTime;
		y = getYPos() + dy * deltaTime;
	}

	wchar_t *charBlocks = field.charBlocks;
		wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;


	// Проверка на выход за карту
	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0))
			&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0))) {
	

		bool isSlowingBlock = false;
		/////////////////////////////////////////////
		// Проверяем окружающие объекты
		for (int i = y / SIZE_BLOCK; i < (y + size.height) / SIZE_BLOCK; i++) {
			for (int j = x / SIZE_BLOCK; j < (x + size.width) / SIZE_BLOCK; j++) {
				// Замедляющие блоки
				if (wcschr(listDestroy.slowingBlocks, map[currentLevelFloor + 1][i][j])) {// ИСПРАВЬ
					step.stepCurrent = step.stepFirst / slowingStep;
					isSlowingBlock = true;
					stamina.needMinusStamina = false;
					break;
				} else if (step.stepCurrent == step.stepFirst / slowingStep) {
					step.stepCurrent = step.stepFirst;
				}



				// Проверяем по списку проходимых блоков
				if (wcschr(listDestroy.passableBlocks, map[currentLevelFloor + 1][i][j]) == 0) {
					x = getXPos();
					y = getYPos();
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
		// Проверяем пол

		for (int i = y / SIZE_BLOCK; i < (y + size.height) / SIZE_BLOCK; i++) {
			for (int j = x / SIZE_BLOCK; j < (x + size.width) / SIZE_BLOCK; j++) {


				// Замедляющие блоки
				if (wcschr(listDestroy.slowingBlocks, map[currentLevelFloor][i][j])) {// ИСПРАВЬ
					step.stepCurrent = step.stepFirst / slowingStep;
					stamina.needMinusStamina = false;
					break;
				} else if (step.stepCurrent == step.stepFirst / slowingStep && !isSlowingBlock) {
					step.stepCurrent = step.stepFirst;
				}

				// Является непроходимым
				if (wcschr(listDestroy.notPassableFloor, map[currentLevelFloor][i][j]) != NULL) {
					x = getXPos();
					y = getYPos();
					wasCollision = true;

					collision.initPos(j, i, currentLevelFloor);
					collision.block = map[currentLevelFloor][i][j];

					directions.directionWalk = NONE_DIRECTION;
					break;
				}

			}
		}

		/////////////////////////////////////////////
	} else {
		x = getXPos();
		y = getYPos();
		wasCollision = true;
		directions.directionWalk = NONE_DIRECTION;
	}

	if(wasCollision == false)
	{
		collision.clear();
	}

	if(map[currentLevelFloor][collision.y][collision.x] == field.charBlocks[idBlocks::air])
	{
		currentLevelFloor -= 1;
		x = collision.x * SIZE_BLOCK;
		y = collision.y * SIZE_BLOCK;
	}

	spriteEntity->setPosition(x, y);
}


void Entity::interactionWitnUnlifeObject(vector<UnlifeObject> *unlifeObjects, const float deltaTime)// ИСПРАВЬ for enity and mainPerson
{
	float dx(movement.x);
	float dy(movement.y);

	float x;
	float y;
	x = getXPos();
	y = getYPos();

	wasCollision = false;

	// Проверка на выход за карту
	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x >  0))
			&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y >  0))) {
		Sprite *spriteObject;
		FloatRect objectBound;

		int levelUnlifeObject;
		Sprite *transparentSpiteObject;
		FloatRect objectAltBound;
		FloatRect entityBound;

		vector<UnlifeObject> &objects = *unlifeObjects;
		for (int i = 0; i != objects.size(); ++i) {
			levelUnlifeObject = objects[i].currentLevel;

			spriteObject = objects[i].spriteObject;
			objectBound = spriteObject->getGlobalBounds();

			transparentSpiteObject = objects[i].transparentSpiteObject;
			objectAltBound = transparentSpiteObject->getGlobalBounds();
			entityBound = spriteEntity->getGlobalBounds();

			if (entityBound.intersects(objectBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				if (directions.directionWalk >= Direction::UP_LEFT) {
					// Чтобы скорость по диагонали была равной скорости по вертикали и горизонтали
					x -= DIAGONAL_SCALE_SPEED * dx * deltaTime;
					y -= DIAGONAL_SCALE_SPEED * dy * deltaTime;
				} else {
					x -= dx * deltaTime;
					y -= dy * deltaTime;
				}
				wasCollision = true;
				directions.directionWalk = NONE_DIRECTION;
				break;
			} else if (entityBound.intersects(objectAltBound) && (levelUnlifeObject == currentLevelFloor + 1)) {
				transparentSpiteObject->setColor(TRANSPARENT_COLOR);
			} else {
				transparentSpiteObject->setColor(NORMAL_COLOR);
			}

		}
	} else {
		wasCollision = true;
		x = int(getXPos());
		y = int(getYPos());
	}

	spriteEntity->setPosition(x, y);
	movement = { 0.f, 0.f };
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
// Поиск неживого объекта
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
// Поиск предмета
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
	int xPosBlock = x / SIZE_BLOCK;
	int yPosBlock = y / SIZE_BLOCK;

	bool checkX = (((getXPos() + size.width / 2) / SIZE_BLOCK) + radiusUse > xPosBlock)
		&& (((getXPos() + size.width / 2) / SIZE_BLOCK) - (radiusUse + 1) <= xPosBlock);

	bool checkY = (((getYPos() + size.height / 2) / SIZE_BLOCK) + radiusUse > yPosBlock)
		&& (((getYPos() + size.height / 2) / SIZE_BLOCK) - (radiusUse + 1) <= yPosBlock);

	bool checkUnderPerson = xPosBlock == (((int)getXPos() + SIZE_BLOCK / 2) / SIZE_BLOCK)
		&& yPosBlock == (((int)getYPos() + SIZE_BLOCK / 2) / SIZE_BLOCK);

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
	int x = getXPos() / SIZE_BLOCK;
	int y = getYPos() / SIZE_BLOCK;

	wchar_t *charBlocks = field.charBlocks;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			// Если над лестницей стена не переходим
			if (i == 0 && j == 0) {// Если спускаемся блок лестницы не проверяем
				if (isExitFromBorder(x, y) == false && Level != currentLevelFloor) {
					if (map[Level][y][x] != charBlocks[idBlocks::air]) {
						return{ -1, -1 };
					}
				}
			} else {
				if (isExitFromBorder(x + i, y + j) == false) {
					// Проверка стены
					if (Level != currentLevelFloor) {
						// Проверяем пол и стену над ним
						if (map[Level][y + j][x + i] != charBlocks[idBlocks::air]
								&& (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::air]
								|| map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder]))// ИСПРАВЬ
						{
							return{ x + i, y + j };
						}
					} else {// Проверяем пол
						if (map[Level][y + j][x + i] == charBlocks[idBlocks::air]
								|| map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder])// ИСПРАВЬ
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

	if (((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0))
			&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0))) {
		return false;
	}
	return true;
}
////////////////////////////////////////////////////////////////////
void Entity::throwItem(Field &field, vector<Item> &items)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
	if (currentItem.typeItem != founds.emptyItem->typeItem) {
		// Определяем позицию


		Item* addItem = new Item;
		*addItem = itemFromPanelQuickAccess[idSelectItem];
		// Задаём уровень расположения
		addItem->setPosition(getXPos() / SIZE_BLOCK, getYPos() / SIZE_BLOCK, currentLevelFloor + 1);
		Vector2f posHero = { getXPos() + size.width / 2, getYPos() + size.height / 2 };// Начало отсчёта не в центре спрайта
		addItem->mainSprite->setPosition(posHero);
		addItem->mainSprite->scale(scaleOutItems);
		items.push_back(*addItem);
		delete addItem;

		itemFromPanelQuickAccess[idSelectItem] = *founds.emptyItem;
	}
}

////////////////////////////////////////////////////////////////////////////////////
// Разрушаемый блок или нет
bool Entity::isInListBlocks(wchar_t block, wchar_t *listBlocks) {
	if (listBlocks) {
		int i = 0;
		while (listBlocks[i] != u'\0') {
			if (listBlocks[i] == block) {
				return true;
			}
			i++;
		}
	}
	
	return false;
}
bool Entity::isInListObjects(String* listObjects, int sizeString) {
	if(listObjects)
	{
			for (size_t i = 0; i < sizeString; i++) {
		if (founds.findObject->typeObject->name == listObjects[i]) {
			return true;
		}
	}
	}


	return false;
}
////////////////////////////////////////////////////////////////////////////////////

void Entity::initStepSounds(dataSound & databaseSound)
{
	soundsEntity.push_back(&databaseSound.sounds[idSoundEntity::stepGrass]);
	soundsEntity.push_back(&databaseSound.sounds[idSoundEntity::stepStone]);
}

void Entity::choceShiftUseItem(int& shiftX, int& shiftY, bool prickBlow)
{
	float percentTime = 1.f - 2.f * animation.currentTimeFightAnimation / animation.timeFightAnimation;
	shiftX = -spriteEntity->getOrigin().x;
	shiftY = -spriteEntity->getOrigin().y;


	switch (directions.directionLook) {
	case UP:
		shiftX -= size.width / 4;
		shiftY -= size.width / 3;
		shiftY -= size.width / 4 * percentTime;
		break;
	case DOWN:
		shiftX += size.width / 4;
		shiftY += size.width / 3;
		shiftY += size.width / 4 * percentTime;
		break;
	case RIGHT:
		shiftX += size.width / 3;
		shiftY -= size.width / 4;
		shiftX -= size.width / 4 * percentTime;
		break;
	case LEFT:
		shiftX -= size.width / 3;
		shiftY += size.width / 4;
		shiftX += size.width / 4 * percentTime;
		break;
	case UP_RIGHT:
		shiftX = 0;
		shiftY -= size.width / 4;

		shiftX += size.width / 4 * percentTime;
		shiftY -= size.width / 4 * percentTime;
		break;
	case UP_LEFT:
		shiftX -= size.width / 4;
		shiftY = 0;

		shiftX -= size.width / 4 * percentTime;
		shiftY -= size.width / 4 * percentTime;
		break;
	case DOWN_RIGHT:
		shiftX += size.width / 4;
		shiftY = 0;

		shiftX += size.width / 4 * percentTime;
		shiftY += size.width / 4 * percentTime;
		break;
	case DOWN_LEFT:
		shiftX = 0;
		shiftY += size.width / 3;

		shiftX -= size.width / 4 * percentTime;
		shiftY += size.width / 4 * percentTime;
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
		// TODO
		int shiftX;
		int shiftY;

		bool prickBlow = rand() % 2;
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
