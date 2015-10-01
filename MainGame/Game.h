#pragma once

#include "Map.h"
#include "Sound.h"
#include "MainPerson.h"

#include <math.h>

using namespace sf;

struct Game
{
	MainPerson mainPerson;//MainPerson.h
	Field field;//Map.h
	Clock clock;
	SoundBuffer soundBuffer[25];
	//Vector2f iso = { sqrt(2.f) / 2, sqrt(2.f) / 2 };
};

void initializeGame(Game & game);
void destroyGame(Game & game);
void initializeClock(Clock &clock);