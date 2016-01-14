#include "TypeShoots.h"

using namespace sf;
using namespace std;

void TypeShoot::init(int id, int idTexture, const String *pathTexture , sf::IntRect rectTexture , int *typesDamage)
{
	idType = id;
	textureShoot = new Texture;
	textureShoot->loadFromFile(pathTexture[idTexture] , rectTexture);
	for (int i = 0; i < amountTypeDamage; i++) {
		damageShoot[i] = typesDamage[i];
	};
	rectSprite = rectTexture;
}

TypeShoot::~TypeShoot()
{
	//delete textureShoot;// TODO : bug ?
}

void initTypeShoots(TypeShoot * typesShoots)
{
	int typeDamage[amountTypeDamage];

	typeDamage[cuttingDamage] = 16;
	typeDamage[crushingDamage] = 16;
	typeDamage[unlifeDamage] = 0;
	typesShoots[pistolShoot].init(pistolShoot, bulletPath,
																texturePaths, rectBullet, typeDamage);
	g_Functions::cleanIntArray(typeDamage , amountTypeDamage);

	typeDamage[cuttingDamage] = 32;
	typeDamage[crushingDamage] = 32;
	typeDamage[unlifeDamage] = 0;
	typesShoots[rifleShoot].init(rifleShoot, bulletPath ,
															 texturePaths , rectBullet, typeDamage);
	g_Functions::cleanIntArray(typeDamage , amountTypeDamage);

	typeDamage[cuttingDamage] = 50;
	typeDamage[crushingDamage] = 50;
	typeDamage[unlifeDamage] = 0;
	typesShoots[heavyRifleShoot].init(heavyRifleShoot , bulletPath,
																		texturePaths , rectBullet, typeDamage);
	g_Functions::cleanIntArray(typeDamage , amountTypeDamage);

	typeDamage[cuttingDamage] = 100;
	typeDamage[crushingDamage] = 100;
	typeDamage[unlifeDamage] = 0;
	typesShoots[mineExplosionShoot].init(mineExplosionShoot, mineExplosionPath ,
																			 texturePaths, rectMineExplosion, typeDamage);
	g_Functions::cleanIntArray(typeDamage , amountTypeDamage);

}