#include "Sound.h"

using namespace sf;

void initializeSound(dataSound &soundBuffer)
{
	const float minDistanse = 300.f;

	soundBuffer.soundBuffer[idSoundEntity::stepGrass].loadFromFile(soundPaths[idSoundPaths::stepGrass1]);
	soundBuffer.startSounds[idSoundEntity::stepGrass] = 0;
	soundBuffer.sounds[idSoundEntity::stepGrass].setBuffer(soundBuffer.soundBuffer[idSoundEntity::stepGrass]);
	//soundBuffer.sounds[idSoundEntity::stepGrass].setRelativeToListener(true);
	soundBuffer.sounds[idSoundEntity::stepGrass].setMinDistance(minDistanse / 2);
	soundBuffer.sounds[idSoundEntity::stepGrass].setAttenuation(minDistanse + 1.f);


	soundBuffer.soundBuffer[idSoundEntity::stepStone].loadFromFile(soundPaths[idSoundPaths::stepStone1]);
	soundBuffer.startSounds[idSoundEntity::stepStone] = 0;
	soundBuffer.sounds[idSoundEntity::stepStone].setBuffer(soundBuffer.soundBuffer[idSoundEntity::stepStone]);
	//soundBuffer.sounds[idSoundEntity::stepStone].setRelativeToListener(true);
	soundBuffer.sounds[idSoundEntity::stepStone].setMinDistance(minDistanse / 2);
	soundBuffer.sounds[idSoundEntity::stepStone].setAttenuation(minDistanse + 1.f);
}