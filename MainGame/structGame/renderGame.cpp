#include  "renderGame.h"

using namespace sf;
using namespace std;

void Game::render()
{
	window.clear();

	Entity &mainPerson = world.Enemys[0];
	View &view = world.view;
	Listener &listener = world.listener;

	mainPerson.updateView(view, listener, window);
	Vector2f centerWindow = window.getView().getCenter();

	Vector2f sizeWindow = { float(DEFAULT_WIDTH_WINDOW), float(DEFAULT_HEIGHT_WINDOW) };
	FloatRect rectWindow = FloatRect(centerWindow - sizeWindow, sizeWindow + centerWindow);

	renderMap(rectWindow);
	renderItems(rectWindow);


	mainPerson.renderCurrentItem(window);
	window.draw(*mainPerson.spriteEntity);

	renderEntitys(rectWindow);
	renderUnlifeObjects(rectWindow);

	gui.setPositionGui(window, mainPerson, world.Enemys, textGame);

	renderGui();

	window.display();
}

void Game::renderMap(FloatRect const& rectWindow)
{
	Field &field = world.field;

	Entity &mainPerson = world.Enemys[0];
	int l = mainPerson.currentLevelFloor;
	int lowBorder = l - 1;
	if (lowBorder < 0)
		lowBorder = 0;
	int topBorder = l + 2;
	if (topBorder > HEIGHT_MAP - 1)
		topBorder = HEIGHT_MAP - 1;

	l = lowBorder;
	FloatRect rectWallSprite;
	FloatRect rectFloorSprite;
	while (l <= topBorder) {

		for (int i = 0; i < LONG_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP - BORDER1; j++) {
				field.setTypeSprite(mainPerson.currentLevelFloor, l, i, j);

				drawInWindow(*field.floorSprite, rectWindow);
				drawInWindow(*field.wallSprite, rectWindow);
			}
		}

		l++;
	}
}

void Game::renderItems(FloatRect const& rectWindow)
{
	vector<Item> &items = world.items;
	int levelItem;
	int levelPlayer;
	for (int i = 0; i != items.size(); ++i) {
		levelItem = items[i].currentLevel;

		Entity &mainPerson = world.Enemys[0];
		levelPlayer = mainPerson.currentLevelFloor;
		if (levelItem >= levelPlayer
			&& levelItem <= levelPlayer + 2) {


			if (levelItem == levelPlayer) {
				items[i].mainSprite->setColor(DOWN_VIEW);
			} else if (levelItem == levelPlayer + 1) {
				items[i].mainSprite->setColor(NORMAL_VIEW);
			} else if (levelItem == levelPlayer + 2) {
				items[i].mainSprite->setColor(UP_VIEW);
			}

			drawInWindow(*items[i].mainSprite, rectWindow);
		}

	}
}

void Game::renderEntitys(FloatRect const& rectWindow)
{
	vector<Entity>& Enemys = world.Enemys;

	int enemyLevel;

	Entity &mainPerson = world.Enemys[0];
	const int personLevel = mainPerson.currentLevelFloor;
	for (int i = 1; i < Enemys.size(); ++i) {
		enemyLevel = Enemys[i].currentLevelFloor;
		if (enemyLevel >= personLevel - 1 && enemyLevel <= personLevel + 1) {

			
			Enemys[i].renderCurrentItem(window);

			Color currentColor;
			if (personLevel) {
				currentColor = NORMAL_COLOR;
			}
			else if (personLevel - 1) {
				currentColor = DOWN_VIEW;
			}
			else if (personLevel + 1) {
				currentColor = UP_VIEW;
			}
			Enemys[i].spriteEntity->setColor(currentColor);

			drawInWindow(*Enemys[i].spriteEntity, rectWindow);
		}

	}

}

void Game::renderUnlifeObjects(FloatRect const& rectWindow)
{
	Entity &mainPerson = world.Enemys[0];
	int levelPerson = mainPerson.currentLevelFloor;
	int levelObject;
	vector<UnlifeObject> &unlifeObjects = world.unlifeObjects;
	bool inView;
	for (int i = 0; i != unlifeObjects.size(); ++i) {
		levelObject = unlifeObjects[i].currentLevel;

		inView = levelObject >= levelPerson
				&& levelObject <= levelPerson + 2;

		if (inView) {
			if (levelObject == levelPerson) {
				unlifeObjects[i].spriteObject->setColor(DOWN_VIEW);
				unlifeObjects[i].transparentSpiteObject->setColor(DOWN_VIEW);
			} else if (levelObject == levelPerson + 2) {
				unlifeObjects[i].spriteObject->setColor(UP_VIEW);
				unlifeObjects[i].transparentSpiteObject->setColor(UP_VIEW);
			}

			drawInWindow(*unlifeObjects[i].spriteObject, rectWindow);
			drawInWindow(*unlifeObjects[i].transparentSpiteObject, rectWindow);
		}

	}
}

void Game::drawAwardItems(vector<Vector2i> &listAward)
{
	int currentLevel = difficult;
	TypeItem *typesItems = world.typesObjects.typesItem;

	Entity *mainPerson = world.mainPerson;
	View &view = world.view;

	Vector2f centerWindow = view.getCenter();
	Vector2f posImage = centerWindow;
	size_t amountTypeItems = listAward.size();

	float shift = float(amountTypeItems / 2);
	if (amountTypeItems % 2 == 0)
	{
		shift -= 0.5f;
	}
	posImage.x -= shift * (SIZE_ITEM + DISTANSE_BETWEEN_AWARD_ITEMS);

	// TODO
	Text *currentText = &textGame.texts[idText::panelText];
	Vector2f posText = centerWindow;

	Item *drawItem = new Item;

	for (size_t i = 0; i < listAward.size(); i++) {
		string amountItems;
		intToString(listAward[i].y, amountItems);
		currentText->setString(amountItems);
		int sizeText = currentText->getCharacterSize();
		float middleText = float(computeMiddleString(*currentText));

		posText = posImage;
		posText.y += SIZE_ITEM;
		posText.x -= middleText;
		currentText->setPosition(posText);
		window.draw(*currentText);


		drawItem->setType(typesItems[listAward[i].x]);
		drawItem->mainSprite->setPosition(posImage);
		drawItem->mainSprite->setScale(SCALE_AWARD_ITEMS, SCALE_AWARD_ITEMS);
		posImage.x += DISTANSE_BETWEEN_AWARD_ITEMS + SIZE_ITEM;
		window.draw(*drawItem->mainSprite);
	}

	delete drawItem;

}

void Game::setPositionAwardText()
{
	Entity *mainPerson = world.mainPerson;
	View &view = world.view;

	Vector2f centerWindow = view.getCenter();
	Vector2f posText = centerWindow;

	setPositionTitleAward(centerWindow, posText);
	setPositionHelpTextAward(centerWindow, posText);
}


void Game::setPositionTitleAward(Vector2f const& centerWindow, Vector2f &posText)
{
	posText = centerWindow;
	Text *currentText = &textGame.texts[idText::panelTitleText];

	currentText->setString(TEXT_AWARD);
	int sizeText = currentText->getCharacterSize();
	float middleText = float(computeMiddleString(*currentText));
	posText.y += -HEIGHT_AWARD_GUI / 2 + SHIFT_Y_AWARD_TITLE_TEXT;
	posText.x -= middleText;

	currentText->setPosition(posText);
}

void Game::setPositionHelpTextAward(sf::Vector2f const & centerWindow, sf::Vector2f & posText)
{
	Text *currentText = &textGame.texts[idText::panelTitleText];
	int sizeText = currentText->getCharacterSize();

	posText.x = centerWindow.x;
	currentText = &textGame.texts[idText::panelHelpText];
	currentText->setString(TEXT_HELP_AWARD);

	float middleText = float(computeMiddleString(*currentText));
	posText.y += SHIFT_Y_AWARD_HELP_TEXT + sizeText;
	posText.x -= middleText;

	currentText->setPosition(posText);

	if (updateDifficult) {
		posText.x += middleText;
		setPositionWaveText(posText);
	}
}


void Game::setPositionWaveText(sf::Vector2f& posText)
{
	Text *currentText = &textGame.texts[idText::panelTitleText];
	int sizeText = currentText->getCharacterSize();

	currentText = &textGame.texts[idText::panelHelpText];

	string numberWave;
	intToString(difficult, numberWave);
	String inputString = TEXT_NUMBER_WAVE_START;
	inputString += String(numberWave);
	inputString += TEXT_NUMBER_WAVE_END;

	currentText->setString(inputString);

	float middleText = float(computeMiddleString(*currentText));
	posText.y += sizeText;
	posText.x -= middleText;

	currentText->setPosition(posText);
}

void Game::setPositionEndGameText()
{
	View &view = world.view;

	Vector2f centerWindow = view.getCenter();
	Text *currentText = &textGame.texts[idText::panelTitleText];
	Vector2f posText = centerWindow;

	currentText->setString(TEXT_VICTORY);
	int sizeText = currentText->getCharacterSize();
	float middleText = float(computeMiddleString(*currentText));
	posText.y += -HEIGHT_AWARD_GUI / 2 + SHIFT_Y_AWARD_TITLE_TEXT;
	posText.x -= middleText;

	currentText->setPosition(posText);


	currentText = &textGame.texts[idText::panelHelpText];
	posText.x = centerWindow.x;

	currentText->setString(TEXT_UNDER_VICTORY);

	middleText = float(computeMiddleString(*currentText));
	posText.y += SHIFT_Y_AWARD_HELP_TEXT + sizeText;
	posText.x -= middleText;

	currentText->setPosition(posText);

}


void Game::drawAwardPanel()
{
	panel &awardPanel = gui.panels.awardPanel;

	awardPanel.draw = true;
	setPositionAwardText();

	playGlobalSound(idSoundPaths::waveEndSound, world.databaseSound);

	stateGame = pauseState;
}

void Game::drawEndGamepanel()
{
	panel &awardPanel = gui.panels.awardPanel;

	awardPanel.draw = true;
	setPositionEndGameText();

	playGlobalSound(idSoundPaths::levelUpSound, world.databaseSound);

	stateGame = endGameState;
	updateDifficult = false;
}

void Game::renderGui()
{
	if (stateGame == pauseState
			|| stateGame == endGameState) {

		View &view = world.view;

		Vector2f centerWindow = view.getCenter();
		panels &panels = gui.panels;

		panel &panel = panels.awardPanel;
		Sprite &sprite = panel.sprite;

		if (panel.draw) {
			panel.setPosition(centerWindow);
			window.draw(sprite);

			window.draw(textGame.texts[idText::panelTitleText]);		
			window.draw(textGame.texts[idText::panelHelpText]);

			if (updateDifficult) {
				vector<Vector2i> award;

				for (size_t i = 0; i < awardForWave.size(); i++) {
					award.push_back((awardForWave)[i]);
				}
				for (size_t i = 0; i < awardForLevel[difficult].size(); i++) {
					award.push_back(awardForLevel[difficult][i]);
				}

				drawAwardItems(award);

			}// TODO
			else if(stateGame != endGameState)
			{
				drawAwardItems(awardForWave);
			}
		}

	}
}

bool isExitFromWindow(FloatRect const& rectWindow, FloatRect &rectObject)
{
	bool checkLeft = rectObject.left > rectWindow.left;
	bool checkRight = rectObject.left < rectWindow.left + rectWindow.width;
	bool checkTop = rectObject.top + rectObject.height < rectWindow.top;
	bool checkLow = rectObject.top < rectWindow.top + rectWindow.height;

	if ((checkLeft || checkRight) && (checkTop || checkLow))
	{
		return true;
	}
	return false;
}

void Game::drawInWindow(sf::Sprite &sprite, sf::FloatRect const& rectWindow)
{
	FloatRect rectSprite = sprite.getGlobalBounds();
	if (rectSprite != NULL_RECT) {
		if (isExitFromWindow(rectWindow, rectSprite)) {
			window.draw(sprite);
		}
	}
}

void Game::showFPS(const Time timeSinceLastUpdate)
{
	float currentWorldTime = world.worldTime.getElapsedTime().asSeconds();

	if (currentWorldTime - int(currentWorldTime) <= faultWorldTime) {
		world.lastSecond += 1.f;
		printf("FPS: %f\n", 1.f / timeSinceLastUpdate.asSeconds());
	}
}