#include  "updateGame.h"

using namespace sf;
using namespace std;


void Game::update(const float &deltaTime)
{
	Entity *mainPerson = &world.Enemys[ID_PLAYER_IN_LIST];

	processEvents(deltaTime);

	if ((mainPerson->isDeath == false)
			&& (stateGame != pauseState)
			&& (stateGame != endGameState)) {
	
		updatePlayer(deltaTime);
		updateBullets(deltaTime);
		updateEntity(deltaTime);
		updateUnlifeObjects(deltaTime);
		updateWorldTimeCircles();

	}
}

void Game::updatePlayer(const float &deltaTime)
{
	Entity *mainPerson = &world.Enemys[ID_PLAYER_IN_LIST];


	mainPerson->update(deltaTime);
	if(mainPerson->currenMode == idEntityMode::atack || mainPerson->getStateGiveDamage())
	{
		mainPerson->updateAtack(world, deltaTime);
	}
	mainPerson->interactionWitnUnlifeObject(world.unlifeObjects, world.deleteUnlifeObjects, deltaTime);
	mainPerson->interactionWithEntity(&world.Enemys , 0 , deltaTime);
	mainPerson->interactionWithMap(world.field, world.listDestroy, deltaTime);
	mainPerson->interactionWitnShoots(world.shoots , world.deleteShoots, deltaTime);
	mainPerson->getCoordinateForView(mainPerson->getPosition(), world.view);

	mainPerson->updateView(world.view, world.listener, window);
	window.setView(world.view);


	//printf("Angle %f \n", mainPerson.rotation);
}

void Game::updateBullets(const float deltaTime)
{
	vector<shoot>& shoots = world.shoots;

	for (int i = 0; i < shoots.size(); ++i) {
		if(shoots[i].getDirection() != RESET_VECTOR_2F)
		{
			shoots[i].move(deltaTime);

			if((Math::distansePoints(ZERO_VECTOR_2F, shoots[i].getDirection()) < ABOUT_ZERO_VALUE_SPEED_BULLET)
				&& (shoots[i].getIdType() != mineExplosionShoot))
			{
				world.deleteShoots.push_back(i);
			}
		}
	}
}

void Game::updateEntity(const float deltaTime)
{
	vector<Entity>& Enemys = world.Enemys;
	Entity *mainPerson = &world.Enemys[ID_PLAYER_IN_LIST];

	Field &field = world.field;
	for (int i = 1; i < Enemys.size(); ++i) {
		Enemys[i].update(deltaTime);

		if (!Enemys[i].getStateDeath()) {
			Enemys[i].interactionWitnUnlifeObject(world.unlifeObjects , world.deleteUnlifeObjects , deltaTime);

			Enemys[i].interactionWithEntity(&world.Enemys , i , deltaTime);
			Enemys[i].interactionWithMap(field , world.listDestroy , deltaTime);

			if (Enemys[i].type->converse.isAgressiveForPlayer) {
				Enemys[i].searchEnemy(*mainPerson , world , deltaTime);
			}
			Enemys[i].interactionWitnShoots(world.shoots , world.deleteShoots , deltaTime);

			Enemys[i].randomWalk(deltaTime);
		}
		else {
			g_Functions::addIdDeleteInList(i , world.deleteEnemys);

		}
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
		else if (idTypeObject == mineObject) {
			if (g_Functions::isInListObjects(world.deleteUnlifeObjects, i)) {

				vector<shoot> &shoots = world.shoots;
				objects[i].createBullet(shoots ,
																world.getTypeShoot(mineExplosionShoot) ,
																objects[i].getLevel());
				shoots[shoots.size() - 1].setDirection(ZERO_VECTOR_2F);

				Vector2i posInFloorXYOnMap = Math::inMapCoordinate(objects[i].getPosition());
				Vector3i posEffect = { posInFloorXYOnMap.x + 1, 
																posInFloorXYOnMap.y + 1,
																objects[i].getLevel() };

				world.createUnlifeObject(mineExplosionEffect, posEffect);
				::playSound(mineExplosionSound , *objects[objects.size() - 1].typeObject->soundBase ,
										objects[objects.size() - 1].soundObject, 
										objects[i].getPosition());
				
				stateGame = pauseState;
			}
		}
		else if (idTypeObject == destroyBlockEffect) {
			int &currentToughness = objects[i].currentToughness;
			int &maxToughnessObject = objects[i].typeObject->toughnessObject;

			if (currentToughness > maxToughnessObject) {
				currentToughness = maxToughnessObject;
			}

			if (objects[i].timeLife > TIME_LIFE_DESTROY_BLOCK_EFFECT) {
				objects[i].timeLife = 0.f;

				if (currentToughness < 1) {
					assert(objects.size() != 0);
					objects.erase(objects.begin() + i);
					continue;
				}
				else {
					float partToughness = (PERCENT_INCREASE_TOUGHNESS_BLOCK / 100.f);
					currentToughness += int(partToughness * maxToughnessObject);
				}

			}

		}
		else if (idTypeObject != destroyBlockEffect) {
			sf::SoundSource::Status stateSound = objects[i].soundObject.getStatus();
			if (stateSound == sf::SoundSource::Status::Stopped) {
				assert(objects.size() != 0);
				objects.erase(objects.begin() + i);
				continue;
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
	Vector3i posOnMap = { int((currentPos.x + SIZE_BLOCK / 2) / SIZE_BLOCK),
												int((currentPos.y + SIZE_BLOCK / 2) / SIZE_BLOCK),
												object.getLevel() };

	TypeUnlifeObject *nextType = &world.typesObjects.typesUnlifeObject[redefine.id];

	object.setType(*nextType);
	object.setPosition(posOnMap);
}

void world::createUnlifeObject(int id , const Vector3i &pos) {
	UnlifeObject addObject;

	addObject.setType(getTypeUnlifeObject(id));
	addObject.setPosition(pos);
	unlifeObjects.push_back(addObject);
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

