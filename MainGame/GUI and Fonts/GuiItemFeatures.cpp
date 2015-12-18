#include "GuiItemFeatures.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////
void itemFeatures::renderNameItem(Entity& mainPerson, Vector2f& position, featuresWindow features,
																	TextGame &textGame)
{
	RenderWindow &window = *features.window;
	Vector2f centerWindow = features.center;
	Vector2u sizeWindow = features.size;

	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[mainPerson.idSelectItem].typeItem->features.name;
	Text *currentText = &textGame.texts[idText::itemGui];

	currentText->setString(nameCurrentItem);
	position = { centerWindow.x - WIDTH_ITEM_OVER_PANEL_INFO / 2 + SHIFT_FEATURES_PANEL,
		centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - HEIGHT_ITEM_OVER_PANEL_INFO / 2 };
	currentText->setPosition(position);
	window.draw(*currentText);
}

void itemFeatures::renderValueMiddle(string string, Text* text, sf::Vector2f &position, RenderWindow &window)
{
	position.x += WIDTH_DAMAGE_GUI * SCALE_FEATURES.x;
	text->setString(string);
	text->setOrigin(float(string.size() / 2), float(text->getCharacterSize() / 2));
	text->setPosition(position);
	window.draw(*text);
}

void itemFeatures::renderIconWithScale(Sprite &sprite, sf::Vector2f position, sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setScale(SCALE_FEATURES);
	window.draw(sprite);
}

void itemFeatures::renderBar(Sprite &sprite, sf::Vector2f position, sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setScale(scaleGuiForEnemy);
	window.draw(sprite);
	sprite.setScale(normalSizeGuiForEnemy);
}

void itemFeatures::renderFeatures(Entity& mainPerson, featuresWindow features,
																	TextGame &textGame, barMainFeatures &bars)
{
	RenderWindow &window = *features.window;
	Vector2f centerWindow = features.center;
	Vector2u sizeWindow = features.size;

	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[0].typeItem->features.name;
	String nameEmptyItem = mainPerson.founds.emptyItem->typeItem->features.name;
	Text *currentText = &textGame.texts[idText::itemGui];

	Vector2f posName;// Сначала выписываем характеристики, потом имя(так как имя перед ними)
	renderNameItem(mainPerson, posName, features, textGame);

	int i = mainPerson.idSelectItem;
	int paritySize = currentText->getString().getSize() % 2;
	int shiftName = currentText->getCharacterSize();// TODO
	int halfSizeString = shiftName * (2 - paritySize) + int(computeSizeString(*currentText) / 2);
	//////////////////////////////////////////////


	Item& currentItem = mainPerson.itemFromPanelQuickAccess[i];
	TypeItem *typeItem = currentItem.typeItem;
	featuresItem *featuresItem = &typeItem->features;
	int categoryItem = typeItem->features.category;
	Vector2f pos;

	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * i;// TODO
															/////////////////////////////////////////////////////////////
															// Если предмет инструмент или оружие
	bool isDestroy = featuresItem->isDestroy;
	if (isDestroy) {
		pos = { centerWindow.x - startPosition + shift + SHIFT_START_ITEM_PANEL,
			centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };
		// то отображаем прочность
		pos.x -= SIZE_ITEM / 2;
		pos.y += SIZE_ITEM / 2 - HEIGHT_BARS_GUI * 0.5f * scaleOutItems.y;

		renderBar(bars.bar, pos, window);

		float levelToughness = float(currentItem.currentToughness) / currentItem.maxToughness;

		pos.x += X_SHIFT_BARS * scaleGuiForEnemy.x;
		pos.y += Y_SHIFT_BARS * scaleGuiForEnemy.y;
		int currentToughness = int(WIDTH_LEVEL_BAR_GUI * levelToughness);
		bars.levelStamina.setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, currentToughness, HEIGHT_LEVEL_BAR_GUI));

		renderBar(bars.levelStamina, pos, window);
	}
	////////////////////////////////
	// Характеристики
	//////////////////////////////////////////////////////////
	// Отображение характеристик
	pos = { posName.x + halfSizeString,
		centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess - Y_SHIFT_OUT_PANEL };
	// Перевод из числа в строку
	int itemCutDam = typeItem->damageItem.cuttingDamage;
	int itemCrashDam = typeItem->damageItem.crushingDamage;
	int itemUnlifeDam = typeItem->damageItem.unlifeDamage;

	string itemCut;
	string itemCrash;
	string itemUnlife;

	intToString(itemCutDam, itemCut);
	intToString(itemCrashDam, itemCrash);
	intToString(itemUnlifeDam, itemUnlife);


	renderIconWithScale(cutSprite, pos, window);
	renderValueMiddle(itemCut, currentText, pos, window);

	pos.x += computeSizeString(*currentText) + SHIFT_FEATURES_PANEL;
	renderIconWithScale(crashSprite, pos, window);
	renderValueMiddle(itemCrash, currentText, pos, window);

	pos.x += computeSizeString(*currentText) + SHIFT_FEATURES_PANEL;
	renderIconWithScale(unlifeSprite, pos, window);
	renderValueMiddle(itemUnlife, currentText, pos, window);

	//////////////////////////////////////////////////////////
	// Отображение характеристик

	pos.x += computeSizeString(*currentText) + SHIFT_FEATURES_PANEL;
	int itemToughness = currentItem.currentToughness;

	string itemToug;

	intToString(itemToughness, itemToug);

	////////////////
	// Голод
	if (categoryItem == idCategoryItem::food) {
		hungrySprite.setPosition(pos);
		hungrySprite.setScale(SCALE_FEATURES);
		window.draw(hungrySprite);
	}
	////////////////
	// Жажда
	else if (categoryItem == idCategoryItem::bottleWithWater
					 || categoryItem == idCategoryItem::bukketWithWater) {
		thirstSprite.setPosition(pos);
		thirstSprite.setScale(SCALE_FEATURES);
		window.draw(thirstSprite);
	}
	////////////////
	// Другое не показываем
	else {
		itemToug = "";// ИСПРАВЬ
	}

	renderValueMiddle(itemToug, currentText, pos, window);
	//////////////////////////////////////////////////////////

}
