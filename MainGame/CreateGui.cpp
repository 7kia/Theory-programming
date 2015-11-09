#include "CreateGui.h"


void createGUITexture(Texture &texture, sf::String fileName)
{
	texture.loadFromFile(fileName);
}

void createGUI(infoAboutSelect &gui)
{
	gui.Texture = new Texture;
	gui.sprite = new Sprite;

	gui.Texture->loadFromFile(texturePaths[idTexturePaths::infoSelectBlock]);
	gui.sprite->setTexture(*gui.Texture);
	gui.sprite->setTextureRect(IntRect(0, 0, widthInfo, heightInfo));
}

void createGUI(panelQuickAccess &gui, Texture &texture)
{
	gui.spritePanel = new Sprite;
	gui.spriteSelect = new Sprite;

	gui.spritePanel->setTexture(texture);
	gui.spritePanel->setOrigin(widthPanelQuickAccess / 2, heightPanelQuickAccess / 2);// �������
	gui.spritePanel->setTextureRect(IntRect(0, 0, widthPanelQuickAccess, heightPanelQuickAccess));

	gui.spriteSelect->setTexture(texture);
	gui.spriteSelect->setOrigin(0, heightSelectInPanelQuickAccess / 2);// �������
	gui.spriteSelect->setTextureRect(IntRect(shiftXSelectInPanelQuickAccess, shiftYSelectInPanelQuickAccess, widthSelectInPanelQuickAccess, heightSelectInPanelQuickAccess));

}

void createPanels(panels &gui, Texture &texture)
{
	createGUI(gui.infoAboutSelect);
	createGUI(gui.panelQuickAccess, texture);
	createGUI(gui.itemInfoOverPanel, texture);
}

void createGUI(barHungry &gui, Texture *texture)
{
	gui.lowHungry = new Sprite;
	gui.highHungry = new Sprite;
	gui.levelHungry = new Sprite;

	gui.lowHungry->setTexture(*texture);
	gui.lowHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.highHungry->setTexture(*texture);
	gui.highHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI, WIDTH_HUNGY_GUI, HEIGHT_HUNGY_GUI));

	gui.levelHungry->setTexture(*texture);
	gui.levelHungry->setTextureRect(IntRect(X_HUNGY_GUI, Y_HUNGY_GUI + HEIGHT_HUNGY_GUI * 2, WIDTH_HUNGY_GUI, LEVEL_HUNGY_GUI));
}

void createGUI(barThirst &gui, Texture *texture)
{
	gui.bottle = new Sprite;
	gui.levelThirst = new Sprite;

	// �����
	gui.bottle->setTexture(*texture);
	gui.bottle->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI, WIDTH_THIRST_GUI, HEIGHT_THIRST_GUI));

	gui.levelThirst->setTexture(*texture);
	gui.levelThirst->setTextureRect(IntRect(X_THIRST_GUI, Y_THIRST_GUI + HEIGHT_THIRST_GUI, WIDTH_THIRST_GUI, LEVEL_THIRST));

}

void createGUI(sf::Sprite &itemInfoOverPanel, Texture &texture)
{
	itemInfoOverPanel.setTexture(texture);
	itemInfoOverPanel.setOrigin(WIDTH_ITEM_OVER_PANEL_INFO / 2, HEIGHT_ITEM_OVER_PANEL_INFO / 2);
	itemInfoOverPanel.setTextureRect(IntRect(X_ITEM_OVER_PANEL_INFO, Y_ITEM_OVER_PANEL_INFO,
																	 WIDTH_ITEM_OVER_PANEL_INFO, HEIGHT_ITEM_OVER_PANEL_INFO));
}

void createGUI(itemFeatures& gui, Texture *textureWidgets, Texture *textureBars)
{


	gui.cutSprite = new Sprite;
	gui.crashSprite = new Sprite;
	gui.hungrySprite = new Sprite;
	gui.thirstSprite = new Sprite;

	gui.crashSprite->setTexture(*textureBars);
	gui.crashSprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.crashSprite->setTextureRect(IntRect(X_CRASH_DAMAGE_GUI, Y_CRASH_DAMAGE_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));

	gui.cutSprite->setTexture(*textureBars);
	gui.cutSprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.cutSprite->setTextureRect(IntRect(X_CUT_DAMAGE_GUI, Y_CUT_DAMAGE_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));

	gui.hungrySprite->setTexture(*textureBars);
	gui.hungrySprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.hungrySprite->setTextureRect(IntRect(X_HUNGRY_ITEM_GUI, Y_HUNGRY_ITEM_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));

	gui.thirstSprite->setTexture(*textureBars);
	gui.thirstSprite->setOrigin(WIDTH_DAMAGE_GUI / 2, HEIGHT_DAMAGE_GUI / 2);
	gui.thirstSprite->setTextureRect(IntRect(X_THIRST_ITEM_GUI, Y_THIRST_ITEM_GUI, WIDTH_DAMAGE_GUI, HEIGHT_DAMAGE_GUI));
}

void createGUI(barMainFeatures &gui, Texture *texture)
{
	gui.bar = new Sprite;
	gui.levelHealth = new Sprite;
	gui.levelStamina = new Sprite;
	gui.levelMana = new Sprite;

	// ��������
	gui.bar->setTexture(*texture);
	gui.bar->setTextureRect(IntRect(X_HEALTH_GUI, Y_HEALTH_GUI, WIDTH_BARS_GUI, HEIGHT_BARS_GUI));

	gui.levelHealth->setTexture(*texture);
	gui.levelHealth->setTextureRect(IntRect(X_LEVEL_HEALTH_GUI, Y_LEVEL_HEALTH_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));

	gui.levelStamina->setTexture(*texture);
	gui.levelStamina->setTextureRect(IntRect(X_LEVEL_STAMINA_GUI, Y_LEVEL_STAMINA_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));

	gui.levelMana->setTexture(*texture);
	gui.levelMana->setTextureRect(IntRect(X_LEVEL_MANA_GUI, Y_LEVEL_MANA_GUI, WIDTH_LEVEL_BAR_GUI, HEIGHT_LEVEL_BAR_GUI));
}