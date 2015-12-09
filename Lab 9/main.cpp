#include <SFML/Graphics.hpp>

#include "Program.h"

using namespace sf;
using namespace std;

const float PER_FRAME = 1.f / 60.f;
const Time TIME_PER_FRAME = seconds(PER_FRAME);

void renameTitle(bool cheked, RenderWindow &window)
{
	if (cheked) {
		window.setTitle(featureWindow::TITLE_PROGRAM);
	}
	else {
		window.setTitle(featureWindow::TWO_TITLE_PROGRAM);
	}
}


void startProgram()
{
	//setlocale(LC_ALL, "Windows-1251");

	Program *mainProgram = new Program();

	RenderWindow &window = mainProgram->window;

	mainProgram->chechBox1->handler=[&window](bool cheked)
	{
		if (cheked) {
			window.setTitle(featureWindow::TITLE_PROGRAM);
		}
		else {
			window.setTitle(featureWindow::TWO_TITLE_PROGRAM);
		}
	};


	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;

			mainProgram->processEvents();
			mainProgram->update(PER_FRAME);
			mainProgram->render();
		}

	}

	delete mainProgram;
}

int main()
{
	startProgram();
	return 0;
}

