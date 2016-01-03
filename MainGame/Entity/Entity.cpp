#include "Entity.h"

using namespace sf;
using namespace std;


void entityProtection::init(float cut, float crash, float unlife)
{
	protectionCut = cut;
	protectionCrash = crash;
	protectionUnlife = unlife;
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

void Entity::playAtackSound(Item &currentItem)
{
	Vector2f posPerson = { getXPos(), getYPos() };
	int idSound;
	if (currentItem.typeItem->features.isCutting) {
		idSound = idSoundPaths::metalPunchBody1Sound;
		::playSound(idSound , *soundBase , soundEntity , posPerson);
	}
	else {
		idSound = idSoundPaths::punchBody1Sound;
		::playSound(idSound , *soundBase , soundEntity , posPerson);
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

int Entity::getXPosOnMap()
{
	return int(getXPos() / SIZE_BLOCK);
}

int Entity::getYPosOnMap()
{
	return int(getYPos() / SIZE_BLOCK);
}

sf::Vector2i Entity::getMapPosition()
{
	return sf::Vector2i(getXPosOnMap() , getYPosOnMap());
}

float Entity::getAbsolutXPos()
{
	return getXPos() + (SIZE_BLOCK / 2);
}

float Entity::getAbsolutYPos()
{
	return getYPos() + (SIZE_BLOCK / 2);
}

sf::Vector2f Entity::getAbsolutPosition()
{
	return sf::Vector2f(getAbsolutXPos(), getAbsolutYPos());
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

Item & Entity::getFindItem()
{
	return *founds.findItem;
}

UnlifeObject & Entity::getFindUnlifeObject()
{
	return *founds.findObject;
}

Entity & Entity::getFindEntity()
{
	return *founds.findEnemy;
}

Item * Entity::getRefOnEmptyItem()
{
	return founds.emptyItem;
}

UnlifeObject* Entity::getRefOnEmptyUnlifeObject()
{
	return founds.emptyObject;
}

Entity* Entity::getRefOnEmptyEntity()
{
	return founds.emptyEnemy;
}

int Entity::getIdFindItem()
{
	return founds.findItemFromList;
}

int Entity::getIdFindUnlifeObject()
{
	return founds.findObjectFromList;
}

int Entity::getIdFindEntity()
{
	return founds.findEnemyFromList;
}

const TypeEnemy* Entity::getType()
{
	return type;
}

const sizeSprite& Entity::getSize()
{
	return getType()->featuresSprite.size;
}

int Entity::getWidth()
{
	return getSize().width;
}

int Entity::getHeight()
{
	return getSize().height;
}

int Entity::getRadiuseUse()
{
	return getType()->view.radiusUse;
}

bool Entity::isEmptySlot()
{
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		if (itemsEntity[i].getType() == getRefOnEmptyItem()->getType()) {
			emptySlot = i;
			return true;
		}
	}
	return false;
}

bool Entity::isInUseField(Vector2f pos, bool under)
{
	// TODO : CurrentPosition
	Vector2i posBlock = inMapCoordinate(pos);

	int radiusUse = getRadiuseUse();
	Vector2i absolutePosition = inMapCoordinate(getAbsolutPosition());
	bool checkX = ( (absolutePosition.x + radiusUse ) > posBlock.x)
								&& (absolutePosition.x - (radiusUse + 1) <= posBlock.x);

	bool checkY = ((absolutePosition.y + radiusUse)> posBlock.y)
		&& (absolutePosition.y - (radiusUse + 1) <= posBlock.y);

	bool checkUnderPerson = (posBlock.x == absolutePosition.x)
		&& (posBlock.y == absolutePosition.y);//((int(getYPos()) + SIZE_BLOCK / 2) / SIZE_BLOCK);

	if (checkX && checkY) {
		{
			if (checkUnderPerson && !under) return false;
			return true;
		}
	}

	return false;
}

bool Entity::isExitFromBorder(int x, int y)
{

	if (((x < WIDTH_MAP) && (x > 0))
			&& (y < (LONG_MAP - 1) && (y > 0))) {
		return false;
	}
	return true;
}

bool Entity::isExitFromBorder(float x , float y)
{

	if ((x < (SIZE_BLOCK * WIDTH_MAP)) && (x > 0)
		&& (y < (SIZE_BLOCK * (LONG_MAP - 1)) && (y > 0))) {
		return false;
	}
	return true;
}

Vector2i  Entity::isEmptyFloor(Field &field, int Level)
{
	Vector2i posOnMap = getMapPosition();
	int x = posOnMap.x;
	int y = posOnMap.y;

	wchar_t *charBlocks = field.charBlocks;
	wchar_t(*map)[LONG_MAP][WIDTH_MAP] = field.dataMap;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			// Если над лестницей стена не переходим
			if ((i == 0) && (j == 0)) {// Если спускаемся блок лестницы не проверяем
				if (!isExitFromBorder(x, y) && (Level != currentLevelFloor)) {
					if (map[Level][y][x] != charBlocks[idBlocks::air]) {
						return{ -1, -1 };
					}
				}
			} 
			else {
				if (isExitFromBorder(x + i, y + j) == false) {
					// Проверка стены
					bool goUp = Level != currentLevelFloor;
					if (goUp) {
						bool checkFloor = (map[Level][y + j][x + i] == charBlocks[idBlocks::air]);
						bool checkWall = (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::air])
													|| (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder]);
						if (checkFloor && checkWall)
						{
							return{ x + i, y + j };
						}
					}
					else {// Проверяем пол
						if ((map[Level][y + j][x + i] == charBlocks[idBlocks::air])
								|| (map[Level + 1][y + j][x + i] == charBlocks[idBlocks::woodLadder]))
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

////////////////////////////////////////////////////////////////////
void Entity::throwItem(Field &field, vector<Item> &items)
{
	Item& currentItem = itemsEntity[idSelectItem];
	if (currentItem.typeItem != founds.emptyItem->typeItem) {
		// Определяем позицию


		Item* addItem = new Item;
		*addItem = itemsEntity[idSelectItem];
		// Задаём уровень расположения
		Vector3i posItem = { getXPosOnMap(),
												 getYPosOnMap(),
												 currentLevelFloor + 1 };
		addItem->setPosition(posItem);

		sizeSprite &size = type->featuresSprite.size;
		Vector2f posHero = { getXPos() + size.width / 2, getYPos() + size.height / 2 };// Начало отсчёта не в центре спрайта
		addItem->mainSprite->setPosition(posHero);
		addItem->mainSprite->scale(scaleOutItems);
		items.push_back(*addItem);
		delete addItem;

		playObjectDropSound(posHero);

		itemsEntity[idSelectItem] = *founds.emptyItem;
	}
}

void Entity::run()
{
	float &stepCurrent = step.stepCurrent;
	float &stepFirst = step.stepFirst;

	if (stepCurrent > stepFirst) {
		stepCurrent = stepFirst;
		stamina.needMinusStamina = false;
	}
	else {
		stepCurrent = stepFirst * 3;
		stamina.needMinusStamina = true;
	}
}

bool Entity::isInListBlocks(vector<wchar_t> &listObjects , wchar_t block) {
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

void Entity::renderCurrentItem(sf::RenderWindow& window)
{

	Item& currentItem = itemsEntity[idSelectItem];
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


		sizeSprite &size = type->featuresSprite.size;

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

void Entity::choceShiftUseItem(int& shiftX , int& shiftY , bool prickBlow)
{
	float percentTime = 1.f - 2.f * animation.currentTimeFightAnimation / animation.timeFightAnimation;
	shiftX = int(-spriteEntity->getOrigin().x);
	shiftY = int(-spriteEntity->getOrigin().y);

	sizeSprite &size = type->featuresSprite.size;

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

