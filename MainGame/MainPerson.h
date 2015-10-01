#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#define border1 1
#define border10 10
#define LongMap 25//������ ����� ������
#define WidthMap 40 + border1//������ ����� ������ 
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
	// ���������
	Sprite *spritePerson;
	Texture *textureMainPerson;

	// �����
	SoundBuffer soundBuffer[5];
	Sound sounds[5];
	float startSounds[5];
	
	// ��� ��������
	Direction direction;
	int stepFirst;
	int stepCurrent;
	float timeAnimation;
	Vector2f movement;

	// ��� �������������� � �����
	int currentLevelFloor;
	int currentLevel;
	int currenMode;
	const int amountTypeItems = 10;
	int idSelectItem;

	// ��� ���������
	int width;
	int height;
	float rotation;

	// ������������. ��� �������� � �������
	void update(const Time & deltaTime);
	void playSound(float &time, float &start, const int &idSound);
	void resetTimeAnimation(float &time, float &reset);
	void computeAngle(RenderWindow &window);

	// ������
	View *view;
	void getCoordinateForView(float x, float y);
	void viewmap(float time);
	void changeview();
	
	// �������������� � �����
	void interactionWithMap(wchar_t(*map)[LongMap][WidthMap], const Time & deltaTime);
	void modeProcess(wchar_t(*map)[LongMap][WidthMap], Event &eventPerson, int x, int y);

	//��������������� �������
	float getXPos();
	float getYPos();
};

// ���������� ���������
void initializeMainPerson(MainPerson & mainPerson);
