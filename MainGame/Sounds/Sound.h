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
	luggage1IdSound,
	itemChoiseSound,
	amountIdSoundsEntity
} idSoundEntity;
const int sizeBuffer = amountIdSoundsEntity;

struct dataSound
{
	float startSounds[sizeBuffer];
	sf::Sound sounds[sizeBuffer];
	sf::SoundBuffer soundBuffer[sizeBuffer];
	sf::Sound globalSound;

	dataSound();
	void initSound(int id, sf::String path, float start);
};

void playSound(const int idSound, dataSound &soundBase, sf::Vector2f pos);
