#include "UnlifeObject.h"

using namespace sf;

void initializeTypeUnlifeObjects(TypesUnlifeObject *typesUnlifeObjects, dataSound &databaseSound)
{
	typesUnlifeObjects->typeUnlifeObject = new TypeUnlifeObject[maxUnlifeObject];
	typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak].Init(pathTrees, "Oak", 136, 208, 0, 0);
	typesUnlifeObjects->countTypeObjects += 1;
}

void initializeUnlifeObjects(UnlifeObjects *unlifeObjects, TypesUnlifeObject *typesUnlifeObjects)
{
	unlifeObjects->unlifeObject = new UnlifeObject[maxUnlifeObject];

	unlifeObjects->unlifeObject[0].setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak]);
	unlifeObjects->unlifeObject[0].setPosition(200.f, 200.f, 1);
	unlifeObjects->countObject += 1;

	unlifeObjects->unlifeObject[1].setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak]);
	unlifeObjects->unlifeObject[1].setPosition(500.f, 300.f, 1);
	unlifeObjects->countObject += 1;
}

////////////////////////////////////////////////////////////////////
// Виды объектов
void TypeUnlifeObject::Init(const char * filenameTexture, char *typeName, int w, int h, int pixelX, int pixelY)
{
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
////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////
// Анимация и озвучка объектов НЕРАБОТАЕТ пока
void UnlifeObject::update(const Time & deltaTime, dataSound &databaseSound)
{
	float pauseStep = 5, resetAnimation = 2;
}

void UnlifeObject::playSound(float time, float start, const int idSound)
{
	if (time == start)
	{
		//soundsEntity[idSound]->play();
	}
}

void UnlifeObject::resetTimeAnimation(float &time, float &reset)
{
	if (time > reset)
	{
		//time = 0;
	}
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Вспомагательные функции
float UnlifeObject::getXPos()
{
	return spriteObject->getPosition().x;
}

float UnlifeObject::getYPos()
{
	return spriteObject->getPosition().y;
}
////////////////////////////////////////////////////////////////////

void UnlifeObject::setType(TypeUnlifeObject &type)
{
	spriteObject = new Sprite;

	spriteObject->setTexture(*type.textureObject);
	spriteObject->setTextureRect(IntRect(type.pixelPosX, type.pixelPosY, type.width, type.height));

	spriteObject->setOrigin(type.width / 2, type.height / 2);
}

void UnlifeObject::setPosition(float xPos, float yPos, int Level)
{
	// Позиция и направление
	currentLevel = Level;
	spriteObject->setPosition(xPos, yPos);
	direction = NONE;
}