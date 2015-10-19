#include "Program.h"

using namespace sf;
using namespace std;

void initializeProgram(Program & program)
{
	unsigned int width = program.widthMainWindow;
	unsigned int height = program.heightMainWindow;
	program.window = new RenderWindow(VideoMode(width, height), TITLE_PROGRAM);

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
	strcpy_s(stringInput, currentFolder);
	strcat_s(stringInput, MASK);
	strcat_s(stringInput, formats[0]);
	program.searchImage(stringInput);

	// По умолчанию первая попавшаяся картинка
	program.currentPath = program.pathsImages->begin();

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
	Vector2u centerWindow = { sizeWindow.x / 2, sizeWindow.y / 2};

	// Выбор текущего изображения
	list<string>& pathsImages = *program.pathsImages;

	// ИСПРАВЬ
	for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
		if (program.currentPath == it) {
			program.textureCurrentImage->loadFromFile(*it);
			program.textProgram->texts[idText::currentImageGui].setString(*it);
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



	// Масштабирование изображения
	if (sizeImage.x + WIDTH_ARROW_GUI + 100 > sizeWindow.x) {
		scaleImage = {(float)sizeImage.x / sizeWindow.x,  (float)sizeImage.x / sizeWindow.x };
		sourseScale = { 1 / scaleImage.x ,  1 / scaleImage.x };
		program.currentImage->setScale(scaleImage);
	}
	else if (sizeImage.y + HEIGHT_ARROW_GUI + 100 > sizeWindow.y) {
		scaleImage = {(float)sizeImage.y / sizeWindow.y,  (float)sizeImage.y / sizeWindow.y };
		sourseScale = { 1 / scaleImage.y ,  1 / scaleImage.y };
		program.currentImage->setScale(scaleImage);
	}
	else {
		program.currentImage->setScale(sourseScale);
		sourseScale = { 1.f, 1.f };
		scaleImage = { 1.f, 1.f };
	}
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

	int shiftArrows = 8;
	Vector2f &scaleImage = *program.scaleImage;
	Vector2f &sourseScale = *program.sourseScale;
	arrowLeft.setScale(scaleImage);
	arrowLeft.setPosition(pos.x - scaleImage.x * sizeImage.x / 2 - shiftArrows - WIDTH_ARROW_GUI, pos.y);
	arrowRight.setScale(scaleImage);
	arrowRight.setPosition(pos.x + scaleImage.x * sizeImage.x / 2 + shiftArrows + WIDTH_ARROW_GUI, pos.y);


	// Размещение текста
	TextProgram& textProgram = *program.textProgram;
	list<std::string>& pathsImages = *program.pathsImages;

	// Абсолютный путь каталога
	pos = centerWindow;
	Text& currentText = textProgram.texts[idText::currentImageGui];
	string inputString = textProgram.texts[idText::currentImageGui].getString();// ИСПРаВЬ

	// Определение количества символов
	int sizeString = 0;
	for (int i = 0; i < SIZE_STRING; i++) {
		if (inputString[i] != '\0') {
			sizeString += 1;
		}
		else {
			break;
		}
	}

	currentText = textProgram.texts[idText::currentImageGui];
	pos.y += sizeWindow.y / 2 - currentText.getCharacterSize() - shiftText;

	int widthText = currentText.getCharacterSize() * sizeString ;
	pos.x -= widthText / 4;
	currentText.setString(inputString);
	currentText.setPosition(pos);

}

void actionRight(Program & program) {

	list<string>& pathsImages = *program.pathsImages;
	for (std::list<string>::iterator it = pathsImages.begin(); it != pathsImages.end(); ++it) {
		if (program.currentPath == it && it != pathsImages.end()) {
			it++;
			if (it != pathsImages.end()) {
				program.currentPath = it;
				program.textureCurrentImage->loadFromFile(*it);
				program.textProgram->texts[idText::currentImageGui].setString(*it);
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
			program.textProgram->texts[idText::currentImageGui].setString(*it);
		}
	}

}

void destroyProgram(Program & program)
{
	delete &program;
}