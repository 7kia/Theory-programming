#pragma once
#include <SFML\Graphics.hpp>

#include "../ListObjectsAndBlocks.h"
#include "../Sounds/Sound.h"
#include "../structGame/CommonStructs.h"

struct typeDamageItem
{
	int cuttingDamage;// �������
	int crushingDamage;// ��������
	void init(int cut, int crush);
};

struct idCreateObjects
{
	int idBlockForUse;
	int idUnlideOnjectForUse;
	void init(int idBlock, int idObject);
};

struct featuresItem
{
	sf::String name;
	int category;
	int id;
	bool isDestroy;
	int toughness;// ���������
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
	// ���������
	sf::Texture* textureItem;
	sf::Texture* textureItemForUse;

	// ������ �� �����
	//Sound *soundsEntity[sizeBuffer];// �������
	int maxAmount;
	featuresItem features;

	destroyObjectsAndBlocks destroy;
	featuresSprite sizeMain;
	featuresSprite sizeAlternative;
	typeDamageItem damageItem;
	idCreateObjects idAdd;

	void Init(sf::String filenameTexture, featuresItem featuresAddItem,
						featuresSprite featuresSprite, idCreateObjects idCreated, typeDamageItem damage);
	void InitForUse(sf::String filenameTextureForUse, featuresSprite features);
};

void initializeTypesItem(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);

void initStoneBlock(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initWoodBlock(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initSeadling(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initGroundBlock(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initWeapon(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initTools(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initFoods(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initHaveWater(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
void initEmptyItem(TypeItem *typesItem, listDestroyObjectsAndBlocks &list);
