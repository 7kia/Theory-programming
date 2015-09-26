///////////////////////////////////////////////////////
// Переменные для генерации карт
const int border(2);
const int amountShips(10), sizeRectangleWeb(12 + border); 
const int amountEveryType[] = { 4, 3, 2, 1 };
char myPlace[sizeRectangleWeb][sizeRectangleWeb];// Поля
char enemyPlace[sizeRectangleWeb][sizeRectangleWeb];
int coordinatesMyShips[amountShips][4];// Храним начало и конец корябля
int coordinatesEnemyShips[amountShips][4];
///////////////////////////////////////////////////////

////////////////////////////////////////
// Переменные нужные противнику
int countMyDestroyShips(0), countEnemyDestroyShips(0);// Счётчик моих и вражеских кораблей
int victoryNumber(10);// Число поражённых клеток необходимое для победы
int lastTile[] = { -1, -1 };// первая ячейка поражённая в этом ходу
int direction, x, y;// направление корабля
bool findDirection(false);
bool directionNotRedefine(true);
bool findShip(false);// Если корабль длиннее 2 клеток то уничтожаем остальную часть
int memberDirection[] = { 0, 0, 0 };
/////////////////////////////////////////

/////////////////////////////////////////
// Состояния игры
bool gameNotFinish(true);
bool myQueue(true);
/////////////////////////////////////////

/////////////////////////////////////////
// Для выдачи сообщений о поражённых игроком кораблях
bool isFindStart(false);
bool isNotFindEnd(true);
bool isNotDestroyShip(true);
int countTile(0);
/////////////////////////////////////////

enum stateTile
{
	Unknow,
	Empty,
	isShip,
	shipDestroy
};

enum direction
{
	None,
	Up,
	Down,
	Left,
	Right,
	Up_Left,
	Up_Right,
	Down_Left,
	Down_right
};