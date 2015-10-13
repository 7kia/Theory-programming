#include "UnlifeObject.h"

using namespace sf;
using namespace std;

void initializeUnlifeObjects(list<UnlifeObject> &unlifeObjects, TypesUnlifeObject *typesUnlifeObjects)
{
	//unlifeObjects->unlifeObject = new UnlifeObject[MAX_UNLIFE_OBJECT];

	//int &countObject = unlifeObjects->countObject;

	UnlifeObject addObject;

	addObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak]);
	addObject.setPosition(4, 12, 1);
	unlifeObjects.push_back(addObject);

	addObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak]);
	addObject.setPosition(12, 12, 1);
	unlifeObjects.push_back(addObject);

	addObject.setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::smallStone]);
	addObject.setPosition(8, 8, 1);
	unlifeObjects.push_back(addObject);
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
	spriteObject->setTextureRect(IntRect(type.pixelPosX, type.pixelPosY, type.width, type.height));

	transparentSpiteObject->setTexture(*type.textureObject);
	transparentSpiteObject->setTextureRect(IntRect(type.pixelXTransparent, type.pixelXTransparent, type.widthTransparent, type.heightTransparent));

	spriteObject->setOrigin(type.width / 2, type.height / 2);
	transparentSpiteObject->setOrigin(type.widthTransparent / 2, type.heightTransparent / 2);

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
	transparentSpiteObject->setPosition(numberX, numberY - typeObject->heightTransparent / 2 + typeObject->height / 2);

	direction = NONE;
}