#include "Program.h"

using namespace sf;
using namespace std;

Program::Program()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window = new RenderWindow(VideoMode(unsigned int(SIZE_WINDOW.x), unsigned int(SIZE_WINDOW.y)),
														TITLE_PROGRAM, Style::Default, settings);
}

Program::~Program()
{
	delete window;
}

void Program::processEvents()
{
	Event event;
	while (window->pollEvent(event)) {

		if (event.type == sf::Event::Resized) {
			window->setSize(Vector2u(SIZE_WINDOW));
		}

		if (event.type == Event::Closed) {
			window->close();
		}

	}
}

void Program::update()
{
	Clock.update();
}

void Program::render()
{
	window->clear(COLOR_GREY);
	Clock.draw(*window);
	window->display();
}