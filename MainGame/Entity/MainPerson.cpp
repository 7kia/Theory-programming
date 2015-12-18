#include "MainPerson.h"

using namespace sf;
using namespace std;

void initializeViewer(View &view , Listener &listener)
{
	
	// TODO
	float posX = float(CENTER_WORLD.x * SIZE_BLOCK);
	float posY = float(CENTER_WORLD.y * SIZE_BLOCK);
	view.setSize(DEFAULT_WIDTH_WINDOW, DEFAULT_HEIGHT_WINDOW);
	view.setCenter(posX, posY);

	// TODO
	listener.setUpVector(0.f, 1.f, 0.f);
	listener.setGlobalVolume(100.f);

}

void Entity::updateView(View &view , Listener &listener , RenderWindow &window)
{
	Vector2u sizeWindow = window.getSize();
	//sizeWindow.x /= 1.f;//SCALE_VIEW
	//sizeWindow.y /= 1.f;// TODO
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

void Entity::initFounds(::Item &item, UnlifeObject& object, ::Entity& enemy)
{
	founds.init(&item, &object);
	emptyEnemy = &enemy;
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

	bool isEnemy = findEnemyFromList > -1;
	if (giveDamage && isEnemy) {

		if (findEnemy->isDeath) {
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
	findEnemy->EnemyDrop(world);
	findEnemy->playSoundDeath(world);
	world.Enemys.erase(world.Enemys.begin() + findEnemyFromList);
	world.countEntity--;

	resetAtack();
}

void Entity::hurtEnemy(Item &currentItem, const float deltaTime)
{
	currenMode = idEntityMode::atack;

	Vector2f posPerson = { getXPos(), getYPos() };
	Vector2f posEnemy = { findEnemy->getXPos(), findEnemy->getYPos() };
	float distanse = distansePoints(posPerson, posEnemy);

	animation.updateFight(deltaTime, giveDamage, currenMode);
	if (giveDamage && distanse <= SIZE_BLOCK * 2.5f) {
		resetAtack();
		findEnemy->takeDamage(damage, currentItem);
		playAtackSound(currentItem);
	}
}

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

void Entity::attractionEnemy(Entity &enemy, world &world, const float deltaTime)
{
	float radiuseView = enemy.type->view.radiuseView;
	bool feelEnemy = enemy.type->view.feelEnemy;

	bool onLevelEnemy = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEnemy || feelEnemy;
	bool noAtack = enemy.currenMode != idEntityMode::atack;
	Vector2f personPoint = { getXPos(), getYPos() };
	Vector2f enemyPoint;
	float distanse;

	enemyPoint = enemy.spriteEntity->getPosition();
	distanse = distansePoints(personPoint, enemyPoint);

	if (distanse <= radiuseView && onLevel) {
		Vector2f movemoment;
		if (noAtack) {
			enemy.currenMode = idEntityMode::fight;

			movemoment = vectorDirection(enemyPoint, personPoint);
			enemy.checkLevelHealth(movemoment);
			enemy.defineDirectionLook(movemoment);

			// TODO

			if (feelEnemy == false)
				enemy.checkBlock(world.field, distanse);

			bool isFight = enemy.currenMode == idEntityMode::fight;
			if (isFight) {

				enemy.choiceDirections(movemoment);
				//step.currentTime = 0;

				if (enemy.wasCollision) {

					enemy.directions.directionWalk = NONE_DIRECTION;
					if (!onLevelEnemy && feelEnemy) {
						enemy.searchWay(world);
					}
					else if (feelEnemy) {
						enemy.choiceBlock(world);
					}

				}
				else {

					bool isNearFight = distanse <= SIZE_BLOCK;
					if (isNearFight) {
						enemy.currenMode = idEntityMode::atack;
						enemy.directions.directionWalk = NONE_DIRECTION;
					}

				}


			}


		}
		else
		{
			bool isNearFight = distanse <= SIZE_BLOCK;
			if (isNearFight) {
				// TODO
				//enemy.animation.updateFight(deltaTime, enemy.giveDamage, enemy.currenMode);
				//enemy.playAnimationAtack(deltaTime);
				if (enemy.giveDamage) {
					enemy.hurtPerson(*this, world, deltaTime);
					enemy.resetAtack();
				}
			}
			else {
				
				////////////////////////////////////
				// TODO
				Vector2i posBlock = { enemy.founds.currentTarget.x, enemy.founds.currentTarget.y };
				if (posBlock != RESET_VECTOR_2I)
				{
					//enemy.currenMode = idEntityMode::atack;
					//enemy.animation.updateFight(deltaTime, enemy.giveDamage, enemy.currenMode);
					//enemy.playAnimationAtack(deltaTime);
					if (enemy.giveDamage) {
						enemy.breakNearCollision(world);

					}
				}
				else {
					/////////
					// TODO
					enemy.currenMode = idEntityMode::walk;
					/////////
					enemy.resetAtack();
				}
				////////////////////////////////////
				
			}
		}
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


	bool isEnemy = findEnemy != emptyEnemy;
	bool isObject = founds.findObject->typeObject->id != founds.emptyObject->typeObject->id;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEnemy && isAtack && isInUseField(pos.x, pos.y, true)) {

		if (findEnemy->currentLevelFloor == currentLevelFloor) {

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

////////////////////////////////////////////////////////////////////
// Èñïîëüçóþ ïîòîì (íå ÂÊËÞ×ÅÍÀ)
void Entity::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);
	float dX = pos.x - spriteEntity->getPosition().x - size.width / 2;
	float dY = pos.y - spriteEntity->getPosition().y - size.height / 2;
	rotation = (atan2(dX, dY)) * 180 / PI - 90;
	if(rotation < 0)
	{
		rotation += 360;
	}
}


void Entity::getCoordinateForView(Vector2f position , View &view)
{
	view.setCenter(position);
}