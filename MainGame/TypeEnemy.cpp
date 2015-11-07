#include "TypeEnemy.h"
#include "EntityVar.h"
#include "Recourses.h"
using namespace sf;
using namespace std;

void initializeTypeEnemy(TypeEnemy *typesEnemy, dataSound &databaseSound)
{
	////////////////////////////////////////////////////////////////
	// Волк
	TypeEnemy* typeEnemy = &typesEnemy[idEnemy::wolfEnemy];

	String texturePath = texturePaths[idTexturePaths::wolf];
	String name = "Wolf";

	objectDropItems drop;
	drop.addItem(1, 4, idItem::rawMeatWolfItem);

	typeEnemy->size.init(WIDTH_WOLF, HEIGHT_WOLF, 0, 0);
	typeEnemy->protection.init(1.5f, 1.f);
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(100, 25, 0);
	typeEnemy->damage.init(5, 0, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->InitOtherFeatures(texturePath, name, databaseSound, AMOUNT_WOLF_SLOTS, RADIUSE_VIEW);

	drop.clear();
	////////////////////////////////////////////////////////////////
	// Волк
	typeEnemy = &typesEnemy[idEnemy::skeletEnemy];

	texturePath = texturePaths[idTexturePaths::skelet];
	name = "Skelet";

	drop.addItem( 1, 2, idItem::dirtItem );

	typeEnemy->size.init(WIDTH_SKELET, HEIGHT_SKELET, 0, 0);
	typeEnemy->protection.init(0.f, 1.f);
	typeEnemy->step.init(SPEED_ENTITY);
	typeEnemy->features.init(75, 0, 0);
	typeEnemy->damage.init(0, 5, 1.f);
	typeEnemy->drop.init(drop);
	typeEnemy->InitOtherFeatures(texturePath, name, databaseSound, AMOUNT_SKELET_SLOTS, RADIUSE_VIEW);

	drop.clear();
	////////////////////////////////////////////////////////////////
}

void enemyFeatures::init(int health, int stamina, int mana)
{
	maxHealth = health;
	maxMana = mana;
	maxStamina = stamina;
}

void TypeEnemy::InitOtherFeatures(sf::String texturePath, sf::String nameEnemy, dataSound &databaseSound,
																	int amountEnemySlots, float view)
{
	textureEntity = new Texture;
	textureEntity->loadFromFile(texturePath);

	amountSlots = amountEnemySlots;

	name = nameEnemy;

	radiusUse = 1;
	radiuseView = view;

	// TODO
	soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

}
