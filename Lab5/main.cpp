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
				} else if (pressKey == Keyboard::Add) {
					actionZoomPlus(program, pos);
				} else if (pressKey == Keyboard::Subtract) {
					actionZoomMinus(program, pos);
				}
			}

			if (event.type == Event::MouseMoved && program.isShift && program.isZoom) { 
				Vector2f movemoment = { 0.f, 0.f };
				
				program.newPositionMouse = pos;

				if (program.oldPositionMouse.x > program.newPositionMouse.x) {
					movemoment.x = -SPEED_SHIFT;
				}
				if (program.oldPositionMouse.x < program.newPositionMouse.x) {
					movemoment.x = +SPEED_SHIFT;
				}
				if (program.oldPositionMouse.y > program.newPositionMouse.y) {
					movemoment.y = -SPEED_SHIFT;
				}
				if (program.oldPositionMouse.y < program.newPositionMouse.y) {
					movemoment.y = +SPEED_SHIFT;
				}
				
				program.oldPositionMouse = pos;

				program.currentImage->move(movemoment);
				updateView(program, deltaTime);
			}
			
			if (Mouse::isButtonPressed(Mouse::Left)) {
				program.oldPositionMouse.x = pos.x;
				program.oldPositionMouse.y = pos.y;
				program.isShift = true;
			} else {
				program.isShift = false;
			} 

			if (event.type == Event::MouseButtonPressed) {
				if (pressKey == Mouse::Left) {
					Sprite &arrowLeft = *program.gui->arrowLeft;
					Sprite &arrowRight = *program.gui->arrowRight;
					Sprite &plus = *program.gui->plus;
					Sprite &minus = *program.gui->minus;
					if (arrowLeft.getGlobalBounds().contains(pos)) {
						if (program.isZoom == false)
							actionLeft(program);
					} else if (arrowRight.getGlobalBounds().contains(pos)) {
						if(program.isZoom == false)
							actionRight(program);
					} else if (plus.getGlobalBounds().contains(pos)) {
						actionZoomPlus(program, pos);
					} else if (minus.getGlobalBounds().contains(pos)) {
						actionZoomMinus(program, pos);
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

	if(program.isZoom == false)
	{
		window.draw(*program.gui->arrowLeft);
	window.draw(*program.gui->arrowRight);
	window.draw(*program.gui->plus);
	window.draw(*program.gui->minus);
	}
	
	if (program.currentTitle != TITLE_PROGRAM) {
		if (program.isZoom == false) {
			Vector2u sizeImage = program.textureCurrentImage->getSize();
			Vector2f &scaleImage = *program.scaleImage;
			Vector2f &sourseScale = *program.sourseScale;

			int shiftBorder = 200;
			if (sizeImage.x + WIDTH_GUI_ELEMENT + shiftBorder > sizeWindow.x) {
				scaleImage = { float(sizeWindow.x) / (sizeImage.x + WIDTH_GUI_ELEMENT + shiftBorder),
					float(sizeWindow.x) / (sizeImage.x + WIDTH_GUI_ELEMENT + shiftBorder) };
				sourseScale = { 1 / scaleImage.x ,  1 / scaleImage.x };
				program.currentImage->setScale(scaleImage);
			} else if (sizeImage.y + HEIGHT_GUI_ELEMENT + shiftBorder > sizeWindow.y) {
				scaleImage = { float(sizeWindow.y) / (sizeImage.y + HEIGHT_GUI_ELEMENT + shiftBorder),
					float(sizeWindow.y) / (sizeImage.y + HEIGHT_GUI_ELEMENT + shiftBorder) };
				sourseScale = { 1 / scaleImage.y ,  1 / scaleImage.y };
				program.currentImage->setScale(scaleImage);
			} else {
				program.currentImage->setScale(sourseScale);
				sourseScale = { 1.f, 1.f };
				scaleImage = { 1.f, 1.f };
			}
			program.currentImage->setPosition(centerWindow);
		}

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

void startProgram()
{
	Program *mainProgram = new Program();
	initializeProgram(*mainProgram);
	// Если нет изображений
	Text* textError = &mainProgram->textProgram->texts[idText::errorText];
	if (textError->getString() != INVALID_PATH) {
		if (mainProgram->pathsImages->end() == mainProgram->pathsImages->begin()) {
			textError->setString(DIRECTORY_EMPTY);
		} else {
			textError->setString("");
			initializeImage(*mainProgram);
			printf("sdf\n");
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
				if (textError->getString() != DIRECTORY_EMPTY && textError->getString() != INVALID_PATH) {
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

int main()
{
	startProgram();
	return 0;
}

