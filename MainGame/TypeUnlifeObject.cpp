#include "TypeUnlifeObject.h"

using namespace sf;

void initializeTypeUnlifeObjects(TypesUnlifeObject *typesUnlifeObjects, dataSound &databaseSound) {
	typesUnlifeObjects->typeUnlifeObject = new TypeUnlifeObject[maxUnlifeObject];

	for (size_t i = 0; i < sizeof(idUnlifeObject); i++) {
		 
	}
	typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak].Init(texturePaths[idTexturePaths::Trees], "Oak", 47, 30, 0, 208);
	typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak].InitAlternate(136, 208, 0, 0);
	typesUnlifeObjects->countTypeObjects += 1;
}

////////////////////////////////////////////////////////////////////
// ���� ��������
void TypeUnlifeObject::Init(String filenameTexture, char *typeName, int w, int h, int pixelX, int pixelY) {
	textureObject = new Texture;

	// ������� �������
	height = h;
	width = w;

	pixelPosX = pixelX;
	pixelPosY = pixelY;

	// ��������
	textureObject->loadFromFile(filenameTexture);

	// ����� 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeUnlifeObject::InitAlternate(int w, int h, int pixelX, int pixelY) {
	// ������� �������
	heightAlternative = h;
	widthAlternative = w;

	pixelXAlternative = pixelX;
	pixelYAlternative = pixelY;
}
////////////////////////////////////////////////////////////////////