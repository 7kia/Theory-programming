#include "Items.h"
#include "ItemsVar.h"

using namespace sf;
using namespace std;

void initializeItems(vector<Item> &items, TypesItem *typesItem, Item &emptyItem)
{

	Item* addItem = new Item;

	// ������ �������
	emptyItem.setType(typesItem->typesItem[idItem::emptyItem]);// �������

	for (size_t i = 0; i < 3; i++) {
		addItem->setType(typesItem->typesItem[idItem::stoneItem]);
		addItem->setPosition(2, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::planksBlockItem]);
		addItem->setPosition(2, 3, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::dirtItem]);
		addItem->setPosition(3, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::grassItem]);
		addItem->setPosition(3, 4, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::glassBottleItem]);
		addItem->setPosition(3, 5, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::glassbukketWithWater]);
		addItem->setPosition(4, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::sandItem]);
		addItem->setPosition(4, 3, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::logOakItem]);
		addItem->setPosition(4, 4, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stonePickaxItem]);
		addItem->setPosition(5, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stoneAxeItem]);
		addItem->setPosition(5, 3, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::ironBackHoerIte]);
		addItem->setPosition(5, 4, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodLadderItem]);
		addItem->setPosition(6, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stoneBrickItem]);
		addItem->setPosition(6, 3, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodBukketItem]);
		addItem->setPosition(6, 4, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodBukketWithWaterItem]);
		addItem->setPosition(7, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodClubItem]);
		addItem->setPosition(7, 3, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stoneKnifeItem]);
		addItem->setPosition(7, 4, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::mushroomItem]);// �������
		addItem->setPosition(8, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::rawMeatWolfItem]);// �������
		addItem->setPosition(8, 3, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::roastMeatWolfItem]);// �������
		addItem->setPosition(8, 4, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::seadlingOakItem]);// �������
		addItem->setPosition(9, 2, 1);
		items.push_back(*addItem);

		addItem->setType(typesItem->typesItem[idItem::appleItem]);// �������
		addItem->setPosition(9, 3, 1);
		items.push_back(*addItem);
		// ���������� ��������
	}

	delete addItem;
};


////////////////////////////////////////////////////////////////////
// �������� � ������� ��������� ���������� ����
void Item::update(const Time & deltaTime, dataSound &databaseSound)
{
	float pauseStep = 5, resetAnimation = 2;
}

void Item::playSound(float time, float start, const int idSound)
{
	if (time == start) {
		//soundsEntity[idSound]->play();
	}
}

void Item::resetTimeAnimation(float &time, float &reset)
{
	if (time > reset) {
		//time = 0;
	}
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// ��������������� �������
float Item::getXPos()
{
	return mainSprite->getPosition().x;
}

float Item::getYPos()
{
	return mainSprite->getPosition().y;
}
////////////////////////////////////////////////////////////////////

void Item::setType(TypeItem &type)
{
	mainSprite = new Sprite;
	spriteForUse = new Sprite;

	typeItem = &type;
	categoryItem = type.category;
	isDestroy = type.isDestroy;

	cuttingDamage = type.cuttingDamage;
	crushingDamage = type.crushingDamage;

	mainSprite->setTexture(*type.textureItem);
	mainSprite->setTextureRect(IntRect(type.pixelPosX, type.pixelPosY, type.width, type.height));
	mainSprite->scale(scaleItems);// ��� ��������� ������� ����� ������

	spriteForUse->setTexture(*type.textureItem);
	spriteForUse->setTextureRect(IntRect(type.pixelXUse, type.pixelXUse, type.widthForUse, type.heightUse));

	mainSprite->setOrigin(type.width / 2, type.height / 2);
	spriteForUse->setOrigin(type.widthForUse / 2, type.widthForUse / 2);

	// ��������� 
	currentToughness = type.toughnessObject;
	maxToughness = type.toughnessObject;
}

void Item::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	// ������� � �����������
	currentLevel = Level;
	mainSprite->setPosition(numberX, numberY);
	spriteForUse->setPosition(numberX, numberY - typeItem->heightUse / 2 + typeItem->height / 2);

	//direction = NONE;// �������
}