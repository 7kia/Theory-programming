#pragma once
const int NUMBER_TYPE_BLOCKS = 256;

const int MAX_UNLIFE_OBJECT = 256;
const int AMOUNT_TYPES_UNLIFE_OBJECT = 15;

// выросший дуб
const int WIDTH_OAK = 136;
const int HEIGHT_OAK = 208;

const int PIXEL_X_OAK = 0;
const int PIXEL_Y_OAK = 0;

const int WIDTH_OAK_STUMP = 47;
const int HEIGHT_OAK_STUMP = 30;
const int PIXEL_X_OAK_STUMP = 0;
const int PIXEL_Y_OAK_STUMP = 208;
// маленький дуб
const int WIDTH_SMALL_OAK = 115;
const int HEIGHT_SMALL_OAK = 142;

const int PIXEL_X_SMALL_OAK = WIDTH_OAK;
const int PIXEL_Y_SMALL_OAK = 0;

// саженец дуба
const int WIDTH_SEADLING_OAK = 58;
const int HEIGHT_SEADLING_OAK = 101;

const int PIXEL_X_SEADLING_OAK = WIDTH_SMALL_OAK + WIDTH_OAK;
const int PIXEL_Y_SEADLING_OAK = 0;


typedef enum
{
	oakSeadling,
	oakSmall,
	oakGrow,
	smallStone,
	empty
} idUnlifeObject;