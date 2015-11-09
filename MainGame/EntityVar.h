#pragma once
const int AMOUNT_ENEMY_ITEM = 8;

const float MULTIPLIER_OF_DAMAGE = 1.f;
const float TIME_GIVEN_DAMAGE = 1.f;

const float SPEED_ENTITY = 150.f;
const float RADIUSE_VIEW = 300.f;

const int WIDTH_WOLF = 81;
const int HEIGHT_WOLF = 81;
const int AMOUNT_WOLF_SLOTS = 8;

const int WIDTH_SKELET = 32;
const int HEIGHT_SKELET = 32;
const int AMOUNT_SKELET_SLOTS = 8;

enum idEnemy
{
	wolfEnemy,
	skeletEnemy,
	emptyEnemy,
	amountEnemy
};

enum idEntityMode
{
	walk,
	fight,
	atack,
	panic,
	amountEnemyMode
};