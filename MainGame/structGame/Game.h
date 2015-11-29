#pragma once
#include "../Entity/MainPerson.h"

#include "../GUI and Fonts/Font.h"
#include "../GUI and Fonts/GUI.h"

const sf::String TITLE_PROGRAM = "MainGame v1.7.3";

const float faultWorldTime = 0.03f;

namespace hotKeys
{
	enum id {
		Up,
		UpAlternate,
		Left,
		LeftAlternate,
		Down,
		DownAlternate,
		Right,
		RightAlternate,

		run,
		takeItem,
		throwItem,

		actionMain,
		actionAlternate,

		amountKeys
	};

	const Keyboard::Key defaultValue[amountKeys]
	{
		Keyboard::W,
		Keyboard::Up,
		Keyboard::A,
		Keyboard::Left,
		Keyboard::S,
		Keyboard::Down,
		Keyboard::D,
		Keyboard::Right,

		Keyboard::LShift,
		Keyboard::R,
		Keyboard::Q,

		Keyboard::E,
		Keyboard::C
	};
}


struct Game
{
	sf::RenderWindow window;

	GUI gui;
	TextGame textGame;

	Keyboard::Key keys[hotKeys::amountKeys];
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


	Game();
	void loadConfig();
	void initializeCategorysBreakingObject();
	void initializeHotKeys();

	void informationAboutSelect(float x, float y);

	// processEvents.cpp
	void processEvents(const float deltaTime);
	void processArrows();
	void processPersonAction(Vector2f pos);
	void processOtherAction(Event& event, Vector2f pos);
	void processPanelQuickAccess();
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
void initializeCategorysBreakingObject(Game &game);

void updateEntity(Game &game, const float deltaTime);
void renderEntitys(Game &game);

void renderUnlifeObjects(Game &game);

void destroyGame(Game & game);
void initializeClock(Clock &clock);
