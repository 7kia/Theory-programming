#include <SFML/Graphics.hpp>

#include "Program.h"

using namespace sf;

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;


void processEvents(Program &program, const Time & deltaTime)
{
	Event event;
	RenderWindow &window = *program.window;
	while (window.pollEvent(event)) {
		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(mousePos);

		Keyboard::Key pressKey = event.key.code;

		Text& textError = program.textProgram->texts[idText::errorText];
		if (textError.getString() != DIRECTORY_EMPTY) {
			///////////////////////////////////////////////////
			// Проверяем одну стрелки
			if (event.type == Event::KeyPressed) {
				if (pressKey == Keyboard::Left) {
					actionLeft(program);
				} else if (pressKey == Keyboard::Right) {
					actionRight(program);
				}
			}

			if (event.type == Event::MouseButtonPressed) {
				if (pressKey == Mouse::Left) {
					Sprite &arrowLeft = *program.gui->arrowLeft;
					Sprite &arrowRight = *program.gui->arrowRight;
					if (arrowLeft.getGlobalBounds().contains(pos)) {
						actionLeft(program);
					} else if (arrowRight.getGlobalBounds().contains(pos)) {
						actionRight(program);
					}
				}
			}

			///////////////////////////////////////////////////
		}

		/////////////////////////////////////////////////////////////
		// Для обновления окна
		if (event.type == sf::Event::Resized) {
			unsigned int width = window.getSize().x;
			unsigned int height = window.getSize().y;
			program.widthMainWindow = width;// ИСПРАВЬ
			program.heightMainWindow = height;
			window.create(VideoMode(width, height), program.currentTitle);
		}
		/////////////////////////////////////////////////////////////


		// Окно закрыли
		if (event.type == Event::Closed) {
			window.close();
		}

	}
}

void render(Program & program)
{
	RenderWindow &window = *program.window;
	Vector2u sizeWindow = window.getSize();
	Vector2f centerWindow = { (float)sizeWindow.x / 2, (float)sizeWindow.y / 2 };
	window.clear(COLOR_GREY);

	//////////////////////////////////////////////
	// GUI
	setPositionGui(program);
	window.draw(*program.gui->arrowLeft);
	window.draw(*program.gui->arrowRight);
	if (program.currentTitle != TITLE_PROGRAM) {
		// Масштабирование изображения
		Vector2u sizeImage = program.textureCurrentImage->getSize();
		Vector2f &scaleImage = *program.scaleImage;
		Vector2f &sourseScale = *program.sourseScale;

		int shiftBorder = 200;
		if (sizeImage.x + WIDTH_GUI_ELEMENT + shiftBorder > sizeWindow.x) {
			scaleImage = { (float)sizeImage.x / sizeWindow.x,  (float)sizeImage.x / sizeWindow.x };
			sourseScale = { 1 / scaleImage.x ,  1 / scaleImage.x };
			program.currentImage->setScale(scaleImage);
		} else if (sizeImage.y + HEIGHT_GUI_ELEMENT + shiftBorder > sizeWindow.y) {
			scaleImage = { (float)sizeImage.y / sizeWindow.y,  (float)sizeImage.y / sizeWindow.y };
			sourseScale = { 1 / scaleImage.y ,  1 / scaleImage.y };
			program.currentImage->setScale(scaleImage);
		} else {
			program.currentImage->setScale(sourseScale);
			sourseScale = { 1.f, 1.f };
			scaleImage = { 1.f, 1.f };
		}

		program.currentImage->setPosition(centerWindow);
		window.draw(*program.currentImage);
	}


	//////////////////////////////////////////////
	// Текст GUI
	for (size_t i = 0; i < idText::amountTextsGui; i++) {
		if (i != idText::errorText || program.currentTitle == TITLE_PROGRAM) {
			window.draw(program.textProgram->texts[i]);
		}
	}

	window.display();
}

void startProgram(char argv[])
{
	Program *mainProgram = new Program();
	initializeProgram(*mainProgram, argv);

	// Если нет изображений
	Text* textError = &mainProgram->textProgram->texts[idText::errorText];
	if (textError->getString() != INVALID_PATH) {
		if (mainProgram->pathsImages->end() == mainProgram->pathsImages->begin()) {
			textError->setString(DIRECTORY_EMPTY);// ИСПРаВЬ
		} else {
			textError->setString("");
			initializeImage(*mainProgram);
		}
	}
	
	
	RenderWindow &window = *mainProgram->window;

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TIME_PER_FRAME)
			{
				timeSinceLastUpdate -= TIME_PER_FRAME;
				processEvents(*mainProgram, TIME_PER_FRAME);
				if (textError->getString() != DIRECTORY_EMPTY
						&& textError->getString() != INVALID_PATH) {
					if (*mainProgram->currentPath != mainProgram->newPath) {
						initializeImage(*mainProgram);
						printf("sdf\n");
					}
				}

			}
		
		
		render(*mainProgram);
	}
	destroyProgram(*mainProgram);
}

int main(int argc, char *argv[])
{
	startProgram(argv[1]);
	return 0;
}

