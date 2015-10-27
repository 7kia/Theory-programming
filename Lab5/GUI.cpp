#include "GUI.h"

using namespace sf;

void initializeGUI(GUI &gui)
{
	// »ÌÙÓÏ‡ˆËˇ Ó ‚˚‰ÂÎÂÌÓÏ ·ÎÓÍÂ
	gui.textureArrow = new Texture;
	gui.arrowLeft = new Sprite;
	gui.arrowRight = new Sprite;

	gui.textureArrow->loadFromFile(path[idPath::arrowGui]);
	gui.arrowLeft->setTexture(*gui.textureArrow);
	gui.arrowLeft->setTextureRect(IntRect(PIXEL_X_GUI + WIDTH_GUI_ELEMENT, PIXEL_Y_GUI, -WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	gui.arrowLeft->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);

	gui.arrowRight->setTexture(*gui.textureArrow);
	gui.arrowRight->setTextureRect(IntRect(PIXEL_X_GUI, PIXEL_Y_GUI, WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	gui.arrowRight->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);


	gui.texturePlus = new Texture;
	gui.plus = new Sprite;

	gui.texturePlus->loadFromFile(path[idPath::plusGui]);
	gui.plus->setTexture(*gui.texturePlus);
	gui.plus->setTextureRect(IntRect(PIXEL_X_GUI + WIDTH_GUI_ELEMENT, PIXEL_Y_GUI, -WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	gui.plus->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);


	gui.textureMinus = new Texture;
	gui.minus = new Sprite;

	gui.textureMinus->loadFromFile(path[idPath::minusGui]);
	gui.minus->setTexture(*gui.textureMinus);
	gui.minus->setTextureRect(IntRect(PIXEL_X_GUI + WIDTH_GUI_ELEMENT, PIXEL_Y_GUI, -WIDTH_GUI_ELEMENT, HEIGHT_GUI_ELEMENT));
	gui.minus->setOrigin(WIDTH_GUI_ELEMENT / 2, HEIGHT_GUI_ELEMENT / 2);
	// »—œ–¿¬‹
	// Õ≈–¿¡Œ“¿≈“
	//gui.textGui[idTextGui::infoWindowBlockGui] = &textProgram.texts[idText::infoWindowBlock];
	//gui.textGui[idTextGui::infoWindowFloorGui] = &textProgram.texts[idText::infoWindowFloor];
	//gui.textGui[idTextGui::infoWindowUnlifeObjectGui] = &textProgram.texts[idText::infoWindowUnlifeObject];
	//gui.textGui[idTextGui::infoWindowItemGui] = &textProgram.texts[idText::infoWindowItemGui];
}