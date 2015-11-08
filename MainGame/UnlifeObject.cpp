#include "UnlifeObject.h"
#include "BlocksVar.h"
#include "UnlifeObjectVar.h"

using namespace sf;
using namespace std;

void initializeUnlifeObjects(vector<UnlifeObject> &unlifeObjects, TypesUnlifeObject *typesUnlifeObjects, UnlifeObject &emptyObject)
{
	UnlifeObject addObject;

	addObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oakGrow]);
	addObject.setPosition(4, 12, 1);
	unlifeObjects.push_back(addObject);

	///*
	addObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oakSmall]);
	addObject.setPosition(8, 12, 1);
	unlifeObjects.push_back(addObject);

	addObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oakSeadling]);
	addObject.setPosition(12, 13, 1);
	unlifeObjects.push_back(addObject);

	addObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::smallStone]);
	addObject.setPosition(8, 8, 1);
	unlifeObjects.push_back(addObject);

	emptyObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::empty]);
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
}

void UnlifeObject::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	int width = typeObject->mainSize.size.width;
	int height = typeObject->mainSize.size.height;
	currentLevel = Level;
	spriteObject->setPosition(numberX, numberY);
	transparentSpiteObject->setPosition(numberX, numberY - width / 2 - height / 2);

	// TODO
	directionWalk = NONE_DIRECTION;
}