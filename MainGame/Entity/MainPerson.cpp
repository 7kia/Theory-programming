#include "MainPerson.h"

using namespace sf;
using namespace std;

void world::initializePlayer(View &view , Listener &listener)
{
	mainPerson = &Enemys[ID_PLAYER_IN_LIST];

	float posX = float(CENTER_WORLD.x * SIZE_BLOCK);
	float posY = float(CENTER_WORLD.y * SIZE_BLOCK);
	view.setSize(float(DEFAULT_WIDTH_WINDOW), float(DEFAULT_HEIGHT_WINDOW));
	view.setCenter(posX, posY);

	listener.setUpVector(0.f, 1.f, 0.f);
	listener.setGlobalVolume(100.f);
}

void Entity::updateView(View &view , Listener &listener , RenderWindow &window)
{
	Vector2u sizeWindow = window.getSize();
	//sizeWindow.x /= 1.f;//SCALE_VIEW
	//sizeWindow.y /= 1.f;// TODO : increase zoom for camera, small image
	view.setSize(Vector2f(sizeWindow));

	float tempX = getXPos();
	float tempY = getYPos();

	listener.setPosition(tempX, tempY, 0);

	float x = getXPos();
	float y = getYPos();

	int leftBorder = sizeWindow.x / 2;
	int rightBorder = SIZE_BLOCK * (WIDTH_MAP - BORDER1) - sizeWindow.x / 2;
	int topBorder = sizeWindow.y / 2;
	int lowBorder = SIZE_BLOCK * LONG_MAP - sizeWindow.y / 2;

	if (int(x) < leftBorder) tempX = float(leftBorder);
	else if (int(x) > rightBorder) tempX = float(rightBorder);
	if (int(y) < topBorder) tempY = float(topBorder);
	else if (int(y) > lowBorder) tempY = float(lowBorder);

	view.setCenter(tempX, tempY);
}

void Entity::givenForPersonDamage(Entity &person)
{
	Item& itemEnemy = itemFromPanelQuickAccess[idSelectItem];
	typeDamageItem damageEnemyItem = itemEnemy.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = damage;
	float cutDamage;
	float crashDamage;
	float multiplirer = enemyDamege.damageMultiplirer;

	cutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEnemyItem.cuttingDamage);
	crashDamage = multiplirer * (enemyDamege.crushingDamage + damageEnemyItem.crushingDamage);

	cutDamage *= person.protection.protectionCut;
	crashDamage *= person.protection.protectionCrash;

	person.damage.inputDamage = int(cutDamage + crashDamage);
	person.health.currentHealth -= person.damage.inputDamage;

	person.damage.inputDamage = 0;
}

void Entity::updateAtack(world &world, const float deltaTime)
{

	bool isEnemy = founds.findEnemyFromList > -1;
	bool notMyself = founds.findEnemy != this;
	if (giveDamage && isEnemy && notMyself) {

		if (founds.findEnemy->isDeath) {
			killFindEnemy(world);
		}
		else {
			Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
			hurtEnemy(currentItem, deltaTime);
		}
	}
	else if(!isEnemy && giveDamage)
	{	
		breakNearCollision(world);	
	}
}

void Entity::killFindEnemy(world& world)
{
	founds.findEnemy->Drop(world);
	founds.findEnemy->playSoundDeath(world);
	world.Enemys.erase(world.Enemys.begin() + founds.findEnemyFromList);
	world.countEntity--;

	resetAtack();
}

void Entity::hurtEnemy(Item &currentItem, const float deltaTime)
{
	currenMode = idEntityMode::atack;

	Vector2f posPerson = { getXPos(), getYPos() };
	Vector2f posEnemy = { founds.findEnemy->getXPos(), founds.findEnemy->getYPos() };
	float distanse = distansePoints(posPerson, posEnemy);

	animation.updateFight(deltaTime, giveDamage, currenMode);
	if (giveDamage && distanse <= SIZE_BLOCK * 2.5f) {
		resetAtack();
		founds.findEnemy->takeDamage(damage, currentItem);
		playAtackSound(currentItem);
	}
}
/*
void Entity::hurtPerson(Entity& enemy, world& world, const float deltaTime)
{
	givenForPersonDamage(enemy);

	Item &itemEnemy = itemFromPanelQuickAccess[idSelectItem];

	playAtackSound(itemEnemy);


	itemEnemy.currentToughness -= 1;
	if (itemEnemy.currentToughness < 1) {
		redefineType(itemEnemy, world, -itemEnemy.typeItem->features.id);
	}
}
*/

void Entity::searchEnemy(Entity &enemy, world &world, const float deltaTime)
{
	float radiuseView = type->view.radiuseView;
	bool feelEnemy = type->view.feelEnemy;

	bool onLevelEnemy = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEnemy || feelEnemy;
	bool noAtack = currenMode != idEntityMode::atack;
	Vector2f enemyPoint = enemy.getPosition();
	Vector2f searcherPoint = getPosition();

	float distanse;
	distanse = distansePoints(searcherPoint , enemyPoint);

	if (distanse <= radiuseView && onLevel) {
		Vector2f movemoment;
		if (noAtack) {
			currenMode = idEntityMode::fight;

			movemoment = vectorDirection(searcherPoint , enemyPoint);

			checkLevelHealth(movemoment);
			defineDirectionLook(movemoment);

			if (feelEnemy == false) {
				checkBlock(world.field , distanse);
			}

			bool isFight = currenMode == idEntityMode::fight;
			if (isFight) {

				choiceDirections(movemoment);

				if (wasCollision) {

					if (!onLevelEnemy && feelEnemy) {
						searchWay(world);
					}
					else if (feelEnemy) {
						choiceBlock(world);
					}

				}
				else {

					bool isNearFight = distanse <= SIZE_BLOCK;
					if (isNearFight) {
						currenMode = idEntityMode::atack;
						directions.directionWalk = NONE_DIRECTION;
						founds.currentTarget = RESET_VECTOR_3I;
					}

				}

				if(currenMode == atack 
					 || currenMode == fight)
				{
					founds.findEnemy = &enemy;//Player
				}

			}


		}
		else
		{
			bool isNearFight = distanse <= SIZE_BLOCK;
			if (isNearFight) {
				if (giveDamage) {
					founds.findEnemy->takeDamage(damage , getCurrentItem());
					resetAtack();
				}
			}
			else {

				////////////////////////////////////
				// TODO
				if (giveDamage) {

						Field &field = world.field;
						Vector3i posUse;
						int x = int(getXPos() / SIZE_BLOCK);
						int y = int(getYPos() / SIZE_BLOCK);
						for (int i = -1; i < 2; i++) {
							for (int j = -1; j < 2; j++) {
								posUse = { x + j, y + i, currentLevelFloor + 1 };
								if (field.dataMap[posUse.z][posUse.y][posUse.x] != field.charBlocks[idBlocks::air]
										|| isUnlifeObject(posUse, world)) {
									founds.currentTarget = { x + j, y + i, currentLevelFloor + 1 };
									break;
								}
							}

						}

					if (founds.currentTarget != RESET_VECTOR_3I) {
						breakNearCollision(world);
					}
				}
				////////////////////////////////////
				
			}
		}
	}
	else
	{
		founds.currentTarget = RESET_VECTOR_3I;
	}
}

void Entity::useItem(world &world, Event &event, Vector2f pos)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];

	int x = int(pos.x / SIZE_BLOCK);
	int y = int(pos.y / SIZE_BLOCK);
	Vector3i &posUse = founds.currentTarget;

	posUse.x = x;
	posUse.y = y;

	bool isEnemy = founds.findEnemy != founds.emptyEnemy;
//	bool isObject = founds.findObject->typeObject->id != founds.emptyObject->typeObject->id;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEnemy && isAtack && isInUseField(pos.x, pos.y, true)) {

		if (founds.findEnemy->currentLevelFloor == currentLevelFloor) {

			if (animation.currentTimeFightAnimation == 0.f) {
				currenMode = idEntityMode::atack;
			}

		}
	}
	else {
		
		int category = currentItem.typeItem->features.category;
		switch (category) {
		case idCategoryItem::backhoe:
		case idCategoryItem::pickax:
		case idCategoryItem::axe:
			if (isInUseField(pos.x, pos.y, true)) {
				int level;
				defineLevel(level, event);

				
				posUse = { x, y, level };

				Field &field = world.field;
				wchar_t	*block = &field.dataMap[level][y][x];
				int idNature;
				idNature = field.idsNature[field.findIdBlock(*block)];

				if(idNature <= idNatureObject::Unbreaking)
				{
					idNature = founds.findObject->typeObject->idNature;
				}
				if (idNature != idNatureObject::Unbreaking && isInListObjects(*currentItem.typeItem->destroy, idNature)) {
					currenMode = idEntityMode::atack;
					giveDamage = false;
				}
			}
			break;
		case idCategoryItem::block:
		case idCategoryItem::unlifeObject:
			if (isInUseField(pos.x, pos.y, false)) {
				int level;
				defineLevel(level, event);

				posUse = { x, y, level };

				useBlock(posUse, world, currentItem);
			}
			break;
		case idCategoryItem::food:
			useAsFood(currentItem, event);
			break;
		case idCategoryItem::bukketWithWater:
			useAsBukketWithWater(currentItem, world, event);
			break;
		case idCategoryItem::bottleWithWater:
			useAsBottleWithWater(currentItem, world, event);
			break;
		case idCategoryItem::healthPotion:
			useAsHealthPotion(currentItem, world, event);
			break;
		case idCategoryItem::bukketEmpty:// ÈÑÏÐÀÂÜ
			if (isInUseField(pos.x, pos.y, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBukket(currentItem, world, level);
			}
			break;
		case idCategoryItem::bottleEmpty:
			if (isInUseField(pos.x, pos.y, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBottle(currentItem, world, level);
			}
			break;
		case idCategoryItem::other:
			break;
		default:
			break;
		}
	}

}

void Entity::playSoundChoiseItem()
{
	int id = idSoundPaths::itemChoiseIdSound;
	::playSound(id, *soundBase, soundEntity, getPosition());
}

Item & Entity::getCurrentItem()
{
	return itemFromPanelQuickAccess[idSelectItem];
}

////////////////////////////////////////////////////////////////////
// Èñïîëüçóþ ïîòîì (íå ÂÊËÞ×ÅÍÀ)
void Entity::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	sizeSprite &size = type->featuresSprite.size;
	float dX = pos.x - spriteEntity->getPosition().x - size.width / 2;
	float dY = pos.y - spriteEntity->getPosition().y - size.height / 2;
	rotation = (atan2(dX, dY)) * 180 / PI - 180;
	if(rotation < 0)
	{
		rotation += 360;
	}
}


void Entity::getCoordinateForView(Vector2f position , View &view)
{
	view.setCenter(position);
}