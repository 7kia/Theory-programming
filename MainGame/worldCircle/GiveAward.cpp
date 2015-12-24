#include "worldCircle.h"

using namespace sf;
using namespace std;


void Game::createListAward()
{

	awardForWave.push_back({ idItem::healthPotionItem , 1 });
	awardForWave.push_back({ idItem::mushroomItem , 4 });

	awardForLevel[0].push_back({ idItem::stoneAxeItem , 1 });
	awardForLevel[0].push_back({ idItem::roastMeatWolfItem , 1 });
	awardForLevel[0].push_back({ idItem::glassbukketWithWater , 4 });
	awardForLevel[0].push_back({ idItem::seadlingOakItem , 4 });
	awardForLevel[0].push_back({ idItem::seadlingApple , 1 });

	awardForLevel[1].push_back({ idItem::stonePickaxItem , 1 });
	awardForLevel[1].push_back({ idItem::woodBukketWithWaterItem , 16 });
	awardForLevel[1].push_back({ idItem::glassBottleItem , 4 });
	awardForLevel[1].push_back({ idItem::planksBlockItem , 40 });

	awardForLevel[2].push_back({ idItem::ironSwordItem , 1 });
	awardForLevel[2].push_back({ idItem::ironAxeItem , 1 });
	awardForLevel[2].push_back({ idItem::ironClubItem , 1 });
	awardForLevel[2].push_back({ idItem::stoneItem , 40 });

	awardForLevel[3].push_back({ idItem::silverSwordItem , 1 });
	awardForLevel[3].push_back({ idItem::stoneBrickItem , 40 });

}

void Game::giveAward()
{
	if (updateDifficult) {
		dropAward(awardForLevel[difficult]);
	}
	drawAwardPanel();
	dropAward(awardForWave);
}

void Game::dropAward(vector<Vector2i> &listAward)
{
	TypeItem *typesItems = world.typesObjects.typesItem;
	vector<Item> &items = world.items;
	Item addItem;

	Vector3i posAward = { CENTER_WORLD.x, CENTER_WORLD.y, 2 };
	for (Vector2i awardInfo : listAward) {


		for (size_t count = 0; count < awardInfo.y; count++) {
			addItem.setType(typesItems[awardInfo.x]);
			addItem.setPosition(posAward);
			addItem.mainSprite->setScale(scaleOutItems);

			items.push_back(addItem);
		}
	}
}
