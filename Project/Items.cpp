#include "Items.h"
#include "ItemsVar.h"

using namespace sf;
using namespace std;

void initializeItems(vector<Item> &items, TypeItem *typesItem, Item &emptyItem)
{

	Item* addItem = new Item;

	// ������ �������
	emptyItem.setType(typesItem[idItem::emptyItem]);// �������

	for (size_t i = idItem::airItem + 1; i < AMOUNT_TYPES_ITEM; i++) {
		for (size_t countItem = 1; countItem <= 4; countItem++)
		{
				addItem->setType(typesItem[i]);
		addItem->setPosition(i / 2 + 2, i % 3 + 2, 1);
		items.push_back(*addItem);
		// ���������� ��������	
		}

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

	typeItem = &type;

	mainSprite->setTexture(*type.textureItem);

	int pixelXPos = type.sizeMain.pixelPosX;
	int pixelYPos = type.sizeMain.pixelPosY;
	int width = type.sizeMain.width;
	int height = type.sizeMain.height;
	mainSprite->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	mainSprite->scale(scaleItems);// ��� ��������� ������� ����� ������
	mainSprite->setOrigin(width / 2, height / 2);

	/*
	spriteForUse = new Sprite;

	pixelXPos = type.sizeAlternative.pixelXForUse;
	pixelYPos = type.sizeAlternative.pixelYForUse;
	width = type.sizeAlternative.widthForUse;
	height = type.sizeAlternative.heightForUse;
	spriteForUse->setTexture(*type.textureItem);
	spriteForUse->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	spriteForUse->setOrigin(width / 2, height / 2);
	*/
	

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
	//direction = NONE_DIRECRION;
}