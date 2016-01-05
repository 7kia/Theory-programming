#include "shoot.h"

using namespace sf;
using namespace std;

void TypeShoot::init(int id, const String *pathTexture , int *typesDamage)
{
	textureShoot = new Texture;
	textureShoot->loadFromFile(pathTexture[id] , rectBullet);
	for (int i = 0; i < amountTypeDamage; i++) {
		damageShoot[i] = typesDamage[i];
	};
}

TypeShoot::~TypeShoot()
{
	delete textureShoot;// TODO : bug ?
}

void initTypeShoots(TypeShoot * typesShoots)
{
	int typeDamage[amountTypeDamage];

	typeDamage[cuttingDamage] = 16;
	typeDamage[crushingDamage] = 16;
	typeDamage[unlifeDamage] = 0;
	typesShoots[pistolShoot].init(bulletPath, texturePaths, typeDamage);
	cleanIntArray(typeDamage , amountTypeDamage);

	typeDamage[cuttingDamage] = 32;
	typeDamage[crushingDamage] = 32;
	typeDamage[unlifeDamage] = 0;
	typesShoots[rifleShoot].init(bulletPath , texturePaths , typeDamage);
	cleanIntArray(typeDamage , amountTypeDamage);

	typeDamage[cuttingDamage] = 70;
	typeDamage[crushingDamage] = 70;
	typeDamage[unlifeDamage] = 0;
	typesShoots[heavyRifleShoot].init(bulletPath , texturePaths , typeDamage);
	cleanIntArray(typeDamage , amountTypeDamage);

}