#include "Items.h"

using namespace sf;
using namespace std;

void initializeItems(list<Item> &items, TypesItem *typesItem, Item &emptyItem)
{

	Item* addItem = new Item;

	// Пустой предмет
	emptyItem.setType(typesItem->typesItem[idItem::emptyItem]);// ИСПРАВЬ

	for (size_t i = 0; i < 12; i++) {
		addItem->setType(typesItem->typesItem[idItem::stoneItem]);
		addItem->setPosition(3, 3, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::planksBlockItem]);
		addItem->setPosition(3, 4, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::dirtItem]);
		addItem->setPosition(3, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::grassItem]);
		addItem->setPosition(3, 4, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::glassBottleItem]);
		addItem->setPosition(2, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::glassbukketWithWater]);
		addItem->setPosition(1, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::sandItem]);
		addItem->setPosition(3, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::logOakItem]);
		addItem->setPosition(3, 1, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stonePickaxItem]);
		addItem->setPosition(2, 1, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stoneAxeItem]);
		addItem->setPosition(4, 1, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::ironBackHoerIte]);
		addItem->setPosition(2, 3, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodLadderItem]);
		addItem->setPosition(3, 6, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stoneBrickItem]);
		addItem->setPosition(12, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodBukketItem]);
		addItem->setPosition(11, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodBukketWithWaterItem]);
		addItem->setPosition(10, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::woodClubItem]);
		addItem->setPosition(9, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::stoneKnifeItem]);
		addItem->setPosition(8, 2, 1);
		items.push_front(*addItem);

		addItem->setType(typesItem->typesItem[idItem::mushroomItem]);// ИСПРАВЬ
		addItem->setPosition(2, 3, 1);
		items.push_front(*addItem);
		// ДОБАВЛЕНИЕ ПРЕДМЕТА
	}

	delete addItem;
};


////////////////////////////////////////////////////////////////////
// Анимация и озвучка предметов НЕРАБОТАЕТ пока
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
// Вспомагательные функции
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
	mainSprite->scale(scaleItems);// Вне инвентаря предмет будет меньше

	spriteForUse->setTexture(*type.textureItem);
	spriteForUse->setTextureRect(IntRect(type.pixelXUse, type.pixelXUse, type.widthForUse, type.heightUse));

	mainSprite->setOrigin(type.width / 2, type.height / 2);
	spriteForUse->setOrigin(type.widthForUse / 2, type.widthForUse / 2);

	// Прочность 
	currentToughness = type.toughnessObject;
	maxToughness = type.toughnessObject;
}

void Item::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	// Позиция и направление
	currentLevel = Level;
	mainSprite->setPosition(numberX, numberY);
	spriteForUse->setPosition(numberX, numberY - typeItem->heightUse / 2 + typeItem->height / 2);

	//direction = NONE;// ИСПРАВЬ
}