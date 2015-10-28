#pragma once
#include <SFML/Audio.hpp>
#include "GlobalVar.h"



typedef enum
{
	stepGrass,
	stepStone,
	stepWood,
	stepWool
} idSoundEntity;
const int sizeBuffer = sizeof(idSoundEntity);

typedef enum
{
	build,
	fight
} idModeEntity;

struct dataSound
{
	float *startSounds;
	sf::Sound *sounds;
	sf::SoundBuffer *soundBuffer;
};

void initializeSound(dataSound *soundBuffer);