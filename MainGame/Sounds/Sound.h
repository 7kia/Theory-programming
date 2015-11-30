#pragma once
#include <SFML/Audio.hpp>
#include "../Recourses.h"

const float minDistanse = 300.f;

const int sizeBuffer = amountSoundSound;

struct dataSound
{
	float startSounds[sizeBuffer];
	sf::Sound sounds[sizeBuffer];
	sf::SoundBuffer soundBuffer[sizeBuffer];
	sf::Sound globalSound;

	dataSound();
	void initSound(int id, const std::string *paths, float start);
};

static dataSound *sounds;

void playGlobalSound(const int idSound, dataSound &soundBase);
void playSound(const int idSound, dataSound& soundBase, sf::Sound &sound, sf::Vector2f pos);
