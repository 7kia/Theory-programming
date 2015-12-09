#include  "worldCircle.h"

using namespace sf;
using namespace std;

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
	bool &waveEntitysCreated = world.waveEntitysCreated;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();
	int *config = world.enemyWaveVariables;

	bool nowNight = world.timeDay == night;
	bool needGenerateWave = int(currentWorldTime) % config[TIME_GENERATE_WAVE_ENEMYS] == 0;

	if (nowNight && needGenerateWave && !waveEntitysCreated) {
		createGroups(currentWorldTime);
	}

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
		world.waveEntitysCreated = false;
	}
}

void Game::setNight()
{
	world.worldTime.restart();
	switchMusic();
	world.timeDay = night;
}

void Game::setDay()
{
	world.worldTime.restart();
	switchMusic();
	world.timeDay = day;
}

void Game::destroyUnlife()
{
	std::vector<Entity>& Entitys = *world.Entitys;
	int i = 0;
	while (i < Entitys.size()) {
		if (Entitys[i].protection.deathDay) {
			Entitys[i].playSoundDeath(world);
			Entitys.erase(Entitys.begin() + i);
			world.countEntity--;
			continue;
		}
		i++;
	}
}

void Game::giveAward()
{
	if (updateDifficult) {
		dropAward(awardForLevel[difficult]);
	}
	drawAwardPanel();
	dropAward(*awardForWave);
}


void Game::dropAward(vector<Vector2i> &listAward)
{
	TypeItem *typesItems = world.typesObjects.typesItem;
	Item *addItem = new Item;

	for (size_t i = 0; i < listAward.size(); i++) {
		addItem->setType(typesItems[listAward[i].x]);
		addItem->setPosition(CENTER_WORLD.x, CENTER_WORLD.y, 2);
		addItem->mainSprite->setScale(scaleOutItems);

		for (int count = 0; count < listAward[i].y; count++) {
			world.items->push_back(*addItem);

		}

	}

	delete addItem;
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

void Game::createGroups(float time)
{
	countWave++;
	world.waveEntitysCreated = true;
	Vector3i pos = { 3, 10, 0 };

	///*
	pos = { 5, 5, 2 };	
	createSmallGroupSkelets(world, pos);


	checkDifficult();
	generateStrongGroups();
}

void Game::checkDifficult()
{
	int *config = world.enemyWaveVariables;

	updateDifficult = countWave == config[AMOUNT_WAVE_FOR_UPDATE_DIFFICULT];
	if (updateDifficult) {
		countWave = 0;
		difficult++;
	}

}

void Game::generateStrongGroups()
{
	Vector3i pos;

	if (difficult > 1) {
		pos = { 10, 10, 1 };
		createMiddleGroupSkelets(world, pos);
	}
	if (difficult > 2) {
		pos = { 20, 20, 1 };
		createBigGroupSkelets(world, pos);
	}

}
