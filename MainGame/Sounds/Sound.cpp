#include "Sound.h"

using namespace sf;


void dataSound::initSound(int id, sf::String path, float start)
{
	soundBuffer[id].loadFromFile(path);
	startSounds[id] = start;
}

dataSound::dataSound()
{
	initSound(idSoundEntity::stepGrass, soundPaths[idSoundPaths::stepGrass1], 0.f);
	initSound(idSoundEntity::stepStone, soundPaths[idSoundPaths::stepStone1], 0.f);
	initSound(idSoundEntity::dropSound, soundPaths[idSoundPaths::drop1], 0.f);
	initSound(idSoundEntity::punchBody1Id, soundPaths[idSoundPaths::punchBody1], 0.f);
	initSound(idSoundEntity::metalPunchBody1Id, soundPaths[idSoundPaths::metalPunchBody1], 0.f);
}

