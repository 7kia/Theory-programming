#include <SFML/Graphics.hpp>

#include "Program.h"

using namespace sf;

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;


void processEvents(Program &program, const Time & deltaTime)
{
	Event event;
	RenderWindow &window = program.window;
	while (window.pollEvent(event)) {
		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(mousePos);

		Keyboard::Key pressKey = event.key.code;

		/////////////////////////////////////////////////////////////
		// Для обновления окна
		if (event.type == sf::Event::Resized) {
			window.setSize(SIZE_WINDOW);
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
	RenderWindow &window = program.window;
	Vector2u sizeWindow = window.getSize();
	Vector2f centerWindow = { float(sizeWindow.x) / 2, float(sizeWindow.y) / 2 };
	window.clear(COLOR_GREY);


	//////////////////////////////////////////////
	// Текст Clock
	program.Clock.render(window);


	window.display();
}

void startProgram()
{
	Program *mainProgram = new Program();
	initializeProgram(*mainProgram);
	// Если нет изображений

	RenderWindow &window = mainProgram->window;

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TIME_PER_FRAME)
			{
				timeSinceLastUpdate -= TIME_PER_FRAME;
				processEvents(*mainProgram, TIME_PER_FRAME);
				

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

