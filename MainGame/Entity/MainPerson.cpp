#include "../Items/ItemsVar.h"


#include "EntityVar.h"

#include "UseItem.h"
using namespace sf;
using namespace std;

<<<<<<< HEAD
void initializeMainPerson(MainPerson &mainPerson, world &world)
=======
////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(Entity &mainPerson, world &world, View &view)
>>>>>>> master
{
	float posX = float(CENTER_WORLD.x * SIZE_BLOCK);
	float posY = float(CENTER_WORLD.y * SIZE_BLOCK);
<<<<<<< HEAD
	mainPerson.view = new View;
	mainPerson.listener = new Listener;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);
=======
	view.setSize(640, 480);
	view.setCenter(posX, posY);
>>>>>>> master

	// TODO
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
	sf::Listener::setGlobalVolume(100.f);

	mainPerson.EntityInit(world.typesObjects.typesEntity[idEntity::mainPersonEntity], world, CENTER_WORLD.x, CENTER_WORLD.y, 2);
}

<<<<<<< HEAD
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	sizeWindow.x /= 1.f;//SCALE_VIEW
	sizeWindow.y /= 1.f;// TODO
	view->setSize(Vector2f(sizeWindow));
=======
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Обновление камеры
void Entity::updateView(RenderWindow & window, View &view)
{
	Vector2u sizeWindow = window.getSize();
	//sizeWindow.x /= 1.5;
	//sizeWindow.y /= 1.5;
	view.setSize(Vector2f(sizeWindow));// ИСПРАВЬ
>>>>>>> master

	float tempX = getXPos();
	float tempY = getYPos();

	listener->setPosition(tempX, tempY, 0);

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


<<<<<<< HEAD
void Enemy::givenForPersonDamage(MainPerson &person)
{
	Item& itemEnemy = itemFromPanelQuickAccess[idSelectItem];
	typeDamageItem damageEnemyItem = itemEnemy.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = damage;
=======

void Entity::givenForPersonDamage(Entity &enemy)
{
	Item& itemEntity = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];
	typeDamageItem damageEntityItem = itemEntity.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = enemy.damage;
>>>>>>> master
	float cutDamage;
	float crashDamage;
	float multiplirer = enemyDamege.damageMultiplirer;

<<<<<<< HEAD
	cutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEnemyItem.cuttingDamage);
	crashDamage = multiplirer * (enemyDamege.crushingDamage + damageEnemyItem.crushingDamage);
=======
	cutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEntityItem.cuttingDamage);
	crashDamage = multiplirer * (enemyDamege.crushingDamage + damageEntityItem.crushingDamage);
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;
>>>>>>> master

	cutDamage *= person.protection.protectionCut;
	crashDamage *= person.protection.protectionCrash;

	person.damage.inputDamage = int(cutDamage + crashDamage);
	person.health.currentHealth -= person.damage.inputDamage;

	person.damage.inputDamage = 0;
}

<<<<<<< HEAD
void MainPerson::updateAtack(world &world, const float deltaTime)
=======
void Entity::EntityDrop(world& world)
>>>>>>> master
{

<<<<<<< HEAD
	bool isEnemy = findEnemyFromList > -1;
	if (giveDamage && isEnemy) {
=======
	Item* addItem = new Item;
	TypeEntity& typeEntity = *type;
	size_t countItem = typeEntity.drop.minCountItems.size();

	vector<int> &minAmount = typeEntity.drop.minCountItems;
	vector<int> &maxAmount = typeEntity.drop.maxCountItems;

	throwItem(field, items);

	int currentAmount;
	for (int i = 0; i < countItem; i++) {

		currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 2);
		for (int j = 0; j < currentAmount; j++) {
			addItem->setType(typesItems[typeEntity.drop.dropItems[i]]);
			addItem->setPosition(founds.currentTarget.x + 1,
													 founds.currentTarget.y + 1,
													 currentLevelFloor + 1);
			world.items->push_back(*addItem);
>>>>>>> master

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

<<<<<<< HEAD
void MainPerson::killFindEnemy(world& world)
{
	findEnemy->EnemyDrop(world);
	findEnemy->playSoundDeath(world);
	world.Enemys->erase(world.Enemys->begin() + findEnemyFromList);
	world.countEntity--;
=======
void Entity::playSoundDeath(world& world)
{
	vector<UnlifeObject> &objects = *world.unlifeObjects;
	TypeUnlifeObject *typeObjects = world.typesObjects.typesUnlifeObject;
	UnlifeObject addObject;
	sizeSprite &sizeSprite = type->featuresSprite.size;
	Vector3i pos = { int((getXPos() + sizeSprite.width / 2) / SIZE_BLOCK),
		int((getYPos() + sizeSprite.height / 2) / SIZE_BLOCK),
									currentLevelFloor + 1 };

	bool findSound = true;
	switch(type->id)
	{
	case idEntity::wolfEntity:
		addObject.setType(typeObjects[idUnlifeObject::wolfDeathEffect]);
		addObject.setPosition(pos.x, pos.y, pos.z);
		break;
	case idEntity::skeletEntity:
	case idEntity::skeletBuilderEntity:
	case idEntity::skeletDiggerEntity:
	case idEntity::skeletLumbermillEntity:
	case idEntity::skeletMinerEntity:
		addObject.setType(typeObjects[idUnlifeObject::skeletDeathEffect]);
		addObject.setPosition(pos.x, pos.y, pos.z);
		break;
	default:
		findSound = false;
		break;
	}

	if(findSound)
	{
			objects.push_back(addObject);

			Sound &soundObject = objects[objects.size() - 1].soundObject;

			switch (type->id) {
			case idEntity::wolfEntity:
				playSound(idSoundPaths::wolfDeathSound, *soundBase, soundObject, getPosition());
				break;
			case idEntity::skeletEntity:
			case idEntity::skeletBuilderEntity:
			case idEntity::skeletDiggerEntity:
			case idEntity::skeletLumbermillEntity:
			case idEntity::skeletMinerEntity:
				playSound(idSoundPaths::skeletonDeathSound, *soundBase, soundObject, getPosition());
				break;
			default:
				break;
			}

	}

>>>>>>> master

	resetAtack();
}

<<<<<<< HEAD
void MainPerson::hurtEnemy(Item &currentItem, const float deltaTime)
{
	currenMode = idEntityMode::atack;
=======
void Entity::updateAtack(world &world, const float deltaTime)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];

	Entity &findEntity = *founds.findEntity;
	Entity &emptyEntity = *founds.emptyEntity;
	TypeEntity &typeFindEntity = *findEntity.type;
	TypeEntity &typeEmptyEntity = *emptyEntity.type;

	bool isAtack = currenMode == idEntityMode::atack;
	bool isEntity = founds.findEntityFromList > -1;// && (typeFindEntity.name != typeEmptyEntity.name);
	if (isAtack && isEntity) {

		if (findEntity.isDeath) {

			// TODO
			//findEntity->playSound(0.f, 0.f, idSoundPaths::skeletonDeathPath);

			findEntity.EntityDrop(world);
			findEntity.playSoundDeath(world);
			world.Entitys->erase(world.Entitys->begin() + founds.findEntityFromList);
			world.countEntity--;

			animation.currentTimeFightAnimation = 0.f;

			currenMode = idEntityMode::walk;
			giveDamage = false;



		}
		else {
			currenMode = idEntityMode::atack;

			Vector2f posPerson = { getXPos(), getYPos() };
			Vector2f posEntity = { findEntity.getXPos(), findEntity.getYPos() };
			float distanse = distansePoints(posPerson, posEntity);

			if (giveDamage && distanse <= SIZE_BLOCK * 2.5f) {
				animation.currentTimeFightAnimation = 0.f;

				currenMode = idEntityMode::walk;
				giveDamage = false;
				findEntity.takeDamage(damage, currentItem);

				playAtackSound(currentItem);
			}

		}

	}
	else
	{
		animation.currentTimeFightAnimation = 0.f;
>>>>>>> master

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

<<<<<<< HEAD
void Enemy::hurtPerson(MainPerson& enemy, world& world, const float deltaTime)
=======
void Entity::hurtPerson(Entity& enemy, world& world, const float deltaTime)
>>>>>>> master
{
	givenForPersonDamage(enemy);

	Item &itemEnemy = itemFromPanelQuickAccess[idSelectItem];

	playAtackSound(itemEnemy);

<<<<<<< HEAD
	itemEnemy.currentToughness -= 1;
	if (itemEnemy.currentToughness < 1) {
		redefineType(itemEnemy, world, -itemEnemy.typeItem->features.id);
=======
		enemy.currenMode = idEntityMode::fight;
		enemy.giveDamage = false;
		givenForPersonDamage(enemy);

		Item &itemEntity = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];

		enemy.playAtackSound(itemEntity);

		itemEntity.currentToughness -= 1;
		if (itemEntity.currentToughness < 1) {
			enemy.redefineType(itemEntity, world, -itemEntity.typeItem->features.id);
		}
>>>>>>> master
	}
}

void Entity::attractionEntity(Entity &enemy, world &world, const float deltaTime)
{
	float radiuseView = enemy.type->view.radiuseView;
	bool feelEntity = enemy.type->view.feelEntity;

<<<<<<< HEAD
	bool onLevelEnemy = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEnemy || feelEnemy;
	bool noAtack = enemy.currenMode != idEntityMode::atack;
=======
	bool onLevelEntity = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEntity || feelEntity;

>>>>>>> master
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

<<<<<<< HEAD
			if (feelEnemy == false)
				enemy.checkBlock(world.field, distanse);
=======
		if (feelEntity == false)
			enemy.checkBlock(world.field, distanse);
>>>>>>> master

			bool isFight = enemy.currenMode == idEntityMode::fight;
			if (isFight) {

				enemy.choiceDirections(movemoment);
				step.currentTime = 0;

				if (enemy.wasCollision) {

					enemy.directions.directionWalk = NONE_DIRECTION;
					if (!onLevelEnemy && feelEnemy) {
						enemy.searchWay(world);
					}
					else if (feelEnemy) {
						enemy.choiceBlock(world);
					}

<<<<<<< HEAD
=======
				enemy.directions.directionWalk = NONE_DIRECTION;
				if (!onLevelEntity && feelEntity) {
					enemy.searchWay(world);
				}
				else if (feelEntity) {
					enemy.choiceBlock(world);
>>>>>>> master
				}
				else {

<<<<<<< HEAD
					bool isNearFight = distanse <= SIZE_BLOCK;
					if (isNearFight) {
						enemy.currenMode = idEntityMode::atack;
						enemy.directions.directionWalk = NONE_DIRECTION;
					}

=======

			} 
			else {

				bool isNearFight = distanse <= SIZE_BLOCK;
				if (isNearFight) {
					hurtPerson(enemy, world, deltaTime);
				}
				else if (onLevelEntity) {
					enemy.resetFightAnimation();
>>>>>>> master
				}


			}


		}
		else
		{
			bool isNearFight = distanse <= SIZE_BLOCK;
			if (isNearFight) {
				// TODO
				enemy.animation.updateFight(deltaTime, enemy.giveDamage, enemy.currenMode);
				enemy.playAnimationAtack(deltaTime);
				if (enemy.giveDamage) {
					enemy.hurtPerson(*this, world, deltaTime);
					enemy.resetAtack();
				}
			}
			else {
				////////////////////////////////////
				// TODO
				Vector2i posBlock = { enemy.founds.currentTarget.x, enemy.founds.currentTarget.y };
				if (posBlock != ZERO_VECTOR_2I)
				{
					enemy.animation.updateFight(deltaTime, enemy.giveDamage, enemy.currenMode);
					enemy.playAnimationAtack(deltaTime);
					if (enemy.giveDamage) {
						Vector3i &posUse = enemy.founds.currentTarget;
						Field &field = world.field;
						wchar_t	*block = &field.dataMap[posUse.z][posUse.y][posUse.x];
						int idNature;
						idNature = field.idsNature[field.findIdBlock(*block)];




						if (idNature > idNatureObject::Unbreaking && !enemy.isDestroyEffect(posUse, world)) {
							enemy.createDestroyEffect(world, posUse);
							enemy.founds.findObject = &(*world.unlifeObjects)[world.unlifeObjects->size() - 1];
							enemy.playObjectBreakSound(idNature);
							enemy.resetAtack();
						}
						else {

							enemy.useTool(posUse, world, enemy.itemFromPanelQuickAccess[enemy.idSelectItem]);
						}
					

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

<<<<<<< HEAD
void MainPerson::useItem(world &world, Event &event, Vector2f pos)
=======
void Entity::useItem(world &world,
												Event &event, Vector2f pos)
>>>>>>> master
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];

<<<<<<< HEAD
=======
	Entity &findEntity = *founds.findEntity;
	Entity &emptyEntity = *founds.emptyEntity;



>>>>>>> master
	int x = int(pos.x / SIZE_BLOCK);
	int y = int(pos.y / SIZE_BLOCK);
	Vector3i &posUse = founds.currentTarget;

	posUse.x = x;
	posUse.y = y;


<<<<<<< HEAD
	bool isEnemy = findEnemy != emptyEnemy;
	bool isObject = founds.findObject->typeObject->id != founds.emptyObject->typeObject->id;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEnemy && isAtack && isInUseField(pos.x, pos.y, true)) {

		if (findEnemy->currentLevelFloor == currentLevelFloor) {
=======
	bool isEntity = findEntity.type != emptyEntity.type;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEntity && isAtack) {

		if (isInUseField(pos.x, pos.y, true)) {
			if (findEntity.currentLevelFloor == currentLevelFloor) {

				if (animation.currentTimeFightAnimation == 0.f) {
					currenMode = idEntityMode::atack;
				}
>>>>>>> master

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
				if (idNature != idNatureObject::Unbreaking ) {
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
		case idCategoryItem::bukketEmpty:// ИСПРАВЬ
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
// Использую потом (не ВКЛЮЧЕНА)
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

<<<<<<< HEAD

void MainPerson::getCoordinateForView(float x, float y)//функция для считывания координат игрока
{
	view->setCenter(x, y);//следим за игроком, передавая его координаты. 
}

// TODO
void MainPerson::changeview()
{
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view->zoom(1.0100f);
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		view->rotate(1);
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view->setSize(640, 480);
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view->setSize(540, 380);
	}

=======
////////////////////////////////////////////////////////////////////
// View
void Entity::getCoordinateForView(Vector2f pos, View &view)//функция для считывания координат игрока
{
	view.setCenter(pos.x, pos.y);//следим за игроком, передавая его координаты. 
>>>>>>> master
}
