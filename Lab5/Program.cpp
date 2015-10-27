#include "Program.h"

const char currentFolder[] = "c:\\Study\\ИиП\\Programs\\Lab4\\Lab4\\";

using namespace sf;
using namespace std;

void initializeProgram(Program & program)
{
	unsigned int width = program.widthMainWindow;
	unsigned int height = program.heightMainWindow;
	program.window = new RenderWindow(VideoMode(width, height), TITLE_PROGRAM);
	program.currentTitle = TITLE_PROGRAM;

	program.view.setCenter(width / 2, height / 2);
	program.view.setSize(width, height);

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

	char stringInput[SIZE_STRING];
	for (size_t j = 0; j < AMOUNT_FORMATS; j++) {

		strcpy_s(stringInput, currentFolder);
		strcat_s(stringInput, MASK);
		strcat_s(stringInput, formats[j]);
		program.searchImage(stringInput); 
		// Очистка строки перед следующим использованием
		for (size_t i = 0; i < SIZE_STRING; i++) {
			stringInput[i] = 0;
		}

	}
	

	// По умолчанию первая попавшаяся картинка
	program.currentPath = program.pathsImages->begin();

	//
	program.window->setView(program.view);

	initializeGUI(*program.gui);
	initializeTexts(*program.textProgram);
	initializeImage(program);
}

void Program::searchImage(const char *path)
{
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {

			printf("%s: %s\n", (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "Folder" : "File", fd.cFileName);
			(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "Folder" : "File", pathsImages->push_back(fd.cFileName);// ИСПРАВЬ
			//if ((fd.dwFileAttributes ) == "File") {

			//}
		}
		while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	}

};

void initializeImage(Program & program)
{
	Vector2u sizeWindow = program.window->getSize();
	Vector2u centerWindow = { sizeWindow.x / 2, sizeWindow.y / 2 };

	// Выбор текущего изображения
	list<string>& pathsImages = *program.pathsImages;

	for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
		if (program.currentPath == it) {

			unsigned int width = program.widthMainWindow;
			unsigned int height = program.heightMainWindow;

			if (program.textureCurrentImage->loadFromFile(*it)) {
				if (*it != program.currentTitle) {
					program.currentTitle = *it;
					program.newPath = *it;
					program.window->setTitle(*it);
				}

			} else {
				Vector2u sizeImage = program.textureCurrentImage->getSize();

				// Если изображение слишком большое
				if (sizeImage.x < sf::Texture::getMaximumSize()
						|| sizeImage.y < sf::Texture::getMaximumSize()) {
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

	Vector2f &scaleImage = *program.scaleImage;
	Vector2f &sourseScale = *program.sourseScale;

	Vector2u sizeImage = program.textureCurrentImage->getSize();
	//sizeImage = { sizeImage.x * sourseScale.x , sizeImage.y * sourseScale.y };
	program.currentImage->setPosition((Vector2f)centerWindow);
	program.currentImage->setOrigin(sizeImage.x / 2, sizeImage.y / 2);
	program.currentImage->setTextureRect(IntRect(0, 0, sizeImage.x, sizeImage.y));

	program.view.setCenter((Vector2f)centerWindow);
	program.view.setSize((Vector2f)sizeWindow);
	program.window->setView(program.view);


	/*
	// Масштабирование изображения
	int shiftBorder = 200;
	if (sizeImage.x + WIDTH_GUI_ELEMENT + shiftBorder > sizeWindow.x) {
		scaleImage = { (float)sizeImage.x / sizeWindow.x,  (float)sizeImage.x / sizeWindow.x };
		sourseScale = { 1.f , 1.f };
		program.currentImage->setScale(scaleImage);
	} else if (sizeImage.y + HEIGHT_GUI_ELEMENT + shiftBorder > sizeWindow.y) {
		scaleImage = { (float)sizeImage.y / sizeWindow.y,  (float)sizeImage.y / sizeWindow.y };
		sourseScale = { 1.f ,  1.f };
		program.currentImage->setScale(scaleImage);
	} else {
		program.currentImage->setScale(sourseScale);
		sourseScale = { 1.f, 1.f };
		scaleImage = { 1.f, 1.f };
	}
	*/
	


}

void setPositionGui(Program & program)
{
	RenderWindow& window = *program.window;
	Vector2u sizeWindow = program.window->getSize();
	Vector2f centerWindow = window.getView().getCenter();//{ sizeWindow.x / 2, sizeWindow.y / 2 };

	// Определение позиции картинки
	Vector2f pos = centerWindow;
	// Сдвиг текста
	const int shiftText = 20;

	// Положение стрелок
	Vector2u sizeImage = program.textureCurrentImage->getSize();
	Sprite& arrowLeft = *program.gui->arrowLeft;
	Sprite& arrowRight = *program.gui->arrowRight;
	Sprite& plus = *program.gui->plus;
	Sprite& minus = *program.gui->minus;

	int shiftArrows = 8;
	int shiftZoom = 8;
	Vector2f &scaleImage = *program.scaleImage;
	Vector2f &sourseScale = *program.sourseScale;

	arrowLeft.setPosition(pos.x - WIDTH_GUI_ELEMENT / 2 - shiftArrows, pos.y + sizeWindow.y / 2 - HEIGHT_GUI_ELEMENT - shiftText);
	arrowRight.setPosition(pos.x + WIDTH_GUI_ELEMENT / 2 + shiftArrows, pos.y + sizeWindow.y / 2 - HEIGHT_GUI_ELEMENT - shiftText);

	plus.setPosition(pos.x + sizeWindow.x / 2 - WIDTH_GUI_ELEMENT - shiftZoom, pos.y + sizeWindow.y / 2 - HEIGHT_GUI_ELEMENT - shiftZoom);
	minus.setPosition(pos.x + sizeWindow.x / 2 - 2 * WIDTH_GUI_ELEMENT - shiftZoom, pos.y + sizeWindow.y / 2 - HEIGHT_GUI_ELEMENT - shiftZoom);
	// Размещение текста
	TextProgram& textProgram = *program.textProgram;
	list<std::string>& pathsImages = *program.pathsImages;

	if (program.currentTitle == TITLE_PROGRAM) {
		// Текст ошибки
		pos = centerWindow;
		Text& currentText = textProgram.texts[idText::errorText];
		string inputString = currentText.getString();// ИСПРаВЬ

		// Определение количества символов
		int sizeString = 0;
		for (int i = 0; i < SIZE_STRING; i++) {
			if (inputString[i] != '\0') {
				sizeString += 1;
			} else {
				break;
			}
		}

		//pos.y += sizeWindow.y / 2 - currentText.getCharacterSize() - shiftText;

		int widthText = currentText.getCharacterSize() * sizeString;
		pos.x -= widthText / 4;
		currentText.setPosition(pos);

	}


}

void actionRight(Program & program) {

	list<string>& pathsImages = *program.pathsImages;
	for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
		if (program.currentPath == it && it != pathsImages.end()) {
			it++;
			if (it != pathsImages.end()) {
				program.currentPath = it;
				program.textureCurrentImage->loadFromFile(*it);
				program.window->setTitle(*it);
			}
			else {
				it--;
			}

		}
	}

}

void actionLeft(Program & program) {

	list<string>& pathsImages = *program.pathsImages;
	for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
		if (program.currentPath == it && it != pathsImages.begin()) {
			it--;
			program.currentPath = it;
			program.textureCurrentImage->loadFromFile(*it);
			program.window->setTitle(*it);
		}
	}

}

void updateView(Program & program, const Time & deltaTime)
{
	RenderWindow& window = *program.window;
	View& view = program.view;
	Vector2f sizeWindow = (Vector2f)program.window->getSize();
	Vector2f centerWindow = window.getView().getCenter();

	Vector2f sizeImage = (Vector2f)program.textureCurrentImage->getSize();
	Vector2f scaleImage = *program.sourseScale;

	view.setSize(sizeWindow);// ИСПРАВЬ

	float tempX = view.getCenter().x;
	float tempY = view.getCenter().y;// Текущие координаты

	float x = tempX;
	float y = tempY;

	/*

	int leftBorder = sizeWindow.x / 2;
	int rightBorder = scaleImage.x * sizeImage.x / 2 - sizeWindow.x;// - sizeWindow.x / 2
	int topBorder = sizeWindow.y / 2;
	int lowBorder = scaleImage.y * sizeImage.y / 2 - sizeWindow.y / 2;// - sizeWindow.y / 2

	if (x < leftBorder) tempX = leftBorder;//убираем из вида левую сторону
	else if (x > rightBorder) tempX = rightBorder;//убираем из вида левую сторону
	if (y < topBorder) tempY = topBorder;//верхнюю сторону
	else if (y > lowBorder) tempY = lowBorder;//нижнюю сторону	
	//*/

	view.setSize(sizeWindow);
	view.setCenter(tempX, tempY);
	window.setView(view);
}

void actionZoomPlus(Program & program) 
{
	printf("+\n");
	Vector2f scale = { 1.5f, 1.5f };
	program.currentImage->setScale(scale);
	program.view.zoom(1.5f);
}

void actionZoomMinus(Program & program)
{
	printf("-\n");
	Vector2f scale = { 0.5f, 0.5f };
	program.currentImage->setScale(scale);
	program.view.zoom(0.67f);
}

void destroyProgram(Program & program)
{
	delete &program;
}