#pragma once
#include <SFML\Graphics.hpp>
// PATHs

typedef enum {
	mainPerson,
	wolf,
	skelet,
	mapFloor,
	mapWall,
	Trees,
	infoSelectBlock,
	widgets,
	bars,
	inventory,
	items,
	amountTexturePaths
} idTexturePaths;

typedef enum {
	stepGrass1,
	stepStone1,
	amountSoundPaths
} idSoundPaths;

const sf::String texturePaths[idTexturePaths::amountTexturePaths] =
{
	"recourses\\images\\entity\\mainPerson.png",
	"recourses\\images\\entity\\wolf.png",
	"recourses\\images\\entity\\skeleton.png",
	"recourses\\images\\blocks\\mapFloor.png",
	"recourses\\images\\blocks\\mapWall.png",
	"recourses\\images\\unlife\\Trees.png",
	"recourses\\images\\gui\\InfoWindow.png",
	"recourses\\images\\gui\\widgets.png",
	"recourses\\images\\gui\\bars.png",
	"recourses\\images\\gui\\inventory.png",
	"recourses\\images\\things\\Items.png"
};

const sf::String soundPaths[idSoundPaths::amountSoundPaths] =
{
	"recourses\\sounds\\step\\grass1.ogg",
	"recourses\\sounds\\step\\stone1.ogg"
};
