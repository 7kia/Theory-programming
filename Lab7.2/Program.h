#pragma once
#include "blockConstuction.h"

const std::string TITLE_PROGRAM = "Lab 7.2 \"Animation\"";
const sf::Color CLEAR_COLOR(200, 200, 200, 255);
const int ANTIALIASING = 8;
struct Program
{
	sf::RenderWindow window;
	blockConstuction constuction;

	Program();
	~Program();
	void processEvents();
	void update(float deltaTime);
	void render();
};