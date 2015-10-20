#include "TypeUnlifeObject.h"

using namespace sf;

void initializeTypeUnlifeObjects(TypesUnlifeObject *typesUnlifeObjects, dataSound &databaseSound) {
	typesUnlifeObjects->typeUnlifeObject = new TypeUnlifeObject[AMOUNT_TYPES_UNLIFE_OBJECT];

	typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak].Init(texturePaths[idTexturePaths::Trees], "Oak", true, 2,  47, 30, 0, 208);
	typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak].InitTransparent(136, 208, 0, 0);
	typesUnlifeObjects->countTypeObjects += 1;

	typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::smallStone].Init(texturePaths[idTexturePaths::items], "SmallStone", false, 0, SIZE_ITEM, SIZE_ITEM, PIXEL_X_SMALL_STONE, PIXEL_Y_SMALL_STONE);
	//typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::smallStone].InitTransparent(136, 208, 0, 0);
	typesUnlifeObjects->countTypeObjects += 1;
}

////////////////////////////////////////////////////////////////////
// ���� ��������
void TypeUnlifeObject::Init(String filenameTexture, String typeName, bool canDestroy, int toughness, int w, int h, int pixelX, int pixelY) {
	textureObject = new Texture;

	name = typeName;

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
	textureObject->loadFromFile(filenameTexture);

	// ����� 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeUnlifeObject::InitTransparent(int w, int h, int pixelX, int pixelY) {
	// ������� �������
	heightTransparent = h;
	widthTransparent = w;

	pixelXTransparent = pixelX;
	pixelYTransparent = pixelY;
}
////////////////////////////////////////////////////////////////////