#include "Program.h"

using namespace sf;
using namespace std;
using namespace featureWindow;

Program::Program()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(unsigned int(SIZE_WINDOW.x), unsigned int(SIZE_WINDOW.y)),
														TITLE_PROGRAM, Style::Default, settings);

	Vector2f pos = CENTER_WINDOW;
	chechBox1 = new checkBox(pos);

	pos.y += featureCheckBox::SIZE_CHECKBOX.y * 2;
	lineEdit1 = new lineEdit(pos, assets);

	chechBox1->handler = [&](bool cheked) {
		if (cheked) {
			window.setTitle(featureWindow::TITLE_PROGRAM);
		}
		else {
			window.setTitle(featureWindow::TWO_TITLE_PROGRAM);
		}
	};
}

Program::~Program()
{
	delete chechBox1;
	delete lineEdit1;
}

void Program::processEvents()
{
	Event event;
	while (window.pollEvent(event)) {

		processGUI(event);

		switch (event.type) {
		case sf::Event::Resized:
			window.setSize(Vector2u(window.getSize()));
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}

	}


}

void Program::processGUI(Event& event)
{
	if (chechBox1->OnEvent(event)) {
		chechBox1->handler(chechBox1->IsChecked());
	}
	if(lineEdit1->OnEvent(event))
	{
		
	}
}

void Program::update(float deltaTime)
{
}

void Program::render()
{
	window.clear(CLEAR_COLOR);
	chechBox1->Draw(window);
	lineEdit1->Draw(window);
	window.display();
}