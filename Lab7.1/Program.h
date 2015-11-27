#pragma once
#include "programClock.h"

const std::string TITLE_PROGRAM = "Clock";
const sf::Color COLOR_GREY(122, 122, 122, 255);
const int ANTIALIASING = 8;
struct Program
{
	sf::RenderWindow *window;
	programClock Clock;

	Program();
	~Program();
	void processEvents();
	void update();
	void render();
};