#include <SFML/Graphics.hpp>

#include "Program.h"

using namespace sf;

const Time TIME_PER_FRAME = seconds(1.f / 60.f);

using namespace sf;
using namespace std;


void processEvents(Program &program, const Time & deltaTime)
{
	Event event;
	RenderWindow &window = *program.window;
	while (window.pollEvent(event)) {
		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(mousePos);

		Keyboard::Key pressKey = event.key.code;

		Text& textError = program.textProgram->texts[idText::errorText];
		if (textError.getString() != DIRECTORY_EMPTY) {
			///////////////////////////////////////////////////
			// ��������� ���� �������
			if (event.type == Event::KeyPressed) {
				if (pressKey == Keyboard::Left) {
					actionLeft(program);
				} else if (pressKey == Keyboard::Right) {
					actionRight(program);
				} else if (pressKey == Keyboard::Add) {
					actionZoomPlus(program, pos);
				} else if (pressKey == Keyboard::Subtract) {
					actionZoomMinus(program, pos);
				}
			}

			if (event.type == Event::MouseMoved && program.isShift && program.isZoom) {// 
				//if (pressKey == Keyboard::Left) {
				View& view = program.view;
				///////////////////////////////////////////////
				Vector2f movemoment = { 0.f, 0.f };

				/*
				
				view.move(program.shiftMouse.x, program.shiftMouse.y);
				window.setView(view);
				program.xMouse = pos.x;
				program.yMouse = pos.y;

if (mousePos.x < 20) {
					printf("mousePos.x < 20");
					movemoment = { -SHIFT_VIEW * deltaTime.asSeconds(), 0.f };
					view.move(movemoment);//���� ������ �������� � ����� ���� ������,�� ������� ������ �����
					window.setView(view);
				} else if (mousePos.x > window.getSize().x - 20) {
					movemoment = { SHIFT_VIEW * deltaTime.asSeconds(), 0.f };
					view.move(movemoment);//������ ����-������
					window.setView(view);
				}
				if (mousePos.y > window.getSize().y - 20) {
					movemoment = { 0.f, SHIFT_VIEW * deltaTime.asSeconds() };
					view.move(movemoment);//������ ���� - ����
					window.setView(view);
				} else if (mousePos.y < 20) {
					movemoment = { 0.f, -SHIFT_VIEW * deltaTime.asSeconds() };
					view.move(movemoment);//������� ���� - �����
					window.setView(view);
				}
				//*/
				
				program.newPositionMouse = pos;

				if (program.oldPositionMouse.x > program.newPositionMouse.x) {
					movemoment.x = -SPEED_SHIFT;
				}
					
				if (program.oldPositionMouse.x < program.newPositionMouse.x) {
					movemoment.x = +SPEED_SHIFT;
				}
				if (program.oldPositionMouse.y > program.newPositionMouse.y) {
					movemoment.y = -SPEED_SHIFT;
				}
				if (program.oldPositionMouse.y < program.newPositionMouse.y) {
					movemoment.y = +SPEED_SHIFT;
				}
				
				program.oldPositionMouse = pos;

				program.currentImage->move(movemoment);
				///////////////////////////////////////////////
				updateView(program, deltaTime);
			}
			
			if (Mouse::isButtonPressed(Mouse::Left)) {
				program.oldPositionMouse.x = pos.x;
				program.oldPositionMouse.y = pos.y;
				program.isShift = true;
			} else {
				program.isShift = false;
			} 

			if (event.type == Event::MouseButtonPressed) {
				if (pressKey == Mouse::Left) {
					Sprite &arrowLeft = *program.gui->arrowLeft;
					Sprite &arrowRight = *program.gui->arrowRight;
					Sprite &plus = *program.gui->plus;
					Sprite &minus = *program.gui->minus;
					if (arrowLeft.getGlobalBounds().contains(pos)) {
						actionLeft(program);
					} else if (arrowRight.getGlobalBounds().contains(pos)) {
						actionRight(program);
					} else if (plus.getGlobalBounds().contains(pos)) {
						actionZoomPlus(program, pos);
					} else if (minus.getGlobalBounds().contains(pos)) {
						actionZoomMinus(program, pos);
					}
				}
			}

			///////////////////////////////////////////////////
		}

		/////////////////////////////////////////////////////////////
		// ��� ���������� ����
		if (event.type == sf::Event::Resized) {
			unsigned int width = window.getSize().x;
			unsigned int height = window.getSize().y;
			program.widthMainWindow = width;// �������
			program.heightMainWindow = height;
			window.create(VideoMode(width, height), program.currentTitle);
		}
		/////////////////////////////////////////////////////////////


		// ���� �������
		if (event.type == Event::Closed) {
			window.close();
		}

	}
}

void render(Program & program)
{
	RenderWindow &window = *program.window;
	window.clear(COLOR_GREY);

	//////////////////////////////////////////////
	// GUI
	setPositionGui(program);

	if(program.isZoom == false)
	{
		window.draw(*program.gui->arrowLeft);
	window.draw(*program.gui->arrowRight);
	window.draw(*program.gui->plus);
	window.draw(*program.gui->minus);
	}
	
	if (program.currentTitle != TITLE_PROGRAM) {
		window.draw(*program.currentImage);
	}


	//////////////////////////////////////////////
	// ����� GUI
	for (size_t i = 0; i < idText::amountTextsGui; i++) {
		if (i != idText::errorText || program.currentTitle == TITLE_PROGRAM) {
			window.draw(program.textProgram->texts[i]);
		}
	}

	window.display();
}

void startProgram()
{
	Program *mainProgram = new Program();
	initializeProgram(*mainProgram);
	// ���� ��� �����������
	Text* textError = &mainProgram->textProgram->texts[idText::errorText];
	if (textError->getString() != INVALID_PATH) {
		if (mainProgram->pathsImages->end() == mainProgram->pathsImages->begin()) {
			textError->setString(DIRECTORY_EMPTY);// �������
		} else {
			textError->setString("");
			initializeImage(*mainProgram);
			printf("sdf\n");
		}
	}
	RenderWindow &window = *mainProgram->window;

	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;

	while (window.isOpen())
	{
		
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TIME_PER_FRAME)
			{
				timeSinceLastUpdate -= TIME_PER_FRAME;
				processEvents(*mainProgram, TIME_PER_FRAME);
				if (textError->getString() != DIRECTORY_EMPTY && textError->getString() != INVALID_PATH) {
					if (*mainProgram->currentPath != mainProgram->newPath) {
						initializeImage(*mainProgram);
						printf("sdf\n");
					}
				}

			}
		
		
		render(*mainProgram);
	}
	destroyProgram(*mainProgram);
}

int main()
{
	startProgram();
	return 0;
}

