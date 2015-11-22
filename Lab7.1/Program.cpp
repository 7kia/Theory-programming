#include "Program.h"

const char currentFolder[] = "c:\\Study\\»Ëœ\\Programs\\Lab5\\";

using namespace sf;
using namespace std;

void initializeProgram(Program & program)
{
	program.window.create(VideoMode(DEFAULT_WIDTH_WINDOW, DEFAULT_HEIGHT_WINDOW), TITLE_PROGRAM);

	initializeClock(program.Clock);
	initializeTexts(program.textProgram);
	
}


void setPositionGui(Program & program)
{

	Vector2u sizeWindow = program.window.getSize();
	Vector2i centerWindow = { int(sizeWindow.x / 2), int(sizeWindow.y / 2) };//{ sizeWindow.x / 2, sizeWindow.y / 2 };


}

void destroyProgram(Program & program)
{
	delete &program;
}