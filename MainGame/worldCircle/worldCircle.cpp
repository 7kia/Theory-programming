#include  "worldCircle.h"

void Game::updateWorldTimeCircles()
{
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		generateGroups();
		updateTimeDay(currentWorldTime);
		printf("World time: %f\n", currentWorldTime);
	}
}

void Game::generateGroups()
{
	bool &needGenerateWave = world.waveEnemysCreated;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();
	int *config = world.enemyWaveVariables;

	bool condition = int(currentWorldTime) % config[TIME_GENERATE_WAVE_ENEMYS] == 0;
	condition &= world.timeDay == night;
	if (condition && needGenerateWave == false) {
		createGroups(currentWorldTime);
	}
}

void Game::updateTimeDay(float &time)
{
	TimeDay &timeDay = world.timeDay;
	if (timeDay == day) {
		if (time > float(world.enemyWaveVariables[TIME_DAY])) {
			world.worldTime.restart();
			switchMusic();
			timeDay = night;
		}

	}
	else {
		if (time > float(world.enemyWaveVariables[TIME_NIGHT])) {
			world.worldTime.restart();
			switchMusic();
			timeDay = day;

			std::vector<Enemy>& Enemys = *world.Enemys;
			int i = 0;
			while (i < Enemys.size()) {
				if (Enemys[i].protection.deathDay) {
					Enemys[i].playSoundDeath(world);
					Enemys.erase(Enemys.begin() + i);
					world.countEntity--;

					drawAwardPanel();
					continue;
				}
				i++;
			}

		}
	}
}


void Game::playDayMusic()
{
	TimeDay &timeDay = world.timeDay;

	music.openFromFile(musicPaths[idMusicPaths::DayMusic]);
	timeDay = day;
	music.play();

}

void Game::playNightMusic()
{
	TimeDay &timeDay = world.timeDay;

	music.openFromFile(musicPaths[idMusicPaths::NightMusic]);
	timeDay = night;
	music.play();
}

void Game::switchMusic()
{
	TimeDay &timeDay = world.timeDay;
	if (timeDay == day) {
		playNightMusic();
	}
	else if (timeDay == night ){
		playDayMusic();
	}
}

void Game::createGroups(float time)
{
	Vector3i pos = { 3, 10, 0 };

	///*
	pos = { 5, 5, 2 };	
	createSmallGroupSkelets(world, pos);


	createSmallGroupSkelets(world, pos);
	//pos = { 5, 5, 2 };
	//createSmallGroupSkelets(world, pos);

	//*/

	/*
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

	*/
}

