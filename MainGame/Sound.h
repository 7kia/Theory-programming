#pragma once
#include <SFML/Audio.hpp>
#include "GlobalVar.h"

using namespace sf;

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
	Sound *sounds;
	SoundBuffer *soundBuffer;
};

void initializeSound(dataSound *soundBuffer);