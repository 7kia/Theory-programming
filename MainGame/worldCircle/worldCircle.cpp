#include "../structGame/Game.h"

using namespace sf;
using namespace std;

void Game::updateWorldTimeCircles()
{
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	world.deleteObjects();
	world.deleteBullets();
	world.deleteEntitys();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		assert(world.Enemys[ID_PLAYER_IN_LIST].getType()->id == 0);

		generateGroups();
		assert(world.Enemys[ID_PLAYER_IN_LIST].getType()->id == 0);

		updateTimeDay(currentWorldTime);
		printf("World time: %f\n", currentWorldTime);
	}
}

void world::deleteObjects()
{
	int i = 0;
	int id;
	while (i < deleteUnlifeObjects.size()) {
		id = deleteUnlifeObjects[i];
		if (!unlifeObjects.empty()) {
			assert(unlifeObjects.size() != 0);
			assert(id > RESET_VALUE);
			unlifeObjects.erase(unlifeObjects.begin() + id);
			deleteUnlifeObjects.erase(deleteUnlifeObjects.begin() + i);
			continue;
		}
		i++;
	}
	deleteUnlifeObjects.clear();
}

void world::deleteBullets()
{
	int i = 0;
	int id;
	while (i < deleteShoots.size()) {
		id = deleteShoots[i];
		if (!shoots.empty()) {
			assert(shoots.size() != 0);
			assert(id > RESET_VALUE);
			//if(g_Functions::isInListObjects(shoots, id))

			shoots.erase(shoots.begin() + id);
			deleteShoots.erase(deleteShoots.begin() + i);

			continue;
		}
		i++;
	}
	deleteShoots.clear();
}

void world::deleteEntitys()
{
	int i = 0;
	int id;
	while (i < deleteEnemys.size()) {
		id = deleteEnemys[i];
		if (!Enemys.empty()) {
			assert(deleteEnemys.size() != 0);
			assert(id > RESET_VALUE);

			Enemys[id].Drop(*this);
			Enemys[id].playSoundDeath(*this);

			Enemys.erase(Enemys.begin() + id);

			countEntity--;
			deleteEnemys.erase(deleteEnemys.begin() + i);
			continue;
		}
		i++;
	}
	deleteEnemys.clear();
}

void Game::updateTimeDay(float &time)
{
	TimeDay &timeDay = world.timeDay;
	bool endDay = time > float(world.enemyWaveVariables[TIME_DAY]);
	bool endNight = time > float(world.enemyWaveVariables[TIME_NIGHT]);

	if (timeDay == day && endDay) {
		setNight();
	}
	else if (endNight) {
		setDay();
		destroyUnlife();
		if (difficult < NUMBER_LEVELS) {
			giveAward();
		}
		else
		{
			drawEndGamepanel();
		}
		world.waveEnemysCreated = false;
	}
}

void Game::setNight()
{
	world.worldTime.restart();
	if(playMusic)
	{
		switchMusic();
	}
	world.timeDay = night;
}

void Game::setDay()
{
	world.worldTime.restart();
	if (playMusic) {
		switchMusic();
	}
	world.timeDay = day;
}

void Game::destroyUnlife()
{
	std::vector<Entity>& Enemys = world.Enemys;
	int i = 0;
	while (i < Enemys.size()) {
		if (Enemys[i].protection.deathDay) {
			Enemys[i].playSoundDeath(world);

			assert(Enemys.size() != 0);
			Enemys.erase(Enemys.begin() + i);
			world.countEntity--;
			continue;
		}
		i++;
	}
}

void Game::switchMusic()
{
	TimeDay &timeDay = world.timeDay;
	if (timeDay == day) {
		playNightMusic();
	}
	else if (timeDay == night) {
		playDayMusic();
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

