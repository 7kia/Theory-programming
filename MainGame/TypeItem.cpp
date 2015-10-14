#include "TypeItems.h"

using namespace sf;

void initializeTypesItem(TypesItem &typesItem, dataSound &databaseSound)
{
	typesItem.typesItem = new TypeItem[AMOUNT_TYPES_ITEM];

	typesItem.typesItem[idItem::smallStoneItem].Init(texturePaths[idTexturePaths::items], "Small stone", false, 0, WIDTH_SMALL_STONE, HEIGHT_SMALL_STONE, 0, 0);
	//typesItem.typesItem[idUnlifeObject::oak].InitForUse(texturePaths[idTexturePaths::items], 0, 0, 0, 0);
	typesItem.countTypeItem += 1;

	typesItem.typesItem[idItem::mushroom].Init(texturePaths[idTexturePaths::items], "Mushroom", true, 0, WIDTH_MUSHROOM, HEIGHT_MUSHROOM, PIXEL_X_MUSHROOM, PIXEL_Y_MUSHROOM);
	typesItem.countTypeItem += 1;

	typesItem.typesItem[idItem::emptyItem].Init(texturePaths[idTexturePaths::items], "Empty", true, 0, 0, 0, 0, 0);
	typesItem.countTypeItem += 1;

}

////////////////////////////////////////////////////////////////////
// ���� ��������
void TypeItem::Init(String filenameTexture, String typeName, bool canDestroy, int toughness, int w, int h, int pixelX, int pixelY)
{
	textureItem = new Texture;

	nameType = typeName;

	// ������� �������
	height = h;
	width = w;

	pixelPosX = pixelX;
	pixelPosY = pixelY;

	// ����������� ��� ���������������
	isDestroy = canDestroy;

	// ��������� 
	toughnessObject = toughness;

	// � ����������� ��������� �������� ���� ���������
	if (isDestroy == false) {
		toughness = 0;
	}

	// ��������
	textureItem->loadFromFile(filenameTexture);

	// ����� 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeItem::InitForUse(String filenameTextureForUse, int w, int h, int pixelX, int pixelY)
{
	textureItemForUse = new Texture;

	// ������� �������
	heightUse = h;
	widthForUse = w;

	pixelXUse = pixelX;
	pixelYUse = pixelY;
}
////////////////////////////////////////////////////////////////////