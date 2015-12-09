#include "../Items/ItemsVar.h"


#include "EntityVar.h"

#include "UseItem.h"
using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson &mainPerson, world &world, View &view)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// Задание размера
	mainPerson.size.init(32, 32);

	// Дальность подбора предметов
	mainPerson.radiusUse = 1;

	// Скорость ходьбы
	mainPerson.step.init(150.f);
	mainPerson.animation.timeAnimation = 0.f;

	// TODO
	float posX = float(CENTER_WORLD.x * SIZE_BLOCK);
	float posY = float(CENTER_WORLD.y * SIZE_BLOCK);
	view.setSize(640, 480);
	view.setCenter(posX, posY);

	// TODO
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
	sf::Listener::setGlobalVolume(100.f);

	// Текстура
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.size.width, mainPerson.size.height));
	//mainPerson.spriteEntity->setOrigin(mainPerson.size.width / 2, mainPerson.size.height / 2);


	mainPerson.soundBase = &world.databaseSound;

	emptyObjects &emptyObjects = world.emptyObjects;
	mainPerson.founds.init(&emptyObjects.emptyItem, &emptyObjects.emptyObject, &emptyObjects.emptyEntity);
	// Создайм и заполняем панель
	mainPerson.idSelectItem = 0;
	mainPerson.amountSlots = AMOUNT_ACTIVE_SLOTS;
	mainPerson.itemFromPanelQuickAccess = new Item[AMOUNT_ACTIVE_SLOTS];
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		mainPerson.itemFromPanelQuickAccess[i].typeItem = emptyObjects.emptyItem.typeItem;
	}

	// Позиция и направление
	mainPerson.currentLevelFloor = 1;
	mainPerson.currenMode = idEntityMode::walk;
	mainPerson.spriteEntity->setPosition(posX, posY);

	entityAnimation &animation = mainPerson.animation;
	animation.init(1.5f, 1.f);

	Directions &directions = mainPerson.directions;
	directions.directionWalk = NONE_DIRECTION;
	directions.directionLook = DOWN;

	mainPerson.health.maxHealth = 1000;
	mainPerson.health.currentHealth = 900;
	mainPerson.stamina.currentStamina = 35;
	mainPerson.mana.currentMana = 10;

	mainPerson.thirst.currentThirst = 5;
	mainPerson.hungry.currentHungry = 5;

	entityProtection &protection = mainPerson.protection;
	protection.protectionCut = 0.15f;
	protection.protectionCrash = 1.f;
	protection.protectionUnlife = 0.f;

	mainPerson.damage.damageMultiplirer = 1;


}

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Обновление камеры
void MainPerson::updateView(RenderWindow & window, View &view)
{
	Vector2u sizeWindow = window.getSize();
	//sizeWindow.x /= 1.5;
	//sizeWindow.y /= 1.5;
	view.setSize(Vector2f(sizeWindow));// ИСПРАВЬ

	float tempX = getXPos();
	float tempY = getYPos();//считываем коорд игрока и проверяем их, чтобы убрать края

	// TODO
	sf::Listener::setPosition(tempX, tempY, 0);

	float x = getXPos();
	float y = getYPos();

	int leftBorder = sizeWindow.x / 2;
	int rightBorder = SIZE_BLOCK * (WIDTH_MAP - BORDER1) - sizeWindow.x / 2;
	int topBorder = sizeWindow.y / 2;
	int lowBorder = SIZE_BLOCK * LONG_MAP - sizeWindow.y / 2;
	///*
	if (int(x) < leftBorder) tempX = leftBorder;//убираем из вида левую сторону
	else if (int(x) > rightBorder) tempX = rightBorder;//убираем из вида левую сторону
	if (int(y) < topBorder) tempY = topBorder;//верхнюю сторону
	else if (int(y) > lowBorder) tempY = lowBorder;//нижнюю сторону	
	//*/
	

	view.setCenter(tempX, tempY);
}



void MainPerson::givenForPersonDamage(Entity &enemy)
{
	Item& itemEntity = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];
	typeDamageItem damageEntityItem = itemEntity.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = enemy.damage;
	float cutDamage;
	float crashDamage;
	float multiplirer = enemyDamege.damageMultiplirer;

	cutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEntityItem.cuttingDamage);
	crashDamage = multiplirer * (enemyDamege.crushingDamage + damageEntityItem.crushingDamage);
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;

	damage.inputDamage = int(cutDamage + crashDamage);
	health.currentHealth -= damage.inputDamage;

	damage.inputDamage = 0;// TODO	
}

void Entity::EntityDrop(world& world)
{
	Field &field = world.field;
	vector<Item> &items = *world.items;
	TypeItem *typesItems = world.typesObjects.typesItem;

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

		}

	}
	delete addItem;

}

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


}

void MainPerson::updateAtack(world &world, const float deltaTime)
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

		currenMode = idEntityMode::walk;

	}
}

void MainPerson::hurtPerson(Entity& enemy, world& world, const float deltaTime)
{
	enemy.currenMode = idEntityMode::atack;

	entityAnimation &animation = enemy.animation;

	animation.currentTimeFightAnimation += deltaTime;
	if (animation.currentTimeFightAnimation > animation.timeFightAnimation) {
		animation.currentTimeFightAnimation = 0.f;

		enemy.currenMode = idEntityMode::fight;
		enemy.giveDamage = false;
		givenForPersonDamage(enemy);

		Item &itemEntity = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];

		enemy.playAtackSound(itemEntity);

		itemEntity.currentToughness -= 1;
		if (itemEntity.currentToughness < 1) {
			enemy.redefineType(itemEntity, world, -itemEntity.typeItem->features.id);
		}
	}

	enemy.directions.directionWalk = NONE_DIRECTION;

}

void MainPerson::attractionEntity(Entity &enemy, world &world, const float deltaTime)
{
	float radiuseView = enemy.type->view.radiuseView;
	bool feelEntity = enemy.type->view.feelEntity;

	bool onLevelEntity = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEntity || feelEntity;

	Vector2f personPoint = { getXPos(), getYPos() };
	Vector2f enemyPoint;
	float distanse;

	enemyPoint = enemy.spriteEntity->getPosition();
	distanse = distansePoints(personPoint, enemyPoint);

	if (distanse <= radiuseView && onLevel) {
		Vector2f movemoment;
		enemy.currenMode = idEntityMode::fight;

		movemoment = vectorDirection(enemyPoint, personPoint);
		enemy.checkLevelHealth(movemoment);
		enemy.defineDirectionLook(movemoment);

		// TODO

		if (feelEntity == false)
			enemy.checkBlock(world.field, distanse);

		bool isFight = enemy.currenMode == idEntityMode::fight;
		if (isFight) {

			enemy.choiceDirections(movemoment);
			step.currentTime = 0;

			if (enemy.wasCollision) {

				enemy.directions.directionWalk = NONE_DIRECTION;
				if (!onLevelEntity && feelEntity) {
					enemy.searchWay(world);
				}
				else if (feelEntity) {
					enemy.choiceBlock(world);
				}


			} 
			else {

				bool isNearFight = distanse <= SIZE_BLOCK;
				if (isNearFight) {
					hurtPerson(enemy, world, deltaTime);
				}
				else if (onLevelEntity) {
					enemy.resetFightAnimation();
				}

			}


		}

	}

}
	

////////////////////////////////////////////////////////////////////

void MainPerson::useItem(world &world,
												Event &event, Vector2f pos)
{

	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];

	Entity &findEntity = *founds.findEntity;
	Entity &emptyEntity = *founds.emptyEntity;



	int x = int(pos.x / SIZE_BLOCK);
	int y = int(pos.y / SIZE_BLOCK);
	founds.currentTarget = { x, y };

	bool isEntity = findEntity.type != emptyEntity.type;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEntity && isAtack) {

		if (isInUseField(pos.x, pos.y, true)) {
			if (findEntity.currentLevelFloor == currentLevelFloor) {

				if (animation.currentTimeFightAnimation == 0.f) {
					currenMode = idEntityMode::atack;
				}

			}

		}


	}
	else {
		
		Vector3i posUse;
		int category = currentItem.typeItem->features.category;
		switch (category) {
		case idCategoryItem::backhoe:
		case idCategoryItem::pickax:
		case idCategoryItem::axe:
			if (isInUseField(pos.x, pos.y, true)) {
				int level;
				defineLevel(level, event);

				x = founds.currentTarget.x;
				y = founds.currentTarget.y;
				posUse = { x, y, level };
				useTool(posUse, world, currentItem);
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Блок и неживой объект
		case idCategoryItem::block:
		case idCategoryItem::unlifeObject:
			if (isInUseField(pos.x, pos.y, false)) {
				int level;
				defineLevel(level, event);

				x = founds.currentTarget.x;
				y = founds.currentTarget.y;
				posUse = { x, y, level };

				useBlock(posUse, world,
								 currentItem);
			}
			break;
			////////////////////////////////////////////////////////////////////////
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
		case idCategoryItem::bottleEmpty:// ИСПРАВЬ
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

void MainPerson::playSoundChoiseItem()
{
	int id = idSoundPaths::itemChoiseIdSound;
	::playSound(id, *soundBase, soundEntity, getPosition());
}

////////////////////////////////////////////////////////////////////
// Использую потом (не ВКЛЮЧЕНА)
void MainPerson::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
	float dX = pos.x - spriteEntity->getPosition().x - size.width / 2;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float dY = pos.y - spriteEntity->getPosition().y - size.height / 2;//он же, координата y
	rotation = (atan2(dX, dY)) * 180 / PI - 90;//получаем угол в радианах и переводим его в градусы
	if(rotation < 0)
	{
		rotation += 360;
	}
}

////////////////////////////////////////////////////////////////////
// View
void MainPerson::getCoordinateForView(Vector2f pos, View &view)//функция для считывания координат игрока
{
	view.setCenter(pos.x, pos.y);//следим за игроком, передавая его координаты. 
}
