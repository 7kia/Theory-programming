#include "../Items/ItemsVar.h"


#include "EntityVar.h"

#include "UseItem.h"
using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson &mainPerson, world &world)
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
	mainPerson.view = new View;
	mainPerson.listener = new Listener;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

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
	mainPerson.initFounds(emptyObjects.emptyItem, emptyObjects.emptyObject, emptyObjects.emptyEnemy);
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
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	sizeWindow.x /= SCALE_VIEW;
	sizeWindow.y /= SCALE_VIEW;
	view->setSize(Vector2f(sizeWindow));

	float tempX = getXPos();
	float tempY = getYPos();


	listener->setPosition(tempX, tempY, 0);

	float x = getXPos();
	float y = getYPos();

	int leftBorder = sizeWindow.x / 2;
	int rightBorder = SIZE_BLOCK * (WIDTH_MAP - BORDER1) - sizeWindow.x / 2;
	int topBorder = sizeWindow.y / 2;
	int lowBorder = SIZE_BLOCK * LONG_MAP - sizeWindow.y / 2;

	if (int(x) < leftBorder) tempX = leftBorder;
	else if (int(x) > rightBorder) tempX = rightBorder;
	if (int(y) < topBorder) tempY = topBorder;
	else if (int(y) > lowBorder) tempY = lowBorder;

	view->setCenter(tempX, tempY);
}

void MainPerson::initFounds(::Item &item, UnlifeObject& object, ::Enemy& enemy)
{
	founds.init(&item, &object);
	emptyEnemy = &enemy;
}

void Enemy::givenForPersonDamage(MainPerson &person)
{
	Item& itemEnemy = itemFromPanelQuickAccess[idSelectItem];
	typeDamageItem damageEnemyItem = itemEnemy.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = damage;
	float cutDamage;
	float crashDamage;
	float multiplirer = enemyDamege.damageMultiplirer;

	cutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEnemyItem.cuttingDamage);
	crashDamage = multiplirer * (enemyDamege.crushingDamage + damageEnemyItem.crushingDamage);
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;

	cutDamage *= person.protection.protectionCut;
	crashDamage *= person.protection.protectionCrash;

	person.damage.inputDamage = int(cutDamage + crashDamage);
	person.health.currentHealth -= person.damage.inputDamage;

	person.damage.inputDamage = 0;
}


void Enemy::EnemyDrop(world& world)
{
	Field &field = world.field;
	vector<Item> &items = *world.items;
	TypeItem *typesItems = world.typesObjects.typesItem;

	Item* addItem = new Item;
	TypeEnemy& typeEnemy = *type;
	size_t countItem = typeEnemy.drop.minCountItems.size();

	vector<int> &minAmount = typeEnemy.drop.minCountItems;
	vector<int> &maxAmount = typeEnemy.drop.maxCountItems;

	throwItem(field, items);

	int currentAmount;
	for (int i = 0; i < countItem; i++) {

		currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 2);
		for (int j = 0; j < currentAmount; j++) {
			addItem->setType(typesItems[typeEnemy.drop.dropItems[i]]);
			addItem->setPosition(founds.currentTarget.x + 1,
													 founds.currentTarget.y + 1,
													 currentLevelFloor + 1);
			world.items->push_back(*addItem);

		}

	}
	delete addItem;

}

void Enemy::playSoundDeath(world& world)
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
	case idEntity::wolfEnemy:
		addObject.setType(typeObjects[idUnlifeObject::wolfDeathEffect]);
		addObject.setPosition(pos.x, pos.y, pos.z);
		break;
	case idEntity::skeletEnemy:
	case idEntity::skeletBuilderEnemy:
	case idEntity::skeletDiggerEnemy:
	case idEntity::skeletLumbermillEnemy:
	case idEntity::skeletMinerEnemy:
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
			case idEntity::wolfEnemy:
				playSound(idSoundPaths::wolfDeathSound, *soundBase, soundObject, getPosition());
				break;
			case idEntity::skeletEnemy:
			case idEntity::skeletBuilderEnemy:
			case idEntity::skeletDiggerEnemy:
			case idEntity::skeletLumbermillEnemy:
			case idEntity::skeletMinerEnemy:
				playSound(idSoundPaths::skeletonDeathSound, *soundBase, soundObject, getPosition());
				break;
			default:
				break;
			}

	}


}

void MainPerson::updateAtack(world &world, const float deltaTime)
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

void MainPerson::killFindEnemy(world& world)
{
	findEnemy->EnemyDrop(world);
	findEnemy->playSoundDeath(world);
	world.Enemys->erase(world.Enemys->begin() + findEnemyFromList);
	world.countEntity--;

	resetAtack();
}

void MainPerson::hurtEnemy(Item &currentItem, const float deltaTime)
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


void Enemy::hurtPerson(MainPerson& enemy, world& world, const float deltaTime)
{
	givenForPersonDamage(enemy);

	Item &itemEnemy = itemFromPanelQuickAccess[idSelectItem];

	playAtackSound(itemEnemy);

	itemEnemy.currentToughness -= 1;
	if (itemEnemy.currentToughness < 1) {
		redefineType(itemEnemy, world, -itemEnemy.typeItem->features.id);
	}
}

void MainPerson::attractionEnemy(Enemy &enemy, world &world, const float deltaTime)
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
				step.currentTime = 0;

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

void MainPerson::useItem(world &world, Event &event, Vector2f pos)
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
	if (isEnemy && isAtack) {

		if (isInUseField(pos.x, pos.y, true)) {
			if (findEnemy->currentLevelFloor == currentLevelFloor) {

				if (animation.currentTimeFightAnimation == 0.f) {
					currenMode = idEntityMode::atack;
				}

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
void MainPerson::getCoordinateForView(float x, float y)//функция для считывания координат игрока
{
	view->setCenter(x, y);//следим за игроком, передавая его координаты. 
}

void MainPerson::changeview()
{
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view->zoom(1.0100f); //масштабируем, уменьшение
							 //view.zoom(1.0006f); //тоже самое помедленнее соответственно
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//сразу же задает поворот камере
		view->rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view->setSize(640, 480);//устанавливает размер камеры (наш исходный)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view->setSize(540, 380);//например другой размер
	}

}
////////////////////////////////////////////////////////////////////