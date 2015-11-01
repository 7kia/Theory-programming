#pragma once
#include <SFML/Audio.hpp>

typedef enum
{
	stepGrass,
	stepStone,
	stepWood,
	stepWool
} idSoundEntity;
const int sizeBuffer = sizeof(idSoundEntity);

struct dataSound
{
	float *startSounds;
	sf::Sound *sounds;
	sf::SoundBuffer *soundBuffer;
};

void initializeSound(dataSound *soundBuffer);