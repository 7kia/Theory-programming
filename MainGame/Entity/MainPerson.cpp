#include "MainPerson.h"

using namespace sf;
using namespace std;

void world::initializePlayer(View &view , Listener &listener)
{
	mainPerson = &Enemys[ID_PLAYER_IN_LIST];


	Vector2f centerView = { float(CENTER_WORLD.x * SIZE_BLOCK),   float(CENTER_WORLD.y * SIZE_BLOCK) };
	view.setSize(float(DEFAULT_WIDTH_WINDOW), float(DEFAULT_HEIGHT_WINDOW));
	view.setCenter(centerView);

	listener.setUpVector(0.f, 1.f, 0.f);
	listener.setGlobalVolume(100.f);
}

void Entity::updateView(View &view , Listener &listener , RenderWindow &window)
{
	Vector2u sizeWindow = window.getSize();
	//sizeWindow.x /= 1.f;//SCALE_VIEW
	//sizeWindow.y /= 1.f;// TODO : increase zoom for camera, reason: small image
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

void Entity::updateAtack(world &world, const float deltaTime)
{
	bool isEnemy = founds.findEnemyFromList > -1;
	bool notMyself = founds.findEnemy != this;
	if (giveDamage && isEnemy && notMyself) {

		if (founds.findEnemy->isDeath) {
			killFindEnemy(world);
		}
		else {
			Item& currentItem = itemsEntity[idSelectItem];
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

	Vector2f posPerson = getPosition();
	Vector2f posEnemy = founds.findEnemy->getPosition();
	float distanse = distansePoints(posPerson, posEnemy);

	animation.updateFight(deltaTime, giveDamage, currenMode);
	if (giveDamage && distanse <= SIZE_BLOCK * 2.5f) {
		resetAtack();
		founds.findEnemy->takeDamage(damage, currentItem);
		playAtackSound(currentItem);
	}
}

void Entity::playSoundChoiseItem()
{
	int id = idSoundPaths::itemChoiseIdSound;
	::playSound(id, *soundBase, soundEntity, getPosition());
}

Item & Entity::getCurrentItem()
{
	return itemsEntity[idSelectItem];
}
