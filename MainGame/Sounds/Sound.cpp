#include "Sound.h"

using namespace sf;

void initializeSound(dataSound &soundBuffer)
{
	soundBuffer.soundBuffer[idSoundEntity::stepGrass].loadFromFile(soundPaths[idSoundPaths::stepGrass1]);
	soundBuffer.startSounds[idSoundEntity::stepGrass] = 0;

	soundBuffer.soundBuffer[idSoundEntity::stepStone].loadFromFile(soundPaths[idSoundPaths::stepStone1]);
	soundBuffer.startSounds[idSoundEntity::stepStone] = 0;

}