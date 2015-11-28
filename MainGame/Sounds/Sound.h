#pragma once
#include <SFML/Audio.hpp>
#include "../Recourses.h"

const float minDistanse = 300.f;

typedef enum
{
	stepGrass,
	stepStone,
	dropSound,
	punchBody1Id,
	metalPunchBody1Id,
	amountIdSoundsEntity
} idSoundEntity;
const int sizeBuffer = amountIdSoundsEntity;

struct dataSound
{
	float startSounds[sizeBuffer];
	sf::Sound sounds[sizeBuffer];
	sf::SoundBuffer soundBuffer[sizeBuffer];

	dataSound();
	void initSound(int id, sf::String path, float start);
};
