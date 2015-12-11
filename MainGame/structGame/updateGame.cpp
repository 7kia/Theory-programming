#include  "updateGame.h"

using namespace sf;
using namespace std;


void Game::update(const float &deltaTime)
{
	processEvents(deltaTime);

	if (mainPerson->isDeath == false
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
	mainPerson->update(deltaTime);
	if(mainPerson->currenMode == idEntityMode::atack)
	{
		mainPerson->updateAtack(world, deltaTime);
	}
	mainPerson->interactionWithMap(world.field, *world.listDestroy, deltaTime);
	mainPerson->interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);
	mainPerson->getCoordinateForView(mainPerson->getPosition(), *view);

	mainPerson->updateView(window, *view);
	window.setView(*view);

	//printf("Angle %f \n", mainPerson->rotation);
}


void Game::updateEntity(const float deltaTime)
{
	vector<Entity>& Entitys = *world.Entitys;
	Field &field = world.field;
	for (int i = 0; i < Entitys.size(); ++i) {
		Entitys[i].update(deltaTime);
		Entitys[i].interactionWithMap(field, *world.listDestroy, deltaTime);
		Entitys[i].interactionWithEntity(world.Entitys, i, deltaTime);
		Entitys[i].interactionWitnUnlifeObject(world.unlifeObjects, deltaTime);

		mainPerson->attractionEntity(Entitys[i], world, deltaTime);
		Entitys[i].randomWalk(deltaTime);
	}
}


void Game::updateUnlifeObjects(const float &deltaTime)
{
	vector<UnlifeObject> &objects = *world.unlifeObjects;
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
					i = 0;
					continue;
				}
				else {
					float partToughness = (PERCENT_INCREASE_TOUGHNESS_BLOCK / 100.f);
					currentToughness += partToughness * maxToughnessObject;
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