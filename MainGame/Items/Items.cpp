#include "../World.h"


using namespace sf;
using namespace std;

void dropBlock(world &world, Vector3i pos, int level)
{
	vector<Item> &items = *world.items;
	TypeItem *typesItems = world.typesObjects.typesItem;
	Field &field = world.field;

	Item* addItem = new Item;

	wchar_t &block = field.dataMap[pos.z][pos.y][pos.z];

	addItem->setType(typesItems[field.findIdBlock(block)]);
	addItem->setPosition(pos.x + 1, pos.y + 1, pos.z + 1);
	items.push_back(*addItem);

	delete addItem;
}

void initializeItems(vector<Item> &items, TypeItem *typesItem, Item &emptyItem)
{

	Item* addItem = new Item;

	// Пустой предмет
	emptyItem.setType(typesItem[idItem::emptyItem]);// ИСПРАВЬ

	for (size_t i = idItem::airItem + 1; i < AMOUNT_TYPES_ITEM; i++) {
		for (size_t countItem = 1; countItem <= 4; countItem++)
		{
				addItem->setType(typesItem[i]);
		addItem->setPosition(CENTER_WORLD.x + i / 2 + 2, CENTER_WORLD.y + i % 3 + 2, 2);
		items.push_back(*addItem);
		// ДОБАВЛЕНИЕ ПРЕДМЕТА	
		}

	}

	delete addItem;
};


////////////////////////////////////////////////////////////////////
// Анимация и озвучка предметов НЕРАБОТАЕТ пока
void Item::update(const float deltaTime, dataSound &databaseSound)
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
	typeItem = &type;

	amount = 1;

	mainSprite = new Sprite;
	mainSprite->setTexture(*type.textureItem);

	int pixelXPos = type.sizeMain.pixPos.x;
	int pixelYPos = type.sizeMain.pixPos.y;
	int width = type.sizeMain.size.width;
	int height = type.sizeMain.size.height;
	mainSprite->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	mainSprite->scale(scaleOutItems);// Вне инвентаря предмет будет меньше
	mainSprite->setOrigin(width / 2, height / 2);

	///*
	spriteForUse = new Sprite;

	pixelXPos = type.sizeAlternative.pixPos.x;
	pixelYPos = type.sizeAlternative.pixPos.y;
	width = type.sizeAlternative.size.width;
	height = type.sizeAlternative.size.width;
	spriteForUse->setTexture(*type.textureItem);
	spriteForUse->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	spriteForUse->setOrigin(width / 2, height / 2);
	//*/
	

	maxToughness = type.features.toughness;
	currentToughness = maxToughness;
}

void Item::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	currentLevel = Level;
	mainSprite->setPosition(numberX, numberY);
	// TODO
	//spriteForUse->setPosition(numberX, numberY - typeItem->sizeAlternative.heightForUse / 2 + typeItem->sizeMainSprite.height / 2);
	//directionWalk = NONE_DIRECRION;
}