#include "UnlifeObject.h"

using namespace sf;
using namespace std;

void initializeUnlifeObjects(vector<UnlifeObject> &unlifeObjects, TypeUnlifeObject *typesUnlifeObjects, UnlifeObject &emptyObject)
{
	UnlifeObject addObject;

	Vector3i pos;
	pos.z = 2;

	pos = { 4, 12, 2 };
	addObject.setType(typesUnlifeObjects[idUnlifeObject::oakGrow]);
	addObject.setPosition(pos);
	unlifeObjects.push_back(addObject);

	///*
	pos = { 8, 12, 2 };
	addObject.setType(typesUnlifeObjects[idUnlifeObject::oakSmall]);
	addObject.setPosition(pos);
	unlifeObjects.push_back(addObject);

	pos = { 12, 13, 2 };
	addObject.setType(typesUnlifeObjects[idUnlifeObject::oakSeadling]);
	addObject.setPosition(pos);
	unlifeObjects.push_back(addObject);

	pos = { 12, 18, 2 };
	addObject.setType(typesUnlifeObjects[idUnlifeObject::appleSeadling]);
	addObject.setPosition(pos);
	unlifeObjects.push_back(addObject);

	pos = { 5, 11, 2 };
	addObject.setType(typesUnlifeObjects[idUnlifeObject::smallStone]);
	addObject.setPosition(pos);
	unlifeObjects.push_back(addObject);

	pos = { 5, 11, 2 };
	addObject.setType(typesUnlifeObjects[idUnlifeObject::wolfDeathEffect]);
	addObject.setPosition(pos);
	unlifeObjects.push_back(addObject);


	emptyObject.setType(typesUnlifeObjects[idUnlifeObject::empty]);
}

float UnlifeObject::getXPos()
{
	return spriteObject->getPosition().x;
}

float UnlifeObject::getYPos()
{
	return spriteObject->getPosition().y;
}

void UnlifeObject::setType(TypeUnlifeObject &type)
{
	spriteObject = new Sprite;
	transparentSpiteObject = new Sprite;

	typeObject = &type;
	isDestroy = type.isDestroy;

	setSpriteTexture(*spriteObject , type.mainSize , *type.textureObject);
	setSpriteTexture(*transparentSpiteObject , type.transparentSize , *type.textureObject);

	currentToughness = type.toughnessObject;

	timeLife = 0.f;
}

void UnlifeObject::setSpriteTexture(sf::Sprite& sprite, featuresSprite features, Texture &texture)
{
	int width = features.size.width;
	int height = features.size.height;
	int pixelXPos = features.pixPos.x;
	int pixelYPos = features.pixPos.y;
	spriteObject->setTexture(texture);
	spriteObject->setTextureRect(IntRect(pixelXPos , pixelYPos , width , height));
	spriteObject->setOrigin(float(width / 2) , float(height / 2));

}

void UnlifeObject::setPosition(Vector3i pos)
{
	float numberX = float(pos.x * SIZE_BLOCK - SIZE_BLOCK / 2);
	float numberY = float(pos.y * SIZE_BLOCK - SIZE_BLOCK / 2);

	int heightMain = typeObject->mainSize.size.height;
	int height = typeObject->transparentSize.size.height;
	currentLevel = pos.z;
	spriteObject->setPosition(numberX, numberY);
	transparentSpiteObject->setPosition(numberX, numberY - (height - heightMain) / 2);
}

void UnlifeObject::setMainColor(sf::Color color)
{
	spriteObject->setColor(color);
}

void UnlifeObject::setTransparentColor(sf::Color color)
{
	transparentSpiteObject->setColor(color);
}

bool UnlifeObject::isDestroyed()
{
	return currentToughness < 1;
}

sf::Vector2f UnlifeObject::getPosition()
{
	return{ getXPos(), getYPos() };
}