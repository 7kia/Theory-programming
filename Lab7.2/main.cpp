#include <SFML/Graphics.hpp>

#include "Program.h"

using namespace sf;
using namespace std;

const float PER_FRAME = 1.f / 60.f;
const Time TIME_PER_FRAME = seconds(PER_FRAME);


void startProgram()
{
	Program *mainProgram = new Program();

	RenderWindow &window = mainProgram->window;

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
}

int main()
{
	startProgram();
	return 0;
}

