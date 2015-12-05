#pragma once
#include "CheckBox.h"
#include "LineEdit.h"

namespace featureWindow {
const float DEFAULT_WIDTH_WINDOW = 800;
const float DEFAULT_HEIGHT_WINDOW = 600;
const sf::Vector2f SIZE_WINDOW = { DEFAULT_WIDTH_WINDOW , DEFAULT_HEIGHT_WINDOW };
const sf::Vector2f CENTER_WINDOW = { float(SIZE_WINDOW.x / 2) , float(SIZE_WINDOW.y / 2) };

const std::string TITLE_PROGRAM = "Lab 9.1 \"Elements GUI\"";
const sf::Color CLEAR_COLOR(200, 200, 200, 255);
};

struct Program
{
	sf::RenderWindow window;
	checkBox *chechBox1;
	lineEdit *lineEdit1;
	Assets assets;

	Program();
	~Program();

	void processEvents();
	void processGUI(sf::Event &event);

	void update(float deltaTime);
	void render();
};