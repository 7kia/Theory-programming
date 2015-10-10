#include "UnlifeObject.h"

using namespace sf;


void initializeUnlifeObjects(UnlifeObjects *unlifeObjects, TypesUnlifeObject *typesUnlifeObjects)
{
	unlifeObjects->unlifeObject = new UnlifeObject[MAX_UNLIFE_OBJECT];

	int &countObject = unlifeObjects->countObject;

	unlifeObjects->unlifeObject[0].setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak]);
	unlifeObjects->unlifeObject[0].setPosition(4, 12, 1);
	countObject += 1;

	unlifeObjects->unlifeObject[countObject].setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::oak]);
	unlifeObjects->unlifeObject[countObject].setPosition(12, 12, 1);
	countObject += 1;

	unlifeObjects->unlifeObject[countObject].setType(typesUnlifeObjects->typeUnlifeObject[idUnlifeObject::smallStone]);
	unlifeObjects->unlifeObject[countObject].setPosition(8, 8, 1);
	countObject += 1;
}

////////////////////////////////////////////////////////////////////
// �������� � ������� �������� ���������� ����
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
// ��������������� �������
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

	// ��������� 
	currentToughness = type.toughnessObject;
}

void UnlifeObject::setPosition(int xPos, int yPos, int Level)
{
	float numberX = xPos * SIZE_BLOCK - SIZE_BLOCK / 2;
	float numberY = yPos * SIZE_BLOCK - SIZE_BLOCK / 2;

	// ������� � �����������
	currentLevel = Level;
	spriteObject->setPosition(numberX, numberY);
	transparentSpiteObject->setPosition(numberX, numberY - typeObject->heightTransparent / 2 + typeObject->height / 2);

	direction = NONE;
}