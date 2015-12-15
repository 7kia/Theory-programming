#include "GuiBarMainFeatures.h"

void barMainFeatures::renderBar(int& current, int& max, sf::Sprite& sprite, Vector2f scale, featuresSprite &sizes, TextGame& textGame,
																sf::Vector2f& position, sf::RenderWindow& window)
{
	render(current, max, sprite, scale,
				 sizes, position, window);
	renderText(current, max, scale,
						 position, window, textGame);
}


void barMainFeatures::render(int &current, int& max, Sprite &sprite, Vector2f scale,
														 featuresSprite &featuresSprite, Vector2f &position, RenderWindow &window)
{
	
	bar.setPosition(position);
	bar.setScale(scale);
	window.draw(bar);
	bar.setScale(normalSize);

	float level = float(current) / max;

	position.x += X_SHIFT_BARS * scale.x;
	position.y += Y_SHIFT_BARS * scale.y;
	int currentLevel = int(WIDTH_LEVEL_BAR_GUI * level);
	int pixelXpos = featuresSprite.pixPos.x;
	int pixelYpos = featuresSprite.pixPos.y;
	int height = featuresSprite.size.height;
	sprite.setTextureRect(IntRect(pixelXpos, pixelYpos, currentLevel, height));
	sprite.setPosition(position);
	sprite.setScale(scale);
	window.draw(sprite);
	sprite.setScale(normalSize);
}

void barMainFeatures::renderText(int &current, int& max, Vector2f scale,
																 Vector2f& position, RenderWindow& window, TextGame &textGame)
{
	Text* currentText = &textGame.texts[idText::levelBar];

	currentText->setString(toStringCharacter(current, max));

	// TODO
	float middleString = float(computeMiddleString(*currentText));
	position = { position.x + WIDTH_LEVEL_BAR_GUI / 2 - middleString, position.y - Y_SHIFT_BARS / 2 };
	//position.x += middleString;// *scale.x;
	// * scale.y
	//position.y += (HEIGHT_BARS_GUI / 2);

	currentText->setPosition(position);

	//currentText->setScale(scale);
	window.draw(*currentText);
	//currentText->setScale(normalSize);
}

void barMainFeatures::renderTextEnemy(Enemy &enemy, int & current, int & max, int shift,
																			RenderWindow & window, TextGame & textGame)
{
	Text *currentText = &textGame.texts[idText::levelBar];
	Vector2f pos;
	pos = enemy.spriteEntity->getPosition();
	pos.y -= Y_SHIFT_BARS * scaleGuiForEnemy.y;
	pos.y -= enemy.size.height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * shift;


	currentText->setString(toStringCharacter(current, max));

	pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
	currentText->setPosition(pos);

	window.draw(*currentText);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void barMainFeatures::renderDamageForEnemy(Enemy &enemy, TextGame &textGame, RenderWindow &window, int shift)
{
	Text *currentText = &textGame.texts[idText::inputDamage];

	Vector2f pos;
	pos = enemy.spriteEntity->getPosition();
	pos.y -= enemy.size.height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (3 + shift) + shiftEnemyDamage;

	// Если нанесли урон то отображаем
	int damage = enemy.damage.inputDamage;
	if (damage) {
		std::string stringDamage;
		intToString(damage, stringDamage);

		currentText->setString(stringDamage);


		pos.x -= currentText->getString().getSize() * currentText->getCharacterSize() / 4;
		currentText->setPosition(pos);
		window.draw(*currentText);
	}
}

void barMainFeatures::renderBarMainPerson(MainPerson &mainPerson, int &current, int &max, int shift, Sprite &sprite, featuresSprite &sizes,
																					featuresWindow features, TextGame &textGame)
{
	RenderWindow &window = *features.window;
	Vector2f centerWindow = features.center;
	Vector2u sizeWindow = features.size;
	Vector2f pos;
	pos.x = centerWindow.x - sizeWindow.x / 2;//* scaleGuiForEnemy.y
	pos.y = centerWindow.y + sizeWindow.y / 2 - float(HEIGHT_BARS_GUI)  * shift;

	renderBar(current, max, sprite, NORMAL_SCALE,
						sizes, textGame, pos, window);

}

void barMainFeatures::renderBarEnemy(Enemy &enemy, int &current, int &max, int shift, Sprite &sprite, featuresSprite &sizes,
																		 TextGame &textGame, RenderWindow &window)
{
	int shiftBar = enemy.mana.maxMana > 0;
	Vector2f pos = enemy.spriteEntity->getPosition();
	pos.x -= scaleGuiForEnemy.x * WIDTH_BARS_GUI / 2;
	pos.y -= enemy.size.height / 2 + scaleGuiForEnemy.y * HEIGHT_BARS_GUI * (shift + shiftBar);


	renderDamageForEnemy(enemy, textGame, window, shiftBar);

	if (max) {
		render(current, max, sprite, scaleGuiForEnemy,
					 sizes, pos, window);

		renderTextEnemy(enemy, current, max, shift,
										window, textGame);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////