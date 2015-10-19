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
	gui.arrowLeft->setTextureRect(IntRect(PIXEL_X_ARROW_GUI + WIDTH_ARROW_GUI, PIXEL_Y_ARROW_GUI, -WIDTH_ARROW_GUI, HEIGHT_ARROW_GUI));
	gui.arrowLeft->setOrigin(WIDTH_ARROW_GUI / 2, HEIGHT_ARROW_GUI / 2);

	gui.arrowRight->setTexture(*gui.textureArrow);
	gui.arrowRight->setTextureRect(IntRect(PIXEL_X_ARROW_GUI, PIXEL_Y_ARROW_GUI, WIDTH_ARROW_GUI, HEIGHT_ARROW_GUI));
	gui.arrowRight->setOrigin(WIDTH_ARROW_GUI / 2, HEIGHT_ARROW_GUI / 2);


	// »—œ–¿¬‹
	// Õ≈–¿¡Œ“¿≈“
	//gui.textGui[idTextGui::infoWindowBlockGui] = &textProgram.texts[idText::infoWindowBlock];
	//gui.textGui[idTextGui::infoWindowFloorGui] = &textProgram.texts[idText::infoWindowFloor];
	//gui.textGui[idTextGui::infoWindowUnlifeObjectGui] = &textProgram.texts[idText::infoWindowUnlifeObject];
	//gui.textGui[idTextGui::infoWindowItemGui] = &textProgram.texts[idText::infoWindowItemGui];
}