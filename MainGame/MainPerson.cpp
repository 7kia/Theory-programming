
#include "ItemsVar.h"
#include "EntityVar.h"
#include "Font.h"


#include "UseItem.h"
using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, Item &emptyItem, UnlifeObject &emptyObject, Enemy &emptyEnemy)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// Задание размера
	mainPerson.size.init(32, 32);

	// Дальность подбора предметов
	mainPerson.radiusUse = 1;

	// Скорость ходьбы
	mainPerson.step.init(SPEED_ENTITY);
	mainPerson.animation.timeAnimation = 0.f;

	// Камера
	int posX(64), posY(64);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// TODO
	sf::Listener::setUpVector(0.f, 1.f, 0.f);
	sf::Listener::setGlobalVolume(100.f);

	// Текстура
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.size.width, mainPerson.size.height));

	mainPerson.initStepSounds(databaseSound);

	mainPerson.initFounds(emptyItem, emptyObject, emptyEnemy);

	// Создайм и заполняем панель
	mainPerson.idSelectItem = 0;
	mainPerson.amountSlots = AMOUNT_ACTIVE_SLOTS;
	mainPerson.itemFromPanelQuickAccess = new Item[AMOUNT_ACTIVE_SLOTS];
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {
		mainPerson.itemFromPanelQuickAccess[i].typeItem = emptyItem.typeItem;
	}

	// Позиция и направление
	mainPerson.currentLevelFloor = 0;
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
	protection.protectionCut = 1.5f;
	protection.protectionCrash = 1.f;

	mainPerson.damage.damageMultiplirer = 1;

}

////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Обновление камеры
void MainPerson::updateView(RenderWindow & window)
{
	Vector2u sizeWindow = window.getSize();
	view->setSize(Vector2f(sizeWindow));// ИСПРАВЬ

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

	if (x < leftBorder) tempX = leftBorder;//убираем из вида левую сторону
	else if (x > rightBorder) tempX = rightBorder;//убираем из вида левую сторону
	if (y < topBorder) tempY = topBorder;//верхнюю сторону
	else if (y > lowBorder) tempY = lowBorder;//нижнюю сторону	

	view->setCenter(tempX, tempY);
}

void MainPerson::initFounds(::Item &item, UnlifeObject& object, ::Enemy& enemy)
{
	founds.init(&item, &object);
	emptyEnemy = &enemy;
}

void MainPerson::initStepSounds(dataSound& databaseSound)
{
	soundsEntity.push_back(&databaseSound.sounds[idSoundEntity::stepGrass]);
	soundsEntity.push_back(&databaseSound.sounds[idSoundEntity::stepStone]);
}

void MainPerson::givenForPersonDamage(Enemy &enemy)
{
	Item& itemEnemy = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];
	typeDamageItem damageEnemyItem = itemEnemy.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = enemy.damage;
	float cutDamage;
	float crashDamage;
	float multiplirer = enemyDamege.damageMultiplirer;

	damage.inputCutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEnemyItem.cuttingDamage);
	damage.inputCrashDamage = multiplirer * (enemyDamege.crushingDamage + damageEnemyItem.crushingDamage);
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;

	damage.inputCutDamage *= protection.protectionCut;
	damage.inputCrashDamage *= protection.protectionCrash;

	damage.inputDamage = damage.inputCutDamage + damage.inputCrashDamage;
	health.currentHealth -= damage.inputDamage;

	damage.inputDamage = 0;// TODO
}


void MainPerson::updateAtack(world &world, TypeItem *typesItems, const Time &deltaTime)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];
	Field &field = world.field;
	vector<Enemy> &enemy = *world.Enemys;
	vector<Item> &items = *world.items;

	if (currenMode == idEntityMode::atack
			&& findEnemy->type->name != emptyEnemy->type->name) {
		if (findEnemy->isDeath) {

			Item* addItem = new Item;
			TypeEnemy& typeEnemy = *findEnemy->type;
			int countItem = typeEnemy.drop.minCountItems.size();

			vector<int> &minAmount = typeEnemy.drop.minCountItems;
			vector<int> &maxAmount = typeEnemy.drop.maxCountItems;
			vector<int> &idItems = typeEnemy.drop.dropItems;

			findEnemy->throwItem(field, items);

			int currentAmount;
			for (int i = 0; i < countItem; i++) {

				currentAmount = minAmount[i] + rand() % (maxAmount[i] - minAmount[i] + 2);
				for (int j = 0; j < currentAmount; j++) {
					addItem->setType(typesItems[typeEnemy.drop.dropItems[i]]);
					addItem->setPosition(founds.currentTarget.x + 1, founds.currentTarget.y + 1, currentLevelFloor + 1);
					world.items->push_back(*addItem);

				}

			}
			delete addItem;
			if (findEnemyFromList) {
				enemy.erase(enemy.begin() + findEnemyFromList);
			}
			else
			{
				enemy.clear();//TODO
			}

			//if (giveDamage) {
				animation.currentTimeFightAnimation = 0.f;

				currenMode = idEntityMode::walk;
				giveDamage = false;
				currentItem.currentToughness -= 1;
			//}
			

				breakItem(currentItem);
		} 
		else {
			currenMode = idEntityMode::atack;
			//animation.currentTimeFightAnimation += deltaTime.asSeconds();
			// TODO //enemy->giveDamage//
			Vector2f posPerson = { getXPos(), getYPos() };
			Vector2f posEnemy = { findEnemy->getXPos(), findEnemy->getYPos() };
			float distanse = distansePoints(posPerson, posEnemy);

			if (giveDamage && distanse <= SIZE_BLOCK * 2.5f) {
				animation.currentTimeFightAnimation = 0.f;

				currenMode = idEntityMode::walk;
				giveDamage = false;
				findEnemy->takeDamage(damage, currentItem);

				currentItem.currentToughness -= 1;
				breakItem(currentItem);
			}

		}
	}
}


void MainPerson::attractionEnemy(Enemy &enemy, world &world, TypeItem *typesItems, TypeUnlifeObject *typesObject,
																 const Time &deltaTime)
{
	Vector2f personPoint = { getXPos(), getYPos() };
	Vector2f enemyPoint;
	Vector2f movemoment;
	float distanse;

	enemyPoint = enemy.spriteEntity->getPosition();

	distanse = distansePoints(personPoint, enemyPoint);
	// Если увидел
	Directions &directions = enemy.directions;
	entityAnimation &animation = enemy.animation;

	float radiuseView = enemy.type->view.radiuseView;
	bool feelEnemy = enemy.type->view.feelEnemy;

	bool onLevelEnemy = currentLevelFloor == enemy.currentLevelFloor;
	bool onLevel = onLevelEnemy || feelEnemy;
	if (distanse <= radiuseView && onLevel) {

		movemoment = vectorDirection(enemyPoint, personPoint);

		bool canPanic = enemy.type->converse.canPanic;

		if (enemy.health.currentHealth < (enemy.health.maxHealth / 4)) {
			enemy.currenMode = idEntityMode::panic;
			if (canPanic) {
				movemoment = { -movemoment.x, -movemoment.y };
				enemy.choiceDirections(movemoment);

				enemy.animation.currentTimeFightAnimation = 0.f;
				step.currentTime = 0;
			}
		}
		else
		{
			enemy.currenMode = idEntityMode::fight;
		}
		


		enemy.defineDirectionLook(movemoment);


		if (feelEnemy != true)
			enemy.checkBlock(world.field);


		if (enemy.currenMode == idEntityMode::fight) {

			enemy.choiceDirections(movemoment);
			step.currentTime = 0;
			Item &itemEnemy = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];

			if (enemy.wasCollision) {

				if (!onLevelEnemy && feelEnemy) {
					Vector3i posEnemy = { int(enemy.getXPos() / SIZE_BLOCK),
					int(enemy.getXPos() / SIZE_BLOCK),
					enemy.collision.level };
					enemy.findLadder(world, typesItems, posEnemy);
				}


				String nameCurrentItem = itemEnemy.typeItem->features.name;
				String nameEmptyItem = founds.emptyItem->typeItem->features.name;

				bool isLadder = itemEnemy.typeItem->features.category == idCategoryItem::block;
				bool isNotEmpty = nameCurrentItem != nameEmptyItem;
				if (isNotEmpty && onLevelEnemy) {
					enemy.choiceBlock(world, typesItems);
				} else if (isNotEmpty && isLadder) {
					enemy.buildLadder(world, typesItems, typesObject);
				}

			} else {

				bool noNearFight = distanse >= SIZE_BLOCK;
				if (noNearFight) {
					enemy.animation.currentTimeFightAnimation = 0.f;
				} else if (onLevelEnemy) {
					enemy.currenMode = idEntityMode::atack;

					enemy.animation.currentTimeFightAnimation += deltaTime.asSeconds();
					if (enemy.animation.currentTimeFightAnimation > enemy.animation.timeFightAnimation) {
						enemy.animation.currentTimeFightAnimation = 0.f;

						enemy.currenMode = idEntityMode::fight;
						enemy.giveDamage = false;
						givenForPersonDamage(enemy);

						itemEnemy.currentToughness -= 1;
						if (itemEnemy.currentToughness < 1) {
							redefineType(itemEnemy, typesItems, -itemEnemy.typeItem->features.id);
						}
					}

					directions.directionWalk = NONE_DIRECTION;
				}

			}


		}

	}

}
	

////////////////////////////////////////////////////////////////////

void MainPerson::useItem(world &world, listDestroyObjectsAndBlocks& listDestroy, const Time &deltaTime,
												 TypeItem *typesItems, TypeUnlifeObject *typesUnlifeObjects, Event &event, float xMouse, float yMouse)
{
	Field &field = world.field;
	vector<Item> &items = *world.items;
	vector<UnlifeObject> &unlifeObjects = *world.unlifeObjects;
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];



	int x = xMouse / SIZE_BLOCK;
	int y = yMouse / SIZE_BLOCK;
	founds.currentTarget = { x, y };

	bool isEnemy = findEnemy != emptyEnemy;
	bool isAtack = event.key.code == Mouse::Left;
	if (isEnemy && isAtack) {

		if (isInUseField(xMouse, yMouse, true)) {
			if (findEnemy->currentLevelFloor == currentLevelFloor) {

				if (animation.currentTimeFightAnimation == 0.f) {
					currenMode = idEntityMode::atack;
				}

			}

		}


	}
	else {

		//currenMode = idEntityMode::walk;

		String* listObjects;
		wchar_t* listBlocks;
		int sizeListObjects;

		bool findTool = true;

		int category = currentItem.typeItem->features.category;
		switch (category) {
		case idCategoryItem::backhoe:
		case idCategoryItem::pickax:
		case idCategoryItem::axe:
			if (isInUseField(xMouse, yMouse, true)) {
				int level;
				defineLevel(level, event);

				int x = founds.currentTarget.x;
				int y = founds.currentTarget.y;

				Vector3i pos = { x, y, level };
				useTool(pos, world, currentItem, typesItems);
			}
			break;
			////////////////////////////////////////////////////////////////////////
			// Блок и неживой объект
		case idCategoryItem::block:
		case idCategoryItem::unlifeObject:
			if (isInUseField(xMouse, yMouse, false)) {
				int level;
				defineLevel(level, event);

				int x = founds.currentTarget.x;
				int y = founds.currentTarget.y;
				Vector3i pos = { x, y, level };


				useBlock(pos, world,
								 currentItem, typesItems,
								 typesUnlifeObjects);
			}
			break;
			////////////////////////////////////////////////////////////////////////
		case idCategoryItem::food:
			useAsFood(currentItem, event);
			break;
		case idCategoryItem::bukketWithWater:
			useAsBukketWithWater(currentItem, typesItems, event, field);
			break;
		case idCategoryItem::bottleWithWater:
			useAsBottleWithWater(currentItem, typesItems, event);
			break;
		case idCategoryItem::bukketEmpty:// ИСПРАВЬ
			if (isInUseField(xMouse, yMouse, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBukket(currentItem, typesItems, field, level);
			}
			break;
		case idCategoryItem::bottleEmpty:// ИСПРАВЬ
			if (isInUseField(xMouse, yMouse, true)) {
				int level;
				defineLevel(level, event);
				useAsEmptyBottle(currentItem, typesItems, field, level);
			}
			break;
		case idCategoryItem::other:
			break;
		default:
			break;
		}
	}

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

// Возможно пригодится (не ВКЛЮЧЕНА)
void MainPerson::viewmap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view->move(0.1*time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view->move(0, 0.1*time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view->move(-0.1*time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view->move(0, -0.1*time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
	}

}
// Возможно пригодится (не ВКЛЮЧЕНА)
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