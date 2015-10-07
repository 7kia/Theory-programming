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
// Виды объектов
void TypeUnlifeObject::Init(String filenameTexture, char *typeName, int w, int h, int pixelX, int pixelY) {
	textureObject = new Texture;

	// Задание размера
	height = h;
	width = w;

	pixelPosX = pixelX;
	pixelPosY = pixelY;

	// Текстура
	textureObject->loadFromFile(filenameTexture);

	// Звуки 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void TypeUnlifeObject::InitAlternate(int w, int h, int pixelX, int pixelY) {
	// Задание размера
	heightAlternative = h;
	widthAlternative = w;

	pixelXAlternative = pixelX;
	pixelYAlternative = pixelY;
}
////////////////////////////////////////////////////////////////////