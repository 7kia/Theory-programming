#pragma once
#include "../Entity/MainPerson.h"

#include "../GUI and Fonts/Font.h"
#include "../GUI and Fonts/GUI.h"

const sf::String TITLE_PROGRAM = "MainGame v1.9.3";

const float faultWorldTime = 0.05f;

const int NUMBER_LEVELS = 4;

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

		pauseGame,

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
		Keyboard::C,
		Keyboard::P
	};
}

enum StateGame
{
	gameState,
	pauseState,
	startGameState,
	menuState,
	waveEndState,
	endGameState
};

struct Game
{
	sf::RenderWindow window;

	GUI gui;
	TextGame textGame;
	Music music;
	StateGame stateGame = StateGame::gameState;

	Keyboard::Key keys[hotKeys::amountKeys];

	sf::View *view;

	Entity *mainPerson;

	bool updateDifficult = false;
	int difficult = 0;
	int countWave = 0;

	int countDay = 0;
	world world;
	std::vector<Vector2i> *awardForLevel;
	std::vector<Vector2i> *awardForWave;

	sf::Clock clock;

	unsigned int widthMainWindow = DEFAULT_WIDTH_WINDOW;
	unsigned int heightMainWindow = DEFAULT_HEIGHT_WINDOW;


	Game();
	void loadConfig(char *nameConfig, int *variables);
	void initializeCategorysBreakingObject();
	void initializeHotKeys();
	void informationAboutSelect(float x, float y);

	// processEvents.cpp
	void processEvents(const float deltaTime);
	void processArrows();
	void processInterface();
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

	void checkDifficult();
	void generateStrongGroups();
	void createGroups(float time);
	void generateGroups();

	// GiveAward.cpp
	void createListAward();
	void giveAward();
	void drawAwardPanel();
	void dropAward(std::vector<sf::Vector2i> &listAward);

	// worldCircle.cpp
	void updateWorldTimeCircles();
	void updateTimeDay(float &time);
	void setNight();
	void setDay();
	void destroyUnlife();
	void switchMusic();
	void playDayMusic();
	void playNightMusic();
	// renderGame.cpp
	void render();
	void drawInWindow(sf::Sprite &sprite, sf::FloatRect const& rectWindow);
	void renderEntitys(sf::FloatRect const& rectWindow);
	void renderUnlifeObjects(sf::FloatRect const& rectWindow);

	void drawEndGamepanel();
	void setPositionAwardText();
	void setPositionTitleAward(sf::Vector2f const& centerWindow, sf::Vector2f &posText);
	void setPositionHelpTextAward(sf::Vector2f const& centerWindow, sf::Vector2f &posText);

	void setPositionEndGameText();
	void drawAwardItems(std::vector<sf::Vector2i> &listAward);

	void renderItems(sf::FloatRect const& rectWindow);
	void renderMap(sf::FloatRect const& rectWindow);
	void renderGui();
	void showFPS(const Time timeSinceLastUpdate);
};
void initializeCategorysBreakingObject(Game &game);

void updateEntity(Game &game, const float deltaTime);
void renderEntitys(Game &game);

void renderUnlifeObjects(Game &game);

void destroyGame(Game & game);
