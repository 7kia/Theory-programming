#include "UnlifeObject.h"

using namespace sf;
using namespace std;

void initializeUnlifeObjects(vector<UnlifeObject> &unlifeObjects, TypeUnlifeObject *typesUnlifeObjects, UnlifeObject &emptyObject)
{
	UnlifeObject addObject;

	addObject.setType(typesUnlifeObjects[idUnlifeObject::oakGrow]);
	addObject.setPosition(4, 12, 1);
	unlifeObjects.push_back(addObject);

	///*
	addObject.setType(typesUnlifeObjects[idUnlifeObject::oakSmall]);
	addObject.setPosition(8, 12, 1);
	unlifeObjects.push_back(addObject);

	addObject.setType(typesUnlifeObjects[idUnlifeObject::oakSeadling]);
	addObject.setPosition(12, 13, 1);
	unlifeObjects.push_back(addObject);

	addObject.setType(typesUnlifeObjects[idUnlifeObject::appleSeadling]);
	addObject.setPosition(12, 8, 1);
	unlifeObjects.push_back(addObject);

	addObject.setType(typesUnlifeObjects[idUnlifeObject::smallStone]);
	addObject.setPosition(5, 11, 1);
	unlifeObjects.push_back(addObject);

	emptyObject.setType(typesUnlifeObjects[idUnlifeObject::empty]);
}

////////////////////////////////////////////////////////////////////
// Анимация и озвучка объектов НЕРАБОТАЕТ пока
void UnlifeObject::update(const float deltaTime, dataSound &databaseSound)
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
	transparentSpiteObject = new Sprite;

	typeObject = &type;
	isDestroy = type.isDestroy;


	int width = type.mainSize.size.width;
	int height = type.mainSize.size.height;
	int pixelXPos = type.mainSize.pixPos.x;
	int pixelYPos = type.mainSize.pixPos.y;
	spriteObject->setTexture(*type.textureObject);
	spriteObject->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	spriteObject->setOrigin(width / 2, height / 2);

	width = type.transparentSize.size.width;
	height = type.transparentSize.size.height;
	pixelXPos = type.transparentSize.pixPos.x;
	pixelYPos = type.transparentSize.pixPos.y;
	transparentSpiteObject->setTexture(*type.textureObject);
	transparentSpiteObject->setTextureRect(IntRect(pixelXPos, pixelYPos, width, height));
	transparentSpiteObject->setOrigin(width / 2, height / 2);

	// Прочность 
	currentToughness = type.toughnessObject;

	timeLife = 0.f;
}

void UnlifeObject::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	int heightMain = typeObject->mainSize.size.height;
	int height = typeObject->transparentSize.size.height;
	currentLevel = Level;
	spriteObject->setPosition(numberX, numberY);
	transparentSpiteObject->setPosition(numberX, numberY - (height - heightMain) / 2);
}