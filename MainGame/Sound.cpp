#include "Sound.h"

void initializeSound(dataSound *soundBuffer)
{
	soundBuffer->soundBuffer = new SoundBuffer[sizeBuffer];
	soundBuffer->sounds = new Sound[sizeBuffer];
	soundBuffer->startSounds = new float[sizeBuffer];

	soundBuffer->soundBuffer[idSoundEntity::stepGrass].loadFromFile("recourses\\sounds\\step\\grass1.ogg");
	soundBuffer->startSounds[idSoundEntity::stepGrass] = 0;
	soundBuffer->sounds[idSoundEntity::stepGrass].setBuffer(soundBuffer->soundBuffer[idSoundEntity::stepGrass]);

	soundBuffer->soundBuffer[idSoundEntity::stepStone].loadFromFile("recourses\\sounds\\step\\stone1.ogg");
	soundBuffer->startSounds[idSoundEntity::stepStone] = 0;
	soundBuffer->sounds[idSoundEntity::stepStone].setBuffer(soundBuffer->soundBuffer[idSoundEntity::stepStone]);
}