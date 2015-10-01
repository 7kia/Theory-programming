#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#define border1 1
#define border10 10
#define LongMap 25//размер карты высота
#define WidthMap 40 + border1//размер карты ширина 
#define HeightMap 2
#define sizeTile 32

using namespace sf;

typedef enum
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
} Direction;

typedef enum
{
	stepGrass,
	stepStone,
	stepWood,
	stepWool
} idSoundPerson;

typedef enum
{
	build,
	fight
} idModeMainPerson;

struct MainPerson
{
	// Текструра
	Sprite *spritePerson;
	Texture *textureMainPerson;

	// Звуки
	SoundBuffer soundBuffer[5];
	Sound sounds[5];
	float startSounds[5];
	
	// Для движения
	Direction direction;
	int stepFirst;
	int stepCurrent;
	float timeAnimation;
	Vector2f movement;

	// Для взаимодействия с миром
	int currentLevelFloor;
	int currentLevel;
	int currenMode;
	const int amountTypeItems = 10;
	int idSelectItem;

	// Для отрисовки
	int width;
	int height;
	float rotation;

	// Передвижение. Его анимация и озвучка
	void update(const Time & deltaTime);
	void playSound(float &time, float &start, const int &idSound);
	void resetTimeAnimation(float &time, float &reset);
	void computeAngle(RenderWindow &window);

	// Камера
	View *view;
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();
	
	// Взаимодейтсвие с миром
	void interactionWithMap(wchar_t(*map)[LongMap][WidthMap], const Time & deltaTime);
	void modeProcess(wchar_t(*map)[LongMap][WidthMap], Event &eventPerson, int x, int y);

	//Вспомагательные функции
	float getXPos();
	float getYPos();
};

// Объявление персонажа
void initializeMainPerson(MainPerson & mainPerson);
