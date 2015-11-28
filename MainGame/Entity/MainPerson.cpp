#include "../Items/ItemsVar.h"


#include "EntityVar.h"

#include "UseItem.h"
using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound, emptyObjects &emptyObjects)
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

	// TODO
	float posX = float(CENTER_WORLD.x * SIZE_BLOCK);
	float posY = float(CENTER_WORLD.y * SIZE_BLOCK);
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

	mainPerson.soundBase = &databaseSound;

	mainPerson.initFounds(emptyObjects.emptyItem, emptyObjects.emptyObject, emptyObjects.emptyEnemy);
	emptyObjects.emptyEnemy.type->name;
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
	/*
	if (x < leftBorder) tempX = leftBorder;//убираем из вида левую сторону
	else if (x > rightBorder) tempX = rightBorder;//убираем из вида левую сторону
	if (y < topBorder) tempY = topBorder;//верхнюю сторону
	else if (y > lowBorder) tempY = lowBorder;//нижнюю сторону	
	//*/
	

	view->setCenter(tempX, tempY);
}

void MainPerson::initFounds(::Item &item, UnlifeObject& object, ::Enemy& enemy)
{
	founds.init(&item, &object);
	emptyEnemy = &enemy;
}

void MainPerson::givenForPersonDamage(Enemy &enemy)
{
	Item& itemEnemy = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];
	typeDamageItem damageEnemyItem = itemEnemy.typeItem->damageItem;
	DamageInputAndOutput &enemyDamege = enemy.damage;
	float cutDamage;
	float crashDamage;
	float multiplirer = enemyDamege.damageMultiplirer;

	cutDamage = multiplirer * (enemyDamege.cuttingDamage + damageEnemyItem.cuttingDamage);
	crashDamage = multiplirer * (enemyDamege.crushingDamage + damageEnemyItem.crushingDamage);
	//float cutDamage = damageMultiplirer * currentItem.cuttingDamage;
	//float crashDamage = damageMultiplirer * currentItem.crushingDamage;

	cutDamage *= protection.protectionCut;
	crashDamage *= protection.protectionCrash;

	damage.inputDamage = int(cutDamage + crashDamage);
	health.currentHealth -= damage.inputDamage;

	damage.inputDamage = 0;// TODO



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

void MainPerson::updateAtack(world &world, const float deltaTime)
{
	Item& currentItem = itemFromPanelQuickAccess[idSelectItem];


	bool isAtack = currenMode == idEntityMode::atack;
	bool isEnemy = findEnemyFromList > -1;
	if (isAtack && isEnemy) {

		if (findEnemy->isDeath) {

			findEnemy->EnemyDrop(world);
			world.Enemys->erase(world.Enemys->begin() + findEnemyFromList);

			animation.currentTimeFightAnimation = 0.f;

			currenMode = idEntityMode::walk;
			giveDamage = false;

		}
		else {
			currenMode = idEntityMode::atack;

			Vector2f posPerson = { getXPos(), getYPos() };
			Vector2f posEnemy = { findEnemy->getXPos(), findEnemy->getYPos() };
			float distanse = distansePoints(posPerson, posEnemy);

			if (giveDamage && distanse <= SIZE_BLOCK * 2.5f) {
				animation.currentTimeFightAnimation = 0.f;

				currenMode = idEntityMode::walk;
				giveDamage = false;
				findEnemy->takeDamage(damage, currentItem);

				
			}

		}


	}
}


void MainPerson::attractionEnemy(Enemy &enemy, world &world, const float deltaTime)
{
	typesObjectsInWorld &types = world.typesObjects;

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
		enemy.currenMode = idEntityMode::fight;

		movemoment = vectorDirection(enemyPoint, personPoint);
		enemy.checkLevelHealth(movemoment);
		enemy.defineDirectionLook(movemoment);

		// TODO
		bool isFight = enemy.currenMode == idEntityMode::fight;
		if (feelEnemy == false)
			enemy.checkBlock(world.field, distanse);

		isFight = enemy.currenMode == idEntityMode::fight;
		if (isFight) {

			enemy.choiceDirections(movemoment);
			step.currentTime = 0;
			Item &itemEnemy = enemy.itemFromPanelQuickAccess[enemy.idSelectItem];

			if (enemy.wasCollision) {

				enemy.directions.directionWalk = NONE_DIRECTION;
				if (!onLevelEnemy && feelEnemy) {
					Vector3i posEnemy = { int(enemy.getXPos() / SIZE_BLOCK),
						int(enemy.getXPos() / SIZE_BLOCK),
						enemy.collision.level };
					enemy.findLadder(world, posEnemy);


					String nameCurrentItem = itemEnemy.typeItem->features.name;
					String nameEmptyItem = founds.emptyItem->typeItem->features.name;

					bool isLadder = itemEnemy.typeItem->features.category == idCategoryItem::block;
					bool isNotEmpty = nameCurrentItem != nameEmptyItem;

					if (isNotEmpty && isLadder) {
						enemy.buildLadder(world);
					}
				}
				else if (feelEnemy) {
					enemy.choiceBlock(world);
				}




			} 
			else {

				bool noNearFight = distanse >= SIZE_BLOCK;
				if (noNearFight) {
					enemy.animation.currentTimeFightAnimation = 0.f;
				} else if (onLevelEnemy) {
					enemy.currenMode = idEntityMode::atack;

					enemy.animation.currentTimeFightAnimation += deltaTime;
					if (enemy.animation.currentTimeFightAnimation > enemy.animation.timeFightAnimation) {
						enemy.animation.currentTimeFightAnimation = 0.f;

						enemy.currenMode = idEntityMode::fight;
						enemy.giveDamage = false;
						givenForPersonDamage(enemy);

						itemEnemy.currentToughness -= 1;
						if (itemEnemy.currentToughness < 1) {
							redefineType(itemEnemy, world, -itemEnemy.typeItem->features.id);
						}
					}

					directions.directionWalk = NONE_DIRECTION;
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



	int x = int(pos.x / SIZE_BLOCK);
	int y = int(pos.y / SIZE_BLOCK);
	founds.currentTarget = { x, y };

	bool isEnemy = findEnemy != emptyEnemy;
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

/*
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

*/
// Возможно пригодится (не ВКЛЮЧЕНА)
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