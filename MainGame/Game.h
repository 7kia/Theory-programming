#pragma once

#include "Sound.h"
#include "Entity.h"

#include <math.h>

using namespace sf;

struct Game
{
	Entity *mainPerson;//Entity.h
	Field *field;//Map.h
	Clock *clock;
	dataSound *databaseSound;

	unsigned int widthMainWindow = 800;
	unsigned int heightMainWindow = 600;

	//SoundBuffer soundBuffer[globalSizeSoundBuffer];
	//Sound sounds[globalAmountSounds];
	//Vector2f iso = { sqrt(2.f) / 2, sqrt(2.f) / 2 };
};

void initializeGame(Game & game);
void destroyGame(Game & game);
void initializeClock(Clock &clock);