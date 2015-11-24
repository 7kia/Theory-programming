#pragma once
#include "Entity/MainPerson.h"

#include "GUI and Fonts/Font.h"
#include "GUI and Fonts/GUI.h"

const sf::String TITLE_PROGRAM = "MainGame v1.6.6";

const float faultWorldTime = 0.03f;

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

	void informationAboutSelect(float x, float y);

	void processEvents(const float deltaTime);

	void updatePlayer(const float& deltaTime);
	void updateEntity(const float deltaTime);

	void updateUnlifeObjects(const float& deltaTime);
	void upgradeObject(UnlifeObject& object);

	void createGroups(float time);
	void generateGroups();
	void updateWorldTimeCircles();

	void update(const float& deltaTime);

	void renderEntitys();
	void renderUnlifeObjects();
	void render();

	void showFPS(const Time timeSinceLastUpdate);
};

void initializeGame(Game & game);

void initializeCategorysBreakingObject(Game &game);

void updateEntity(Game &game, const float deltaTime);
void renderEntitys(Game &game);

void renderUnlifeObjects(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
void informationAboutSelect(Game &game, float x, float y);