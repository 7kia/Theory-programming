#pragma once
#include <SFML/Audio.hpp>
#include "GlobalVar.h"

#define sizeBuffer sizeof(idSoundEntity)

typedef enum
{
	stepGrass,
	stepStone,
	stepWood,
	stepWool
} idSoundEntity;

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