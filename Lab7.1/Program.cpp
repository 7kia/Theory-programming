#include "Program.h"

const char currentFolder[] = "c:\\Study\\»Ëœ\\Programs\\Lab5\\";

using namespace sf;
using namespace std;

Program::Program()
{
	settings.antialiasingLevel = 8;
	window.create(VideoMode(DEFAULT_WIDTH_WINDOW, DEFAULT_HEIGHT_WINDOW), TITLE_PROGRAM, Style::Default, settings);
	initializeClock(Clock);
}

void Program::processEvents()
{
	Event event;
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Resized) {
			window.setSize(SIZE_WINDOW);
		}

		if (event.type == Event::Closed) {
			window.close();
		}

	}
}

void Program::update()
{
	Clock.update();
}

void Program::render()
{
	window.clear(COLOR_GREY);
	Clock.draw(window);
	window.display();
}

void destroyProgram(Program & program)
{
	delete &program;
}