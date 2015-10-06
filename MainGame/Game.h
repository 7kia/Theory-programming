#pragma once

#include "Sound.h"
#include "MainPerson.h"
#include "UnlifeObject.h"

#include <math.h>

struct Game
{
	Entity *entitys;//��������� ��������
	MainPerson *mainPerson;//MainPerson.h

	TypesUnlifeObject *typesUnlifeObject;
	UnlifeObjects *unlifeObjects;

	Field *field;//Map.h
	sf::Clock *clock;
	dataSound *databaseSound;

	int countUnlifeObject = 0;

	unsigned int widthMainWindow = 800;
	unsigned int heightMainWindow = 600;

	//SoundBuffer soundBuffer[globalSizeSoundBuffer];
	//Sound sounds[globalAmountSounds];
	//Vector2f iso = { sqrt(2.f) / 2, sqrt(2.f) / 2 };
};

void initializeGame(Game & game);
void destroyGame(Game & game);
void initializeClock(Clock &clock);