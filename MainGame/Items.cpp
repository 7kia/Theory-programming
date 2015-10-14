#include "Items.h"

using namespace sf;
using namespace std;

void initializeItems(list<Item> &items, TypesItem *typesItem, Item &emptyItem)
{

	Item* addItem = new Item[3];

	// Пустой предмет
	emptyItem.setType(typesItem->typesItem[idItem::emptyItem]);// ИСПРАВЬ

	addItem[0].setType(typesItem->typesItem[idItem::smallStoneItem]);
	addItem[0].setPosition(3, 3, 1);
	items.push_front(addItem[0]);

	addItem[1].setType(typesItem->typesItem[idItem::mushroom]);// ИСПРАВЬ
	addItem[1].setPosition(2, 3, 1);
	items.push_front(addItem[1]);

	delete[] addItem;
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
	isDestroy = type.isDestroy;

	//width = type.width;
	//height = type.height;

	mainSprite->setTexture(*type.textureItem);
	mainSprite->setTextureRect(IntRect(type.pixelPosX, type.pixelPosY, type.width, type.height));
	mainSprite->setScale(scaleItems);// Вне инвентаря предмет будет меньше

	spriteForUse->setTexture(*type.textureItem);
	spriteForUse->setTextureRect(IntRect(type.pixelXUse, type.pixelXUse, type.widthForUse, type.heightUse));

	mainSprite->setOrigin(type.width / 2, type.height / 2);
	spriteForUse->setOrigin(type.widthForUse / 2, type.widthForUse / 2);

	// Прочность 
	currentToughness = type.toughnessObject;
}

void Item::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	// Позиция и направление
	currentLevel = Level;
	mainSprite->setPosition(numberX, numberY);
	spriteForUse->setPosition(numberX, numberY - typeItem->heightUse / 2 + typeItem->height / 2);

	//direction = NONE;
}