#include  "updateGame.h"

using namespace sf;
using namespace std;


void Game::update(const float &deltaTime)
{
	processEvents(deltaTime);

	Entity &mainPerson = world.Enemys[0];
	if (mainPerson.isDeath == false
			&& stateGame != pauseState
			&& stateGame != endGameState) {
		updatePlayer(deltaTime);
		updateEntity(deltaTime);
		updateUnlifeObjects(deltaTime);
		updateWorldTimeCircles();
	}
}

void Game::updatePlayer(const float &deltaTime)
{
	Entity &mainPerson = world.Enemys[0];
	mainPerson.update(deltaTime);
	if(mainPerson.currenMode == idEntityMode::atack || mainPerson.giveDamage)
	{
		mainPerson.updateAtack(world, deltaTime);
	}
	mainPerson.interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);
	mainPerson.interactionWithEntity(&world.Enemys , 0 , deltaTime);

	mainPerson.interactionWithMap(world.field, world.listDestroy, deltaTime);
	mainPerson.getCoordinateForView(mainPerson.getPosition(), world.view);

	mainPerson.updateView(world.view, world.listener, window);
	window.setView(world.view);

	//printf("Angle %f \n", mainPerson.rotation);
}


void Game::updateEntity(const float deltaTime)
{
	vector<Entity>& Enemys = world.Enemys;
	Entity &mainPerson = world.Enemys[0];

	Field &field = world.field;
	for (int i = 1; i < Enemys.size(); ++i) {
		Enemys[i].update(deltaTime);
		Enemys[i].interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);

		Enemys[i].interactionWithEntity(&world.Enemys, i, deltaTime);
		Enemys[i].interactionWithMap(field, world.listDestroy, deltaTime);

		//Enemys[i].currenMode = Enemys[i].currenMode;
		Enemys[i].searchEnemy(mainPerson , world, deltaTime);
		Enemys[i].randomWalk(deltaTime);
	}
}


void Game::updateUnlifeObjects(const float &deltaTime)
{
	vector<UnlifeObject> &objects = world.unlifeObjects;
	size_t i = 0;

	while(i < objects.size()) {
		objects[i].timeLife += deltaTime;

		int idTypeObject = objects[i].typeObject->id;
		if (idTypeObject < idUnlifeObject::shiftEffects) {

			redefineObject &redefine = objects[i].typeObject->redefine;
			float timeUpdate = redefine.timeUpdate;
			if (timeUpdate) {
				if (objects[i].timeLife > timeUpdate) {
					upgradeObject(objects[i]);
				}
			}
		}
		/////////////////////////////////
		// Обновление  звуковых эффектов
		else if(idTypeObject != destroyBlockEffect){
			sf::SoundSource::Status stateSound = objects[i].soundObject.getStatus();
			if (stateSound == sf::SoundSource::Status::Stopped) {
				objects.erase(objects.begin() + i);
			}
		}
		/////////////////////////////////
		else {
			int &currentToughness = objects[i].currentToughness;
			int &maxToughnessObject = objects[i].typeObject->toughnessObject;

			if (currentToughness > maxToughnessObject) {
				currentToughness = maxToughnessObject;
			}

			if (objects[i].timeLife > TIME_LIFE_DESTROY_BLOCK_EFFECT) {
				objects[i].timeLife = 0.f;

				if (currentToughness < 1) {
					objects.erase(objects.begin() + i);
					continue;
				}
				else {
					float partToughness = (PERCENT_INCREASE_TOUGHNESS_BLOCK / 100.f);
					currentToughness += int(partToughness * maxToughnessObject);
				}

			}

		}

		i++;
	}
}

void Game::upgradeObject(UnlifeObject &object)
{
	redefineObject &redefine = object.typeObject->redefine;
	Sprite &spriteObject = *object.spriteObject;
	Vector2f currentPos = spriteObject.getPosition();
	Vector2i posOnMap = { int((currentPos.x + SIZE_BLOCK / 2) / SIZE_BLOCK),
		int((currentPos.y + SIZE_BLOCK / 2) / SIZE_BLOCK) };

	TypeUnlifeObject &nextType = world.typesObjects.typesUnlifeObject[redefine.id];

	object.setType(nextType);
	object.setPosition(posOnMap.x, posOnMap.y, object.currentLevel);
}


void Game::generateGroups()
{
	bool &waveEnemysCreated = world.waveEnemysCreated;
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();
	int *config = world.enemyWaveVariables;

	bool nowNight = world.timeDay == night;
	bool needGenerateWave = int(currentWorldTime) % config[TIME_GENERATE_WAVE_ENEMYS] == 0;

	if (nowNight && needGenerateWave && !waveEnemysCreated) {
		createGroups(currentWorldTime);
	}

}

void Game::createGroups(float time)
{
	countWave++;
	world.waveEnemysCreated = true;

	Vector3i pos;

	pos = { 5, 5, 2 };
	createSmallGroupSkelets(world , pos);

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
		createMiddleGroupSkelets(world , pos);
	}
	if (difficult > 2) {
		pos = { 20, 20, 1 };
		createBigGroupSkelets(world , pos);
	}
}

