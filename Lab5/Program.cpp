#include "Program.h"

const char currentFolder[] = "c:\\Study\\ИиП\\Programs\\Lab5\\";

using namespace sf;
using namespace std;

void initializeProgram(Program & program)
{
	unsigned int width = program.widthMainWindow;
	unsigned int height = program.heightMainWindow;
	program.window = new RenderWindow(VideoMode(width, height), TITLE_PROGRAM);
	program.currentTitle = TITLE_PROGRAM;

	program.gui = new GUI;
	program.textProgram = new TextProgram;

	program.pathsImages = new list<std::string>;
	program.textureCurrentImage = new Texture;
	program.currentImage = new Sprite;
	program.sizeImage = new Vector2u;

	program.scaleImage = new Vector2f;
	program.sourseScale = new Vector2f;

	*program.sourseScale = { 1.f, 1.f };
	*program.scaleImage = { 1.f, 1.f };
	// Загрузка путей
	program.pathsImages = new list<string>;

	program.searchImages();

	initializeGUI(*program.gui);
	initializeTexts(*program.textProgram);
	initializeImage(program);
}

void Program::searchImages()
{

	char stringInput[SIZE_STRING];
	for (size_t j = 0; j < AMOUNT_FORMATS; j++) {
		for (size_t i = 0; i < SIZE_STRING; i++) {
			stringInput[i] = 0;
		}
		strcpy_s(stringInput, currentFolder);
		strcat_s(stringInput, MASK);
		strcat_s(stringInput, formats[j]);
		searchImage(stringInput); 
		// Очистка строки перед следующим использованием

	}

	currentPath = pathsImages->begin();
}

void Program::searchImage(const char *path)
{
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {

			printf("%s: %s\n", (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "Folder" : "File", fd.cFileName);
			(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "Folder" : "File", pathsImages->push_back(fd.cFileName);
		}
		while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	} else {
		textProgram->texts[idText::errorText].setString(INVALID_PATH);
	}

};

void initializeImage(Program & program)
{
	Vector2u sizeWindow = program.window->getSize();
	Vector2u centerWindow = { sizeWindow.x / 2, sizeWindow.y / 2 };
	RenderWindow &window = *program.window;

	// Выбор текущего изображения
	list<string>& pathsImages = *program.pathsImages;

	for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
		if (program.currentPath == it) {

			unsigned int width = program.widthMainWindow;
			unsigned int height = program.heightMainWindow;

			//////////////////////////////////////////
			// Размер изображения
			std::fstream fp(*it, std::fstream::in);
			fp.seekp(0, std::ios::end);
			long size = fp.tellp();
			//////////////////////////////////////////
			if (program.textureCurrentImage->loadFromFile(*it)) {
				if (*it != program.currentTitle) {
					program.currentTitle = *it;
					program.newPath = *it;
					program.window->setTitle(*it);
				}

			} else {

				// Если изображение слишком большое
				if (size < MAX_SIZE) {
					program.textProgram->texts[idText::errorText].setString(FAILED_LOAD);
				} else {
					program.textProgram->texts[idText::errorText].setString(BIG_IMAGE);
				}
				program.currentTitle = TITLE_PROGRAM;
				program.window->setTitle(TITLE_PROGRAM);
			}
			break;
		}
	}

	program.currentImage->setTexture(*program.textureCurrentImage);



	Vector2f sizeImage = Vector2f(program.textureCurrentImage->getSize());

	program.currentImage->setPosition(Vector2f(centerWindow));
	program.currentImage->setOrigin(sizeImage.x / 2, sizeImage.y / 2);
	program.currentImage->setTextureRect(IntRect(0, 0, sizeImage.x, sizeImage.y));

}

void Program::setPositionsArrows(Vector2i centerWindow, Vector2u sizeWindow)
{
	Sprite& arrowLeft = *gui->arrowLeft;
	Sprite& arrowRight = *gui->arrowRight;
	Vector2i pos = centerWindow;
	
	//pos.x += - WIDTH_GUI_ELEMENT / 2;
	pos.y += sizeWindow.y / 2 - HEIGHT_GUI_ELEMENT - SHIFT_ARROWS;
	arrowLeft.setPosition(pos.x - WIDTH_GUI_ELEMENT, pos.y);
	arrowRight.setPosition(pos.x + WIDTH_GUI_ELEMENT, pos.y );
}

void Program::setPositionsZoomButtons(Vector2u sizeWindow)
{
	Sprite& plus = *gui->plus;
	Sprite& minus = *gui->minus;

	Vector2f pos;
	pos.x = sizeWindow.x - WIDTH_GUI_ELEMENT - SHIFT_ZOOM;
	pos.y = sizeWindow.y - HEIGHT_GUI_ELEMENT - SHIFT_ZOOM;
	plus.setPosition(pos.x, pos.y);
	minus.setPosition(pos.x - WIDTH_GUI_ELEMENT, pos.y);
}
void Program::setPositionErrorText(Vector2i centerWindow)
{
	bool isError = currentTitle == TITLE_PROGRAM;

	if (isError) {
		Vector2f pos = Vector2f(centerWindow);
		Text& currentText = textProgram->texts[idText::errorText];
		String inputString = currentText.getString();

		// делим на 2, чтобы получить нужный сдвиг
		size_t widthText = currentText.getCharacterSize() * inputString.getSize() / 2;
		pos.x -= widthText / 2;
		currentText.setPosition(Vector2f(pos));
	}
}

void setPositionGui(Program & program)
{

	Vector2u sizeWindow = program.window->getSize();
	Vector2i centerWindow = { int(sizeWindow.x / 2), int(sizeWindow.y / 2) };//{ sizeWindow.x / 2, sizeWindow.y / 2 };

	program.setPositionsArrows(centerWindow, sizeWindow);
	program.setPositionsZoomButtons(sizeWindow);
	program.setPositionErrorText(centerWindow);
}

void actionRight(Program & program) {

	if (program.isZoom == false) {
		list<string>& pathsImages = *program.pathsImages;

		std::list<string>::iterator next;
		for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
			if (program.currentPath == it && it != pathsImages.end()) {
				next = it++;
				if (next != pathsImages.end()) {
					program.currentPath = it;
					program.textureCurrentImage->loadFromFile(*it);
					program.window->setTitle(*it);
				} else {
					--it;
				}

			}
		}

	}
}

void actionLeft(Program & program) {

	if (program.isZoom == false) {
		list<string>& pathsImages = *program.pathsImages;
		for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
			if (program.currentPath == it && it != pathsImages.begin()) {
				--it;
				program.currentPath = it;
				program.textureCurrentImage->loadFromFile(*it);
				program.window->setTitle(*it);
			}
		}
	}


}

void updateView(Program & program, const Time & deltaTime)
{
	Sprite &currentImage = *program.currentImage;
	Vector2f sizeWindow = Vector2f(program.window->getSize());
	Vector2f centerWindow = { sizeWindow.x / 2, sizeWindow.y / 2 };

	Vector2f sizeCurrent = program.currentImage->getScale();

	Vector2f sizeImage = Vector2f(program.textureCurrentImage->getSize());
	Vector2f scaleImage = *program.sourseScale;


	float tempX = currentImage.getPosition().x;
	float tempY = currentImage.getPosition().y;

	float x = tempX;
	float y = tempY;


	if (sizeImage.x * sizeCurrent.x > sizeWindow.x) {
		float scale = 1 / sizeCurrent.x;
		float scaleForRightBorder = sizeCurrent.x;

		// leftBorder + sizeImage.x * scaleForRightBorder - sizeWindow.x * scale;
		int leftBorder = centerWindow.x - sizeImage.x / 2 * sizeCurrent.x + sizeWindow.x / 2;
		int rightBorder = centerWindow.x + sizeImage.x / 2 * sizeCurrent.x - sizeWindow.x / 2;
		if (x < leftBorder) {
			tempX = leftBorder;
		}
		else if (x > rightBorder) {
			tempX = rightBorder;
		}
	}
	else {
		tempX = centerWindow.x;
	}


	if (sizeImage.y * sizeCurrent.y > sizeWindow.y) 
	{
		float scale = 1 / sizeCurrent.y;
		float scaleForLowBorder = sizeCurrent.y;
		//topBorder + sizeImage.y * scaleForLowBorder - sizeWindow.y * scale
		int topBorder = centerWindow.y  - sizeImage.y / 2 * sizeCurrent.y + sizeWindow.y / 2 ;
		int lowBorder = centerWindow.y  + sizeImage.y / 2 * sizeCurrent.y - sizeWindow.y / 2 ;

		printf("x = %f, y = %f\n", scaleImage.x, scaleImage.y);
		printf("top = %d, low = %d\n", topBorder, lowBorder);
		if (y < topBorder) {
			tempY = topBorder;
		}
		else if (y > lowBorder) {
			tempY = lowBorder;
		}
	}
	else
	{
		tempY = centerWindow.y;
	}
	
	currentImage.setPosition(tempX, tempY);	
}

void actionZoomPlus(Program & program,Vector2f posMouse)
{
	printf("+\n");
	Vector2f &scaleImage = *program.scaleImage;
	Vector2f sizeCurrent = program.currentImage->getScale();

	if (sizeCurrent.x < MAX_SCALE) {
		program.isZoom = true;
		Vector2f scale = { sizeCurrent.x + SCALE_IMAGE, sizeCurrent.y + SCALE_IMAGE };
		scaleImage = scale;
		program.currentImage->setScale(scale);
	}
}

void actionZoomMinus(Program & program, Vector2f posMouse)
{
	printf("-\n");
	Vector2f &scaleImage = *program.scaleImage;
	Vector2f sizeCurrent = program.currentImage->getScale();

	if (sizeCurrent.x > NORMAL_SCALE) {
		program.isZoom = true;
		Vector2f scale = { sizeCurrent.x - SCALE_IMAGE, sizeCurrent.y - SCALE_IMAGE };
		scaleImage = scale;
		program.currentImage->setScale(scale);
	}
	else {
		Vector2f sizeWindow = Vector2f(program.window->getSize());
		program.currentImage->setPosition(sizeWindow.x / 2, sizeWindow.y / 2);
		program.isZoom = false;
	}

}

void destroyProgram(Program & program)
{
	delete &program;
}