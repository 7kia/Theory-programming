#pragma once
#include <SFML\Graphics.hpp>
// PATHs

typedef enum {
	mainPersonPath,
	wolfPath ,
	skeletPath ,

	mapFloorPath ,
	mapWallPath ,

	TreesPath ,
	destroyBlockPath ,

	infoSelectBlockPath ,
	widgetsPath ,
	barsPath ,
	inventoryPath ,

	itemsPath ,
	bulletPath,

	awardGuiPath ,
	menuGuiPath ,
	amountTexturePaths
} idTexturePaths;

typedef enum {
	stepGrass1Sound,
	stepStone1Sound,

	drop1Sound,

	skeletonDeathSound,
	wolfDeathSound,

	punchBody1Sound,
	metalPunchBody1Sound,
	chopp1Sound,
	treeDropSound,
	forage1Sound,

	hitGroundSound,
	hitSandSound,
	hitStoneSound,

	waveEndSound,
	levelUpSound,
	itemChoiseIdSound,
	luggage1Sound,
	buttonClickSound,

	amountSoundSound
} idSoundPaths;

typedef enum {
	DayMusic,
	NightMusic,
	amountMusicPaths
} idMusicPaths;

const sf::String texturePaths[idTexturePaths::amountTexturePaths] =
{
	"recourses\\images\\entity\\mainPerson.png",
	"recourses\\images\\entity\\wolf.png",
	"recourses\\images\\entity\\skeleton.png",

	"recourses\\images\\blocks\\mapFloor.png",
	"recourses\\images\\blocks\\mapWall.png",

	"recourses\\images\\unlife\\Trees.png",
	"recourses\\images\\unlife\\destroyBlock.png",

	"recourses\\images\\gui\\InfoWindow.png",
	"recourses\\images\\gui\\widgets.png",
	"recourses\\images\\gui\\bars.png",
	"recourses\\images\\gui\\inventory.png",

	"recourses\\images\\things\\Items.png",
	"recourses\\images\\things\\bullet.png",

	"recourses\\images\\gui\\Award.png",
	"recourses\\images\\gui\\Menu.png"
};



const std::string pathToSounds = "recourses\\sounds\\";
const std::string soundPaths[idSoundPaths::amountSoundSound]
{
	pathToSounds + "step\\grass1.ogg",
	pathToSounds + "step\\stone1.ogg",

	pathToSounds + "Entity\\drop_1.ogg",

	pathToSounds + "Entity\\skeleton_death.ogg",
	pathToSounds + "Entity\\wolf_death.ogg",

	pathToSounds + "breaking\\punch_body1.ogg",
	pathToSounds + "breaking\\metal_punch_body1.ogg",
	pathToSounds + "breaking\\chopper1.ogg",
	pathToSounds + "breaking\\wood_drop1.ogg",
	pathToSounds + "breaking\\forage1.ogg",

	pathToSounds + "breaking\\hit_ground_1.ogg",
	pathToSounds + "breaking\\hit_sand_1.ogg",
	pathToSounds + "breaking\\hit_stone_1.ogg",

	pathToSounds + "GUI\\wave_end.ogg",
	pathToSounds + "GUI\\level_up.ogg",
	pathToSounds + "GUI\\item_choose.ogg",
	pathToSounds + "GUI\\luggage1.ogg",
	pathToSounds + "GUI\\button_click.ogg"

};

const std::string musicPaths[idMusicPaths::amountMusicPaths]
{
	pathToSounds + "Music\\Day_ambient.ogg",
	pathToSounds + "Music\\Night_ambient.ogg"
};
