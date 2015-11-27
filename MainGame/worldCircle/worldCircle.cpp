#include  "worldCircle.h"

void Game::updateWorldTimeCircles()
{
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		generateGroups();

		printf("World time: %f\n", currentWorldTime);
	}
}

void Game::generateGroups()
{
	bool &needGenerateWave = world.waveEnemysCreated;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();
	int *config = world.configVariable;

	bool condition = int(currentWorldTime) % config[TIME_GENERATE_WAVE_ENEMYS] == 0;
	if (condition && needGenerateWave == false) {
		createGroups(currentWorldTime);
	}
}


void Game::createGroups(float time)
{
	Vector3i pos = { 3, 10, 0 };
	createSmallGroupSkelets(world, pos);

	pos = { 5, 5, 2 };
	createSmallGroupSkelets(world, pos);

	bool updateDifficult = int(time) % TIME_UPDATE_DIFFICULT == 0;
	if (updateDifficult)
		world.difficult++;

	if (world.difficult > 0) {
		pos = { 10, 10, 1 };
		createMiddleGroupSkelets(world, pos);
	}
	if (world.difficult > 1) {
		pos = { 20, 20, 1 };
		createBigGroupSkelets(world, pos);
	}
}

