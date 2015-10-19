#include <SFML/Graphics.hpp>

#include "Program.h"

using namespace sf;

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;


void processEvents(Program &program)
{
	Event event;
	RenderWindow &window = *program.window;
	while (window.pollEvent(event)) {
		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(mousePos);

		Keyboard::Key pressKey = event.key.code;
		///////////////////////////////////////////////////
		// Проверяем одну стрелки
		if (pressKey == Keyboard::Left) {
			actionLeft(program);
		}
		else if (pressKey == Keyboard::Right) {
			actionRight(program);
		}

		if (pressKey == Mouse::Left) {
			Sprite &arrowLeft = *program.gui->arrowLeft;
			Sprite &arrowRight = *program.gui->arrowRight;
			if (arrowLeft.getGlobalBounds().contains(pos)) {
				actionLeft(program);
			}
			else if (arrowRight.getGlobalBounds().contains(pos)) {
				actionRight(program);
			}
		}
		///////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////
		// Для обновления окна
		if (event.type == sf::Event::Resized) {
			unsigned int width = window.getSize().x;
			unsigned int height = window.getSize().y;
			program.widthMainWindow = width;// ИСПРАВЬ
			program.heightMainWindow = height;
			window.create(VideoMode(width, height), TITLE_PROGRAM);
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
	window.clear(Color(COLOR_GREY[0], COLOR_GREY[1], COLOR_GREY[2], COLOR_GREY[3]));

	//////////////////////////////////////////////
	// GUI
	setPositionGui(program);
	window.draw(*program.gui->arrowLeft);
	window.draw(*program.gui->arrowRight);
	window.draw(*program.currentImage);

	//////////////////////////////////////////////
	// Текст GUI
	for (size_t i = 0; i < idText::amountTextsGui; i++) {
		window.draw(program.textProgram->texts[i]);
	}

	window.display();
}

void startProgram()
{
	Program *mainProgram = new Program();
	initializeProgram(*mainProgram);

	RenderWindow &window = *mainProgram->window;

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents(*mainProgram);
			initializeImage(*mainProgram);

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

