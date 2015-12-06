#include  "updateGame.h"

using namespace sf;
using namespace std;


void Game::update(const float &deltaTime)
{
	processEvents(deltaTime);

	if (mainPerson.isDeath == false) {
		updatePlayer(deltaTime);
		updateEntity(deltaTime);
		updateUnlifeObjects(deltaTime);
		updateWorldTimeCircles();
	}
}

void Game::updatePlayer(const float &deltaTime)
{
	mainPerson.update(deltaTime);
	mainPerson.updateAtack(world, deltaTime);
	mainPerson.interactionWithMap(world.field, *world.listDestroy, deltaTime);
	mainPerson.interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);
	mainPerson.getCoordinateForView(mainPerson.getXPos(), mainPerson.getYPos());

	mainPerson.updateView(window);
	window.setView(*mainPerson.view);

	//printf("Angle %f \n", mainPerson.rotation);
}


void Game::updateEntity(const float deltaTime)
{
	vector<Enemy>& Enemys = *world.Enemys;
	Field &field = world.field;
	for (int i = 0; i < Enemys.size(); ++i) {
		Enemys[i].update(deltaTime);
		Enemys[i].interactionWithMap(field, *world.listDestroy, deltaTime);
		Enemys[i].interactionWithEntity(world.Enemys, i, deltaTime);
		Enemys[i].interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);

		mainPerson.attractionEnemy(Enemys[i], world, deltaTime);
		Enemys[i].randomWalk(deltaTime);
	}
}


void Game::updateUnlifeObjects(const float &deltaTime)
{
	vector<UnlifeObject> &objects = *world.unlifeObjects;
	for (int i = 0; i < objects.size(); ++i) {
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
		// Обновление эффектов( пока звуковых
		else {
			sf::SoundSource::Status stateSound = objects[i].soundObject.getStatus();
			if (stateSound == sf::SoundSource::Status::Stopped) {
				objects.erase(objects.begin() + i);
			}
		}
		/////////////////////////////////
		

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