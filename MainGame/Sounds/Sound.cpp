#include "Sound.h"

using namespace sf;


void dataSound::initSound(int id, const std::string *paths, float start)
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
	initSound(wolfDeathSound, soundPaths, 0.f);

	initSound(chopp1Sound, soundPaths, 0.f);
	initSound(treeDropSound, soundPaths, 0.f);
	initSound(forage1Sound, soundPaths, 0.f);

	initSound(hitGroundSound, soundPaths, 0.f);
	initSound(hitSandSound, soundPaths, 0.f);
	initSound(hitStoneSound, soundPaths, 0.f);

	initSound(waveEndSound, soundPaths, 0.f);
	initSound(levelUpSound, soundPaths, 0.f);

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
	sound.setMinDistance(minDistanse);
	sound.setAttenuation(minDistanse);
	sound.setPosition(pos.x, pos.y, 1);
}