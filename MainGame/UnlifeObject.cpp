#include "UnlifeObject.h"

void initializeUnlifeObjects(UnlifeObjects *unlifeObjects, dataSound &databaseSound)
{
	unlifeObjects->unlifeObject = new UnlifeObject[maxUnlifeObject];
	unlifeObjects->unlifeObject[0].Init(pathTrees, 136, 208, 0, 0);
	unlifeObjects->unlifeObject[0].setPosition(200.f, 200.f, 1);
	unlifeObjects->countObjects += 1;

	unlifeObjects->unlifeObject[unlifeObjects->countObjects].Init(pathTrees, 136, 208, 0, 0);
	unlifeObjects->unlifeObject[unlifeObjects->countObjects].setPosition(400.f, 300.f, 1);
	unlifeObjects->countObjects += 1;

}

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

void UnlifeObject::Init(const char * filenameTexture, int w, int h, int pixelX, int pixelY)
{
	spriteObject = new Sprite;
	textureObject = new Texture;

	// Задание размера

	height = h;
	width = w;

	// Текстура
	textureObject->loadFromFile(filenameTexture);
	spriteObject->setTexture(*textureObject);
	spriteObject->setTextureRect(IntRect(pixelX, pixelY, width, height));

	// Звуки 
	//mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	//mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];
};

void UnlifeObject::setPosition(float xPos, float yPos, int Level)
{
	// Позиция и направление
	currentLevel = Level;
	spriteObject->setOrigin(width / 2, height / 2);
	spriteObject->setPosition(xPos, yPos);
	direction = NONE;
}