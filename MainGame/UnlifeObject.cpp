#include "UnlifeObject.h"
#include "BlocksVar.h"
#include "UnlifeObjectVar.h"

using namespace sf;
using namespace std;

void initializeUnlifeObjects(vector<UnlifeObject> &unlifeObjects, TypesUnlifeObject *typesUnlifeObjects, UnlifeObject &emptyObject)
{
	//unlifeObjects->unlifeObject = new UnlifeObject[MAX_UNLIFE_OBJECT];

	//int &countObject = unlifeObjects->countObject;

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
	//*/
	

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

	//width = type.width;
	//height = type.height;

	spriteObject->setTexture(*type.textureObject);
	spriteObject->setTextureRect(IntRect(type.mainSize.pixelPosX, type.mainSize.pixelPosY,
															 type.mainSize.width, type.mainSize.height));
	spriteObject->setOrigin(type.mainSize.width / 2, type.mainSize.height / 2);


	transparentSpiteObject->setTexture(*type.textureObject);
	transparentSpiteObject->setTextureRect(IntRect(type.transparentSize.pixelPosX, type.transparentSize.pixelPosY,
																				 type.transparentSize.width, type.transparentSize.height));
	transparentSpiteObject->setOrigin(type.transparentSize.width / 2, type.transparentSize.height / 2);

	// Прочность 
	currentToughness = type.toughnessObject;
}

void UnlifeObject::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	// Позиция и направление
	currentLevel = Level;
	spriteObject->setPosition(numberX, numberY);
	transparentSpiteObject->setPosition(numberX, numberY - typeObject->transparentSize.width / 2
																			+ typeObject->transparentSize.height / 2);
	// TODO
	directionWalk = NONE_DIRECTION;
}