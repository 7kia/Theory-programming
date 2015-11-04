#include "Program.h"

using namespace sf;
using namespace std;

void initializeProgram(Program & program, char argv[256])
{

	program.currentFolder = argv;

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

	program.pathsImages = new list<string>;

	initializeTexts(*program.textProgram);

	printf("path %s\n", program.currentFolder);// ИСПРАВЬ

	char stringInput[SIZE_STRING];
	for (size_t j = 0; j < AMOUNT_FORMATS; j++) {

		strcpy_s(stringInput, program.currentFolder);
		strcat_s(stringInput, MASK);
		strcat_s(stringInput, formats[j]);
		program.searchImage(stringInput); 
		if (program.textProgram->texts[idText::errorText].getString() == INVALID_PATH) {
			break;
		}
		// Очистка строки перед следующим использованием
		for (size_t i = 0; i < SIZE_STRING; i++) {
			stringInput[i] = 0;
		}

	}
	

	// По умолчанию первая попавшаяся картинка
	program.currentPath = program.pathsImages->begin();

	initializeGUI(*program.gui);
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
	else {
		textProgram->texts[idText::errorText].setString(INVALID_PATH);
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

			//////////////////////////////////////////
			// Размер изображения
			std::fstream fp(*it, std::fstream::in);
			fp.seekp(0, std::ios::end);
			long size = fp.tellp();

			program.sizeFile = size;
			//////////////////////////////////////////
			std::cout << "currrent image:" << program.currentFolder + *it << std::endl;// ИСПРАВЬ

			if (program.textureCurrentImage->loadFromFile(program.currentFolder + *it)) {
				if (*it != program.currentTitle) {
					program.currentTitle = *it;
					program.newPath = program.currentFolder + *it;
					program.window->setTitle(*it);
				}

			} else {
				Vector2u sizeImage = program.textureCurrentImage->getSize();

				// Если изображение слишком большое
				if (size < 4 * 1024 * 1024) {
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
	int shiftZoom = 8;
	Vector2f &scaleImage = *program.scaleImage;
	Vector2f &sourseScale = *program.sourseScale;

	arrowLeft.setPosition(pos.x - WIDTH_GUI_ELEMENT / 2 - shiftArrows, pos.y + sizeWindow.y / 2 - HEIGHT_GUI_ELEMENT - shiftText);
	arrowRight.setPosition(pos.x + WIDTH_GUI_ELEMENT / 2 + shiftArrows, pos.y + sizeWindow.y / 2 - HEIGHT_GUI_ELEMENT - shiftText);

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
void destroyProgram(Program & program)
{
	delete &program;
}