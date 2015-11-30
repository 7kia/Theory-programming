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
	stepGrass1Sound,
	stepStone1Sound,
	drop1Sound,
	punchBody1Sound,
	metalPunchBody1Sound,
	luggage1Sound,
	itemChoiseIdSound,
	skeletonDeathSound,


	chopp1Sound,
	treeDropSound,
	amountSoundSound
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

const sf::String soundPaths[idSoundPaths::amountSoundSound]
{
	"recourses\\sounds\\step\\grass1.ogg",
	"recourses\\sounds\\step\\stone1.ogg",
	"recourses\\sounds\\drop_1.ogg",
	"recourses\\sounds\\punch_body1.ogg",
	"recourses\\sounds\\metal_punch_body1.ogg",
	"recourses\\sounds\\luggage1.ogg",
	"recourses\\sounds\\item_choose.ogg",
	"recourses\\sounds\\skeleton_death.ogg",

	"recourses\\sounds\\chopper1.ogg",
	"recourses\\sounds\\wood_drop1.ogg"


	
};
