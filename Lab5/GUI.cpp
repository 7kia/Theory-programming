#include "GUI.h"

using namespace sf;

void GUI::createZoomButtons()
{	
	texturePlus = new Texture;
	plus = new Sprite;

	texturePlus->loadFromFile(path[idPathGui::plusGui]);
	plus->setTexture(*texturePlus);
	plus->setTextureRect(IntRect(PIXEL_X_GUI + WIDTH_GUI_ELEMENT, PIXEL_Y_GUI, -WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	plus->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);


	textureMinus = new Texture;
	minus = new Sprite;

	textureMinus->loadFromFile(path[idPathGui::minusGui]);
	minus->setTexture(*textureMinus);
	minus->setTextureRect(IntRect(PIXEL_X_GUI + WIDTH_GUI_ELEMENT, PIXEL_Y_GUI, -WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	minus->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);
}

void GUI::createArrows()
{
	textureArrow = new Texture;
	arrowLeft = new Sprite;
	arrowRight = new Sprite;

	textureArrow->loadFromFile(path[idPathGui::arrowGui]);
	arrowLeft->setTexture(*textureArrow);
	arrowLeft->setTextureRect(IntRect(PIXEL_X_GUI + WIDTH_GUI_ELEMENT, PIXEL_Y_GUI, -WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	arrowLeft->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);

	arrowRight->setTexture(*textureArrow);
	arrowRight->setTextureRect(IntRect(PIXEL_X_GUI, PIXEL_Y_GUI, WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	arrowRight->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);
}

void initializeGUI(GUI &gui)
{
	gui.createArrows();
	gui.createZoomButtons();
}
