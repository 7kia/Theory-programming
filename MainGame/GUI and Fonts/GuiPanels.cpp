#include "GuiPanels.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////
void infoAboutSelect::render(Vector2f position, RenderWindow &window, TextGame &textGame)
{
	sprite.setPosition(position);
	window.draw(sprite);

	Text* currentText = &textGame.texts[idText::infoWindowBlock];
	position = { position.x + shiftXInfoText , position.y + shiftYInfoText };
	currentText->setPosition(position);
	window.draw(*currentText);

	for (int i = idText::infoWindowFloor; i <= idText::infoEntity; i++) {
		currentText = &textGame.texts[i];
		position.y += textGame.texts[i - 1].getCharacterSize();
		currentText->setPosition(position);
		window.draw(*currentText);
	}
}


void panelQuickAccess::renderPanel(Vector2f position, RenderWindow& window)
{
	spritePanel.setPosition(position);
	window.draw(spritePanel);
}

void panelQuickAccess::renderSelect(Entity& mainPerson, featuresWindow features)
{
	RenderWindow &window = *features.window;
	Vector2f centerWindow = features.center;
	Vector2u sizeWindow = features.size;

	int &idSelectItem = mainPerson.idSelectItem;
	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * idSelectItem;

	Vector2f position;
	position = { centerWindow.x - startPosition + shift, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };// ÈÑÏÐÀÂÜ

	spriteSelect.setPosition(position);
	window.draw(spriteSelect);
}

void panelQuickAccess::renderAmountItem(int amount, Vector2f pos, TextGame &textGame, featuresWindow features)
{
	RenderWindow &window = *features.window;
	Text *currentText = &textGame.texts[idText::itemGui];

	if (amount > 1) {
		string str;
		intToString(amount, str);

		currentText->setString(str);

		currentText->setPosition(pos);
		window.draw(*currentText);
	}

}

void panels::renderItemPanel(sf::Vector2f position, RenderWindow& window)
{
	itemInfoOverPanel.setPosition(position);
	window.draw(itemInfoOverPanel.sprite);
}

void panelQuickAccess::renderItems(Entity& mainPerson, featuresWindow features,
																	 TextGame &textGame, barMainFeatures &bars, itemFeatures &itemFeatures)
{
	RenderWindow &window = *features.window;
	Vector2f centerWindow = features.center;
	Vector2u sizeWindow = features.size;

	String nameCurrentItem = mainPerson.itemsEntity[0].getName();
	String nameEmptyItem = mainPerson.getRefOnEmptyItem()->getName();

	int startPosition = widthPanelQuickAccess / 2;
	for (int i = 0; i < mainPerson.type->amountSlots; i++) {

		nameCurrentItem = mainPerson.itemsEntity[i].getName();
		if (nameCurrentItem != nameEmptyItem) {

			Item& currentItem = mainPerson.itemsEntity[i];

			int shift = shiftSelect * i;
			Vector2f pos;
			pos = { centerWindow.x - startPosition + shift + SHIFT_START_ITEM_PANEL,
				centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };// ÈÑÏÐÀÂÜ
		
			currentItem.setPosition(Vector3i(pos.x, pos.y, currentItem.getLevelOnMap()));


			if (mainPerson.idSelectItem == i) {
				itemFeatures.renderFeatures(mainPerson, features, textGame, bars);
				currentItem.setScale(normalSize);
			}
			else
			{
				currentItem.setScale(scaleOutItems);
			}
			window.draw(currentItem.getSprite());
			renderAmountItem(currentItem.amount, pos, textGame, features);
		}

	}

}

void panel::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}