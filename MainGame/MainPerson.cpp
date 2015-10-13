#include "MainPerson.h"

using namespace sf;
using namespace std;

////////////////////////////////////////////////////////////////////
// ���������� ���������
void initializeMainPerson(MainPerson & mainPerson, dataSound &databaseSound)
{
	mainPerson.spriteEntity = new Sprite;
	mainPerson.textureEntity = new Texture;

	// ������� �������
	mainPerson.height = 22;
	mainPerson.width = 22;

	mainPerson.radiusUse = 1;

	// �������� ������
	mainPerson.stepFirst = 150.f;
	mainPerson.stepCurrent = 150.f;
	mainPerson.timeAnimation = 0.f;

	// ������
	int posX(70), posY(70);
	mainPerson.view = new View;
	mainPerson.view->setSize(640, 480);
	mainPerson.view->setCenter(posX, posY);

	// ��������
	mainPerson.textureEntity->loadFromFile(texturePaths[idTexturePaths::mainPerson]);
	mainPerson.spriteEntity->setTexture(*mainPerson.textureEntity);
	mainPerson.spriteEntity->setTextureRect(IntRect(0, 0, mainPerson.width, mainPerson.height));

	// ����� 
	mainPerson.soundsEntity[idSoundEntity::stepGrass] = &databaseSound.sounds[idSoundEntity::stepGrass];
	mainPerson.soundsEntity[idSoundEntity::stepStone] = &databaseSound.sounds[idSoundEntity::stepStone];

	// ������� ��������� ��� �����
	mainPerson.idSelectItem = 0;

	// ������� � �����������
	mainPerson.currentLevelFloor = 0;
	mainPerson.currenMode = idModeEntity::build;
	mainPerson.spriteEntity->setPosition(posX, posY);
	mainPerson.direction = NONE;
}
////////////////////////////////////////////////////////////////////



void MainPerson::modeProcess(Field &field, list<UnlifeObject> *unlifeObjects, list<Item> *items, Event &eventPerson, float x, float y)
{
	Keyboard::Key pressKey = eventPerson.key.code;

	int isFloor;

	//printf("%f %f\n", getXPos(), getYPos());

	int xPosBlock = x / SIZE_BLOCK;
	int yPosBlock = y / SIZE_BLOCK;

	if (isInUseField(x, y)) {

		switch (currenMode) {
			////////////////////////////////////////////////////////////////////////////////////////////////
			// ������������ �����
		case idModeEntity::build:
			///////////////////////////////////////////////////
			// ��������� �����
			if (pressKey == Mouse::Left) {
				isFloor = 1;
			}
			// ��������� ����
			else if (pressKey == Mouse::Right) {
				isFloor = 0;
			}
			//
			else {
				isFloor = -1;
			}
			///////////////////////////////////////////////////
			if (isFloor >= 0) {
				//printf("%d %d\n", numberX, numberY);
				wchar_t currentBlock(u'\x00');
				switch (idSelectItem) {
				case 0:
					currentBlock = field.charBlocks[idBlocks::air];
					break;
				case 1:
					currentBlock = field.charBlocks[idBlocks::stone];
					break;
				case 2:
					currentBlock = field.charBlocks[idBlocks::stoneBrick];
					break;
				case 3:
					currentBlock = field.charBlocks[idBlocks::sand];
					break;
				case 4:
					currentBlock = field.charBlocks[idBlocks::dirt];
					break;
				case 5:
					currentBlock = field.charBlocks[idBlocks::woodBoard];
					break;
				case 6:
					currentBlock = field.charBlocks[idBlocks::woodLadder];
					break;
				case 9:
					currentBlock = u'\x99';
					break;
				default:
					break;
				}
				if (currentBlock != u'\x00') {
					field.dataMap[currentLevelFloor + isFloor][yPosBlock][xPosBlock] = currentBlock;
				}
			}
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////
			// ������ �����
		case idModeEntity::fight:
			// �������� �������� - �����, ���������� ����� ��� �������
			if (pressKey == Mouse::Left) {
				for (int l = 0; l < HEIGHT_MAP; l++) {
					////////////////////////////////////////////////////////////////////////
					// ���� ������ �� ������� ������
					// ������� ������ ��� �������
					if (l == currentLevelFloor + 1) {
						//////////////////////////////////////////////
						// �������
						if (field.isItem(x, y, items, findItem, findItemFromList, l)) {
							//////////////////////////////////
							// ���� ������� ������������ �� ...
							if (findItem->isDestroy) {
							}
							//////////////////////////////////
							// ����� ������ �������������
							else {
								Sprite &mainSprite = *findItem->mainSprite;
								if (mainSprite.getGlobalBounds().contains(x, y))//� ��� ���� ���������� ������� �������� � ������
								{
									printf("isClicked!\n");//������� � ������� ��������� �� ����

																				 //spriteObject.setPosition(x, y);
									dMoveItemX = x - mainSprite.getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
									dMoveItemY = y - mainSprite.getPosition().y;//���� ����� �� ������
									isMoveItem = true;//����� ������� ������							
								}
							}
							//////////////////////////////////
						}
						//////////////////////////////////////////////
						// ������
						else if (field.isObject(x, y, unlifeObjects, findObject, findObjectFromList, l)) {
							

							//////////////////////////////////
							// ���� ������ ������������ �� ...
							if (findObject->isDestroy) {

								printf("currentToughness %d and now %d\n", findObject->currentToughness, findObject->currentToughness - 1);

								// ��������� ���������
								if (findObject->currentToughness > 0) {
									findObject->currentToughness -= 1;
								}

								// ���������� ���� ��������� = 0
								if (findObject->currentToughness == 0) 
								{
									//printf("%s destroy \n", findObject->typeObject->nameType);
									//////////////////////////////////////////
									// ��������
									for (std::list<UnlifeObject>::iterator it = unlifeObjects->begin(); it != unlifeObjects->end(); ++it) {

										//if (&findElement != NULL) {
										if (it == findObjectFromList) {// �������
											unlifeObjects->erase(it);
											break;
										}

									}

								}
							//////////////////////////////////
							}
							//////////////////////////////////
							// ����� ������ �������������
							else {
								Sprite &spriteObject = *findObject->spriteObject;
								if (spriteObject.getGlobalBounds().contains(x, y))//� ��� ���� ���������� ������� �������� � ������
								{
									printf("isClicked!\n");//������� � ������� ��������� �� ����

																				 //spriteObject.setPosition(x, y);
									dMoveItemX = x - spriteObject.getPosition().x;//������ �������� ����� �������� ������� � �������.��� ������������� �������
									dMoveItemY = y - spriteObject.getPosition().y;//���� ����� �� ������
									isMoveItem = true;//����� ������� ������							
								}
							}
						///////////////////////////////////////////////////////////
						}
						///////////////////////////////////////////////////////////
					}
					////////////////////////////////////////////////////////////////////////		
				}
				//////////////////////////////////////////////////////////////
			}
			// 
			else if (pressKey == Mouse::Right) {
			}
			else {
			};
			break;
			////////////////////////////////////////////////////////////////////////////////////////////////
		default:
			break;
		}

	}
}



// �������������� � ����������
void MainPerson::actionMain(Field &field, int x, int y)
{
	if ((currentLevelFloor >= 0 && currentLevelFloor < HEIGHT_MAP - 1)
		&& (currentLevelFloor + 1 >= 1 && currentLevelFloor + 1 <= HEIGHT_MAP - 1))
	{

		if (field.dataMap[currentLevelFloor + 1][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			Vector2i noPos = { -1, -1 };
			Vector2i emptyPos = isEmptyFloor(field, currentLevelFloor + 1);
			//printf("%d %d\n", emptyPos.x, emptyPos.y);
			if (emptyPos != noPos)
			{
				currentLevelFloor += 1;
				spriteEntity->setPosition(emptyPos.x * SIZE_BLOCK, emptyPos.y * SIZE_BLOCK);
			}
		}

	}
}

void MainPerson::actionAlternate(Field &field, int x, int y)
{


	if ((currentLevelFloor > 0 && currentLevelFloor <= HEIGHT_MAP - 1)
		&& (currentLevelFloor + 1 > 1 && currentLevelFloor + 1 <= HEIGHT_MAP - 1))
	{

		if (field.dataMap[currentLevelFloor][y][x] == field.charBlocks[idBlocks::woodLadder])
		{
			Vector2i noPos = { -1, -1 };
			Vector2i emptyPos = isEmptyFloor(field, currentLevelFloor);
			//printf("%d %d\n", emptyPos.x, emptyPos.y);
			if (emptyPos != noPos)
			{
				currentLevelFloor -= 1;
				spriteEntity->setPosition(emptyPos.x * SIZE_BLOCK, emptyPos.y * SIZE_BLOCK);
			}
		}

	}
}
////////////////////////////////////////////////////////////////////

// ��������� ����� (�� ��������)
void MainPerson::computeAngle(RenderWindow &window)
{
	Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
	Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)

	float dX = pos.x - spriteEntity->getPosition().x - width / 2;//������ , ����������� ������, ������� ���������� ������ � ������
	float dY = pos.y - spriteEntity->getPosition().y - height / 2;//�� ��, ���������� y
	rotation = (atan2(dY, dX)) * 180 / PI;//�������� ���� � �������� � ��������� ��� � �������
}

////////////////////////////////////////////////////////////////////
// View
void MainPerson::getCoordinateForView(float x, float y)//������� ��� ���������� ��������� ������
{
	view->setCenter(x, y);//������ �� �������, ��������� ��� ����������. 
}

// �������� ���������� (�� ��������)
void MainPerson::viewmap(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view->move(0.1*time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view->move(0, 0.1*time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view->move(-0.1*time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view->move(0, -0.1*time);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
	}

}
// �������� ���������� (�� ��������)
void MainPerson::changeview()
{
	if (Keyboard::isKeyPressed(Keyboard::U)) {
		view->zoom(1.0100f); //������������, ����������
							 //view.zoom(1.0006f); //���� ����� ����������� ��������������
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		//view.setRotation(90);//����� �� ������ ������� ������
		view->rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
	}


	if (Keyboard::isKeyPressed(Keyboard::I)) {
		view->setSize(640, 480);//������������� ������ ������ (��� ��������)
	}

	if (Keyboard::isKeyPressed(Keyboard::P)) {
		view->setSize(540, 380);//�������� ������ ������
	}

}
////////////////////////////////////////////////////////////////////