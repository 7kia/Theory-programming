#include "Sound.h"

using namespace sf;


void dataSound::initSound(int id, const sf::String *paths, float start)
{
	soundBuffer[id].loadFromFile(paths[id]);
	startSounds[id] = start;
}

dataSound::dataSound()
{
	globalSound.setRelativeToListener(false);

	initSound(stepGrass1Sound, soundPaths, 0.f);
	initSound(stepGrass1Sound, soundPaths, 0.f);
	initSound(drop1Sound, soundPaths, 0.f);
	initSound(punchBody1Sound, soundPaths, 0.f);
	initSound(metalPunchBody1Sound, soundPaths, 0.f);
	initSound(luggage1Sound, soundPaths, 0.f);
	initSound(itemChoiseIdSound, soundPaths, 0.f);
	initSound(skeletonDeathSound, soundPaths, 0.f);

	initSound(chopp1Sound, soundPaths, 0.f);
	initSound(treeDropSound, soundPaths, 0.f);
}

void playGlobalSound(const int idSound, dataSound &soundBase)
{
	sf::Sound &globalSound = soundBase.globalSound;

	globalSound.setBuffer(soundBase.soundBuffer[idSound]);

	globalSound.play();	

}

void playSound(const int idSound, dataSound& soundBase, sf::Sound &sound, sf::Vector2f pos)
{
	sound.setBuffer(soundBase.soundBuffer[idSound]);

	sound.play();
	sound.setPosition(pos.x, pos.y, 0);
}