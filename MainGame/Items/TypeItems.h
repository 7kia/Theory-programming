#pragma once
#include <SFML\Graphics.hpp>

#include "../ListObjectsAndBlocks.h"
#include  "../Shoots/TypeShoots.h"
#include "../Sounds/Sound.h"
#include "../structGame/CommonStructs.h"

typedef enum
{
	idBlockForUse,
	idUnlideOnjectForUse,
	idAddShoot,
	amountIdCreateObjects
} idCreateObjects;

struct featuresItem
{
	sf::String name;
	int category;
	int id;
	bool isDestroy;
	int toughness;// прочность
	bool isCutting;
	void init(sf::String nameItem, int idItem, int idCategory, bool cutting);
	void defineToughness(bool destroy, int toughnessItem);
};

struct destroyObjectsAndBlocks
{
	std::vector<sf::String> *objects = nullptr;
	int amountObjects;

	std::vector<wchar_t> *blocks = nullptr;
	void init(std::vector<sf::String> *namesObjects, std::vector<wchar_t> *charBlocks);
};

struct TypeItem {
public:
	// Текструра
	sf::Texture* textureItem;
	sf::Texture* textureItemForUse;

	int maxAmount;
	featuresItem features;

	std::vector<int> *destroy;
	void initListDestroy(std::vector<int> &idsNature);


	featuresSprite sizeMain;
	featuresSprite sizeAlternative;
	int damageItem[amountTypeDamage];
	int idAdd[amountIdCreateObjects];
	void initIdsAddObject(int idBlock , int idObject, int idShoot);


	void Init(sf::String filenameTexture, featuresItem featuresAddItem,
						featuresSprite featuresSprite);
	void InitForUse(sf::String filenameTextureForUse, featuresSprite features);
};

void initializeTypesItem(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);

void initStoneBlock(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
void initWoodBlock(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
void initSeadling(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
void initGroundBlock(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
void initWeapon(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
void initDistanseWeapon(TypeItem *typesItem , listDestroyObjectsAndBlocks &list);
void initTools(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
void initFoods(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
void initPotions(TypeItem *typesItem , listDestroyObjectsAndBlocks &list);
void initTraps(TypeItem *typesItem , listDestroyObjectsAndBlocks &list);
void initEmptyItem(TypeItem *typesItem,  listDestroyObjectsAndBlocks &list);
