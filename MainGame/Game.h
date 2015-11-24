#pragma once
#include "Entity/MainPerson.h"

#include "GUI and Fonts/Font.h"
#include "GUI and Fonts/GUI.h"

const sf::String TITLE_PROGRAM = "MainGame v1.6.6";

const float faultWorldTime = 0.03f;

struct hotKeys
{
	Keyboard::Key Up = Keyboard::W;
	Keyboard::Key UpAlternate = Keyboard::Up;
	Keyboard::Key Left = Keyboard::A;
	Keyboard::Key LeftAlternate = Keyboard::Left;
	Keyboard::Key Down = Keyboard::S;
	Keyboard::Key DownAlternate = Keyboard::Down;
	Keyboard::Key Right = Keyboard::D;
	Keyboard::Key RightAlternate = Keyboard::Right;

	Keyboard::Key run = Keyboard::LShift;
};

struct Game
{
	sf::RenderWindow window;

	GUI gui;
	TextGame textGame;

	hotKeys keys;
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

	// processEvents.cpp
	void processEvents(const float deltaTime);
	void processArrows();
	void resizeWindow();

	// updateGame.cpp
	void update(const float& deltaTime);
	void updatePlayer(const float& deltaTime);
	void updateEntity(const float deltaTime);
	void updateUnlifeObjects(const float& deltaTime);
	void upgradeObject(UnlifeObject& object);

	// worldCircle.cpp
	void createGroups(float time);
	void generateGroups();
	void updateWorldTimeCircles();

	// renderGame.cpp
	void render();
	void renderEntitys();
	void renderUnlifeObjects();
	void renderItems();
	void renderMap();
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