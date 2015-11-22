#pragma once
#include "Entity/MainPerson.h"

#include "GUI and Fonts/Font.h"
#include "GUI and Fonts/GUI.h"

const sf::String TITLE_PROGRAM = "MainGame v1.6.6";

const int TIME_GENERATE_WAVE_ENEMYS = 10;
const int TIME_UPDATE_DIFFICULT = TIME_GENERATE_WAVE_ENEMYS * 2;


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

void updateEntity(Game &game, const float deltaTime);
void renderEntitys(Game &game);

void renderUnlifeObjects(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);