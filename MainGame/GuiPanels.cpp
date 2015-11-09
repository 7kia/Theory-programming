#include "GuiPanels.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
void infoAboutSelect::render(Vector2f position, RenderWindow &window, TextGame &textGame)
{
	sprite->setPosition(position);
	window.draw(*sprite);

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
	spritePanel->setPosition(position);
	window.draw(*spritePanel);
}

void panelQuickAccess::renderSelect(MainPerson& mainPerson, featuresWindow features)
{
	RenderWindow &window = *features.window;
	Vector2f centerWindow = features.center;
	Vector2u sizeWindow = features.size;

	int &idSelectItem = mainPerson.idSelectItem;
	int startPosition = widthPanelQuickAccess / 2;
	int shift = shiftSelect * idSelectItem;

	Vector2f position;
	position = { centerWindow.x - startPosition + shift, centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };// ÈÑÏÐÀÂÜ

	spriteSelect->setPosition(position);
	window.draw(*spriteSelect);
}

void panels::renderItemPanel(sf::Vector2f position, RenderWindow& window)
{
	itemInfoOverPanel.setPosition(position);
	window.draw(itemInfoOverPanel);
}

void panelQuickAccess::renderItems(MainPerson& mainPerson, featuresWindow features,
																	 TextGame &textGame, barMainFeatures &bars, itemFeatures &itemFeatures)
{
	RenderWindow &window = *features.window;
	Vector2f centerWindow = features.center;
	Vector2u sizeWindow = features.size;

	Text *currentText;
	String nameCurrentItem = mainPerson.itemFromPanelQuickAccess[0].typeItem->features.name;
	String nameEmptyItem = mainPerson.founds.emptyItem->typeItem->features.name;

	int startPosition = widthPanelQuickAccess / 2;
	for (int i = 0; i < AMOUNT_ACTIVE_SLOTS; i++) {

		nameCurrentItem = mainPerson.itemFromPanelQuickAccess[i].typeItem->features.name;
		if (nameCurrentItem != nameEmptyItem) {

			Item& currentItem = mainPerson.itemFromPanelQuickAccess[i];

			int shift = shiftSelect * i;
			Vector2f pos;
			pos = { centerWindow.x - startPosition + shift + SHIFT_START_ITEM_PANEL,
				centerWindow.y + sizeWindow.y / 2 - heightPanelQuickAccess / 2 };// ÈÑÏÐÀÂÜ
			currentItem.mainSprite->setPosition(pos);
			window.draw(*currentItem.mainSprite);


			if (mainPerson.idSelectItem == i) {
				itemFeatures.renderFeatures(mainPerson, features, textGame, bars);
			}

		}

	}

}