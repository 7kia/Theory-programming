#pragma once
#include <SFML/Audio.hpp>
#include "../Recourses.h"

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
	float startSounds[sizeBuffer];
	sf::Sound sounds[sizeBuffer];
	sf::SoundBuffer soundBuffer[sizeBuffer];
};

void initializeSound(dataSound &soundBuffer);