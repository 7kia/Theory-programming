#include "UseBlocksAndObjects.h"

using namespace sf;
using namespace std;

void Entity::useBlock(Vector3i pos, world &world,
					  Item & currentItem)
{

	TypeUnlifeObject *typesUnlifeObjects = world.typesObjects.typesUnlifeObject;

	Field &field = world.field;
	vector<UnlifeObject> &unlifeObjects = world.unlifeObjects;

	bool useForAnyLevel = pos.z > -1;
	if (useForAnyLevel) {
		bool successfullUse;

		wchar_t *block = &field.dataMap[pos.z][pos.y][pos.x];

		int idUseBlock = currentItem.getIdAddObject(idBlockForUse);
		int idUseObject = currentItem.getIdAddObject(idUnlideOnjectForUse);

		bool isIdBlock = idUseBlock > -1;
		bool isAir = *block == field.charBlocks[idBlocks::air];
		if (isIdBlock && isAir) {
			*block = field.charBlocks[idUseBlock];
			successfullUse = true;
		}
		else if (idUseObject > -1) {
			UnlifeObject* addObject = new UnlifeObject;
			Vector3i posAdd = { pos.x + 1, pos.y + 1 , currentLevelFloor + 1 };

			addObject->setType(typesUnlifeObjects[idUseObject]);
			addObject->setPosition(posAdd);
			unlifeObjects.push_back(*addObject);

			delete addObject;
			successfullUse = true;
		}
		else {
			successfullUse = false;
		}


		if (successfullUse) {
			breakItem(currentItem);
		}
	}

}

void Entity::upgradeObject(UnlifeObject &object, world &world)
{
	redefineObject &redefine = object.typeObject->redefine;
	Sprite &spriteObject = *object.spriteObject;
	Vector2f currentPos = spriteObject.getPosition();
	Vector2i posOnMap = { int((currentPos.x + SIZE_BLOCK / 2) / SIZE_BLOCK),
												int((currentPos.y + SIZE_BLOCK / 2) / SIZE_BLOCK) };

	TypeUnlifeObject &nextType = world.typesObjects.typesUnlifeObject[redefine.id];

	Vector3i posItems = { posOnMap.x - 1, posOnMap.y - 1, currentLevelFloor + 1 };
	object.dropObject(posItems, world, true);

	Vector3i posObject = { posOnMap.x, posOnMap.y , object.currentLevel };
	object.setType(nextType);
	object.setPosition(posObject);
}


void Entity::useAsRifle(Item & currentItem , world & world)
{
	int idBullets = searchBulletInInventory();

	if (idBullets > RESET_VALUE) {
		int levelShooter = getLevelWall();
		int levelEnemy = getFindEntity().getLevelWall();

		bool isEnemyLowThatShooter = levelEnemy < levelShooter;
		bool enemyOnLevelShooter = (levelEnemy == levelShooter);

		float distanseInFloorXY = Math::distansePoints(getPosition() , getFindEntity().getPosition());
		bool blocksFloorNotCollisionWithFutureShoot = (isEnemyLowThatShooter
																									 && (distanseInFloorXY < DISTANSE_ATACK_FOR_HIGH_LEVEL));
		int levelShoot = levelShooter;

		if (enemyOnLevelShooter
				|| blocksFloorNotCollisionWithFutureShoot) {

			if (blocksFloorNotCollisionWithFutureShoot) {
				levelShoot = levelEnemy;
			}

			// Если понадобятся разные виды пуль
			//world.getTypeShoot(currentItem.getIdTypeShoot())
			createBullet(world.shoots , world.getTypeShoot(currentItem.getIdTypeShoot()) , levelShoot);
			::playSound(currentItem.getIdSoundShoot() , *soundBase ,
									soundEntity , currentItem.getPositionSprite());
			minusAmount(itemsEntity[idBullets]);
			currenMode = idEntityMode::atack;
		}


	}
	else
	{
		
	}
}

int Entity::searchBulletInInventory()
{
	Item *currentItem = &itemsEntity[0];
	int idBullet = getCurrentItem().getIdTypeBullet();// +idItem::heavyRifleItem - 1;
	for (int i = 0; i < getAmountSlots(); i++)
	{
		currentItem = &itemsEntity[i];
		if (currentItem->getIdType() == idBullet)
		{
			return i;
		}
	}
	return RESET_VALUE;
}
