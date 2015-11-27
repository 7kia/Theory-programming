#include <SFML/Graphics.hpp>

#include "Program.h"

using namespace sf;
using namespace std;

void startProgram()
{
	Program *mainProgram = new Program();

	RenderWindow &window = *mainProgram->window;

	while (window.isOpen())
	{
		mainProgram->processEvents();
		mainProgram->update();
		mainProgram->render();
	}
}

int main()
{
	startProgram();
	return 0;
}

