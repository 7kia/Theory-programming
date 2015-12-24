#include "../World.h"


using namespace sf;
using namespace std;

void dropBlock(world &world, Vector3i &pos, int level)
{
	vector<Item> &items = world.items;
	TypeItem *typesItems = world.typesObjects.typesItem;
	Field &field = world.field;

	Item* addItem = new Item;

	wchar_t &block = field.dataMap[pos.z][pos.y][pos.x];

	int id = field.findIdBlock(block);
	if (id > idItem::airItem) {
		addItem->setType(typesItems[id]);

		Vector3i posAdd = { pos.x + 1, pos.y + 1, level };
		addItem->setPosition(posAdd);
		items.push_back(*addItem);
	}

	delete addItem;
}

void initializeItems(vector<Item> &items, TypeItem *typesItem, Item &emptyItem)
{

	Item* addItem = new Item;

	emptyItem.setType(typesItem[idItem::emptyItem]);

	for (int i = idItem::airItem + 1; i < AMOUNT_TYPES_ITEM; i++) {
		for (int countItem = 1; countItem <= 4; countItem++) {
			addItem->setType(typesItem[i]);
			Vector3i posAdd = { CENTER_WORLD.x + i / 2 + 2, CENTER_WORLD.y + i % 3 + 2, 2 };

			addItem->setPosition(posAdd);
			items.push_back(*addItem);
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

	// TODO
	int pixelXPos = type.sizeMain.pixPos.x;
	int pixelYPos = type.sizeMain.pixPos.y;
	int width = type.sizeMain.size.width;
	int height = type.sizeMain.size.height;
	mainSprite->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	mainSprite->scale(scaleOutItems);// Вне инвентаря предмет будет меньше
	mainSprite->setOrigin(float(width / 2), float(height / 2));


	spriteForUse = new Sprite;

	pixelXPos = type.sizeAlternative.pixPos.x;
	pixelYPos = type.sizeAlternative.pixPos.y;
	width = type.sizeAlternative.size.width;
	height = type.sizeAlternative.size.width;
	spriteForUse->setTexture(*type.textureItem);
	spriteForUse->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	spriteForUse->setOrigin(float(width / 2), float(height / 2));

	

	maxToughness = type.features.toughness;
	currentToughness = maxToughness;
}

void Item::setPosition(Vector3i pos)
{
	float numberX = float(pos.x * SIZE_BLOCK - SIZE_BLOCK / 2);
	float numberY = float(pos.y * SIZE_BLOCK - SIZE_BLOCK / 2);

	currentLevel = pos.z;
	mainSprite->setPosition(numberX, numberY);
}