#pragma once
#include "Sound.h"

#include "MainPerson.h"

#include "Font.h"
#include "GUI.h"

#include "EntityVar.h"


const sf::String TITLE_PROGRAM = "MainGame v1.5.12";


struct Game
{
	sf::RenderWindow window;

	GUI gui;
	TextGame textGame;

	MainPerson mainPerson;

	world world;
	////////////////////////////////////
	// Ходьба по карте(для противников
	float minTimeWalk = 4.f;
	float maxTimeWalk = 12.f;// TODO

	sf::Clock clock;

	dataSound databaseSound;

	unsigned int widthMainWindow = DEFAULT_WIDTH_WINDOW;
	unsigned int heightMainWindow = DEFAULT_HEIGHT_WINDOW;
};

void initializeGame(Game & game);

void initializeCategorysBreakingObject(Game &game);

void updateEntity(Game &game, const sf::Time deltaTime);
void renderEntitys(Game &game);

void renderUnlifeObjects(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);